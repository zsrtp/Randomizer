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
    namespace bgm::enemybgm
    {
        KEEP_VAR void ( *return_startBattleBgm )( libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1 ) = nullptr;
    }     // namespace bgm::enemybgm

    // Temporary bool used to check if enemy BGM should be enabled
    // May be removed when the code is rewritten
    bool enemyBgm = false;

    void enableBattleMusic( rando::Randomizer* randomizer, bool set )
    {
        mod::console << "[2] EnemyBgmDisabled [" << ( set ? "x" : " " ) << "]\n";
        enemyBgm = set;
    }

    KEEP_FUNC void handleStartBattleBgm( libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1 )
    {
        if ( !enemyBgm )
        {
            return;
        }

        bgm::enemybgm::return_startBattleBgm( seqMgr, param_1 );
    }
}     // namespace mod::user_patch