/**	@file seedselector.h
 *  @brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEEDLIST_H
#define RANDO_SEEDLIST_H

#include <cstdint>

#ifdef PLATFORM_WII
#include "gc_wii/nand.h"
#else
#include "gc_wii/card.h"
#endif
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"

#define SEED_MAX_ENTRIES CARD_MAX_FILE


namespace mod::rando
{
    class SeedList
    {
       public:
        SeedList(void);
        ~SeedList(void);

#ifdef DVD
        void getSeedFiles(const char* seedDirectory, MinSeedInfo* minSeedInfoBuffer);
#elif defined PLATFORM_WII
        void getSeedFiles(MinSeedInfo* minSeedInfoBuffer);
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