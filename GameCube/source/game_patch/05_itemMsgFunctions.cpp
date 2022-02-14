#include <cinttypes>
#include <cstring>

#include "data/items.h"
#include "game_patch/00_customItemMessages.h"
#include "game_patch/game_patch.h"
#include "gc/bmgres.h"
#include "main.h"
#include "tp/control.h"
#include "tp/d_a_alink.h"
#include "tp/d_item.h"
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
                                   uint16_t msgId )
    {
        using namespace libtp::data::items;
        // Check if the current text is for an item
        int32_t index = getItemIdFromMsgId( TProcessor, unk3, msgId );
        // The current text is for an item
        auto setMessageText = []( libtp::tp::control::TControl* control, const char* text )
        {
            control->msg = text;
            control->wMsgRender = text;
        };
        switch ( static_cast<uint32_t>( index ) )
        {
            case Forest_Temple_Small_Key:
            {
                setMessageText( control, customForestSKText );
                break;
            }
            case Forest_Temple_Dungeon_Map:
            {
                setMessageText( control, customForestMapText );
                break;
            }
            case Forest_Temple_Compass:
            {
                setMessageText( control, customForestCompassText );
                break;
            }
            case Forest_Temple_Big_Key:
            {
                setMessageText( control, customForestBigKeyText );
                break;
            }

            case Goron_Mines_Small_Key:
            {
                setMessageText( control, customMinesSKText );
                break;
            }
            case Goron_Mines_Dungeon_Map:
            {
                setMessageText( control, customMinesMapText );
                break;
            }
            case Goron_Mines_Compass:
            {
                setMessageText( control, customMinesCompassText );
                break;
            }

            case Lakebed_Temple_Small_Key:
            {
                setMessageText( control, customLakebedSKText );
                break;
            }
            case Lakebed_Temple_Dungeon_Map:
            {
                setMessageText( control, customLakebedMapText );
                break;
            }
            case Lakebed_Temple_Compass:
            {
                setMessageText( control, customLakebedCompassText );
                break;
            }
            case Lakebed_Temple_Big_Key:
            {
                setMessageText( control, customLakebedBigKeyText );
                break;
            }

            case Arbiters_Grounds_Small_Key:
            {
                setMessageText( control, customArbitersSKText );
                break;
            }
            case Arbiters_Grounds_Dungeon_Map:
            {
                setMessageText( control, customArbitersMapText );
                break;
            }
            case Arbiters_Grounds_Compass:
            {
                setMessageText( control, customArbitersCompassText );
                break;
            }
            case Arbiters_Grounds_Big_Key:
            {
                setMessageText( control, customArbitersBigKeyText );
                break;
            }

            case Snowpeak_Ruins_Small_Key:
            {
                setMessageText( control, customSnowpeakSKText );
                break;
            }
            case Snowpeak_Ruins_Dungeon_Map:
            {
                setMessageText( control, customSnowpeakMapText );
                break;
            }
            case Snowpeak_Ruins_Compass:
            {
                setMessageText( control, customSnowpeakCompassText );
                break;
            }

            case Temple_of_Time_Small_Key:
            {
                setMessageText( control, customToTSKText );
                break;
            }
            case Temple_of_Time_Dungeon_Map:
            {
                setMessageText( control, customToTMapText );
                break;
            }
            case Temple_of_Time_Compass:
            {
                setMessageText( control, customToTCompassText );
                break;
            }
            case Temple_of_Time_Big_Key:
            {
                setMessageText( control, customToTBigKeyText );
                break;
            }

            case City_in_The_Sky_Small_Key:
            {
                setMessageText( control, customCitySKText );
                break;
            }
            case City_in_The_Sky_Dungeon_Map:
            {
                setMessageText( control, customCityMapText );
                break;
            }
            case City_in_The_Sky_Compass:
            {
                setMessageText( control, customCityCompassText );
                break;
            }
            case City_in_The_Sky_Big_Key:
            {
                setMessageText( control, customCityBigKeyText );
                break;
            }

            case Palace_of_Twilight_Small_Key:
            {
                setMessageText( control, customPalaceSKText );
                break;
            }
            case Palace_of_Twilight_Dungeon_Map:
            {
                setMessageText( control, customPalaceMapText );
                break;
            }
            case Palace_of_Twilight_Compass:
            {
                setMessageText( control, customPalaceCompassText );
                break;
            }
            case Palace_of_Twilight_Big_Key:
            {
                setMessageText( control, customPalaceBigKeyText );
                break;
            }

            case Hyrule_Castle_Small_Key:
            {
                setMessageText( control, customCastleSKText );
                break;
            }
            case Hyrule_Castle_Dungeon_Map:
            {
                setMessageText( control, customCastleMapText );
                break;
            }
            case Hyrule_Castle_Compass:
            {
                setMessageText( control, customCastleCompassText );
                break;
            }
            case Hyrule_Castle_Big_Key:
            {
                setMessageText( control, customCastleBigKeyText );
                break;
            }
            case Shadow_Crystal:
            {
                setMessageText( control, customCrystalText );
                break;
            }

            case Ending_Blow:
            {
                setMessageText( control, endingBlowText );
                break;
            }
            case Shield_Attack:
            {
                setMessageText( control, shieldAttackText );
                break;
            }
            case Back_Slice:
            {
                setMessageText( control, backSliceText );
                break;
            }
            case Helm_Splitter:
            {
                setMessageText( control, helmSplitterText );
                break;
            }
            case Mortal_Draw:
            {
                setMessageText( control, mortalDrawText );
                break;
            }
            case Jump_Strike:
            {
                setMessageText( control, jumpStrikeText );
                break;
            }
            case Great_Spin:
            {
                setMessageText( control, greatSpinText );
                break;
            }

            case Bulblin_Camp_Key:
            {
                setMessageText( control, customBublinSKText );
                break;
            }

            case Dominion_Rod:
            {
                setMessageText( control, customPoweredRodText );
                break;
            }

            case Ancient_Sky_Book_First_Character:
            {
                setMessageText( control, firstCharacterText );
                break;
            }

            case Ancient_Sky_Book_Second_Character:
            {
                setMessageText( control, secondCharacterText );
                break;
            }

            case Ancient_Sky_Book_Third_Character:
            {
                setMessageText( control, thirdCharacterText );
                break;
            }

            case Ancient_Sky_Book_Fourth_Character:
            {
                setMessageText( control, fourthCharacterText );
                break;
            }

            case Ancient_Sky_Book_Fifth_Character:
            {
                setMessageText( control, fifthCharacterText );
                break;
            }

            case Fused_Shadow_1:
            {
                setMessageText( control, firstFusedShadowText );
                break;
            }

            case Mirror_Piece_2:
            {
                setMessageText( control, secondMirrorShardText );
                break;
            }

            default:
            {
                break;
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
}     // namespace mod::game_patch