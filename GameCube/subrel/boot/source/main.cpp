#include "main.h"
#include "item_wheel_menu.h"
#include "patch.h"

#include "game_patch/game_patch.h"
#include "customMessages.h"
#include "tp/d_stage.h"
#include "tp/d_com_inf_game.h"
#include "tp/f_ap_game.h"
#include "tp/f_op_actor_mng.h"
#include "tp/d_menu_ring.h"
#include "tp/d_item.h"
#include "tp/d_msg_class.h"
#include "tp/resource.h"
#include "tp/d_msg_flow.h"
#include "tp/d_menu_window.h"
#include "Z2AudioLib/Z2AudioMgr.h"
#include "tp/d_s_logo.h"
#include "user_patch/01_randombgm.h"
#include "user_patch/02_enemybgm.h"
#include "Z2AudioLib/Z2SeqMgr.h"

#include <cstdint>

namespace mod
{
    void main()
    {
        // Run game patches
        game_patch::_00_poe();
        game_patch::_02_modifyItemData();
        game_patch::_03_increaseClimbSpeed();
        game_patch::_06_writeASMPatches();

        // Load custom messages
        customMessages::createMsgTable();
        customMessages::createCharloDonationMessage();

        // Load item wheel menu strings
        customMessages::createItemWheelMenuData();

        // Display some info
        console << "Welcome to TPR!\n"
                << "(C) AECX, Lunar Soap, Zephiles\n\n"
                << "Note:\n"
                << "Please avoid [re]starting rando unnecessarily\n"
                << "on ORIGINAL HARDWARE as it wears down your\n"
                << "Memory Card!\n"
                << "Press R + Z to close the console.\n\n";

        // Generate our seedList
        seedList = new rando::SeedList();

        // Just hook functions for now
        hookFunctions();
    }

    void exit() {}

    void hookFunctions()
    {
        using namespace libtp;
        using namespace libtp::tp::d_stage;
        using namespace libtp::tp::d_com_inf_game;

        // Hook functions
        return_fapGm_Execute = patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, mod::handle_fapGm_Execute );

        // DMC
        return_do_Link = patch::hookFunction( libtp::tp::dynamic_link::do_link, mod::handle_do_link );
        return_do_unlink = patch::hookFunction( libtp::tp::dynamic_link::do_unlink, mod::handle_do_unlink );

        // DZX
        return_actorInit = patch::hookFunction( actorInit, mod::handle_actorInit );
        return_actorInit_always = patch::hookFunction( actorInit_always, mod::handle_actorInit_always );
        return_actorCommonLayerInit = patch::hookFunction( actorCommonLayerInit, mod::handle_actorCommonLayerInit );
        return_tgscInfoInit = patch::hookFunction( tgscInfoInit, mod::handle_tgscInfoInit );
        return_roomLoader = patch::hookFunction( libtp::tp::d_stage::roomLoader, mod::handle_roomLoader );
        return_stageLoader = patch::hookFunction( libtp::tp::d_stage::stageLoader, mod::handle_stageLoader );

        // Custom States
        return_getLayerNo_common_common = patch::hookFunction( getLayerNo_common_common, game_patch::_01_getLayerNo );

