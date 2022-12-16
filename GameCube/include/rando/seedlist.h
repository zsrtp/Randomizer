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

// Earliest SeedData version (Major.Minor) which this version of the Randomizer
// supports.
#define MIN_SUPPORTED_SEED_DATA_VER_MAJOR 1
#define MIN_SUPPORTED_SEED_DATA_VER_MINOR 0

// Final SeedData version (Major.Minor) for which this version of the Randomizer
// is guaranteed to support 100% of the features. This will change more often
// than the minSupportedVersion. Generally speaking, this should be set to the
// version of the SeedData that the website will output when this version of the
// Randomizer is released. This maxFullySupportedVersion will be used in a
// future update (pre-1.0 release) to determine if a SeedData can be played even
// if some of its non-critical features are not supported.
#define MAX_FULLY_SUPPORTED_SEED_DATA_VER_MAJOR 1
#define MAX_FULLY_SUPPORTED_SEED_DATA_VER_MINOR 1

// Defines to help with version comparisions, as otherwise we get: "error:
// comparison is always true due to limited range of data type
// [-Werror=type-limits]" when the macro values are 0.
#if MIN_SUPPORTED_SEED_DATA_VER_MAJOR == 0
#define CHECK_MIN_SUPPORTED_SEED_DATA_VER_MAJOR( version ) 1
#else
#define CHECK_MIN_SUPPORTED_SEED_DATA_VER_MAJOR( version ) static_cast<uint16_t>( version ) >= MIN_SUPPORTED_SEED_DATA_VER_MAJOR
#endif

#if MIN_SUPPORTED_SEED_DATA_VER_MINOR == 0
#define CHECK_MIN_SUPPORTED_SEED_DATA_VER_MINOR( version ) 1
#else
#define CHECK_MIN_SUPPORTED_SEED_DATA_VER_MINOR( version ) static_cast<uint16_t>( version ) >= MIN_SUPPORTED_SEED_DATA_VER_MINOR
#endif

#if MAX_FULLY_SUPPORTED_SEED_DATA_VER_MAJOR == 0
#define CHECK_MAX_FULLY_SUPPORTED_SEED_DATA_VER_MAJOR( version ) 1
#else
#define CHECK_MAX_FULLY_SUPPORTED_SEED_DATA_VER_MAJOR( version ) \
    static_cast<uint16_t>( version ) <= MAX_FULLY_SUPPORTED_SEED_DATA_VER_MAJOR
#endif

#if MAX_FULLY_SUPPORTED_SEED_DATA_VER_MINOR == 0
#define CHECK_MAX_FULLY_SUPPORTED_SEED_DATA_VER_MINOR( version ) 1
#else
#define CHECK_MAX_FULLY_SUPPORTED_SEED_DATA_VER_MINOR( version ) \
    static_cast<uint16_t>( version ) <= MAX_FULLY_SUPPORTED_SEED_DATA_VER_MINOR
#endif

namespace mod::rando
{
    class SeedList
    {
       public:
        SeedList( void );
        ~SeedList( void );

#ifdef DVD
        void GetSeedFiles( const char* seedDirectory, MinSeedInfo* minSeedInfoBuffer );
#else
        void GetSeedFiles( int32_t chan, MinSeedInfo* minSeedInfoBuffer );
#endif
        // SeedInfo FindSeed( uint64_t seed );

        uint8_t m_numSeeds;
        uint8_t m_selectedSeed;

        MinSeedInfo* m_minSeedInfo = nullptr;
    };
}     // namespace mod::rando
#endif