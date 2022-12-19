#include "customMessages.h"
#include "main.h"
#include "cxx.h"
#include "game_patch/game_patch.h"

#ifdef TP_EU
#include "tp/d_s_logo.h"
#endif

#include <cstdint>
#include <cstring>

namespace mod::customMessages
{
#ifdef TP_EU
    using namespace libtp::tp::d_s_logo;
    Languages currentLanguage = getPalLanguage2( nullptr );
#endif
    void createMsgTable()
    {
        // Get the MsgEntry to use
        const MsgEntry* entries;
#ifdef TP_US
        game_patch::dungeonItemAreaColorIndex = 57;
        entries = entriesUs;
#elif defined TP_JP
        entries = entriesJp;
#elif defined TP_EU
        switch ( currentLanguage )
        {
            case Languages::uk:
            default:     // The language is invalid/unsupported, so the game defaults to English
            {
                entries = entriesUs;
                break;
            }
            case Languages::de:
            {
                entries = entriesDe;
                break;
            }
            case Languages::fr:
            {
                entries = entriesFr;
                break;
            }
            case Languages::it:
            {
                entries = entriesIt;
                break;
            }
            case Languages::sp:
            {
                entries = entriesSp;
                break;
            }
        }
#endif
        // Get the total size to allocate for the table
        // Get the space used by the message ids
        uint32_t messageIdsSize = TOTAL_CUSTOM_MESSAGES * sizeof( uint16_t );

        // Round messageIdsSize up to the size of the offsets to make sure the offsets are properly aligned
        messageIdsSize = ( messageIdsSize + sizeof( uint32_t ) - 1 ) & ~( sizeof( uint32_t ) - 1 );

        // Get the space used by the message offsets
        uint32_t messageOffsetsSize = TOTAL_CUSTOM_MESSAGES * sizeof( uint32_t );

        // Get the total size of all of the strings
        uint32_t totalMessagesSize = 0;
        for ( uint32_t i = 0; i < TOTAL_CUSTOM_MESSAGES; i++ )
        {
            totalMessagesSize += entries[i].size;
        }

        // Allocate memory for the table
        // Align to uint32_t, as it is the largest variable type used in the table
        uint8_t* buf = new ( sizeof( uint32_t ) ) uint8_t[messageIdsSize + messageOffsetsSize + totalMessagesSize];

        // Get the address for the ids
        uint16_t* msgIdTable = reinterpret_cast<uint16_t*>( buf );

        // Get the address for the offsets
        uint32_t bufRaw = reinterpret_cast<uint32_t>( buf );
        uint32_t* msgOffsetTable = reinterpret_cast<uint32_t*>( bufRaw + messageIdsSize );

        // Get the address for the messages
        char* msgTable = reinterpret_cast<char*>( bufRaw + messageIdsSize + messageOffsetsSize );

        // Write the dataSrc to the table
        uint32_t msgTableWrittenSize = 0;
        for ( uint32_t i = 0; i < TOTAL_CUSTOM_MESSAGES; i++ )
        {
            const MsgEntry* entry = &entries[i];

            msgIdTable[i] = entry->id;
            msgOffsetTable[i] = msgTableWrittenSize;

            // Must use memcpy instead of strncpy since message commands have NULL characters
            uint32_t entrySize = entry->size;
            memcpy( &msgTable[msgTableWrittenSize], entry->msg, entrySize );

            // Increment msgTableWrittenSize to go to the next string
            msgTableWrittenSize += entrySize;
        }

        // Assign the buffer and total entries
        m_MsgTableInfo = buf;
        m_TotalMsgEntries = TOTAL_CUSTOM_MESSAGES;
    }

