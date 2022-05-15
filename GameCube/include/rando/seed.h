/**	@file seed.h
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEED_H
#define RANDO_SEED_H

#include <cstdint>

#include "rando/data.h"
#include "tools.h"

namespace mod::rando
{
    class Seed
    {
        // Member vars
       public:
        int32_t m_CARDResult;     // Most recent status from the CARDApi functions

        uint32_t m_PatchesApplied = 0;
        uint32_t m_EventFlagsModified = 0;
        uint32_t m_AreaFlagsModified = 0;

        Header* m_Header = nullptr;
        uint32_t m_StageIDX = 0xFF;     // StageIDX from last Checkload

        dzxCheck* m_DZXChecks = nullptr;       // DZX replacement checks for current stage
        uint32_t m_numLoadedDZXChecks = 0;     // Number of currently loaded DZXCheck

        RELCheck* m_RELChecks = nullptr;       // REL Modifications for current stage
        uint32_t m_numLoadedRELChecks = 0;     // Number of currently loaded RELCheck

        POECheck* m_POEChecks = nullptr;       // POE Checks for current stage
        uint32_t m_numLoadedPOEChecks = 0;     // Number of currently loaded POEChecks

        ARCReplacement* m_ArcReplacements = nullptr;     // Checks for the currently loaded .arc file
        uint32_t m_numLoadedArcReplacements = 0;         // Number of currently loaded ArcChecks

        BOSSCheck* m_BossChecks = nullptr;
        uint32_t m_numLoadedBossChecks = 0;

        HiddenSkillCheck* m_HiddenSkillChecks = nullptr;
        uint32_t m_numHiddenSkillChecks = 0;

        BugReward* m_BugRewardChecks = nullptr;
        uint32_t m_numBugRewardChecks = 0;

        SkyCharacter* m_SkyBookChecks = nullptr;
        uint32_t m_numSkyBookChecks = 0;

        shopCheck* m_ShopChecks = nullptr;
        uint32_t m_numShopChecks = 0;

        ObjectArchiveReplacement* m_ObjectArcReplacements = nullptr;
        uint32_t m_numLoadedObjectArcReplacements = 0;

        uint8_t* m_MsgTableInfo = nullptr; // Custom message string data
        uint32_t m_TotalMsgEntries = 0; // Number of currently loaded custom string

        // Member functions
       public:
        /**
         *  @brief Class to dynamically load required data from a given seed
         *
         *  @param seedInfo Pointer to the seedinfo that we intend to load
         */
        Seed( int32_t chan, SeedInfo* seedInfo );

        /**
         *  @brief Deletes all allocated members and unpatches all the previously applied patches
         */
        ~Seed();

        /**
         *  @brief Applies patches, event & region flags according to this seed to the current savefile
         *
         *  @return True if successful
         */
        bool InitSeed( void );

        /**
         *  @brief Load check data for a given stage & stores them in a temp. (smaller) buffer
         *
         *  @return True if checks have been updated (new stage) otherwise we are still on the same stage
         */
        bool LoadChecks( const char* stage );
        void LoadARCChecks( uint8_t stageIDX, FileDirectory fileDirectory, int roomNo );

        void LoadObjectARCChecks();

        void loadShopModels();

        void applyPatches( bool set );

       private:
        uint8_t* m_GCIData = nullptr;     // GCI Data including header
        uint8_t m_fileIndex = 0xFF;       // GCI Fileindex
        int32_t m_CardSlot = 0;           // Selected Card slot
        void ClearChecks( void );

        /**
         *  @brief Manages game_patches from the seed
         *
         *  @param set If true it will set the patches, otherwise restore the original
         */

        void applyEventFlags( void );
        void applyRegionFlags( void );
        void giveStartingItems( void );

        void LoadDZX( uint8_t stageIDX );
        void LoadREL( uint8_t stageIDX );
        void LoadPOE( uint8_t stageIDX );
        void LoadBOSS( uint8_t stageIDX );
        void LoadSkyCharacter( uint8_t stageIDX );
        void LoadHiddenSkill();
        void LoadBugReward();
        bool loadCustomText( uint8_t* data );
    };
}     // namespace mod::rando
#endif