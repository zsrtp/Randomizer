#include "main.h"
#include "patch.h"
#include "rando/seed.h"
#include "Z2AudioLib/Z2SceneMgr.h"
#include "Z2AudioLib/Z2SoundMgr.h"

namespace mod
{
    KEEP_FUNC void handle_sceneChange(libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,
                                      libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,
                                      uint8_t SeWave1,
                                      uint8_t SeWave2,
                                      uint8_t BgmWave1,
                                      uint8_t BgmWave2,
                                      uint8_t DemoWave,
                                      bool param_7)
    {
        rando::Seed* seed;
        const rando::bgmReplacement* bgmTable;

        if ((seed = getCurrentSeed(randomizer), !seed) || (bgmTable = seed->m_BgmTable, !bgmTable))
        {
            // Call the original function
            return return_sceneChange(sceneMgr, BGMid, SeWave1, SeWave2, BgmWave1, BgmWave2, DemoWave, param_7);
        }

        // Make sure id is a bgm
        const uint32_t bgmId = BGMid.id;
        if ((bgmId < 0x1000000) || (bgmId >= 0x2000000))
        {
            // Call the original function
            return return_sceneChange(sceneMgr, BGMid, SeWave1, SeWave2, BgmWave1, BgmWave2, DemoWave, param_7);
        }

        const uint32_t entries = seed->m_BgmTableEntries;
        const uint32_t bgmIdCheck = bgmId - 0x1000000;

        for (uint32_t i = 0; i < entries; i++)
        {
            const rando::bgmReplacement* tempBgmTable = &bgmTable[i];
            if (tempBgmTable->originalBgmTrack == bgmIdCheck)
            {
                // Original ids are the same, return the function with replaced values
                libtp::z2audiolib::z2scenemgr::JAISoundID replacementId;
                replacementId.id = tempBgmTable->replacementBgmTrack + 0x1000000;

                return return_sceneChange(sceneMgr,
                                          replacementId,
                                          SeWave1,
                                          SeWave2,
                                          tempBgmTable->replacementBgmWave,
                                          BgmWave2,
                                          DemoWave,
                                          param_7);
            }
        }

        // Call the original function
        return_sceneChange(sceneMgr, BGMid, SeWave1, SeWave2, BgmWave1, BgmWave2, DemoWave, param_7);
    }

    KEEP_FUNC void handle_startSound(void* soundMgr,
                                     libtp::z2audiolib::z2scenemgr::JAISoundID soundId,
                                     void* soundHandle,
                                     void* pos)
    {
        rando::Seed* seed;
        const rando::bgmReplacement* fanfareTable;

        if ((seed = getCurrentSeed(randomizer), !seed) || (fanfareTable = seed->m_FanfareTable, !fanfareTable))
        {
            // Call the original function
            return return_startSound(soundMgr, soundId, soundHandle, pos);
        }

        const uint32_t id = soundId.id;
        if ((id < 0x1000000) || (id >= 0x2000000))
        {
            // Call the original function
            return return_startSound(soundMgr, soundId, soundHandle, pos);
        }

        // Sound playing is part of the bgm table
        const uint32_t entries = seed->m_FanfareTableEntries;
        const uint32_t idCheck = id - 0x1000000;

        for (uint32_t i = 0; i < entries; i++)
        {
            const rando::bgmReplacement* tempfanfareTable = &fanfareTable[i];
            if (tempfanfareTable->originalBgmTrack == idCheck)
            {
                // Both have the same ID, so play the replacement
                libtp::z2audiolib::z2scenemgr::JAISoundID replacementId;
                replacementId.id = tempfanfareTable->replacementBgmTrack + 0x1000000;

                return return_startSound(soundMgr, replacementId, soundHandle, pos);
            }
        }

        // Call the original function
        return_startSound(soundMgr, soundId, soundHandle, pos);
    }
} // namespace mod