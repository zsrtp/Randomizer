/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include <cstring>

#include "rando/randomizer.h"
#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "gc_wii/OSModule.h"
#include "gc_wii/card.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/d_meter2_info.h"
#include "tp/d_resource.h"
#include "tp/dzx.h"

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
            m_Seed = new Seed( CARD_SLOT_A, seedInfo );
            // Load checks for first load
            onStageLoad();
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