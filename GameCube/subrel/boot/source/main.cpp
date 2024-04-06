#include "main.h"
#include "item_wheel_menu.h"
#include "patch.h"

#include "game_patch/game_patch.h"
#include "customMessages.h"
#include "cxx.h"
#include "tp/d_stage.h"
#include "tp/d_com_inf_game.h"
#include "tp/f_ap_game.h"
#include "tp/f_op_actor_mng.h"
#include "tp/d_menu_ring.h"
#include "tp/d_item.h"
#include "tp/d_msg_class.h"
#include "tp/resource.h"
#include "tp/d_msg_flow.h"
#include "tp/d_a_npc.h"
#include "tp/d_menu_window.h"
#include "Z2AudioLib/Z2AudioMgr.h"
#include "tp/d_s_logo.h"
#include "user_patch/02_enemybgm.h"
#include "Z2AudioLib/Z2SeqMgr.h"
#include "Z2AudioLib/Z2SoundMgr.h"
#include "tp/dynamic_link.h"
#include "gc_wii/OSTime.h"
#include "tp/d_a_itembase.h"
#include "tp/JKRMemArchive.h"
#include "tp/m_Do_dvd_thread.h"
#include "gc_wii/dvdfs.h"
#include "gc_wii/OSCache.h"
#include "codehandler.h"
#include "memory.h"
#include "gc_wii/OSInterrupt.h"
#include "gc_wii/vi.h"
#include "asm.h"

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cinttypes>

namespace mod
{
    void main()
    {
        // Set up the console
        // Align to uint8_t, as that's the largest variable type in the Console class
        mod::console = new (sizeof(uint8_t)) libtp::display::Console(CONSOLE_PROTECTED_LINES);

#ifdef TP_EU
        // Set the current language being used
        currentLanguage = libtp::tp::d_s_logo::getPalLanguage2(nullptr);
#endif

        // Handle the main function hooks
        hookFunctions();

        // Set up the codehandler
        // writeCodehandlerToMemory();

        // Initialize the Golden Wolf item replacement actor id to -1
        rando::goldenWolfItemReplacement.itemActorId = -1;

        // Initialize randState
        initRandState();

        // Run game patches
        game_patch::_00_poe();
        game_patch::_02_modifyItemData();
        game_patch::_03_increaseClimbSpeed();
        game_patch::_06_writeASMPatches();

        // Load custom messages
        customMessages::createMsgTable();
        customMessages::setDungeonItemAreaColorIndex();

        // Load item wheel menu strings
        customMessages::createItemWheelMenuData();

        // Display some info
#ifndef DVD
        getConsole() << "Note:\n"
                     << "Please avoid [re]starting rando unnecessarily\n"
                     << "on ORIGINAL HARDWARE as it wears down your\n"
                     << "Memory Card!\n";
#endif
        getConsole() << "Press R + Z to close the console.\n\n";

        // Generate our seedList
        // Align to void*, as pointers use the largest variable type in the SeedList class
        seedList = new (sizeof(void*)) rando::SeedList();

        // Initialize the table of archive file entries that are used for texture recoloring.
        initArcLookupTable();
    }

    void exit() {}

