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
    MSG_BEGIN_ARRAY( forestSmallKeySp )
        MSG_SPEED( MSG_SPEED_FAST )
        // ¡Has obtenido una
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20"
        MSG_COLOR(MSG_COLOR_RED)
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        " %s %s\n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( shadowCrystalSp )
        MSG_SPEED(MSG_SPEED_SLOW)
        // ¡Has obtenido el 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x65\x6C\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Cristal Oscuro
        "\x43\x72\x69\x73\x74\x61\x6C\x20\x4F\x73\x63\x75\x72\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\nEsa manifestación maléfica del\npoder de 
        "\x21\x0A\x45\x73\x61\x20\x6D\x61\x6E\x69\x66\x65\x73\x74\x61\x63\x69\xF3\x6E\x20\x6D\x61\x6C\xE9\x66\x69\x63\x61\x20\x64\x65\x6C\x0A\x70\x6F\x64\x65\x72\x20\x64\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Zant 
        "\x5A\x61\x6E\x74\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        // te permite\ntransformarte cuando quieras!
        "\x74\x65\x20\x70\x65\x72\x6D\x69\x74\x65\x0A\x74\x72\x61\x6E\x73\x66\x6F\x72\x6D\x61\x72\x74\x65\x20\x63\x75\x61\x6E\x64\x6F\x20\x71\x75\x69\x65\x72\x61\x73\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( endingBlowSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // golpe de gracia
        "\x67\x6F\x6C\x70\x65\x20\x64\x65\x20\x67\x72\x61\x63\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( shieldAttackSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // ataque de escudo
        "\x61\x74\x61\x71\x75\x65\x20\x64\x65\x20\x65\x73\x63\x75\x64\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( backSliceSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // tajo trastero
        "\x74\x61\x6A\x6F\x20\x74\x72\x61\x73\x74\x65\x72\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( helmSplitterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // rompeyelmos
        "\x72\x6F\x6D\x70\x65\x79\x65\x6C\x6D\x6F\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( mortalDrawSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // tajo relámpago
        "\x74\x61\x6A\x6F\x20\x72\x65\x6C\xE1\x6D\x70\x61\x67\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( jumpStrikeSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // mandoble volador
        "\x6D\x61\x6E\x64\x6F\x62\x6C\x65\x20\x76\x6F\x6C\x61\x64\x6F\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( greatSpinSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Técnica aprendida :\n
        "\xA1\x54\xE9\x63\x6E\x69\x63\x61\x20\x61\x70\x72\x65\x6E\x64\x69\x64\x61\x20\x3A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // gran ataque circular
        "\x67\x72\x61\x6E\x20\x61\x74\x61\x71\x75\x65\x20\x63\x69\x72\x63\x75\x6C\x61\x72"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( poweredRodSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // El 
        "\x45\x6C\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // cetro de dominio 
        "\x63\x65\x74\x72\x6F\x20\x64\x65\x20\x64\x6F\x6D\x69\x6E\x69\x6F\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ha\nrecuperado su magia! Ahora\npuede ser utilizado para dar\nvida a estatuas en el presente."
        "\x68\x61\x0A\x72\x65\x63\x75\x70\x65\x72\x61\x64\x6F\x20\x73\x75\x20\x6D\x61\x67\x69\x61\x21\x20\x41\x68\x6F\x72\x61\x0A\x70\x75\x65\x64\x65\x20\x73\x65\x72\x20\x75\x74\x69\x6C\x69\x7A\x61\x64\x6F\x20\x70\x61\x72\x61\x20\x64\x61\x72\x0A\x76\x69\x64\x61\x20\x61\x20\x65\x73\x74\x61\x74\x75\x61\x73\x20\x65\x6E\x20\x65\x6C\x20\x70\x72\x65\x73\x65\x6E\x74\x65\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( skyBookCharacterSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has encontrado una 
        "\xA1\x48\x61\x73\x20\x65\x6E\x63\x6F\x6E\x74\x72\x61\x64\x6F\x20\x75\x6E\x61\x20" 
        MSG_COLOR(MSG_COLOR_RED)
        // letra\n
        "\x6C\x65\x74\x72\x61\x0A"
        MSG_COLOR(MSG_COLOR_WHITE)
        // del 
        "\x64\x65\x6C\x20"
         MSG_COLOR(MSG_COLOR_RED)
        // Libro de los Cielos
        "\x4C\x69\x62\x72\x6F\x20\x64\x65\x20\x6C\x6F\x73\x20\x43\x69\x65\x6C\x6F\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\n Has conseguido
        "\x21\x0A\x48\x61\x73\x20\x63\x6f\x6e\x73\x65\x67\x75\x69\x64\x6f\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // hasta ahora.
        "\x20\x68\x61\x73\x74\x61\x20\x61\x68\x6f\x72\x61\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY( firstFusedShadowSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido un fragmento de\n
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x75\x6E\x20\x66\x72\x61\x67\x6D\x65\x6E\x74\x6F\x20\x64\x65\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // Sombra Fundida
        "\x53\x6F\x6D\x62\x72\x61\x20\x46\x75\x6E\x64\x69\x64\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ! Parece que\nalgo de 
        "\x21\x20\x50\x61\x72\x65\x63\x65\x20\x71\x75\x65\x0A\x61\x6C\x67\x6F\x20\x64\x65\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        // musgo 
        "\x6D\x75\x73\x67\x6F\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ha crecido\nsobre él..
        "\x68\x61\x20\x63\x72\x65\x63\x69\x64\x6F\x0A\x73\x6F\x62\x72\x65\x20\xE9\x6C\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( secondFusedShadowSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido el segundo\nfragmento de 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x65\x6C\x20\x73\x65\x67\x75\x6E\x64\x6F\x0A\x66\x72\x61\x67\x6D\x65\x6E\x74\x6F\x20\x64\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Sombra Fundida
        "\x53\x6F\x6D\x62\x72\x61\x20\x46\x75\x6E\x64\x69\x64\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\nEstá 
        "\x21\x0A\x45\x73\x74\xE1\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // caliente 
        "\x63\x61\x6C\x69\x65\x6E\x74\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        // al tocar..
        "\x61\x6C\x20\x74\x6F\x63\x61\x72\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( thirdFusedShadowSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido el último\nfragmento de 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x65\x6C\x20\xFA\x6C\x74\x69\x6D\x6F\x0A\x66\x72\x61\x67\x6D\x65\x6E\x74\x6F\x20\x64\x65\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Sombra Fundida
        "\x53\x6F\x6D\x62\x72\x61\x20\x46\x75\x6E\x64\x69\x64\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\nParece 
        "\x21\x0A\x50\x61\x72\x65\x63\x65\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        // mojado 
        "\x6D\x6F\x6A\x61\x64\x6F\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        // y huele\na pescado..
        "\x79\x20\x68\x75\x65\x6C\x65\x0A\x61\x20\x70\x65\x73\x63\x61\x64\x6F\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( secondMirrorShardSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido el segundo\nfragmento del 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x65\x6C\x20\x73\x65\x67\x75\x6E\x64\x6F\x0A\x66\x72\x61\x67\x6D\x65\x6E\x74\x6F\x20\x64\x65\x6C\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Espejo del\nCrepúsculo
        "\x45\x73\x70\x65\x6A\x6F\x20\x64\x65\x6C\x0A\x43\x72\x65\x70\xFA\x73\x63\x75\x6C\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ! Es reluciente y\n
        "\x21\x20\x45\x73\x20\x72\x65\x6C\x75\x63\x69\x65\x6E\x74\x65\x20\x79\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        // frio 
        "\x66\x72\x69\x6F\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        // al tocar..
        "\x61\x6C\x20\x74\x6F\x63\x61\x72\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( thirdMirrorShardSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido el tercer\nfragmento del
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x65\x6C\x20\x74\x65\x72\x63\x65\x72\x0A\x66\x72\x61\x67\x6D\x65\x6E\x74\x6F\x20\x64\x65\x6C\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Espejo del\nCrepúsculo
        "\x45\x73\x70\x65\x6A\x6F\x20\x64\x65\x6C\x0A\x43\x72\x65\x70\xFA\x73\x63\x75\x6C\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ! Está cubierto de\ntierra y 
        "\x21\x20\x45\x73\x74\xE1\x20\x63\x75\x62\x69\x65\x72\x74\x6F\x20\x64\x65\x0A\x74\x69\x65\x72\x72\x61\x20\x79\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        // telarañas
        "\x74\x65\x6C\x61\x72\x61\xF1\x61\x73"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ..
        "\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( fourthMirrorShardSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido el último\nfragmento del 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x65\x6C\x20\xFA\x6C\x74\x69\x6D\x6F\x0A\x66\x72\x61\x67\x6D\x65\x6E\x74\x6F\x20\x64\x65\x6C\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Espejo del\nCrepúsculo
        "\x45\x73\x70\x65\x6A\x6F\x20\x64\x65\x6C\x0A\x43\x72\x65\x70\xFA\x73\x63\x75\x6C\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ! Parece aún más\nligero que el 
        "\x21\x20\x50\x61\x72\x65\x63\x65\x20\x61\xFA\x6E\x20\x6D\xE1\x73\x0A\x6C\x69\x67\x65\x72\x6F\x20\x71\x75\x65\x20\x65\x6C\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        // aire
        "\x61\x69\x72\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ..
        "\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( foolishItemSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // Sopla un viento 
        "\x53\x6F\x70\x6C\x61\x20\x75\x6E\x20\x76\x69\x65\x6E\x74\x6F\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        // frio
        "\x66\x72\xED\x6F"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ..
        "\x2E\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( talkToMidnaSp )
        // ¿Qué quieres, 
        "\xBF\x51\x75\xE9\x20\x71\x75\x69\x65\x72\x65\x73\x2C\x20"
        MSG_PLYR_NAME
        // ?
        "\x3F"
        MSG_OPTION_LIST(MSG_OPTION_1)
        // Transformarse
        "\x54\x72\x61\x6E\x73\x66\x6F\x72\x6D\x61\x72\x73\x65\x0A"
        MSG_OPTION_LIST(MSG_OPTION_2)
        // Teletransportar
        "\x54\x65\x6C\x65\x74\x72\x61\x6E\x73\x70\x6F\x72\x74\x61\x72\x0A"
        MSG_OPTION_LIST(MSG_OPTION_3)
        // Cambiar la hora del día 
        "\x43\x61\x6D\x62\x69\x61\x72\x20\x6C\x61\x20\x68\x6F\x72\x61\x20\x64\x65\x6C\x20\x64\xED\x61\x20"
    MSG_END();
    MSG_BEGIN_ARRAY( bigWalletSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido la 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x6C\x61\x20" 
        MSG_COLOR(MSG_COLOR_RED)
        // bolsa grande
        "\x62\x6F\x6C\x73\x61\x20\x67\x72\x61\x6E\x64\x65" 
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\n¡Caben 
        "\x21\x0A\xA1\x43\x61\x62\x65\x6E\x20" 
        MSG_COLOR(MSG_COLOR_RED)
        // 5000 rupias
        "\x35\x30\x30\x30\x20\x72\x75\x70\x69\x61\x73" 
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( giantWalletSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // ¡Has obtenido la 
        "\xA1\x48\x61\x73\x20\x6F\x62\x74\x65\x6E\x69\x64\x6F\x20\x6C\x61\x20" 
        MSG_COLOR(MSG_COLOR_RED)
        // bolsa\ngigantesca
        "\x62\x6F\x6C\x73\x61\x0A\x67\x69\x67\x61\x6E\x74\x65\x73\x63\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ! ¡Caben 
        "\x21\x20\xA1\x43\x61\x62\x65\x6E\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        // 9999 rupias
        "\x39\x39\x39\x39\x20\x72\x75\x70\x69\x61\x73" 
        MSG_COLOR(MSG_COLOR_WHITE)
        // !
        "\x21"
    MSG_END();
    MSG_BEGIN_ARRAY( smallWalletPauseSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // Objeto que te acompaña desde tu más tierna infancia. Caben hasta 1000 rupias.
        "\x4F\x62\x6A\x65\x74\x6F\x20\x71\x75\x65\x20\x74\x65\x20\x61\x63\x6F\x6D\x70\x61\xF1\x61\x0A\x64\x65\x73\x64\x65\x20\x74\x75\x20\x6D\xE1\x73\x20\x74\x69\x65\x72\x6E\x61\x20\x69\x6E\x66\x61\x6E\x63\x69\x61\x2E\x0A\x43\x61\x62\x65\x6E\x20\x68\x61\x73\x74\x61\x20\x31\x30\x30\x30\x20\x72\x75\x70\x69\x61\x73\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( bigWalletPauseSp )
        MSG_SPEED(MSG_SPEED_FAST)
        //Bolsa que te dio Maripola, reina de los insectos. Caben hasta 5000 rupias.
        "\x42\x6F\x6C\x73\x61\x20\x71\x75\x65\x20\x74\x65\x20\x64\x69\x6F\x20\x4D\x61\x72\x69\x70\x6F\x6C\x61\x2C\x0A\x72\x65\x69\x6E\x61\x20\x64\x65\x20\x6C\x6F\x73\x20\x69\x6E\x73\x65\x63\x74\x6F\x73\x2E\x0A\x43\x61\x62\x65\x6E\x20\x68\x61\x73\x74\x61\x20\x35\x30\x30\x30\x20\x72\x75\x70\x69\x61\x73\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( giantWalletPauseSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // Bolsa que te dio Maripola, reina de los insectos. Solo la reciben sus fieles servidores. Caben hasta 9999 rupias.
        "\x42\x6F\x6C\x73\x61\x20\x71\x75\x65\x20\x74\x65\x20\x64\x69\x6F\x20\x4D\x61\x72\x69\x70\x6F\x6C\x61\x2C\x20\x72\x65\x69\x6E\x61\x20\x64\x65\x20\x6C\x6F\x73\x0A\x69\x6E\x73\x65\x63\x74\x6F\x73\x2E\x20\x53\x6F\x6C\x6F\x20\x6C\x61\x20\x72\x65\x63\x69\x62\x65\x6E\x20\x73\x75\x73\x20\x66\x69\x65\x6C\x65\x73\x0A\x73\x65\x72\x76\x69\x64\x6F\x72\x65\x73\x2E\x20\x43\x61\x62\x65\x6E\x20\x68\x61\x73\x74\x61\x20\x39\x39\x39\x39\x20\x72\x75\x70\x69\x61\x73\x2E"
    MSG_END();
    MSG_BEGIN_ARRAY( poeSoulSp )
        MSG_SPEED( MSG_SPEED_FAST )
        // Es un
        "\x45\x73\x20\x75\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // Alma de Espectro
        "\x41\x6c\x6d\x61\x20\x64\x65\x20\x45\x73\x70\x65\x63\x74\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        // !\nHas conseguido
        "\x21\x20\x0a\x48\x61\x73\x20\x63\x6f\x6e\x73\x65\x67\x75\x69\x64\x6f\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // hasta ahora.
        "\x20\x68\x61\x73\x74\x61\x20\x61\x68\x6f\x72\x61\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY( skyBookDescriptionSp )
        MSG_SPEED(MSG_SPEED_FAST)
        // Libro escrito en la antigua lengua Uca.\nParecen faltarle letras.\n\n
        "\x4C\x69\x62\x72\x6F\x20\x65\x73\x63\x72\x69\x74\x6F\x20\x65\x6E\x20\x6C\x61\x20\x61\x6E\x74\x69\x67\x75\x61\x20\x6C\x65\x6E\x67\x75\x61\x20\x55\x63\x61\x2E\x0A\x50\x61\x72\x65\x63\x65\x6E\x20\x66\x61\x6C\x74\x61\x72\x6C\x65\x20\x6C\x65\x74\x72\x61\x73\x2E\x0A\x0A\x48\x61\x73\x20\x63\x6f\x6e\x73\x65\x67\x75\x69\x64\x6f\x20"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // hasta ahora.
        "\x20\x68\x61\x73\x74\x61\x20\x61\x68\x6f\x72\x61\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY( charloDonationSp )
        // ¿Darme una limosna por la paz de Hyrule?
        "\xBF\x44\x61\x72\x6D\x65\x20\x75\x6E\x61\x20\x6C\x69\x6D\x6F\x73\x6E\x61\x20\x70\x6F\x72\x20\x6C\x61\x20\x70\x61\x7A\x0A\x64\x65\x20\x48\x79\x72\x75\x6C\x65\x3F" 
        MSG_OPTION_LIST( MSG_OPTION_1 ) 
        // 100 rupias
        "\x31\x30\x30\x20\x72\x75\x70\x69\x61\x73\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_2 ) 
        // 50 rupias
        "\x35\x30\x20\x72\x75\x70\x69\x61\x73\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_3 ) 
        // No
        "\x4E\x6F";
    MSG_END();
    MSG_BEGIN_ARRAY( recognitionSp )
        MSG_SPEED(MSG_SPEED_FAST)
        //Queremos agradecer a nuestros increíbles Testers de parte del Equipo Randomizer. Sin ustedes, éste proyecto no sería lo que es el día de hoy
        "\x51\x75\x65\x72\x65\x6D\x6F\x73\x20\x61\x67\x72\x61\x64\x65\x63\x65\x72\x20\x61\x20\x6E\x75\x65\x73\x74\x72\x6F\x73\n\x69\x6E\x63\x72\x65\xED\x62\x6C\x65\x73\x20\x54\x65\x73\x74\x65\x72\x73\x20\x64\x65\x20\x70\x61\x72\x74\x65\n\x64\x65\x6C\x20\x45\x71\x75\x69\x70\x6F\x20\x52\x61\x6E\x64\x6F\x6D\x69\x7A\x65\x72\x2E\x20\x53\x69\x6E\n\x75\x73\x74\x65\x64\x65\x73\x2C\x20\xE9\x73\x74\x65\x20\x70\x72\x6F\x79\x65\x63\x74\x6F\x20\x6E\x6F\x20\x73\x65\x72\xED\x61\n\x6C\x6F\x20\x71\x75\x65\x20\x65\x73\x20\x65\x6C\x20\x64\xED\x61\x20\x64\x65\x20\x68\x6F\x79: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END();

    char smallKeyTextSp[] = "\x75\x6E\x61\x20\x6C\x6C\x61\x76\x65\x20\x70\x65\x71\x75\x65\xF1\x61"; // una llave pequeña
    char dungeonMapTextSp[] = "\x65\x6C\x20\x6D\x61\x70\x61"; // el mapa
    char compassTextSp[] = "\x6C\x61\x20\x62\x72\xFA\x6A\x75\x6C\x61"; // la brújula
    char bigKeyTextSp[] = "\x6C\x61\x20\x67\x72\x61\x6E\x20\x6C\x6C\x61\x76\x65"; // la gran llave
    char forestTempleTextSp[] = "\x64\x65\x6C\x20\x54\x65\x6D\x70\x6C\x6F\x20\x64\x65\x6C\x20\x42\x6F\x73\x71\x75\x65"; //del Templo del Bosque
    char goronMinesTextSp[] = "\x64\x65\x20\x6C\x61\x20\x4D\x69\x6E\x61\x73\x20\x64\x65\x20\x6C\x6F\x73\x20\x47\x6F\x72\x6F\x6E"; // de la Minas de los Goron
    char lakebedTempleTextSp[] = "\x64\x65\x6C\x20\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x20\x4C\x61\x67\x6F"; // del Santuario del Lago
    char arbitersGroundsTextSp[] = "\x64\x65\x6C\x20\x50\x61\x74\xED\x62\x75\x6C\x6F\x20\x64\x65\x6C\x20\x44\x65\x73\x69\x65\x72\x74\x6F"; // del Patibulo del Desierto
    char snowpeakRuinsTextSp[] = "\x64\x65\x20\x6C\x61\x73\x20\x52\x75\x69\x6E\x61\x73\x20\x64\x65\x6C\x20\x50\x69\x63\x6F\x20\x4E\x65\x76\x61\x64\x6F"; // de las Ruinas del Pico Nevado
    char templeOfTimeTextSp[] = "\x64\x65\x6C\x20\x54\x65\x6D\x70\x6C\x6F\x20\x64\x65\x6C\x20\x54\x69\x65\x6D\x70\x6F"; // del Templo del Tiempo
    char cityInTheSkyTextSp[] = "\x64\x65\x20\x43\x65\x6C\x65\x73\x74\x69\x61"; // de Celestia
    char palaceOfTwilightTextSp[] = "\x64\x65\x6C\x20\x50\x61\x6C\x61\x63\x69\x6F\x20\x64\x65\x6C\x20\x43\x72\x65\x70\xFA\x73\x63\x75\x6C\x6F"; // del Palacio del Crepusculo
    char hyruleCastleTextSp[] = "\x64\x65\x6C\x20\x43\x61\x73\x74\x69\x6C\x6C\x6F\x20\x64\x65\x20\x48\x79\x72\x75\x6C\x65"; // del Castillo de Hyrule
    char bulblinCampTextSp[] = "\x64\x65\x6C\x20\x43\x61\x6D\x70\x6F\x20\x42\x75\x6C\x62\x69\x6E"; // del Campo Bulblin
    // clang-format on

    const MsgEntry entriesSp[] = {
        // Forest Temple small key
        forestSmallKeySp,
        sizeof(forestSmallKeySp),
        0x00E9,

        // Shadow Crystal
        shadowCrystalSp,
        sizeof(shadowCrystalSp),
        0x0096,

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
        skyBookCharacterSp,
        sizeof(skyBookCharacterSp),
        0x013F,

        // First Fused Shadow
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
        0x0077,

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

        // Small Wallet Menu Text
        smallWalletPauseSp,
        sizeof(smallWalletPauseSp),
        0x0298,

        // Big Wallet Menu Text
        bigWalletPauseSp,
        sizeof(bigWalletPauseSp),
        0x0299,

        // Giant Wallet Menu Text
        giantWalletPauseSp,
        sizeof(giantWalletPauseSp),
        0x029a,

        // Poe Soul
        poeSoulSp,
        sizeof(poeSoulSp),
        0x0144,

        // Sky Book Item Wheel Description
        skyBookDescriptionSp,
        sizeof(skyBookDescriptionSp),
        0x34d,

        // Recognition text
        recognitionSp,
        sizeof(recognitionSp),
        0x0b44,

        // Special invalid-id texts
        // Small Key
        smallKeyTextSp,
        sizeof(smallKeyTextSp),
        game_patch::SpecialMessageIds::SMALL_KEY,

        // Dungeon Map
        dungeonMapTextSp,
        sizeof(dungeonMapTextSp),
        game_patch::SpecialMessageIds::DUNGEON_MAP,

        // Compass
        compassTextSp,
        sizeof(compassTextSp),
        game_patch::SpecialMessageIds::COMPASS,

        // Big Key
        bigKeyTextSp,
        sizeof(bigKeyTextSp),
        game_patch::SpecialMessageIds::BIG_KEY,

        // Forest Temple
        forestTempleTextSp,
        sizeof(forestTempleTextSp),
        game_patch::SpecialMessageIds::FOREST_TEMPLE,

        // Goron Mines
        goronMinesTextSp,
        sizeof(goronMinesTextSp),
        game_patch::SpecialMessageIds::GORON_MINES,

        // Lakebed Temple
        lakebedTempleTextSp,
        sizeof(lakebedTempleTextSp),
        game_patch::SpecialMessageIds::LAKEBED_TEMPLE,

        // Arbiter's Grounds
        arbitersGroundsTextSp,
        sizeof(arbitersGroundsTextSp),
        game_patch::SpecialMessageIds::ARBITERS_GROUNDS,

        // Snowpeak Ruins
        snowpeakRuinsTextSp,
        sizeof(snowpeakRuinsTextSp),
        game_patch::SpecialMessageIds::SNOWPEAK_RUINS,

        // Temple of Time
        templeOfTimeTextSp,
        sizeof(templeOfTimeTextSp),
        game_patch::SpecialMessageIds::TEMPLE_OF_TIME,

        // City in the Sky
        cityInTheSkyTextSp,
        sizeof(cityInTheSkyTextSp),
        game_patch::SpecialMessageIds::CITY_IN_THE_SKY,

        // Palace of Twilight
        palaceOfTwilightTextSp,
        sizeof(palaceOfTwilightTextSp),
        game_patch::SpecialMessageIds::PALACE_OF_TWILIGHT,

        // Hyrule Castle
        hyruleCastleTextSp,
        sizeof(hyruleCastleTextSp),
        game_patch::SpecialMessageIds::HYRULE_CASTLE,

        // Bulblin Camp
        bulblinCampTextSp,
        sizeof(bulblinCampTextSp),
        game_patch::SpecialMessageIds::BULBLIN_CAMP,

        // This is an extra section that should go unused, and is only needed for _05_getMsgById in 05_itemMsgFunctions.cpp to
        // ensure that it can properly calculate sizeOut
        "",
        0,
        0xFFFF,
    };

    const uint32_t totalCustomMessagesSp = sizeof(entriesSp) / sizeof(MsgEntry);
    const MsgEntry charloDonationEntrySp = {charloDonationSp, sizeof(charloDonationSp), 0x0355};

    const ItemWheelMenuStrings itemWheelMenuStringsSp = {
        // areasBeingTracked
        {
            // Forest Temple
            // Templo del Bosque
            "\x54\x65\x6D\x70\x6C\x6F\x20\x64\x65\x6C\x20\x42\x6F\x73\x71\x75\x65",

            // Goron Mines
            // Minas de los Goron
            "\x4D\x69\x6E\x61\x73\x20\x64\x65\x20\x6C\x6F\x73\x20\x47\x6F\x72\x6F\x6E",

            // Lakebed Temple
            // Santuario del Lago
            "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x20\x4C\x61\x67\x6F",

            // Arbiter's Grounds
            // Patíbulo del Desierto
            "\x50\x61\x74\xED\x62\x75\x6C\x6F\x20\x64\x65\x6C\x20\x44\x65\x73\x69\x65\x72\x74\x6F",

            // Snowpeak Ruins
            // Ruinas del Pico Nevado
            "\x52\x75\x69\x6E\x61\x73\x20\x64\x65\x6C\x20\x50\x69\x63\x6F\x20\x4E\x65\x76\x61\x64\x6F",

            // Temple of Time
            // Templo del Tiempo
            "\x54\x65\x6D\x70\x6C\x6F\x20\x64\x65\x6C\x20\x54\x69\x65\x6D\x70\x6F",

            // City in the Sky
            // Celestia
            "\x43\x65\x6C\x65\x73\x74\x69\x61",

            // Palace of Twilight
            // Palacio del Crepúsculo
            "\x50\x61\x6C\x61\x63\x69\x6F\x20\x64\x65\x6C\x20\x43\x72\x65\x70\xFA\x73\x63\x75\x6C\x6F",

            // Hyrule Castle
            // Castillo de Hyrule
            "\x43\x61\x73\x74\x69\x6C\x6C\x6F\x20\x64\x65\x20\x48\x79\x72\x75\x6C\x65",

            // Faron Woods
            // Bosque de Farone
            "\x42\x6F\x73\x71\x75\x65\x20\x64\x65\x20\x46\x61\x72\x6F\x6E\x65",

            // Bulblin Camp
            // Campo Bulbin
            "\x43\x61\x6D\x70\x6F\x20\x42\x75\x6C\x62\x69\x6E",
        },

        // seedIsLoaded
        "Seed",

        // seedIsNotLoaded
        // Ninguna seed está cargada actualmente
        "\x4E\x69\x6E\x67\x75\x6E\x61\x20\x73\x65\x65\x64\x20\x65\x73\x74\xE1\x20\x63\x61\x72\x67\x61\x64\x61\x20\x61\x63\x74"
        "\x75\x61\x6C\x6D\x65\x6E\x74\x65",

        // yes/no
        // Sí
        "\x53\xED",

        // No
        "\x4E\x6F",

        // shadowsShards
        // Sombras Fundidas\nFragmentos de espejo
        "\x53\x6F\x6D\x62\x72\x61\x73\x20\x46\x75\x6E\x64\x69\x64\x61\x73\x0A\x46\x72\x61\x67\x6D\x65\x6E\x74\x6F\x73\x20\x64"
        "\x65\x20\x65\x73\x70\x65\x6A\x6F",

        // Pumpkin
        // Calabaza
        "\x43\x61\x6C\x61\x62\x61\x7A\x61",

        // Cheese
        // Queso
        "\x51\x75\x65\x73\x6F",

        // Gate Keys
        // Llaves de portón
        "\x4C\x6C\x61\x76\x65\x73\x20\x64\x65\x20\x70\x6F\x72\x74\xF3\x6E",

        // Areas
        // Áreas
        "\xC1\x72\x65\x61\x73",

        // Small Keys
        // Llaves\npequeñas
        "\x4C\x6C\x61\x76\x65\x73\x0A\x70\x65\x71\x75\x65\xF1\x61\x73",

        // Big Keys
        // Llaves\ngrandes
        "\x4C\x6C\x61\x76\x65\x73\x0A\x67\x72\x61\x6E\x64\x65\x73",

        // Maps
        // Mapas
        "\x4D\x61\x70\x61\x73",

        // Compasses
        // Brújulas
        "\x42\x72\xFA\x6A\x75\x6C\x61\x73",

        // helpText
        // Presiona\nInicio o Z\npara alternar\ninformación\nadicional
        "\x50\x72\x65\x73\x69\x6F\x6E\x61\x0A\x49\x6E\x69\x63\x69\x6F\x20\x6F\x20\x5A\x0A\x70\x61\x72\x61\x20\x61\x6C\x74\x65"
        "\x72\x6E\x61\x72\x0A\x69\x6E\x66\x6F\x72\x6D\x61\x63\x69\xF3\x6E\x0A\x61\x64\x69\x63\x69\x6F\x6E\x61\x6C",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsSp {
        // Fused Shadows/Mirror Shards
        187,

        // Pumpkin
        40,

        // Yes/No
        27,
        23,

        // Cheese
        83,

        // Yes/No
        18,
        14,

        // Gate Keys
        64,

        // Yes/No
        58,
        54,

        // Headers
        // Small Keys
        185,

        // Big Keys
        95,

        // Maps
        82,

        // Compasses
        69,

        // Header values
        // Small Keys values
        33,

        // Big keys values
        // Yes/No
        23,
        20,

        // Goron Mines
        26,

        // Maps values
        // Yes/No
        17,
        14,

        // Compasses values
        // Yes/No
        24,
        21,
    };
} // namespace mod::customMessages
#endif