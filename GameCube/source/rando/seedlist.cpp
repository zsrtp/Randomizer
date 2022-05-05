/**	@file seedselector.cpp
 *  @brief Selection tool to select the desired data-gci
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/seedlist.h"

#include <cinttypes>
#include <cstdio>
#include <cstring>

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
    SeedList::SeedList()
    {
        using namespace libtp;

        // Loop through possible seed-data-gcis until we don't read anything
        char filename[12] = "rando-data\0";

        // Bitwise representation of the seeds available
        uint16_t seedIDX = 0;

        // Store header data so we don't have to open the files again later
        Header* headerBuffer = new Header[SEED_MAX_ENTRIES];

        m_numSeeds = 0;

        // Only mount/unmount the memory card once
        constexpr int32_t memCardChan = CARD_SLOT_A;
        if ( CARD_RESULT_READY == tools::mountMemoryCard( memCardChan ) )
        {
            for ( uint8_t i = 0; i < SEED_MAX_ENTRIES; i++ )
            {
                // Check next filename depending on i
                // rando-data0, rando-data1, ...
                filename[10] = static_cast<char>( '0' + i );

                Header header;

                if ( CARD_RESULT_READY ==
                     libtp::tools::ReadGCIMounted( memCardChan, filename, sizeof( header ), 0, &header, true ) )
                {
                    uint16_t minVersion = header.minVersion;
                    uint16_t maxVersion = header.maxVersion;

                    uint16_t version = static_cast<uint16_t>( _VERSION_MAJOR << 8 | _VERSION_MINOR );
                    if ( minVersion <= version )
                    {
                        if ( maxVersion >= version )
                        {
                            seedIDX = seedIDX | ( 1 << i );
                            memcpy( &headerBuffer[i], &header, sizeof( Header ) );

                            m_numSeeds++;
                        }
                    }
                }
            }
            libtp::gc_wii::card::CARDUnmount( memCardChan );
        }

        if ( m_numSeeds > 0 )
        {
            m_seedInfo = new SeedInfo[m_numSeeds];

            uint8_t j = 0;     // seedInfo index

            // Loop through all possible seeds and load them into our seedInfo
            for ( uint8_t i = 0; i < SEED_MAX_ENTRIES; i++ )
            {
                if ( ( ( seedIDX >> i ) & 1 ) == 1 )
                {
                    memcpy( &m_seedInfo[j].header, &headerBuffer[i], sizeof( Header ) );
                    m_seedInfo[j].fileIndex = i;
                    j++;
                }
            }
        }

        mod::console << m_numSeeds << " seed(s) available.\n";

        delete[] headerBuffer;
    }

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