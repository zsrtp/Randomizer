// This file should only be used for EU
#ifdef TP_EU

#include "customMessages.h"
#include "tp/resource.h"
#include "item_wheel_menu.h"

#include <cstdint>

namespace mod::customMessages
{
    using namespace item_wheel_menu;

    // Disable formatting for the textbox messages because it makes things look weird.
    // clang-format off
    MSG_BEGIN_ARRAY( forestSmallKeyIt )
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
    MSG_BEGIN_ARRAY( minesSmallKeyIt )
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
    MSG_BEGIN_ARRAY( lakebedSmallKeyIt )
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
    MSG_BEGIN_ARRAY( arbitersSmallKeyIt )
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
    MSG_BEGIN_ARRAY( snowpeakSmallKeyIt )
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
    MSG_BEGIN_ARRAY( timeSmallKeyIt )
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
    MSG_BEGIN_ARRAY( citySmallKeyIt )
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
    MSG_BEGIN_ARRAY( palaceSmallKeyIt )
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
    MSG_BEGIN_ARRAY( hyruleSmallKeyIt )
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
    MSG_BEGIN_ARRAY( campSmallKeyIt )
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
    MSG_BEGIN_ARRAY( shadowCrystalIt )
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
    MSG_BEGIN_ARRAY( forestDungeonMapIt )
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
    MSG_BEGIN_ARRAY( minesDungeonMapIt )
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
    MSG_BEGIN_ARRAY( lakebedDungeonMapIt )
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
    MSG_BEGIN_ARRAY( arbitersDungeonMapIt )
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
    MSG_BEGIN_ARRAY( snowpeakDungeonMapIt )
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
    MSG_BEGIN_ARRAY( timeDungeonMapIt )
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
    MSG_BEGIN_ARRAY( cityDungeonMapIt )
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
    MSG_BEGIN_ARRAY( palaceDungeonMapIt )
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
    MSG_BEGIN_ARRAY( hyruleDungeonMapIt )
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
    MSG_BEGIN_ARRAY( forestCompassIt )
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
    MSG_BEGIN_ARRAY( minesCompassIt )
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
    MSG_BEGIN_ARRAY( lakebedCompassIt )
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
    MSG_BEGIN_ARRAY( arbitersCompassIt )
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
    MSG_BEGIN_ARRAY( snowpeakCompassIt )
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
    MSG_BEGIN_ARRAY( timeCompassIt )
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
    MSG_BEGIN_ARRAY( cityCompassIt )
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
    MSG_BEGIN_ARRAY( palaceCompassIt )
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
    MSG_BEGIN_ARRAY( hyruleCompassIt )
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
    MSG_BEGIN_ARRAY( forestBigKeyIt )
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
    MSG_BEGIN_ARRAY( lakebedBigKeyIt )
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
    MSG_BEGIN_ARRAY( arbitersBigKeyIt )
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
    MSG_BEGIN_ARRAY( timeBigKeyIt )
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
    MSG_BEGIN_ARRAY( cityBigKeyIt )
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
    MSG_BEGIN_ARRAY( palaceBigKeyIt )
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
    MSG_BEGIN_ARRAY( hyruleBigKeyIt )
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
    MSG_BEGIN_ARRAY( endingBlowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Ending Blow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Shield Attack"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Back Slice"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Helm Splitter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Mortal Draw"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Jump Strike"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Great Spin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "Power has been restored to\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Dominion Rod"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Now it can\nbe used to imbude statues\nwith life in the present!"
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the first "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the second "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the third "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fourth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fifth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowIt )
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
    MSG_BEGIN_ARRAY( secondFusedShadowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "second Fused\nShadow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It feels "
        MSG_COLOR(MSG_COLOR_RED)
        "warm"
        MSG_COLOR(MSG_COLOR_WHITE)
        " to\nthe touch.."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdFusedShadowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "final Fused\nShadow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It feels "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "wet"
        MSG_COLOR(MSG_COLOR_WHITE)
        " and\nsmells like fish.."
    MSG_END()
    MSG_BEGIN_ARRAY( secondMirrorShardIt )
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
    MSG_BEGIN_ARRAY( thirdMirrorShardIt )
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
    MSG_BEGIN_ARRAY( fourthMirrorShardIt )
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
    MSG_BEGIN_ARRAY( foolishItemIt )
        MSG_SPEED(MSG_SPEED_FAST)
        "A "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "cold"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind blows.."
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaIt )
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
    MSG_BEGIN_ARRAY( bigWalletIt )
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
    MSG_BEGIN_ARRAY( giantWalletIt )
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
    
    MsgEntry entriesIt[TOTAL_CUSTOM_MESSAGES] = 
    {
        // Forest Temple small key
        forestSmallKeyIt,
        sizeof(forestSmallKeyIt),
        0x00E9,
        
        // Goron Mines small key
        minesSmallKeyIt,
        sizeof(minesSmallKeyIt),
        0x00EA,
        
        // Lakebed Temple small key
        lakebedSmallKeyIt,
        sizeof(lakebedSmallKeyIt),
        0x00EB,
        
        // Arbiter's Grounds small key
        arbitersSmallKeyIt,
        sizeof(arbitersSmallKeyIt),
        0x00EC,
        
        // Snowpeak Ruins small key
        snowpeakSmallKeyIt,
        sizeof(snowpeakSmallKeyIt),
        0x00ED,
        
        // Temple of Time small key
        timeSmallKeyIt,
        sizeof(timeSmallKeyIt),
        0x00EE,
        
        // City in the Sky small key
        citySmallKeyIt,
        sizeof(citySmallKeyIt),
        0x00EF,
        
        // Palace of Twilight small key
        palaceSmallKeyIt,
        sizeof(palaceSmallKeyIt),
        0x00F0,
        
        // Hyrule Castle small key
        hyruleSmallKeyIt,
        sizeof(hyruleSmallKeyIt),
        0x00F1,
        
        // Bublin Camp small key
        campSmallKeyIt,
        sizeof(campSmallKeyIt),
        0x00F2,
        
        // Shadow Crystal
        shadowCrystalIt,
        sizeof(shadowCrystalIt),
        0x0096,
        
        // Forest Temple dungeon map
        forestDungeonMapIt,
        sizeof(forestDungeonMapIt),
        0x011A,
        
        // Goron Mines dungeon map
        minesDungeonMapIt,
        sizeof(minesDungeonMapIt),
        0x011B,
        
        // Lakebed Temple dungeon map
        lakebedDungeonMapIt,
        sizeof(lakebedDungeonMapIt),
        0x011C,
        
        // Arbiter's Grounds dungeon map
        arbitersDungeonMapIt,
        sizeof(arbitersDungeonMapIt),
        0x011D,
        
        // Snowpeak Ruins dungeon map
        snowpeakDungeonMapIt,
        sizeof(snowpeakDungeonMapIt),
        0x011E,
        
        // Temple of Time dungeon map
        timeDungeonMapIt,
        sizeof(timeDungeonMapIt),
        0x011F,
        
        // City in the Sky dungeon map
        cityDungeonMapIt,
        sizeof(cityDungeonMapIt),
        0x0120,
        
        // Palace of Twilight dungeon map
        palaceDungeonMapIt,
        sizeof(palaceDungeonMapIt),
        0x0121,
        
        // Hyrule Castle dungeon map
        hyruleDungeonMapIt,
        sizeof(hyruleDungeonMapIt),
        0x0122,

        // Forest Temple compass
        forestCompassIt,
        sizeof(forestCompassIt),
        0x00FD,

        // Goron Mines compass
        minesCompassIt,
        sizeof(minesCompassIt),
        0x00FE,
        
        // Lakebed Temple compass
        lakebedCompassIt,
        sizeof(lakebedCompassIt),
        0x00FF,

        // Arbiter's Grounds compass
        arbitersCompassIt,
        sizeof(arbitersCompassIt),
        0x010C,

        // Snowpeak Ruins compass
        snowpeakCompassIt,
        sizeof(snowpeakCompassIt),
        0x010D,

        // Temple of Time compass
        timeCompassIt,
        sizeof(timeCompassIt),
        0x010E,

        // City in the Sky compass
        cityCompassIt,
        sizeof(cityCompassIt),
        0x010F,

        // Palace of Twilight compass
        palaceCompassIt,
        sizeof(palaceCompassIt),
        0x0110,

        // Hyrule Castle compass
        hyruleCompassIt,
        sizeof(hyruleCompassIt),
        0x0111,

        // Forest Temple big key
        forestBigKeyIt,
        sizeof(forestBigKeyIt),
        0x00F6,

        // Lakebed Temple big key
        lakebedBigKeyIt,
        sizeof(lakebedBigKeyIt),
        0x00F7,

        // Arbiter's Grounds big key
        arbitersBigKeyIt,
        sizeof(arbitersBigKeyIt),
        0x00F8,

        // Temple of Time big key
        timeBigKeyIt,
        sizeof(timeBigKeyIt),
        0x00F9,

        // City in the Sky big key
        cityBigKeyIt,
        sizeof(cityBigKeyIt),
        0x00FA,

        // Palace of Twilight big key
        palaceBigKeyIt,
        sizeof(palaceBigKeyIt),
        0x00FB,

        // Hyrule Castle big key
        hyruleBigKeyIt,
        sizeof(hyruleBigKeyIt),
        0x00FC,
        
        // Ending Blow hidden skill
        endingBlowIt,
        sizeof(endingBlowIt),
        0x0145,

        // Shield Attack hidden skill
        shieldAttackIt,
        sizeof(shieldAttackIt),
        0x0146,

        // Back Slice hidden skill
        backSliceIt,
        sizeof(backSliceIt),
        0x0147,

        // Helm Splitter hidden skill
        helmSplitterIt,
        sizeof(helmSplitterIt),
        0x0148,

        // Mortal Draw hidden skill
        mortalDrawIt,
        sizeof(mortalDrawIt),
        0x0149,

        // Jump Strike hidden skill
        jumpStrikeIt,
        sizeof(jumpStrikeIt),
        0x014A,

        // Great Spin hidden skill
        greatSpinIt,
        sizeof(greatSpinIt),
        0x014B,

        // Powered up Dominion Rod
        poweredRodIt,
        sizeof(poweredRodIt),
        0x00B0,

        // First Ancient Sky Book character
        firstCharacterIt,
        sizeof(firstCharacterIt),
        0x013F,

        // Second Ancient Sky Book character
        secondCharacterIt,
        sizeof(secondCharacterIt),
        0x0140,

        // Third Ancient Sky Book character
        thirdCharacterIt,
        sizeof(thirdCharacterIt),
        0x0141,

        // Fourth Ancient Sky Book character
        fourthCharacterIt,
        sizeof(fourthCharacterIt),
        0x0142,

        // Fifth Ancient Sky Book character
        fifthCharacterIt,
        sizeof(fifthCharacterIt),
        0x0143,

        // Sixth Ancient Sky Book character
        firstFusedShadowIt,
        sizeof(firstFusedShadowIt),
        0x013C,

        // Second Fused Shadow
        secondFusedShadowIt,
        sizeof(secondFusedShadowIt),
        0x013D,

        // Third Fused Shadow
        thirdFusedShadowIt,
        sizeof(thirdFusedShadowIt),
        0x013E,

        // Second Mirror Shard
        secondMirrorShardIt,
        sizeof(secondMirrorShardIt),
        0x0109,

        // Third Mirror Shard
        thirdMirrorShardIt,
        sizeof(thirdMirrorShardIt),
        0x010A,

        // Fourth Mirror Shard
        fourthMirrorShardIt,
        sizeof(fourthMirrorShardIt),
        0x010B,

        // Foolish Item
        foolishItemIt,
        sizeof(foolishItemIt),
        0x00F3,

        // Talking to Midna
        talkToMidnaIt,
        sizeof(talkToMidnaIt),
        0x0BBB,

        // Big Wallet
        bigWalletIt,
        sizeof(bigWalletIt),
        0x0099,

        // Giant Wallet
        giantWalletIt,
        sizeof(giantWalletIt),
        0x009A,
    };

    const ItemWheelMenuStrings itemWheelMenuStringsIt = {
        // areasBeingTracked
        {
            // Forest Temple
            // Santuario della foresta
            "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x6C\x61\x20\x66\x6F\x72\x65\x73\x74\x61",

            // Goron Mines
            // Miniera dei Goron
            "\x4D\x69\x6E\x69\x65\x72\x61\x20\x64\x65\x69\x20\x47\x6F\x72\x6F\x6E",

            // Lakebed Temple
            // Santuario nel lago
            "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x6E\x65\x6C\x20\x6C\x61\x67\x6F",

            // Arbiter's Grounds
            // Patibolo del deserto
            "\x50\x61\x74\x69\x62\x6F\x6C\x6F\x20\x64\x65\x6C\x20\x64\x65\x73\x65\x72\x74\x6F",

            // Snowpeak Ruins
            // Rovine sul ghiacciaio
            "\x52\x6F\x76\x69\x6E\x65\x20\x73\x75\x6C\x20\x67\x68\x69\x61\x63\x63\x69\x61\x69\x6F",

            // Temple of Time
            // Santuario del tempo
            "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x20\x74\x65\x6D\x70\x6F",

            // City in the Sky
            // Città eterea
            "\x43\x69\x74\x74\xE0\x20\x65\x74\x65\x72\x65\x61",

            // Palace of Twilight
            // Palazzo del crepuscolo
            "\x50\x61\x6C\x61\x7A\x7A\x6F\x20\x64\x65\x6C\x20\x63\x72\x65\x70\x75\x73\x63\x6F\x6C\x6F",

            // Hyrule Castle
            // Castello di Hyrule
            "\x43\x61\x73\x74\x65\x6C\x6C\x6F\x20\x64\x69\x20\x48\x79\x72\x75\x6C\x65",

            // Faron Woods
            // Foresta di Firone
            "\x46\x6F\x72\x65\x73\x74\x61\x20\x64\x69\x20\x46\x69\x72\x6F\x6E\x65",

            // Bublin Camp
            // campo dei Bulbin
            "\x63\x61\x6D\x70\x6F\x20\x64\x65\x69\x20\x42\x75\x6C\x62\x69\x6E",
        },

        // seedIsLoaded
        // Seed
        "\x53\x65\x65\x64",

        // seedIsNotLoaded
        // Nessun seed é stato caricato
        "\x4E\x65\x73\x73\x75\x6E\x20\x73\x65\x65\x64\x20\xE9\x20\x73\x74\x61\x74\x6F\x20\x63\x61\x72\x69\x63\x61\x74\x6F",

        // yes/no
        // Sì
        "\x53\xEC",

        // No
        "\x4E\x6F",

        // shadowsShards
        // Cristalli oscuri\nFrammenti di specchio
        "\x43\x72\x69\x73\x74\x61\x6C\x6C\x69\x20\x6F\x73\x63\x75\x72\x69\x0A\x46\x72\x61\x6D\x6D\x65\x6E\x74\x69\x20\x64\x69"
        "\x20\x73\x70\x65\x63\x63\x68\x69\x6F",

        // Pumpkin
        // Zucca
        "\x5A\x75\x63\x63\x61",

        // Cheese
        // Formaggio
        "\x46\x6F\x72\x6D\x61\x67\x67\x69\x6F",

        // Gate Keys
        // Chiavi del cancello
        "\x43\x68\x69\x61\x76\x69\x20\x64\x65\x6C\x20\x63\x61\x6E\x63\x65\x6C\x6C\x6F",

        // Areas
        // Aree
        "\x41\x72\x65\x65",

        // Small Keys
        // Piccole\nChiavi
        "\x50\x69\x63\x63\x6F\x6C\x65\x0A\x43\x68\x69\x61\x76\x69",

        // Big Keys
        // Grandi\nChiavi
        "\x47\x72\x61\x6E\x64\x69\x0A\x43\x68\x69\x61\x76\x69",

        // Maps
        // Mappe
        "\x4D\x61\x70\x70\x65",

        // Compasses
        // Bussole
        "\x42\x75\x73\x73\x6F\x6C\x65",

        // helpText
        // Premere Start\no Z per\nattivare\ni dati\naggiuntivi
        "\x50\x72\x65\x6D\x65\x72\x65\x0A\x53\x74\x61\x72\x74\x0A\x6F\x20\x5A\x20\x70\x65\x72\x0A\x61\x74\x74\x69\x76\x61\x72"
        "\x65\x0A\x69\x20\x64\x61\x74\x69\x0A\x61\x67\x67\x69\x75\x6E\x74\x69\x76\x69",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsIt {
        // Fused Shadows/Mirror Shards
        185,

        // Pumpkin
        35,

        // Yes/No
        15,
        12,

        // Cheese
        57,

        // Yes/No
        32,
        29,

        // Gate Keys
        90,

        // Yes/No
        64,
        61,

        // Headers
        // Small Keys
        200,

        // Big Keys
        75,

        // Maps
        73,

        // Compasses
        74,

        // Header values
        // Small Keys values
        23,

        // Big keys values
        // Yes/No
        17,
        14,

        // Goron Mines
        20,

        // Maps values
        // Yes/No
        18,
        15,

        // Compasses values
        // Yes/No
        23,
        20,
    };
}     // namespace mod::customMessages
#endif