/**	@file randomizer.h
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_RANDOMIZER_H
#define RANDO_RANDOMIZER_H

#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"
#include "tools.h"
#include "tp/dynamic_link.h"
#include "tp/dzx.h"
#include "tp/d_resource.h"

namespace mod::rando
{
    class Randomizer
    {
       public:
        // Main/Subrel
        ~Randomizer();
        void onStageLoad( void );

        // Main
        void initSave( void );
        void overrideREL();
        void overrideDZX( libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );
        int32_t getPoeItem( uint8_t flag );
        uint8_t getSkyCharacter();
        uint8_t getBossItem( int32_t originalItem );
        void overrideARC( uint32_t fileAddr, FileDirectory fileDirectory, int roomNo );
        void overrideObjectARC( libtp::tp::d_resource::dRes_info_c* resourcePtr, const char* fileName );
        void overrideEventARC();
        uint8_t overrideBugReward( uint8_t bugID );
        uint8_t getHiddenSkillItem( uint16_t eventIndex );

        // Subrel
        Randomizer( SeedInfo* seedInfo, uint8_t selectedSeed );
        void loadSeed( SeedInfo* seedInfo, uint8_t selectedSeed );
        void changeSeed( SeedInfo* seedInfo, uint8_t newSeed );

        /**
         * @brief Returns the seed
         */
        inline uint64_t getSeed() { return m_SeedInfo->header.seed; }

       public:
        SeedInfo* m_SeedInfo = nullptr;     // SeedInfo associated with this randomizer instance
        Seed* m_Seed;
        bool m_Enabled = true;            // True if the randomizer is currently enabled
        bool m_SeedInit = false;          // True if seed-specific patches, flags, etc. have been applied to the save-file
        uint8_t m_CurrentSeed = 0xFF;     // The seed that is currently loaded
    };
}     // namespace mod::rando
#endif