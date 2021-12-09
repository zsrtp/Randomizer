/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/randomizer.h"

#include <cstring>
#include <cstdio>

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
#include "gc/dvdfs.h"
#include "data/stages.h"

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

    uint8_t Randomizer::getBossItem()
    {
        // Essentially we just loop through the BOSS Checks and check to see if the stage index matches the check and return the item in the check if it matches.
        // Default
        return libtp::data::items::Poe_Soul;
    }

    void Randomizer::getArcIndex()
    {
        // Local vars
        uint32_t numReplacements = m_Seed->m_numLoadedArcChecks;
        char filePath[32];
        int32_t len = 0;

        // Loop through all ArcChecks and set their corresponding file index
        for ( uint32_t i = 0; i < numReplacements; i++ )
        {
            switch (m_Seed->m_ArcChecks[i].directory)
            {
                case rando::FileDirectory::Stage:
                {
                    len = snprintf(filePath, sizeof(filePath), "res/Stage/%s", m_Seed->m_ArcChecks[i].fileName);
                    break;
                }
                case rando::FileDirectory::Message:
                {
#ifdef TP_US
                    len = snprintf(filePath, sizeof(filePath), "res/Msgus/%s", m_Seed->m_ArcChecks[i].fileName);
#elif defined TP_JP
                    len = snprintf(filePath, sizeof(filePath), "res/Msgjp/%s", m_Seed->m_ArcChecks[i].fileName);
#elif defined TP_EU
                    // PAL uses a different file for each language
                    libtp::tp::d_s_logo::Languages lang = tp::d_s_logo::getPalLanguage2(nullptr);
                    if ((lang < tp::d_s_logo::Languages::uk) || (lang > tp::d_s_logo::Languages::it))
                    {
                        // The language is invalid/unsupported, so the game defaults to English
                        lang = tp::d_s_logo::Languages::uk;
                    }
                    
                    static const char* langStrings[] = {"uk", "de", "fr", "sp", "it"};
                    len = snprintf(filePath, sizeof(filePath), "res/Msg%s/%s", langStrings[static_cast<s32>(lang)], m_Seed->m_ArcChecks[i].fileName);
#endif
                    break;
                }
                default:
                {
                    len = snprintf(filePath, sizeof(filePath), "%s", m_Seed->m_ArcChecks[i].fileName);
                } 
            }

            if ((len >= 0) && (len < static_cast<int32_t>(sizeof(filePath))))
            {
                m_Seed->m_ArcChecks[i].arcFileIndex = libtp::gc::dvdfs::DVDConvertPathToEntrynum(filePath);
            }
            else // Failsafe in case we did not get a valid result.
            {
                m_Seed->m_ArcChecks[i].arcFileIndex = -1;
            }
        }
    }
}     // namespace mod::rando