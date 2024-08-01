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
#include "cxx.h"
#include "game_patch/game_patch.h"
#include "main.h"
#include "rando/data.h"
#include "tools.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_item_data.h"
#include "user_patch/user_patch.h"
#include "gc_wii/OSInterrupt.h"

namespace mod::rando
{
    Seed::Seed(int32_t chan, SeedInfo* seedInfo): m_CardSlot(chan)
    {
        m_Header = &seedInfo->header;
        // Loading seed rando-dataX '<seed>'...

        // Store our filename index
        MinSeedInfo* minSeedInfo = seedInfo->minSeedInfo;
        m_fileIndex = minSeedInfo->fileIndex;

        const char* fileName = minSeedInfo->fileName;
        getConsole() << "Loading seed " << static_cast<int32_t>(m_fileIndex + 1) << ": '" << fileName << "'...\n";

        // Allocate the buffer to the back of the heap to prevent fragmentation
        uint32_t totalSize = minSeedInfo->totalSize;

        // Align to 0x20 for safety, since some functions may cast parts of it to classes/structs/arrays/etc.
        uint8_t* data = new (-0x20) uint8_t[totalSize];

        // Interrupts are required to be enabled for CARD/DVD functions to work properly
        bool enable = libtp::gc_wii::os_interrupt::OSEnableInterrupts();

#ifdef DVD
        // fileName does not contain the full file path
        char filePath[96];
        snprintf(filePath, sizeof(filePath), "/mod/seed/%s", fileName);

        m_CARDResult = libtp::tools::readFile(filePath, totalSize, 0, data);
        constexpr int32_t resultComparison = DVD_STATE_END;
#else
        // The memory card should already be mounted
        m_CARDResult = libtp::tools::readGCIMounted(m_CardSlot, fileName, totalSize, 0, data, true);
        constexpr int32_t resultComparison = CARD_RESULT_READY;
#endif
        // Restore interrupts
        libtp::gc_wii::os_interrupt::OSRestoreInterrupts(enable);

        if (m_CARDResult == resultComparison)
        {
            Header* headerPtr = m_Header;

            // Get the header data
            memcpy(headerPtr, data, sizeof(Header));

            // Get the main seed data
            // Align to 0x20 for safety, since some functions cast parts of it to classes/structs/arrays/etc.
            uint32_t dataSize = headerPtr->dataSize;
            m_GCIData = new (0x20) uint8_t[dataSize];
            memcpy(m_GCIData, &data[headerPtr->headerSize], dataSize);

            // Generate the BGM/Fanfare table data
            loadBgmData(data);
            m_CLR0 = reinterpret_cast<CLR0Header*>(m_GCIData + headerPtr->clr0Offset);
            m_RawRGBTable = reinterpret_cast<RawRGBTable*>(m_GCIData + headerPtr->clr0Offset + m_CLR0->rawRGBOffset);
            m_BmdEntries = reinterpret_cast<BMDEntry*>(m_GCIData + headerPtr->clr0Offset + m_CLR0->bmdEntriesOffset);

            // Load the custom text data
            this->loadCustomText(data);

            // Set the static pointers for the Seed Header and Data. These are used by TPO
            void** ptrTable = reinterpret_cast<void**>(0x800042BC);
            ptrTable[0] = m_Header;
            ptrTable[1] = m_GCIData;
        }
        delete[] data;
    }

    Seed::~Seed()
    {
        // Make sure to delete tempcheck buffers
        this->clearChecks();

        // Clear the static pointers for the Seed Header and Data.  These are used by TPO
        void** ptrTable = reinterpret_cast<void**>(0x800042BC);
        ptrTable[0] = nullptr;
        ptrTable[1] = nullptr;

        // Only work with m_GCIData if the buffer is populated
        if (m_GCIData)
        {
            this->applyOneTimePatches(false);

            // Last clear gcibuffer as other functions before rely on it
            delete[] m_GCIData;
        }

        // Clear the bgm table buffers
        delete[] m_BgmTable;
        delete[] m_FanfareTable;
    }

    void Seed::applyOneTimePatches(bool set)
    {
        using namespace libtp;

        uint32_t num_bytes = m_Header->oneTimePatchInfo.numEntries;
        uint32_t gci_offset = m_Header->oneTimePatchInfo.dataOffset;

        // Don't bother to patch anything if there's nothing to patch
        if (num_bytes > 0)
        {
            // Set the pointer as offset into our buffer
            uint8_t* patch_config = &m_GCIData[gci_offset];

            for (uint32_t i = 0; i < num_bytes; i++)
            {
                uint8_t byte = patch_config[i];

                for (uint32_t b = 0; b < 8; b++)
                {
                    if ((byte << b) & 0x80)
                    {
                        // Run the patch function for this bit index
                        uint32_t index = i * 8 + b;

                        if (index < sizeof(user_patch::oneTimePatches) / sizeof(user_patch::oneTimePatches[0]))
                        {
                            user_patch::oneTimePatches[index](mod::randomizer, set);
                            m_PatchesApplied++;
                        }
                    }
                }
            }
        }
    }

