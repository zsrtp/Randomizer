// This file should only be used for EU
#ifdef TP_EU

#include "customMessages.h"
#include "tp/resource.h"

#include <cstdint>

namespace mod::customMessages
{
    MSG_BEGIN_ARRAY( forestSmallKeyDe )
    MSG_SPEED( MSG_SPEED_FAST )
    "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir Türen\nim "
        MSG_COLOR(MSG_COLOR_GREEN)
        "Waldschrein"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( minesSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir Türen\nin den "
        MSG_COLOR(MSG_COLOR_RED)
        "Minen der Goronen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedSmallKeyDe )
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir Türen\nim "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Seeschrein"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir Türen\nin der "
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Wüstenburg"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir Türen\nin der "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Bergruine"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( timeSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir\nTüren im "
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Zeitschrein"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( citySmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir\nTüren in "
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Kumula"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( palaceSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir\nTüren im "
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Schattenpalast"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir\nTüren auf "
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Schloss Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( campSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "kleinen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet das\nTor im "
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Camp der Bulblins"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( shadowCrystalDe )
        MSG_SPEED(MSG_SPEED_SLOW)
        "Du erhältst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Nachtkristall"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nDiese dunkle Manifestation der\nMacht "
        MSG_COLOR(MSG_COLOR_RED)
        "Zantos "
        MSG_COLOR(MSG_COLOR_WHITE)
        "erlaubt es dir, dich\nnach Belieben zu verwandeln!"
    MSG_END()
    MSG_BEGIN_ARRAY( forestDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie im "
        MSG_COLOR(MSG_COLOR_GREEN)
        "Waldschrein"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( minesDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie in den "
        MSG_COLOR(MSG_COLOR_RED)
        "Minen der\nGoronen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie im "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Seeschrein"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie in der "
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Wüstenburg"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie in der "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Bergruine"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( timeDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie im "
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Zeitschrein"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( cityDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie in "
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Kumula"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( palaceDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie im "
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Schattenpalast"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst eine "
        MSG_COLOR(MSG_COLOR_RED)
        "Dungeon-Karte"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nVerwende sie auf "
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Schloss Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( forestCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nim "
        MSG_COLOR(MSG_COLOR_GREEN)
        "Waldschrein "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( minesCompassDe )
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nin den "
        MSG_COLOR(MSG_COLOR_RED)
        "Minen der Goronen "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nim "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Seeschrein "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nin der "
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Wüstenburg "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nin der "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Bergruine "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( timeCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nim "
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Zeitschrein "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( cityCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nin "
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Kumula "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( palaceCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nim "
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Schattenpalast "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "Kompass"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nEr zeigt dir, wo du die Schätze\nauf "
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Schloss Hyrule "
        MSG_COLOR(MSG_COLOR_WHITE)
        "findest."
    MSG_END()
    MSG_BEGIN_ARRAY( forestBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir den\nWeg zum Boss des "
        MSG_COLOR(MSG_COLOR_GREEN)
        "Waldschreins"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir den\nWeg zum Boss der "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Seeschreins"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir den\nWeg zum Boss der "
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Wüstenburg"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( timeBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir den\nWeg zum Boss des "
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Zeitschreins"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( cityBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir den\nWeg zum Boss von "
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Kumula"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( palaceBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir\nden Weg zum Boss\ndes "
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Schattenpalasts"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen "
        MSG_COLOR(MSG_COLOR_RED)
        "großen\nSchlüssel"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er öffnet dir\nden Weg zum Boss\nvon "
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Schloss Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN_ARRAY( endingBlowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Fangstoß"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst die "
        MSG_COLOR(MSG_COLOR_RED)
        "Schildattacke"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Rundumhieb"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Helmspalter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst das "
        MSG_COLOR(MSG_COLOR_RED)
        "Blankziehen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst die\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Riesensprungattacke"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst die\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Riesenwirbelattacke"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Der "
        MSG_COLOR(MSG_COLOR_RED)
        "Kopierstab "
        MSG_COLOR(MSG_COLOR_WHITE)
        "hat wieder\nmagische Kraft! Verwende ihn,\num den antiken Statuen wieder\nLeben einzuhauchen."
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das erste\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das zweite\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das dritte\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das vierte\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das fünfte\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst einen\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Schattenkristall"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Es scheint,\nals würde etwas "
        MSG_COLOR(MSG_COLOR_GREEN)
        "Moos\n"
        MSG_COLOR(MSG_COLOR_WHITE)
        "darauf wachsen.."
    MSG_END()
    MSG_BEGIN_ARRAY( secondFusedShadowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst den zweiten\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Schattenkristall"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Er fühlt sich\n"
        MSG_COLOR(MSG_COLOR_RED)
        "warm "
        MSG_COLOR(MSG_COLOR_WHITE)
        "an.."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdFusedShadowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst den letzten\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Schattenkristall"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Ein Geruch\nvon "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Wasser und Fisch "
        MSG_COLOR(MSG_COLOR_WHITE)
        "steigt\ndir in die Nase.."
    MSG_END()
    MSG_BEGIN_ARRAY( secondMirrorShardDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst die zweite\nScherbe des "
        MSG_COLOR(MSG_COLOR_RED)
        "Schattenspiegels"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nDie "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "vereiste Oberfläche\n"
        MSG_COLOR(MSG_COLOR_WHITE)
        "glitzert im Licht um dich herum.."
    MSG_END()
    MSG_BEGIN_ARRAY( thirdMirrorShardDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst die dritte\nScherbe des "
        MSG_COLOR(MSG_COLOR_RED)
        "Schattenspiegels"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nSie ist übersäht mit Staub und\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Spinnweben"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END()
    MSG_BEGIN_ARRAY( fourthMirrorShardDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst die letzte\nScherbe des "
        MSG_COLOR(MSG_COLOR_RED)
        "Schattenspiegels"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nSie fühlt sich leicht wie eine\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Feder "
        MSG_COLOR(MSG_COLOR_WHITE)
        "an.."
    MSG_END()
    MSG_BEGIN_ARRAY( foolishItemDe )
        MSG_SPEED(MSG_SPEED_FAST)
        "Ein "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "kalter"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind weht.."
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaDe )
        "Was ist los, "
        MSG_PLYR_NAME
        "?"
        MSG_OPTION_LIST(MSG_OPTION_1)
        "Verwandeln\n"
        MSG_OPTION_LIST(MSG_OPTION_2)
        "Teleportieren\n"
        MSG_OPTION_LIST(MSG_OPTION_3)
        "Tageszeit ändern"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletDe )
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
    MSG_BEGIN_ARRAY( giantWalletDe )
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
    
    MsgEntry entriesDe[TOTAL_CUSTOM_MESSAGES] = 
    {
        // Forest Temple small key
        forestSmallKeyDe,
        sizeof(forestSmallKeyDe),
        0x00E9,
        
        // Goron Mines small key
        minesSmallKeyDe,
        sizeof(minesSmallKeyDe),
        0x00EA,
        
        // Lakebed Temple small key
        lakebedSmallKeyDe,
        sizeof(lakebedSmallKeyDe),
        0x00EB,
        
        // Arbiter's Grounds small key
        arbitersSmallKeyDe,
        sizeof(arbitersSmallKeyDe),
        0x00EC,
        
        // Snowpeak Ruins small key
        snowpeakSmallKeyDe,
        sizeof(snowpeakSmallKeyDe),
        0x00ED,
        
        // Temple of Time small key
        timeSmallKeyDe,
        sizeof(timeSmallKeyDe),
        0x00EE,
        
        // City in the Sky small key
        citySmallKeyDe,
        sizeof(citySmallKeyDe),
        0x00EF,
        
        // Palace of Twilight small key
        palaceSmallKeyDe,
        sizeof(palaceSmallKeyDe),
        0x00F0,
        
        // Hyrule Castle small key
        hyruleSmallKeyDe,
        sizeof(hyruleSmallKeyDe),
        0x00F1,
        
        // Bublin Camp small key
        campSmallKeyDe,
        sizeof(campSmallKeyDe),
        0x00F2,
        
        // Shadow Crystal
        shadowCrystalDe,
        sizeof(shadowCrystalDe),
        0x0096,
        
        // Forest Temple dungeon map
        forestDungeonMapDe,
        sizeof(forestDungeonMapDe),
        0x011A,
        
        // Goron Mines dungeon map
        minesDungeonMapDe,
        sizeof(minesDungeonMapDe),
        0x011B,
        
        // Lakebed Temple dungeon map
        lakebedDungeonMapDe,
        sizeof(lakebedDungeonMapDe),
        0x011C,
        
        // Arbiter's Grounds dungeon map
        arbitersDungeonMapDe,
        sizeof(arbitersDungeonMapDe),
        0x011D,
        
        // Snowpeak Ruins dungeon map
        snowpeakDungeonMapDe,
        sizeof(snowpeakDungeonMapDe),
        0x011E,
        
        // Temple of Time dungeon map
        timeDungeonMapDe,
        sizeof(timeDungeonMapDe),
        0x011F,
        
        // City in the Sky dungeon map
        cityDungeonMapDe,
        sizeof(cityDungeonMapDe),
        0x0120,
        
        // Palace of Twilight dungeon map
        palaceDungeonMapDe,
        sizeof(palaceDungeonMapDe),
        0x0121,
        
        // Hyrule Castle dungeon map
        hyruleDungeonMapDe,
        sizeof(hyruleDungeonMapDe),
        0x0122,

        // Forest Temple compass
        forestCompassDe,
        sizeof(forestCompassDe),
        0x00FD,

        // Goron Mines compass
        minesCompassDe,
        sizeof(minesCompassDe),
        0x00FE,
        
        // Lakebed Temple compass
        lakebedCompassDe,
        sizeof(lakebedCompassDe),
        0x00FF,

        // Arbiter's Grounds compass
        arbitersCompassDe,
        sizeof(arbitersCompassDe),
        0x010C,

        // Snowpeak Ruins compass
        snowpeakCompassDe,
        sizeof(snowpeakCompassDe),
        0x010D,

        // Temple of Time compass
        timeCompassDe,
        sizeof(timeCompassDe),
        0x010E,

        // City in the Sky compass
        cityCompassDe,
        sizeof(cityCompassDe),
        0x010F,

        // Palace of Twilight compass
        palaceCompassDe,
        sizeof(palaceCompassDe),
        0x0110,

        // Hyrule Castle compass
        hyruleCompassDe,
        sizeof(hyruleCompassDe),
        0x0111,

        // Forest Temple big key
        forestBigKeyDe,
        sizeof(forestBigKeyDe),
        0x00F6,

        // Lakebed Temple big key
        lakebedBigKeyDe,
        sizeof(lakebedBigKeyDe),
        0x00F7,

        // Arbiter's Grounds big key
        arbitersBigKeyDe,
        sizeof(arbitersBigKeyDe),
        0x00F8,

        // Temple of Time big key
        timeBigKeyDe,
        sizeof(timeBigKeyDe),
        0x00F9,

        // City in the Sky big key
        cityBigKeyDe,
        sizeof(cityBigKeyDe),
        0x00FA,

        // Palace of Twilight big key
        palaceBigKeyDe,
        sizeof(palaceBigKeyDe),
        0x00FB,

        // Hyrule Castle big key
        hyruleBigKeyDe,
        sizeof(hyruleBigKeyDe),
        0x00FC,
        
        // Ending Blow hidden skill
        endingBlowDe,
        sizeof(endingBlowDe),
        0x0145,

        // Shield Attack hidden skill
        shieldAttackDe,
        sizeof(shieldAttackDe),
        0x0146,

        // Back Slice hidden skill
        backSliceDe,
        sizeof(backSliceDe),
        0x0147,

        // Helm Splitter hidden skill
        helmSplitterDe,
        sizeof(helmSplitterDe),
        0x0148,

        // Mortal Draw hidden skill
        mortalDrawDe,
        sizeof(mortalDrawDe),
        0x0149,

        // Jump Strike hidden skill
        jumpStrikeDe,
        sizeof(jumpStrikeDe),
        0x014A,

        // Great Spin hidden skill
        greatSpinDe,
        sizeof(greatSpinDe),
        0x014B,

        // Powered up Dominion Rod
        poweredRodDe,
        sizeof(poweredRodDe),
        0x00B0,

        // First Ancient Sky Book character
        firstCharacterDe,
        sizeof(firstCharacterDe),
        0x013F,

        // Second Ancient Sky Book character
        secondCharacterDe,
        sizeof(secondCharacterDe),
        0x0140,

        // Third Ancient Sky Book character
        thirdCharacterDe,
        sizeof(thirdCharacterDe),
        0x0141,

        // Fourth Ancient Sky Book character
        fourthCharacterDe,
        sizeof(fourthCharacterDe),
        0x0142,

        // Fifth Ancient Sky Book character
        fifthCharacterDe,
        sizeof(fifthCharacterDe),
        0x0143,

        // Sixth Ancient Sky Book character
        firstFusedShadowDe,
        sizeof(firstFusedShadowDe),
        0x013C,

        // Second Fused Shadow
        secondFusedShadowDe,
        sizeof(secondFusedShadowDe),
        0x013D,

        // Third Fused Shadow
        thirdFusedShadowDe,
        sizeof(thirdFusedShadowDe),
        0x013E,

        // Second Mirror Shard
        secondMirrorShardDe,
        sizeof(secondMirrorShardDe),
        0x0109,

        // Third Mirror Shard
        thirdMirrorShardDe,
        sizeof(thirdMirrorShardDe),
        0x010A,

        // Fourth Mirror Shard
        fourthMirrorShardDe,
        sizeof(fourthMirrorShardDe),
        0x010B,

        // Foolish Item
        foolishItemDe,
        sizeof(foolishItemDe),
        0x00F3,

        // Talking to Midna
        talkToMidnaDe,
        sizeof(talkToMidnaDe),
        0x0BBB,

        // Big Wallet
        bigWalletDe,
        sizeof(bigWalletDe),
        0x0099,

        // Giant Wallet
        giantWalletDe,
        sizeof(giantWalletDe),
        0x009A,
    };

}     // namespace mod::customMessages
#endif