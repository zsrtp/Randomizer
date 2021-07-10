/** 
 * @file 01_bgm.h
 * @author jdflyer
 * @brief Handles randomizing the game's BGM
 * 
 * @bug No known bugs
 */
#ifndef RANDO_RANDOM_BGM_PATCH_H
#define RANDO_RANDOM_BGM_PATCH_H
#include "game_patch/game_patch.h"

namespace mod::game_patch::bgm::bgmrando {
    /**
     * @brief Enables Random Background Music
    */
    void initRandomBgm( rando::Randomizer* randomizer, bool set);

}   //namespace mod::game_patch::bgm::bgmrando

#endif