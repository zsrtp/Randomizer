/**	@file seed.cpp
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */

#include <cstdint>
#include <cstring>

#include "rando/seed.h"
#include "cxx.h"
#include "game_patch/game_patch.h"
#include "gc_wii/card.h"
#include "main.h"
#include "rando/data.h"
#include "tools.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"
#include "tp/d_s_logo.h"
#include "tp/d_save.h"
#include "user_patch/user_patch.h"

namespace mod::rando
{
    Seed::Seed( int32_t chan, SeedInfo* seedInfo ): m_CardSlot( chan )
    {
        m_Header = &seedInfo->header;
        mod::console << m_Header << "\n";
        // Loading seed rando-dataX '<seed>'...

        // Store our filename index
        m_fileIndex = seedInfo->fileIndex;

        mod::console << "Loading seed " << m_fileIndex << ": '" << m_Header->seed << "'...\n";

        // Load the whole gci locally to reduce number of reads (memcard)
        char fileName[12] = "rando-data\0";

        fileName[10] = static_cast<char>( '0' + m_fileIndex );

        // Allocate the buffer to the back of the heap to prevent fragmentation
        uint32_t totalSize = m_Header->totalSize;
        uint8_t* data = new ( -0x4 ) uint8_t[totalSize];

        // The memory card should already be mounted
        m_CARDResult = libtp::tools::ReadGCIMounted( m_CardSlot, fileName, totalSize, 0, data, true );
        if ( m_CARDResult == CARD_RESULT_READY )
        {
            // Get the main seed data
            uint32_t dataSize = m_Header->dataSize;
            m_GCIData = new uint8_t[dataSize];
            memcpy( m_GCIData, &data[m_Header->headerSize], dataSize );

            // Get the custom text data
            this->loadCustomText( data );
        }
        delete[] data;
    }

    Seed::~Seed()
    {
        // Make sure to delete tempcheck buffers
        this->ClearChecks();

        // Reset the custom message data
        m_TotalMsgEntries = 0;
        delete[] m_MsgTableInfo;

        // Only work with m_GCIData if the buffer is populated
        if ( m_GCIData )
        {
            this->applyPatches( false );

            // Last clear gcibuffer as other functions before rely on it
            delete[] m_GCIData;
        }
    }

    void Seed::applyPatches( bool set )
    {
        using namespace libtp;

        uint32_t num_bytes = m_Header->patchInfo.numEntries;
        uint32_t gci_offset = m_Header->patchInfo.dataOffset;

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
                        // run the patch function for this bit index
                        uint32_t index = i * 8 + b;

                        if ( index < sizeof( user_patch::patches ) / sizeof( user_patch::patches[0] ) )
                        {
                            user_patch::patches[index]( mod::randomizer, set );
                            m_PatchesApplied++;
                        }
                    }
                }
            }
        }
    }

    void Seed::loadShopModels()
    {
        using namespace libtp::tp;
        if ( m_GCIData &&
             m_Header )     // A fail-safe as the randomizer will crash if it tries to read a seed and there isn't one.
        {
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
    }

    bool Seed::loadCustomText( uint8_t* data )
    {
        // Get the custom message header
        CustomMessageHeaderInfo* customMessageHeader =
            reinterpret_cast<CustomMessageHeaderInfo*>( &data[m_Header->customTextHeaderOffset] );

        // Keep track of the index for the language that is about to be selected
        uint32_t languageIndex = 0;

        // Get the text for the current language
#ifdef TP_EU
        libtp::tp::d_s_logo::Languages lang = libtp::tp::d_s_logo::getPalLanguage2( nullptr );
        if ( ( lang < libtp::tp::d_s_logo::Languages::uk ) || ( lang > libtp::tp::d_s_logo::Languages::it ) )
        {
            // The language is invalid/unsupported, so the game defaults to English
            lang = libtp::tp::d_s_logo::Languages::uk;
        }
        uint32_t language = static_cast<uint32_t>( lang );

        // Get a pointer to the language to use
        uint32_t totalLanguages = customMessageHeader->totalLanguages;
        CustomMessageEntryInfo* customMessageInfo = nullptr;

        for ( uint32_t i = 0; i < totalLanguages; i++ )
        {
            CustomMessageEntryInfo* entry = &customMessageHeader->entry[i];
            if ( entry->language == language )
            {
                languageIndex = i;
                customMessageInfo = entry;
                break;
            }
        }

        // If the language wasn't found, then default to English, which should always be the first language included
        if ( !customMessageInfo )
        {
            customMessageInfo = &customMessageHeader->entry[0];
        }
#else
        // US/JP should only have one language included
        CustomMessageEntryInfo* customMessageInfo = &customMessageHeader->entry[0];
#endif

        // Allocate memory for the ids, message offsets, and messages
        uint32_t totalEntries = customMessageInfo->totalEntries;
        m_TotalMsgEntries = totalEntries;

        uint32_t msgIdTableSize = totalEntries * sizeof( uint16_t );
        uint32_t msgOffsetTableSize = totalEntries * sizeof( uint32_t );

        // Round msgIdTableSize up to the size of the offsets to make sure the offsets are properly aligned
        msgIdTableSize = ( msgIdTableSize + sizeof( uint32_t ) - 1 ) & ~( sizeof( uint32_t ) - 1 );

        uint32_t msgTableInfoSize = msgIdTableSize + msgOffsetTableSize + customMessageInfo->msgTableSize;
        m_MsgTableInfo = new uint8_t[msgTableInfoSize];

        // When calculating the offset the the message table information, we are assuming that the message header is
        // followed by the entry information for all of the languages in the seed data.

        uint32_t offset = m_Header->customTextHeaderOffset + customMessageInfo->msgIdTableOffset +
                          ( sizeof( CustomMessageEntryInfo ) * languageIndex ) + sizeof( CustomMessageHeaderInfo );

        // Copy the data to the pointers
        memcpy( m_MsgTableInfo, &data[offset], msgTableInfoSize );
        return true;
    }

}     // namespace mod::rando