#include "main.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "patch.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "rando/seedList.h"
#include "tools.h"
#include "tp/d_com_inf_game.h"
#include "tp/f_ap_game.h"
#include "tp/f_op_scene_req.h"
#include "tp/f_pc_node_req.h"
#include "tp/m_do_controller_pad.h"

namespace mod
{
    // Bind extern global variables
    libtp::display::Console console( 9 );
    rando::Randomizer* randomizer = nullptr;
    rando::SeedList* seedList = nullptr;

    // Variables
    uint32_t lastButtonInput = 0;
    bool consoleState = true;
    uint8_t gameState = GAME_BOOT;

    // Function hook return trampolines
    void ( *return_fapGm_Execute )( void ) = nullptr;
    bool ( *return_do_Link )( libtp::tp::dynamic_link::DynamicModuleControl* dmc ) = nullptr;

    void main()
    {
        // Display some info
        console << "Welcome to TPR!\n"
                << "(C) AECX, Lunar Soap, Zephiles\n\n"
                << "Note:\n"
                << "Please avoid [re]starting rando unnecessarily\n"
                << "on ORIGINAL HARDWARE as it wears down your\n"
                << "Memory Card!\n\n";

        // Just hook functions for now
        hookFunctions();

        // Generate our seedList
        seedList = new rando::SeedList();
    }

    void hookFunctions()
    {
        // Hook functions
        return_fapGm_Execute = libtp::patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, mod::handle_fapGm_Execute );
        return_do_Link = libtp::patch::hookFunction( libtp::tp::dynamic_link::do_link, handle_do_Link );
    }

    void setScreen( bool state )
    {
        consoleState = state;
        libtp::display::setConsole( state, 0 );
    }

    void doInput( uint32_t input )
    {
        using namespace libtp::tp::m_do_controller_pad;
        auto checkBtn = [&input]( uint32_t combo ) { return ( input & combo ) == combo; };

        if ( input && gameState == GAME_TITLE )
        {
            // Handle seed selection if necessary
            if ( seedList->m_numSeeds > 1 )
            {
                if ( checkBtn( Button_X ) )
                {
                    seedList->m_selectedSeed++;

                    if ( seedList->m_selectedSeed >= seedList->m_numSeeds )
                        seedList->m_selectedSeed = 0;
                }
                else if ( checkBtn( Button_Y ) )
                {
                    if ( seedList->m_selectedSeed == 0 )
                        seedList->m_selectedSeed = seedList->m_numSeeds;

                    seedList->m_selectedSeed--;
                }

                // 8 is the line it typically appears
                console.setLine( 8 );
                console << "\r"
                        << "[" << seedList->m_selectedSeed + 1 << "/" << seedList->m_numSeeds
                        << "] Seed: " << seedList->m_seedInfo[seedList->m_selectedSeed].header.seed << "\n";
            }
        }
        // End of handling title screen inputs
    }

    void handle_fapGm_Execute()
    {
        using namespace libtp;
        using namespace tp::m_do_controller_pad;
        using namespace tp::d_com_inf_game;

        // Load relevant pointers locally for faster access
        CPadInfo* padInfo = &cpadInfo;
        GameInfo* gameInfo = &dComIfG_gameInfo;

        // Handle game state updates
        using namespace libtp::tp::f_pc_node_req;

        if ( l_fpcNdRq_Queue )
        {
            // Previous state
            uint8_t prevState = gameState;
            uint8_t state = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( l_fpcNdRq_Queue ) + 0x59 );

            // Normal/Loading into game
            if ( prevState != GAME_ACTIVE && state == 11 )
            {
                // check whether we're in title screen CS
                if ( 0 != strcmp( "S_MV000", gameInfo->nextStageVars.nextStage ) )
                {
                    gameState = GAME_ACTIVE;
                }
            }
            else if ( prevState != GAME_TITLE && ( state == 12 || state == 13 ) )
            {
                gameState = GAME_TITLE;

                // Handle console differently when the user first loads it
                if ( prevState == GAME_BOOT )
                {
                    switch ( seedList->m_numSeeds )
                    {
                        case 0:
                            // Err, no seeds
                            console << "No seeds available! Please check your memory card and region!\n";
                            setScreen( true );
                            break;

                        case 1:
                            // Only one seed present, auto-select it and disable console for convenience
                            console << "First and only seed automatically applied...\n";
                            setScreen( false );
                            break;

                        default:
                            // User has to select one of the seeds

                            console << "Please select a seed <X/Y>\n";
                            // trigger a dummy input to print the current selection
                            doInput( Button_Start );

                            setScreen( true );
                            break;
                    }
                }
            }
        }
        // End of handling gameStates

        // handle button inputs only if buttons are being held that weren't held last time
        if ( padInfo->buttonInput != lastButtonInput )
        {
            // Store before processing since we (potentially) un-set the padInfo values later
            lastButtonInput = padInfo->buttonInput;

            // Special combo to (de)activate the console should be handled first
            if ( ( padInfo->buttonInput & ( PadInputs::Button_R | PadInputs::Button_Z ) ) ==
                 ( PadInputs::Button_R | PadInputs::Button_Z ) )
            {
                // Disallow during boot as we print copyright info etc.
                // Will automatically disappear if there is no seeds to select from
                setScreen( !consoleState || gameState == GAME_BOOT );
            }
            // Handle Inputs if console is already active
            else if ( consoleState )
            {
                doInput( padInfo->buttonInput );

                // Disable input so game doesn't notice
                padInfo->buttonInput = 0;
                padInfo->buttonInputTrg = 0;
            }
        }

        // Handle rando state
        if ( gameState == GAME_ACTIVE )
        {
            if ( seedList->m_numSeeds > 0 && !randomizer && !tp::f_op_scene_req::isLoading )
            {
                randomizer = new rando::Randomizer( &seedList->m_seedInfo[seedList->m_selectedSeed] );
            }
        }
        else if ( randomizer )
        {
            delete randomizer;
            randomizer = nullptr;
        }

        return return_fapGm_Execute();
    }

    bool handle_do_Link( libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        // Call the original function immediately, as the REL file needs to be linked before applying patches
        const bool result = return_do_Link( dmc );

        // TODO: Implementation of dynamic module overrides

        return result;
    }
}     // namespace mod