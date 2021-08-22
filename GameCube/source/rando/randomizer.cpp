/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/randomizer.h"

#include <cstring>

#include "data/items.h"
#include "gc/OSModule.h"
#include "gc/card.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"
#include "tp/d_com_inf_game.h"
#include "tp/dynamic_link.h"
#include "tp/dzx.h"

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

            // Load the seed
            m_SeedInfo = seedInfo;
            m_Seed = new Seed( CARD_SLOT_A, seedInfo );

            // Load checks for first load
            onStageLoad();
        }
    }

    Randomizer::~Randomizer( void )
    {
        mod::console << "Rando unloading...\n";

        // Clear Seed
        delete m_Seed;
    }

    void Randomizer::initSave( void )
    {
        if ( m_Seed )
        {
            m_SeedInit = m_Seed->InitSeed();
        }
    }

    void Randomizer::onStageLoad( void )
    {
        const char* stage = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mNextStage.mStage;
        m_Seed->LoadChecks( stage );
    }

    void Randomizer::overrideREL( libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        // Local vars
        uint32_t numReplacements = m_Seed->m_numLoadedDZXChecks;
        RELCheck* relReplacements = m_Seed->m_RELChecks;

        // Get the pointer to the current REL file
        libtp::gc::os_module::OSModuleInfo* moduleInfo = dmc->moduleInfo;

        // If we don't have replacements just leave
        if ( !numReplacements )
            return;

        // Also make sure the REL is actually loaded
        if ( !moduleInfo )
            return;

        // Get the REL pointer as a raw u32, to use for overwrites
        uint32_t relPtrRaw = reinterpret_cast<uint32_t>( moduleInfo );

        // Loop through RELChecks and apply if necessary
        for ( uint32_t i = 0; i < numReplacements; i++ )
        {
            RELCheck* relCheck = &relReplacements[i];
            if ( moduleInfo->id == relCheck->moduleID )
            {
                // Override as specified
                *reinterpret_cast<uint32_t*>( relPtrRaw + relCheck->offset ) = relCheck->override;
            }
        }
    }

    void Randomizer::overrideDZX( libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        // Local vars
        uint32_t numReplacements = m_Seed->m_numLoadedDZXChecks;
        dzxCheck* dzxReplacements = m_Seed->m_DZXChecks;

        uint32_t numChunks = chunkTypeInfo->numChunks;
        libtp::tp::dzx::ACTR* dzxData = reinterpret_cast<libtp::tp::dzx::ACTR*>( chunkTypeInfo->chunkDataPtr );

        // Check if we have DZX checks to work with
        if ( !numReplacements )
            return;

        // Loop through all chunks the game is currently loading/setting
        for ( uint32_t i = 0; i < numChunks; i++ )
        {
            // The hash in RAM right now
            uint16_t actorHash =
                libtp::tools::fletcher16( reinterpret_cast<uint8_t*>( &dzxData[i] ), sizeof( libtp::tp::dzx::ACTR ) );

            // Compare to all available replacements
            for ( uint32_t j = 0; j < numReplacements; j++ )
            {
                if ( dzxReplacements[j].hash == actorHash )
                {
                    // Bytearray of target ACTR struct
                    uint8_t* target = reinterpret_cast<uint8_t*>( &dzxData[i] );

                    // Replace target Actor with replacement values if != FF
                    for ( uint8_t b = 0; b < sizeof( libtp::tp::dzx::ACTR ); b++ )
                    {
                        // Fetch replacement byte
                        uint8_t newByte = dzxReplacements[j].data[b];

                        if ( newByte != dzxReplacements[j].magicByte )
                            target[b] = newByte;
                    }
                }
            }
        }
    }

    int32_t Randomizer::getPoeItem( uint8_t flag )
    {
        for ( uint32_t i = 0; i < m_Seed->m_numLoadedPOEChecks; i++ )
        {
            if ( flag == m_Seed->m_POEChecks[i].flag )
            {
                // Return new item
                return static_cast<int32_t>( m_Seed->m_POEChecks[i].item );
            }
        }

        // Default
        return libtp::data::items::Poe_Soul;
    }
}     // namespace mod::rando