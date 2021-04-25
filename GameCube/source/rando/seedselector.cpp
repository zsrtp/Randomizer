/**	@file seedselector.cpp
 *  @brief Selection tool to select the desired data-gci
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/seedselector.h"

#include <gc/card.h>

#include <cinttypes>
#include <cstdio>
#include <cstring>

#include "gci/data.h"
#include "main.h"
#include "rando/seed.h"
#include "tools.h"
#include "tp/m_do_controller_pad.h"
namespace mod::rando
{
    SeedSelector::SeedSelector()
    {
        using namespace libtp;
        m_StatusText = new char[50];

        // Loop through possible seed-data-gcis until we don't read anything
        char filename[12] = "rando-data\0";
        uint8_t i = 0;
        do
        {
            // Check next filename depending on i
            // rando-data0, rando-data1, ...
            filename[10] = static_cast<char>( '0' + i );

            if ( CARD_RESULT_READY ==
                 tools::ReadGCI( 0, const_cast<char*>( filename ), sizeof( gci::data::Header ), 0, &m_Headers[i] ) )
            {
                i++;
            }
            else
            {
                break;
            }

            *mod::console << "SS: Checking for GCI: " << filename << "\n";

        } while ( i < SEED_MAX_ENTRIES );

        m_totalSeeds = i;

        // If we have seeds we initialise the default seed to be 1; 0 (default) if there is no seeds
        m_selectedSeed = ( i > 0 ? 1 : 0 );
    }

    SeedSelector::~SeedSelector() { delete[] m_Headers; }

    bool SeedSelector::HandleInputs( uint32_t buttonInput )
    {
        using namespace mod::gci;
        using namespace libtp::tp::m_do_controller_pad;
        using namespace libtp;

        bool status = false;

        if ( m_selectedSeed > 0 )
        {
            if ( ( buttonInput & PadInputs::Button_A ) == PadInputs::Button_A )
            {
                // Increase seed or reset to 1
                m_selectedSeed = m_selectedSeed == m_totalSeeds ? 1 : m_selectedSeed + 1;
                status = true;
            }

            if ( ( buttonInput & PadInputs::Button_B ) == PadInputs::Button_B )
            {
                // Decrease seed or reset to m_totalSeeds
                m_selectedSeed = m_selectedSeed == 1 ? m_totalSeeds : m_selectedSeed - 1;
                status = true;
            }

            // Read in the seed from our previously cached headers (constructor)
            uint64_t seed = m_Headers[( m_selectedSeed - 1 )].seed;
            snprintf( m_StatusText,
                      50,
                      "SS:: %" PRIu8 "/%" PRIu8 " - %04" PRIX32 "%04" PRIX32,
                      m_selectedSeed,
                      m_totalSeeds,
                      static_cast<uint32_t>( seed ),
                      static_cast<uint32_t>( seed >> 32 ) );
        }
        else
        {
            // Selected seed = 0; no seeds available
            strncpy( m_StatusText, "SS:: No seeds in Slot A or read error", 50 );
            status = true;
        }

        return status;
    }

}     // namespace mod::rando