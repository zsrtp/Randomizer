/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include "rando/randomizer.h"

#include <cstdio>
#include <cstring>

#include "data/items.h"
#include "data/stages.h"
#include "gc/OSModule.h"
#include "gc/card.h"
#include "main.h"
#include "patch.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/dynamic_link.h"
#include "tp/dzx.h"
#include "user_patch/03_customCosmetics.h"

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
            m_Seed->setArcIndex();
            m_Seed->loadShopModels();
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
        const char* stage = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mNextStage.stageValues.mStage;
        m_Seed->LoadChecks( stage );
    }

    void Randomizer::overrideREL()
    {
        // Local vars
        uint32_t numReplacements = m_Seed->m_numLoadedRELChecks;
        RELCheck* relReplacements = m_Seed->m_RELChecks;

        // If we don't have replacements just leave
        if ( !numReplacements )
            return;

        // Loop through all loaded OSModuleInfo entries and apply the specified values to the rels already loaded.
        libtp::gc::os_module::OSModuleInfo* rel = libtp::gc::os_module::osModuleList.first;
        for ( ; rel; rel = rel->next )
        {
            for ( uint32_t i = 0; i < numReplacements; i++ )
            {
                if ( rel->id == relReplacements[i].moduleID )
                {
                    *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( rel ) + relReplacements[i].offset ) =
                        relReplacements[i].override;
                }
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

    uint8_t Randomizer::getSkyCharacter()
    {
        if ( m_Seed->m_numSkyBookChecks == 1 )
        {
            return m_Seed->m_SkyBookChecks[0].itemID;
        }
        else
        {
            for ( uint32_t i = 0; i < m_Seed->m_numSkyBookChecks; i++ )
            {
                if ( m_Seed->m_SkyBookChecks[i].roomID == libtp::tp::d_kankyo::env_light.currentRoom )
                {
                    return m_Seed->m_SkyBookChecks[i].itemID;
                }
            }
        }
        // default
        return libtp::data::items::Ancient_Sky_Book_Partly_Filled;
    }

    uint8_t Randomizer::getBossItem() { return m_Seed->m_BossChecks[0].item; }

    void Randomizer::overrideARC( void* filePtr, int32_t fileIndex )
    {
        m_Seed->LoadARCChecks( fileIndex );
        uint32_t numReplacements = m_Seed->m_numLoadedArcReplacements;
        // Loop through all ArcChecks and replace the item at an offset given the fileIndex.
        for ( uint32_t i = 0; i < numReplacements; i++ )
        {
            switch ( m_Seed->m_ArcReplacements[i].replacementType )
            {
                case rando::ArcReplacementType::Item:
                {
                    *reinterpret_cast<uint8_t*>(
                        ( reinterpret_cast<uint32_t>( filePtr ) + m_Seed->m_ArcReplacements[i].offset ) ) =
                        m_Seed->m_ArcReplacements[i].replacementValue;
                    break;
                }
                case rando::ArcReplacementType::HiddenSkill:
                {
                    uint8_t stageIDX;
                    for ( stageIDX = 0;
                          stageIDX < sizeof( libtp::data::stage::allStages ) / sizeof( libtp::data::stage::allStages[0] );
                          stageIDX++ )
                    {
                        if ( !strcmp( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_last_stay_info
                                          .player_last_stage,
                                      libtp::data::stage::allStages[stageIDX] ) )
                        {
                            break;
                        }
                    }

                    for ( uint i = 0; i < m_Seed->m_numHiddenSkillChecks; i++ )
                    {
                        if ( ( m_Seed->m_HiddenSkillChecks[i].stageIDX == stageIDX ) &&
                             ( m_Seed->m_HiddenSkillChecks[i].roomID == libtp::tp::d_kankyo::env_light.currentRoom ) )
                        {
                            *reinterpret_cast<uint16_t*>(
                                ( reinterpret_cast<uint32_t>( filePtr ) + m_Seed->m_ArcReplacements[i].offset ) ) =
                                m_Seed->m_HiddenSkillChecks[i].itemID + 0x65;
                        }
                    }
                    break;
                }
                case rando::ArcReplacementType::ItemMessage:
                {
                    *reinterpret_cast<uint16_t*>(
                        ( reinterpret_cast<uint32_t>( filePtr ) + m_Seed->m_ArcReplacements[i].offset ) ) =
                        m_Seed->m_ArcReplacements[i].replacementValue + 0x65;
                }
            }
        }
    }

    uint8_t Randomizer::overrideBugReward( uint8_t bugID )
    {
        for ( uint32_t i = 0; i < m_Seed->m_numBugRewardChecks; i++ )
        {
            if ( bugID == m_Seed->m_BugRewardChecks[i].bugID )
            {
                // Return new item
                return m_Seed->m_BugRewardChecks[i].itemID;
            }
        }
        // Default
        return bugID;
    }

    uint8_t Randomizer::getHiddenSkillItem( uint16_t eventIndex )
    {
        for ( uint32_t i = 0; i < m_Seed->m_numHiddenSkillChecks; i++ )
        {
            if ( eventIndex == m_Seed->m_HiddenSkillChecks[i].indexNumber )
            {
                // Return new item
                return m_Seed->m_HiddenSkillChecks[i].itemID;
            }
        }
        // Default
        return libtp::data::items::Recovery_Heart;
    }
}     // namespace mod::rando