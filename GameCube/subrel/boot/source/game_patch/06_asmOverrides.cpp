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

namespace mod::game_patch
{
    void _06_writeASMPatches()
    {
        // Get the addresses to overwrite
#ifdef TP_US
        uint32_t* enableCrashScreen = reinterpret_cast<uint32_t*>(0x8000B8A4);
        uint32_t* patchMessageCalculation = reinterpret_cast<uint32_t*>(0x80238F58);
#elif defined TP_EU
        uint32_t* enableCrashScreen = reinterpret_cast<uint32_t*>(0x8000B878);
        uint32_t* patchMessageCalculation = reinterpret_cast<uint32_t*>(0x802395D8);
#elif defined TP_JP
        uint32_t* enableCrashScreen = reinterpret_cast<uint32_t*>(0x8000B8A4);
        uint32_t* patchMessageCalculation = reinterpret_cast<uint32_t*>(0x802398E0);
#endif

        // Perform the overwrites

        /* If the address is loaded into the cache before the overwrite is made,
        then the cache will need to be cleared after the overwrite */

        // Enable the crash screen
        *enableCrashScreen = ASM_BRANCH(0x14);

        // Nop out the instruction that causes a miscalculation in message resources.
        *patchMessageCalculation = ASM_NOP;

        // Modify the skipper function to check whether or not a cutscene is skippable instead of whether the player skips the
        // CS. This effectively auto-skips all skippable cutscenes.
        uint32_t skipperFunctionAddress = reinterpret_cast<uint32_t>(libtp::tp::d_event::skipper);
        *reinterpret_cast<uint32_t*>(skipperFunctionAddress + 0x54) =
            ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(30, 0); // Previous rlwinm r0,r0,0,19,19

        // Modify the Wooden Sword function to not set a region flag by default by nopping out the function call to isSwitch
        uint32_t woodenSwordFunctionAddress = reinterpret_cast<uint32_t>(libtp::tp::d_item::item_func_WOOD_STICK);
        *reinterpret_cast<uint32_t*>(woodenSwordFunctionAddress + 0x40) = ASM_NOP; // Previous 0x4bf9cafd

        // Modify the Heart Container function to not set the dungeon flag for the heart container upon collection
        uint32_t heartContainerFunctionAddress = reinterpret_cast<uint32_t>(libtp::tp::d_item::item_func_UTUWA_HEART);
        *reinterpret_cast<uint32_t*>(heartContainerFunctionAddress + 0x7C) = ASM_NOP; // Previous 0x4bf9c5e9

        // Modify event035 to not remove Auru's Memo from inventory after talking to Fyer.
        uint32_t event035MemoAddress = reinterpret_cast<uint32_t>(libtp::tp::d_msg_flow::event035);

        *reinterpret_cast<uint32_t*>(event035MemoAddress + 0x40) =
            ASM_COMPARE_WORD_IMMEDIATE(4, libtp::data::items::Asheis_Sketch); // Previous 0x2c040090

        // Modify procCoGetItem to display the 20 and 60 poe messages when the player currently has 19 and 59 respectively, as
        // this project changes the poe count to increment after the message is displayed instead of before
        uint32_t procCoGetItemAddress = reinterpret_cast<uint32_t>(libtp::tp::d_a_alink::procCoGetItem);
        *reinterpret_cast<uint32_t*>(procCoGetItemAddress + 0x56C) = ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(0, 19);
        *reinterpret_cast<uint32_t*>(procCoGetItemAddress + 0x580) = ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(0, 59);

        // Prevent onStageBossEnemyAddress from setting the Ooccoo flag when defeating a boss.
        uint32_t onStageBossEnemyAddress = reinterpret_cast<uint32_t>(libtp::tp::d_com_inf_game::dComIfGs_onStageBossEnemy);
        *reinterpret_cast<uint32_t*>(onStageBossEnemyAddress + 0x60) = ASM_NOP; // Previous 480070e9
        *reinterpret_cast<uint32_t*>(onStageBossEnemyAddress + 0x8C) = ASM_NOP; // Previous 480070bd

        // Patch setSceneName so that the Morpheel Boss Music plays even if MDH is skipped.
        uint32_t setSceneNameAddress = reinterpret_cast<uint32_t>(libtp::z2audiolib::z2scenemgr::setSceneName);
        *reinterpret_cast<uint32_t*>(setSceneNameAddress + 0x216C) = ASM_BRANCH(0x28); // Previous beq- 0x28

        uint32_t mDoDvdThd_mountArchive_c__execute =
            reinterpret_cast<uint32_t>(libtp::tp::m_Do_dvd_thread::mountArchive__execute);

        events::performStaticASMReplacement(mDoDvdThd_mountArchive_c__execute + 0x200, ASM_NOP);

        // Modify dKyr_odour_draw to draw the Reekfish path so long as we have smelled the fish once.
        uint32_t odourDrawAddress = reinterpret_cast<uint32_t>(libtp::tp::d_kankyo_rain::dKyr_odour_draw);
        libtp::patch::writeBranchBL(odourDrawAddress + 0xBC, assembly::asmShowReekfishPath);

        // Modify getRupeeMax calls in screenSet to display the proper wallet in the pause menu
        uint32_t screenSetAddress = reinterpret_cast<uint32_t>(libtp::tp::d_menu_collect::dMenuCollect_screenSet);
        libtp::patch::writeBranchBL(screenSetAddress + 0xDCC, events::getPauseRupeeMax);
        libtp::patch::writeBranchBL(screenSetAddress + 0xDF0, events::getPauseRupeeMax);

        // Modify isSend button checks to allow for automashing through text
        uint32_t isSendAddress = reinterpret_cast<uint32_t>(libtp::tp::d_msg_object::isSend);
        libtp::patch::writeBranchBL(isSendAddress + 0xE4, events::autoMashThroughText);
        libtp::patch::writeBranchBL(isSendAddress + 0x160, events::autoMashThroughText);
        libtp::patch::writeBranchBL(isSendAddress + 0x1B8, events::autoMashThroughText);
#ifdef TP_JP
        uint32_t checkWarpStartAddress = reinterpret_cast<uint32_t>(libtp::tp::d_a_alink::checkWarpStart);

        // Patch checkWarpStart to remove the instruction that updates the map glitch value later
        *reinterpret_cast<uint32_t*>(checkWarpStartAddress + 0x15C) = ASM_NOP; // Previous 0x901e0570

        // Patch checkWarpStart to allow map glitch to work
        libtp::patch::writeStandardBranches(checkWarpStartAddress + 0x64,
                                            assembly::asmUnpatchMapGlitchStart,
                                            assembly::asmUnpatchMapGlitchEnd);
#endif
    }
} // namespace mod::game_patch