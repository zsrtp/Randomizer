/**
 * @file 02_enemybgm.h
 * @author jdflyer
 * @brief Patches the game to allow for optional enemy BGM
 * 
 * @bug No known bugs
 */
#include "game_patch/02_enemybgm.h"
#include "main.h"
#include "patch.h"
#include "tp/Z2SeqMgr.h"

namespace mod::game_patch::bgm::enemybgm {
    void (*startBattleBgmTrampoline)(libtp::tp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, bool param_1) = nullptr;

    void patchBattleMusic( rando::Randomizer* randomizer, bool set) {
        mod::console << randomizer->m_SeedInfo->header.seed << "::EnemyBgmDisabled [" << ( set ? "x" : " " ) << "]\n";
        if (set) {
            startBattleBgmTrampoline = libtp::patch::hookFunction(libtp::tp::z2audiolib::z2seqmgr::startBattleBgm,[](libtp::tp::z2audiolib::z2seqmgr::Z2SeqMgr* Z2SequenceMgr, bool param_1){
                return;
            });
        } else{
            if (startBattleBgmTrampoline != nullptr) {
                libtp::patch::unhookFunction(startBattleBgmTrampoline);
            }
        }
    }
}   //namespace mod::game_patch::bgm::enemybgm