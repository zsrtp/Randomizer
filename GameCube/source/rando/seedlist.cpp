/**	@file seedselector.cpp
 *  @brief Selection tool to select the desired data-gci
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/seedlist.h"

#include <gc/card.h>

#include <cinttypes>
#include <cstdio>
#include <cstring>

#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "tools.h"
#include "tp/JKRExpHeap.h"
#include "tp/m_do_controller_pad.h"
#include "tp/m_do_ext.h"

namespace mod::rando
{
    SeedList::SeedList()
    {
        using namespace libtp;

        // Loop through possible seed-data-gcis until we don't read anything
        char filename[12] = "rando-data\0";

        // Bitwise representation of the seeds available
        uint16_t seedIDX = 0;
        m_numSeeds = 0;

        for ( uint8_t i = 0; i < SEED_MAX_ENTRIES; i++ )
        {
            // Check next filename depending on i
            // rando-data0, rando-data1, ...
            filename[10] = static_cast<char>( '0' + i );

            Seed tempSeed = Seed( CARD_SLOT_A, filename );

            if ( CARD_RESULT_READY == tempSeed.m_CARDResult )
            {
                uint16_t version = static_cast<uint16_t>( _VERSION_MAJOR << 8 | _VERSION_MINOR );
                if ( tempSeed.m_Header->minVersion >= version )
                {
                    if ( tempSeed.m_Header->maxVersion <= version )
                    {
                        seedIDX = seedIDX | ( 1 << i );
                        m_numSeeds++;
                    }
                }
            }
        }

        m_seedInfo = new SeedInfo[m_numSeeds];

        uint8_t j = 0;     // seedInfo index

        // Loop through all possible seeds and load them into our seedInfo
        for ( uint8_t i = 0; i < SEED_MAX_ENTRIES; i++ )
        {
            if ( ( ( seedIDX >> i ) & 1 ) == 1 )
            {
                // Index exists, load seed
                filename[10] = static_cast<char>( '0' + i );

                Seed tempSeed = Seed( CARD_SLOT_A, filename );

                m_seedInfo[j].seed = tempSeed.m_Header->seed;
                m_seedInfo[j].fileIndex = i;
                j++;
            }
        }
    }

    SeedInfo SeedList::FindSeed( uint64_t seed )
    {
        for ( uint8_t i = 0; i < SEED_MAX_ENTRIES && i < m_numSeeds; i++ )
        {
            if ( m_seedInfo[i].seed == seed )
            {
                return static_cast<SeedInfo>( m_seedInfo[i] );
            }
        }

        // No seed found; Return one with index FF as error indicator (max is 9)
        return { 0x00, 0xFF };
    }

    SeedList::~SeedList() { delete[] m_seedInfo; }

}     // namespace mod::rando