/**	@file seedselector.cpp
 *  @brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/seedlist.h"

namespace mod::rando
{
    // Needs work and is currently unused
    /*
    SeedInfo SeedList::FindSeed( uint64_t seed )
    {
        for ( uint8_t i = 0; i < SEED_MAX_ENTRIES && i < m_numSeeds; i++ )
        {
            if ( m_seedInfo[i].header.seed == seed )
            {
                return static_cast<SeedInfo>( m_seedInfo[i] );
            }
        }

        // No seed found; Return one with index FF as error indicator (max is 9)
        return { 0x00, 0xFF };
    }
    */

    SeedList::~SeedList()
    {
        delete[] m_minSeedInfo;
    }

} // namespace mod::rando