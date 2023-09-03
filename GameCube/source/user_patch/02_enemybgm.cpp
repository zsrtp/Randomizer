/**
 * @file 02_enemybgm.h
 * @author jdflyer
 * @brief Patches the game to allow for optional enemy BGM
 *
 * @bug No known bugs
 */
#include "user_patch/02_enemybgm.h"

#include "Z2AudioLib/Z2SeqMgr.h"
#include "main.h"

namespace mod::user_patch
{
    namespace bgm::enemybgm
    {
        KEEP_VAR void (*return_startBattleBgm)(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1) = nullptr;
    } // namespace bgm::enemybgm

    // Handles if enemy BGM should be enabled
    KEEP_VAR bool disableEnemyBgm = false;

    KEEP_FUNC void handle_startBattleBgm(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1)
    {
        if (disableEnemyBgm)
        {
            return;
        }

        // Call the original function
        bgm::enemybgm::return_startBattleBgm(seqMgr, param_1);
    }
} // namespace mod::user_patch