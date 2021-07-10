/**
 * @file 01_randombgm.h
 * @author jdflyer
 * @brief Handles randomizing the game's BGM
 *
 * @bug No known bugs
 */
#ifndef RANDO_RANDOM_BGM_PATCH_H
#define RANDO_RANDOM_BGM_PATCH_H
#include "game_patch/game_patch.h"

namespace mod::game_patch
{
    /**
     * @brief Enables Random Background Music
     */
    void patchRandomBgm( rando::Randomizer* randomizer, bool set );

}     // namespace mod::game_patch

#endif