    void hookFunctions()
    {
        using namespace libtp;
        using namespace libtp::tp::d_stage;
        using namespace libtp::tp::d_com_inf_game;

        // Hook functions
        patch::writeBranch(snprintf, assembly::asm_handle_snprintf);
        patch::writeBranch(vsnprintf, assembly::asm_handle_vsnprintf);
        return_fapGm_Execute = patch::hookFunction(libtp::tp::f_ap_game::fapGm_Execute, mod::handle_fapGm_Execute);

        // DMC
        return_do_unlink = patch::hookFunction(libtp::tp::dynamic_link::do_unlink, mod::handle_do_unlink);

        // DZX
        return_actorInit = patch::hookFunction(actorInit, mod::handle_actorInit);
        return_actorInit_always = patch::hookFunction(actorInit_always, mod::handle_actorInit_always);
        return_actorCommonLayerInit = patch::hookFunction(actorCommonLayerInit, mod::handle_actorCommonLayerInit);
        return_tgscInfoInit = patch::hookFunction(tgscInfoInit, mod::handle_tgscInfoInit);
        return_roomLoader = patch::hookFunction(libtp::tp::d_stage::roomLoader, mod::handle_roomLoader);
        // return_stageLoader = patch::hookFunction( libtp::tp::d_stage::stageLoader, mod::handle_stageLoader );
        return_dStage_playerInit = patch::hookFunction(libtp::tp::d_stage::dStage_playerInit, mod::handle_dStage_playerInit);

        return_dComIfGp_setNextStage =
            patch::hookFunction(libtp::tp::d_com_inf_game::dComIfGp_setNextStage, mod::handle_dComIfGp_setNextStage);

        // Custom States
        return_getLayerNo_common_common = patch::hookFunction(getLayerNo_common_common, game_patch::_01_getLayerNo);

        // Item Creation Functions
        return_createItemForBoss =
            patch::hookFunction(libtp::tp::f_op_actor_mng::createItemForBoss, mod::handle_createItemForBoss);

        return_createItemForMidBoss =
            patch::hookFunction(libtp::tp::f_op_actor_mng::createItemForMidBoss, mod::handle_createItemForMidBoss);

        return_createItemForPresentDemo =
            patch::hookFunction(libtp::tp::f_op_actor_mng::createItemForPresentDemo, mod::handle_createItemForPresentDemo);

        return_createItemForTrBoxDemo =
            patch::hookFunction(libtp::tp::f_op_actor_mng::createItemForTrBoxDemo, mod::handle_createItemForTrBoxDemo);

        return_CheckFieldItemCreateHeap =
            patch::hookFunction(libtp::tp::d_a_itembase::CheckFieldItemCreateHeap, mod::handle_CheckFieldItemCreateHeap);

        // Item Wheel functions
        return_setLineUpItem = patch::hookFunction(tp::d_save::setLineUpItem, mod::handle_setLineUpItem);

        item_wheel_menu::return_dMenuRing__create =
            patch::hookFunction(libtp::tp::d_menu_ring::dMenuRing__create, item_wheel_menu::handle_dMenuRing__create);

        item_wheel_menu::return_dMenuRing__delete =
            patch::hookFunction(libtp::tp::d_menu_ring::dMenuRing__delete, item_wheel_menu::handle_dMenuRing__delete);

        item_wheel_menu::return_dMenuRing__draw =
            patch::hookFunction(libtp::tp::d_menu_ring::dMenuRing__draw, item_wheel_menu::handle_dMenuRing__draw);

        // ItemGet functions
        return_execItemGet = patch::hookFunction(libtp::tp::d_item::execItemGet, mod::handle_execItemGet);
        return_checkItemGet = patch::hookFunction(libtp::tp::d_item::checkItemGet, mod::handle_checkItemGet);
        return_item_func_ASHS_SCRIBBLING =
            patch::hookFunction(libtp::tp::d_item::item_func_ASHS_SCRIBBLING, mod::handle_item_func_ASHS_SCRIBBLING);

        // Message Functions
        return_setMessageCode_inSequence =
            patch::hookFunction(libtp::tp::control::setMessageCode_inSequence, mod::handle_setMessageCode_inSequence);

        return_getFontCCColorTable = patch::hookFunction(tp::d_msg_class::getFontCCColorTable, mod::handle_getFontCCColorTable);

        return_getFontGCColorTable = patch::hookFunction(tp::d_msg_class::getFontGCColorTable, mod::handle_getFontGCColorTable);

        return_jmessage_tSequenceProcessor__do_begin =
            patch::hookFunction(tp::d_msg_class::jmessage_tSequenceProcessor__do_begin,
                                mod::handle_jmessage_tSequenceProcessor__do_begin);

        return_jmessage_tSequenceProcessor__do_tag = patch::hookFunction(tp::d_msg_class::jmessage_tSequenceProcessor__do_tag,
                                                                         mod::handle_jmessage_tSequenceProcessor__do_tag);

        // Query/EventFunctions
        return_query022 = patch::hookFunction(libtp::tp::d_msg_flow::query022, mod::handle_query022);
        return_query023 = patch::hookFunction(libtp::tp::d_msg_flow::query023, mod::handle_query023);
        return_query025 = patch::hookFunction(libtp::tp::d_msg_flow::query025, mod::handle_query025);
        return_checkEmptyBottle = patch::hookFunction(libtp::tp::d_save::checkEmptyBottle, mod::handle_checkEmptyBottle);
        return_query037 = patch::hookFunction(libtp::tp::d_msg_flow::query037, mod::handle_query037);
        return_query049 = patch::hookFunction(libtp::tp::d_msg_flow::query049, mod::handle_query049);
        return_query042 = patch::hookFunction(libtp::tp::d_msg_flow::query042, mod::handle_query042);
        // return_event000 = patch::hookFunction( libtp::tp::d_msg_flow::event000, mod::handle_event000 );
        return_event017 = patch::hookFunction(libtp::tp::d_msg_flow::event017, mod::handle_event017);
        return_doFlow = patch::hookFunction(libtp::tp::d_msg_flow::doFlow, mod::handle_doFlow);
        return_setNormalMsg = patch::hookFunction(libtp::tp::d_msg_flow::setNormalMsg, mod::handle_setNormalMsg);

        // Save flag functions
        return_isDungeonItem = patch::hookFunction(tp::d_save::isDungeonItem, mod::handle_isDungeonItem);
        return_onDungeonItem = patch::hookFunction(tp::d_save::onDungeonItem, mod::handle_onDungeonItem);
        return_daNpcT_chkEvtBit = patch::hookFunction(libtp::tp::d_a_npc::daNpcT_chkEvtBit, mod::handle_daNpcT_chkEvtBit);
        return_isEventBit = patch::hookFunction(libtp::tp::d_save::isEventBit, mod::handle_isEventBit);
        return_onEventBit = patch::hookFunction(libtp::tp::d_save::onEventBit, mod::handle_onEventBit);

        return_isSwitch_dSv_memBit =
            patch::hookFunction(libtp::tp::d_save::isSwitch_dSv_memBit, mod::handle_isSwitch_dSv_memBit);

        return_onSwitch_dSv_memBit =
            patch::hookFunction(libtp::tp::d_save::onSwitch_dSv_memBit, mod::handle_onSwitch_dSv_memBit);

        return_checkTreasureRupeeReturn =
            patch::hookFunction(tp::d_a_alink::checkTreasureRupeeReturn, mod::handle_checkTreasureRupeeReturn);

        return_isDarkClearLV = patch::hookFunction(tp::d_save::isDarkClearLV, mod::handle_isDarkClearLV);

        // Pause Menu Functions
        return_collect_save_open_init =
            patch::hookFunction(tp::d_menu_window::collect_save_open_init, mod::handle_collect_save_open_init);

        // Link functions
        return_checkBootsMoveAnime =
            patch::hookFunction(libtp::tp::d_a_alink::checkBootsMoveAnime, mod::handle_checkBootsMoveAnime);

        return_setGetItemFace = patch::hookFunction(libtp::tp::d_a_alink::setGetItemFace, mod::handle_setGetItemFace);

        return_setWolfLockDomeModel =
            patch::hookFunction(libtp::tp::d_a_alink::setWolfLockDomeModel, mod::handle_setWolfLockDomeModel);

        return_procFrontRollCrashInit =
            patch::hookFunction(libtp::tp::d_a_alink::procFrontRollCrashInit, mod::handle_procFrontRollCrashInit);

        return_procWolfDashReverseInit =
            patch::hookFunction(libtp::tp::d_a_alink::procWolfDashReverseInit, mod::handle_procWolfDashReverseInit);

        return_procWolfAttackReverseInit =
            patch::hookFunction(libtp::tp::d_a_alink::procWolfAttackReverseInit, mod::handle_procWolfAttackReverseInit);

        return_searchBouDoor = patch::hookFunction(libtp::tp::d_a_alink::searchBouDoor, mod::handle_searchBouDoor);
        return_checkCastleTownUseItem =
            patch::hookFunction(libtp::tp::d_a_alink::checkCastleTownUseItem, mod::handle_checkCastleTownUseItem);

        return_damageMagnification =
            patch::hookFunction(libtp::tp::d_a_alink::damageMagnification, mod::handle_damageMagnification);

        return_procCoGetItemInit = patch::hookFunction(libtp::tp::d_a_alink::procCoGetItemInit, mod::handle_procCoGetItemInit);

        // Audio functions
        return_loadSeWave = patch::hookFunction(libtp::z2audiolib::z2scenemgr::loadSeWave, mod::handle_loadSeWave);
        return_sceneChange = patch::hookFunction(libtp::z2audiolib::z2scenemgr::sceneChange, mod::handle_sceneChange);
        return_startSound = patch::hookFunction(libtp::z2audiolib::z2soundmgr::startSound, mod::handle_startSound);
        return_checkBgmIDPlaying =
            patch::hookFunction(libtp::z2audiolib::z2seqmgr::checkBgmIDPlaying, mod::handle_checkBgmIDPlaying);

        // Title Screen functions
        return_dScnLogo_c_dt = patch::hookFunction(libtp::tp::d_s_logo::dScnLogo_c_dt, mod::handle_dScnLogo_c_dt);

        // Enemy BGM
        user_patch::bgm::enemybgm::return_startBattleBgm =
            patch::hookFunction(libtp::z2audiolib::z2seqmgr::startBattleBgm, user_patch::handle_startBattleBgm);

        // Archive/Resource functions
        return_getResInfo = patch::hookFunction(libtp::tp::d_resource::getResInfo, mod::handle_getResInfo);

        return_mountArchive__execute =
            patch::hookFunction(libtp::tp::m_Do_dvd_thread::mountArchive__execute, mod::handle_mountArchive__execute);

        // d_meter functions
        return_resetMiniGameItem =
            patch::hookFunction(libtp::tp::d_meter2_info::resetMiniGameItem, mod::handle_resetMiniGameItem);

        // Game Over functions
        return_dispWait_init = patch::hookFunction(libtp::tp::d_gameover::dispWait_init, mod::handle_dispWait_init);

        // Shop Functions
        return_seq_decide_yes = patch::hookFunction(libtp::tp::d_shop_system::seq_decide_yes, mod::handle_seq_decide_yes);
    }

