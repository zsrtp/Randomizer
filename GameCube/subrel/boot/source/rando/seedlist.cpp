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
#include "cxx.h"

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
        // Allocate the memory to the back of the heap to avoid fragmentation
        Header* headerBuffer = new (-0x4) Header[SEED_MAX_ENTRIES];

        m_numSeeds = 0;

        // The memory card should already be mounted
        constexpr int32_t memCardChan = CARD_SLOT_A;
        for ( uint8_t i = 0; i < SEED_MAX_ENTRIES; i++ )
        {
            // Check next filename depending on i
            // rando-data0, rando-data1, ...
            filename[10] = static_cast<char>( '0' + i );

            Header header;

            if ( CARD_RESULT_READY == libtp::tools::ReadGCIMounted( memCardChan, filename, sizeof( header ), 0, &header, true ) )
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

    SeedList::~SeedList() { delete[] m_seedInfo; }

}     // namespace mod::rando