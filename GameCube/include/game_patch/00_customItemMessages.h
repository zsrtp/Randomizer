/** @file 00_wallet.h
 * @author AECX
 * @brief Patches Links wallet to be bigger.
 *
 * @bug No known bugs
 */
#ifndef RANDO_ITEM_MESSAGE_PATCH_H
#define RANDO_ITEM_MESSAGE_PATCH_H

#include "rando/randomizer.h"
#include "tp/resource.h"

namespace mod::game_patch
{
    MSG_BEGIN( customForestSKText )
    MSG_SPEED( MSG_SPEED_FAST )
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "small key" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "!\nIt can be used in the\n" 
    MSG_COLOR(MSG_COLOR_GREEN) 
    "Forest Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customMinesSKText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "small key" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n" 
    MSG_COLOR(MSG_COLOR_RED) 
    "Goron Mines" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customLakebedSKText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "small key" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_BLUE) 
    "Lakebed Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customArbitersSKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_ORANGE)
    "Arbiter's Grounds"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customSnowpeakSKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
    "Snowpeak Ruins"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customToTSKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
    "Temple of Time"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCitySKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_YELLOW)
    "City in The Sky"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customPalaceSKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_PURPLE)
    "Palace of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCastleSKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
    "Hyrule Castle"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customBublinSKText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "small key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_ORANGE)
    "Bulblin Camp"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCrystalText) 
    MSG_SPEED(MSG_SPEED_SLOW) 
    "You got the " 
    MSG_COLOR(MSG_COLOR_RED) 
    "Shadow Crystal" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "!\nThis is a dark manifestation\nof "
    MSG_COLOR(MSG_COLOR_RED)
    "Zant's "
    MSG_COLOR(MSG_COLOR_WHITE)
    "power that allows\nyou to transform at will!"
    MSG_END()

    MSG_BEGIN(customForestMapText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "dungeon map" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "!\nIt can be used in the\n" 
    MSG_COLOR(MSG_COLOR_GREEN) 
    "Forest Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customMinesMapText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "dungeon map" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n" 
    MSG_COLOR(MSG_COLOR_RED) 
    "Goron Mines" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customLakebedMapText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "dungeon map" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_BLUE) 
    "Lakebed Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customArbitersMapText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "dungeon map"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_ORANGE)
    "Arbiter's Grounds"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customSnowpeakMapText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "dungeon map"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
    "Snowpeak Ruins"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customToTMapText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "dungeon map"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
    "Temple of Time"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCityMapText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "dungeon map"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_YELLOW)
    "City in The Sky"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customPalaceMapText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "dungeon map"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_PURPLE)
    "Palace of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCastleMapText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "dungeon map"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
    "Hyrule Castle"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customForestCompassText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "compass" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "!\nIt can be used in the\n" 
    MSG_COLOR(MSG_COLOR_GREEN) 
    "Forest Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customMinesCompassText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "compass" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n" 
    MSG_COLOR(MSG_COLOR_RED) 
    "Goron Mines" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customLakebedCompassText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "compass" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_BLUE) 
    "Lakebed Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customArbitersCompassText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "compass"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_ORANGE)
    "Arbiter's Grounds"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customSnowpeakCompassText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "compass"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
    "Snowpeak Ruins"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customToTCompassText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "compass"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
    "Temple of Time"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCityCompassText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "compass"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_YELLOW)
    "City in The Sky"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customPalaceCompassText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "compass"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_PURPLE)
    "Palace of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCastleCompassText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "compass"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
    "Hyrule Castle"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customForestBigKeyText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "big key" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "!\nIt can be used in the\n" 
    MSG_COLOR(MSG_COLOR_GREEN) 
    "Forest Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customMinesBigKeyText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "big key" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n" 
    MSG_COLOR(MSG_COLOR_RED) 
    "Goron Mines" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customLakebedBigKeyText) 
    MSG_SPEED(MSG_SPEED_FAST) 
    "You got a " 
    MSG_COLOR(MSG_COLOR_RED) 
    "big key" 
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_BLUE) 
    "Lakebed Temple" 
    MSG_COLOR(MSG_COLOR_WHITE) 
    "." 
    MSG_END()

    MSG_BEGIN(customArbitersBigKeyText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "big key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_ORANGE)
    "Arbiter's Grounds"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customSnowpeakBigKeyText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "big key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
    "Snowpeak Ruins"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customToTBigKeyText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "big key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
    "Temple of Time"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCityBigKeyText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "big key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_YELLOW)
    "City in The Sky"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customPalaceBigKeyText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "big key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in the\n"
    MSG_COLOR(MSG_COLOR_PURPLE)
    "Palace of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(customCastleBigKeyText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "big key"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!\nIt can be used in\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
    "Hyrule Castle"
    MSG_COLOR(MSG_COLOR_WHITE)
    "."
    MSG_END()

    MSG_BEGIN(endingBlowText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Ending Blow"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(shieldAttackText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Shield Attack"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(backSliceText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Back Slice"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(helmSplitterText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Helm Splitter"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(mortalDrawText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Mortal Draw"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(jumpStrikeText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Jump Strike"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(greatSpinText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the "
    MSG_COLOR(MSG_COLOR_RED)
    "Great Spin"
    MSG_COLOR(MSG_COLOR_WHITE)
    "!"
    MSG_END()

    MSG_BEGIN(customPoweredRodText)
    MSG_SPEED(MSG_SPEED_FAST)
    "Power has been restored to\nthe "
    MSG_COLOR(MSG_COLOR_RED)
    "Dominion Rod"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! Now it can\nbe used to imbude statues\nwith life in the present!"
    MSG_END()

    MSG_BEGIN(firstCharacterText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You found the "
    MSG_COLOR(MSG_COLOR_RED)
    "first Sky\ncharacter"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()

    MSG_BEGIN(secondCharacterText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You found the "
    MSG_COLOR(MSG_COLOR_RED)
    "second Sky\ncharacter"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()

    MSG_BEGIN(thirdCharacterText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You found the "
    MSG_COLOR(MSG_COLOR_RED)
    "third Sky\ncharacter"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()

    MSG_BEGIN(fourthCharacterText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You found the "
    MSG_COLOR(MSG_COLOR_RED)
    "fourth Sky\ncharacter"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()

    MSG_BEGIN(fifthCharacterText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You found the "
    MSG_COLOR(MSG_COLOR_RED)
    "fifth Sky\ncharacter"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()

    MSG_BEGIN(firstFusedShadowText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got a "
    MSG_COLOR(MSG_COLOR_RED)
    "Fused Shadow!\n"
    MSG_COLOR(MSG_COLOR_WHITE)
    "It seems to have some "
    MSG_COLOR(MSG_COLOR_GREEN) 
    "moss"
    MSG_COLOR(MSG_COLOR_WHITE) 
    "\ngrowing on it.."
    MSG_END()

    MSG_BEGIN(secondFusedShadowText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the second "
    MSG_COLOR(MSG_COLOR_RED)
    "Fused\nShadow"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! It feels "
    MSG_COLOR(MSG_COLOR_RED) 
    "warm"
    MSG_COLOR(MSG_COLOR_WHITE) 
    " to\nthe touch.."
    MSG_END()

    MSG_BEGIN(thirdFusedShadowText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the final "
    MSG_COLOR(MSG_COLOR_RED)
    "Fused\nShadow"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! It feels "
    MSG_COLOR(CUSTOM_MSG_COLOR_BLUE) 
    "wet"
    MSG_COLOR(MSG_COLOR_WHITE) 
    " and\nsmells like fish.."
    MSG_END()

    MSG_BEGIN(secondMirrorShardText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the second shard of\nthe "
    MSG_COLOR(MSG_COLOR_RED)
    "Mirror of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! It\nhas a beautiful shine to it\nand feels slightly "
    MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
    "cold"
    MSG_COLOR(MSG_COLOR_WHITE)
    ".."
    MSG_END()

    MSG_BEGIN(thirdMirrorShardText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the third shard of\nthe "
    MSG_COLOR(MSG_COLOR_RED)
    "Mirror of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! It\nis covered in dirt and\n"
    MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
    "webs"
    MSG_COLOR(MSG_COLOR_WHITE)
    ".."
    MSG_END()

    MSG_BEGIN(fourthMirrorShardText)
    MSG_SPEED(MSG_SPEED_FAST)
    "You got the final shard of\nthe "
    MSG_COLOR(MSG_COLOR_RED)
    "Mirror of Twilight"
    MSG_COLOR(MSG_COLOR_WHITE)
    "! It\nfeels lighter than "
    MSG_COLOR(MSG_COLOR_YELLOW)
    "air"
    MSG_COLOR(MSG_COLOR_WHITE)
    ".."
    MSG_END()


    MSG_BEGIN(foolishItemText)
    MSG_SPEED(MSG_SPEED_FAST)
    "A "
    MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
    "cold"
    MSG_COLOR(MSG_COLOR_WHITE)
    " wind blows.."
    MSG_END()

    const char* talkToMidnaText = { "Talk to Midna" };
    const char* smallDonationText = { "30 Rupees" };
}     // namespace mod::game_patch
#endif