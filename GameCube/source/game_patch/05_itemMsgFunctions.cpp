#include "game_patch/game_patch.h"
#include "data/items.h"
#include "data/stages.h"
#include "gc_wii/bmgres.h"
#include "main.h"
#include "tp/control.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/processor.h"
#include "tp/resource.h"
#include "tp/JKRArchivePub.h"
#include "gc_wii/OSCache.h"

#include <cstring>
#include <cstdarg>

namespace mod::game_patch
{
    KEEP_VAR uint8_t dungeonItemAreaColorIndex = 0;

    /*
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
    */

    // Most checks will use zel_00.bmg, so use a dedicated function for it that specifies the archive, so less code runs per
    // check
    void* getZel00BmgInf()
    {
        uint32_t infPtrRaw = reinterpret_cast<uint32_t>( libtp::tp::JKRArchivePub::JKRArchivePub_getGlbResource(
            0x524F4F54,     // ROOT
            "zel_00.bmg",
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mMsgDtArchive[0] ) );

        // getGlbResource gets a pointer to MESGbmg1, but we need a pointer to INF1, which is just past MESGbmg1, and MESGbmg1
        // has a size of 0x20
        return reinterpret_cast<void*>( infPtrRaw + 0x20 );
    }

    void* getInf1Ptr( const char* file )
    {
        uint32_t infPtrRaw = reinterpret_cast<uint32_t>(
            libtp::tp::JKRArchivePub::JKRArchivePub_getGlbResource( /* ROOT */ 0x524F4F54, file, nullptr ) );

        // getGlbResource gets a pointer to MESGbmg1, but we need a pointer to INF1, which is just past MESGbmg1, and MESGbmg1
        // has a size of 0x20
        return reinterpret_cast<void*>( infPtrRaw + 0x20 );
    }

    // Assume that all variadic params will be strings
    const char* mergeStrings( const char* format, uint32_t size, ... )
    {
        static char buf[160];
        constexpr uint32_t maxLength = sizeof( buf ) - 1;

        char* tempBuf = buf;
        uint32_t currentIndex = 0;

        va_list args;
        va_start( args, size );

        // Loop through each character
        for ( uint32_t i = 0; i < ( size - 1 ); i++ )
        {
            // If currentIndex reaches the end of the buffer, then break
            if ( currentIndex >= maxLength )
            {
                break;
            }

            char currentCharacter = format[i];

            // Handle specifier
            if ( currentCharacter == '%' )
            {
                bool exitIf = false;
                switch ( format[i + 1] )     // Current specifier
                {
                    case 's':
                    {
                        break;
                    }
                    case '\0':
                    {
                        // The string ends after the %
                        exitIf = true;
                        break;
                    }
                    default:
                    {
                        // The specifier is not a string, so just write the raw character
                        exitIf = true;
                        tempBuf[currentIndex++] = currentCharacter;
                        break;
                    }
                }

                if ( !exitIf )
                {
                    // Get the length of the current string to write
                    const char* currentString = va_arg( args, const char* );
                    int32_t len = strlen( currentString );

                    // Make sure the string will not overflow the buffer
                    uint32_t endingIndex = len + currentIndex;
                    if ( endingIndex < maxLength )
                    {
                        // String will not overflow, so write it
                        strcpy( &tempBuf[currentIndex], currentString );
                        currentIndex = endingIndex;
                        i++;
                    }
                    else
                    {
                        // String will overflow
                        strcpy( tempBuf, "Error: currentString will overflow the buffer." );
                        return tempBuf;
                    }
                }
            }
            else
            {
                // Write the current char
                tempBuf[currentIndex++] = currentCharacter;
            }
        }

        va_end( args );

        // Ensure currentIndex is valid
        if ( currentIndex > maxLength )
        {
            currentIndex = maxLength;
        }

        // Ensure the buffer is NULL terminated
        tempBuf[currentIndex] = '\0';
        return tempBuf;
    }

