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

namespace mod::user_patch
{
    /**
     * @brief Patches the game to allow for optional enemy BGM
     */
    void patchBattleMusic( rando::Randomizer* randomizer, bool set );
}     // namespace mod::user_patch

#endif