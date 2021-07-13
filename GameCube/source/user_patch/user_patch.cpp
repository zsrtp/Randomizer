/** @file game_patch.cpp
 * @author AECX
 * @brief Game patches are functions that change game functions.
 *
 * @bug No known bugs
 */

#include "user_patch/00_wallet.h"
#include "user_patch/01_randombgm.h"
#include "user_patch/02_enemybgm.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    GamePatch patches[3] = { patchWallet, patchRandomBgm, patchBattleMusic };
}