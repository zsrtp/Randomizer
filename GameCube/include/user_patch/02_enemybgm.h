/**
 * @file 02_enemybgm.h
 * @author jdflyer
 * @brief Patches the game to allow for optional enemy BGM
 *
 * @bug No known bugs
 */

#ifndef RANDO_ENEMY_BGM_PATCH_H
#define RANDO_ENEMY_BGM_PATCH_H

#include "rando/randomizer.h"
#include "Z2AudioLib/Z2SeqMgr.h"

namespace mod::user_patch
{
    namespace bgm::enemybgm
    {
        /**
         * @brief startBattleBgm function hook handler
         */
        extern void (*return_startBattleBgm)(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1);
    } // namespace bgm::enemybgm

    /**
     * @brief Handles if enemy BGM should be enabled
     */
    extern bool disableEnemyBgm;

    /**
     * @brief Patches the game to allow for optional enemy BGM
     */
    void disableBattleMusic(rando::Randomizer* randomizer, bool set);

    /**
     * @brief Handles Enemy Background Music
     */
    void handle_startBattleBgm(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1);
} // namespace mod::user_patch

#endif