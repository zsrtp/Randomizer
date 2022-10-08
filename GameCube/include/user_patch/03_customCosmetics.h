/**
 * @file 03_customCosmetics.h
 * @author Lunar Soap
 * @brief Contains function definitions for patching cosmetics.
 *
 * @bug No known bugs
 */

#ifndef RANDO_CUSTOM_COSMETICS_PATCH_H
#define RANDO_CUSTOM_COSMETICS_PATCH_H

#include "rando/randomizer.h"

namespace mod::user_patch
{
    /**
     * @brief Updates the cosmetics for the user interface (Buttons, Hearts, etc.)
     */
    void setHUDCosmetics( rando::Randomizer* randomizer );
}     // namespace mod::user_patch

#endif