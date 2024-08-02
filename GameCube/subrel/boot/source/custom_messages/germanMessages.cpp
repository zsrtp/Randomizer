// This file should only be used for EU
#ifdef TP_EU

#include "customMessages.h"
#include "tp/resource.h"
#include "item_wheel_menu.h"
#include "game_patch/game_patch.h"

#include <cstdint>
#include <cstdio>
#include <cinttypes>

namespace mod::customMessages
{
    using namespace item_wheel_menu;

    // Disable formatting for the textbox messages because it makes things look weird.
    // clang-format off
    MSG_BEGIN_ARRAY(forestSmallKeyDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20"
        MSG_COLOR(MSG_COLOR_RED)
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        " %s %s\n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY(shadowCrystalDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(endingBlowDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst den 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Fangstoß
        "\x46\x61\x6e\x67\x73\x74\x6f\xdf"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(shieldAttackDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst die 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x69\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Schildattacke
        "\x53\x63\x68\x69\x6c\x64\x61\x74\x74\x61\x63\x6b\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(backSliceDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst den 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Rundumhieb
        "\x52\x75\x6e\x64\x75\x6d\x68\x69\x65\x62"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(helmSplitterDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst den 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x65\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Helmspalter
        "\x48\x65\x6c\x6d\x73\x70\x61\x6c\x74\x65\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(mortalDrawDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst das 
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x61\x73\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Blankziehen
        "\x42\x6c\x61\x6e\x6b\x7a\x69\x65\x68\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(jumpStrikeDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst die
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x69\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Riesensprungattacke
        "\x52\x69\x65\x73\x65\x6e\x73\x70\x72\x75\x6e\x67\x61\x74\x74\x61\x63\x6b\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(greatSpinDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erlernst die
        "\x44\x75\x20\x65\x72\x6c\x65\x72\x6e\x73\x74\x20\x64\x69\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Riesenwirbelattacke
        "\x52\x69\x65\x73\x65\x6e\x77\x69\x72\x62\x65\x6c\x61\x74\x74\x61\x63\x6b\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(poweredRodDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Der 
        "\x44\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Kopierstab 
        "\x4b\x6f\x70\x69\x65\x72\x73\x74\x61\x62\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //hat wiedermagische Kraft! Verwende ihn,um den antiken Statuen wiederLeben einzuhauchen.
        "\x68\x61\x74\x20\x77\x69\x65\x64\x65\x72\x0A\x6d\x61\x67\x69\x73\x63\x68\x65\x20\x4b\x72\x61\x66\x74\x21\x20\x56\x65\x72\x77\x65\x6e\x64\x65\x20\x69\x68\x6e\x2c\x0A\x75\x6d\x20\x64\x65\x6e\x20\x61\x6e\x74\x69\x6b\x65\x6e\x20\x53\x74\x61\x74\x75\x65\x6e\x20\x77\x69\x65\x64\x65\x72\x0A\x4c\x65\x62\x65\x6e\x20\x65\x69\x6e\x7a\x75\x68\x61\x75\x63\x68\x65\x6e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(skyBookCharacterDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Du entdeckst ein
        "\x44\x75\x20\x65\x6E\x74\x64\x65\x63\x6B\x73\x74\x0A\x65\x69\x6E\x20" 
        MSG_COLOR(MSG_COLOR_RED)
        // kumulanisches Zeichen
        "\x6B\x75\x6D\x75\x6C\x61\x6E\x69\x73\x63\x68\x65\x73\x20\x5A\x65\x69\x63\x68\x65\x6E"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\nDu hast bisher
        "\x21\x0A\x44\x75\x20\x68\x61\x73\x74\x20\x62\x69\x73\x68\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // gesammelt.
        "\x20\x67\x65\x73\x61\x6d\x6d\x65\x6c\x74\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(firstFusedShadowDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(secondFusedShadowDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(thirdFusedShadowDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(firstMirrorShardDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Du hast die erste
        "\x44\x75\x20\x68\x61\x73\x74\x20\x64\x69\x65\x20\x65\x72\x73\x74\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Schattenspiegels
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x73\x70\x69\x65\x67\x65\x6c\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        // gefunden! Sie ist von
        "\x67\x65\x66\x75\x6E\x64\x65\x6E\x21\x0A\x53\x69\x65\x20\x69\x73\x74\x20\x76\x6F\x6E\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        // Sand
        "\x53\x61\x6E\x64"
        MSG_COLOR(MSG_COLOR_WHITE)
        // bedeckt...
        "\x20\x62\x65\x64\x65\x63\x6B\x74\x2E\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY(secondMirrorShardDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Du erhältst die zweite Scherbe des 
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
    MSG_END();
    MSG_BEGIN_ARRAY(thirdMirrorShardDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(fourthMirrorShardDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(foolishItemDe)
        MSG_SPEED(MSG_SPEED_FAST)
        //Ein 
        "\x45\x69\x6e\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //kalter
        "\x6b\x61\x6c\x74\x65\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        // wind weht..
        "\x20\x77\x69\x6e\x64\x20\x77\x65\x68\x74\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(talkToMidnaDe)
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
    MSG_END();
    MSG_BEGIN_ARRAY(bigWalletDe)
        MSG_COLOR(MSG_COLOR_RED)
        "\x47\x72\x6f\xdf\x65\x20\x47\x65\x6c\x64\x62\xf6\x72\x73\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x65\x72\x68\x61\x6c\x74\x65\x6e\x2e\x20\x49\x6e\x20\x69\x68\x72\x20\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x62\x69\x73\x20\x7a\x75\x20"
        MSG_COLOR(MSG_COLOR_RED)
        "\x35\x30\x30\x30\x20\x52\x75\x62\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x61\x75\x66\x62\x65\x77\x61\x68\x72\x65\x6e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(giantWalletDe)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        "\x4d\x61\x78\x69\x2d\x47\x65\x6c\x64\x62\xf6\x72\x73\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x65\x72\x68\x61\x6c\x74\x65\x6e\x2e\x20\x49\x6e\x20\x69\x68\x72\x20\x6b\x61\x6e\x6e\x73\x74\x20\x64\x75\x20\x62\x69\x73\x20\x7a\x75\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "\x39\x39\x39\x39\x20\x52\x75\x62\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\x61\x75\x66\x62\x65\x77\x61\x68\x72\x65\x6e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(smallWalletPauseDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Schon seit vielen Jahren in deinem Besitz. Sie fasst bis zu 1000 Rubine.
        "\x53\x63\x68\x6F\x6E\x20\x73\x65\x69\x74\x20\x76\x69\x65\x6C\x65\x6E\x20\x4A\x61\x68\x72\x65\x6E\x20\x69\x6E\x0A\x64\x65\x69\x6E\x65\x6D\x20\x42\x65\x73\x69\x74\x7A\x2E\x20\x53\x69\x65\x20\x66\x61\x73\x73\x74\x20\x62\x69\x73\x0A\x7A\x75\x20\x31\x30\x30\x30\x20\x52\x75\x62\x69\x6E\x65\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY(bigWalletPauseDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Geldbörse von Agnetha, der Königin des Insektenreichs. Bewahre in ihr bis zu 5000 Rubine auf!
        "\x47\x65\x6C\x64\x62\xF6\x72\x73\x65\x20\x76\x6F\x6E\x20\x41\x67\x6E\x65\x74\x68\x61\x2C\x20\x64\x65\x72\x20\x4B\xF6\x6E\x69\x67\x69\x6E\x0A\x64\x65\x73\x20\x49\x6E\x73\x65\x6B\x74\x65\x6E\x72\x65\x69\x63\x68\x73\x2E\x20\x42\x65\x77\x61\x68\x72\x65\x20\x69\x6E\x20\x69\x68\x72\x0A\x62\x69\x73\x20\x7A\x75\x20\x35\x30\x30\x30\x20\x52\x75\x62\x69\x6E\x65\x20\x61\x75\x66\x21"
    MSG_END();
    MSG_BEGIN_ARRAY(giantWalletPauseDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Ein Geschenk von Agnetha: Höchste Auszeichnung, die das Insektenreich bietet. Fasst bis zu 9999 Rubine.
        "\x45\x69\x6E\x20\x47\x65\x73\x63\x68\x65\x6E\x6B\x20\x76\x6F\x6E\x20\x41\x67\x6E\x65\x74\x68\x61\x3A\x20\x48\xF6\x63\x68\x73\x74\x65\x0A\x41\x75\x73\x7A\x65\x69\x63\x68\x6E\x75\x6E\x67\x2C\x20\x64\x69\x65\x20\x64\x61\x73\x20\x49\x6E\x73\x65\x6B\x74\x65\x6E\x72\x65\x69\x63\x68\x0A\x62\x69\x65\x74\x65\x74\x2E\x20\x46\x61\x73\x73\x74\x20\x62\x69\x73\x20\x7A\x75\x20\x39\x39\x39\x39\x20\x52\x75\x62\x69\x6E\x65\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY(poeSoulDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Du erhältst eine
        "\x44\x75\x20\x65\x72\x68\xe4\x6c\x74\x73\x74\x20\x65\x69\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Geisterseele
        "\x47\x65\x69\x73\x74\x65\x72\x73\x65\x65\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!\nDu hast bisher
        "\x21\x0a\x44\x75\x20\x68\x61\x73\x74\x20\x62\x69\x73\x68\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // gesammelt.
        "\x20\x67\x65\x73\x61\x6d\x6d\x65\x6c\x74\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(skyBookDescriptionDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Text, der in altem Kumulanisch ver-\nfasst ist. Leider fehlen einige Buchstaben.\nEr enthält wichtige Hinweise 
        // für die Reise\nnach Kumula.\n\nDu hast bisher 0
        "\x54\x65\x78\x74\x2C\x20\x64\x65\x72\x20\x69\x6E\x20\x61\x6C\x74\x65\x6D\x20\x4B\x75\x6D\x75\x6C\x61\x6E\x69\x73\x63\x68\x20\x76\x65\x72\x2D\x0A\x66\x61\x73\x73\x74\x20\x69\x73\x74\x2E\x20\x4C\x65\x69\x64\x65\x72\x20\x66\x65\x68\x6C\x65\x6E\x20\x65\x69\x6E\x69\x67\x65\x20\x42\x75\x63\x68\x73\x74\x61\x62\x65\x6E\x2E\x0A\x45\x72\x20\x65\x6E\x74\x68\xE4\x6C\x74\x20\x77\x69\x63\x68\x74\x69\x67\x65\x20\x48\x69\x6E\x77\x65\x69\x73\x65\x20\x66\xFC\x72\x20\x64\x69\x65\x20\x52\x65\x69\x73\x65\x0A\x6E\x61\x63\x68\x20\x4B\x75\x6D\x75\x6C\x61\x2E\x0A\x0A\x44\x75\x20\x68\x61\x73\x74\x20\x62\x69\x73\x68\x65\x72\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // gesammelt.
        "\x20\x67\x65\x73\x61\x6d\x6d\x65\x6c\x74\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(charloDonationDe)
        // ...eine kleine Spende? Für den Frieden in Hyrule?
        "\x2E\x2E\x2E\x65\x69\x6E\x65\x20\x6B\x6C\x65\x69\x6E\x65\x20\x53\x70\x65\x6E\x64\x65\x3F\x0A\x46\xFC\x72\x20\x64\x65\x6E\x20\x46\x72\x69\x65\x64\x65\x6E\x20\x69\x6E\x20\x48\x79\x72\x75\x6C\x65\x3F"
        MSG_OPTION_LIST(MSG_OPTION_1) 
        // 100 Rubine
        "\x31\x30\x30\x20\x52\x75\x62\x69\x6E\x65\x0A" 
        MSG_OPTION_LIST(MSG_OPTION_2) 
        // 50 Rubine
        "\x35\x30\x20\x52\x75\x62\x69\x6E\x65\x0A" 
        MSG_OPTION_LIST(MSG_OPTION_3) 
        // Nein danke!
        "\x4E\x65\x69\x6E\x20\x64\x61\x6E\x6B\x65\x21";
    MSG_END();
    MSG_BEGIN_ARRAY(recognitionDe)
        MSG_SPEED(MSG_SPEED_FAST)
        // Das gesamte Randomizer Team möchte sich bei unseren fantastischen Testern bedanken. Ohne euch wäre das Projekt nicht, was es heute ist.
        "\x44\x61\x73\x20\x67\x65\x73\x61\x6D\x74\x65\x20\x52\x61\x6E\x64\x6F\x6D\x69\x7A\x65\x72\x20\x54\x65\x61\x6D\n\x6D\xF6\x63\x68\x74\x65\x20\x73\x69\x63\x68\x20\x62\x65\x69\x20\x75\x6E\x73\x65\x72\x65\x6E\n\x66\x61\x6E\x74\x61\x73\x74\x69\x73\x63\x68\x65\x6E\x20\x54\x65\x73\x74\x65\x72\x6E\x20\x62\x65\x64\x61\x6E\x6B\x65\x6E\x2E\n\x4F\x68\x6E\x65\x20\x65\x75\x63\x68\x20\x77\xE4\x72\x65\x20\x64\x61\x73\x20\x50\x72\x6F\x6A\x65\x6B\x74\n\x6E\x69\x63\x68\x74\x2C\x20\x77\x61\x73\x20\x65\x73\x20\x68\x65\x75\x74\x65\x20\x69\x73\x74: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END();
    
    char forTextDe[] = "\x66\xfc\x72";
    char smallKeyTextDe[] = "\x65\x69\x6e\x65\x6e\x0A\x6b\x6c\x65\x69\x6e\x65\x6e\x20\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"; //einen kleinen Schlüssel
    char dungeonMapTextDe[] = "\x64\x69\x65\x0A\x44\x75\x6e\x67\x65\x6f\x6e\x2d\x4b\x61\x72\x74\x65"; // die Dungeon-Karte
    char compassTextDe[] = "\x64\x65\x6e\x20\x4b\x6f\x6d\x70\x61\x73\x73"; // den Kompass
    char bigKeyTextDe[] = "\x64\x65\x6e\x0A\x67\x72\x6f\xdf\x65\x6e\x20\x53\x63\x68\x6c\xfc\x73\x73\x65\x6c"; // den großen Schlüssel
    char forestTempleTextDe[] = "\x64\x65\x6e\x20\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e"; //den Waldschrein
    char goronMinesTextDe[] = "\x64\x69\x65\x20\x4d\x69\x6e\x65\x6e\x20\x64\x65\x72\x20\x47\x6f\x72\x6f\x6e\x65\x6e"; // die Mine der Goronen
    char lakebedTempleTextDe[] = "\x64\x65\x6e\x20\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e"; // die Seeschrein
    char arbitersGroundsTextDe[] = "\x64\x69\x65\x20\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67"; // die Wüstenburg
    char snowpeakRuinsTextDe[] = "\x64\x69\x65\x20\x42\x65\x72\x67\x72\x75\x69\x6e\x65"; // die Bergruine
    char templeOfTimeTextDe[] = "\x64\x65\x6e\x20\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e"; // den Zeitschrein
    char cityInTheSkyTextDe[] = "\x4b\x75\x6d\x75\x6c\x61"; // Kumula
    char palaceOfTwilightTextDe[] = "\x64\x65\x6e\x20\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74"; // den Schattenpalast
    char hyruleCastleTextDe[] = "\x53\x63\x68\x6c\x6f\x73\x73\x20\x48\x79\x72\x75\x6c\x65"; // Schloss Hyrule
    char bulblinCampTextDe[] = "\x64\x61\x73\x20\x4C\x61\x67\x65\x72\x20\x64\x65\x72\x20\x42\x75\x6C\x62\x6C\x69\x6E\x73"; // das lager der Bulblins
    // clang-format on

    const MsgEntry entriesDe[] = {
        // Forest Temple small key
        forestSmallKeyDe,
        sizeof(forestSmallKeyDe),
        0x00E9,

        // Shadow Crystal
        shadowCrystalDe,
        sizeof(shadowCrystalDe),
        0x0096,

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
        skyBookCharacterDe,
        sizeof(skyBookCharacterDe),
        0x013F,

        // First Fused Shadow
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

        // First Mirror Shard
        firstMirrorShardDe,
        sizeof(firstMirrorShardDe),
        0x0B7,

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
        0x0077,

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

        // Small Wallet Menu Text
        smallWalletPauseDe,
        sizeof(smallWalletPauseDe),
        0x0298,

        // Big Wallet Menu Text
        bigWalletPauseDe,
        sizeof(bigWalletPauseDe),
        0x0299,

        // Giant Wallet Menu Text
        giantWalletPauseDe,
        sizeof(giantWalletPauseDe),
        0x029a,

        // Poe Soul
        poeSoulDe,
        sizeof(poeSoulDe),
        0x0144,

        // Sky Book Item Wheel Description
        skyBookDescriptionDe,
        sizeof(skyBookDescriptionDe),
        0x34d,

        // Recognition text
        recognitionDe,
        sizeof(recognitionDe),
        0x0b44,

        // Special invalid-id texts
        // for
        forTextDe,
        sizeof(forTextDe),
        game_patch::SpecialMessageIds::FOR,

        // Small Key
        smallKeyTextDe,
        sizeof(smallKeyTextDe),
        game_patch::SpecialMessageIds::SMALL_KEY,

        // Dungeon Map
        dungeonMapTextDe,
        sizeof(dungeonMapTextDe),
        game_patch::SpecialMessageIds::DUNGEON_MAP,

        // Compass
        compassTextDe,
        sizeof(compassTextDe),
        game_patch::SpecialMessageIds::COMPASS,

        // Big Key
        bigKeyTextDe,
        sizeof(bigKeyTextDe),
        game_patch::SpecialMessageIds::BIG_KEY,

        // Forest Temple
        forestTempleTextDe,
        sizeof(forestTempleTextDe),
        game_patch::SpecialMessageIds::FOREST_TEMPLE,

        // Goron Mines
        goronMinesTextDe,
        sizeof(goronMinesTextDe),
        game_patch::SpecialMessageIds::GORON_MINES,

        // Lakebed Temple
        lakebedTempleTextDe,
        sizeof(lakebedTempleTextDe),
        game_patch::SpecialMessageIds::LAKEBED_TEMPLE,

        // Arbiter's Grounds
        arbitersGroundsTextDe,
        sizeof(arbitersGroundsTextDe),
        game_patch::SpecialMessageIds::ARBITERS_GROUNDS,

        // Snowpeak Ruins
        snowpeakRuinsTextDe,
        sizeof(snowpeakRuinsTextDe),
        game_patch::SpecialMessageIds::SNOWPEAK_RUINS,

        // Temple of Time
        templeOfTimeTextDe,
        sizeof(templeOfTimeTextDe),
        game_patch::SpecialMessageIds::TEMPLE_OF_TIME,

        // City in the Sky
        cityInTheSkyTextDe,
        sizeof(cityInTheSkyTextDe),
        game_patch::SpecialMessageIds::CITY_IN_THE_SKY,

        // Palace of Twilight
        palaceOfTwilightTextDe,
        sizeof(palaceOfTwilightTextDe),
        game_patch::SpecialMessageIds::PALACE_OF_TWILIGHT,

        // Hyrule Castle
        hyruleCastleTextDe,
        sizeof(hyruleCastleTextDe),
        game_patch::SpecialMessageIds::HYRULE_CASTLE,

        // Bulblin Camp
        bulblinCampTextDe,
        sizeof(bulblinCampTextDe),
        game_patch::SpecialMessageIds::BULBLIN_CAMP,

        // This is an extra section that should go unused, and is only needed for _05_getMsgById in 05_itemMsgFunctions.cpp to
        // ensure that it can properly calculate sizeOut
        "",
        0,
        0xFFFF,
    };

    const uint32_t totalCustomMessagesDe = sizeof(entriesDe) / sizeof(MsgEntry);
    const MsgEntry charloDonationEntryDe = {charloDonationDe, sizeof(charloDonationDe), 0x0355};

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
} // namespace mod::customMessages
#endif