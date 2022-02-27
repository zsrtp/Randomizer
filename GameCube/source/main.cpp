#include "main.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "patch.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "rando/seedlist.h"
#include "tools.h"
#include "tp/JKRDvdRipper.h"
#include "tp/control.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_kankyo.h"
#include "tp/d_menu_window.h"
#include "tp/d_meter2_info.h"
#include "tp/d_msg_class.h"
#include "tp/d_msg_flow.h"
#include "tp/d_msg_object.h"
#include "tp/d_save.h"
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
    void ( *return_setLineUpItem )( libtp::tp::d_save::dSv_player_item_c* ) = nullptr;
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

    int32_t ( *return_createItemForPresentDemo )( const float pos[3],
                                                  int32_t item,
                                                  uint8_t unk3,
                                                  int32_t unk4,
                                                  int32_t unk5,
                                                  const float unk6[3],
                                                  const float unk7[3] ) = nullptr;

    int32_t ( *return_createItemForTrBoxDemo )( const float pos[3],
                                                int32_t item,
                                                int32_t itemPickupFlag,
                                                int32_t roomNo,
                                                const int16_t rot[3],
                                                const float scale[3] ) = nullptr;
    int32_t ( *return_createItemForMidBoss )( const float pos[3],
                                              int32_t item,
                                              int32_t roomNo,
                                              const int16_t rot[3],
                                              const float scale[3],
                                              int32_t unk6,
                                              int32_t itemPickupFlag ) = nullptr;

    int32_t ( *return_execItemGet )( uint8_t item ) = nullptr;

    int32_t ( *return_checkItemGet )( uint8_t item, int32_t defaultValue ) = nullptr;

    void* ( *return_loadToMainRAM2 )( int32_t fileIndex,
                                      uint8_t* unk2,
                                      uint32_t jkrExpandSwitch,
                                      uint32_t unk4,
                                      void* jkrHeap,
                                      uint32_t eAllocDirection,
                                      uint32_t unk7,
                                      int32_t* unk8,
                                      uint32_t* unk9 ) = nullptr;

    bool ( *return_setMessageCode_inSequence )( libtp::tp::control::TControl* control,
                                                const void* TProcessor,
                                                uint16_t unk3,
                                                uint16_t msgId ) = nullptr;

    uint32_t ( *return_getFontCCColorTable )( uint8_t colorId, uint8_t unk ) = nullptr;
    uint32_t ( *return_getFontGCColorTable )( uint8_t colorId, uint8_t unk ) = nullptr;

    bool ( *return_query022 )( void* unk1, void* unk2, int32_t unk3 ) = nullptr;
    bool ( *return_query023 )( void* unk1, void* unk2, int32_t unk3 ) = nullptr;
    bool ( *return_query025 )( void* unk1, void* unk2, int32_t unk3 ) = nullptr;

    bool ( *return_checkTreasureRupeeReturn )( void* unk1, int32_t item ) = nullptr;

    void ( *return_collect_save_open_init )( uint8_t param_1 ) = nullptr;

    bool ( *return_isDungeonItem )( libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int memBit ) = nullptr;

    bool ( *return_chkEvtBit )( uint32_t flag ) = nullptr;

    bool ( *return_isEventBit )( libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag ) = nullptr;
    uint32_t ( *return_event000 )( void* messageFlow, void* nodeEvent, void* actrPtr ) = nullptr;

    void main()
    {
        // Run game patches
        game_patch::_00_poe();
        game_patch::_02_modifyItemData();
        game_patch::_03_increaseClimbSpeed();
        game_patch::_06_writeASMPatches();

        // Display some info
        console << "Welcome to TPR!\n"
                << "(C) AECX, Lunar Soap, Zephiles\n\n"
                << "Note:\n"
                << "Please avoid [re]starting rando unnecessarily\n"
                << "on ORIGINAL HARDWARE as it wears down your\n"
                << "Memory Card!\n"
                << "Press R + Z to close the console.\n"
                << "Press X/Y to select a seed.\n\n";

        // Generate our seedList
        seedList = new rando::SeedList();

        // Just hook functions for now
        hookFunctions();
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
        return_do_Link = patch::hookFunction( libtp::tp::dynamic_link::do_link,
                                              []( libtp::tp::dynamic_link::DynamicModuleControl* dmc )
                                              {
                                                  // Call the original function immediately, as the REL file needs to be linked
                                                  // before applying patches
                                                  const bool result = return_do_Link( dmc );

                                                  events::onRELLink( randomizer, dmc );

                                                  return result;
                                              } );

        // DZX
        return_actorInit =
            patch::hookFunction( actorInit,
                                 []( void* mStatus_roomControl, ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 )
                                 {
                                     events::onDZX( mod::randomizer, chunkTypeInfo );
                                     return return_actorInit( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
                                 } );

        return_actorInit_always =
            patch::hookFunction( actorInit_always,
                                 []( void* mStatus_roomControl, ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 )
                                 {
                                     events::onDZX( mod::randomizer, chunkTypeInfo );
                                     return return_actorInit_always( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
                                 } );

        return_actorCommonLayerInit =
            patch::hookFunction( actorCommonLayerInit,
                                 []( void* mStatus_roomControl, ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 )
                                 {
                                     events::onDZX( mod::randomizer, chunkTypeInfo );
                                     return return_actorCommonLayerInit( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
                                 } );

        // Custom States
        return_getLayerNo_common_common =
            patch::hookFunction( getLayerNo_common_common,
                                 []( const char* stageName, int32_t roomId, int32_t layerOverride )
                                 { return game_patch::_01_getLayerNo( stageName, roomId, layerOverride ); } );

        // Custom Item Messages
        return_setMessageCode_inSequence = patch::hookFunction(
            libtp::tp::control::setMessageCode_inSequence,
            []( libtp::tp::control::TControl* control, const void* TProcessor, uint16_t unk3, uint16_t msgId )
            {
                // Call the original function immediately, as a lot of stuff needs to be set before our code runs
                const bool ret = return_setMessageCode_inSequence( control, TProcessor, unk3, msgId );

                // Make sure the function ran successfully
                if ( !ret )
                {
                    return ret;
                }
                game_patch::_05_setCustomItemMessage( control, TProcessor, unk3, msgId );
                return ret;
            } );

        // Set custom font color
        return_getFontCCColorTable = patch::hookFunction( tp::d_msg_class::getFontCCColorTable,
                                                          []( uint8_t colorId, uint8_t unk )
                                                          {
                                                              if ( colorId >= 0x9 )
                                                              {
                                                                  return game_patch::_05_getCustomMsgColor( colorId );
                                                              }
                                                              else
                                                              {
                                                                  return return_getFontCCColorTable( colorId, unk );
                                                              }
                                                          } );
        // Set custom font color
        return_getFontGCColorTable = patch::hookFunction( tp::d_msg_class::getFontGCColorTable,
                                                          []( uint8_t colorId, uint8_t unk )
                                                          {
                                                              if ( colorId >= 0x9 )
                                                              {
                                                                  return game_patch::_05_getCustomMsgColor( colorId );
                                                              }
                                                              else
                                                              {
                                                                  return return_getFontCCColorTable( colorId, unk );
                                                              }
                                                          } );

        return_collect_save_open_init = patch::hookFunction( tp::d_menu_window::collect_save_open_init,
                                                             []( uint8_t param_1 )
                                                             {
                                                                 game_patch::_07_checkPlayerStageReturn();
                                                                 return return_collect_save_open_init( param_1 );
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
                                     int32_t parameters )
                                 {
                                     // Spawn the appropriate item with model
                                     uint8_t itemID = randomizer->getBossItem();
                                     itemID = game_patch::_04_verifyProgressiveItem( mod::randomizer, itemID );
                                     uint32_t params = 0xFF0000 | ( parameters & 0xFF ) << 0x8 | ( itemID & 0xFF );
                                     return tp::f_op_actor_mng::fopAcM_create( 539, params, pos, roomNo, rot, scale, -1 );
                                 } );

        return_createItemForMidBoss =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForMidBoss,
                                 []( const float pos[3],
                                     int32_t item,
                                     int32_t roomNo,
                                     const int16_t rot[3],
                                     const float scale[3],
                                     int32_t unk6,
                                     int32_t itemPickupFlag )
                                 {
                                     if ( item == 0x40 )
                                     {
                                         // Spawn the appropriate item
                                         uint8_t itemID = randomizer->getBossItem();
                                         itemID = game_patch::_04_verifyProgressiveItem( mod::randomizer, itemID );
                                         uint32_t params = itemID | 0xFFFF00;
                                         return tp::f_op_actor_mng::fopAcM_create( 539, params, pos, roomNo, rot, scale, -1 );
                                     }
                                     return return_createItemForMidBoss( pos, item, roomNo, rot, scale, unk6, itemPickupFlag );
                                 } );

        return_createItemForPresentDemo =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForPresentDemo,
                                 []( const float pos[3],
                                     int32_t item,
                                     uint8_t unk3,
                                     int32_t unk4,
                                     int32_t unk5,
                                     const float rot[3],
                                     const float scale[3] )
                                 {
                                     item = game_patch::_04_verifyProgressiveItem( mod::randomizer, item );
                                     return return_createItemForPresentDemo( pos, item, unk3, 0x32, 0x32, rot, scale );
                                 } );

        return_checkTreasureRupeeReturn =
            patch::hookFunction( tp::d_a_alink::checkTreasureRupeeReturn, []( void* unk1, int32_t item ) { return false; } );

        return_execItemGet = patch::hookFunction( libtp::tp::d_item::execItemGet,
                                                  []( uint8_t item )
                                                  {
                                                      item = game_patch::_04_verifyProgressiveItem( mod::randomizer, item );
                                                      return return_execItemGet( item );
                                                  } );

        return_checkItemGet = patch::hookFunction(
            libtp::tp::d_item::checkItemGet,
            []( uint8_t item, int32_t defaultValue )
            {
                switch ( item )
                {
                    using namespace libtp::tp;
                    using namespace libtp::data;
                    case items::Hylian_Shield:
                    {
                        // Check if we are at Kakariko Malo mart and verify that we have not bought the shield.
                        if ( tp::d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Kakariko_Village_Interiors] ) &&
                             tp::d_kankyo::env_light.currentRoom == 3 && tp::d_a_alink::dComIfGs_isEventBit( 0x6002 ) )
                        {
                            // Return false so we can buy the shield.
                            return 0;
                        }
                        break;
                    }
                    case items::Hawkeye:
                    {
                        // Check if we are at Kakariko Village and that the hawkeye is currently not for sale.
                        if ( ( tp::d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Kakariko_Village] ) &&
                               !libtp::tp::d_save::isSwitch_dSv_memBit(
                                   &d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags,
                                   0x3E ) ) )
                        {
                            // Return false so we can buy the hawkeye.
                            return 0;
                        }
                        break;
                    }

                    case items::Ordon_Pumpkin:
                    case items::Ordon_Goat_Cheese:
                    {
                        // Check to see if currently in Snowpeak Ruins
                        if ( libtp::tp::d_a_alink::checkStageName(
                                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Snowpeak_Ruins] ) )
                        {
                            // Return false so that yeta will give the map item no matter what.
                            return 0;
                        }
                        break;
                    }
                    default:
                    {
                        // Call original function if the conditions are not met.
                        return return_checkItemGet( item, defaultValue );
                    }
                }
                return return_checkItemGet( item, defaultValue );
            } );

        return_query022 = patch::hookFunction( libtp::tp::d_msg_flow::query022,
                                               []( void* unk1, void* unk2, int32_t unk3 )
                                               { return events::proc_query022( unk1, unk2, unk3 ); } );

        return_query023 = patch::hookFunction( libtp::tp::d_msg_flow::query023,
                                               []( void* unk1, void* unk2, int32_t unk3 )
                                               { return events::proc_query023( unk1, unk2, unk3 ); } );

        return_query025 =
            patch::hookFunction( libtp::tp::d_msg_flow::query025,
                                 []( void* unk1, void* unk2, int32_t unk3 )
                                 {
                                     if ( libtp::tp::d_a_alink::checkStageName(
                                              libtp::data::stage::allStages[libtp::data::stage::stageIDs::Cave_of_Ordeals] ) )
                                     {
                                         // Return False to allow us to collect the item from the floor 50 reward.
                                         return false;
                                     }
                                     return return_query025( unk1, unk2, unk3 );
                                 } );

        return_chkEvtBit = patch::hookFunction(
            libtp::tp::d_msg_flow::chkEvtBit,
            []( uint32_t flag )
            {
                // need to make this a switch
                if ( ( flag == 0x153 ) && libtp::tp::d_a_alink::checkStageName(
                                              libtp::data::stage::allStages[libtp::data::stage::stageIDs::Hidden_Skill] ) )
                {
                    return true;
                }
                if ( ( flag == 0x169 ) && libtp::tp::d_a_alink::checkStageName(
                                              libtp::data::stage::allStages[libtp::data::stage::stageIDs::Lake_Hylia] ) )
                {
                    return false;
                }
                return return_chkEvtBit( flag );
            } );

        return_setLineUpItem = patch::hookFunction(
            tp::d_save::setLineUpItem,
            []( libtp::tp::d_save::dSv_player_item_c* unk1 )
            {
                using namespace libtp::tp::d_com_inf_game;
                static uint8_t i_item_lst[24] = { 0x0A, 0x08, 0x06, 0x02, 0x09, 0x04, 0x03, 0x00, 0x01, 0x17, 0x14, 0x05,
                                                  0x0F, 0x10, 0x11, 0x0B, 0x0C, 0x0D, 0x0E, 0x13, 0x12, 0x16, 0x15, 0x7 };
                int i1 = 0;
                int i2 = 0;

                for ( ; i1 < 24; i1++ )
                {
                    dComIfG_gameInfo.save.save_file.player.player_item.item_slots[i1] = 0xFF;
                }

                for ( i1 = 0; i1 < 24; i1++ )
                {
                    if ( dComIfG_gameInfo.save.save_file.player.player_item.item[i_item_lst[i1]] != 0xFF )
                    {
                        dComIfG_gameInfo.save.save_file.player.player_item.item_slots[i2] = i_item_lst[i1];
                        i2++;
                    }
                }
            } );
        return_isEventBit = patch::hookFunction( libtp::tp::d_save::isEventBit,
                                                 []( libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag )
                                                 {
                                                     using namespace libtp::tp::d_a_alink;
                                                     using namespace libtp::data::stage;
                                                     switch ( flag )
                                                     {
                                                         case 0x2904:
                                                         {
                                                             if ( checkStageName( allStages[stageIDs::Hidden_Skill] ) )
                                                             {
                                                                 return true;
                                                             }
                                                             break;
                                                         }

                                                         case 0x2320:
                                                         case 0x3E02:
                                                         {
                                                             if ( checkStageName( allStages[stageIDs::Hidden_Village] ) )
                                                             {
                                                                 if ( !dComIfGs_isEventBit( 0x2280 ) )
                                                                 {
                                                                     return false;
                                                                 }
                                                             }
                                                             break;
                                                         }

                                                         case 0x701:
                                                         {
                                                             if ( checkStageName( allStages[stageIDs::Goron_Mines] ) )
                                                             {
                                                                 return false;
                                                             }
                                                             break;
                                                         }
                                                         default:
                                                         {
                                                             return return_isEventBit( eventPtr, flag );
                                                             break;
                                                         }
                                                     }
                                                     return return_isEventBit( eventPtr, flag );
                                                 } );
        return_event000 =
            patch::hookFunction( libtp::tp::d_msg_flow::event000,
                                 []( void* messageFlow, void* nodeEvent, void* actrPtr )
                                 {
                                     // Prevent the hidden skill CS from setting the proper flags
                                     if ( libtp::tp::d_a_alink::checkStageName(
                                              libtp::data::stage::allStages[libtp::data::stage::stageIDs::Hidden_Skill] ) )
                                     {
                                         *reinterpret_cast<uint16_t*>( reinterpret_cast<uint32_t>( nodeEvent ) + 4 ) = 0x0000;
                                     }
                                     return return_event000( messageFlow, nodeEvent, actrPtr );
                                 } );

        return_createItemForTrBoxDemo =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForTrBoxDemo,
                                 []( const float pos[3],
                                     int32_t item,
                                     int32_t itemPickupFlag,
                                     int32_t roomNo,
                                     const int16_t rot[3],
                                     const float scale[3] )
                                 {
                                     events::handleDungeonHeartContainer();     // Set the flag for the dungeon heart container
                                                                                // if this item replaces it.
                                     item = game_patch::_04_verifyProgressiveItem( mod::randomizer, item );
                                     return return_createItemForTrBoxDemo( pos, item, itemPickupFlag, roomNo, rot, scale );
                                 } );

        return_loadToMainRAM2 = patch::hookFunction(
            tp::JKRDvdRipper::loadToMainRAM2,
            []( int32_t fileIndex,
                uint8_t* unk2,
                uint32_t jkrExpandSwitch,
                uint32_t unk4,
                void* jkrHeap,
                uint32_t eAllocDirection,
                uint32_t unk7,
                int32_t* unk8,
                uint32_t* unk9 )
            {
                // Call the original function immediately, as we need the pointer it returns
                void* filePtr =
                    return_loadToMainRAM2( fileIndex, unk2, jkrExpandSwitch, unk4, jkrHeap, eAllocDirection, unk7, unk8, unk9 );
                events::onARC( mod::randomizer, filePtr, fileIndex );
                return filePtr;
            } );

        return_isDungeonItem = patch::hookFunction( tp::d_save::isDungeonItem,
                                                    []( tp::d_save::dSv_memBit_c* membitPtr, const int memBit )
                                                    { return events::proc_isDungeonItem( membitPtr, memBit ); } );
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
                if ( 0 != strcmp( "S_MV000", gameInfo->play.mNextStage.stageValues.mStage ) )
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
                setScreen( !consoleState );
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