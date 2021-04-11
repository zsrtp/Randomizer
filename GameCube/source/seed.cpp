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
#include "gc/card.h"
#include "gci_data/check.h"
#include "main.h"
#include "tools.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"

namespace mod::rando
{
    Seed::Seed( int32_t chan, const char* fileName ): m_FileName( fileName ), m_CardSlot( chan )
    {
        m_Header = new gci_data::Header();

        m_CARDResult = libtp::tools::ReadGCI( m_CardSlot, m_FileName, sizeof( gci_data::Header ), 0, m_Header );
    }

    Seed::~Seed()
    {
        this->ClearChecks();
        delete[] m_Header;
    }

    void Seed::InitSeed( void )
    {
        m_SeedStatus |= SEED_STATUS_INITIALIZED;

        // this->applyPatches();
        this->applyEventFlags();
        this->applyRegionFlags();
    }

    void Seed::LoadChecks( const char* stage )
    {
        this->ClearChecks();

        this->LoadDZX();
        this->LoadREL();
        this->LoadSHOP();
    }

    void Seed::ClearChecks()
    {
        delete[] m_DZXChecks;
        delete[] m_RELChecks;
        delete[] m_ShopChecks;
    }

    void Seed::applyPatches()
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
                    if ( ( byte << b ) & 0x80 )
                    {
                        // run the patch function for this bit index
                        // TODO: Function pointer to patch functions (enum?)
                        m_PatchesApplied++;
                        // uint32_t index = byte * 8 + b;
                    }
                }
            }

            delete[] patch_config;
        }
    }

    void Seed::applyEventFlags()
    {
        using namespace libtp;
        using namespace mod::gci_data;

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
        using namespace mod::gci_data;

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

    void Seed::LoadDZX()
    {
        m_SeedStatus |= SEED_STATUS_DZXLOAD;
        //
    }
    void Seed::LoadREL()
    {
        m_SeedStatus |= SEED_STATUS_RELLOAD;
        //
    }
    void Seed::LoadSHOP()
    {
        m_SeedStatus |= SEED_STATUS_SHOPLOAD;
        //
    }

}     // namespace mod::rando