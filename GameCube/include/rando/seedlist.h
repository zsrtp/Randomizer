/**	@file seedselector.h
 *  @brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEEDLIST_H
#define RANDO_SEEDLIST_H

#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"

#define SEED_MAX_ENTRIES 10
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
#define MAX_FULLY_SUPPORTED_SEED_DATA_VER_MINOR 0

namespace mod::rando
{
    class SeedList
    {
       public:
        SeedList( void );
        ~SeedList( void );

        // SeedInfo FindSeed( uint64_t seed );

        uint8_t m_numSeeds;
        uint8_t m_selectedSeed;

        SeedInfo* m_seedInfo = nullptr;
    };
}     // namespace mod::rando
#endif