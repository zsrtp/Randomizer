/**	@file seed.cpp
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */

#include "seed.h"

#include <string.h>

#include <cstdint>
#include <cstdio>

#include "data/stages.h"
#include "game_patch/game_patch.h"
#include "gc/card.h"
#include "gci/data.h"
#include "main.h"
#include "tools.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"

namespace mod::rando
{
    Seed::Seed( int32_t chan, const char* fileName ): m_FileName( fileName ), m_CardSlot( chan )
    {
        m_Header = new gci::data::Header();

        m_CARDResult = libtp::tools::ReadGCI( m_CardSlot, m_FileName, sizeof( gci::data::Header ), 0, m_Header );
    }

    Seed::~Seed()
    {
        // Unpatch
        this->applyPatches( false );
        this->ClearChecks();
        delete[] m_Header;
    }

    void Seed::InitSeed( void )
    {
        // Reset counters & status
        m_SeedStatus = 0;
        m_AreaFlagsModified = 0;
        m_EventFlagsModified = 0;
        m_PatchesApplied = 0;

        m_SeedStatus |= SEED_STATUS_INITIALIZED;

        this->applyPatches( true );
        this->applyEventFlags();
        this->applyRegionFlags();
    }

    void Seed::LoadChecks( const char* stage )
    {
        using namespace libtp;

        // Find the index of this stage
        uint8_t stageIDX;
        for ( stageIDX = 0; stageIDX < sizeof( data::stage::allStages ) / sizeof( data::stage::allStages[0] ); stageIDX++ )
        {
            if ( !strcmp( stage, data::stage::allStages[stageIDX] ) )
            {
                break;
            }
        }

        // Don't run if this isn't actually a new stage
        if ( stageIDX != m_StageIDX )
        {
            this->ClearChecks();

            this->LoadDZX( stageIDX );
            this->LoadREL( stageIDX );
            this->LoadSHOP( stageIDX );

            // Save current stageIDX for next time
            m_StageIDX = stageIDX;
        }
    }

    void Seed::ClearChecks()
    {
        m_numLoadedDZXChecks = 0;
        m_numLoadedRELChecks = 0;
        m_numLoadedSHOPChecks = 0;

        delete[] m_DZXChecks;
        delete[] m_RELChecks;
        delete[] m_ShopChecks;
    }

    void Seed::applyPatches( bool set )
    {
        using namespace libtp;

        m_SeedStatus |= SEED_STATUS_PATCHED;

        uint32_t num_patches = m_Header->patchInfo.numEntries;
        uint32_t gci_offset = m_Header->patchInfo.dataOffset;

        // Don't bother to patch anything if there's nothing to patch
        if ( num_patches > 0 )
        {
            uint32_t num_bytes = num_patches / 8 + 1;
            uint8_t* patch_config = new uint8_t[num_bytes];

            m_CARDResult = tools::ReadGCI( m_CardSlot, m_FileName, num_bytes, gci_offset, patch_config );

            // TODO: Handle other CARDResults

            for ( uint32_t i = 0; i < num_bytes; i++ )
            {
                uint8_t byte = patch_config[i];

                for ( uint32_t b = 0; b < 8; b++ )
                {
                    if ( ( byte >> b ) & 0x80 )
                    {
                        // run the patch function for this bit index
                        uint32_t index = i * 8 + b;

                        using namespace game_patch;
                        if ( index < sizeof( patches ) / sizeof( patches[0] ) )
                        {
                            patches[index]( set );
                            m_PatchesApplied++;
                        }
                    }
                }
            }

            delete[] patch_config;
        }
    }

    void Seed::applyEventFlags()
    {
        using namespace libtp;
        using namespace mod::gci::data;

        m_SeedStatus |= SEED_STATUS_EVENTFLG;

        uint32_t num_eventFlags = m_Header->eventFlagsInfo.numEntries;
        uint32_t gci_offset = m_Header->eventFlagsInfo.dataOffset;

        if ( num_eventFlags > 0 )
        {
            // Load game-info
            tp::d_com_inf_game::GameInfo* gameInfo = &tp::d_com_inf_game::dComIfG_gameInfo;
            eventFlag* eventFlags = new eventFlag[num_eventFlags];

            m_CARDResult = tools::ReadGCI( m_CardSlot, m_FileName, num_eventFlags * 2, gci_offset, eventFlags );

            // TODO: Handle other CARDResults

            for ( uint32_t i = 0; i < num_eventFlags; i++ )
            {
                uint8_t offset = eventFlags[i].offset;
                uint8_t flag = eventFlags[i].flag;

                gameInfo->scratchPad.eventBits[offset] |= flag;
                m_EventFlagsModified++;
            }

            delete[] eventFlags;
        }
    }

