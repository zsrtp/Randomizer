/**
 * @file 01_randombgm.h
 * @author jdflyer
 * @brief Handles randomizing the game's BGM
 *
 * @bug No known bugs
 */
#ifndef RANDO_RANDOM_BGM_PATCH_H
#define RANDO_RANDOM_BGM_PATCH_H

#include "rando/randomizer.h"

namespace mod::user_patch
{
    /**
     * @brief Enables Random Background Music
     */
    void patchRandomBgm( rando::Randomizer* randomizer, bool set );

}     // namespace mod::user_patch

#endif