    void createItemWheelMenuData()
    {
        using namespace item_wheel_menu;

        // Get the ItemWheelMenuData and itemWheeleStringsSize to use
        const ItemWheelMenuStrings* stringsSrc;
        const ItemWheelMenuOffsets* offsetsSrc;
#ifdef TP_US
        stringsSrc = &itemWheelMenuStringsUs;
        offsetsSrc = &itemWheelMenuOffsetsUs;
#elif defined TP_JP
        stringsSrc = &itemWheelMenuStringsJp;
        offsetsSrc = &itemWheelMenuOffsetsJp;
#elif defined TP_EU
        switch ( currentLanguage )
        {
            case Languages::uk:
            default:     // The language is invalid/unsupported, so the game defaults to English
            {
                stringsSrc = &itemWheelMenuStringsUs;
                offsetsSrc = &itemWheelMenuOffsetsUs;
                break;
            }
            case Languages::de:
            {
                stringsSrc = &itemWheelMenuStringsDe;
                offsetsSrc = &itemWheelMenuOffsetsDe;
                break;
            }
            case Languages::fr:
            {
                stringsSrc = &itemWheelMenuStringsFr;
                offsetsSrc = &itemWheelMenuOffsetsFr;
                break;
            }
            case Languages::it:
            {
                stringsSrc = &itemWheelMenuStringsIt;
                offsetsSrc = &itemWheelMenuOffsetsIt;
                break;
            }
            case Languages::sp:
            {
                stringsSrc = &itemWheelMenuStringsSp;
                offsetsSrc = &itemWheelMenuOffsetsSp;
                break;
            }
        }
#endif
        // Get the total length used for the strings
        // The menu strings struct should only contain const char* pointers, so can just cast that to an array
        const char** menuStringsSrc = reinterpret_cast<const char**>( const_cast<ItemWheelMenuStrings*>( stringsSrc ) );
        constexpr uint32_t menuStringsEntries = sizeof( struct ItemWheelMenuStrings ) / sizeof( const char* );

        uint32_t totalStringsLength = 0;
        for ( uint32_t i = 0; i < menuStringsEntries; i++ )
        {
            totalStringsLength += strlen( menuStringsSrc[i] );
        }

        // Allocate memory for the strings
        // Add menuStringsEntries to account for each string being NULL terminated
        // Align to char, as strings don't have specific alignment requirements
        char* textData = new ( sizeof( char ) ) char[totalStringsLength + menuStringsEntries];

        // Set up itemWheelMenuData variables
        ItemWheelMenuData* dataDest = &itemWheelMenuData;

        // Set up the strings
        // The menu strings struct should only contain const char* pointers, so can just cast that to an array
        const char** menuStringsDest = reinterpret_cast<const char**>( &dataDest->strings );

        uint32_t writtenSize = 0;
        for ( uint32_t i = 0; i < menuStringsEntries; i++ )
        {
            // Set the current entry
            char* currentStringEntry = &textData[writtenSize];
            menuStringsDest[i] = currentStringEntry;

            // Copy the current string to textData
            const char* currentSrcEntry = menuStringsSrc[i];
            uint32_t currentSrcEntryLength = strlen( currentSrcEntry );
            strncpy( currentStringEntry, currentSrcEntry, currentSrcEntryLength );

            // Make sure the string is properly NULL terminated
            currentStringEntry[currentSrcEntryLength] = '\0';

            // Increment writtenSize to go to the next string
            // Add one to account for the NULL terminator
            writtenSize += currentSrcEntryLength + 1;
        }

        // Set up the offsets
        memcpy( &dataDest->offsets, offsetsSrc, sizeof( dataDest->offsets ) );

        // Assign textData
        dataDest->textData = textData;
    }

    void createCharloDonationMessage()
    {
        // Get the donation string to use
        using namespace customMessages;
        const MsgEntry* donationEntry;
#ifdef TP_US
        donationEntry = &charloDonationEntryUs;
#elif defined TP_JP
        donationEntry = &charloDonationEntryJp;
#elif defined TP_EU
        switch ( currentLanguage )
        {
            case Languages::uk:
            default:     // The language is invalid/unsupported, so the game defaults to English
            {
                donationEntry = &charloDonationEntryUs;
                break;
            }
            case Languages::de:
            {
                donationEntry = &charloDonationEntryDe;
                break;
            }
            case Languages::fr:
            {
                donationEntry = &charloDonationEntryFr;
                break;
            }
            case Languages::it:
            {
                donationEntry = &charloDonationEntryIt;
                break;
            }
            case Languages::sp:
            {
                donationEntry = &charloDonationEntrySp;
                break;
            }
        }
#endif
        // Allocate memory for the buffer and write the string
        // Must use memcpy instead of strncpy since message commands have NULL characters
        // Align to char, as strings don't have specific alignment requirements
        uint32_t donationEntrySize = donationEntry->size;
        char* buf = new ( sizeof( char ) ) char[donationEntrySize];
        memcpy( buf, donationEntry->msg, donationEntrySize );

        // Assign the buffer
        m_DonationText = buf;
    }
}     // namespace mod::customMessages