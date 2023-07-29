/** @file user_patch.h
 * @author AECX
 * @brief User patches are optional & modify how the game works.
 *
 * @bug No known bugs
 */
#ifndef RANDO_USER_PATCH_H
#define RANDO_USER_PATCH_H

#include <cstdint>

#include "rando/randomizer.h"

namespace mod::user_patch
{
    /**
     *  @brief Defines a game_patch function
     *
     *  @param randomizer Pointer to currently active Randomizer
     *  @param set If true we apply the patch, otherwise restore original behavior
     */
    typedef void (*GamePatch)(rando::Randomizer* randomizer, bool set);

    // Available Game patches accessible by index
    extern GamePatch volatilePatches[6];
    extern GamePatch oneTimePatches[6];

} // namespace mod::user_patch
#endif