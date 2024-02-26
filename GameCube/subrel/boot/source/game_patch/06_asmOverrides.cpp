#include <cstdint>

#include "game_patch/game_patch.h"
#include "asm_templates.h"
#include "tp/d_item.h"
#include "tp/d_msg_flow.h"
#include "tp/d_a_alink.h"
#include "data/items.h"
#include "tp/d_menu_collect.h"
#include "patch.h"
#include "events.h"
#include "tp/d_kankyo_rain.h"
#include "asm.h"
#include "tp/d_com_inf_game.h"
#include "tp/m_Do_dvd_thread.h"
#include "Z2AudioLib/Z2SceneMgr.h"
#include "tp/d_msg_object.h"
#include "tp/d_meter2_draw.h"
#include "tp/m_Do_machine.h"
#include "tp/d_msg_unit.h"

namespace mod::game_patch
{
    void _06_writeASMPatches()
    {
        // Perform the overwrites

        /* If the address is loaded into the cache before the overwrite is made,
        then the cache will need to be cleared after the overwrite */

        // Enable the crash screen
#ifdef PLATFORM_WII
        constexpr uint32_t crashScreenAddressOffset = 0x198;
        constexpr uint32_t crashScreenBranchDistance = 0x2C;
#else
        constexpr uint32_t crashScreenAddressOffset = 0xDC;
        constexpr uint32_t crashScreenBranchDistance = 0x14;
#endif
        uint32_t myExceptionCallbackAddress = reinterpret_cast<uint32_t>(libtp::tp::m_Do_machine::myExceptionCallback);

        *reinterpret_cast<uint32_t*>(myExceptionCallbackAddress + crashScreenAddressOffset) =
            ASM_BRANCH(crashScreenBranchDistance);

        // Nop out the instruction that causes a miscalculation in message resources.
#ifdef TP_GJP
        constexpr uint32_t setTagAddressOffset = 0x2E0;
#elif defined PLATFORM_WII
        constexpr uint32_t setTagAddressOffset = 0x39C;
#else
        constexpr uint32_t setTagAddressOffset = 0x26C;
#endif
        uint32_t setTagAddress = reinterpret_cast<uint32_t>(libtp::tp::d_msg_unit::setTag);
        *reinterpret_cast<uint32_t*>(setTagAddress + setTagAddressOffset) = ASM_NOP;

        // Modify the Wooden Sword function to not set a region flag by default by nopping out the function call to isSwitch
        uint32_t woodenSwordAddress = reinterpret_cast<uint32_t>(libtp::tp::d_item::item_func_WOOD_STICK);
        *reinterpret_cast<uint32_t*>(woodenSwordAddress + 0x40) = ASM_NOP; // Previous 0x4bf9cafd

        // Modify the Heart Container function to not set the dungeon flag for the heart container upon collection
#ifdef PLATFORM_WII
        constexpr uint32_t heartContainerAddressOffset = 0x74;
#else
        constexpr uint32_t heartContainerAddressOffset = 0x7C;
#endif
        uint32_t heartContainerAddress = reinterpret_cast<uint32_t>(libtp::tp::d_item::item_func_UTUWA_HEART);
        *reinterpret_cast<uint32_t*>(heartContainerAddress + heartContainerAddressOffset) = ASM_NOP; // Previous 0x4bf9c5e9

        // Modify event035 to not remove Auru's Memo from inventory after talking to Fyer.
        uint32_t event035MemoAddress = reinterpret_cast<uint32_t>(libtp::tp::d_msg_flow::event035);

#ifdef PLATFORM_WII
        *reinterpret_cast<uint32_t*>(event035MemoAddress + 0x34) =
            ASM_SUBTRACT_IMMEDIATE(0, 4, libtp::data::items::Asheis_Sketch); // Previous 0x3804ff70

        *reinterpret_cast<uint32_t*>(event035MemoAddress + 0x38) =
            ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(0, 0); // Previous 0x28000001
#else
        *reinterpret_cast<uint32_t*>(event035MemoAddress + 0x40) =
            ASM_COMPARE_WORD_IMMEDIATE(4, libtp::data::items::Asheis_Sketch); // Previous 0x2c040090
#endif

        // Modify procCoGetItem to display the 20 and 60 poe messages when the player currently has 19 and 59 respectively, as
        // this project changes the poe count to increment after the message is displayed instead of before
#ifdef PLATFORM_WII
        constexpr uint32_t procCoGetItemAddressOffset = 0x524;
#else
        constexpr uint32_t procCoGetItemAddressOffset = 0x56C;
#endif
        uint32_t procCoGetItemAddress = reinterpret_cast<uint32_t>(libtp::tp::d_a_alink::procCoGetItem);

        *reinterpret_cast<uint32_t*>(procCoGetItemAddress + procCoGetItemAddressOffset) =
            ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(0, 19);

        *reinterpret_cast<uint32_t*>(procCoGetItemAddress + procCoGetItemAddressOffset + 0x14) =
            ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(0, 59);

        // Prevent onStageBossEnemyAddress from setting the Ooccoo flag when defeating a boss.
#ifdef PLATFORM_WII
        constexpr uint32_t onStageBossEnemyAddressOffset = 0x58;
#else
        constexpr uint32_t onStageBossEnemyAddressOffset = 0x60;
#endif
        uint32_t onStageBossEnemyAddress = reinterpret_cast<uint32_t>(libtp::tp::d_com_inf_game::dComIfGs_onStageBossEnemy);
        *reinterpret_cast<uint32_t*>(onStageBossEnemyAddress + onStageBossEnemyAddressOffset) = ASM_NOP; // Previous 480070e9

        *reinterpret_cast<uint32_t*>(onStageBossEnemyAddress + onStageBossEnemyAddressOffset + 0x2C) =
            ASM_NOP; // Previous 480070bd

        // Patch setSceneName so that the Morpheel Boss Music plays even if MDH is skipped.
        // Wii code is different here, so maybe not necessary?
#ifdef PLATFORM_WII
        constexpr uint32_t setSceneNameAddressOffset = 0x1A60;
        constexpr uint32_t setSceneNameBranchDistance = 0x14;
#else
        constexpr uint32_t setSceneNameAddressOffset = 0x216C;
        constexpr uint32_t setSceneNameBranchDistance = 0x28;
#endif
        uint32_t setSceneNameAddress = reinterpret_cast<uint32_t>(libtp::z2audiolib::z2scenemgr::setSceneName);
        *reinterpret_cast<uint32_t*>(setSceneNameAddress + setSceneNameAddressOffset) = ASM_BRANCH(setSceneNameBranchDistance);

#ifdef PLATFORM_WII
        constexpr uint32_t mountArchive__execute_Address_Offset = 0x11C;
#else
        constexpr uint32_t mountArchive__execute_Address_Offset = 0x200;
#endif
        uint32_t mountArchive__execute_Address = reinterpret_cast<uint32_t>(libtp::tp::m_Do_dvd_thread::mountArchive__execute);
        events::performStaticASMReplacement(mountArchive__execute_Address + mountArchive__execute_Address_Offset, ASM_NOP);

        // Modify dKyr_odour_draw to draw the Reekfish path so long as we have smelled the fish once.
#ifdef PLATFORM_WII
        constexpr uint32_t odourDrawAddressOffset = 0xC0;
#else
        constexpr uint32_t odourDrawAddressOffset = 0xBC;
#endif
        uint32_t odourDrawAddress = reinterpret_cast<uint32_t>(libtp::tp::d_kankyo_rain::dKyr_odour_draw);
        libtp::patch::writeBranchBL(odourDrawAddress + odourDrawAddressOffset, assembly::asmShowReekfishPath);

        // Modify getRupeeMax calls in screenSet to display the proper wallet in the pause menu
#ifdef PLATFORM_WII
        constexpr uint32_t dMenuCollect_screenSet_Offset_1 = 0xC80;
        constexpr uint32_t dMenuCollect_screenSet_Offset_2 = 0xCA0;
#else
        constexpr uint32_t dMenuCollect_screenSet_Offset_1 = 0xDCC;
        constexpr uint32_t dMenuCollect_screenSet_Offset_2 = 0xDF0;
#endif
        uint32_t screenSetAddress = reinterpret_cast<uint32_t>(libtp::tp::d_menu_collect::dMenuCollect_screenSet);
        libtp::patch::writeBranchBL(screenSetAddress + dMenuCollect_screenSet_Offset_1, events::getPauseRupeeMax);
        libtp::patch::writeBranchBL(screenSetAddress + dMenuCollect_screenSet_Offset_2, events::getPauseRupeeMax);

        // Modify isSend button checks to allow for automashing through text
#ifdef PLATFORM_WII
        constexpr uint32_t isSendAddressOffset1 = 0xE0;
        constexpr uint32_t isSendAddressOffset2 = 0x160;
        constexpr uint32_t isSendAddressOffset3 = 0x1BC;
#else
        constexpr uint32_t isSendAddressOffset1 = 0xE4;
        constexpr uint32_t isSendAddressOffset2 = 0x160;
        constexpr uint32_t isSendAddressOffset3 = 0x1B8;
#endif
        uint32_t isSendAddress = reinterpret_cast<uint32_t>(libtp::tp::d_msg_object::isSend);
        libtp::patch::writeBranchBL(isSendAddress + isSendAddressOffset1, events::autoMashThroughText);
        libtp::patch::writeBranchBL(isSendAddress + isSendAddressOffset2, events::autoMashThroughText);
        libtp::patch::writeBranchBL(isSendAddress + isSendAddressOffset3, events::autoMashThroughText);

        // Modify drawKanteraScreen to change the lantern meter color to match lantern light color from seed.
#ifdef PLATFORM_WII
        constexpr uint32_t drawKanteraAddressOffset = 0xDC;
#else
        constexpr uint32_t drawKanteraAddressOffset = 0xE4;
#endif
        uint32_t drawKanteraAddress = reinterpret_cast<uint32_t>(libtp::tp::d_meter2_draw::drawKanteraScreen);
        libtp::patch::writeBranchBL(drawKanteraAddress + drawKanteraAddressOffset, events::modifyLanternMeterColor);

#if defined TP_GJP || defined TP_WUS2
#ifdef TP_WUS2
        constexpr uint32_t checkWarpStartAddressNopOffset = 0x14C;
        constexpr uint32_t checkWarpStartAddressHookOffset = 0x68;
#else
        constexpr uint32_t checkWarpStartAddressNopOffset = 0x15C;
        constexpr uint32_t checkWarpStartAddressHookOffset = 0x64;
#endif
        // Patch checkWarpStart to remove the instruction that updates the map glitch value later
        uint32_t checkWarpStartAddress = reinterpret_cast<uint32_t>(libtp::tp::d_a_alink::checkWarpStart);
        *reinterpret_cast<uint32_t*>(checkWarpStartAddress + checkWarpStartAddressNopOffset) = ASM_NOP; // Previous 0x901e0570

        // Patch checkWarpStart to allow map glitch to work
        libtp::patch::writeStandardBranches(checkWarpStartAddress + checkWarpStartAddressHookOffset,
                                            assembly::asmUnpatchMapGlitchStart,
                                            assembly::asmUnpatchMapGlitchEnd);
#endif
    }
} // namespace mod::game_patch