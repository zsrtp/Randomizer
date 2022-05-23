#include <cstring>

#include "data/items.h"
#include "data/stages.h"
#include "game_patch/00_customItemMessages.h"
#include "game_patch/game_patch.h"
#include "gc_wii/bmgres.h"
#include "main.h"
#include "tp/control.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_kankyo.h"
#include "tp/processor.h"

namespace mod::game_patch
{
    int32_t getItemIdFromMsgId( const void* TProcessor, uint16_t unk3, uint32_t msgId )
    {
        void* unk = libtp::tp::processor::getResource_groupID( TProcessor, unk3 );
        if ( !unk )
        {
            return -1;
        }

        libtp::gc::bmgres::TextIndexTable* textIndexTable =
            *reinterpret_cast<libtp::gc::bmgres::TextIndexTable**>( reinterpret_cast<uint32_t>( unk ) + 0xC );

        libtp::gc::bmgres::MessageEntry* entry = &textIndexTable->entry[0];
        uint32_t loopCount = textIndexTable->numEntries;

        // Loop through the item IDs until msgId is found
        uint32_t itemId = libtp::data::items::Recovery_Heart;
        for ( uint32_t i = 0; i < loopCount; i++ )
        {
            uint16_t entryMessageId = entry->messageId;
            if ( entryMessageId == ( itemId + 0x64 ) )
            {
                if ( entryMessageId == msgId )
                {
                    return static_cast<int32_t>( itemId );
                }
                else
                {
                    itemId++;

                    // Make sure itemId is valid
                    if ( itemId > libtp::data::items::NullItem )
                    {
                        break;
                    }
                }
            }
            entry++;
        }

        // Didn't find the index
        return -1;
    }
    void _05_setCustomItemMessage( libtp::tp::control::TControl* control,
                                   const void* TProcessor,
                                   uint16_t unk3,
                                   uint16_t msgId,
                                   rando::Randomizer* randomizer )
    {
        using namespace libtp::data::items;
        // The current text is for an item
        auto setMessageText = []( libtp::tp::control::TControl* control, const char* text )
        {
            control->msg = text;
            control->wMsgRender = text;
        };

        const char* newMessage = _05_getMsgById( randomizer, msgId );
        // Only replace the message if we get a valid string returned.
        if ( newMessage )
        {
            setMessageText( control, newMessage );
        }
    }

    uint32_t _05_getCustomMsgColor( uint8_t colorId )
    {
        uint32_t newColorCode;     // RGBA
        switch ( colorId )
        {
            case CUSTOM_MSG_COLOR_DARK_GREEN_HEX:
            {
                newColorCode = 0x4BBE4BFF;
                break;
            }
            case CUSTOM_MSG_COLOR_BLUE_HEX:
            {
                newColorCode = 0x4B96D7FF;
                break;
            }
            case CUSTOM_MSG_COLOR_SILVER_HEX:
            {
                newColorCode = 0xBFBFBFFF;
                break;
            }
            default:
            {
                // Return the color white if there is not a match
                newColorCode = 0xFFFFFFFF;
                break;
            }
        }
        return newColorCode;
    }

    const char** _05_replaceMessageString( const char** text )
    {
        const char* replacementText;
        if ( strncmp( *text, talkToMidnaText, strlen( talkToMidnaText ) ) == 0 )
        {
            // If it is day/night set the text to reflect the current time.

            if ( ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.skyAngle >= 284 ) ||
                 ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.skyAngle <= 104 ) )
            {
                replacementText = { "Wait until day" };
            }
            else
            {
                replacementText = { "Wait until night" };
            }
            *text = replacementText;
        }
        else if ( strncmp( *text, smallDonationText, strlen( smallDonationText ) ) == 0 )
        {
            if ( libtp::tp::d_a_alink::checkStageName(
                     libtp::data::stage::allStages[libtp::data::stage::stageIDs::Castle_Town] ) &&
                 libtp::tp::d_kankyo::env_light.currentRoom == 2 )
            {
                replacementText = {
                    "100 Rupees"
                    "\x0A\x1A\x06\x00\x00\x09\x02"
                    "50 Rupees"
                    "\x0A\x1A\x06\x00\x00\x09\x03"
                    "Sorry" };
                *text = replacementText;
            }
        }
        return text;
    }

    const char* _05_getMsgById( rando::Randomizer* randomizer, uint32_t msgId )
    {
        // Make sure the randomizer is loaded/enabled
        if ( !randoIsEnabled( randomizer ) )
        {
            return nullptr;
        }

        // Make sure the seed data is loaded
        rando::Seed* seed = randomizer->m_Seed;
        if ( !seed )
        {
            return nullptr;
        }

        // Make sure the custom text is loaded
        uint32_t msgTableInfoRaw = reinterpret_cast<uint32_t>( seed->m_MsgTableInfo );
        if ( !msgTableInfoRaw )
        {
            return nullptr;
        }

        // Get a pointer to the message ids to search for
        uint16_t* msgIds = reinterpret_cast<uint16_t*>( msgTableInfoRaw );

        // Get the total size of the message ids
        uint32_t totalMessages = seed->m_TotalMsgEntries;
        uint32_t msgIdTableSize = totalMessages * sizeof( uint16_t );

        // Round msgIdTableSize up to the size of the offset type to make sure the offsets are properly aligned
        msgIdTableSize = ( msgIdTableSize + sizeof( uint32_t ) - 1 ) & ~( sizeof( uint32_t ) - 1 );

        // Get a pointer to the message offsets
        uint32_t* msgOffsets = reinterpret_cast<uint32_t*>( msgTableInfoRaw + msgIdTableSize );

        // Get the total size of the message offsets
        uint32_t msgOffsetTableSize = totalMessages * sizeof( uint32_t );

        // Get a pointer to the messages
        const char* messages = reinterpret_cast<const char*>( msgTableInfoRaw + msgIdTableSize + msgOffsetTableSize );

        // Get the custom message
        for ( uint32_t i = 0; i < totalMessages; i++ )
        {
            if ( msgIds[i] == msgId )
            {
                mod::console << reinterpret_cast<void*>(msgTableInfoRaw) << "\n";
                mod::console << &messages << "\n";
                return &messages[msgOffsets[i]];
            }
        }

        // Didn't find msgId
        return nullptr;
    }
}     // namespace mod::game_patch