/**	@file seedselector.cpp
 *  @brief Selection tool to select the desired data-gci
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/seedlist.h"

#include <cstring>
#include <cstdio>
#include <cinttypes>

#include "gc_wii/card.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "tools.h"
#include "tp/JKRExpHeap.h"
#include "tp/m_do_controller_pad.h"
#include "tp/m_do_ext.h"

namespace mod::rando
{
    // Currently unused, so will leave in for now
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

    SeedList::~SeedList() { delete[] m_seedInfo; }

}     // namespace mod::rando