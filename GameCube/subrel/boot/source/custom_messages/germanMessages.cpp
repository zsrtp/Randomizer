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
    MSG_BEGIN_ARRAY( forestSmallKeyDe )
        MSG_SPEED( MSG_SPEED_FAST )
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir Türenim 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x54\xfc\x72\x65\x6e\x0A\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Waldschrein
        "\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir Türenin den 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x54\xfc\x72\x65\x6e\x0A\x69\x6e\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Minen der Goronen
        "\x4d\x69\x6e\x65\x6e\x20\x64\x65\x72\x20\x47\x6f\x72\x6f\x6e\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedSmallKeyDe )
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir Türenim 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x54\xfc\x72\x65\x6e\x0A\x69\x6d\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Seeschrein
        "\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir Türenin der 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x54\xfc\x72\x65\x6e\x0A\x69\x6e\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Wüstenburg
        "\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir Türenin der 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x54\xfc\x72\x65\x6e\x0A\x69\x6e\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Bergruine
        "\x42\x65\x72\x67\x72\x75\x69\x6e\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dirTüren im 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x0A\x54\xfc\x72\x65\x6e\x20\x69\x6d\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Zeitschrein
        "\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( citySmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dirTüren in 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x0A\x54\xfc\x72\x65\x6e\x20\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Kumula
        "\x4b\x75\x6d\x75\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dirTüren im 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x0A\x54\xfc\x72\x65\x6e\x20\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Schattenpalast
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dirTüren auf 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x0A\x54\xfc\x72\x65\x6e\x20\x61\x75\x66\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Schloss Hyrule
        "\x53\x63\x68\x6c\x6f\x73\x73\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( campSmallKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //kleinenSchlüssel
        "\x6b\x6c\x65\x69\x6e\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dasTor im 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x61\x73\x0A\x54\x6f\x72\x20\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Camp der Bulblins
        "\x43\x61\x6d\x70\x20\x64\x65\x72\x20\x42\x75\x6c\x62\x6c\x69\x6e\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( shadowCrystalDe )
        MSG_SPEED(MSG_SPEED_SLOW)
        //Du erhältst den 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Nachtkristall
        "\x4e\x61\x63\x68\x74\x6b\x72\x69\x73\x74\x61\x6c\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Diese dunkle Manifestation derMacht 
        "\x21\x0A\x44\x69\x65\x73\x65\x20\x64\x75\x6e\x6b\x6c\x65\x20\x4d\x61\x6e\x69\x66\x65\x73\x74\x61\x74\x69\x6f\x6e\x20\x64\x65\x72\x0A\x4d\x61\x63\x68\x74\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Zantos 
        "\x5a\x61\x6e\x74\x6f\x73\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //erlaubt es dir, dichnach Belieben zu verwandeln!
        "\x65\x72\x6c\x61\x75\x62\x74\x20\x65\x73\x20\x64\x69\x72\x2c\x20\x64\x69\x63\x68\x0A\x6e\x61\x63\x68\x20\x42\x65\x6c\x69\x65\x62\x65\x6e\x20\x7a\x75\x20\x76\x65\x72\x77\x61\x6e\x64\x65\x6c\x6e\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( forestDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie im 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Waldschrein
        "\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie in den 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6e\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Minen derGoronen
        "\x4d\x69\x6e\x65\x6e\x20\x64\x65\x72\x0A\x47\x6f\x72\x6f\x6e\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie im 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6d\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Seeschrein
        "\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie in der 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6e\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Wüstenburg
        "\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie in der 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6e\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Bergruine
        "\x42\x65\x72\x67\x72\x75\x69\x6e\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie im 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6d\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Zeitschrein
        "\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie in 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Kumula
        "\x4b\x75\x6d\x75\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie im 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Schattenpalast
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleDungeonMapDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst eine 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Dungeon-Karte
        "\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Verwende sie auf 
        "\x21\x0A\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x73\x69\x65\x20\x61\x75\x66\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Schloss Hyrule
        "\x53\x63\x68\x6c\x6f\x73\x73\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( forestCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzeim 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Waldschrein 
        "\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesCompassDe )
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzein den 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6e\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Minen der Goronen 
        "\x4d\x69\x6e\x65\x6e\x20\x64\x65\x72\x20\x47\x6f\x72\x6f\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzeim 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6d\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Seeschrein 
        "\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzein der 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6e\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Wüstenburg 
        "\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzein der 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6e\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Bergruine 
        "\x42\x65\x72\x67\x72\x75\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzeim 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6d\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Zeitschrein 
        "\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzein 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Kumula 
        "\x4b\x75\x6d\x75\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzeim 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x69\x6d\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Schattenpalast 
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleCompassDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kompass
        "\x4b\x6f\x6d\x70\x61\x73\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Er zeigt dir, wo du die Schätzeauf 
        "\x21\x0A\x45\x72\x20\x7a\x65\x69\x67\x74\x20\x64\x69\x72\x2c\x20\x77\x6f\x20\x64\x75\x20\x64\x69\x65\x20\x53\x63\x68\xe4\x74\x7a\x65\x0A\x61\x75\x66\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Schloss Hyrule 
        "\x53\x63\x68\x6c\x6f\x73\x73\x20\x48\x79\x72\x75\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //findest.
        "\x66\x69\x6e\x64\x65\x73\x74\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( forestBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir denWeg zum Boss des 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x64\x65\x6e\x0A\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x20\x64\x65\x73\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Waldschreins
        "\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir denWeg zum Boss der 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x64\x65\x6e\x0A\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x20\x64\x65\x72\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Seeschreins
        "\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir denWeg zum Boss der 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x64\x65\x6e\x0A\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x20\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Wüstenburg
        "\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir denWeg zum Boss des 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x64\x65\x6e\x0A\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x20\x64\x65\x73\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Zeitschreins
        "\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dir denWeg zum Boss von 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x20\x64\x65\x6e\x0A\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x20\x76\x6f\x6e\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Kumula
        "\x4b\x75\x6d\x75\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dirden Weg zum Bossdes 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x0A\x64\x65\x6e\x20\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x0A\x64\x65\x73\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Schattenpalasts
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleBigKeyDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //großenSchlüssel
        "\x67\x72\x6f\xdf\x65\x6e\x0A\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er öffnet dirden Weg zum Bossvon 
        "\x21\x20\x45\x72\x20\xf6\x66\x66\x6e\x65\x74\x20\x64\x69\x72\x0A\x64\x65\x6e\x20\x57\x65\x67\x20\x7a\x75\x6d\x20\x42\x6f\x73\x73\x0A\x76\x6f\x6e\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Schloss Hyrule
        "\x53\x63\x68\x6c\x6f\x73\x73\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( endingBlowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst den 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Fangstoß
        "\x46\x61\x6e\x67\x73\x74\x6f\xdf"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst die 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x69\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Schildattacke
        "\x53\x63\x68\x69\x6c\x64\x61\x74\x74\x61\x63\x6b\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst den 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Rundumhieb
        "\x52\x75\x6e\x64\x75\x6d\x68\x69\x65\x62"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst den 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Helmspalter
        "\x48\x65\x6c\x6d\x73\x70\x61\x6c\x74\x65\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst das 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x61\x73\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Blankziehen
        "\x42\x6c\x61\x6e\x6b\x7a\x69\x65\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst die
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x69\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Riesensprungattacke
        "\x52\x69\x65\x73\x65\x6e\x73\x70\x72\x75\x6e\x67\x61\x74\x74\x61\x63\x6b\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst die
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x69\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Riesenwirbelattacke
        "\x52\x69\x65\x73\x65\x6e\x77\x69\x72\x62\x65\x6c\x61\x74\x74\x61\x63\x6b\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Der 
        "\x44\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kopierstab 
        "\x4b\x6f\x70\x69\x65\x72\x73\x74\x61\x62\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //hat wiedermagische Kraft! Verwende ihn,um den antiken Statuen wiederLeben einzuhauchen.
        "\x68\x61\x74\x20\x77\x69\x65\x64\x65\x72\x0A\x6d\x61\x67\x69\x73\x63\x68\x65\x20\x4b\x72\x61\x66\x74\x21\x20\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x69\x68\x6e\x2c\x0A\x75\x6d\x20\x64\x65\x6e\x20\x61\x6e\x74\x69\x6b\x65\x6e\x20\x53\x74\x61\x74\x75\x65\x6e\x20\x77\x69\x65\x64\x65\x72\x0A\x4c\x65\x62\x65\x6e\x20\x65\x69\x6e\x7a\x75\x68\x61\x75\x63\x68\x65\x6e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst das erste
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x61\x73\x20\x65\x72\x73\x74\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //kumulanische Zeichen
        "\x6b\x75\x6d\x75\x6c\x61\x6e\x69\x73\x63\x68\x65\x20\x5a\x65\x69\x63\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Damitkannst du einen Teil desKumulaner-Dokuments lesen!
        "\x21\x20\x44\x61\x6d\x69\x74\x0A\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x65\x69\x6e\x65\x6e\x20\x54\x65\x69\x6c\x20\x64\x65\x73\x0A\x4b\x75\x6d\x75\x6c\x61\x6e\x65\x72\x2d\x44\x6f\x6b\x75\x6d\x65\x6e\x74\x73\x20\x6c\x65\x73\x65\x6e\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst das zweite
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x61\x73\x20\x7a\x77\x65\x69\x74\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //kumulanische Zeichen
        "\x6b\x75\x6d\x75\x6c\x61\x6e\x69\x73\x63\x68\x65\x20\x5a\x65\x69\x63\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Damitkannst du einen Teil desKumulaner-Dokuments lesen!
        "\x21\x20\x44\x61\x6d\x69\x74\x0A\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x65\x69\x6e\x65\x6e\x20\x54\x65\x69\x6c\x20\x64\x65\x73\x0A\x4b\x75\x6d\x75\x6c\x61\x6e\x65\x72\x2d\x44\x6f\x6b\x75\x6d\x65\x6e\x74\x73\x20\x6c\x65\x73\x65\x6e\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst das dritte
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x61\x73\x20\x64\x72\x69\x74\x74\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //kumulanische Zeichen
        "\x6b\x75\x6d\x75\x6c\x61\x6e\x69\x73\x63\x68\x65\x20\x5a\x65\x69\x63\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Damitkannst du einen Teil desKumulaner-Dokuments lesen!
        "\x21\x20\x44\x61\x6d\x69\x74\x0A\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x65\x69\x6e\x65\x6e\x20\x54\x65\x69\x6c\x20\x64\x65\x73\x0A\x4b\x75\x6d\x75\x6c\x61\x6e\x65\x72\x2d\x44\x6f\x6b\x75\x6d\x65\x6e\x74\x73\x20\x6c\x65\x73\x65\x6e\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst das vierte
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x61\x73\x20\x76\x69\x65\x72\x74\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //kumulanische Zeichen
        "\x6b\x75\x6d\x75\x6c\x61\x6e\x69\x73\x63\x68\x65\x20\x5a\x65\x69\x63\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Damitkannst du einen Teil desKumulaner-Dokuments lesen!
        "\x21\x20\x44\x61\x6d\x69\x74\x0A\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x65\x69\x6e\x65\x6e\x20\x54\x65\x69\x6c\x20\x64\x65\x73\x0A\x4b\x75\x6d\x75\x6c\x61\x6e\x65\x72\x2d\x44\x6f\x6b\x75\x6d\x65\x6e\x74\x73\x20\x6c\x65\x73\x65\x6e\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst das fünfte
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x61\x73\x20\x66\xfc\x6e\x66\x74\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //kumulanische Zeichen
        "\x6b\x75\x6d\x75\x6c\x61\x6e\x69\x73\x63\x68\x65\x20\x5a\x65\x69\x63\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Damitkannst du einen Teil desKumulaner-Dokuments lesen!
        "\x21\x20\x44\x61\x6d\x69\x74\x0A\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x65\x69\x6e\x65\x6e\x20\x54\x65\x69\x6c\x20\x64\x65\x73\x0A\x4b\x75\x6d\x75\x6c\x61\x6e\x65\x72\x2d\x44\x6f\x6b\x75\x6d\x65\x6e\x74\x73\x20\x6c\x65\x73\x65\x6e\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst einen
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x6e\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenkristall
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x6b\x72\x69\x73\x74\x61\x6c\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Es scheint,als würde etwas 
        "\x21\x20\x45\x73\x20\x73\x63\x68\x65\x69\x6e\x74\x2c\x0A\x61\x6c\x73\x20\x77\xfc\x72\x64\x65\x20\x65\x74\x77\x61\x73\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Moos
        "\x4d\x6f\x6f\x73\x0A"
        MSG_COLOR(MSG_COLOR_WHITE)
        //darauf wachsen..
        "\x64\x61\x72\x61\x75\x66\x20\x77\x61\x63\x68\x73\x65\x6e\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( secondFusedShadowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst den zweiten
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x65\x6e\x20\x7a\x77\x65\x69\x74\x65\x6e\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenkristall
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x6b\x72\x69\x73\x74\x61\x6c\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Er fühlt sich
        "\x21\x20\x45\x72\x20\x66\xfc\x68\x6c\x74\x20\x73\x69\x63\x68\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //warm 
        "\x77\x61\x72\x6d\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //an..
        "\x61\x6e\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdFusedShadowDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst den letzten
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x65\x6e\x20\x6c\x65\x74\x7a\x74\x65\x6e\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenkristall
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x6b\x72\x69\x73\x74\x61\x6c\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ein Geruchvon 
        "\x21\x20\x45\x69\x6e\x20\x47\x65\x72\x75\x63\x68\x0A\x76\x6f\x6e\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Wasser und Fisch 
        "\x57\x61\x73\x73\x65\x72\x20\x75\x6e\x64\x20\x46\x69\x73\x63\x68\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //steigtdir in die Nase..
        "\x73\x74\x65\x69\x67\x74\x0A\x64\x69\x72\x20\x69\x6e\x20\x64\x69\x65\x20\x4e\x61\x73\x65\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( secondMirrorShardDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst die zweiteScherbe des 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x69\x65\x20\x7a\x77\x65\x69\x74\x65\x0A\x53\x63\x68\x65\x72\x62\x65\x20\x64\x65\x73\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenspiegels
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x73\x70\x69\x65\x67\x65\x6c\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Die 
        "\x21\x0A\x44\x69\x65\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //vereiste Oberfläche
        "\x76\x65\x72\x65\x69\x73\x74\x65\x20\x4f\x62\x65\x72\x66\x6c\xe4\x63\x68\x65\x0A"
        MSG_COLOR(MSG_COLOR_WHITE)
        //glitzert im Licht um dich herum..
        "\x67\x6c\x69\x74\x7a\x65\x72\x74\x20\x69\x6d\x20\x4c\x69\x63\x68\x74\x20\x75\x6d\x20\x64\x69\x63\x68\x20\x68\x65\x72\x75\x6d\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdMirrorShardDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst die dritteScherbe des 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x69\x65\x20\x64\x72\x69\x74\x74\x65\x0A\x53\x63\x68\x65\x72\x62\x65\x20\x64\x65\x73\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenspiegels
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x73\x70\x69\x65\x67\x65\x6c\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Sie ist übersäht mit Staub und
        "\x21\x0A\x53\x69\x65\x20\x69\x73\x74\x20\xfc\x62\x65\x72\x73\xe4\x68\x74\x20\x6d\x69\x74\x20\x53\x74\x61\x75\x62\x20\x75\x6e\x64\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Spinnweben
        "\x53\x70\x69\x6e\x6e\x77\x65\x62\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //..
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthMirrorShardDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst die letzteScherbe des 
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x64\x69\x65\x20\x6c\x65\x74\x7a\x74\x65\x0A\x53\x63\x68\x65\x72\x62\x65\x20\x64\x65\x73\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenspiegels
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x73\x70\x69\x65\x67\x65\x6c\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Sie fühlt sich leicht wie eine
        "\x21\x0A\x53\x69\x65\x20\x66\xfc\x68\x6c\x74\x20\x73\x69\x63\x68\x20\x6c\x65\x69\x63\x68\x74\x20\x77\x69\x65\x20\x65\x69\x6e\x65\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Feder 
        "\x46\x65\x64\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //an..
        "\x61\x6e\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( foolishItemDe )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ein 
        "\x45\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //kalter
        "\x6b\x61\x6c\x74\x65\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        // wind weht..
        "\x20\x77\x69\x6e\x64\x20\x77\x65\x68\x74\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaDe )
        //Was ist los, 
        "\x57\x61\x73\x20\x69\x73\x74\x20\x6c\x6f\x73\x2c\x20"
        MSG_PLYR_NAME
        //?
        "\x3f"
        MSG_OPTION_LIST(MSG_OPTION_1)
        //Verwandeln
        "\x56\x65\x72\x77\x61\x6e\x64\x65\x6c\x6e\x0A"
        MSG_OPTION_LIST(MSG_OPTION_2)
        //Teleportieren
        "\x54\x65\x6c\x65\x70\x6f\x72\x74\x69\x65\x72\x65\x6e\x0A"
        MSG_OPTION_LIST(MSG_OPTION_3)
        //Tageszeit ändern
        "\x54\x61\x67\x65\x73\x7a\x65\x69\x74\x20\xe4\x6e\x64\x65\x72\x6e"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletDe )
        MSG_COLOR(MSG_COLOR_RED)
        "\x47\x72\x6f\xdf\x65\x20\x47\x65\x6c\x64\x62\xf6\x72\x73\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x65\x72\x68\x61\x6c\x74\x65\x6e\x2e\x20\x49\x6e\x20\x69\x68\x72\x20\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x62\x69\x73\x20\x7a\x75\x20"
        MSG_COLOR(MSG_COLOR_RED)
        "\x35\x30\x30\x30\x20\x52\x75\x62\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x61\x75\x66\x62\x65\x77\x61\x68\x72\x65\x6e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletDe )
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        "\x4d\x61\x78\x69\x2d\x47\x65\x6c\x64\x62\xf6\x72\x73\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x65\x72\x68\x61\x6c\x74\x65\x6e\x2e\x20\x49\x6e\x20\x69\x68\x72\x20\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x62\x69\x73\x20\x7a\x75\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "\x39\x39\x39\x39\x20\x52\x75\x62\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x61\x75\x66\x62\x65\x77\x61\x68\x72\x65\x6e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( smallWalletPauseDe )
        MSG_SPEED(MSG_SPEED_FAST)
        // Schon seit vielen Jahren in deinem Besitz. Sie fasst bis zu 1000 Rubine.
        "\x53\x63\x68\x6F\x6E\x20\x73\x65\x69\x74\x20\x76\x69\x65\x6C\x65\x6E\x20\x4A\x61\x68\x72\x65\x6E\x20\x69\x6E\x0A\x64\x65\x69\x6E\x65\x6D\x20\x42\x65\x73\x69\x74\x7A\x2E\x20\x53\x69\x65\x20\x66\x61\x73\x73\x74\x20\x62\x69\x73\x0A\x7A\x75\x20\x31\x30\x30\x30\x20\x52\x75\x62\x69\x6E\x65\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletPauseDe )
        MSG_SPEED(MSG_SPEED_FAST)
        // Geldbörse von Agnetha, der Königin des Insektenreichs. Bewahre in ihr bis zu 5000 Rubine auf!
        "\x47\x65\x6C\x64\x62\xF6\x72\x73\x65\x20\x76\x6F\x6E\x20\x41\x67\x6E\x65\x74\x68\x61\x2C\x20\x64\x65\x72\x20\x4B\xF6\x6E\x69\x67\x69\x6E\x0A\x64\x65\x73\x20\x49\x6E\x73\x65\x6B\x74\x65\x6E\x72\x65\x69\x63\x68\x73\x2E\x20\x42\x65\x77\x61\x68\x72\x65\x20\x69\x6E\x20\x69\x68\x72\x0A\x62\x69\x73\x20\x7A\x75\x20\x35\x30\x30\x30\x20\x52\x75\x62\x69\x6E\x65\x20\x61\x75\x66\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletPauseDe )
        MSG_SPEED(MSG_SPEED_FAST)
        // Ein Geschenk von Agnetha: Höchste Auszeichnung, die das Insektenreich bietet. Fasst bis zu 9999 Rubine.
        "\x45\x69\x6E\x20\x47\x65\x73\x63\x68\x65\x6E\x6B\x20\x76\x6F\x6E\x20\x41\x67\x6E\x65\x74\x68\x61\x3A\x20\x48\xF6\x63\x68\x73\x74\x65\x0A\x41\x75\x73\x7A\x65\x69\x63\x68\x6E\x75\x6E\x67\x2C\x20\x64\x69\x65\x20\x64\x61\x73\x20\x49\x6E\x73\x65\x6B\x74\x65\x6E\x72\x65\x69\x63\x68\x0A\x62\x69\x65\x74\x65\x74\x2E\x20\x46\x61\x73\x73\x74\x20\x62\x69\x73\x20\x7A\x75\x20\x39\x39\x39\x39\x20\x52\x75\x62\x69\x6E\x65\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( charloDonationDe )
        // ...eine kleine Spende? Für den Frieden in Hyrule?
        "\x2E\x2E\x2E\x65\x69\x6E\x65\x20\x6B\x6C\x65\x69\x6E\x65\x20\x53\x70\x65\x6E\x64\x65\x3F\x0A\x46\xFC\x72\x20\x64\x65\x6E\x20\x46\x72\x69\x65\x64\x65\x6E\x20\x69\x6E\x20\x48\x79\x72\x75\x6C\x65\x3F"
        MSG_OPTION_LIST( MSG_OPTION_1 ) 
        // 100 Rubine
        "\x31\x30\x30\x20\x52\x75\x62\x69\x6E\x65\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_2 ) 
        // 50 Rubine
        "\x35\x30\x20\x52\x75\x62\x69\x6E\x65\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_3 ) 
        // Nein danke!
        "\x4E\x65\x69\x6E\x20\x64\x61\x6E\x6B\x65\x21";
    MSG_END()

    MSG_BEGIN_ARRAY( recognitionDe )
        MSG_SPEED(MSG_SPEED_FAST)
        // Das gesamte Randomizer Team möchte sich bei unseren fantastischen Testern bedanken. Ohne euch wäre das Projekt nicht, was es heute ist.
        "\x44\x61\x73\x20\x67\x65\x73\x61\x6D\x74\x65\x20\x52\x61\x6E\x64\x6F\x6D\x69\x7A\x65\x72\x20\x54\x65\x61\x6D\n\x6D\xF6\x63\x68\x74\x65\x20\x73\x69\x63\x68\x20\x62\x65\x69\x20\x75\x6E\x73\x65\x72\x65\x6E\n\x66\x61\x6E\x74\x61\x73\x74\x69\x73\x63\x68\x65\x6E\x20\x54\x65\x73\x74\x65\x72\x6E\x20\x62\x65\x64\x61\x6E\x6B\x65\x6E\x2E\n\x4F\x68\x6E\x65\x20\x65\x75\x63\x68\x20\x77\xE4\x72\x65\x20\x64\x61\x73\x20\x50\x72\x6F\x6A\x65\x6B\x74\n\x6E\x69\x63\x68\x74\x2C\x20\x77\x61\x73\x20\x65\x73\x20\x68\x65\x75\x74\x65\x20\x69\x73\x74: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END()
        // clang-format on

        MsgEntry entriesDe[TOTAL_CUSTOM_MESSAGES] = {
            // Forest Temple small key
            forestSmallKeyDe,
            sizeof( forestSmallKeyDe ),
            0x00E9,

            // Goron Mines small key
            minesSmallKeyDe,
            sizeof( minesSmallKeyDe ),
            0x00EA,

            // Lakebed Temple small key
            lakebedSmallKeyDe,
            sizeof( lakebedSmallKeyDe ),
            0x00EB,

            // Arbiter's Grounds small key
            arbitersSmallKeyDe,
            sizeof( arbitersSmallKeyDe ),
            0x00EC,

            // Snowpeak Ruins small key
            snowpeakSmallKeyDe,
            sizeof( snowpeakSmallKeyDe ),
            0x00ED,

            // Temple of Time small key
            timeSmallKeyDe,
            sizeof( timeSmallKeyDe ),
            0x00EE,

            // City in the Sky small key
            citySmallKeyDe,
            sizeof( citySmallKeyDe ),
            0x00EF,

            // Palace of Twilight small key
            palaceSmallKeyDe,
            sizeof( palaceSmallKeyDe ),
            0x00F0,

            // Hyrule Castle small key
            hyruleSmallKeyDe,
            sizeof( hyruleSmallKeyDe ),
            0x00F1,

            // Bulblin Camp small key
            campSmallKeyDe,
            sizeof( campSmallKeyDe ),
            0x00F2,

            // Shadow Crystal
            shadowCrystalDe,
            sizeof( shadowCrystalDe ),
            0x0096,

            // Forest Temple dungeon map
            forestDungeonMapDe,
            sizeof( forestDungeonMapDe ),
            0x011A,

            // Goron Mines dungeon map
            minesDungeonMapDe,
            sizeof( minesDungeonMapDe ),
            0x011B,

            // Lakebed Temple dungeon map
            lakebedDungeonMapDe,
            sizeof( lakebedDungeonMapDe ),
            0x011C,

            // Arbiter's Grounds dungeon map
            arbitersDungeonMapDe,
            sizeof( arbitersDungeonMapDe ),
            0x011D,

            // Snowpeak Ruins dungeon map
            snowpeakDungeonMapDe,
            sizeof( snowpeakDungeonMapDe ),
            0x011E,

            // Temple of Time dungeon map
            timeDungeonMapDe,
            sizeof( timeDungeonMapDe ),
            0x011F,

            // City in the Sky dungeon map
            cityDungeonMapDe,
            sizeof( cityDungeonMapDe ),
            0x0120,

            // Palace of Twilight dungeon map
            palaceDungeonMapDe,
            sizeof( palaceDungeonMapDe ),
            0x0121,

            // Hyrule Castle dungeon map
            hyruleDungeonMapDe,
            sizeof( hyruleDungeonMapDe ),
            0x0122,

            // Forest Temple compass
            forestCompassDe,
            sizeof( forestCompassDe ),
            0x00FD,

            // Goron Mines compass
            minesCompassDe,
            sizeof( minesCompassDe ),
            0x00FE,

            // Lakebed Temple compass
            lakebedCompassDe,
            sizeof( lakebedCompassDe ),
            0x00FF,

            // Arbiter's Grounds compass
            arbitersCompassDe,
            sizeof( arbitersCompassDe ),
            0x010C,

            // Snowpeak Ruins compass
            snowpeakCompassDe,
            sizeof( snowpeakCompassDe ),
            0x010D,

            // Temple of Time compass
            timeCompassDe,
            sizeof( timeCompassDe ),
            0x010E,

            // City in the Sky compass
            cityCompassDe,
            sizeof( cityCompassDe ),
            0x010F,

            // Palace of Twilight compass
            palaceCompassDe,
            sizeof( palaceCompassDe ),
            0x0110,

            // Hyrule Castle compass
            hyruleCompassDe,
            sizeof( hyruleCompassDe ),
            0x0111,

            // Forest Temple big key
            forestBigKeyDe,
            sizeof( forestBigKeyDe ),
            0x00F6,

            // Lakebed Temple big key
            lakebedBigKeyDe,
            sizeof( lakebedBigKeyDe ),
            0x00F7,

            // Arbiter's Grounds big key
            arbitersBigKeyDe,
            sizeof( arbitersBigKeyDe ),
            0x00F8,

            // Temple of Time big key
            timeBigKeyDe,
            sizeof( timeBigKeyDe ),
            0x00F9,

            // City in the Sky big key
            cityBigKeyDe,
            sizeof( cityBigKeyDe ),
            0x00FA,

            // Palace of Twilight big key
            palaceBigKeyDe,
            sizeof( palaceBigKeyDe ),
            0x00FB,

            // Hyrule Castle big key
            hyruleBigKeyDe,
            sizeof( hyruleBigKeyDe ),
            0x00FC,

            // Ending Blow hidden skill
            endingBlowDe,
            sizeof( endingBlowDe ),
            0x0145,

            // Shield Attack hidden skill
            shieldAttackDe,
            sizeof( shieldAttackDe ),
            0x0146,

            // Back Slice hidden skill
            backSliceDe,
            sizeof( backSliceDe ),
            0x0147,

            // Helm Splitter hidden skill
            helmSplitterDe,
            sizeof( helmSplitterDe ),
            0x0148,

            // Mortal Draw hidden skill
            mortalDrawDe,
            sizeof( mortalDrawDe ),
            0x0149,

            // Jump Strike hidden skill
            jumpStrikeDe,
            sizeof( jumpStrikeDe ),
            0x014A,

            // Great Spin hidden skill
            greatSpinDe,
            sizeof( greatSpinDe ),
            0x014B,

            // Powered up Dominion Rod
            poweredRodDe,
            sizeof( poweredRodDe ),
            0x00B0,

            // First Ancient Sky Book character
            firstCharacterDe,
            sizeof( firstCharacterDe ),
            0x013F,

            // Second Ancient Sky Book character
            secondCharacterDe,
            sizeof( secondCharacterDe ),
            0x0140,

            // Third Ancient Sky Book character
            thirdCharacterDe,
            sizeof( thirdCharacterDe ),
            0x0141,

            // Fourth Ancient Sky Book character
            fourthCharacterDe,
            sizeof( fourthCharacterDe ),
            0x0142,

            // Fifth Ancient Sky Book character
            fifthCharacterDe,
            sizeof( fifthCharacterDe ),
            0x0143,

            // Sixth Ancient Sky Book character
            firstFusedShadowDe,
            sizeof( firstFusedShadowDe ),
            0x013C,

            // Second Fused Shadow
            secondFusedShadowDe,
            sizeof( secondFusedShadowDe ),
            0x013D,

            // Third Fused Shadow
            thirdFusedShadowDe,
            sizeof( thirdFusedShadowDe ),
            0x013E,

            // Second Mirror Shard
            secondMirrorShardDe,
            sizeof( secondMirrorShardDe ),
            0x0109,

            // Third Mirror Shard
            thirdMirrorShardDe,
            sizeof( thirdMirrorShardDe ),
            0x010A,

            // Fourth Mirror Shard
            fourthMirrorShardDe,
            sizeof( fourthMirrorShardDe ),
            0x010B,

            // Foolish Item
            foolishItemDe,
            sizeof( foolishItemDe ),
            0x0077,

            // Talking to Midna
            talkToMidnaDe,
            sizeof( talkToMidnaDe ),
            0x0BBB,

            // Big Wallet
            bigWalletDe,
            sizeof( bigWalletDe ),
            0x0099,

            // Giant Wallet
            giantWalletDe,
            sizeof( giantWalletDe ),
            0x009A,

            // Small Wallet Menu Text
            smallWalletPauseDe,
            sizeof( smallWalletPauseDe ),
            0x0298,

            // Big Wallet Menu Text
            bigWalletPauseDe,
            sizeof( bigWalletPauseDe ),
            0x0299,

            // Giant Wallet Menu Text
            giantWalletPauseDe,
            sizeof( giantWalletPauseDe ),
            0x029a,

            // Recognition text
            recognitionDe,
            sizeof( recognitionDe ),
            0x0b44,
    };

    const MsgEntry charloDonationEntryDe = { charloDonationDe, sizeof( charloDonationDe ), 0x0355 };

    const ItemWheelMenuStrings itemWheelMenuStringsDe = {
        // areasBeingTracked
        {
            // Forest Temple
            // Waldschrein
            "\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e",

            // Goron Mines
            // Minen der Goronen
            "\x4d\x69\x6e\x65\x6e\x20\x64\x65\x72\x20\x47\x6f\x72\x6f\x6e\x65\x6e",

            // Lakebed Temple
            // Seeschrein
            "\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e",

            // Arbiter's Grounds
            // Wüstenburg
            "\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67",

            // Snowpeak Ruins
            // Bergruine
            "\x42\x65\x72\x67\x72\x75\x69\x6e\x65",

            // Temple of Time
            // Zeitschrein
            "\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e",

            // City in the Sky
            // Kumula
            "\x4b\x75\x6d\x75\x6c\x61",

            // Palace of Twilight
            // Schattenpalast
            "\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74",

            // Hyrule Castle
            // Schloss Hyrule
            "\x53\x63\x68\x6c\x6f\x73\x73\x20\x48\x79\x72\x75\x6c\x65",

            // Faron Woods
            // Wald von Phirone
            "\x57\x61\x6C\x64\x20\x76\x6F\x6E\x20\x50\x68\x69\x72\x6F\x6E\x65",

            // Bulblin Camp
            // Camp der Bulblins
            "\x43\x61\x6d\x70\x20\x64\x65\x72\x20\x42\x75\x6c\x62\x6c\x69\x6e\x73",
        },

        // seedIsLoaded
        // Seed
        "\x53\x65\x65\x64",

        // seedIsNotLoaded
        // Kein Seed geladen
        "\x4B\x65\x69\x6E\x20\x53\x65\x65\x64\x20\x67\x65\x6C\x61\x64\x65\x6E",

        // yes/no
        // Ja
        "\x4A\x61",

        // Nein
        "\x4E\x65\x69\x6E",

        // shadowsShards
        // Schattenkristalle\nSchattenspiegelscherben
        "\x53\x63\x68\x61\x74\x74\x65\x6E\x6B\x72\x69\x73\x74\x61\x6C\x6C\x65\x0A\x53\x63\x68\x61\x74\x74\x65\x6E\x73\x70\x69"
        "\x65\x67\x65\x6C\x73\x63\x68\x65\x72\x62\x65\x6E",

        // Pumpkin
        // Kürbis
        "\x4B\xFC\x72\x62\x69\x73",

        // Cheese
        // Käse
        "\x4B\xE4\x73\x65",

        // Gate Keys
        // Tor-Schlüssel
        "\x54\x6F\x72\x2D\x53\x63\x68\x6C\xFC\x73\x73\x65\x6C",

        // Areas
        // Regionen
        "\x52\x65\x67\x69\x6F\x6E\x65\x6E",

        // Small Keys
        // kleine\nSchlüssel
        "\x6B\x6C\x65\x69\x6E\x65\x0A\x53\x63\x68\x6C\xFC\x73\x73\x65\x6C",

        // Big Keys
        // große\nSchlüssel
        "\x67\x72\x6F\xDF\x65\x0A\x53\x63\x68\x6C\xFC\x73\x73\x65\x6C",

        // Maps
        // Dungeon-\nKarten
        "\x44\x75\x6E\x67\x65\x6F\x6E\x2D\x0A\x4B\x61\x72\x74\x65\x6E",

        // Compasses
        // Kompasse
        "\x4B\x6F\x6D\x70\x61\x73\x73\x65",

        // helpText
        // Drücke Start\noder Z, um\nzusätzliche\nDaten\nzu zeigen
        "\x44\x72\xFC\x63\x6B\x65\x20\x53\x74\x61\x72\x74\x0A\x6F\x64\x65\x72\x20\x5A\x2C\x20\x75\x6D\x0A\x7A\x75\x73\xE4\x74"
        "\x7A\x6C\x69\x63\x68\x65\x0A\x44\x61\x74\x65\x6E\x0A\x7A\x75\x20\x7A\x65\x69\x67\x65\x6E",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsDe {
        // Fused Shadows/Mirror Shards
        210,

        // Pumpkin
        43,

        // Yes/No
        17,
        7,

        // Cheese
        73,

        // Yes/No
        10,
        0,

        // Gate Keys
        58,

        // Yes/No
        45,
        35,

        // Headers
        // Small Keys
        152,

        // Big Keys
        92,

        // Maps
        92,

        // Compasses
        94,

        // Header values
        // Small Keys values
        32,

        // Big keys values
        // Yes/No
        29,
        19,

        // Goron Mines
        32,

        // Maps values
        // Yes/No
        30,
        21,

        // Compasses values
        // Yes/No
        31,
        22,
    };
}     // namespace mod::customMessages
#endif