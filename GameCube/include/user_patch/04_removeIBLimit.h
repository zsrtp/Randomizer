/**
 * @file 04_removeIBLimit.h
 * @author Lunar Soap
 * @brief Contains function definitions for patching IB Speed
 *
 * @bug No known bugs
 */

#ifndef RANDO_REMOVE_IB_LIMIT_PATCH_H
#define RANDO_REMOVE_IB_LIMIT_PATCH_H

#include "rando/randomizer.h"

namespace mod::user_patch
{
    /**
     * @brief Patches the functions that modify the IB speed
     */
    void removeIBLimit(rando::Randomizer* randomizer, bool set);
} // namespace mod::user_patch

#endif