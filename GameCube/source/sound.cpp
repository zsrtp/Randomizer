#include "main.h"
#include "patch.h"
#include "rando/seed.h"
#include "Z2AudioLib/Z2SceneMgr.h"
#include "Z2AudioLib/Z2SoundMgr.h"

namespace mod {
    KEEP_FUNC void handle_sceneChange( libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,uint8_t SeWave1,uint8_t SeWave2,uint8_t BgmWave1,uint8_t BgmWave2,uint8_t DemoWave,bool param_7 )
    {
        if (randomizer!=nullptr && randomizer->m_Seed!=nullptr && randomizer->m_Seed->m_BgmTable!=nullptr) {
            uint8_t* tableRaw = randomizer->m_Seed->m_BgmTable;
            if (BGMid.id >= 0x1000000 && BGMid.id < 0x2000000) { //Make sure id is a bgm
                for (int i = 0; i < randomizer->m_Seed->m_BgmTableEntries; i++) {
                    if (tableRaw[i*4]==(BGMid.id-0x1000000)) { //Original ids are the same, return the function with replaced values
                        libtp::z2audiolib::z2scenemgr::JAISoundID replacementId;
                        replacementId.id = tableRaw[(i*4)+1]+0x1000000;
                        return_sceneChange(sceneMgr,replacementId,SeWave1,SeWave2,tableRaw[(i*4)+2],BgmWave2,DemoWave,param_7);
                        return;
                    }
                }
            }
        }
        return_sceneChange(sceneMgr,BGMid,SeWave1,SeWave2,BgmWave1,BgmWave2,DemoWave,param_7);
    }

    KEEP_FUNC void handle_startSound( void* soundMgr, libtp::z2audiolib::z2scenemgr::JAISoundID soundId, void* soundHandle, void* pos) {
        if (randomizer!=nullptr && randomizer->m_Seed!=nullptr && randomizer->m_Seed->m_FanfareTable != nullptr) {
            uint32_t id = soundId.id;
            if (id >= 0x1000000 && id < 0x2000000) { //Sound playing is part of the bgm table       
                uint8_t* tableRaw = randomizer->m_Seed->m_FanfareTable;
                for (int i = 0; i<randomizer->m_Seed->m_FanfareTableEntries; i++) {
                    if (tableRaw[i*4]==id-0x1000000) { //Both have the same ID, so play the replacement
                        libtp::z2audiolib::z2scenemgr::JAISoundID replacementId;
                        replacementId.id = tableRaw[(i*4)+1]+0x1000000;
                        return_startSound(soundMgr,replacementId,soundHandle,pos);
                        return;
                    }
                }
            }
        }
        return_startSound(soundMgr,soundId,soundHandle,pos);
    }
}