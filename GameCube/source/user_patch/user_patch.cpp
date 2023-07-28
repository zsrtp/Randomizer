/** @file game_patch.cpp
 * @author AECX
 * @brief Game patches are functions that change game functions.
 *
 * @bug No known bugs
 */

#include "user_patch/user_patch.h"

#include "user_patch/03_customCosmetics.h"
#include "user_patch/05_newFileFunctions.h"

namespace mod::user_patch
{
    GamePatch volatilePatches[6] =
        {clearFaronTwilight, clearEldinTwilight, clearLanayruTwilight, setMinorCutsceneValues, clearMDH, setMapRegionBits};
}