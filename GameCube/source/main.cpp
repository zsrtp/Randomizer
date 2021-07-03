#include "main.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "patch.h"
#include "tp/d_com_inf_game.h"
#include "tp/f_ap_game.h"
#include "tp/m_do_controller_pad.h"

namespace mod
{
    // Bind extern global variables
    libtp::display::Console console;
    rando::Randomizer* randomizer = nullptr;

    // Variables
    uint32_t lastButtonInput = 0;
    bool consoleState = true;
    uint8_t gameState = GAME_BOOT;

    // Function hook return trampolines
    void ( *return_fapGm_Execute )( void ) = nullptr;

    void main()
    {
        // Just hook functions for now
        hookFunctions();
    }

    void hookFunctions()
    {
        // Hook functions
        return_fapGm_Execute = libtp::patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, mod::handle_fapGm_Execute );
        console << "Functions have been hooked\n";
    }

    void handleInput( uint32_t input )
    {
        // Cycle through available seeds
        if ( gameState == GAME_TITLE )
        {
            // TODO: Printing the currently selected seed
        }
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
        if ( 0 == strcmp( "F_SP102", gameInfo->currentStage ) || 0 == strcmp( "S_MV000", gameInfo->currentStage ) )
        {
            if ( gameState != GAME_TITLE )
            {
                // Title screen or demo
                gameState = GAME_TITLE;
                console << "State switched to TITLE\n";
            }
        }
        else if ( gameState != GAME_ACTIVE && gameState != GAME_BOOT )
        {
            // We can't possibly be ingame if state was GAME_BOOT
            gameState = GAME_ACTIVE;
            console << "State switched to GAMEPLAY\n";
        }

        // handle button inputs only if buttons are being held that weren't held last time
        if ( padInfo->buttonInput != lastButtonInput )
        {
            // Store before processing since we (potentially) un-set the padInfo values later
            lastButtonInput = padInfo->buttonInput;

            // Special combo to (de)activate the console should be handled first
            if ( ( padInfo->buttonInput & ( PadInputs::Button_R | PadInputs::Button_Z ) ) ==
                 ( PadInputs::Button_R | PadInputs::Button_Z ) )
            {
                consoleState = !consoleState;
                display::setConsole( consoleState, 0 );
            }
            // Handle Inputs if console is already active
            else if ( consoleState )
            {
                handleInput( padInfo->buttonInput );

                // Disable input so game doesn't notice
                padInfo->buttonInput = 0;
                padInfo->buttonInputTrg = 0;
            }
        }

        return return_fapGm_Execute();
    }
}     // namespace mod