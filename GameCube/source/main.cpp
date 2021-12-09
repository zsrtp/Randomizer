#include "main.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "data/items.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "patch.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "rando/seedlist.h"
#include "tools.h"
#include "tp/control.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_meter2_info.h"
#include "tp/d_msg_object.h"
#include "tp/d_stage.h"
#include "tp/dzx.h"
#include "tp/f_ap_game.h"
#include "tp/f_op_actor_mng.h"
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
    int32_t lastLoadingState = 0;
    bool consoleState = true;
    uint8_t gameState = GAME_BOOT;

    // Function hook return trampolines
    void ( *return_fapGm_Execute )( void ) = nullptr;
    bool ( *return_do_Link )( libtp::tp::dynamic_link::DynamicModuleControl* dmc ) = nullptr;

    // DZX trampolines
    bool ( *return_actorInit )( void* mStatus_roomControl,
                                libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                int32_t unk3,
                                void* unk4 ) = nullptr;

    bool ( *return_actorInit_always )( void* mStatus_roomControl,
                                       libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                       int32_t unk3,
                                       void* unk4 ) = nullptr;

    bool ( *return_actorCommonLayerInit )( void* mStatus_roomControl,
                                           libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                           int32_t unk3,
                                           void* unk4 ) = nullptr;

    // GetLayerNo trampoline
    int32_t ( *return_getLayerNo_common_common )( const char* stageName, int32_t roomId, int32_t layerOverride ) = nullptr;

    // Used in replacing Heart Containers
    int32_t ( *return_createItemForBoss )( const float pos[3],
                                           int32_t item,
                                           int32_t roomNo,
                                           const int16_t rot[3],
                                           const float scale[3],
                                           float unk6,
                                           float unk7,
                                           int32_t parameters ) = nullptr;

    bool ( *return_render )( void* TControl ) = nullptr;

    void main()
    {
        // Run game patches
        game_patch::_00_poe();
        game_patch::_02_modifyItemData();
        game_patch::_03_increaseClimbSpeed();

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
        using namespace libtp;
        using namespace libtp::tp::d_stage;
        using namespace libtp::tp::dzx;
        using namespace libtp::tp::d_com_inf_game;
        // Hook functions
        return_fapGm_Execute = patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, mod::handle_fapGm_Execute );

        // DMC
        return_do_Link =
            patch::hookFunction( libtp::tp::dynamic_link::do_link, []( libtp::tp::dynamic_link::DynamicModuleControl* dmc ) {
                // Call the original function immediately, as the REL file needs to be linked
                // before applying patches
                const bool result = return_do_Link( dmc );

                events::onRELLink( randomizer, dmc );

                return result;
            } );

        // DZX
        return_actorInit =
            patch::hookFunction( actorInit,
                                 []( void* mStatus_roomControl, ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 ) {
                                     events::onDZX( mod::randomizer, chunkTypeInfo );
                                     return return_actorInit( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
                                 } );

        return_actorInit_always =
            patch::hookFunction( actorInit_always,
                                 []( void* mStatus_roomControl, ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 ) {
                                     events::onDZX( mod::randomizer, chunkTypeInfo );
                                     return return_actorInit_always( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
                                 } );

        return_actorCommonLayerInit =
            patch::hookFunction( actorCommonLayerInit,
                                 []( void* mStatus_roomControl, ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 ) {
                                     events::onDZX( mod::randomizer, chunkTypeInfo );
                                     return return_actorCommonLayerInit( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
                                 } );

        // Custom States
        return_getLayerNo_common_common =
            patch::hookFunction( getLayerNo_common_common, []( const char* stageName, int32_t roomId, int32_t layerOverride ) {
                return game_patch::_01_getLayerNo( stageName, roomId, layerOverride );
            } );

        // Custom GetItem Text
        return_render = patch::hookFunction( tp::control::render, []( void* TControl ) {
            // Get the address of the current text to draw
            const char** currentTextPtr = reinterpret_cast<const char**>( reinterpret_cast<uint32_t>( TControl ) + 0x20 );

            const char* currentText = *currentTextPtr;

            // Make sure a pointer is set
            if ( !currentText )
            {
                return return_render( TControl );
            }
            return return_render( TControl );
        } );

        // Replace the Item that spawns when a boss is defeated
        return_createItemForBoss =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForBoss,
                                 []( const float pos[3],
                                     int32_t item,
                                     int32_t roomNo,
                                     const int16_t rot[3],
                                     const float scale[3],
                                     float unk6,
                                     float unk7,
                                     int32_t parameters ) {
                                     // Spawn the appropriate item with model
                                     uint32_t params = randomizer->getBossItem() | 0xFFFF00;
                                     return tp::f_op_actor_mng::fopAcM_create( 539, params, pos, roomNo, rot, scale, -1 );
                                 } );
    }

    int32_t getMsgIndex( libtp::tp::d_msg_object::StringDataTable* stringDataTable, uint32_t itemId )
    {
        uint32_t totalEntries = stringDataTable->totalEntries;
        libtp::tp::d_msg_object::StringDataTableEntry* entry = &stringDataTable->entry[0];

        // Increment itemId to be at the start of the table entries for items
        itemId += 0x65;

        for ( uint32_t index = 0; index < totalEntries; index++ )
        {
            if ( entry->stringId == itemId )
            {
                return static_cast<int32_t>( index );
            }
            entry++;
        }

        // Didn't find a proper index
        return -1;
    }

    const char* getItemMsgAddress( uint32_t itemId )
    {
        // Get the pointer to the string data table
        libtp::tp::d_msg_object::StringDataTable* stringDataTable = libtp::tp::d_meter2_info::g_meter2_info.stringDataTable;

        // Make sure the pointer is set
        if ( !stringDataTable )
        {
            return nullptr;
        }

        // Get the index for the current item
        int32_t itemIndex = getMsgIndex( stringDataTable, itemId );

        // Make sure the index is valid
        if ( itemIndex < 0 )
        {
            return nullptr;
        }

        // Get the string address
        libtp::tp::d_msg_object::StringDataTableEntry* entry = &stringDataTable->entry[itemIndex];

        return reinterpret_cast<const char*>( reinterpret_cast<uint32_t>( &stringDataTable->unk_20 ) + entry->offsetToString +
                                              ( stringDataTable->stringsStartOffset + 0x8 ) );
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
        dComIfG_inf_c* gameInfo = &dComIfG_gameInfo;

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
                if ( 0 != strcmp( "S_MV000", gameInfo->play.mNextStage.mStage ) )
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
            if ( seedList->m_numSeeds > 0 && !randomizer )
            {
                randomizer = new rando::Randomizer( &seedList->m_seedInfo[seedList->m_selectedSeed] );
            }
        }
        else if ( randomizer )
        {
            delete randomizer;
            randomizer = nullptr;
        }

        // Custom events
        if ( !lastLoadingState && tp::f_op_scene_req::isLoading )
        {
            // OnLoad
            events::onLoad( randomizer );
        }

        if ( lastLoadingState && !tp::f_op_scene_req::isLoading )
        {
            // OffLoad
            events::offLoad( randomizer );
        }

        lastLoadingState = tp::f_op_scene_req::isLoading;
        // End of custom events

        return return_fapGm_Execute();
    }
}     // namespace mod