/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/randomizer.h"
#include "cxx.h"
#include "gc_wii/card.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"

namespace mod::rando
{
    Randomizer::Randomizer( SeedInfo* seedInfo, uint8_t selectedSeed )
    {
        mod::console << "Rando loading...\n";
        loadSeed( seedInfo, selectedSeed );
    }

    Randomizer::~Randomizer( void )
    {
        mod::console << "Rando unloading...\n";

        // Clear Seed
        delete m_Seed;
    }

    void Randomizer::loadSeed( SeedInfo* seedInfo, uint8_t selectedSeed )
    {
        if ( seedInfo->fileIndex == 0xFF )
        {
            mod::console << "<Randomizer> Error: No such seed (0xFF)\n";
        }
        else
        {
            mod::console << "Seed: " << seedInfo->header.seed << "\n";
            // Load the seed
            m_SeedInfo = seedInfo;
            m_CurrentSeed = selectedSeed;

            // Align to void*, as pointers use the largest variable type in the Seed class
            m_Seed = new ( sizeof( void* ) ) Seed( CARD_SLOT_A, seedInfo );

            if ( m_Seed->checkIfSeedLoaded() )
            {
                // Load checks for first load
                onStageLoad();
            }
            else
            {
                // The seed failed to load, so clear the seed
                delete m_Seed;
                m_SeedInfo = nullptr;
                m_Seed = nullptr;
                m_CurrentSeed = 0xFF;
            }
        }
    }

    void Randomizer::changeSeed( SeedInfo* seedInfo, uint8_t newSeed )
    {
        mod::console << "Seed unloading...\n";
        delete m_Seed;
        m_SeedInfo = nullptr;
        m_Seed = nullptr;
        m_SeedInit = false;
        m_CurrentSeed = 0xFF;

        mod::console << "Seed Loading...\n";
        loadSeed( seedInfo, newSeed );
    }
}     // namespace mod::rando