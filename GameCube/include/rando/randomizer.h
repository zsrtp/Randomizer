/**	@file randomizer.h
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_RANDOMIZER_H
#define RANDO_RANDOMIZER_H

#include <cinttypes>

#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"
#include "tools.h"
#include "tp/dynamic_link.h"
#include "tp/dzx.h"

namespace mod::rando
{
    class Randomizer
    {
       public:
        Randomizer( SeedInfo* seedInfo );
        ~Randomizer();

        void initSave( void );

        void onStageLoad( void );

        void overrideREL();
        void overrideDZX( libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );

        int32_t getPoeItem( uint8_t flag );
        void overrideARC( void* filePtr, int32_t fileIndex );
        uint8_t getBossItem();
        uint8_t getHiddenSkillItem( uint16_t eventIndex );
        uint8_t overrideBugReward( uint8_t bugID );
        uint8_t getSkyCharacter();

        /**
         * @brief Returns the seed
         */
        inline uint64_t getSeed() { return m_SeedInfo->header.seed; }

       public:
        SeedInfo* m_SeedInfo = nullptr;     // SeedInfo associated with this randomizer instance
        bool m_SeedInit = false;            // True if seed-specific patches, flags, etc. have been applied to the save-file
        Seed* m_Seed;
    };
}     // namespace mod::rando
#endif