#include "game_patch/game_patch.h"
#include "data/items.h"
#include "data/stages.h"
#include "tp/bmgres.h"
#include "main.h"
#include "tp/control.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/processor.h"
#include "tp/resource.h"
#include "tp/JKRArchivePub.h"
#include "gc_wii/OSCache.h"
#include "rando/customItems.h"

#ifdef TP_EU
#include "tp/d_s_logo.h"
#endif

#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <cinttypes>

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
        uint32_t infPtrRaw = reinterpret_cast<uint32_t>(libtp::tp::JKRArchivePub::JKRArchivePub_getGlbResource(
            0x524F4F54, // ROOT
            "zel_00.bmg",
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mMsgDtArchive[0]));

        // getGlbResource gets a pointer to MESGbmg1, but we need a pointer to INF1, which is just past MESGbmg1, and MESGbmg1
        // has a size of 0x20
        return reinterpret_cast<void*>(infPtrRaw + 0x20);
    }

    void* getInf1Ptr(const char* file)
    {
        uint32_t infPtrRaw = reinterpret_cast<uint32_t>(
            libtp::tp::JKRArchivePub::JKRArchivePub_getGlbResource(/* ROOT */ 0x524F4F54, file, nullptr));

        // getGlbResource gets a pointer to MESGbmg1, but we need a pointer to INF1, which is just past MESGbmg1, and MESGbmg1
        // has a size of 0x20
        return reinterpret_cast<void*>(infPtrRaw + 0x20);
    }

    const char* createString(const char* format, uint32_t size, ...)
    {
        // Make sure format and size are valid
        if (!format || (size == 0))
        {
            return nullptr;
        }

        static char buf[192];
        constexpr uint32_t maxIndex = sizeof(buf) - 1;
        uint32_t currentIndex = 0;

        va_list args;
        va_start(args, size);

        // Loop through each character in the format string
        for (uint32_t i = 0; i < (size - 1); i++)
        {
            // If currentIndex reaches the end of the buffer, then there is no more room for characters
            if (currentIndex >= maxIndex)
            {
                break;
            }

            // If the current character is NULL, then write it and go to the next character
            const char currentCharacter = format[i];
            if (currentCharacter == '\0')
            {
                buf[currentIndex++] = currentCharacter;
                continue;
            }

            // Handle all of the characters up to a NULL character
            const uint32_t currentMaxSize = sizeof(buf) - currentIndex;
            const int32_t len = vsnprintf(&buf[currentIndex], currentMaxSize, &format[i], args);

            // Make sure the characters were handled correctly
            if (len < 0) // Do not need to check if the correct amount of bytes were written
            {
                // Error occured
                snprintf(buf, sizeof(buf), "Error: String could not be\nwritten at index 0x%" PRIx32 ".", currentIndex);
                break;
            }

            // The characters were handled correctly
            // Assume that the NULL character was written as well, so it can be skipped in the loop
            // If not all characters were written, then currentIndex will be >= maxIndex, so the loop will end
            currentIndex += len + 1;
            i += strlen(&format[i]);
        }

        va_end(args);

        // Clear the cache for buf to be safe
        libtp::gc_wii::os_cache::DCFlushRange(buf, sizeof(buf));
        return buf;
    }

    const char* getSkyBookMessage(uint32_t msgId)
    {
        using namespace rando::customItems;

        // Check if this is for the individual characters or the Item Wheel description
        bool isForCharacter = false;
        if (msgId != 0x34D) // Item Wheel description
        {
            // Not for the Item Wheel description, so assume this is for the individual characters
            msgId = ITEM_TO_ID(Ancient_Sky_Book_First_Character);
            isForCharacter = true;
        }

        uint16_t msgSize;
        const char* format = _05_getMsgById(msgId, &msgSize);

        if (!format)
        {
            return nullptr;
        }

        // Figure out how many characters the player currently has
        uint32_t skyCharacterCount = 0;

        // If this is for the individual characters, then the flag for the current character won't update until the textbox has
        // closed, so add one
        if (isForCharacter)
        {
            skyCharacterCount++;
        }

        for (uint32_t i = 0; i < 5; i++)
        {
            if (!events::haveItem(Ancient_Sky_Book_First_Character + i))
            {
                break;
            }
            skyCharacterCount++;
        }

        return createString(format, msgSize, skyCharacterCount);
    }

    const char* getPoeSoulMessage()
    {
        using namespace libtp::data::items;

        uint16_t msgSize;
        const char* format = _05_getMsgById(ITEM_TO_ID(Poe_Soul), &msgSize);

        if (!format)
        {
            return nullptr;
        }

        // This project changes the poe count to increment after the message is displayed, so add one to get the new count
        uint32_t poeCount = libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect.poe_count + 1;
        return createString(format, msgSize, poeCount);
    };

