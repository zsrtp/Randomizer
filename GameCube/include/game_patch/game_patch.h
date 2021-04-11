/** @file game_patch.h
 * @author AECX
 * @brief Game patches are functions that change game functions.
 *
 * @bug No known bugs
 */
#ifndef RANDO_GAME_PATCH_H
#define RANDO_GAME_PATCH_H

#include <cstdint>

// Instruction templates
#define asm_li 0x38600000
#define asm_cmpwi 0x2c000000

namespace mod::game_patch
{
    /**
     *  @brief Defines a game_patch function
     *
     *  @param set If true we apply the patch, otherwise restore original behavior
     */
    typedef void ( *GamePatch )( bool set );

    // Available Game patches accessible by index
    extern GamePatch patches[1];

}     // namespace mod::game_patch
#endif