/**	@file seed.cpp
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cinttypes>

#ifdef DVD
#include "gc_wii/dvd.h"
#else
#include "gc_wii/card.h"
#endif

#include "rando/seed.h"
#include "rando/linkHouseSign.h"
#include "cxx.h"
#include "game_patch/game_patch.h"
#include "main.h"
#include "rando/data.h"
#include "tools.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_item_data.h"
#include "user_patch/user_patch.h"

namespace mod::rando
{
    Seed::Seed( int32_t chan, SeedInfo* seedInfo ): m_CardSlot( chan )
    {
        m_Header = &seedInfo->header;
        // Loading seed rando-dataX '<seed>'...

        // Store our filename index
        MinSeedInfo* minSeedInfo = seedInfo->minSeedInfo;
        m_fileIndex = minSeedInfo->fileIndex;

        const char* fileName = minSeedInfo->fileName;
        getConsole() << "Loading seed " << static_cast<int32_t>( m_fileIndex + 1 ) << ": '" << fileName << "'...\n";

        // Allocate the buffer to the back of the heap to prevent fragmentation
        uint32_t totalSize = minSeedInfo->totalSize;

        // Align to 0x20 for safety, since some functions may cast parts of it to classes/structs/arrays/etc.
        uint8_t* data = new ( -0x20 ) uint8_t[totalSize];
#ifdef DVD
        // fileName does not contain the full file path
        char filePath[96];
        snprintf( filePath, sizeof( filePath ), "/mod/seed/%s", fileName );

        m_CARDResult = libtp::tools::ReadFile( filePath, totalSize, 0, data );
        if ( m_CARDResult == DVD_STATE_END )
#else
        // The memory card should already be mounted
        m_CARDResult = libtp::tools::ReadGCIMounted( m_CardSlot, fileName, totalSize, 0, data, true );
        if ( m_CARDResult == CARD_RESULT_READY )
#endif
        {
            Header* headerPtr = m_Header;

            // Get the header data
            memcpy( headerPtr, data, sizeof( Header ) );

            // Get the main seed data
            // Align to 0x20 for safety, since some functions cast parts of it to classes/structs/arrays/etc.
            uint32_t dataSize = headerPtr->dataSize;
            m_GCIData = new ( 0x20 ) uint8_t[dataSize];
            memcpy( m_GCIData, &data[headerPtr->headerSize], dataSize );

            // Create the required dungeons text that is displayed when reading the sign in front of Link's house
            link_house_sign::createRequiredDungeonsString( this, headerPtr->requiredDungeons );

            // Generate the BGM/Fanfare table data
            loadBgmData( data );
            m_CLR0 = reinterpret_cast<CLR0Header*>( m_GCIData + headerPtr->clr0Offset );
            m_RawRGBTable = reinterpret_cast<RawRGBTable*>( m_GCIData + headerPtr->clr0Offset + m_CLR0->rawRGBOffset );
            m_BmdEntries = reinterpret_cast<BmdEntry*>( m_GCIData + headerPtr->clr0Offset + m_CLR0->bmdEntriesOffset );
        }
        delete[] data;
    }

    Seed::~Seed()
    {
        // Make sure to delete tempcheck buffers
        this->ClearChecks();

        // Only work with m_GCIData if the buffer is populated
        if ( m_GCIData )
        {
            this->applyOneTimePatches( false );

            // Last clear gcibuffer as other functions before rely on it
            delete[] m_GCIData;
        }

        // Clear the memory used by the required dungeons text that is displayed when reading the sign in front of Link's house
        delete[] m_RequiredDungeons;

        // Clear the bgm table buffers
        delete[] m_BgmTable;
        delete[] m_FanfareTable;
    }

    void Seed::applyOneTimePatches( bool set )
    {
        using namespace libtp;

        uint32_t num_bytes = m_Header->oneTimePatchInfo.numEntries;
        uint32_t gci_offset = m_Header->oneTimePatchInfo.dataOffset;

        // Don't bother to patch anything if there's nothing to patch
        if ( num_bytes > 0 )
        {
            // Set the pointer as offset into our buffer
            uint8_t* patch_config = &m_GCIData[gci_offset];

            for ( uint32_t i = 0; i < num_bytes; i++ )
            {
                uint8_t byte = patch_config[i];

                for ( uint32_t b = 0; b < 8; b++ )
                {
                    if ( ( byte << b ) & 0x80 )
                    {
                        // Run the patch function for this bit index
                        uint32_t index = i * 8 + b;

                        if ( index < sizeof( user_patch::oneTimePatches ) / sizeof( user_patch::oneTimePatches[0] ) )
                        {
                            user_patch::oneTimePatches[index]( mod::randomizer, set );
                            m_PatchesApplied++;
                        }
                    }
                }
            }
        }
    }

    void Seed::loadBgmData( uint8_t* data )
    {
        uint32_t headerOffset = m_Header->headerSize + m_Header->bgmHeaderOffset;

        // Get the Bgm Header
        bgmHeader* customBgmHeader = reinterpret_cast<bgmHeader*>( &data[headerOffset] );

        // Handle any bgm entries
        uint32_t bgmTableEntries = customBgmHeader->bgmTableNumEntries;
        if ( bgmTableEntries > 0 )
        {
            // Align to uint32_t, as the table is an array of structs with a size of 0x4 each
            uint32_t bgmTableSize = customBgmHeader->bgmTableSize;
            uint8_t* buf = new ( sizeof( uint32_t ) ) uint8_t[bgmTableSize];
            uint32_t offset = headerOffset + customBgmHeader->bgmTableOffset;
            memcpy( buf, &data[offset], bgmTableSize );

            // Assign the entry count and buffer
            m_BgmTableEntries = static_cast<uint8_t>( bgmTableEntries );
            m_BgmTable = reinterpret_cast<bgmReplacement*>( buf );
        }

        // Handle any fanfare entries
        uint32_t fanfareTableEntries = customBgmHeader->fanfareTableNumEntries;
        if ( fanfareTableEntries > 0 )
        {
            // Align to uint32_t, as the table is an array of structs with a size of 0x4 each
            uint32_t fanfareTableSize = customBgmHeader->fanfareTableSize;
            uint8_t* buf = new ( sizeof( uint32_t ) ) uint8_t[fanfareTableSize];
            uint32_t offset = headerOffset + customBgmHeader->fanfareTableOffset;
            memcpy( buf, &data[offset], fanfareTableSize );

            // Assign the entry count and buffer
            m_FanfareTableEntries = static_cast<uint8_t>( fanfareTableEntries );
            m_FanfareTable = reinterpret_cast<bgmReplacement*>( buf );
        }
    }

    void Seed::loadShopModels()
    {
        using namespace libtp::tp;

        uint32_t num_shopItems = m_Header->shopItemCheckInfo.numEntries;
        uint32_t gci_offset = m_Header->shopItemCheckInfo.dataOffset;

        // Set the pointer as offset into our buffer
        shopCheck* allSHOP = reinterpret_cast<shopCheck*>( &m_GCIData[gci_offset] );

        d_item_data::ItemResource* itemResourcePtr = &d_item_data::item_resource[0];
        for ( uint32_t i = 0; i < num_shopItems; i++ )
        {
            if ( allSHOP[i].replacementItemID == libtp::data::items::Foolish_Item )
            {
                game_patch::_02_modifyFoolishShopModel( allSHOP[i].shopItemID );
            }
            else
            {
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].arcName =
                    itemResourcePtr[allSHOP[i].replacementItemID].arcName;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].modelResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].modelResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBtkResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].btkResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBckResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].bckResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBrkResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].brkResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBtpResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].btpResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].tevFrm =
                    itemResourcePtr[allSHOP[i].replacementItemID].tevFrm;
            }
            d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].btpFrm = 0xFF;
            d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].posY = 15.0f;
            d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].mFlags = 0xFFFFFFFF;
        }
    }

}     // namespace mod::rando