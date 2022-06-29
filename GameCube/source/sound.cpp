#include "main.h"
#include "patch.h"
#include "rando/seed.h"
#include "Z2AudioLib/Z2SceneMgr.h"

namespace mod {
    KEEP_FUNC void handle_sceneChange( libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,uint8_t SeWave1,uint8_t SeWave2,uint8_t BgmWave1,uint8_t BgmWave2,uint8_t DemoWave,bool param_7 )
    {
        if (randomizer!=nullptr && randomizer->m_Seed!=nullptr && randomizer->m_Seed->m_BgmTable!=nullptr) {
            console << "Bgm Table Exists With " << randomizer->m_Seed->m_BgmTableEntries << " entries\n";
            uint8_t* tableRaw = randomizer->m_Seed->m_BgmTable;
            if (BGMid.id >= 0x1000000 && BGMid.id < 0x2000000) { //Make sure id is a bgm
                console << "Bgm " << (BGMid.id-0x1000000) << " playing\n";
                for (int i = 0; i < randomizer->m_Seed->m_BgmTableEntries; i++) {
                    console << tableRaw[i*4] << " " << tableRaw[(i*4)+1] << " " << tableRaw[(i*4)+2] << " " << tableRaw[(i*4)+3] << " ";
                    if (tableRaw[i*4]==(BGMid.id-0x1000000)) { //Original ids are the same, return the function with replaced values
                        console << "\nReplacement Found!\n";
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
}