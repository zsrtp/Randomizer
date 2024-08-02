/**	@file seed.h
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEED_H
#define RANDO_SEED_H

#include <cstdint>

#ifdef DVD
#include "gc_wii/dvd.h"
#else
#include "gc_wii/card.h"
#endif

#include "rando/data.h"
#include "tools.h"
#include "data.h"

namespace mod::rando
{
    class Seed
    {
        // Member vars
       public:
        int32_t m_CARDResult; // Most recent status from the CARDApi functions
        Header* m_Header = nullptr;

        DZXCheck* m_DZXChecks = nullptr;             // DZX replacement checks for current stage
        RELCheck* m_RELChecks = nullptr;             // REL Modifications for current stage
        PoeCheck* m_PoeChecks = nullptr;             // Poe Checks for current stage
        ARCReplacement* m_ArcReplacements = nullptr; // Checks for the currently loaded .arc file
        BossCheck* m_BossChecks = nullptr;
        HiddenSkillCheck* m_HiddenSkillChecks = nullptr;
        BugReward* m_BugRewardChecks = nullptr;
        SkyCharacter* m_SkyBookChecks = nullptr;
        ObjectArchiveReplacement* m_ObjectArcReplacements = nullptr;
        ShuffledEntrance* m_ShuffledEntrances = nullptr;
        EventItem* m_EventChecks = nullptr;

        BGMReplacement* m_BgmTable = nullptr;     // Bgm replacement data
        BGMReplacement* m_FanfareTable = nullptr; // Fanfare replacement data

        CLR0Header* m_CLR0 = nullptr;
        RawRGBTable* m_RawRGBTable = nullptr;
        BMDEntry* m_BmdEntries = nullptr;

        uint16_t m_numLoadedDZXChecks = 0;       // Number of currently loaded DZXCheck
        uint16_t m_numLoadedRELChecks = 0;       // Number of currently loaded RELCheck
        uint16_t m_numLoadedPOEChecks = 0;       // Number of currently loaded POEChecks
        uint16_t m_numLoadedArcReplacements = 0; // Number of currently loaded ArcChecks
        uint16_t m_numHiddenSkillChecks = 0;
        uint16_t m_numBugRewardChecks = 0;
        uint16_t m_numSkyBookChecks = 0;
        uint16_t m_numLoadedEventChecks = 0;
        uint16_t m_numLoadedObjectArcReplacements = 0;
        uint16_t m_numShuffledEntrances = 0;

        uint16_t m_PatchesApplied = 0;
        uint16_t m_EventFlagsModified = 0;
        uint16_t m_AreaFlagsModified = 0;

        uint8_t m_StageIDX = 0xFF; // StageIDX from last Checkload

        uint8_t m_BgmTableEntries = 0;
        uint8_t m_FanfareTableEntries = 0;

        // Member functions
       public:
        // Main
        bool checkIfSeedLoaded()
        {
#ifdef DVD
            bool result = m_CARDResult == DVD_STATE_END;
#else
            bool result = m_CARDResult == CARD_RESULT_READY;
#endif
            if (result)
            {
                return m_GCIData;
            }
            return result;
        }

        /**
         *  @brief Applies patches, event & region flags according to this seed to the current savefile
         *
         *  @return True if successful
         */
        bool InitSeed(void);

        /**
         *  @brief Load check data for a given stage & stores them in a temp. (smaller) buffer
         *
         *  @return True if checks have been updated (new stage) otherwise we are still on the same stage
         */
        bool LoadChecks(const char* stage);
        void LoadARCChecks(uint8_t stageIDX, FileDirectory fileDirectory, int32_t roomNo);

        void LoadObjectARCChecks();

        /**
         *  @brief Manages game_patches from the seed that must occur every time a file is loaded
         *
         *  @param set If true it will set the patches, otherwise restore the original
         */
        void applyVolatilePatches(bool set);

        // Subrel
        /**
         *  @brief Class to dynamically load required data from a given seed
         *
         *  @param seedInfo Pointer to the seedinfo that we intend to load
         */
        Seed(int32_t chan, SeedInfo* seedInfo);

        /**
         *  @brief Deletes all allocated members and unpatches all the previously applied patches
         */
        ~Seed();

        /**
         *  @brief Manages one-time game_patches from the seed
         *
         *  @param set If true it will set the patches, otherwise restore the original
         */
        void applyOneTimePatches(bool set);

        void loadShopModels();
        void loadShuffledEntrances();

       private:
        uint8_t* m_GCIData = nullptr; // GCI Data including header
        int32_t m_CardSlot = 0;       // Selected Card slot
        uint8_t m_fileIndex = 0xFF;   // GCI Fileindex

        void clearChecks(void);
        void loadBgmData(uint8_t* data);

        // Main
        void applyEventFlags(void);
        void applyRegionFlags(void);
        void giveStartingItems(void);

        void LoadDZX(uint8_t stageIDX);
        void LoadREL(uint8_t stageIDX);
        void LoadPOE(uint8_t stageIDX);
        void LoadBOSS(uint8_t stageIDX);
        void LoadSkyCharacter(uint8_t stageIDX);
        void LoadHiddenSkill();
        void LoadBugReward();
        void LoadEventChecks(uint8_t stageIDX);
        void loadCustomText(uint8_t* data);
    };
} // namespace mod::rando
#endif