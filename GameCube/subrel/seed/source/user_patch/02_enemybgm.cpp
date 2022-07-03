/**
 * @file 02_enemybgm.h
 * @author jdflyer
 * @brief Patches the game to allow for optional enemy BGM
 *
 * @bug No known bugs
 */
#include "user_patch/02_enemybgm.h"
#include "Z2AudioLib/Z2SeqMgr.h"
#include "main.h"

namespace mod::user_patch
{
    void disableBattleMusic( rando::Randomizer* randomizer, bool set )
    {
        disableEnemyBgm = set;
        mod::console << "[2] EnemyBgmDisabled [" << ( set ? "x" : " " ) << "]\n";
    }
}     // namespace mod::user_patch