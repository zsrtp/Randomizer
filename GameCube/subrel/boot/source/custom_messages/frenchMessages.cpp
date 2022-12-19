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
    MSG_BEGIN_ARRAY( forestSmallKeyFr )
        MSG_SPEED( MSG_SPEED_FAST )
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x20\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Temple Sylvestre
        "\x54\x65\x6d\x70\x6c\x65\x20\x53\x79\x6c\x76\x65\x73\x74\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée dansla 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x64\x61\x6e\x73\x0A\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mine Goron
        "\x4d\x69\x6e\x65\x20\x47\x6f\x72\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x20\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Temple Abyssal
        "\x54\x65\x6d\x70\x6c\x65\x20\x41\x62\x79\x73\x73\x61\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée dans la
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x64\x61\x6e\x73\x20\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Tour du Jugement
        "\x54\x6f\x75\x72\x20\x64\x75\x20\x4a\x75\x67\x65\x6d\x65\x6e\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée aux
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x78\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Ruines des Pics Blancs
        "\x52\x75\x69\x6e\x65\x73\x20\x64\x65\x73\x20\x50\x69\x63\x73\x20\x42\x6c\x61\x6e\x63\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x20\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Temple du Temps
        "\x54\x65\x6d\x70\x6c\x65\x20\x64\x75\x20\x54\x65\x6d\x70\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( citySmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée à
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\xe0\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Célestia
        "\x43\xe9\x6c\x65\x73\x74\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée dansle 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x64\x61\x6e\x73\x0A\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palais du Crépuscule
        "\x50\x61\x6c\x61\x69\x73\x20\x64\x75\x20\x43\x72\xe9\x70\x75\x73\x63\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Château d'Hyrule
        "\x43\x68\xe2\x74\x65\x61\x75\x20\x64\x27\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( campSmallKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //petite clé
        "\x70\x65\x74\x69\x74\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée dansle 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x64\x61\x6e\x73\x0A\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Camp Bulblin
        "\x43\x61\x6d\x70\x20\x42\x75\x6c\x62\x6c\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( shadowCrystalFr )
        MSG_SPEED(MSG_SPEED_SLOW)
        //Vous obtenez le 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristal Maudit
        "\x43\x72\x69\x73\x74\x61\x6c\x20\x4d\x61\x75\x64\x69\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!La sombre manifestation des pouvoirs de Xanto qui permet de se transformer à volonté!
        "\x21\x0A\x4c\x61\x20\x73\x6f\x6d\x62\x72\x65\x20\x6d\x61\x6e\x69\x66\x65\x73\x74\x61\x74\x69\x6f\x6e\x20\x64\x65\x73\x0A\x70\x6f\x75\x76\x6f\x69\x72\x73\x20\x64\x65\x20\x58\x61\x6e\x74\x6f\x20\x71\x75\x69\x20\x70\x65\x72\x6d\x65\x74\x0A\x64\x65\x20\x73\x65\x20\x74\x72\x61\x6e\x73\x66\x6f\x72\x6d\x65\x72\x20\xe0\x20\x76\x6f\x6c\x6f\x6e\x74\xe9\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( forestDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient au
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Temple Sylvestre
        "\x54\x65\x6d\x70\x6c\x65\x20\x53\x79\x6c\x76\x65\x73\x74\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient a la
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\xE0\x20\x6C\x61\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Mine Goron
        "\x4d\x69\x6e\x65\x20\x47\x6f\x72\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient au
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Temple Abyssal
        "\x54\x65\x6d\x70\x6c\x65\x20\x41\x62\x79\x73\x73\x61\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient à la
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\xe0\x20\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Tour du Jugement
        "\x54\x6f\x75\x72\x20\x64\x75\x20\x4a\x75\x67\x65\x6d\x65\x6e\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient aux
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x78\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Ruines des Pics Blancs
        "\x52\x75\x69\x6e\x65\x73\x20\x64\x65\x73\x20\x50\x69\x63\x73\x20\x42\x6c\x61\x6e\x63\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient au
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Temple du Temps
        "\x54\x65\x6d\x70\x6c\x65\x20\x64\x75\x20\x54\x65\x6d\x70\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient à
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\xe0\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Célestia
        "\x43\xe9\x6c\x65\x73\x74\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient au
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palais du Crépuscule
        "\x50\x61\x6c\x61\x69\x73\x20\x64\x75\x20\x43\x72\xe9\x70\x75\x73\x63\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleDungeonMapFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //carte dedonjon
        "\x63\x61\x72\x74\x65\x20\x64\x65\x0A\x64\x6f\x6e\x6a\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Elle appartient au
        "\x21\x20\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Château d'Hyrule
        "\x43\x68\xe2\x74\x65\x61\x75\x20\x64\x27\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( forestCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x20\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Temple Sylvestre
        "\x54\x65\x6d\x70\x6c\x65\x20\x53\x79\x6c\x76\x65\x73\x74\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient a la
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\xE0\x20\x6C\x61\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Mine Goron
        "\x4d\x69\x6e\x65\x20\x47\x6f\x72\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x20\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Temple Abyssal
        "\x54\x65\x6d\x70\x6c\x65\x20\x41\x62\x79\x73\x73\x61\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient à la 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\xe0\x20\x6c\x61\x20\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Tour du Jugement
        "\x54\x6f\x75\x72\x20\x64\x75\x20\x4a\x75\x67\x65\x6d\x65\x6e\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient aux 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x78\x20\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Ruines des Pics Blancs
        "\x52\x75\x69\x6e\x65\x73\x20\x64\x65\x73\x20\x50\x69\x63\x73\x20\x42\x6c\x61\x6e\x63\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x20\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Temple du Temps
        "\x54\x65\x6d\x70\x6c\x65\x20\x64\x75\x20\x54\x65\x6d\x70\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient à 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\xe0\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Célestia
        "\x43\xe9\x6c\x65\x73\x74\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x20\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palais du Crépuscule
        "\x50\x61\x6c\x61\x69\x73\x20\x64\x75\x20\x43\x72\xe9\x70\x75\x73\x63\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleCompassFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez une 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //boussole
        "\x62\x6f\x75\x73\x73\x6f\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle appartient au 
        "\x21\x0A\x45\x6c\x6c\x65\x20\x61\x70\x70\x61\x72\x74\x69\x65\x6e\x74\x20\x61\x75\x20\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Château d'Hyrule
        "\x43\x68\xe2\x74\x65\x61\x75\x20\x64\x27\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( forestBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Temple Sylvestre
        "\x54\x65\x6d\x70\x6c\x65\x20\x53\x79\x6c\x76\x65\x73\x74\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Temple Abyssal
        "\x54\x65\x6d\x70\x6c\x65\x20\x41\x62\x79\x73\x73\x61\x6c"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée dans la
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x64\x61\x6e\x73\x20\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Tour du Jugement
        "\x54\x6f\x75\x72\x20\x64\x75\x20\x4a\x75\x67\x65\x6d\x65\x6e\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Temple du Temps
        "\x54\x65\x6d\x70\x6c\x65\x20\x64\x75\x20\x54\x65\x6d\x70\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée à
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\xe0\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Célestia
        "\x43\xe9\x6c\x65\x73\x74\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palais du Crépuscule
        "\x50\x61\x6c\x61\x69\x73\x20\x64\x75\x20\x43\x72\xe9\x70\x75\x73\x63\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleBigKeyFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //la grande clé
        "\x6c\x61\x20\x67\x72\x61\x6e\x64\x65\x20\x63\x6c\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut être utilisée au
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\xea\x74\x72\x65\x20\x75\x74\x69\x6c\x69\x73\xe9\x65\x20\x61\x75\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Château d'Hyrule
        "\x43\x68\xe2\x74\x65\x61\x75\x20\x64\x27\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( endingBlowFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris le 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Coup deGrâce
        "\x43\x6f\x75\x70\x20\x64\x65\x0A\x47\x72\xe2\x63\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris la 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //ChargeBouclier
        "\x43\x68\x61\x72\x67\x65\x0A\x42\x6f\x75\x63\x6c\x69\x65\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris le 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Coup àRevers
        "\x43\x6f\x75\x70\x20\xe0\x0A\x52\x65\x76\x65\x72\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris le 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Brise-Casque
        "\x0A\x42\x72\x69\x73\x65\x2d\x43\x61\x73\x71\x75\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris le 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //CoupÉclair
        "\x43\x6f\x75\x70\x0A\xc9\x63\x6c\x61\x69\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris le 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20\x6c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //CoupPlongé
        "\x43\x6f\x75\x70\x0A\x50\x6c\x6f\x6e\x67\xe9"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez appris 
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x61\x70\x70\x72\x69\x73\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //l'AttaqueTourbillon
        "\x6c\x27\x41\x74\x74\x61\x71\x75\x65\x0A\x54\x6f\x75\x72\x62\x69\x6c\x6c\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Le 
        "\x4c\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //bâton Anima 
        "\x62\xe2\x74\x6f\x6e\x20\x41\x6e\x69\x6d\x61\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //a recouvré ses pouvoirs magiques! Vous pouvez désormais insuffler la vie aux statues dans le présent!
        "\x61\x20\x72\x65\x63\x6F\x75\x76\x72\xE9\x20\x73\x65\x73\x0A\x70\x6F\x75\x76\x6F\x69\x72\x73\x20\x6D\x61\x67\x69\x71\x75\x65\x73\x21\x20\x56\x6F\x75\x73\x20\x70\x6F\x75\x76\x65\x7A\x0A\x64\xE9\x73\x6F\x72\x6D\x61\x69\x73\x20\x69\x6E\x73\x75\x66\x66\x6C\x65\x72\x20\x6C\x61\x20\x76\x69\x65\x20\x61\x75\x78\x0A\x73\x74\x61\x74\x75\x65\x73\x20\x64\x61\x6E\x73\x20\x6C\x65\x20\x70\x72\xE9\x73\x65\x6E\x74\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez trouvé le premier
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x74\x72\x6f\x75\x76\xe9\x20\x6c\x65\x20\x70\x72\x65\x6d\x69\x65\x72\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //glyphe célestien
        "\x67\x6c\x79\x70\x68\x65\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Vous avezdéchiffré un des mots manquantsdes anciens écrits célestiens!
        "\x21\x20\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x0A\x64\xe9\x63\x68\x69\x66\x66\x72\xe9\x20\x75\x6e\x20\x64\x65\x73\x20\x6d\x6f\x74\x73\x20\x6d\x61\x6e\x71\x75\x61\x6e\x74\x73\x0A\x64\x65\x73\x20\x61\x6e\x63\x69\x65\x6e\x73\x20\xe9\x63\x72\x69\x74\x73\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e\x73\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez trouvé le second
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x74\x72\x6f\x75\x76\xe9\x20\x6c\x65\x20\x73\x65\x63\x6f\x6e\x64\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //glyphe célestien
        "\x67\x6c\x79\x70\x68\x65\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Vous avezdéchiffré un des mots manquantsdes anciens écrits célestiens!
        "\x21\x20\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x0A\x64\xe9\x63\x68\x69\x66\x66\x72\xe9\x20\x75\x6e\x20\x64\x65\x73\x20\x6d\x6f\x74\x73\x20\x6d\x61\x6e\x71\x75\x61\x6e\x74\x73\x0A\x64\x65\x73\x20\x61\x6e\x63\x69\x65\x6e\x73\x20\xe9\x63\x72\x69\x74\x73\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e\x73\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez trouvé le troisième
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x74\x72\x6f\x75\x76\xe9\x20\x6c\x65\x20\x74\x72\x6f\x69\x73\x69\xe8\x6d\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //glyphe célestien
        "\x67\x6c\x79\x70\x68\x65\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Vous avezdéchiffré un des mots manquantsdes anciens écrits célestiens!
        "\x21\x20\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x0A\x64\xe9\x63\x68\x69\x66\x66\x72\xe9\x20\x75\x6e\x20\x64\x65\x73\x20\x6d\x6f\x74\x73\x20\x6d\x61\x6e\x71\x75\x61\x6e\x74\x73\x0A\x64\x65\x73\x20\x61\x6e\x63\x69\x65\x6e\x73\x20\xe9\x63\x72\x69\x74\x73\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e\x73\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez trouvé le quatrième
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x74\x72\x6f\x75\x76\xe9\x20\x6c\x65\x20\x71\x75\x61\x74\x72\x69\xe8\x6d\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //glyphe célestien
        "\x67\x6c\x79\x70\x68\x65\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Vous avezdéchiffré un des mots manquantsdes anciens écrits célestiens!
        "\x21\x20\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x0A\x64\xe9\x63\x68\x69\x66\x66\x72\xe9\x20\x75\x6e\x20\x64\x65\x73\x20\x6d\x6f\x74\x73\x20\x6d\x61\x6e\x71\x75\x61\x6e\x74\x73\x0A\x64\x65\x73\x20\x61\x6e\x63\x69\x65\x6e\x73\x20\xe9\x63\x72\x69\x74\x73\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e\x73\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous avez trouvé le cinquième
        "\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x20\x74\x72\x6f\x75\x76\xe9\x20\x6c\x65\x20\x63\x69\x6e\x71\x75\x69\xe8\x6d\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //glyphe célestien
        "\x67\x6c\x79\x70\x68\x65\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Vous avezdéchiffré un des mots manquantsdes anciens écrits célestiens!
        "\x21\x20\x56\x6f\x75\x73\x20\x61\x76\x65\x7a\x0A\x64\xe9\x63\x68\x69\x66\x66\x72\xe9\x20\x75\x6e\x20\x64\x65\x73\x20\x6d\x6f\x74\x73\x20\x6d\x61\x6e\x71\x75\x61\x6e\x74\x73\x0A\x64\x65\x73\x20\x61\x6e\x63\x69\x65\x6e\x73\x20\xe9\x63\x72\x69\x74\x73\x20\x63\xe9\x6c\x65\x73\x74\x69\x65\x6e\x73\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez un 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristal d'Ombre
        "\x43\x72\x69\x73\x74\x61\x6c\x20\x64\x27\x4f\x6d\x62\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Sa surface semble êtrerecouverte par 
        "\x21\x0A\x53\x61\x20\x73\x75\x72\x66\x61\x63\x65\x20\x73\x65\x6d\x62\x6c\x65\x20\xea\x74\x72\x65\x0A\x72\x65\x63\x6f\x75\x76\x65\x72\x74\x65\x20\x70\x61\x72\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //de la mousse
        "\x64\x65\x20\x6c\x61\x20\x6d\x6f\x75\x73\x73\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //..
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( secondFusedShadowFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez un second
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x75\x6e\x20\x73\x65\x63\x6f\x6e\x64\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristal d'Ombre
        "\x43\x72\x69\x73\x74\x61\x6c\x20\x64\x27\x4f\x6d\x62\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Il émane 
        "\x21\x20\x49\x6c\x20\xe9\x6d\x61\x6e\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //unedouce chaleur 
        "\x75\x6e\x65\x0A\x64\x6f\x75\x63\x65\x20\x63\x68\x61\x6c\x65\x75\x72\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //sur vos mains..
        "\x73\x75\x72\x20\x76\x6f\x73\x20\x6d\x61\x69\x6e\x73\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdFusedShadowFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez le dernier
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x65\x20\x64\x65\x72\x6e\x69\x65\x72\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristal d'Ombre
        "\x43\x72\x69\x73\x74\x61\x6c\x20\x64\x27\x4f\x6d\x62\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Une forte
        "\x21\x20\x55\x6e\x65\x20\x66\x6f\x72\x74\x65\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //odeur de poisson 
        "\x6f\x64\x65\x75\x72\x20\x64\x65\x20\x70\x6f\x69\x73\x73\x6f\x6e\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //s'en dégage..
        "\x73\x27\x65\x6e\x20\x64\xe9\x67\x61\x67\x65\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( secondMirrorShardFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez le second fragmentdu 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x65\x20\x73\x65\x63\x6f\x6e\x64\x20\x66\x72\x61\x67\x6d\x65\x6e\x74\x0A\x64\x75\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Miroir des Ombres
        "\x4d\x69\x72\x6f\x69\x72\x20\x64\x65\x73\x20\x4f\x6d\x62\x72\x65\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Il est
        "\x21\x20\x49\x6c\x20\x65\x73\x74\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //un peu froid 
        "\x75\x6e\x20\x70\x65\x75\x20\x66\x72\x6f\x69\x64\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //et brille demille feux..
        "\x65\x74\x20\x62\x72\x69\x6c\x6c\x65\x20\x64\x65\x0A\x6d\x69\x6c\x6c\x65\x20\x66\x65\x75\x78\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdMirrorShardFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez le troisièmefragment du 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x65\x20\x74\x72\x6f\x69\x73\x69\xe8\x6d\x65\x0A\x66\x72\x61\x67\x6d\x65\x6e\x74\x20\x64\x75\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Miroir des Ombres
        "\x4d\x69\x72\x6f\x69\x72\x20\x64\x65\x73\x20\x4f\x6d\x62\x72\x65\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Il est très sale et 
        "\x21\x0A\x49\x6c\x20\x65\x73\x74\x20\x74\x72\xe8\x73\x20\x73\x61\x6c\x65\x20\x65\x74\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //recouvertde toiles
        "\x72\x65\x63\x6f\x75\x76\x65\x72\x74\x0A\x64\x65\x20\x74\x6f\x69\x6c\x65\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //..
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthMirrorShardFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez le dernierfragment du 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x65\x20\x64\x65\x72\x6e\x69\x65\x72\x0A\x66\x72\x61\x67\x6d\x65\x6e\x74\x20\x64\x75\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Miroir des Ombres
        "\x4d\x69\x72\x6f\x69\x72\x20\x64\x65\x73\x20\x4f\x6d\x62\x72\x65\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Il est encore plus
        "\x21\x0A\x49\x6c\x20\x65\x73\x74\x20\x65\x6e\x63\x6f\x72\x65\x20\x70\x6c\x75\x73\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //léger que l'air
        "\x6c\xe9\x67\x65\x72\x20\x71\x75\x65\x20\x6c\x27\x61\x69\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        //..
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( foolishItemFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Le 
        "\x4c\x65\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //blizzard 
        "\x62\x6c\x69\x7a\x7a\x61\x72\x64\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //souffle..
        "\x73\x6f\x75\x66\x66\x6c\x65\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaFr )
        //Qu'est-ce qu'il y a, 
        "\x51\x75\x27\x65\x73\x74\x2d\x63\x65\x20\x71\x75\x27\x69\x6c\x20\x79\x20\x61\x2c\x20"
        MSG_PLYR_NAME
        //?
        "\x3f"
        MSG_OPTION_LIST(MSG_OPTION_1)
        //Je veux me transformer
        "\x4a\x65\x20\x76\x65\x75\x78\x20\x6d\x65\x20\x74\x72\x61\x6e\x73\x66\x6f\x72\x6d\x65\x72\x0A"
        MSG_OPTION_LIST(MSG_OPTION_2)
        //Je veux me téléporter
        "\x4a\x65\x20\x76\x65\x75\x78\x20\x6d\x65\x20\x74\xe9\x6c\xe9\x70\x6f\x72\x74\x65\x72\x0A"
        MSG_OPTION_LIST(MSG_OPTION_3)
        //Changer l'heure de la journée
        "\x43\x68\x61\x6e\x67\x65\x72\x20\x6c\x27\x68\x65\x75\x72\x65\x20\x64\x65\x20\x6c\x61\x20\x6a\x6f\x75\x72\x6e\xe9\x65"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez la 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande Bourse
        "\x47\x72\x61\x6e\x64\x65\x20\x42\x6f\x75\x72\x73\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut contenir jusqu'à
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\x63\x6f\x6e\x74\x65\x6e\x69\x72\x20\x6a\x75\x73\x71\x75\x27\xe0\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //5,000 rubis
        "\x35\x2c\x30\x30\x30\x20\x72\x75\x62\x69\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletFr )
        MSG_SPEED(MSG_SPEED_FAST)
        //Vous obtenez la 
        "\x56\x6f\x75\x73\x20\x6f\x62\x74\x65\x6e\x65\x7a\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bourse Géante
        "\x42\x6f\x75\x72\x73\x65\x20\x47\xe9\x61\x6e\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Elle peut contenir jusqu'à
        "\x21\x0A\x45\x6c\x6c\x65\x20\x70\x65\x75\x74\x20\x63\x6f\x6e\x74\x65\x6e\x69\x72\x20\x6a\x75\x73\x71\x75\x27\xe0\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //9,999 rubis
        "\x39\x2c\x39\x39\x39\x20\x72\x75\x62\x69\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( smallWalletPauseFr )
        MSG_SPEED(MSG_SPEED_FAST)
        // Votre bourse préférée que vous avez depuis tout petit. Elle peut contenir 1000 rubis.
        "\x56\x6F\x74\x72\x65\x20\x62\x6F\x75\x72\x73\x65\x20\x70\x72\xE9\x66\xE9\x72\xE9\x65\x20\x71\x75\x65\x20\x76\x6F\x75\x73\x0A\x61\x76\x65\x7A\x20\x64\x65\x70\x75\x69\x73\x20\x74\x6F\x75\x74\x20\x70\x65\x74\x69\x74\x2E\x0A\x45\x6C\x6C\x65\x20\x70\x65\x75\x74\x20\x63\x6F\x6E\x74\x65\x6E\x69\x72\x20\x31\x30\x30\x30\x20\x72\x75\x62\x69\x73\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletPauseFr )
        MSG_SPEED(MSG_SPEED_FAST)
        // La bourse que vous avez reçue de Machaon, la princesse des insectes. Elle peut contenir 5000 rubis.
        "\x4C\x61\x20\x62\x6F\x75\x72\x73\x65\x20\x71\x75\x65\x20\x76\x6F\x75\x73\x20\x61\x76\x65\x7A\x20\x72\x65\xE7\x75\x65\x20\x64\x65\x0A\x4D\x61\x63\x68\x61\x6F\x6E\x2C\x20\x6C\x61\x20\x70\x72\x69\x6E\x63\x65\x73\x73\x65\x20\x64\x65\x73\x20\x69\x6E\x73\x65\x63\x74\x65\x73\x2E\x0A\x45\x6C\x6C\x65\x20\x70\x65\x75\x74\x20\x63\x6F\x6E\x74\x65\x6E\x69\x72\x20\x35\x30\x30\x30\x20\x72\x75\x62\x69\x73\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletPauseFr )
        MSG_SPEED(MSG_SPEED_FAST)
        // La bourse que Machaon vous a donnée en récompense. Elle peut contenir 9999 rubis.
        "\x4C\x61\x20\x62\x6F\x75\x72\x73\x65\x20\x71\x75\x65\x20\x4D\x61\x63\x68\x61\x6F\x6E\x20\x76\x6F\x75\x73\x20\x61\x20\x64\x6F\x6E\x6E\xE9\x65\x0A\x65\x6E\x20\x72\xE9\x63\x6F\x6D\x70\x65\x6E\x73\x65\x2E\x20\x45\x6C\x6C\x65\x20\x70\x65\x75\x74\x20\x63\x6F\x6E\x74\x65\x6E\x69\x72\x0A\x39\x39\x39\x39\x20\x72\x75\x62\x69\x73\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( charloDonationFr )
        // Pour que la paix règne en Hyrule... puis-je vous demander l'aumône...?
        "\x50\x6F\x75\x72\x20\x71\x75\x65\x20\x6C\x61\x20\x70\x61\x69\x78\x20\x72\xE8\x67\x6E\x65\x20\x65\x6E\x20\x48\x79\x72\x75\x6C\x65\x2E\x2E\x2E\x0A\x70\x75\x69\x73\x2D\x6A\x65\x20\x76\x6F\x75\x73\x20\x64\x65\x6D\x61\x6E\x64\x65\x72\x20\x6C\x27\x61\x75\x6D\xF4\x6E\x65\x2E\x2E\x2E\x3F" 
        MSG_OPTION_LIST( MSG_OPTION_1 ) 
        // Voici 100 rubis.
        "\x56\x6F\x69\x63\x69\x20\x31\x30\x30\x20\x72\x75\x62\x69\x73\x2E\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_2 ) 
        // Voici 50 rubis
        "\x56\x6F\x69\x63\x69\x20\x35\x30\x20\x72\x75\x62\x69\x73\x2E\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_3 ) 
        // Je refuse.
        "\x4A\x65\x20\x72\x65\x66\x75\x73\x65\x2E";
    MSG_END()

    MSG_BEGIN_ARRAY( recognitionFr )
        MSG_SPEED(MSG_SPEED_FAST)
        // L'équipe du Randomizer souhaiterait remercier nos incroyables testeurs. Ce projet ne serait pas ce qu'il est aujourd'hui sans vous
        "\x4C\x27\xE9\x71\x75\x69\x70\x65\x20\x64\x75\x20\x52\x61\x6E\x64\x6F\x6D\x69\x7A\x65\x72\n\x73\x6F\x75\x68\x61\x69\x74\x65\x72\x61\x69\x74\x20\x72\x65\x6D\x65\x72\x63\x69\x65\x72\x20\x6E\x6F\x73\n\x69\x6E\x63\x72\x6F\x79\x61\x62\x6C\x65\x73\x20\x74\x65\x73\x74\x65\x75\x72\x73\x2E\x20\x43\x65\n\x70\x72\x6F\x6A\x65\x74\x20\x6E\x65\x20\x73\x65\x72\x61\x69\x74\x20\x70\x61\x73\x20\x63\x65\x20\x71\x75\x27\x69\x6C\n\x65\x73\x74\x20\x61\x75\x6A\x6F\x75\x72\x64\x27\x68\x75\x69\x20\x73\x61\x6E\x73\x20\x76\x6F\x75\x73: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END()
        // clang-format on

        MsgEntry entriesFr[TOTAL_CUSTOM_MESSAGES] = {
            // Forest Temple small key
            forestSmallKeyFr,
            sizeof( forestSmallKeyFr ),
            0x00E9,

            // Goron Mines small key
            minesSmallKeyFr,
            sizeof( minesSmallKeyFr ),
            0x00EA,

            // Lakebed Temple small key
            lakebedSmallKeyFr,
            sizeof( lakebedSmallKeyFr ),
            0x00EB,

            // Arbiter's Grounds small key
            arbitersSmallKeyFr,
            sizeof( arbitersSmallKeyFr ),
            0x00EC,

            // Snowpeak Ruins small key
            snowpeakSmallKeyFr,
            sizeof( snowpeakSmallKeyFr ),
            0x00ED,

            // Temple of Time small key
            timeSmallKeyFr,
            sizeof( timeSmallKeyFr ),
            0x00EE,

            // City in the Sky small key
            citySmallKeyFr,
            sizeof( citySmallKeyFr ),
            0x00EF,

            // Palace of Twilight small key
            palaceSmallKeyFr,
            sizeof( palaceSmallKeyFr ),
            0x00F0,

            // Hyrule Castle small key
            hyruleSmallKeyFr,
            sizeof( hyruleSmallKeyFr ),
            0x00F1,

            // Bulblin Camp small key
            campSmallKeyFr,
            sizeof( campSmallKeyFr ),
            0x00F2,

            // Shadow Crystal
            shadowCrystalFr,
            sizeof( shadowCrystalFr ),
            0x0096,

            // Forest Temple dungeon map
            forestDungeonMapFr,
            sizeof( forestDungeonMapFr ),
            0x011A,

            // Goron Mines dungeon map
            minesDungeonMapFr,
            sizeof( minesDungeonMapFr ),
            0x011B,

            // Lakebed Temple dungeon map
            lakebedDungeonMapFr,
            sizeof( lakebedDungeonMapFr ),
            0x011C,

            // Arbiter's Grounds dungeon map
            arbitersDungeonMapFr,
            sizeof( arbitersDungeonMapFr ),
            0x011D,

            // Snowpeak Ruins dungeon map
            snowpeakDungeonMapFr,
            sizeof( snowpeakDungeonMapFr ),
            0x011E,

            // Temple of Time dungeon map
            timeDungeonMapFr,
            sizeof( timeDungeonMapFr ),
            0x011F,

            // City in the Sky dungeon map
            cityDungeonMapFr,
            sizeof( cityDungeonMapFr ),
            0x0120,

            // Palace of Twilight dungeon map
            palaceDungeonMapFr,
            sizeof( palaceDungeonMapFr ),
            0x0121,

            // Hyrule Castle dungeon map
            hyruleDungeonMapFr,
            sizeof( hyruleDungeonMapFr ),
            0x0122,

            // Forest Temple compass
            forestCompassFr,
            sizeof( forestCompassFr ),
            0x00FD,

            // Goron Mines compass
            minesCompassFr,
            sizeof( minesCompassFr ),
            0x00FE,

            // Lakebed Temple compass
            lakebedCompassFr,
            sizeof( lakebedCompassFr ),
            0x00FF,

            // Arbiter's Grounds compass
            arbitersCompassFr,
            sizeof( arbitersCompassFr ),
            0x010C,

            // Snowpeak Ruins compass
            snowpeakCompassFr,
            sizeof( snowpeakCompassFr ),
            0x010D,

            // Temple of Time compass
            timeCompassFr,
            sizeof( timeCompassFr ),
            0x010E,

            // City in the Sky compass
            cityCompassFr,
            sizeof( cityCompassFr ),
            0x010F,

            // Palace of Twilight compass
            palaceCompassFr,
            sizeof( palaceCompassFr ),
            0x0110,

            // Hyrule Castle compass
            hyruleCompassFr,
            sizeof( hyruleCompassFr ),
            0x0111,

            // Forest Temple big key
            forestBigKeyFr,
            sizeof( forestBigKeyFr ),
            0x00F6,

            // Lakebed Temple big key
            lakebedBigKeyFr,
            sizeof( lakebedBigKeyFr ),
            0x00F7,

            // Arbiter's Grounds big key
            arbitersBigKeyFr,
            sizeof( arbitersBigKeyFr ),
            0x00F8,

            // Temple of Time big key
            timeBigKeyFr,
            sizeof( timeBigKeyFr ),
            0x00F9,

            // City in the Sky big key
            cityBigKeyFr,
            sizeof( cityBigKeyFr ),
            0x00FA,

            // Palace of Twilight big key
            palaceBigKeyFr,
            sizeof( palaceBigKeyFr ),
            0x00FB,

            // Hyrule Castle big key
            hyruleBigKeyFr,
            sizeof( hyruleBigKeyFr ),
            0x00FC,

            // Ending Blow hidden skill
            endingBlowFr,
            sizeof( endingBlowFr ),
            0x0145,

            // Shield Attack hidden skill
            shieldAttackFr,
            sizeof( shieldAttackFr ),
            0x0146,

            // Back Slice hidden skill
            backSliceFr,
            sizeof( backSliceFr ),
            0x0147,

            // Helm Splitter hidden skill
            helmSplitterFr,
            sizeof( helmSplitterFr ),
            0x0148,

            // Mortal Draw hidden skill
            mortalDrawFr,
            sizeof( mortalDrawFr ),
            0x0149,

            // Jump Strike hidden skill
            jumpStrikeFr,
            sizeof( jumpStrikeFr ),
            0x014A,

            // Great Spin hidden skill
            greatSpinFr,
            sizeof( greatSpinFr ),
            0x014B,

            // Powered up Dominion Rod
            poweredRodFr,
            sizeof( poweredRodFr ),
            0x00B0,

            // First Ancient Sky Book character
            firstCharacterFr,
            sizeof( firstCharacterFr ),
            0x013F,

            // Second Ancient Sky Book character
            secondCharacterFr,
            sizeof( secondCharacterFr ),
            0x0140,

            // Third Ancient Sky Book character
            thirdCharacterFr,
            sizeof( thirdCharacterFr ),
            0x0141,

            // Fourth Ancient Sky Book character
            fourthCharacterFr,
            sizeof( fourthCharacterFr ),
            0x0142,

            // Fifth Ancient Sky Book character
            fifthCharacterFr,
            sizeof( fifthCharacterFr ),
            0x0143,

            // Sixth Ancient Sky Book character
            firstFusedShadowFr,
            sizeof( firstFusedShadowFr ),
            0x013C,

            // Second Fused Shadow
            secondFusedShadowFr,
            sizeof( secondFusedShadowFr ),
            0x013D,

            // Third Fused Shadow
            thirdFusedShadowFr,
            sizeof( thirdFusedShadowFr ),
            0x013E,

            // Second Mirror Shard
            secondMirrorShardFr,
            sizeof( secondMirrorShardFr ),
            0x0109,

            // Third Mirror Shard
            thirdMirrorShardFr,
            sizeof( thirdMirrorShardFr ),
            0x010A,

            // Fourth Mirror Shard
            fourthMirrorShardFr,
            sizeof( fourthMirrorShardFr ),
            0x010B,

            // Foolish Item
            foolishItemFr,
            sizeof( foolishItemFr ),
            0x0077,

            // Talking to Midna
            talkToMidnaFr,
            sizeof( talkToMidnaFr ),
            0x0BBB,

            // Big Wallet
            bigWalletFr,
            sizeof( bigWalletFr ),
            0x0099,

            // Giant Wallet
            giantWalletFr,
            sizeof( giantWalletFr ),
            0x009A,

            // Small Wallet Menu Text
            smallWalletPauseFr,
            sizeof( smallWalletPauseFr ),
            0x0298,

            // Big Wallet Menu Text
            bigWalletPauseFr,
            sizeof( bigWalletPauseFr ),
            0x0299,

            // Giant Wallet Menu Text
            giantWalletPauseFr,
            sizeof( giantWalletPauseFr ),
            0x029a,

            // Recognition text
            recognitionFr,
            sizeof( recognitionFr ),
            0x0b44,
    };

    const MsgEntry charloDonationEntryFr = { charloDonationFr, sizeof( charloDonationFr ), 0x0355 };

    const ItemWheelMenuStrings itemWheelMenuStringsFr = {
        // areasBeingTracked
        {
            // Forest Temple
            // Temple Sylvestre
            "\x54\x65\x6d\x70\x6c\x65\x20\x53\x79\x6c\x76\x65\x73\x74\x72\x65",

            // Goron Mines
            // Mine Goron
            "\x4d\x69\x6e\x65\x20\x47\x6f\x72\x6f\x6e",

            // Lakebed Temple
            // Temple Abyssal
            "\x54\x65\x6d\x70\x6c\x65\x20\x41\x62\x79\x73\x73\x61\x6c",

            // Arbiter's Grounds
            // Tour du Jugement
            "\x54\x6f\x75\x72\x20\x64\x75\x20\x4a\x75\x67\x65\x6d\x65\x6e\x74",

            // Snowpeak Ruins
            // Ruines des Pics Blancs
            "\x52\x75\x69\x6e\x65\x73\x20\x64\x65\x73\x20\x50\x69\x63\x73\x20\x42\x6c\x61\x6e\x63\x73",

            // Temple of Time
            // Temple du Temps
            "\x54\x65\x6d\x70\x6c\x65\x20\x64\x75\x20\x54\x65\x6d\x70\x73",

            // City in the Sky
            // Célestia
            "\x43\xe9\x6c\x65\x73\x74\x69\x61",

            // Palace of Twilight
            // Palais du Crépuscule
            "\x50\x61\x6c\x61\x69\x73\x20\x64\x75\x20\x43\x72\xe9\x70\x75\x73\x63\x75\x6c\x65",

            // Hyrule Castle
            // Château d'Hyrule
            "\x43\x68\xe2\x74\x65\x61\x75\x20\x64\x27\x48\x79\x72\x75\x6c\x65",

            // Faron Woods
            // Forêt de Firone
            "\x46\x6F\x72\xEA\x74\x20\x64\x65\x20\x46\x69\x72\x6F\x6E\x65",

            // Bulblin Camp
            // Camp Bulblin
            "\x43\x61\x6d\x70\x20\x42\x75\x6c\x62\x6c\x69\x6e",
        },

        // seedIsLoaded
        // Seed
        "\x53\x65\x65\x64",

        // seedIsNotLoaded
        // Aucune seed n'est chargée
        "\x41\x75\x63\x75\x6E\x65\x20\x73\x65\x65\x64\x20\x6E\x27\x65\x73\x74\x20\x63\x68\x61\x72\x67\xE9\x65",

        // yes/no
        // Oui
        "\x4F\x75\x69",

        // Non
        "\x4E\x6F\x6E",

        // shadowsShards
        // Cristaux d'Ombre\nFragments de Miroir
        "\x43\x72\x69\x73\x74\x61\x75\x78\x20\x64\x27\x4F\x6D\x62\x72\x65\x0A\x46\x72\x61\x67\x6D\x65\x6E\x74\x73\x20\x64\x65"
        "\x20\x4D\x69\x72\x6F\x69\x72",

        // Pumpkin
        // Citrouille
        "\x43\x69\x74\x72\x6F\x75\x69\x6C\x6C\x65",

        // Cheese
        // Fromage
        "\x46\x72\x6F\x6D\x61\x67\x65",

        // Gate Keys
        // Clés des portails
        "\x43\x6C\xE9\x73\x20\x64\x65\x73\x20\x70\x6F\x72\x74\x61\x69\x6C\x73",

        // Areas
        // Zones
        "\x5A\x6F\x6E\x65\x73",

        // Small Keys
        // Petites\nclés
        "\x50\x65\x74\x69\x74\x65\x73\x0A\x63\x6C\xE9\x73",

        // Big Keys
        // Grandes\nclés
        "\x47\x72\x61\x6E\x64\x65\x73\x0A\x63\x6C\xE9\x73",

        // Maps
        // Cartes
        "\x43\x61\x72\x74\x65\x73",

        // Compasses
        // Boussoles
        "\x42\x6F\x75\x73\x73\x6F\x6C\x65\x73",

        // helpText
        // Appuyez sur\npause ou Z\npour activer\nles données\nadditionnelles
        "\x41\x70\x70\x75\x79\x65\x7A\x20\x73\x75\x72\x0A\x70\x61\x75\x73\x65\x20\x6F\x75\x20\x5A\x0A\x70\x6F\x75\x72\x20\x61"
        "\x63\x74\x69\x76\x65\x72\x0A\x6C\x65\x73\x20\x64\x6F\x6E\x6E\xE9\x65\x73\x0A\x61\x64\x64\x69\x74\x69\x6F\x6E\x6E\x65"
        "\x6C\x6C\x65\x73",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsFr {
        // Fused Shadows/Mirror Shards
        170,

        // Pumpkin
        42,

        // Yes/No
        22,
        20,

        // Cheese
        87,

        // Yes/No
        20,
        17,

        // Gate Keys
        82,

        // Yes/No
        52,
        49,

        // Headers
        // Small Keys
        180,

        // Big Keys
        74,

        // Maps
        82,

        // Compasses
        69,

        // Header values
        // Small Keys values
        22,

        // Big keys values
        // Yes/No
        18,
        16,

        // Goron Mines
        27,

        // Maps values
        // Yes/No
        11,
        9,

        // Compasses values
        // Yes/No
        27,
        24,
    };
}     // namespace mod::customMessages
#endif