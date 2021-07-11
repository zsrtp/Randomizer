/**
 * @file 02_enemybgm.h
 * @author jdflyer
 * @brief Patches the game to allow for optional enemy BGM
 *
 * @bug No known bugs
 */
#include "user_patch/02_enemybgm.h"

#include "main.h"
#include "patch.h"
#include "tp/Z2SeqMgr.h"

namespace mod::user_patch
{
    namespace bgm::enemybgm
    {
        void ( *return_startBattleBgm )( libtp::tp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1 ) = nullptr;
    }     // namespace bgm::enemybgm
    void patchBattleMusic( rando::Randomizer* randomizer, bool set )
    {
        mod::console << "[2] EnemyBgmDisabled [" << ( set ? "x" : " " ) << "]\n";
        if ( set )
        {
            bgm::enemybgm::return_startBattleBgm = libtp::patch::hookFunction(
                libtp::tp::z2audiolib::z2seqmgr::startBattleBgm,
                []( libtp::tp::z2audiolib::z2seqmgr::Z2SeqMgr* Z2SequenceMgr, bool param_1 ) { return; } );
        }
        else
        {
            if ( bgm::enemybgm::return_startBattleBgm != nullptr )
            {
                libtp::patch::unhookFunction( bgm::enemybgm::return_startBattleBgm );
            }
        }
    }
}     // namespace mod::user_patch