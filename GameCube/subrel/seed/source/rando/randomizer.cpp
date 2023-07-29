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
#include "memory.h"

namespace mod::rando
{
    Randomizer::Randomizer(MinSeedInfo* minSeedInfo, uint8_t selectedSeed)
    {
        // getConsole() << "Rando loading...\n";
        loadSeed(minSeedInfo, selectedSeed);
    }

    Randomizer::~Randomizer(void)
    {
        // getConsole() << "Rando unloading...\n";

        // Clear Seed
        delete m_Seed;
    }

    void Randomizer::loadSeed(MinSeedInfo* minSeedInfo, uint8_t selectedSeed)
    {
        if (minSeedInfo->fileIndex == 0xFF)
        {
            getConsole() << "<Randomizer> Error: No such seed (0xFF)\n";
        }
        else
        {
            // getConsole() << "Seed: " << minSeedInfo->fileName << "\n";

            // Load the seed
            m_SeedInfo.minSeedInfo = minSeedInfo;
            m_CurrentSeed = selectedSeed;

            // Align to void*, as pointers use the largest variable type in the Seed class
            m_Seed = new (sizeof(void*)) Seed(CARD_SLOT_A, &m_SeedInfo);

            if (m_Seed->checkIfSeedLoaded())
            {
                // Update transformAnywhereEnabled now that a seed is loaded
                transformAnywhereEnabled = static_cast<bool>(m_Seed->m_Header->transformAnywhere);

                // Load checks for first load
                onStageLoad();
            }
            else
            {
                // The seed failed to load, so clear the seed
                delete m_Seed;
                libtp::memory::clearMemory(&m_SeedInfo, sizeof(m_SeedInfo));
                m_Seed = nullptr;
                m_CurrentSeed = 0xFF;
            }
        }
    }

    void Randomizer::changeSeed(MinSeedInfo* minSeedInfo, uint8_t newSeed)
    {
        getConsole() << "Seed unloading...\n";

        delete m_Seed;
        libtp::memory::clearMemory(&m_SeedInfo, sizeof(m_SeedInfo));
        m_Seed = nullptr;
        m_SeedInit = false;
        m_CurrentSeed = 0xFF;

        getConsole() << "Seed Loading...\n";
        loadSeed(minSeedInfo, newSeed);
    }
} // namespace mod::rando