    void initRandState()
    {
        uint32_t state;

        // randState is being used with xorshift32, which requires the state to not be 0. OSGetTick may return 0, so keep
        // calling it until it does not return 0.
        do
        {
            state = libtp::gc_wii::os_time::OSGetTick();
        } while (state == 0);

        randState = state;
    }

    void initArcLookupTable()
    {
        using libtp::gc_wii::dvdfs::DVDConvertPathToEntrynum;

        rando::lookupTable[rando::ResObjectKmdl] = DVDConvertPathToEntrynum("/res/Object/Kmdl.arc"); // Hero's Clothes
        rando::lookupTable[rando::ResObjectZmdl] = DVDConvertPathToEntrynum("/res/Object/Zmdl.arc"); // Zora Armor
        rando::lookupTable[rando::ResObjectOgZORA] =
            DVDConvertPathToEntrynum("/res/Object/O_gD_zora.arc"); // Zora Armor - Get Item
        // lookupTable[ResObjectWmdl] = DVDConvertPathToEntrynum( "/res/Object/Wmdl.arc" );
        // lookupTable[ResObjectCWShd] = DVDConvertPathToEntrynum( "/res/Object/CWShd.arc" );
        // lookupTable[ResObjectSWShd] = DVDConvertPathToEntrynum( "/res/Object/SWShd.arc" );
        // lookupTable[ResObjectHyShd] = DVDConvertPathToEntrynum( "/res/Object/HyShd.arc" );
    }

