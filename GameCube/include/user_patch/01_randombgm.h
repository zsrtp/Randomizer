/**
 * @file 01_randombgm.h
 * @author jdflyer
 * @brief Handles randomizing the game's BGM
 *
 * @bug No known bugs
 */
#ifndef RANDO_RANDOM_BGM_PATCH_H
#define RANDO_RANDOM_BGM_PATCH_H

#include "rando/randomizer.h"
#include "Z2AudioLib/Z2SceneMgr.h"

namespace mod::user_patch
{
    namespace bgm::bgmrando
    {
        /**
         * @brief sceneChange function hook handler
         */
        extern void ( *return_sceneChange )( libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,
                                             libtp::z2audiolib::z2scenemgr::JAISoundID id,
                                             uint8_t SeWave1,
                                             uint8_t SeWave2,
                                             uint8_t BgmWave1,
                                             uint8_t BgmWave2,
                                             uint8_t DemoWave,
                                             bool param_7 );
    }     // namespace bgm::bgmrando

    /**
     * @brief Enables Random Background Music
     */
    void enableRandomBgm( rando::Randomizer* randomizer, bool set );

    /**
     * @brief Handles Random Background Music
     */
    void handleSceneChange( libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,
                            libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,
                            uint8_t SeWave1,
                            uint8_t SeWave2,
                            uint8_t BgmWave1,
                            uint8_t BgmWave2,
                            uint8_t DemoWave,
                            bool param_7 );

}     // namespace mod::user_patch

#endif