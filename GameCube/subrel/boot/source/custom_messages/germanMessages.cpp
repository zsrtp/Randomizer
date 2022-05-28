#include "main.h"
#include "patch.h"

#include "tp/resource.h"

#include <cstdint>

namespace mod::customMessages
{
    MSG_BEGIN( forestSmallKey )
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
    MSG_BEGIN( minesSmallKey )
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
    MSG_BEGIN( lakebedSmallKey )
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
    MSG_BEGIN( arbitersSmallKey )
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
    MSG_BEGIN( snowpeakSmallKey )
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
    MSG_BEGIN( timeSmallKey )
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
    MSG_BEGIN( citySmallKey )
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
    MSG_BEGIN( palaceSmallKey )
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
    MSG_BEGIN( hyruleSmallKey )
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
    MSG_BEGIN( campSmallKey )
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
    MSG_BEGIN( shadowCrystal )
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
    MSG_BEGIN( forestDungeonMap )
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
    MSG_BEGIN( minesDungeonMap )
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
    MSG_BEGIN( lakebedDungeonMap )
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
    MSG_BEGIN( arbitersDungeonMap )
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
    MSG_BEGIN( snowpeakDungeonMap )
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
    MSG_BEGIN( timeDungeonMap )
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
    MSG_BEGIN( cityDungeonMap )
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
    MSG_BEGIN( palaceDungeonMap )
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
    MSG_BEGIN( hyruleDungeonMap )
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
    MSG_BEGIN( forestCompass )
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
    MSG_BEGIN( minesCompass )
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
    MSG_BEGIN( lakebedCompass )
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
    MSG_BEGIN( arbitersCompass )
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
    MSG_BEGIN( snowpeakCompass )
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
    MSG_BEGIN( timeCompass )
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
    MSG_BEGIN( cityCompass )
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
    MSG_BEGIN( palaceCompass )
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
    MSG_BEGIN( hyruleCompass )
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
    MSG_BEGIN( forestBigKey )
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
    MSG_BEGIN( lakebedBigKey )
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
    MSG_BEGIN( arbitersBigKey )
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
    MSG_BEGIN( timeBigKey )
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
    MSG_BEGIN( cityBigKey )
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
    MSG_BEGIN( palaceBigKey )
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
    MSG_BEGIN( hyruleBigKey )
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
    MSG_BEGIN( endingBlow )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Fangstoß"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( shieldAttack )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst die "
        MSG_COLOR(MSG_COLOR_RED)
        "Schildattacke"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( backSlice )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Rundumhieb"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( helmSplitter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst den "
        MSG_COLOR(MSG_COLOR_RED)
        "Helmspalter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( mortalDraw )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst das "
        MSG_COLOR(MSG_COLOR_RED)
        "Blankziehen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( jumpStrike )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst die\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Riesensprungattacke"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( greatSpin )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erlernst die\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Riesenwirbelattacke"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( poweredRod )
        MSG_SPEED(MSG_SPEED_FAST)
        "Der "
        MSG_COLOR(MSG_COLOR_RED)
        "Kopierstab "
        MSG_COLOR(MSG_COLOR_WHITE)
        "hat wieder\nmagische Kraft! Verwende ihn,\num den antiken Statuen wieder\nLeben einzuhauchen."
    MSG_END()
    MSG_BEGIN( firstCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das erste\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN( secondCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das zweite\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN( thirdCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das dritte\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN( fourthCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das vierte\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN( fifthCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Du erhältst das fünfte\n"
        MSG_COLOR(MSG_COLOR_RED)
        "kumulanische Zeichen"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Damit\nkannst du einen Teil des\nKumulaner-Dokuments lesen!"
    MSG_END()
    MSG_BEGIN( firstFusedShadow )
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
    MSG_BEGIN( secondFusedShadow )
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
    MSG_BEGIN( thirdFusedShadow )
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
    MSG_BEGIN( secondMirrorShard )
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
    MSG_BEGIN( thirdMirrorShard )
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
    MSG_BEGIN( fourthMirrorShard )
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
    MSG_BEGIN( foolishItem )
        MSG_SPEED(MSG_SPEED_FAST)
        "Ein "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "kalter"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind weht.."
    MSG_END()
    MSG_BEGIN( talkToMidna )
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