    void Seed::applyRegionFlags()
    {
        using namespace libtp;
        using namespace mod::gci::data;

        m_SeedStatus |= SEED_STATUS_REGIONFLG;

        uint32_t num_regionFlags = m_Header->regionFlagsInfo.numEntries;
        uint32_t gci_offset = m_Header->regionFlagsInfo.dataOffset;

        if ( num_regionFlags > 0 )
        {
            // Load game-info
            tp::d_com_inf_game::GameInfo* gameInfo = &tp::d_com_inf_game::dComIfG_gameInfo;

            regionFlag* regionFlags = new regionFlag[num_regionFlags];

            // Load region-flags from GCI (seed-data)
            m_CARDResult = tools::ReadGCI( m_CardSlot, m_FileName, sizeof( regionFlags ), gci_offset, regionFlags );

            // TODO: Handle other CARDResults

            uint8_t regionID = data::stage::regions[0];
            // Loop through all regions
            for ( uint32_t i = 0; i < sizeof( data::stage::regions ); i++ )
            {
                regionID = data::stage::regions[i];

                tp::d_save::getSave( gameInfo, regionID );

                // Loop through region-flags from gci
                for ( uint32_t j = 0; j < num_regionFlags; j++ )
                {
                    if ( regionFlags[j].region_id == regionID )
                    {
                        // The n'th bit that we want to set TRUE
                        int32_t bit = regionFlags[j].bit_id;

                        int32_t offset = bit / 8;
                        int32_t shift = bit % 8;

                        if ( offset < 0x20 )
                        {
                            gameInfo->localAreaNodes[offset] |= ( 0x80 >> shift );
                            m_AreaFlagsModified++;
                        }
                    }
                }

                // Save the modifications if
                tp::d_save::putSave( gameInfo, regionID );
            }

            delete[] regionFlags;

            // Reset to previous region ID
            uint8_t i = 0;

            while ( !strcmp( data::stage::allStages[i], gameInfo->currentStage ) )
            {
                i++;
            }

            tp::d_save::getSave( gameInfo, data::stage::regions[i] );
        }
    }

    void Seed::LoadDZX( uint8_t stageIDX )
    {
        using namespace libtp;
        using namespace mod::gci::data;

        m_SeedStatus |= SEED_STATUS_DZXLOAD;

        uint32_t num_dzxchecks = m_Header->dzxCheckInfo.numEntries;
        uint32_t gci_offset = m_Header->dzxCheckInfo.dataOffset;

        // Allocate memory for all DZX checks, then load stage specific dzx into m_dzxChecks
        dzxCheck* allDZX = new dzxCheck[num_dzxchecks];

        m_CARDResult = tools::ReadGCI( m_CardSlot, m_FileName, sizeof( dzxCheck ) * num_dzxchecks, gci_offset, allDZX );

        if ( m_CARDResult == CARD_RESULT_READY )
        {
            for ( uint32_t i = 0; i < num_dzxchecks; i++ )
            {
                if ( allDZX[i].stageIDX == stageIDX )
                {
                    m_numLoadedDZXChecks++;
                }
            }

            // Allocate memory the actual RELChecks
            m_DZXChecks = new dzxCheck[m_numLoadedDZXChecks];

            // offset into m_DZXChecks
            uint32_t j = 0;

            for ( uint32_t i = 0; i < num_dzxchecks; i++ )
            {
                if ( allDZX[i].stageIDX == stageIDX )
                {
                    // Store the i'th DZX check into the j'th Loaded DZX check that's relevant to our current stage
                    memcpy( &m_DZXChecks[j], &allDZX[i], sizeof( dzxCheck ) );
                    j++;
                }
            }
        }

        // Free
        delete[] allDZX;
    }

    void Seed::LoadREL( uint8_t stageIDX )
    {
        using namespace libtp;
        using namespace mod::gci::data;

        m_SeedStatus |= SEED_STATUS_RELLOAD;

        uint32_t num_relchecks = m_Header->relCheckInfo.numEntries;
        uint32_t gci_offset = m_Header->relCheckInfo.dataOffset;

        // Allocate memory for DZX checks
        RELCheck* allREL = new RELCheck[num_relchecks];

        m_CARDResult = tools::ReadGCI( m_CardSlot, m_FileName, sizeof( RELCheck ) * num_relchecks, gci_offset, allREL );

        if ( m_CARDResult == CARD_RESULT_READY )
        {
            for ( uint32_t i = 0; i < num_relchecks; i++ )
            {
                if ( allREL[i].stageIDX == stageIDX )
                {
                    m_numLoadedRELChecks++;
                }
            }

            // Allocate memory the actual RELChecks
            m_RELChecks = new RELCheck[m_numLoadedRELChecks];

            // offset into m_RELChecks
            uint32_t j = 0;

            for ( uint32_t i = 0; i < num_relchecks; i++ )
            {
                if ( allREL[i].stageIDX == stageIDX )
                {
                    // Store the i'th DZX check into the j'th Loaded DZX check that's relevant to our current stage
                    memcpy( &m_RELChecks[j], &allREL[i], sizeof( RELCheck ) );
                    j++;
                }
            }
        }

        // Free
        delete[] allREL;
    }

    void Seed::LoadSHOP( uint8_t stageIDX )
    {
        using namespace libtp;
        using namespace mod::gci::data;

        m_SeedStatus |= SEED_STATUS_SHOPLOAD;

        uint32_t num_shopchecks = m_Header->shopCheckInfo.numEntries;
        uint32_t gci_offset = m_Header->shopCheckInfo.dataOffset;

        // Allocate memory for DZX checks
        shopCheck* allSHOP = new shopCheck[num_shopchecks];

        m_CARDResult = tools::ReadGCI( m_CardSlot, m_FileName, sizeof( shopCheck ) * num_shopchecks, gci_offset, allSHOP );

        if ( m_CARDResult == CARD_RESULT_READY )
        {
            for ( uint32_t i = 0; i < num_shopchecks; i++ )
            {
                if ( allSHOP[i].stageIDX == stageIDX )
                {
                    m_numLoadedSHOPChecks++;
                }
            }

            // Allocate memory the actual RELChecks
            m_ShopChecks = new shopCheck[m_numLoadedSHOPChecks];

            // offset into m_RELChecks
            uint32_t j = 0;

            for ( uint32_t i = 0; i < num_shopchecks; i++ )
            {
                if ( allSHOP[i].stageIDX == stageIDX )
                {
                    // Store the i'th DZX check into the j'th Loaded DZX check that's relevant to our current stage
                    memcpy( &m_ShopChecks[j], &allSHOP[i], sizeof( shopCheck ) );
                    j++;
                }
            }
        }

        // Free
        delete[] allSHOP;
    }

}     // namespace mod::rando