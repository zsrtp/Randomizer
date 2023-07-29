/**
 * @file 05_newFileFunctions.h
 * @author Lunar Soap
 * @brief Contains function definitions that patch the game based on user settings.
 *
 * @bug No known bugs
 */

#ifndef RANDO_NEW_FILE_FUNCTIONS_PATCH_H
#define RANDO_NEW_FILE_FUNCTIONS_PATCH_H

#include "rando/randomizer.h"

namespace mod::user_patch
{
    /**
     * @brief A list of potential functions to run upon seed initialization.
     */
    void clearFaronTwilight(rando::Randomizer* randomizer, bool set);
    void clearEldinTwilight(rando::Randomizer* randomizer, bool set);
    void clearLanayruTwilight(rando::Randomizer* randomizer, bool set);
    void loadShopModels(rando::Randomizer* randomizer, bool set);
    void setMinorCutsceneValues(rando::Randomizer* randomizer, bool set);
    void clearMDH(rando::Randomizer* randomizer, bool set);
    void setInstantText(rando::Randomizer* randomizer, bool set);
    void setMapRegionBits(rando::Randomizer* randomizer, bool set);
    void increaseSpinnerVelocity(rando::Randomizer* randomizer, bool set);
} // namespace mod::user_patch

#endif