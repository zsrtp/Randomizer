/**	@file seed.cpp
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */

#include "rando/seed.h"

#include <string.h>

#include <cstdint>
#include <cstdio>

#include "data/stages.h"
#include "game_patch/game_patch.h"
#include "gc/card.h"
#include "main.h"
#include "rando/data.h"
#include "tools.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"

namespace mod::rando
{
    Seed::Seed( int32_t chan, SeedInfo* seedInfo ): m_CardSlot( chan )
    {
        m_Header = &seedInfo->header;

        // Loading seed rando-dataX '<seed>'...

        // Store our filename index
        m_fileIndex = seedInfo->fileIndex;

        mod::console << "Loading seed " << m_fileIndex << ": '" << m_Header->seed << "'...\n";

        // Load the whole gci locally to reduce number of reads (memcard)
        uint32_t length = m_Header->fileSize;
        char fileName[12] = "rando-data\0";

        fileName[10] = static_cast<char>( '0' + m_fileIndex );

        m_GCIData = new uint8_t[length];

        m_CARDResult = libtp::tools::ReadGCI( m_CardSlot, fileName, length, 0x00, m_GCIData );
    }

    Seed::~Seed()
    {
        // Make sure to delete tempcheck buffers
        this->ClearChecks();

        // Only work with m_GCIData if the buffer is populated
        if ( m_GCIData )
        {
            this->applyPatches( false );

            // Last clear gcibuffer as other functions before rely on it
            delete[] m_GCIData;
        }
    }

    bool Seed::InitSeed( void )
    {
        // (Re)set counters & status
        m_AreaFlagsModified = 0;
        m_EventFlagsModified = 0;
        m_PatchesApplied = 0;

        if ( m_CARDResult == CARD_RESULT_READY )
        {
            mod::console << "Patching game:\n";

            this->applyPatches( true );

            mod::console << "Event Flags: \n";
            this->applyEventFlags();

            mod::console << "Region Flags: \n";
            this->applyRegionFlags();
            return true;
        }
        else
        {
            mod::console << "FATAL: Couldn't read Seed #" << m_fileIndex << "\n";
            mod::console << "ERROR: " << m_CARDResult << "\n";
            return false;
        }
    }

    bool Seed::LoadChecks( const char* stage )
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
        bool result = stageIDX != m_StageIDX;
        if ( result )
        {
            this->ClearChecks();

            this->LoadDZX( stageIDX );
            this->LoadREL( stageIDX );

            // Save current stageIDX for next time
            m_StageIDX = stageIDX;
        }

        return result;
    }

    void Seed::ClearChecks()
    {
        m_numLoadedDZXChecks = 0;
        m_numLoadedRELChecks = 0;

        delete[] m_DZXChecks;
        delete[] m_RELChecks;
    }

    void Seed::applyPatches( bool set )
    {
        using namespace libtp;

        uint32_t num_patches = m_Header->patchInfo.numEntries;
        uint32_t gci_offset = m_Header->patchInfo.dataOffset;

        // Don't bother to patch anything if there's nothing to patch
        if ( num_patches > 0 )
        {
            uint32_t num_bytes = num_patches / 8 + 1;

            // Set the pointer as offset into our buffer
            uint8_t* patch_config = &m_GCIData[gci_offset];

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
        }
    }

    void Seed::applyEventFlags()
    {
        using namespace libtp;

        uint32_t num_eventFlags = m_Header->eventFlagsInfo.numEntries;
        uint32_t gci_offset = m_Header->eventFlagsInfo.dataOffset;

        if ( num_eventFlags > 0 )
        {
            tp::d_com_inf_game::GameInfo* gameInfo = &tp::d_com_inf_game::dComIfG_gameInfo;

            // Set the pointer as offset into our buffer
            eventFlag* eventFlags = reinterpret_cast<eventFlag*>( &m_GCIData[gci_offset] );

            for ( uint32_t i = 0; i < num_eventFlags; i++ )
            {
                uint8_t offset = eventFlags[i].offset;
                uint8_t flag = eventFlags[i].flag;

                gameInfo->scratchPad.eventBits[offset] |= flag;
                m_EventFlagsModified++;
            }
        }
    }

    void Seed::applyRegionFlags()
    {
        using namespace libtp;

        uint32_t num_regionFlags = m_Header->regionFlagsInfo.numEntries;
        uint32_t gci_offset = m_Header->regionFlagsInfo.dataOffset;

        if ( num_regionFlags > 0 )
        {
            tp::d_com_inf_game::GameInfo* gameInfo = &tp::d_com_inf_game::dComIfG_gameInfo;

            // Set the pointer as offset into our buffer
            regionFlag* regionFlags = reinterpret_cast<regionFlag*>( &m_GCIData[gci_offset] );

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

                        // Failsafe; localAreaNode size is 0x20
                        if ( offset < 0x20 )
                        {
                            gameInfo->localAreaNodes[offset] |= ( 0x80 >> shift );
                            m_AreaFlagsModified++;
                        }
                    }
                }

                // Save the modifications
                tp::d_save::putSave( gameInfo, regionID );
            }

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

        uint32_t num_dzxchecks = m_Header->dzxCheckInfo.numEntries;
        uint32_t gci_offset = m_Header->dzxCheckInfo.dataOffset;

        // Set the pointer as offset into our buffer
        dzxCheck* allDZX = reinterpret_cast<dzxCheck*>( &m_GCIData[gci_offset] );

        for ( uint32_t i = 0; i < num_dzxchecks; i++ )
        {
            if ( allDZX[i].stageIDX == stageIDX )
            {
                m_numLoadedDZXChecks++;
            }
        }

        // Allocate memory the actual RELChecks
        // We do NOT have to clear the previous buffer as that's already done in "LoadChecks()"
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

    void Seed::LoadREL( uint8_t stageIDX )
    {
        using namespace libtp;

        uint32_t num_relchecks = m_Header->relCheckInfo.numEntries;
        uint32_t gci_offset = m_Header->relCheckInfo.dataOffset;

        // Set the pointer as offset into our buffer
        RELCheck* allREL = reinterpret_cast<RELCheck*>( &m_GCIData[gci_offset] );

        for ( uint32_t i = 0; i < num_relchecks; i++ )
        {
            if ( allREL[i].stageIDX == stageIDX )
            {
                m_numLoadedRELChecks++;
            }
        }

        // Allocate memory to the actual RELChecks
        // Do NOT need to clear the previous buffer as that's taken care of by LoadChecks()
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

}     // namespace mod::rando