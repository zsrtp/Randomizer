/**
 * @file 05_clearRegionTwilights.h
 * @author Lunar Soap
 * @brief Contains function definitions for clearing the twilights in different regions.
 *
 * @bug No known bugs
 */

#ifndef RANDO_CLEAR_REGION_TWILIGHTS_PATCH_H
#define RANDO_CLEAR_REGION_TWILIGHTS_PATCH_H

#include "rando/randomizer.h"

namespace mod::user_patch
{
    /**
     * @brief Sets the flags to clear a specified twilight
     */
    void clearFaronTwilight( rando::Randomizer* randomizer, bool set );
    void clearEldinTwilight( rando::Randomizer* randomizer, bool set );
    void clearLanayruTwilight( rando::Randomizer* randomizer, bool set );
}     // namespace mod::user_patch

#endif