    const char* getCustomMessage( rando::Randomizer* randomizer, uint16_t msgId )
    {
        using namespace libtp::data::items;

        const char* format;
        uint16_t msgSize;

        // Check for item text first
        int32_t itemId = ID_TO_ITEM( msgId );
        if ( ( itemId >= 0 ) && ( itemId <= 255 ) )
        {
            switch ( itemId )
            {
                case Forest_Temple_Small_Key:
                case Goron_Mines_Small_Key:
                case Lakebed_Temple_Small_Key:
                case Arbiters_Grounds_Small_Key:
                case Snowpeak_Ruins_Small_Key:
                case Temple_of_Time_Small_Key:
                case City_in_The_Sky_Small_Key:
                case Palace_of_Twilight_Small_Key:
                case Hyrule_Castle_Small_Key:
                case Bulblin_Camp_Key:
                case Forest_Temple_Big_Key:
                case Lakebed_Temple_Big_Key:
                case Arbiters_Grounds_Big_Key:
                case Temple_of_Time_Big_Key:
                case City_in_The_Sky_Big_Key:
                case Palace_of_Twilight_Big_Key:
                case Hyrule_Castle_Big_Key:
                case Forest_Temple_Compass:
                case Goron_Mines_Compass:
                case Lakebed_Temple_Compass:
                case Arbiters_Grounds_Compass:
                case Snowpeak_Ruins_Compass:
                case Temple_of_Time_Compass:
                case City_in_The_Sky_Compass:
                case Palace_of_Twilight_Compass:
                case Hyrule_Castle_Compass:
                case Forest_Temple_Dungeon_Map:
                case Goron_Mines_Dungeon_Map:
                case Lakebed_Temple_Dungeon_Map:
                case Arbiters_Grounds_Dungeon_Map:
                case Snowpeak_Ruins_Dungeon_Map:
                case Temple_of_Time_Dungeon_Map:
                case City_in_The_Sky_Dungeon_Map:
                case Palace_of_Twilight_Dungeon_Map:
                case Hyrule_Castle_Dungeon_Map:
                {
                    // Get the text and size of the format text
                    // All of these items will use the Forest Temple small key text as a base
                    format = _05_getMsgById( randomizer, ITEM_TO_ID( Forest_Temple_Small_Key ), &msgSize );
                    if ( !format )
                    {
                        return nullptr;
                    }

                    // Figure out what dungeon item this is for
                    uint32_t dungeonItemMsgId;
                    if ( ( itemId >= Forest_Temple_Small_Key ) && ( itemId <= Bulblin_Camp_Key ) )
                    {
                        dungeonItemMsgId = SpecialMessageIds::SMALL_KEY;
                    }
                    else if ( ( itemId >= Forest_Temple_Big_Key ) && ( itemId <= Hyrule_Castle_Big_Key ) )
                    {
                        dungeonItemMsgId = SpecialMessageIds::BIG_KEY;
                    }
                    else if ( ( ( itemId >= Forest_Temple_Compass ) && ( itemId <= Lakebed_Temple_Compass ) ) ||
                              ( ( itemId >= Arbiters_Grounds_Compass ) && ( itemId <= Hyrule_Castle_Compass ) ) )
                    {
                        dungeonItemMsgId = SpecialMessageIds::COMPASS;
                    }
                    else if ( ( itemId >= Forest_Temple_Dungeon_Map ) && ( itemId <= Hyrule_Castle_Dungeon_Map ) )
                    {
                        dungeonItemMsgId = SpecialMessageIds::DUNGEON_MAP;
                    }
                    else
                    {
                        // Error occured somehow
                        return nullptr;
                    }

                    // Figure out what dungeon area this is for
                    // Also figure out what color to use for each area name, as well as what areas should have 'the' infront of
                    // them
                    uint8_t areaColorId = MSG_COLOR_WHITE_HEX;
                    uint32_t dungeonAreaMsgId;
                    bool addTheText = false;

                    switch ( itemId )
                    {
                        case Forest_Temple_Small_Key:
                        case Forest_Temple_Big_Key:
                        case Forest_Temple_Compass:
                        case Forest_Temple_Dungeon_Map:
                        {
                            areaColorId = MSG_COLOR_GREEN_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::FOREST_TEMPLE;
                            addTheText = true;
                            break;
                        }
                        case Goron_Mines_Small_Key:
                        case Goron_Mines_Compass:
                        case Goron_Mines_Dungeon_Map:
                        {
                            areaColorId = MSG_COLOR_RED_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::GORON_MINES;
                            break;
                        }
                        case Lakebed_Temple_Small_Key:
                        case Lakebed_Temple_Big_Key:
                        case Lakebed_Temple_Compass:
                        case Lakebed_Temple_Dungeon_Map:
                        {
                            areaColorId = CUSTOM_MSG_COLOR_BLUE_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::LAKEBED_TEMPLE;
                            addTheText = true;
                            break;
                        }
                        case Arbiters_Grounds_Small_Key:
                        case Arbiters_Grounds_Big_Key:
                        case Arbiters_Grounds_Compass:
                        case Arbiters_Grounds_Dungeon_Map:
                        {
                            areaColorId = MSG_COLOR_ORANGE_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::ARBITERS_GROUNDS;
                            break;
                        }
                        case Snowpeak_Ruins_Small_Key:
                        case Snowpeak_Ruins_Compass:
                        case Snowpeak_Ruins_Dungeon_Map:
                        {
                            areaColorId = MSG_COLOR_LIGHT_BLUE_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::SNOWPEAK_RUINS;
                            break;
                        }
                        case Temple_of_Time_Small_Key:
                        case Temple_of_Time_Big_Key:
                        case Temple_of_Time_Compass:
                        case Temple_of_Time_Dungeon_Map:
                        {
                            areaColorId = CUSTOM_MSG_COLOR_DARK_GREEN_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::TEMPLE_OF_TIME;
                            addTheText = true;
                            break;
                        }
                        case City_in_The_Sky_Small_Key:
                        case City_in_The_Sky_Big_Key:
                        case City_in_The_Sky_Compass:
                        case City_in_The_Sky_Dungeon_Map:
                        {
                            areaColorId = MSG_COLOR_YELLOW_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::CITY_IN_THE_SKY;
                            addTheText = true;
                            break;
                        }
                        case Palace_of_Twilight_Small_Key:
                        case Palace_of_Twilight_Big_Key:
                        case Palace_of_Twilight_Compass:
                        case Palace_of_Twilight_Dungeon_Map:
                        {
                            areaColorId = MSG_COLOR_PURPLE_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::PALACE_OF_TWILIGHT;
                            addTheText = true;
                            break;
                        }
                        case Hyrule_Castle_Small_Key:
                        case Hyrule_Castle_Big_Key:
                        case Hyrule_Castle_Compass:
                        case Hyrule_Castle_Dungeon_Map:
                        {
                            areaColorId = CUSTOM_MSG_COLOR_SILVER_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::HYRULE_CASTLE;
                            break;
                        }
                        case Bulblin_Camp_Key:
                        {
                            areaColorId = MSG_COLOR_ORANGE_HEX;
                            dungeonAreaMsgId = SpecialMessageIds::BULBLIN_CAMP;
                            addTheText = true;
                            break;
                        }
                        default:
                        {
                            // Error occured somehow
                            return nullptr;
                        }
                    }

                    // Get the texts for the small key and area
                    const char* smallKeyText = _05_getMsgById( randomizer, dungeonItemMsgId );
                    if ( !smallKeyText )
                    {
                        return nullptr;
                    }

                    const char* areaText = _05_getMsgById( randomizer, dungeonAreaMsgId );
                    if ( !areaText )
                    {
                        return nullptr;
                    }

                    // Get the 'the' text
                    const char* theText;
                    if ( addTheText )
                    {
                        theText = _05_getMsgById( randomizer, SpecialMessageIds::THE );
                        if ( !theText )
                        {
                            return nullptr;
                        }
                    }
                    else
                    {
                        theText = "";
                    }

                    // Replace the dungeon area color
                    char* colorAddress = const_cast<char*>( &format[dungeonItemAreaColorIndex] );
                    *colorAddress = static_cast<char>( areaColorId );

                    // Clear the cache for the entire format string to be safe
                    libtp::gc_wii::os_cache::DCFlushRange( const_cast<char*>( format ), msgSize );

                    return mergeStrings( format, msgSize, smallKeyText, theText, areaText );
                }
                default:
                {
                    break;
                }
            }
        }
        else
        {
            // Generic checks here
        }

        return _05_getMsgById( randomizer, msgId );
    }

