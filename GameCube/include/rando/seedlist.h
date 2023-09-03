/**	@file seedselector.h
 *  @brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEEDLIST_H
#define RANDO_SEEDLIST_H

#include <cstdint>

#include "gc_wii/card.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"

#define SEED_MAX_ENTRIES CARD_MAX_FILE

// SeedData version (Major.Minor) which this version of the Randomizer
// supports.
#define SUPPORTED_SEED_DATA_VER_MAJOR 1
#define SUPPORTED_SEED_DATA_VER_MINOR 0

// Defines to help with version comparisions, as otherwise we get: "error:
// comparison is always true due to limited range of data type
// [-Werror=type-limits]" when the macro values are 0.
#if SUPPORTED_SEED_DATA_VER_MAJOR == 0
#define CHECK_SUPPORTED_SEED_DATA_VER_MAJOR(version) 1
#else
#define CHECK_SUPPORTED_SEED_DATA_VER_MAJOR(version) static_cast<uint16_t>(version) == SUPPORTED_SEED_DATA_VER_MAJOR
#endif

#if SUPPORTED_SEED_DATA_VER_MINOR == 0
#define CHECK_SUPPORTED_SEED_DATA_VER_MINOR(version) 1
#else
#define CHECK_SUPPORTED_SEED_DATA_VER_MINOR(version) static_cast<uint16_t>(version) == SUPPORTED_SEED_DATA_VER_MINOR
#endif

namespace mod::rando
{
    class SeedList
    {
       public:
        SeedList(void);
        ~SeedList(void);

#ifdef DVD
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