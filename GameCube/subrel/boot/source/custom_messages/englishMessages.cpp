// This file should not be used for JP
#ifndef TP_JP

#include "customMessages.h"
#include "tp/resource.h"
#include "item_wheel_menu.h"

#include <cstdint>

namespace mod::customMessages
{
    using namespace item_wheel_menu;

    // Disable formatting for the textbox messages because it makes things look weird.
    // clang-format off
    MSG_BEGIN_ARRAY( forestSmallKeyEn )
        MSG_SPEED( MSG_SPEED_FAST )
        "You got a "
        MSG_COLOR(MSG_COLOR_RED)
        "small key"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nIt can be used in the \n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "Forest Temple"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( minesSmallKeyEn )
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
    MSG_BEGIN_ARRAY( lakebedSmallKeyEn )
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
    MSG_BEGIN_ARRAY( arbitersSmallKeyEn )
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
    MSG_BEGIN_ARRAY( snowpeakSmallKeyEn )
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
    MSG_BEGIN_ARRAY( timeSmallKeyEn )
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
    MSG_BEGIN_ARRAY( citySmallKeyEn )
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
    MSG_BEGIN_ARRAY( palaceSmallKeyEn )
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
    MSG_BEGIN_ARRAY( hyruleSmallKeyEn )
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
    MSG_BEGIN_ARRAY( campSmallKeyEn )
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
    MSG_BEGIN_ARRAY( shadowCrystalEn )
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
    MSG_BEGIN_ARRAY( forestDungeonMapEn )
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
    MSG_BEGIN_ARRAY( minesDungeonMapEn )
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
    MSG_BEGIN_ARRAY( lakebedDungeonMapEn )
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
    MSG_BEGIN_ARRAY( arbitersDungeonMapEn )
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
    MSG_BEGIN_ARRAY( snowpeakDungeonMapEn )
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
    MSG_BEGIN_ARRAY( timeDungeonMapEn )
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
    MSG_BEGIN_ARRAY( cityDungeonMapEn )
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
    MSG_BEGIN_ARRAY( palaceDungeonMapEn )
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
    MSG_BEGIN_ARRAY( hyruleDungeonMapEn )
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
    MSG_BEGIN_ARRAY( forestCompassEn )
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
    MSG_BEGIN_ARRAY( minesCompassEn )
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
    MSG_BEGIN_ARRAY( lakebedCompassEn )
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
    MSG_BEGIN_ARRAY( arbitersCompassEn )
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
    MSG_BEGIN_ARRAY( snowpeakCompassEn )
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
    MSG_BEGIN_ARRAY( timeCompassEn )
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
    MSG_BEGIN_ARRAY( cityCompassEn )
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
    MSG_BEGIN_ARRAY( palaceCompassEn )
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
    MSG_BEGIN_ARRAY( hyruleCompassEn )
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
    MSG_BEGIN_ARRAY( forestBigKeyEn )
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
    MSG_BEGIN_ARRAY( lakebedBigKeyEn )
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
    MSG_BEGIN_ARRAY( arbitersBigKeyEn )
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
    MSG_BEGIN_ARRAY( timeBigKeyEn )
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
    MSG_BEGIN_ARRAY( cityBigKeyEn )
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
    MSG_BEGIN_ARRAY( palaceBigKeyEn )
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
    MSG_BEGIN_ARRAY( hyruleBigKeyEn )
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
    MSG_BEGIN_ARRAY( endingBlowEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Ending Blow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Shield Attack"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Back Slice"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Helm Splitter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Mortal Draw"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Jump Strike"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Great Spin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "Power has been restored to\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Dominion Rod"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Now it can\nbe used to imbude statues\nwith life in the present!"
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the first "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the second "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the third "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fourth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fifth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowEn )
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
    MSG_BEGIN_ARRAY( secondFusedShadowEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the second"
        MSG_COLOR(MSG_COLOR_RED)
        "Fused\nShadow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It feels "
        MSG_COLOR(MSG_COLOR_RED)
        "warm"
        MSG_COLOR(MSG_COLOR_WHITE)
        " to\nthe touch.."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdFusedShadowEn )
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
    MSG_BEGIN_ARRAY( secondMirrorShardEn )
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
    MSG_BEGIN_ARRAY( thirdMirrorShardEn )
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
    MSG_BEGIN_ARRAY( fourthMirrorShardEn )
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
    MSG_BEGIN_ARRAY( foolishItemEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "A "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "cold"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind blows.."
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaEn )
        "What is it, "
        MSG_PLYR_NAME
        "?"
        MSG_OPTION_LIST(MSG_OPTION_1)
        "Transform\n"
        MSG_OPTION_LIST(MSG_OPTION_2)
        "Warp\n"
        MSG_OPTION_LIST(MSG_OPTION_3)
        "Change time of day"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Big Wallet"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! You can now hold "
        MSG_COLOR(MSG_COLOR_RED)
        "5,000 Rupees"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Giant Wallet"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! You can now hold "
        MSG_COLOR(MSG_COLOR_PURPLE)
        "9,999 Rupees"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    // clang-format on

    MsgEntry entriesUs[TOTAL_CUSTOM_MESSAGES] = 
    {
        // Forest Temple small key
        forestSmallKeyEn,
        sizeof(forestSmallKeyEn),
        0x00E9,
        
        // Goron Mines small key
        minesSmallKeyEn,
        sizeof(minesSmallKeyEn),
        0x00EA,
        
        // Lakebed Temple small key
        lakebedSmallKeyEn,
        sizeof(lakebedSmallKeyEn),
        0x00EB,
        
        // Arbiter's Grounds small key
        arbitersSmallKeyEn,
        sizeof(arbitersSmallKeyEn),
        0x00EC,
        
        // Snowpeak Ruins small key
        snowpeakSmallKeyEn,
        sizeof(snowpeakSmallKeyEn),
        0x00ED,
        
        // Temple of Time small key
        timeSmallKeyEn,
        sizeof(timeSmallKeyEn),
        0x00EE,
        
        // City in the Sky small key
        citySmallKeyEn,
        sizeof(citySmallKeyEn),
        0x00EF,
        
        // Palace of Twilight small key
        palaceSmallKeyEn,
        sizeof(palaceSmallKeyEn),
        0x00F0,
        
        // Hyrule Castle small key
        hyruleSmallKeyEn,
        sizeof(hyruleSmallKeyEn),
        0x00F1,
        
        // Bublin Camp small key
        campSmallKeyEn,
        sizeof(campSmallKeyEn),
        0x00F2,
        
        // Shadow Crystal
        shadowCrystalEn,
        sizeof(shadowCrystalEn),
        0x0096,
        
        // Forest Temple dungeon map
        forestDungeonMapEn,
        sizeof(forestDungeonMapEn),
        0x011A,
        
        // Goron Mines dungeon map
        minesDungeonMapEn,
        sizeof(minesDungeonMapEn),
        0x011B,
        
        // Lakebed Temple dungeon map
        lakebedDungeonMapEn,
        sizeof(lakebedDungeonMapEn),
        0x011C,
        
        // Arbiter's Grounds dungeon map
        arbitersDungeonMapEn,
        sizeof(arbitersDungeonMapEn),
        0x011D,
        
        // Snowpeak Ruins dungeon map
        snowpeakDungeonMapEn,
        sizeof(snowpeakDungeonMapEn),
        0x011E,
        
        // Temple of Time dungeon map
        timeDungeonMapEn,
        sizeof(timeDungeonMapEn),
        0x011F,
        
        // City in the Sky dungeon map
        cityDungeonMapEn,
        sizeof(cityDungeonMapEn),
        0x0120,
        
        // Palace of Twilight dungeon map
        palaceDungeonMapEn,
        sizeof(palaceDungeonMapEn),
        0x0121,
        
        // Hyrule Castle dungeon map
        hyruleDungeonMapEn,
        sizeof(hyruleDungeonMapEn),
        0x0122,

        // Forest Temple compass
        forestCompassEn,
        sizeof(forestCompassEn),
        0x00FD,

        // Goron Mines compass
        minesCompassEn,
        sizeof(minesCompassEn),
        0x00FE,
        
        // Lakebed Temple compass
        lakebedCompassEn,
        sizeof(lakebedCompassEn),
        0x00FF,

        // Arbiter's Grounds compass
        arbitersCompassEn,
        sizeof(arbitersCompassEn),
        0x010C,

        // Snowpeak Ruins compass
        snowpeakCompassEn,
        sizeof(snowpeakCompassEn),
        0x010D,

        // Temple of Time compass
        timeCompassEn,
        sizeof(timeCompassEn),
        0x010E,

        // City in the Sky compass
        cityCompassEn,
        sizeof(cityCompassEn),
        0x010F,

        // Palace of Twilight compass
        palaceCompassEn,
        sizeof(palaceCompassEn),
        0x0110,

        // Hyrule Castle compass
        hyruleCompassEn,
        sizeof(hyruleCompassEn),
        0x0111,

        // Forest Temple big key
        forestBigKeyEn,
        sizeof(forestBigKeyEn),
        0x00F6,

        // Lakebed Temple big key
        lakebedBigKeyEn,
        sizeof(lakebedBigKeyEn),
        0x00F7,

        // Arbiter's Grounds big key
        arbitersBigKeyEn,
        sizeof(arbitersBigKeyEn),
        0x00F8,

        // Temple of Time big key
        timeBigKeyEn,
        sizeof(timeBigKeyEn),
        0x00F9,

        // City in the Sky big key
        cityBigKeyEn,
        sizeof(cityBigKeyEn),
        0x00FA,

        // Palace of Twilight big key
        palaceBigKeyEn,
        sizeof(palaceBigKeyEn),
        0x00FB,

        // Hyrule Castle big key
        hyruleBigKeyEn,
        sizeof(hyruleBigKeyEn),
        0x00FC,
        
        // Ending Blow hidden skill
        endingBlowEn,
        sizeof(endingBlowEn),
        0x0145,

        // Shield Attack hidden skill
        shieldAttackEn,
        sizeof(shieldAttackEn),
        0x0146,

        // Back Slice hidden skill
        backSliceEn,
        sizeof(backSliceEn),
        0x0147,

        // Helm Splitter hidden skill
        helmSplitterEn,
        sizeof(helmSplitterEn),
        0x0148,

        // Mortal Draw hidden skill
        mortalDrawEn,
        sizeof(mortalDrawEn),
        0x0149,

        // Jump Strike hidden skill
        jumpStrikeEn,
        sizeof(jumpStrikeEn),
        0x014A,

        // Great Spin hidden skill
        greatSpinEn,
        sizeof(greatSpinEn),
        0x014B,

        // Powered up Dominion Rod
        poweredRodEn,
        sizeof(poweredRodEn),
        0x00B0,

        // First Ancient Sky Book character
        firstCharacterEn,
        sizeof(firstCharacterEn),
        0x013F,

        // Second Ancient Sky Book character
        secondCharacterEn,
        sizeof(secondCharacterEn),
        0x0140,

        // Third Ancient Sky Book character
        thirdCharacterEn,
        sizeof(thirdCharacterEn),
        0x0141,

        // Fourth Ancient Sky Book character
        fourthCharacterEn,
        sizeof(fourthCharacterEn),
        0x0142,

        // Fifth Ancient Sky Book character
        fifthCharacterEn,
        sizeof(fifthCharacterEn),
        0x0143,

        // Sixth Ancient Sky Book character
        firstFusedShadowEn,
        sizeof(firstFusedShadowEn),
        0x013C,

        // Second Fused Shadow
        secondFusedShadowEn,
        sizeof(secondFusedShadowEn),
        0x013D,

        // Third Fused Shadow
        thirdFusedShadowEn,
        sizeof(thirdFusedShadowEn),
        0x013E,

        // Second Mirror Shard
        secondMirrorShardEn,
        sizeof(secondMirrorShardEn),
        0x0109,

        // Third Mirror Shard
        thirdMirrorShardEn,
        sizeof(thirdMirrorShardEn),
        0x010A,

        // Fourth Mirror Shard
        fourthMirrorShardEn,
        sizeof(fourthMirrorShardEn),
        0x010B,

        // Foolish Item
        foolishItemEn,
        sizeof(foolishItemEn),
        0x00F3,

        // Talking to Midna
        talkToMidnaEn,
        sizeof(talkToMidnaEn),
        0x0BBB,

        // Big Wallet
        bigWalletEn,
        sizeof(bigWalletEn),
        0x0099,

        // Giant Wallet
        giantWalletEn,
        sizeof(giantWalletEn),
        0x009A,
    };

    const ItemWheelMenuStrings itemWheelMenuStringsUs = {
        // areasBeingTracked
        {
            "Forest Temple",
            "Goron Mines",
            "Lakebed Temple",
            "Arbiter's Grounds",
            "Snowpeak Ruins",
            "Temple of Time",
            "City in the Sky",
            "Palace of Twilight",
            "Hyrule Castle",
            "Faron Woods",
            "Bublin Camp",
        },

        // seedIsLoaded
        "Seed",

        // seedIsNotLoaded
        "No seed is currently loaded",

        // yes/no
        "Yes",
        "No",

        // shadowsShards
        "Fused Shadows\nMirror Shards",

        // Pumpkin
        "Pumpkin",

        // Cheese
        "Cheese",

        // Gate Keys
        "Gate Keys",

        // Areas
        "Areas",

        // Small Keys
        "Small\nKeys",

        // Big Keys
        "Big\nKeys",

        // Maps
        "Maps",

        // Compasses
        "Compasses",

        // helpText
        "Press Start\nor Z to\ntoggle\nadditional\ndata",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsUs {
        // Fused Shadows/Mirror Shards
        135,

        // Pumpkin
        60,

        // Yes/No
        20,
        22,

        // Cheese
        90,

        // Yes/No
        15,
        17,

        // Gate Keys
        80,

        // Yes/No
        25,
        27,

        // Headers
        // Small Keys
        155,

        // Big Keys
        70,

        // Maps
        70,

        // Compasses
        70,

        // Header values
        // Small Keys values
        15,

        // Big keys values
        // Yes/No
        5,
        7,

        // Goron Mines
        13,

        // Maps values
        // Yes/No
        7,
        9,

        // Compasses values
        // Yes/No
        30,
        32,
    };
}     // namespace mod::customMessages
#endif