    void Seed::loadBgmData(uint8_t* data)
    {
        uint32_t headerOffset = m_Header->headerSize + m_Header->bgmHeaderOffset;

        // Get the Bgm Header
        BGMHeader* customBgmHeader = reinterpret_cast<BGMHeader*>(&data[headerOffset]);

        // Handle any bgm entries
        uint32_t bgmTableEntries = customBgmHeader->bgmTableNumEntries;
        if (bgmTableEntries > 0)
        {
            // Align to uint32_t, as the table is an array of structs with a size of 0x4 each
            uint32_t bgmTableSize = customBgmHeader->bgmTableSize;
            uint8_t* buf = new (sizeof(uint32_t)) uint8_t[bgmTableSize];
            uint32_t offset = headerOffset + customBgmHeader->bgmTableOffset;
            memcpy(buf, &data[offset], bgmTableSize);

            // Assign the entry count and buffer
            m_BgmTableEntries = static_cast<uint8_t>(bgmTableEntries);
            m_BgmTable = reinterpret_cast<BGMReplacement*>(buf);
        }

        // Handle any fanfare entries
        uint32_t fanfareTableEntries = customBgmHeader->fanfareTableNumEntries;
        if (fanfareTableEntries > 0)
        {
            // Align to uint32_t, as the table is an array of structs with a size of 0x4 each
            uint32_t fanfareTableSize = customBgmHeader->fanfareTableSize;
            uint8_t* buf = new (sizeof(uint32_t)) uint8_t[fanfareTableSize];
            uint32_t offset = headerOffset + customBgmHeader->fanfareTableOffset;
            memcpy(buf, &data[offset], fanfareTableSize);

            // Assign the entry count and buffer
            m_FanfareTableEntries = static_cast<uint8_t>(fanfareTableEntries);
            m_FanfareTable = reinterpret_cast<BGMReplacement*>(buf);
        }
    }

    void Seed::loadShuffledEntrances()
    {
        const entryInfo* shuffledEntranceInfo = &m_Header->EntranceTableInfo;
        const uint32_t num_shuffledEntrances = shuffledEntranceInfo->numEntries;
        const uint32_t gci_offset = shuffledEntranceInfo->dataOffset;

        // Set the pointer as offset into our buffer
        m_ShuffledEntrances = reinterpret_cast<ShuffledEntrance*>(&m_GCIData[gci_offset]);
        m_numShuffledEntrances = num_shuffledEntrances;
    }

    void Seed::loadCustomText(uint8_t* data)
    {
        const uint32_t headerOffset = m_Header->headerSize + m_Header->customTextHeaderOffset;

        // Get the custom message header
        const CustomMessageHeaderInfo* customMessageHeader = reinterpret_cast<CustomMessageHeaderInfo*>(&data[headerOffset]);

        // Allocate memory for the ids, message offsets, and messages
        m_TotalHintMsgEntries = customMessageHeader->totalEntries;
        uint32_t msgIdTableSize = m_TotalHintMsgEntries * sizeof(CustomMessageData);
        const uint32_t msgOffsetTableSize = m_TotalHintMsgEntries * sizeof(uint32_t);

        // Round msgIdTableSize up to the size of the offsets to make sure the offsets are properly aligned
        msgIdTableSize = (msgIdTableSize + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);
        const uint32_t msgTableInfoSize = msgIdTableSize + msgOffsetTableSize + customMessageHeader->msgTableSize;

        // Align to uint16_t, as thagt's the largest variable type in CustomMessageData
        m_HintMsgTableInfo = new (sizeof(uint16_t)) uint8_t[msgTableInfoSize];
        // When calculating the offset the the message table information, we are assuming that the message header is
        // followed by the entry information for all of the languages in the seed data.
        const uint32_t offset = headerOffset + customMessageHeader->msgIdTableOffset;

        // Copy the data to the pointers
        memcpy(m_HintMsgTableInfo, &data[offset], msgTableInfoSize);

        for (uint32_t i = msgIdTableSize + msgOffsetTableSize; i < msgTableInfoSize; i++)
        {
            m_HintMsgTableInfo[i] = ~m_HintMsgTableInfo[i];
        }
    }

} // namespace mod::rando