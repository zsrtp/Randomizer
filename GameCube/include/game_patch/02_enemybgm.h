/**
 * @file 02_enemybgm.h
 * @author jdflyer
 * @brief Patches the game to allow for optional enemy BGM
 *
 * @bug No known bugs
 */

#ifndef RANDO_ENEMY_BGM_PATCH_H
#define RANDO_ENEMY_BGM_PATCH_H
#include "game_patch/game_patch.h"

namespace mod::game_patch
{
    /**
     * @brief Patches the game to allow for optional enemy BGM
     */
    void patchBattleMusic( rando::Randomizer* randomizer, bool set );
}     // namespace mod::game_patch

#endif