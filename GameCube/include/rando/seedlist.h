/**	@file seedselector.h
 *	@brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEEDLIST_H
#define RANDO_SEEDLIST_H

#include <cstdint>
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"

#ifdef PLATFORM_WII
#include "gc_wii/nand.h"
#else
#include "gc_wii/card.h"
#endif

#define SEED_MAX_ENTRIES 127

namespace mod::rando
{
    class SeedList
    {
       public:
        SeedList(void);
        ~SeedList(void);

#if defined DVD || defined PLATFORM_WII
        void getSeedFiles(const char* seedDirectory, MinSeedInfo* minSeedInfoBuffer);
#else
        void getSeedFiles(int32_t chan, MinSeedInfo* minSeedInfoBuffer);
#endif
        // SeedInfo FindSeed( uint64_t seed );

        MinSeedInfo* m_minSeedInfo = nullptr;
        uint8_t m_numSeeds;
        uint8_t m_selectedSeed;
    };
} // namespace mod::rando
#endif