    void writeCodehandlerToMemory()
    {
        // Clear the cache for the codehandler flag and source address to be safe
        uint8_t* codehandlerIsWrittenAddress = reinterpret_cast<uint8_t*>(0x800013FF);
        libtp::gc_wii::os_cache::DCFlushRange(codehandlerIsWrittenAddress, sizeof(uint8_t));

        // Only the first 4 bytes of the codehandler source address's cache needs to be cleared, as we only need to check the
        // first 4 bytes to determine if anything else should be done
        uint32_t* dst = reinterpret_cast<uint32_t*>(0x80001800);
        libtp::memory::clear_DC_IC_Cache(dst, sizeof(uint32_t));

        // If something is already at 0x80001800, then assume a codehandler is already in place
        bool codehandlerIsWritten = static_cast<bool>(*codehandlerIsWrittenAddress);
        if (dst[0] != 0)
        {
            // If the codehandler has not been manually written, then assume an external codehandler is being used
            if (!codehandlerIsWritten)
            {
                return;
            }
        }
        else if (codehandlerIsWritten)
        {
            // Somehow nothing is at 0x80001800 when the codehandler was previously written
            return;
        }

        // Disable interrupts to be safe
        bool enable = libtp::gc_wii::os_interrupt::OSDisableInterrupts();

        // Write the codehandler to memory if necessary
        if (!codehandlerIsWritten)
        {
            // Perform a safety clear before writing the codehandler
            const uint32_t size = codehandler::codehandlerSize;
            libtp::memory::clearMemory(dst, size);

            // Copy the codehandler to 0x80001800
            memcpy(dst, reinterpret_cast<const void*>(codehandler::codehandler), size);

            // Copy the game id, disc number, and version number to 0x80001800
            // These use a total of 8 bytes, so handle as uint32_t variables for simplicity
            uint32_t* gameInfo = reinterpret_cast<uint32_t*>(0x80000000);
            dst[0] = gameInfo[0];
            dst[1] = gameInfo[1];

            // Uncomment out the next line to enable pause at boot
            // *reinterpret_cast<uint32_t*>( 0x80002774 ) = 1;

            // Clear the cache for the codehandler
            libtp::memory::clear_DC_IC_Cache(dst, size);

            // Set the flag for the codehandler being manually written and clear the cache for it
            *codehandlerIsWrittenAddress = 1;
            libtp::gc_wii::os_cache::DCFlushRange(codehandlerIsWrittenAddress, sizeof(uint8_t));
        }

        // Hook VISetNextFrameBuffer to branch to the codehandler
        uint32_t VISetNextFrameBufferAddress = reinterpret_cast<uint32_t>(libtp::gc_wii::vi::VISetNextFrameBuffer);
        libtp::patch::writeBranchBL(VISetNextFrameBufferAddress + 0x44, assembly::asmCallCodehandler);

        // Restore interrupts
        libtp::gc_wii::os_interrupt::OSRestoreInterrupts(enable);
    }
} // namespace mod