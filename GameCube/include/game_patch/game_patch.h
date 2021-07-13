/** @file game_patch.h
 * @author AECX
 * @brief Game patches are always applied & mostly used to fix a bug/softlog.
 *
 * @bug No known bugs
 */
#ifndef RANDO_GAME_PATCH_H
#define RANDO_GAME_PATCH_H

#include <cstdint>

namespace mod::game_patch
{
    void _00_poe( void );
}     // namespace mod::game_patch
#endif