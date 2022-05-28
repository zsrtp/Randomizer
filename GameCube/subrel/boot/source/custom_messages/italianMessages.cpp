#include "main.h"
#include "patch.h"

#include "tp/resource.h"

#include <cstdint>

namespace mod::customMessages
{
    MSG_BEGIN( forestSmallKey )
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
    MSG_BEGIN( minesSmallKey )
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
    MSG_BEGIN( lakebedSmallKey )
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
    MSG_BEGIN( arbitersSmallKey )
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
    MSG_BEGIN( snowpeakSmallKey )
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
    MSG_BEGIN( timeSmallKey )
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
    MSG_BEGIN( citySmallKey )
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
    MSG_BEGIN( palaceSmallKey )
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
    MSG_BEGIN( hyruleSmallKey )
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
    MSG_BEGIN( campSmallKey )
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
    MSG_BEGIN( shadowCrystal )
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
    MSG_BEGIN( forestDungeonMap )
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
    MSG_BEGIN( minesDungeonMap )
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
    MSG_BEGIN( lakebedDungeonMap )
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
    MSG_BEGIN( arbitersDungeonMap )
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
    MSG_BEGIN( snowpeakDungeonMap )
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
    MSG_BEGIN( timeDungeonMap )
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
    MSG_BEGIN( cityDungeonMap )
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
    MSG_BEGIN( palaceDungeonMap )
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
    MSG_BEGIN( hyruleDungeonMap )
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
    MSG_BEGIN( forestCompass )
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
    MSG_BEGIN( minesCompass )
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
    MSG_BEGIN( lakebedCompass )
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
    MSG_BEGIN( arbitersCompass )
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
    MSG_BEGIN( snowpeakCompass )
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
    MSG_BEGIN( timeCompass )
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
    MSG_BEGIN( cityCompass )
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
    MSG_BEGIN( palaceCompass )
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
    MSG_BEGIN( hyruleCompass )
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
    MSG_BEGIN( forestBigKey )
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
    MSG_BEGIN( lakebedBigKey )
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
    MSG_BEGIN( arbitersBigKey )
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
    MSG_BEGIN( timeBigKey )
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
    MSG_BEGIN( cityBigKey )
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
    MSG_BEGIN( palaceBigKey )
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
    MSG_BEGIN( hyruleBigKey )
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
    MSG_BEGIN( endingBlow )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Ending Blow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( shieldAttack )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Shield Attack"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( backSlice )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Back Slice"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( helmSplitter )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Helm Splitter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( mortalDraw )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Mortal Draw"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( jumpStrike )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Jump Strike"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( greatSpin )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Great Spin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( poweredRod )
        MSG_SPEED(MSG_SPEED_FAST)
        "Power has been restored to\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Dominion Rod"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Now it can\nbe used to imbude statues\nwith life in the present!"
    MSG_END()
    MSG_BEGIN( firstCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the first "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN( secondCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the second "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN( thirdCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the third "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN( fourthCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fourth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN( fifthCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fifth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN( firstFusedShadow )
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
    MSG_BEGIN( secondFusedShadow )
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
    MSG_BEGIN( thirdFusedShadow )
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
    MSG_BEGIN( secondMirrorShard )
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
    MSG_BEGIN( thirdMirrorShard )
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
    MSG_BEGIN( fourthMirrorShard )
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
    MSG_BEGIN( foolishItem )
        MSG_SPEED(MSG_SPEED_FAST)
        "A "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "cold"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind blows.."
    MSG_END()
    MSG_BEGIN( talkToMidna )
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
    MSG_BEGIN( bigWallet )
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
    MSG_BEGIN( giantWallet )
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

}     // namespace mod::customMessages