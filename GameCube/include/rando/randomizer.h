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

        void overrideREL( libtp::tp::dynamic_link::DynamicModuleControl* dmc );
        void overrideDZX( libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );

        /**
         * @brief Gets a random number based off the seed and shifts the seed
         *
         * @param max The maximum number that the function can return
         */
        inline uint32_t getRandom( uint32_t max ) { return libtp::tools::getRandom( &m_SeedInfo->header.seed, max ); }

       public:
        SeedInfo* m_SeedInfo = nullptr;     // SeedInfo associated with this randomizer instance
        bool m_SeedInit = false;            // True if seed-specific patches, flags, etc. have been applied to the save-file

       private:
        Seed* m_Seed;
    };
}     // namespace mod::rando
#endif