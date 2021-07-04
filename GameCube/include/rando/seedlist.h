/**	@file seedselector.h
 *  @brief Selection tool to select the desired data-gci
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEEDLIST_H
#define RANDO_SEEDLIST_H
#include <cinttypes>

#include "rando/seed.h"
#include "rando/seedlist.h"

#define SEED_MAX_ENTRIES 10

namespace mod::rando
{
    // Seed with index
    struct SeedInfo
    {
        uint64_t seed;
        uint8_t fileIndex;     // (0-9) rando-dataX
    };

    class SeedList
    {
       public:
        SeedList( void );
        ~SeedList( void );

        SeedInfo FindSeed( uint64_t seed );

        SeedInfo operator[]( int n )
        {
            // Returning with mod guarantees for read access within numSeeds
            return static_cast<SeedInfo>( m_seedInfo[n % m_numSeeds] );
        }
        int m_numSeeds;
        int m_selectedSeed;

       private:
        SeedInfo* m_seedInfo = nullptr;
    };
}     // namespace mod::rando
#endif