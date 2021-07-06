/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/randomizer.h"

#include "gc/card.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"

namespace mod::rando
{
    Randomizer::Randomizer( SeedInfo* seedInfo )
    {
        mod::console << "Rando loading...\n";

        if ( seedInfo->fileIndex == 0xFF )
        {
            mod::console << "<Randomizer> Error: No such seed (0xFF)\n";
        }
        else
        {
            mod::console << "Seed: " << seedInfo->header.seed << "\n";

            m_Seed = new Seed( CARD_SLOT_A, seedInfo );
        }
    }
    Randomizer::~Randomizer()
    {
        mod::console << "Rando unloading...\n";

        // Clear Seed
        delete m_Seed;
    }
}     // namespace mod::rando