        // Item Creation Functions
        return_createItemForBoss =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForBoss, mod::handle_createItemForBoss );
        return_createItemForMidBoss =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForMidBoss, mod::handle_createItemForMidBoss );
        return_createItemForPresentDemo =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForPresentDemo, mod::handle_createItemForPresentDemo );
        return_createItemForTrBoxDemo =
            patch::hookFunction( libtp::tp::f_op_actor_mng::createItemForTrBoxDemo, mod::handle_createItemForTrBoxDemo );

        // Item Wheel functions
        return_setLineUpItem = patch::hookFunction( tp::d_save::setLineUpItem, mod::handle_setLineUpItem );

        item_wheel_menu::return_dMenuRing__create =
            patch::hookFunction( libtp::tp::d_menu_ring::dMenuRing__create, item_wheel_menu::handle_dMenuRing__create );

        item_wheel_menu::return_dMenuRing__delete =
            patch::hookFunction( libtp::tp::d_menu_ring::dMenuRing__delete, item_wheel_menu::handle_dMenuRing__delete );

        item_wheel_menu::return_dMenuRing__draw =
            patch::hookFunction( libtp::tp::d_menu_ring::dMenuRing__draw, item_wheel_menu::handle_dMenuRing__draw );

        // ItemGet functions
        return_execItemGet = patch::hookFunction( libtp::tp::d_item::execItemGet, mod::handle_execItemGet );
        return_checkItemGet = patch::hookFunction( libtp::tp::d_item::checkItemGet, mod::handle_checkItemGet );

        // Message Functions
        return_setMessageCode_inSequence =
            patch::hookFunction( libtp::tp::control::setMessageCode_inSequence, mod::handle_setMessageCode_inSequence );
        return_getFontCCColorTable =
            patch::hookFunction( tp::d_msg_class::getFontCCColorTable, mod::handle_getFontCCColorTable );
        return_getFontGCColorTable =
            patch::hookFunction( tp::d_msg_class::getFontGCColorTable, mod::handle_getFontGCColorTable );
        return_parseCharacter_1Byte =
            patch::hookFunction( tp::resource::parseCharacter_1Byte, mod::handle_parseCharacter_1Byte );

        // Query/EventFunctions
        return_query022 = patch::hookFunction( libtp::tp::d_msg_flow::query022, mod::handle_query022 );
        return_query023 = patch::hookFunction( libtp::tp::d_msg_flow::query023, mod::handle_query023 );
        return_query025 = patch::hookFunction( libtp::tp::d_msg_flow::query025, mod::handle_query025 );
        return_query004 = patch::hookFunction( libtp::tp::d_msg_flow::query004, mod::handle_query004 );
        return_query037 = patch::hookFunction( libtp::tp::d_msg_flow::query037, mod::handle_query037 );
        return_query042 = patch::hookFunction( libtp::tp::d_msg_flow::query042, mod::handle_query042 );
        return_event000 = patch::hookFunction( libtp::tp::d_msg_flow::event000, mod::handle_event000 );
        return_event017 = patch::hookFunction( libtp::tp::d_msg_flow::event017, mod::handle_event017 );
        return_event003 = patch::hookFunction( libtp::tp::d_msg_flow::event003, mod::handle_event003 );
        return_event041 = patch::hookFunction( libtp::tp::d_msg_flow::event041, mod::handle_event041 );

        // Save flag functions
        return_isDungeonItem = patch::hookFunction( tp::d_save::isDungeonItem, mod::handle_isDungeonItem );
        return_chkEvtBit = patch::hookFunction( libtp::tp::d_msg_flow::chkEvtBit, mod::handle_chkEvtBit );
        return_isEventBit = patch::hookFunction( libtp::tp::d_save::isEventBit, mod::handle_isEventBit );
        return_onEventBit = patch::hookFunction( libtp::tp::d_save::onEventBit, mod::handle_onEventBit );
        return_isSwitch_dSv_memBit =
            patch::hookFunction( libtp::tp::d_save::isSwitch_dSv_memBit, mod::handle_isSwitch_dSv_memBit );
        return_onSwitch_dSv_memBit =
            patch::hookFunction( libtp::tp::d_save::onSwitch_dSv_memBit, mod::handle_onSwitch_dSv_memBit );
        return_checkTreasureRupeeReturn =
            patch::hookFunction( tp::d_a_alink::checkTreasureRupeeReturn, mod::handle_checkTreasureRupeeReturn );

        // Pause Menu Functions
        return_collect_save_open_init =
            patch::hookFunction( tp::d_menu_window::collect_save_open_init, mod::handle_collect_save_open_init );

        // Link functions
        return_checkBootsMoveAnime =
            patch::hookFunction( libtp::tp::d_a_alink::checkBootsMoveAnime, mod::handle_checkBootsMoveAnime );
        return_setGetItemFace = patch::hookFunction( libtp::tp::d_a_alink::setGetItemFace, mod::handle_setGetItemFace );

        // Audio functions
        return_loadSeWave = patch::hookFunction( libtp::z2audiolib::z2scenemgr::loadSeWave, mod::handle_loadSeWave );

        // Title Screen functions
        return_dScnLogo_c_dt = patch::hookFunction( libtp::tp::d_s_logo::dScnLogo_c_dt, mod::handle_dScnLogo_c_dt );

        // Random BGM
        user_patch::bgm::bgmrando::return_sceneChange =
            patch::hookFunction( libtp::z2audiolib::z2scenemgr::sceneChange, user_patch::handle_sceneChange );

        // Enemy BGM
        user_patch::bgm::enemybgm::return_startBattleBgm =
            patch::hookFunction( libtp::z2audiolib::z2seqmgr::startBattleBgm, user_patch::handle_startBattleBgm );
    }
}     // namespace mod