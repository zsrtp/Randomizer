/** @file game_patch.cpp
 * @author AECX
 * @brief Game patches are functions that change game functions.
 *
 * @bug No known bugs
 */

#include "game_patch/game_patch.h"

#include "game_patch/00_wallet.h"
#include "game_patch/01_randombgm.h"
#include "game_patch/02_enemybgm.h"

namespace mod::game_patch
{
    GamePatch patches[3] = { patchWallet, initRandomBgm, patchBattleMusic };
}