#ifdef TP_EU
    bool __attribute__((noinline)) shouldGetTheText()
    {
        using namespace libtp::tp::d_s_logo;
        switch (currentLanguage)
        {
            case Languages::uk:
            default: // The language is invalid/unsupported, so the game defaults to English
            {
                return true;
            }
            case Languages::de:
            case Languages::fr:
            case Languages::sp:
            case Languages::it:
            {
                return false;
            }
        }
    }
#endif

    const char* getDungeonItemMessage(int32_t itemId)
    {
        using namespace libtp::data::items;
        using namespace rando::customItems;
#ifdef TP_EU
        using namespace libtp::tp::d_s_logo;
#endif
        // Get the text and size of the format text
        uint32_t itemIdForBase;
#ifdef TP_JP
        switch (itemId)
        {
            case Snowpeak_Ruins_Small_Key:
            case Snowpeak_Ruins_Compass:
            case Snowpeak_Ruins_Dungeon_Map:
            {
                // Snowpeak Ruins requires a special format string, since it's name uses a command
                // All of the Snowpeak Ruins items will use the Snowpeak Ruins small key text as a base
                itemIdForBase = Snowpeak_Ruins_Small_Key;
                break;
            }
            default:
            {
                // All of the items will use the Forest Temple small key text as a base
                itemIdForBase = Forest_Temple_Small_Key;
                break;
            }
        }
#else
        // All of the items will use the Forest Temple small key text as a base
        itemIdForBase = Forest_Temple_Small_Key;
#endif
        uint16_t msgSize;
        const char* format = _05_getMsgById(ITEM_TO_ID(itemIdForBase), &msgSize);
        if (!format)
        {
            return nullptr;
        }

        auto checkIfSnowpeakRuinsText = [&]()
        {
#ifdef TP_JP
            return static_cast<bool>(itemIdForBase == Snowpeak_Ruins_Small_Key);
#else
            return false;
#endif
        };

        // 'for' text is only used for some languages
        auto getForText = []()
        {
#ifdef TP_EU
            switch (currentLanguage)
            {
                case Languages::uk:
                case Languages::de:
                case Languages::it:
                default: // The language is invalid/unsupported, so the game defaults to English
                {
                    return true;
                }
                case Languages::fr:
                case Languages::sp:
                {
                    return false;
                }
            }
#elif defined TP_US
            return true;
#elif defined TP_JP
            // Shouldn't be necessary, but do anyway
            return false;
#endif
        };

        // 'the' text is only used for some languages
        auto getTheText = []()
        {
#ifdef TP_EU
            return shouldGetTheText();
#elif defined TP_US
            return true;
#elif defined TP_JP
            // Shouldn't be necessary, but do anyway
            return false;
#endif
        };

        // JP Snowpeak Ruins doesn't need anything from the next section as the colors are already defined in
        // the customMessage object in japaneseMessages.cpp
        const char* areaText = nullptr;
        bool addTheText;

        if (!checkIfSnowpeakRuinsText())
        {
            // Figure out what dungeon area this is for
            // Also figure out what color to use for each area name, as well as what areas should have 'the' infront
            // of them
            uint8_t areaColorId = MSG_COLOR_WHITE_HEX;
            uint32_t dungeonAreaMsgId;
            addTheText = false;

            switch (itemId)
            {
                case Forest_Temple_Small_Key:
                case Forest_Temple_Big_Key:
                case Forest_Temple_Compass:
                case Forest_Temple_Dungeon_Map:
                {
                    areaColorId = MSG_COLOR_GREEN_HEX;
                    dungeonAreaMsgId = SpecialMessageIds::FOREST_TEMPLE;
                    addTheText = getTheText();
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
                    addTheText = getTheText();
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
                    addTheText = getTheText();
                    break;
                }
                case City_in_The_Sky_Small_Key:
                case City_in_The_Sky_Big_Key:
                case City_in_The_Sky_Compass:
                case City_in_The_Sky_Dungeon_Map:
                {
                    areaColorId = MSG_COLOR_YELLOW_HEX;
                    dungeonAreaMsgId = SpecialMessageIds::CITY_IN_THE_SKY;
                    addTheText = getTheText();
                    break;
                }
                case Palace_of_Twilight_Small_Key:
                case Palace_of_Twilight_Big_Key:
                case Palace_of_Twilight_Compass:
                case Palace_of_Twilight_Dungeon_Map:
                {
                    areaColorId = MSG_COLOR_PURPLE_HEX;
                    dungeonAreaMsgId = SpecialMessageIds::PALACE_OF_TWILIGHT;
                    addTheText = getTheText();
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
                    addTheText = getTheText();
                    break;
                }
                default:
                {
                    // Error occured somehow
                    return nullptr;
                }
            }

            // Get the text for the area
            areaText = _05_getMsgById(dungeonAreaMsgId);
            if (!areaText)
            {
                return nullptr;
            }

            // Replace the dungeon area color
            // Make sure the index was properly adjusted
            uint32_t colorIndex = dungeonItemAreaColorIndex;
            if (colorIndex != 0)
            {
                char* colorAddress = const_cast<char*>(&format[colorIndex]);
                *colorAddress = static_cast<char>(areaColorId);

                // Clear the cache for the changed character
                libtp::gc_wii::os_cache::DCFlushRange(colorAddress, sizeof(char));
            }
        }

        // Figure out what dungeon item this is for
        uint32_t dungeonItemMsgId;
        switch (itemId)
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
            {
                dungeonItemMsgId = SpecialMessageIds::SMALL_KEY;
                break;
            }
            case Forest_Temple_Big_Key:
            case Lakebed_Temple_Big_Key:
            case Arbiters_Grounds_Big_Key:
            case Temple_of_Time_Big_Key:
            case City_in_The_Sky_Big_Key:
            case Palace_of_Twilight_Big_Key:
            case Hyrule_Castle_Big_Key:
            {
                dungeonItemMsgId = SpecialMessageIds::BIG_KEY;
                break;
            }
            case Forest_Temple_Compass:
            case Goron_Mines_Compass:
            case Lakebed_Temple_Compass:
            case Arbiters_Grounds_Compass:
            case Snowpeak_Ruins_Compass:
            case Temple_of_Time_Compass:
            case City_in_The_Sky_Compass:
            case Palace_of_Twilight_Compass:
            case Hyrule_Castle_Compass:
            {
                dungeonItemMsgId = SpecialMessageIds::COMPASS;
                break;
            }
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
                dungeonItemMsgId = SpecialMessageIds::DUNGEON_MAP;
                break;
            }
            default:
            {
                // Error occured somehow
                return nullptr;
            }
        }

        // Get the text for the item
        const char* dungeonItemText = _05_getMsgById(dungeonItemMsgId);
        if (!dungeonItemText)
        {
            return nullptr;
        }