    void _05_setCustomItemMessage( libtp::tp::control::TControl* control,
                                   const void* TProcessor,
                                   uint16_t unk3,
                                   uint16_t msgId,
                                   rando::Randomizer* randomizer )
    {
        using namespace libtp::data::stage;
        using namespace libtp::data::items;

        auto setMessageText = [=]( const char* text )
        {
            // Only replace the message if a valid string was retrieved
            if ( text )
            {
                control->msg = text;
                control->wMsgRender = text;
            }
        };

        auto checkForSpecificMsg =
            [=]( uint16_t desiredMsgId, int32_t room, const char* stage, const void* currentInf1, const char* desiredFile )
        {
            // Check if the message ids are the same
            if ( msgId != desiredMsgId )
            {
                return false;
            }

            // Check if the stage and room are correct
            // Either or can be omitted
            if ( !libtp::tools::playerIsInRoomStage( room, stage ) )
            {
                return false;
            }

            // Check if the desired file is being used
            return currentInf1 == getInf1Ptr( desiredFile );
        };

        // Get message ids for specific checks
        constexpr uint16_t linkHouseMsgId = 0x658;
        constexpr uint16_t charloDonationMsgId = 0x355;

        // Get a pointer to the current BMG file being used
        // The pointer is to INF1
        const void* unk = libtp::tp::processor::getResource_groupID( TProcessor, unk3 );
        if ( !unk )
        {
            return;
        }
        const void* currentInf1 = *reinterpret_cast<void**>( reinterpret_cast<uint32_t>( unk ) + 0xC );

        rando::Seed* seed;

        // Most text replacements are for zel_00.bmg, so check that first
        if ( currentInf1 == getZel00BmgInf() )
        {
            // If msgId is for a foolish item, then only use the value from the first one to avoid duplicate entries
            switch ( ID_TO_ITEM( msgId ) )
            {
                case Foolish_Item_2:
                case Foolish_Item_3:
                case Foolish_Item_4:
                case Foolish_Item_5:
                case Foolish_Item_6:
                {
                    msgId = ITEM_TO_ID( Foolish_Item_1 );
                    break;
                }
                default:
                {
                    break;
                }
            }

            const char* newMessage = getCustomMessage( randomizer, msgId );
            setMessageText( newMessage );
            return;
        }
        else if ( checkForSpecificMsg( charloDonationMsgId, 2, allStages[stageIDs::Castle_Town], currentInf1, "zel_04.bmg" ) )
        {
            setMessageText( m_DonationText );
            return;
        }

        // Make sure the randomizer is loaded/enabled and a seed is loaded for seed-specific checks
        else if ( seed = getCurrentSeed( randomizer ), seed )
        {
            if ( checkForSpecificMsg( linkHouseMsgId, 1, allStages[stageIDs::Ordon_Village], currentInf1, "zel_01.bmg" ) )
            {
                setMessageText( seed->m_RequiredDungeons );
                return;
            }
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

    const char* _05_getMsgById( rando::Randomizer* randomizer, uint32_t msgId )
    {
        return _05_getMsgById( randomizer, msgId, nullptr );
    }

    const char* _05_getMsgById( rando::Randomizer* randomizer, uint32_t msgId, uint16_t* sizeOut )
    {
        using namespace libtp::data::items;

        // Make sure the randomizer is loaded/enabled
        if ( !randoIsEnabled( randomizer ) )
        {
            return nullptr;
        }

        // If there are any special message IDs that require additional logic, we handle them here.
        switch ( msgId )
        {
            case ITEM_TO_ID( Big_Wallet ):       // Big Wallet Item Get Text
            case ITEM_TO_ID( Giant_Wallet ):     // Giant Wallet Item Get Text
            case 0x298:                          // Small Wallet Pause Menu Text
            case 0x299:                          // Big Wallet Pause Menu Text
            case 0x29A:                          // Giant Wallet Pause Menu Text
            {
                if ( !walletsPatched )
                {
                    return nullptr;
                }
                break;
            }
            case 0xFFFF:
            {
                // This is a special entry that is added to the very end of the messages, and is only included to make sure that
                // sizeOut can be properly calculated. It should never be used for anything else.
                return nullptr;
            }
            default:
            {
                break;
            }
        }

        // Make sure the custom text is loaded
        uint32_t msgTableInfoRaw = reinterpret_cast<uint32_t>( m_MsgTableInfo );
        if ( !msgTableInfoRaw )
        {
            return nullptr;
        }

        // Get a pointer to the message ids to search for
        uint16_t* msgIds = reinterpret_cast<uint16_t*>( msgTableInfoRaw );

        // Get the total size of the message ids
        uint32_t totalMessages = m_TotalMsgEntries;
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
                const char* currentMsg = &messages[msgOffsets[i]];

                if ( sizeOut )
                {
                    *sizeOut = static_cast<uint16_t>( &messages[msgOffsets[i + 1]] - currentMsg );
                }

                return currentMsg;
            }
        }

        // Didn't find msgId
        return nullptr;
    }
}     // namespace mod::game_patch