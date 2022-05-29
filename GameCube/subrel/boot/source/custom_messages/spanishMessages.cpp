// This file should only be used for EU
#ifdef TP_EU

#include "customMessages.h"
#include "tp/resource.h"

#include <cstdint>

namespace mod::customMessages
{
    MSG_BEGIN_ARRAY( forestSmallKeySp )
    MSG_SPEED( MSG_SPEED_FAST )
    "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "Templo del Bosque"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( minesSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en las\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Minas de los Goron"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Santuario del Lago"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Patíbulo del Desierto"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en las\n"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Ruinas del Pico Nevado"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( timeSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Templo del Tiempo"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( citySmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Celestia"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( palaceSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Palacio del Crepúsculo"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Castillo de Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( campSmallKeySp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido una "
        MSG_COLOR(MSG_COLOR_RED)
        "llave pequeña"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nPuede ser utilizada en el\n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Campo Bulbin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( shadowCrystalSp )
        MSG_SPEED(MSG_SPEED_SLOW)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "Cristal Oscuro"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEsa manifestación maléfica del\npoder de "
        MSG_COLOR(MSG_COLOR_RED)
        "Zant "
        MSG_COLOR(MSG_COLOR_WHITE)
        "te permite\ntransformarte cuando quieras!"
    MSG_END()
    MSG_BEGIN_ARRAY( forestDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nel "
        MSG_COLOR(MSG_COLOR_GREEN)
        "Templo del Bosque"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( minesDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nlas "
        MSG_COLOR(MSG_COLOR_RED)
        "Minas de los Goron"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nel "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Santuario del Lago"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nel "
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Patíbulo del Desierto"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nlas "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Ruinas del Pico Nevado"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( timeDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nel "
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Templo del Tiempo"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( cityDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Celestia"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( palaceDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nel "
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Palacio del Crepúsculo"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleDungeonMapSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "¡Has obtenido el "
        MSG_COLOR(MSG_COLOR_RED)
        "mapa de una\nmazmorra"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Indica el camino en\nel "
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Castillo de Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( forestCompassSp )
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
    MSG_BEGIN_ARRAY( minesCompassSp )
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
    MSG_BEGIN_ARRAY( lakebedCompassSp )
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
    MSG_BEGIN_ARRAY( arbitersCompassSp )
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
    MSG_BEGIN_ARRAY( snowpeakCompassSp )
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
    MSG_BEGIN_ARRAY( timeCompassSp )
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
    MSG_BEGIN_ARRAY( cityCompassSp )
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
    MSG_BEGIN_ARRAY( palaceCompassSp )
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
    MSG_BEGIN_ARRAY( hyruleCompassSp )
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
    MSG_BEGIN_ARRAY( forestBigKeySp )
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
    MSG_BEGIN_ARRAY( lakebedBigKeySp )
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
    MSG_BEGIN_ARRAY( arbitersBigKeySp )
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
    MSG_BEGIN_ARRAY( timeBigKeySp )
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
    MSG_BEGIN_ARRAY( cityBigKeySp )
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
    MSG_BEGIN_ARRAY( palaceBigKeySp )
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
    MSG_BEGIN_ARRAY( hyruleBigKeySp )
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
    MSG_BEGIN_ARRAY( endingBlowSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Ending Blow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Shield Attack"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Back Slice"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Helm Splitter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Mortal Draw"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Jump Strike"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Great Spin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "Power has been restored to\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Dominion Rod"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Now it can\nbe used to imbude statues\nwith life in the present!"
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the first "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the second "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the third "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fourth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "You found the fifth "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky\ncharacter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! A missing part\nof the word in the Ancient\nSky Book has been restored."
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowSp )
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
    MSG_BEGIN_ARRAY( secondFusedShadowSp )
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
    MSG_BEGIN_ARRAY( thirdFusedShadowSp )
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
    MSG_BEGIN_ARRAY( secondMirrorShardSp )
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
    MSG_BEGIN_ARRAY( thirdMirrorShardSp )
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
    MSG_BEGIN_ARRAY( fourthMirrorShardSp )
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
    MSG_BEGIN_ARRAY( foolishItemSp )
        MSG_SPEED(MSG_SPEED_FAST)
        "A "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "cold"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind blows.."
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaSp )
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
    MSG_BEGIN_ARRAY( bigWalletSp )
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
    MSG_BEGIN_ARRAY( giantWalletSp )
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
    
    MsgEntry entriesSp[TOTAL_CUSTOM_MESSAGES] = 
    {
        // Forest Temple small key
        forestSmallKeySp,
        sizeof(forestSmallKeySp),
        0x00E9,
        
        // Goron Mines small key
        minesSmallKeySp,
        sizeof(minesSmallKeySp),
        0x00EA,
        
        // Lakebed Temple small key
        lakebedSmallKeySp,
        sizeof(lakebedSmallKeySp),
        0x00EB,
        
        // Arbiter's Grounds small key
        arbitersSmallKeySp,
        sizeof(arbitersSmallKeySp),
        0x00EC,
        
        // Snowpeak Ruins small key
        snowpeakSmallKeySp,
        sizeof(snowpeakSmallKeySp),
        0x00ED,
        
        // Temple of Time small key
        timeSmallKeySp,
        sizeof(timeSmallKeySp),
        0x00EE,
        
        // City in the Sky small key
        citySmallKeySp,
        sizeof(citySmallKeySp),
        0x00EF,
        
        // Palace of Twilight small key
        palaceSmallKeySp,
        sizeof(palaceSmallKeySp),
        0x00F0,
        
        // Hyrule Castle small key
        hyruleSmallKeySp,
        sizeof(hyruleSmallKeySp),
        0x00F1,
        
        // Bublin Camp small key
        campSmallKeySp,
        sizeof(campSmallKeySp),
        0x00F2,
        
        // Shadow Crystal
        shadowCrystalSp,
        sizeof(shadowCrystalSp),
        0x0096,
        
        // Forest Temple dungeon map
        forestDungeonMapSp,
        sizeof(forestDungeonMapSp),
        0x011A,
        
        // Goron Mines dungeon map
        minesDungeonMapSp,
        sizeof(minesDungeonMapSp),
        0x011B,
        
        // Lakebed Temple dungeon map
        lakebedDungeonMapSp,
        sizeof(lakebedDungeonMapSp),
        0x011C,
        
        // Arbiter's Grounds dungeon map
        arbitersDungeonMapSp,
        sizeof(arbitersDungeonMapSp),
        0x011D,
        
        // Snowpeak Ruins dungeon map
        snowpeakDungeonMapSp,
        sizeof(snowpeakDungeonMapSp),
        0x011E,
        
        // Temple of Time dungeon map
        timeDungeonMapSp,
        sizeof(timeDungeonMapSp),
        0x011F,
        
        // City in the Sky dungeon map
        cityDungeonMapSp,
        sizeof(cityDungeonMapSp),
        0x0120,
        
        // Palace of Twilight dungeon map
        palaceDungeonMapSp,
        sizeof(palaceDungeonMapSp),
        0x0121,
        
        // Hyrule Castle dungeon map
        hyruleDungeonMapSp,
        sizeof(hyruleDungeonMapSp),
        0x0122,

        // Forest Temple compass
        forestCompassSp,
        sizeof(forestCompassSp),
        0x00FD,

        // Goron Mines compass
        minesCompassSp,
        sizeof(minesCompassSp),
        0x00FE,
        
        // Lakebed Temple compass
        lakebedCompassSp,
        sizeof(lakebedCompassSp),
        0x00FF,

        // Arbiter's Grounds compass
        arbitersCompassSp,
        sizeof(arbitersCompassSp),
        0x010C,

        // Snowpeak Ruins compass
        snowpeakCompassSp,
        sizeof(snowpeakCompassSp),
        0x010D,

        // Temple of Time compass
        timeCompassSp,
        sizeof(timeCompassSp),
        0x010E,

        // City in the Sky compass
        cityCompassSp,
        sizeof(cityCompassSp),
        0x010F,

        // Palace of Twilight compass
        palaceCompassSp,
        sizeof(palaceCompassSp),
        0x0110,

        // Hyrule Castle compass
        hyruleCompassSp,
        sizeof(hyruleCompassSp),
        0x0111,

        // Forest Temple big key
        forestBigKeySp,
        sizeof(forestBigKeySp),
        0x00F6,

        // Lakebed Temple big key
        lakebedBigKeySp,
        sizeof(lakebedBigKeySp),
        0x00F7,

        // Arbiter's Grounds big key
        arbitersBigKeySp,
        sizeof(arbitersBigKeySp),
        0x00F8,

        // Temple of Time big key
        timeBigKeySp,
        sizeof(timeBigKeySp),
        0x00F9,

        // City in the Sky big key
        cityBigKeySp,
        sizeof(cityBigKeySp),
        0x00FA,

        // Palace of Twilight big key
        palaceBigKeySp,
        sizeof(palaceBigKeySp),
        0x00FB,

        // Hyrule Castle big key
        hyruleBigKeySp,
        sizeof(hyruleBigKeySp),
        0x00FC,
        
        // Ending Blow hidden skill
        endingBlowSp,
        sizeof(endingBlowSp),
        0x0145,

        // Shield Attack hidden skill
        shieldAttackSp,
        sizeof(shieldAttackSp),
        0x0146,

        // Back Slice hidden skill
        backSliceSp,
        sizeof(backSliceSp),
        0x0147,

        // Helm Splitter hidden skill
        helmSplitterSp,
        sizeof(helmSplitterSp),
        0x0148,

        // Mortal Draw hidden skill
        mortalDrawSp,
        sizeof(mortalDrawSp),
        0x0149,

        // Jump Strike hidden skill
        jumpStrikeSp,
        sizeof(jumpStrikeSp),
        0x014A,

        // Great Spin hidden skill
        greatSpinSp,
        sizeof(greatSpinSp),
        0x014B,

        // Powered up Dominion Rod
        poweredRodSp,
        sizeof(poweredRodSp),
        0x00B0,

        // First Ancient Sky Book character
        firstCharacterSp,
        sizeof(firstCharacterSp),
        0x013F,

        // Second Ancient Sky Book character
        secondCharacterSp,
        sizeof(secondCharacterSp),
        0x0140,

        // Third Ancient Sky Book character
        thirdCharacterSp,
        sizeof(thirdCharacterSp),
        0x0141,

        // Fourth Ancient Sky Book character
        fourthCharacterSp,
        sizeof(fourthCharacterSp),
        0x0142,

        // Fifth Ancient Sky Book character
        fifthCharacterSp,
        sizeof(fifthCharacterSp),
        0x0143,

        // Sixth Ancient Sky Book character
        firstFusedShadowSp,
        sizeof(firstFusedShadowSp),
        0x013C,

        // Second Fused Shadow
        secondFusedShadowSp,
        sizeof(secondFusedShadowSp),
        0x013D,

        // Third Fused Shadow
        thirdFusedShadowSp,
        sizeof(thirdFusedShadowSp),
        0x013E,

        // Second Mirror Shard
        secondMirrorShardSp,
        sizeof(secondMirrorShardSp),
        0x0109,

        // Third Mirror Shard
        thirdMirrorShardSp,
        sizeof(thirdMirrorShardSp),
        0x010A,

        // Fourth Mirror Shard
        fourthMirrorShardSp,
        sizeof(fourthMirrorShardSp),
        0x010B,

        // Foolish Item
        foolishItemSp,
        sizeof(foolishItemSp),
        0x00F3,

        // Talking to Midna
        talkToMidnaSp,
        sizeof(talkToMidnaSp),
        0x0BBB,

        // Big Wallet
        bigWalletSp,
        sizeof(bigWalletSp),
        0x0099,

        // Giant Wallet
        giantWalletSp,
        sizeof(giantWalletSp),
        0x009A,
    };

}     // namespace mod::customMessages
#endif