#ifndef TP_JP
        // Get the 'for' text
        const char* forText;
        if (getForText())
        {
            forText = _05_getMsgById(SpecialMessageIds::FOR);
            if (!forText)
            {
                return nullptr;
            }
        }
        else
        {
            forText = nullptr;
        }

        // Get the 'the' text
        const char* theText;
        if (addTheText)
        {
            theText = _05_getMsgById(SpecialMessageIds::THE);
            if (!theText)
            {
                return nullptr;
            }
        }
        else
        {
            theText = nullptr;
        }

        return createString(format, msgSize, dungeonItemText, forText, theText, areaText);
#else
        // Prevent the compiler from complaining about getForText and addTheText being unused
        (void)getForText();
        (void)addTheText;

        // JP doesn't use `for` nor `the` and the params are in a different order
        if (checkIfSnowpeakRuinsText())
        {
            return createString(format, msgSize, dungeonItemText);
        }
        else
        {
            return createString(format, msgSize, areaText, dungeonItemText);
        }
#endif
    }

    const char* getCustomMessage(uint32_t msgId)
    {
        using namespace libtp::data::items;
        using namespace rando::customItems;

        switch (msgId)
        {
            case ITEM_TO_ID(Forest_Temple_Small_Key):
            case ITEM_TO_ID(Goron_Mines_Small_Key):
            case ITEM_TO_ID(Lakebed_Temple_Small_Key):
            case ITEM_TO_ID(Arbiters_Grounds_Small_Key):
            case ITEM_TO_ID(Snowpeak_Ruins_Small_Key):
            case ITEM_TO_ID(Temple_of_Time_Small_Key):
            case ITEM_TO_ID(City_in_The_Sky_Small_Key):
            case ITEM_TO_ID(Palace_of_Twilight_Small_Key):
            case ITEM_TO_ID(Hyrule_Castle_Small_Key):
            case ITEM_TO_ID(Bulblin_Camp_Key):
            case ITEM_TO_ID(Forest_Temple_Big_Key):
            case ITEM_TO_ID(Lakebed_Temple_Big_Key):
            case ITEM_TO_ID(Arbiters_Grounds_Big_Key):
            case ITEM_TO_ID(Temple_of_Time_Big_Key):
            case ITEM_TO_ID(City_in_The_Sky_Big_Key):
            case ITEM_TO_ID(Palace_of_Twilight_Big_Key):
            case ITEM_TO_ID(Hyrule_Castle_Big_Key):
            case ITEM_TO_ID(Forest_Temple_Compass):
            case ITEM_TO_ID(Goron_Mines_Compass):
            case ITEM_TO_ID(Lakebed_Temple_Compass):
            case ITEM_TO_ID(Arbiters_Grounds_Compass):
            case ITEM_TO_ID(Snowpeak_Ruins_Compass):
            case ITEM_TO_ID(Temple_of_Time_Compass):
            case ITEM_TO_ID(City_in_The_Sky_Compass):
            case ITEM_TO_ID(Palace_of_Twilight_Compass):
            case ITEM_TO_ID(Hyrule_Castle_Compass):
            case ITEM_TO_ID(Forest_Temple_Dungeon_Map):
            case ITEM_TO_ID(Goron_Mines_Dungeon_Map):
            case ITEM_TO_ID(Lakebed_Temple_Dungeon_Map):
            case ITEM_TO_ID(Arbiters_Grounds_Dungeon_Map):
            case ITEM_TO_ID(Snowpeak_Ruins_Dungeon_Map):
            case ITEM_TO_ID(Temple_of_Time_Dungeon_Map):
            case ITEM_TO_ID(City_in_The_Sky_Dungeon_Map):
            case ITEM_TO_ID(Palace_of_Twilight_Dungeon_Map):
            case ITEM_TO_ID(Hyrule_Castle_Dungeon_Map):
            {
                return getDungeonItemMessage(ID_TO_ITEM(msgId));
            }
            case ITEM_TO_ID(Poe_Soul):
            case 0x4CE: // 20 Poe souls
            case 0x4CF: // 60 Poe souls
            {
                return getPoeSoulMessage();
            }
            case ITEM_TO_ID(Ancient_Sky_Book_First_Character):
            case ITEM_TO_ID(Ancient_Sky_Book_Second_Character):
            case ITEM_TO_ID(Ancient_Sky_Book_Third_Character):
            case ITEM_TO_ID(Ancient_Sky_Book_Fourth_Character):
            case ITEM_TO_ID(Ancient_Sky_Book_Fifth_Character):
            case 0x34D: // Sky Book Item Wheel description
            {
                return getSkyBookMessage(msgId);
            }
            default:
            {
                break;
            }
        }

        return _05_getMsgById(msgId);
    }

    void _05_setCustomItemMessage(libtp::tp::control::TControl* control, const void* TProcessor, uint16_t unk3, uint16_t msgId)
    {
        using namespace libtp::data::stage;
        using namespace libtp::data::items;
        using namespace rando::customItems;

        auto setMessageText = [=](const char* text)
        {
            // Only replace the message if a valid string was retrieved
            if (text)
            {
                control->msg = text;
                control->wMsgRender = text;
            }
        };

        // Get a pointer to the current BMG file being used
        // The pointer is to INF1
        const void* unk = libtp::tp::processor::getResource_groupID(TProcessor, unk3);
        if (!unk)
        {
            return;
        }
        const void* currentInf1 = *reinterpret_cast<void**>(reinterpret_cast<uint32_t>(unk) + 0xC);

        // Most text replacements are for zel_00.bmg, so check that first
        if (currentInf1 == getZel00BmgInf())
        {
            // If msgId is for a foolish item, then only use the value from the first one to avoid duplicate entries
            switch (ID_TO_ITEM(msgId))
            {
                case Foolish_Item_2:
                case Foolish_Item_3:
                case Foolish_Item_4:
                case Foolish_Item_5:
                case Foolish_Item_6:
                {
                    msgId = ITEM_TO_ID(Foolish_Item_1);
                    break;
                }
                default:
                {
                    break;
                }
            }

            const char* newMessage;
            if (msgId == 0x1369) // The custom message ID used for hints on custom signs
            {
                newMessage = _05_getSpecialMsgById(msgId);
            }
            else
            {
                newMessage = getCustomMessage(msgId);
            }

            setMessageText(newMessage);
            return;
        }

        // If the msg we are looking at is not in the zel_00.bmg, it may be a special case (hint, etc.)
        setMessageText(_05_getSpecialMsgById(msgId));
    }

    uint32_t _05_getCustomMsgColor(uint8_t colorId)
    {
        uint32_t newColorCode; // RGBA
        switch (colorId)
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

    const char* _05_getMsgById(uint32_t msgId)
    {
        return _05_getMsgById(msgId, nullptr);
    }

    const char* _05_getMsgById(uint32_t msgId, uint16_t* msgSizeOut)
    {
        using namespace libtp::data::items;

        // If there are any special message IDs that require additional logic, we handle them here.
        switch (msgId)
        {
            case ITEM_TO_ID(Big_Wallet):   // Big Wallet Item Get Text
            case ITEM_TO_ID(Giant_Wallet): // Giant Wallet Item Get Text
            case 0x298:                    // Small Wallet Pause Menu Text
            case 0x299:                    // Big Wallet Pause Menu Text
            case 0x29A:                    // Giant Wallet Pause Menu Text
            {
                if (!walletsPatched)
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
        const uint32_t msgTableInfoRaw = reinterpret_cast<uint32_t>(m_MsgTableInfo);
        if (!msgTableInfoRaw)
        {
            return nullptr;
        }

        // Get a pointer to the message ids to search for
        const uint16_t* msgIds = reinterpret_cast<uint16_t*>(msgTableInfoRaw);

        // Get the total size of the message ids
        const uint32_t totalMessages = m_TotalMsgEntries;
        uint32_t msgIdTableSize = totalMessages * sizeof(uint16_t);

        // Round msgIdTableSize up to the size of the offset type to make sure the offsets are properly aligned
        msgIdTableSize = (msgIdTableSize + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);

        // Get a pointer to the message offsets
        const uint32_t* msgOffsets = reinterpret_cast<uint32_t*>(msgTableInfoRaw + msgIdTableSize);

        // Get the total size of the message offsets
        const uint32_t msgOffsetTableSize = totalMessages * sizeof(uint32_t);

        // Get a pointer to the messages
        const char* messages = reinterpret_cast<const char*>(msgTableInfoRaw + msgIdTableSize + msgOffsetTableSize);

        // Get the custom message
        for (uint32_t i = 0; i < totalMessages; i++)
        {
            if (msgIds[i] == msgId)
            {
                const char* currentMsg = &messages[msgOffsets[i]];

                if (msgSizeOut)
                {
                    *msgSizeOut = static_cast<uint16_t>(&messages[msgOffsets[i + 1]] - currentMsg);
                }

                return currentMsg;
            }
        }

        // Didn't find msgId
        return nullptr;
    }

    const char* _05_getSpecialMsgById(uint32_t msgId)
    {
        using namespace rando;

        // Make sure the hints text is loaded
        const uint32_t hintMsgTableInfoRaw = reinterpret_cast<uint32_t>(m_HintMsgTableInfo);
        if (!hintMsgTableInfoRaw)
        {
            return nullptr;
        }

        // Get some variables now to avoid storing extra stuff on the stack, since a function call is necessary to get one of
        // the variables
        const libtp::tp::d_stage::dStage_startStage* startStagePtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage;

        const char* currentStage = startStagePtr->mStage;
        const int32_t currentRoom = libtp::tools::getCurrentRoomNo();
        const int32_t stageIDX = libtp::tools::getStageIndex(currentStage);

        // Get the total size of the message ids
        const uint32_t hintTotalMessages = m_TotalHintMsgEntries;
        uint32_t msgIdTableSize = hintTotalMessages * sizeof(CustomMessageData);

        // Round msgIdTableSize up to the size of the offset type to make sure the offsets are properly aligned
        msgIdTableSize = (msgIdTableSize + sizeof(uint32_t) - 1) & ~(sizeof(uint32_t) - 1);

        // Get a pointer to the message offsets
        const uint32_t* hintMsgOffsets = reinterpret_cast<uint32_t*>(hintMsgTableInfoRaw + msgIdTableSize);

        // Get the total size of the message offsets
        const uint32_t hintMsgOffsetTableSize = hintTotalMessages * sizeof(uint32_t);

        // Get a pointer to the messages
        const char* hintMessages = reinterpret_cast<const char*>(hintMsgTableInfoRaw + msgIdTableSize + hintMsgOffsetTableSize);

        // Get a pointer to the message data to search for
        const CustomMessageData* msgData = reinterpret_cast<CustomMessageData*>(hintMsgTableInfoRaw);

        // Get the custom message
        for (uint32_t i = 0; i < hintTotalMessages; i++)
        {
            const CustomMessageData* currentMsgData = &msgData[i];

            if (currentMsgData->msgID == msgId)
            {
                if (((stageIDX == currentMsgData->stageIDX) && (currentRoom == currentMsgData->roomIDX)) ||
                    (currentMsgData->stageIDX == 0xFF))
                {
                    return &hintMessages[hintMsgOffsets[i]];
                }
            }
        }

        // Didn't find msgId
        return nullptr;
    }
} // namespace mod::game_patch