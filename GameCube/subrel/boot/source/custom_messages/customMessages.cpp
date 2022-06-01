#include "customMessages.h"
#include "tp/d_s_logo.h"
#include "main.h"

#include <cstdint>
#include <cstring>

namespace mod::customMessages
{
    void createMsgTable()
    {
        using namespace libtp::tp::d_s_logo;

        // Get the MsgEntry to use
        const MsgEntry* entries;
#ifdef TP_US
        entries = entriesUs;
#elif defined TP_JP
        entries = entriesJp;
#elif defined TP_EU
        Languages lang = getPalLanguage2( nullptr );
        switch ( lang )
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
        uint8_t* buf = new uint8_t[messageIdsSize + messageOffsetsSize + totalMessagesSize];

        // Get the address for the ids
        uint16_t* msgIdTable = reinterpret_cast<uint16_t*>( buf );

        // Get the address for the offsets
        uint32_t bufRaw = reinterpret_cast<uint32_t>( buf );
        uint32_t* msgOffsetTable = reinterpret_cast<uint32_t*>( bufRaw + messageIdsSize );

        // Get the address for the messages
        char* msgTable = reinterpret_cast<char*>( bufRaw + messageIdsSize + messageOffsetsSize );

        // Write the data to the table
        uint32_t msgTableWrittenSize = 0;
        for ( uint32_t i = 0; i < TOTAL_CUSTOM_MESSAGES; i++ )
        {
            const MsgEntry* entry = &entries[i];

            msgIdTable[i] = entry->id;
            msgOffsetTable[i] = msgTableWrittenSize;

            // Must use memcpy instead of strncpy since message commands have null characters
            uint32_t entrySize = entry->size;
            memcpy( &msgTable[msgTableWrittenSize], entry->msg, entrySize );

            // Increment msgTableWrittenSize to go to the next string
            msgTableWrittenSize += entrySize;
        }

        // Assign the buffer and total entries
        m_MsgTableInfo = buf;
        m_TotalMsgEntries = TOTAL_CUSTOM_MESSAGES;
    }
}     // namespace mod::customMessages