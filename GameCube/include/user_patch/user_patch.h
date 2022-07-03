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

// Instruction templates
#define ASM_NOP 0x60000000
#define ASM_BRANCH( length ) 0x48000000 + ( static_cast<uint32_t>( length ) & 0x3FFFFFC )
#define ASM_LOAD_IMMEDIATE( register, value ) ( 0x38000000 + ( register * 0x200000 ) ) | ( value & 0xFFFF )
#define ASM_COMPARE_WORD_IMMEDIATE( register, value ) ( 0x2C000000 + ( register * 0x10000 ) ) | ( value & 0xFFFF )
#define ASM_COMPARE_LOGICAL_WORD_IMMEDIATE( register, value ) ( 0x28000000 + ( register * 0x10000 ) ) | ( value & 0xFFFF )

namespace mod::user_patch
{
    /**
     *  @brief Defines a game_patch function
     *
     *  @param randomizer Pointer to currently active Randomizer
     *  @param set If true we apply the patch, otherwise restore original behavior
     */
    typedef void ( *GamePatch )( rando::Randomizer* randomizer, bool set );

    // Available Game patches accessible by index
    extern GamePatch volatilePatches[5];
    extern GamePatch oneTimePatches[4];

}     // namespace mod::user_patch
#endif