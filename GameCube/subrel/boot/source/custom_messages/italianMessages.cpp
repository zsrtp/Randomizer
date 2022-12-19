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
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Santuario della foresta 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x6c\x61\x20\x66\x6f\x72\x65\x73\x74\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nella 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Miniera dei Goron 
        "\x4d\x69\x6e\x69\x65\x72\x61\x20\x64\x65\x69\x20\x47\x6f\x72\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Santuario nel lago 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x6e\x65\x6c\x20\x6c\x61\x67\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Patibolo del deserto 
        "\x50\x61\x74\x69\x62\x6f\x6c\x6f\x20\x64\x65\x6c\x20\x64\x65\x73\x65\x72\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nelle 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x6c\x65\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Rovine sul ghiacciaio 
        "\x52\x6f\x76\x69\x6e\x65\x20\x73\x75\x6c\x20\x67\x68\x69\x61\x63\x63\x69\x61\x69\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Santuario del tempo 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x20\x74\x65\x6d\x70\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( citySmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nella 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Città eterea 
        "\x43\x69\x74\x74\xe0\x20\x65\x74\x65\x72\x65\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palazzo del crepuscolo 
        "\x50\x61\x6c\x61\x7a\x7a\x6f\x20\x64\x65\x6c\x20\x63\x72\x65\x70\x75\x73\x63\x6f\x6c\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Castello di Hyrule 
        "\x43\x61\x73\x74\x65\x6c\x6c\x6f\x20\x64\x69\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( campSmallKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Piccola chiave 
        "\x50\x69\x63\x63\x6f\x6c\x61\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzate nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x65\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //campo dei Bulbin 
        "\x63\x61\x6d\x70\x6f\x20\x64\x65\x69\x20\x42\x75\x6c\x62\x69\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( shadowCrystalIt )
        MSG_SPEED(MSG_SPEED_SLOW)
        //Ora hai il  
        "\x4f\x72\x61\x20\x68\x61\x69\x20\x69\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristallo Maledetto 
        "\x43\x72\x69\x73\x74\x61\x6c\x6c\x6f\x20\x4d\x61\x6c\x65\x64\x65\x74\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Questa manifestazione dei poterimalvagi di  
        "\x21\x0A\x51\x75\x65\x73\x74\x61\x20\x6d\x61\x6e\x69\x66\x65\x73\x74\x61\x7a\x69\x6f\x6e\x65\x20\x64\x65\x69\x20\x70\x6f\x74\x65\x72\x69\x0A\x6d\x61\x6c\x76\x61\x67\x69\x20\x64\x69\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Zant  
        "\x5a\x61\x6e\x74\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //ti permette sitransformarti quando vuoi.  
        "\x74\x69\x20\x70\x65\x72\x6d\x65\x74\x74\x65\x20\x73\x69\x0A\x74\x72\x61\x6e\x73\x66\x6f\x72\x6d\x61\x72\x74\x69\x20\x71\x75\x61\x6e\x64\x6f\x20\x76\x75\x6f\x69\x2e\x20"
    MSG_END()
    MSG_BEGIN_ARRAY( forestDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianel  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Santuario della foresta 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x6c\x61\x20\x66\x6f\x72\x65\x73\x74\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianella  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Miniera dei Goron 
        "\x4d\x69\x6e\x69\x65\x72\x61\x20\x64\x65\x69\x20\x47\x6f\x72\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianel  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Santuario nel lago 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x6e\x65\x6c\x20\x6c\x61\x67\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianel  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x20"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Patibolo del deserto 
        "\x50\x61\x74\x69\x62\x6f\x6c\x6f\x20\x64\x65\x6c\x20\x64\x65\x73\x65\x72\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ora hai la  
        "\x4f\x72\x61\x20\x68\x61\x69\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa del palazzo 
        "\x4d\x61\x70\x70\x61\x20\x64\x65\x6c\x20\x70\x61\x6c\x61\x7a\x7a\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti mostrerà la via nelle 
        "\x21\x0A\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x20\x6e\x65\x6c\x6c\x65\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Rovine sul ghiacciaio 
        "\x52\x6f\x76\x69\x6e\x65\x20\x73\x75\x6c\x20\x67\x68\x69\x61\x63\x63\x69\x61\x69\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianel  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Santuario del tempo 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x20\x74\x65\x6d\x70\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianella  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Città eterea 
        "\x43\x69\x74\x74\xe0\x20\x65\x74\x65\x72\x65\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianel  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x20"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palazzo del crepuscolo 
        "\x50\x61\x6c\x61\x7a\x7a\x6f\x20\x64\x65\x6c\x20\x63\x72\x65\x70\x75\x73\x63\x6f\x6c\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleDungeonMapIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto la  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Mappa di unlabirinto 
        "\x4d\x61\x70\x70\x61\x20\x64\x69\x20\x75\x6e\x0A\x6c\x61\x62\x69\x72\x69\x6e\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Ti mostrerà la vianel  
        "\x21\x20\x54\x69\x20\x6d\x6f\x73\x74\x72\x65\x72\xe0\x20\x6c\x61\x20\x76\x69\x61\x0A\x6e\x65\x6c\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Castello di Hyrule 
        "\x43\x61\x73\x74\x65\x6c\x6c\x6f\x20\x64\x69\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( forestCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nel 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Santuario della foresta 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x6c\x61\x20\x66\x6f\x72\x65\x73\x74\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( minesCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nella 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Miniera dei Goron 
        "\x4d\x69\x6e\x69\x65\x72\x61\x20\x64\x65\x69\x20\x47\x6f\x72\x6f\x6e"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nel 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Santuario nel lago 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x6e\x65\x6c\x20\x6c\x61\x67\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nel 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Patibolo del deserto 
        "\x50\x61\x74\x69\x62\x6f\x6c\x6f\x20\x64\x65\x6c\x20\x64\x65\x73\x65\x72\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( snowpeakCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nelle 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x6c\x65\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //Rovine sul ghiacciaio 
        "\x52\x6f\x76\x69\x6e\x65\x20\x73\x75\x6c\x20\x67\x68\x69\x61\x63\x63\x69\x61\x69\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nel 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Santuario del tempo 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x20\x74\x65\x6d\x70\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nella 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x20\x74\x72\x6f\x76\x61\x6e\x6f\x0A\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x6c\x61\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Città eterea 
        "\x43\x69\x74\x74\xe0\x20\x65\x74\x65\x72\x65\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nel 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palazzo del crepuscolo 
        "\x50\x61\x6c\x61\x7a\x7a\x6f\x20\x64\x65\x6c\x20\x63\x72\x65\x70\x75\x73\x63\x6f\x6c\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleCompassIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Bussola 
        "\x42\x75\x73\x73\x6f\x6c\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ti indicherà dove si trovanogli scrigni nel 
        "\x21\x0A\x54\x69\x20\x69\x6e\x64\x69\x63\x68\x65\x72\xe0\x20\x64\x6f\x76\x65\x20\x73\x69\x0A\x74\x72\x6f\x76\x61\x6e\x6f\x20\x67\x6c\x69\x20\x73\x63\x72\x69\x67\x6e\x69\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Castello di Hyrule 
        "\x43\x61\x73\x74\x65\x6c\x6c\x6f\x20\x64\x69\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( forestBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        //Santuario della foresta 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x6c\x61\x20\x66\x6f\x72\x65\x73\x74\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( lakebedBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //Santuario nel lago 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x6e\x65\x6c\x20\x6c\x61\x67\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( arbitersBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        //Patibolo del deserto 
        "\x50\x61\x74\x69\x62\x6f\x6c\x6f\x20\x64\x65\x6c\x20\x64\x65\x73\x65\x72\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( timeBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //Santuario del tempo 
        "\x53\x61\x6e\x74\x75\x61\x72\x69\x6f\x20\x64\x65\x6c\x20\x74\x65\x6d\x70\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( cityBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nella 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x6c\x61\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //Città eterea 
        "\x43\x69\x74\x74\xe0\x20\x65\x74\x65\x72\x65\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( palaceBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //Palazzo del crepuscolo 
        "\x50\x61\x6c\x61\x7a\x7a\x6f\x20\x64\x65\x6c\x20\x63\x72\x65\x70\x75\x73\x63\x6f\x6c\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( hyruleBigKeyIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto una  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Grande chiave 
        "\x47\x72\x61\x6e\x64\x65\x20\x63\x68\x69\x61\x76\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Pùo essere utilizzata nel 
        "\x21\x0A\x50\xf9\x6f\x20\x65\x73\x73\x65\x72\x65\x20\x75\x74\x69\x6c\x69\x7a\x7a\x61\x74\x61\x20\x6e\x65\x6c\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        //Castello di Hyrule 
        "\x43\x61\x73\x74\x65\x6c\x6c\x6f\x20\x64\x69\x20\x48\x79\x72\x75\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //. 
        "\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( endingBlowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso il  
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x69\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Colpo di grazia 
        "\x43\x6f\x6c\x70\x6f\x20\x64\x69\x20\x67\x72\x61\x7a\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( shieldAttackIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso l' 
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x6c\x27"
        MSG_COLOR(MSG_COLOR_RED)
        //Attaco scudo 
        "\x41\x74\x74\x61\x63\x6f\x20\x73\x63\x75\x64\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( backSliceIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso il  
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x69\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Colpo alle spalle 
        "\x43\x6f\x6c\x70\x6f\x20\x61\x6c\x6c\x65\x20\x73\x70\x61\x6c\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( helmSplitterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso lo  
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x6c\x6f\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Spacca elmo 
        "\x53\x70\x61\x63\x63\x61\x20\x65\x6c\x6d\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( mortalDrawIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso il  
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x69\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Tiro mortale 
        "\x54\x69\x72\x6f\x20\x6d\x6f\x72\x74\x61\x6c\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( jumpStrikeIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso il  
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x69\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Colpo in salto 
        "\x43\x6f\x6c\x70\x6f\x20\x69\x6e\x20\x73\x61\x6c\x74\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( greatSpinIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai appreso il  
        "\x48\x61\x69\x20\x61\x70\x70\x72\x65\x73\x6f\x20\x69\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Gran tornado 
        "\x47\x72\x61\x6e\x20\x74\x6f\x72\x6e\x61\x64\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( poweredRodIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Lo  
        "\x4c\x6f\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Scettro del plagio  
        "\x53\x63\x65\x74\x74\x72\x6f\x20\x64\x65\x6c\x20\x70\x6c\x61\x67\x69\x6f\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //è dotatodi nuovo di poteri magici! Puòinfondere vita alle antichestatue, anche nel presente. 
        "\xe8\x20\x64\x6f\x74\x61\x74\x6f\x0A\x64\x69\x20\x6e\x75\x6f\x76\x6f\x20\x64\x69\x20\x70\x6f\x74\x65\x72\x69\x20\x6d\x61\x67\x69\x63\x69\x21\x20\x50\x75\xf2\x0A\x69\x6e\x66\x6f\x6e\x64\x65\x72\x65\x20\x76\x69\x74\x61\x20\x61\x6c\x6c\x65\x20\x61\x6e\x74\x69\x63\x68\x65\x0A\x73\x74\x61\x74\x75\x65\x2c\x20\x61\x6e\x63\x68\x65\x20\x6e\x65\x6c\x20\x70\x72\x65\x73\x65\x6e\x74\x65\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( firstCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ecco la prima  
        "\x45\x63\x63\x6f\x20\x6c\x61\x20\x70\x72\x69\x6d\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Lettera degliEterei 
        "\x4c\x65\x74\x74\x65\x72\x61\x20\x64\x65\x67\x6c\x69\x0A\x45\x74\x65\x72\x65\x69"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Una parte delle Letteremancanti nella formulacontenuta nell'Antico libro. 
        "\x21\x20\x55\x6e\x61\x20\x70\x61\x72\x74\x65\x20\x64\x65\x6c\x6c\x65\x20\x4c\x65\x74\x74\x65\x72\x65\x0A\x6d\x61\x6e\x63\x61\x6e\x74\x69\x20\x6e\x65\x6c\x6c\x61\x20\x66\x6f\x72\x6d\x75\x6c\x61\x0A\x63\x6f\x6e\x74\x65\x6e\x75\x74\x61\x20\x6e\x65\x6c\x6c\x27\x41\x6e\x74\x69\x63\x6f\x20\x6c\x69\x62\x72\x6f\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( secondCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ecco la seconda  
        "\x45\x63\x63\x6f\x20\x6c\x61\x20\x73\x65\x63\x6f\x6e\x64\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Lettera degliEterei 
        "\x4c\x65\x74\x74\x65\x72\x61\x20\x64\x65\x67\x6c\x69\x0A\x45\x74\x65\x72\x65\x69"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Una parte delle Letteremancanti nella formulacontenuta nell'Antico libro. 
        "\x21\x20\x55\x6e\x61\x20\x70\x61\x72\x74\x65\x20\x64\x65\x6c\x6c\x65\x20\x4c\x65\x74\x74\x65\x72\x65\x0A\x6d\x61\x6e\x63\x61\x6e\x74\x69\x20\x6e\x65\x6c\x6c\x61\x20\x66\x6f\x72\x6d\x75\x6c\x61\x0A\x63\x6f\x6e\x74\x65\x6e\x75\x74\x61\x20\x6e\x65\x6c\x6c\x27\x41\x6e\x74\x69\x63\x6f\x20\x6c\x69\x62\x72\x6f\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ecco la terza  
        "\x45\x63\x63\x6f\x20\x6c\x61\x20\x74\x65\x72\x7a\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Lettera degliEterei 
        "\x4c\x65\x74\x74\x65\x72\x61\x20\x64\x65\x67\x6c\x69\x0A\x45\x74\x65\x72\x65\x69"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Una parte delle Letteremancanti nella formulacontenuta nell'Antico libro. 
        "\x21\x20\x55\x6e\x61\x20\x70\x61\x72\x74\x65\x20\x64\x65\x6c\x6c\x65\x20\x4c\x65\x74\x74\x65\x72\x65\x0A\x6d\x61\x6e\x63\x61\x6e\x74\x69\x20\x6e\x65\x6c\x6c\x61\x20\x66\x6f\x72\x6d\x75\x6c\x61\x0A\x63\x6f\x6e\x74\x65\x6e\x75\x74\x61\x20\x6e\x65\x6c\x6c\x27\x41\x6e\x74\x69\x63\x6f\x20\x6c\x69\x62\x72\x6f\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ecco la quarta  
        "\x45\x63\x63\x6f\x20\x6c\x61\x20\x71\x75\x61\x72\x74\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Lettera degliEterei 
        "\x4c\x65\x74\x74\x65\x72\x61\x20\x64\x65\x67\x6c\x69\x0A\x45\x74\x65\x72\x65\x69"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Una parte delle Letteremancanti nella formulacontenuta nell'Antico libro. 
        "\x21\x20\x55\x6e\x61\x20\x70\x61\x72\x74\x65\x20\x64\x65\x6c\x6c\x65\x20\x4c\x65\x74\x74\x65\x72\x65\x0A\x6d\x61\x6e\x63\x61\x6e\x74\x69\x20\x6e\x65\x6c\x6c\x61\x20\x66\x6f\x72\x6d\x75\x6c\x61\x0A\x63\x6f\x6e\x74\x65\x6e\x75\x74\x61\x20\x6e\x65\x6c\x6c\x27\x41\x6e\x74\x69\x63\x6f\x20\x6c\x69\x62\x72\x6f\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( fifthCharacterIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ecco la quinta  
        "\x45\x63\x63\x6f\x20\x6c\x61\x20\x71\x75\x69\x6e\x74\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Lettera degliEterei 
        "\x4c\x65\x74\x74\x65\x72\x61\x20\x64\x65\x67\x6c\x69\x0A\x45\x74\x65\x72\x65\x69"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Una parte delle Letteremancanti nella formulacontenuta nell'Antico libro. 
        "\x21\x20\x55\x6e\x61\x20\x70\x61\x72\x74\x65\x20\x64\x65\x6c\x6c\x65\x20\x4c\x65\x74\x74\x65\x72\x65\x0A\x6d\x61\x6e\x63\x61\x6e\x74\x69\x20\x6e\x65\x6c\x6c\x61\x20\x66\x6f\x72\x6d\x75\x6c\x61\x0A\x63\x6f\x6e\x74\x65\x6e\x75\x74\x61\x20\x6e\x65\x6c\x6c\x27\x41\x6e\x74\x69\x63\x6f\x20\x6c\x69\x62\x72\x6f\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( firstFusedShadowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto un frammento di 
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x75\x6e\x20\x66\x72\x61\x6d\x6d\x65\x6e\x74\x6f\x20\x64\x69\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristallo oscuro 
        "\x43\x72\x69\x73\x74\x61\x6c\x6c\x6f\x20\x6f\x73\x63\x75\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! C'è  
        "\x21\x20\x43\x27\xe8\x20"
        MSG_COLOR(MSG_COLOR_GREEN)
        //muschio 
        "\x6d\x75\x73\x63\x68\x69\x6f\x0A"
        MSG_COLOR(MSG_COLOR_WHITE)
        //crescendo sopra lui.. 
        "\x63\x72\x65\x73\x63\x65\x6e\x64\x6f\x20\x73\x6f\x70\x72\x61\x20\x6c\x75\x69\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( secondFusedShadowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto il secondoframmento di  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x69\x6c\x20\x73\x65\x63\x6f\x6e\x64\x6f\x0A\x66\x72\x61\x6d\x6d\x65\x6e\x74\x6f\x20\x64\x69\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristallo oscuro 
        "\x43\x72\x69\x73\x74\x61\x6c\x6c\x6f\x20\x6f\x73\x63\x75\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Irradia  
        "\x21\x0A\x49\x72\x72\x61\x64\x69\x61\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //calore  
        "\x63\x61\x6c\x6f\x72\x65\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //come fuoco.. 
        "\x63\x6f\x6d\x65\x20\x66\x75\x6f\x63\x6f\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdFusedShadowIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto il utilmoframmento di  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x69\x6c\x20\x75\x74\x69\x6c\x6d\x6f\x0A\x66\x72\x61\x6d\x6d\x65\x6e\x74\x6f\x20\x64\x69\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Cristallo oscuro 
        "\x43\x72\x69\x73\x74\x61\x6c\x6c\x6f\x20\x6f\x73\x63\x75\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Ma quell'odore è di..  
        "\x21\x0A\x4d\x61\x20\x71\x75\x65\x6c\x6c\x27\x6f\x64\x6f\x72\x65\x20\xe8\x20\x64\x69\x2e\x2e\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        //pesce 
        "\x70\x65\x73\x63\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!? 
        "\x21\x3f"
    MSG_END()
    MSG_BEGIN_ARRAY( secondMirrorShardIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto il secondoframmento del  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x69\x6c\x20\x73\x65\x63\x6f\x6e\x64\x6f\x0A\x66\x72\x61\x6d\x6d\x65\x6e\x74\x6f\x20\x64\x65\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Specchio oscuro 
        "\x53\x70\x65\x63\x63\x68\x69\x6f\x20\x6f\x73\x63\x75\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!È rilucente com'è  
        "\x21\x0A\xc8\x20\x72\x69\x6c\x75\x63\x65\x6e\x74\x65\x20\x63\x6f\x6d\x27\xe8\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //freddo 
        "\x66\x72\x65\x64\x64\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.. 
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( thirdMirrorShardIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto il terzoframmento del  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x69\x6c\x20\x74\x65\x72\x7a\x6f\x0A\x66\x72\x61\x6d\x6d\x65\x6e\x74\x6f\x20\x64\x65\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Specchio oscuro 
        "\x53\x70\x65\x63\x63\x68\x69\x6f\x20\x6f\x73\x63\x75\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //!Sembra vecchio come il  
        "\x21\x0A\x53\x65\x6d\x62\x72\x61\x20\x76\x65\x63\x63\x68\x69\x6f\x20\x63\x6f\x6d\x65\x20\x69\x6c\x20"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        //tempo 
        "\x74\x65\x6d\x70\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.. 
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( fourthMirrorShardIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Hai ottenuto il ultimo frammento del  
        "\x48\x61\x69\x20\x6f\x74\x74\x65\x6e\x75\x74\x6f\x20\x69\x6c\x20\x75\x6c\x74\x69\x6d\x6f\x20\x66\x72\x61\x6d\x6d\x65\x6e\x74\x6f\x0A\x64\x65\x6c\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Specchio oscuro 
        "\x53\x70\x65\x63\x63\x68\x69\x6f\x20\x6f\x73\x63\x75\x72\x6f"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Sembra più leggero  
        "\x21\x20\x53\x65\x6d\x62\x72\x61\x0a\x70\x69\xf9\x20\x6c\x65\x67\x67\x65\x72\x6f\x20"
        MSG_COLOR(MSG_COLOR_YELLOW)
        //dell'aria 
        "\x64\x65\x6c\x6c\x27\x61\x72\x69\x61"
        MSG_COLOR(MSG_COLOR_WHITE)
        //.. 
        "\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( foolishItemIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Un  
        "\x55\x6e\x20"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        //vento freddo  
        "\x76\x65\x6e\x74\x6f\x20\x66\x72\x65\x64\x64\x6f\x20"
        MSG_COLOR(MSG_COLOR_WHITE)
        //soffia.. 
        "\x73\x6f\x66\x66\x69\x61\x2e\x2e"
    MSG_END()
    MSG_BEGIN_ARRAY( talkToMidnaIt )
        //Cosa vuoi,  
        "\x43\x6f\x73\x61\x20\x76\x75\x6f\x69\x2c\x20"
        MSG_PLYR_NAME
        //? 
        "\x3f"
        MSG_OPTION_LIST(MSG_OPTION_1)
        //Trasformare 
        "\x54\x72\x61\x73\x66\x6f\x72\x6d\x61\x72\x65\x0A"
        MSG_OPTION_LIST(MSG_OPTION_2)
        //Teletrasportare 
        "\x54\x65\x6c\x65\x74\x72\x61\x73\x70\x6f\x72\x74\x61\x72\x65\x0A"
        MSG_OPTION_LIST(MSG_OPTION_3)
        //Cambiare il tempo del giorno 
        "\x43\x61\x6d\x62\x69\x61\x72\x65\x20\x69\x6c\x20\x74\x65\x6d\x70\x6f\x20\x64\x65\x6c\x20\x67\x69\x6f\x72\x6e\x6f"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ora hai un  
        "\x4f\x72\x61\x20\x68\x61\x69\x20\x75\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Portarupie grande 
        "\x50\x6f\x72\x74\x61\x72\x75\x70\x69\x65\x20\x67\x72\x61\x6e\x64\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Può contenere fino a  
        "\x21\x0A\x50\x75\xf2\x20\x63\x6f\x6e\x74\x65\x6e\x65\x72\x65\x20\x66\x69\x6e\x6f\x20\x61\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        //5.000 Rupie 
        "\x35\x2e\x30\x30\x30\x20\x52\x75\x70\x69\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Ora hai un  
        "\x4f\x72\x61\x20\x68\x61\x69\x20\x75\x6e\x20"
        MSG_COLOR(MSG_COLOR_RED)
        //Portarupie gigante 
        "\x50\x6f\x72\x74\x61\x72\x75\x70\x69\x65\x20\x67\x69\x67\x61\x6e\x74\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! Può contenere anche  
        "\x21\x0A\x50\x75\xf2\x20\x63\x6f\x6e\x74\x65\x6e\x65\x72\x65\x20\x61\x6e\x63\x68\x65\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        //9.999 Rupie 
        "\x39\x2e\x39\x39\x39\x20\x52\x75\x70\x69\x65"
        MSG_COLOR(MSG_COLOR_WHITE)
        //! 
        "\x21"
    MSG_END()
    MSG_BEGIN_ARRAY( smallWalletPauseIt )
        MSG_SPEED(MSG_SPEED_FAST)
        //Oggetto dell'infanzia. Può contenere fino a 1000 Rupie.
        "\x4F\x67\x67\x65\x74\x74\x6F\x20\x64\x65\x6C\x6C\x27\x69\x6E\x66\x61\x6E\x7A\x69\x61\x2E\x20\x50\x75\xF2\x0A\x63\x6F\x6E\x74\x65\x6E\x65\x72\x65\x20\x66\x69\x6E\x6F\x20\x61\x20\x31\x2E\x30\x30\x30\x20\x52\x75\x70\x69\x65\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( bigWalletPauseIt )
        MSG_SPEED(MSG_SPEED_FAST)
        // Portarupie ricevuto in dono da Xenia, la principessa del regno degli insetti. Può contenere fino a 5000 Rupie.
        "\x50\x6F\x72\x74\x61\x72\x75\x70\x69\x65\x20\x72\x69\x63\x65\x76\x75\x74\x6F\x20\x69\x6E\x20\x64\x6F\x6E\x6F\x0A\x64\x61\x20\x58\x65\x6E\x69\x61\x2C\x20\x6C\x61\x20\x70\x72\x69\x6E\x63\x69\x70\x65\x73\x73\x61\x20\x64\x65\x6C\x0A\x72\x65\x67\x6E\x6F\x20\x64\x65\x67\x6C\x69\x20\x69\x6E\x73\x65\x74\x74\x69\x2E\x20\x50\x75\xF2\x0A\x63\x6F\x6E\x74\x65\x6E\x65\x72\x65\x20\x66\x69\x6E\x6F\x20\x61\x20\x35\x2E\x30\x30\x30\x20\x52\x75\x70\x69\x65\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( giantWalletPauseIt )
        MSG_SPEED(MSG_SPEED_FAST)
        // Portarupie ricevuto in dono da Xenia, la principessa del regno degli insetti. Lo merita solo chi ha aiutato il regno. Può contenere fino a 9.999 Rupie.
        "\x50\x6F\x72\x74\x61\x72\x75\x70\x69\x65\x20\x72\x69\x63\x65\x76\x75\x74\x6F\x20\x69\x6E\x20\x64\x6F\x6E\x6F\x20\x64\x61\x20\x58\x65\x6E\x69\x61\x2C\x0A\x6C\x61\x20\x70\x72\x69\x6E\x63\x69\x70\x65\x73\x73\x61\x20\x64\x65\x6C\x20\x72\x65\x67\x6E\x6F\x20\x64\x65\x67\x6C\x69\x20\x69\x6E\x73\x65\x74\x74\x69\x2E\x0A\x4C\x6F\x20\x6D\x65\x72\x69\x74\x61\x20\x73\x6F\x6C\x6F\x20\x63\x68\x69\x20\x68\x61\x20\x61\x69\x75\x74\x61\x74\x6F\x20\x69\x6C\x20\x72\x65\x67\x6E\x6F\x2E\x0A\x50\x75\xF2\x20\x63\x6F\x6E\x74\x65\x6E\x65\x72\x65\x20\x66\x69\x6E\x6F\x20\x61\x20\x39\x2E\x39\x39\x39\x20\x52\x75\x70\x69\x65\x2E"
    MSG_END()
    MSG_BEGIN_ARRAY( charloDonationIt )
    // Avresti qualche spicciolo da dare per la pace di Hyrule?
        "\x41\x76\x72\x65\x73\x74\x69\x20\x71\x75\x61\x6C\x63\x68\x65\x20\x73\x70\x69\x63\x63\x69\x6F\x6C\x6F\x20\x64\x61\x0A\x64\x61\x72\x65\x20\x70\x65\x72\x20\x6C\x61\x20\x70\x61\x63\x65\x20\x64\x69\x20\x48\x79\x72\x75\x6C\x65\x3F\x31"
        MSG_OPTION_LIST( MSG_OPTION_1 ) 
        // 100 Rupie
        "\x31\x30\x30\x20\x52\x75\x70\x69\x65\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_2 ) 
        // 50 Rupie
        "\x35\x30\x20\x52\x75\x70\x69\x65\x0A" 
        MSG_OPTION_LIST( MSG_OPTION_3 ) 
        // No
        "\x4E\x6F";
    MSG_END()

    MSG_BEGIN_ARRAY( recognitionIt )
        MSG_SPEED(MSG_SPEED_FAST)
        // La Squadra Randomizer vuole ringraziare ai nostri fantastici tester. Senza di voi, questo progetto non sarebbe quello lo che è oggi
        "\x4C\x61\x20\x53\x71\x75\x61\x64\x72\x61\x20\x52\x61\x6E\x64\x6F\x6D\x69\x7A\x65\x72\x20\x76\x75\x6F\x6C\x65\n\x72\x69\x6E\x67\x72\x61\x7A\x69\x61\x72\x65\x20\x61\x69\x20\x6E\x6F\x73\x74\x72\x69\n\x66\x61\x6E\x74\x61\x73\x74\x69\x63\x69\x20\x74\x65\x73\x74\x65\x72\x2E\x20\x53\x65\x6E\x7A\x61\x20\x64\x69\n\x76\x6F\x69\x2C\x20\x71\x75\x65\x73\x74\x6F\x20\x70\x72\x6F\x67\x65\x74\x74\x6F\x20\x6E\x6F\x6E\n\x73\x61\x72\x65\x62\x62\x65\x20\x71\x75\x65\x6C\x6C\x6F\x20\x6C\x6F\x20\x63\x68\x65\x20\xE8\x20\x6F\x67\x67\x69: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END()
        // clang-format on

        MsgEntry entriesIt[TOTAL_CUSTOM_MESSAGES] = {
            // Forest Temple small key
            forestSmallKeyIt,
            sizeof( forestSmallKeyIt ),
            0x00E9,

            // Goron Mines small key
            minesSmallKeyIt,
            sizeof( minesSmallKeyIt ),
            0x00EA,

            // Lakebed Temple small key
            lakebedSmallKeyIt,
            sizeof( lakebedSmallKeyIt ),
            0x00EB,

            // Arbiter's Grounds small key
            arbitersSmallKeyIt,
            sizeof( arbitersSmallKeyIt ),
            0x00EC,

            // Snowpeak Ruins small key
            snowpeakSmallKeyIt,
            sizeof( snowpeakSmallKeyIt ),
            0x00ED,

            // Temple of Time small key
            timeSmallKeyIt,
            sizeof( timeSmallKeyIt ),
            0x00EE,

            // City in the Sky small key
            citySmallKeyIt,
            sizeof( citySmallKeyIt ),
            0x00EF,

            // Palace of Twilight small key
            palaceSmallKeyIt,
            sizeof( palaceSmallKeyIt ),
            0x00F0,

            // Hyrule Castle small key
            hyruleSmallKeyIt,
            sizeof( hyruleSmallKeyIt ),
            0x00F1,

            // Bulblin Camp small key
            campSmallKeyIt,
            sizeof( campSmallKeyIt ),
            0x00F2,

            // Shadow Crystal
            shadowCrystalIt,
            sizeof( shadowCrystalIt ),
            0x0096,

            // Forest Temple dungeon map
            forestDungeonMapIt,
            sizeof( forestDungeonMapIt ),
            0x011A,

            // Goron Mines dungeon map
            minesDungeonMapIt,
            sizeof( minesDungeonMapIt ),
            0x011B,

            // Lakebed Temple dungeon map
            lakebedDungeonMapIt,
            sizeof( lakebedDungeonMapIt ),
            0x011C,

            // Arbiter's Grounds dungeon map
            arbitersDungeonMapIt,
            sizeof( arbitersDungeonMapIt ),
            0x011D,

            // Snowpeak Ruins dungeon map
            snowpeakDungeonMapIt,
            sizeof( snowpeakDungeonMapIt ),
            0x011E,

            // Temple of Time dungeon map
            timeDungeonMapIt,
            sizeof( timeDungeonMapIt ),
            0x011F,

            // City in the Sky dungeon map
            cityDungeonMapIt,
            sizeof( cityDungeonMapIt ),
            0x0120,

            // Palace of Twilight dungeon map
            palaceDungeonMapIt,
            sizeof( palaceDungeonMapIt ),
            0x0121,

            // Hyrule Castle dungeon map
            hyruleDungeonMapIt,
            sizeof( hyruleDungeonMapIt ),
            0x0122,

            // Forest Temple compass
            forestCompassIt,
            sizeof( forestCompassIt ),
            0x00FD,

            // Goron Mines compass
            minesCompassIt,
            sizeof( minesCompassIt ),
            0x00FE,

            // Lakebed Temple compass
            lakebedCompassIt,
            sizeof( lakebedCompassIt ),
            0x00FF,

            // Arbiter's Grounds compass
            arbitersCompassIt,
            sizeof( arbitersCompassIt ),
            0x010C,

            // Snowpeak Ruins compass
            snowpeakCompassIt,
            sizeof( snowpeakCompassIt ),
            0x010D,

            // Temple of Time compass
            timeCompassIt,
            sizeof( timeCompassIt ),
            0x010E,

            // City in the Sky compass
            cityCompassIt,
            sizeof( cityCompassIt ),
            0x010F,

            // Palace of Twilight compass
            palaceCompassIt,
            sizeof( palaceCompassIt ),
            0x0110,

            // Hyrule Castle compass
            hyruleCompassIt,
            sizeof( hyruleCompassIt ),
            0x0111,

            // Forest Temple big key
            forestBigKeyIt,
            sizeof( forestBigKeyIt ),
            0x00F6,

            // Lakebed Temple big key
            lakebedBigKeyIt,
            sizeof( lakebedBigKeyIt ),
            0x00F7,

            // Arbiter's Grounds big key
            arbitersBigKeyIt,
            sizeof( arbitersBigKeyIt ),
            0x00F8,

            // Temple of Time big key
            timeBigKeyIt,
            sizeof( timeBigKeyIt ),
            0x00F9,

            // City in the Sky big key
            cityBigKeyIt,
            sizeof( cityBigKeyIt ),
            0x00FA,

            // Palace of Twilight big key
            palaceBigKeyIt,
            sizeof( palaceBigKeyIt ),
            0x00FB,

            // Hyrule Castle big key
            hyruleBigKeyIt,
            sizeof( hyruleBigKeyIt ),
            0x00FC,

            // Ending Blow hidden skill
            endingBlowIt,
            sizeof( endingBlowIt ),
            0x0145,

            // Shield Attack hidden skill
            shieldAttackIt,
            sizeof( shieldAttackIt ),
            0x0146,

            // Back Slice hidden skill
            backSliceIt,
            sizeof( backSliceIt ),
            0x0147,

            // Helm Splitter hidden skill
            helmSplitterIt,
            sizeof( helmSplitterIt ),
            0x0148,

            // Mortal Draw hidden skill
            mortalDrawIt,
            sizeof( mortalDrawIt ),
            0x0149,

            // Jump Strike hidden skill
            jumpStrikeIt,
            sizeof( jumpStrikeIt ),
            0x014A,

            // Great Spin hidden skill
            greatSpinIt,
            sizeof( greatSpinIt ),
            0x014B,

            // Powered up Dominion Rod
            poweredRodIt,
            sizeof( poweredRodIt ),
            0x00B0,

            // First Ancient Sky Book character
            firstCharacterIt,
            sizeof( firstCharacterIt ),
            0x013F,

            // Second Ancient Sky Book character
            secondCharacterIt,
            sizeof( secondCharacterIt ),
            0x0140,

            // Third Ancient Sky Book character
            thirdCharacterIt,
            sizeof( thirdCharacterIt ),
            0x0141,

            // Fourth Ancient Sky Book character
            fourthCharacterIt,
            sizeof( fourthCharacterIt ),
            0x0142,

            // Fifth Ancient Sky Book character
            fifthCharacterIt,
            sizeof( fifthCharacterIt ),
            0x0143,

            // Sixth Ancient Sky Book character
            firstFusedShadowIt,
            sizeof( firstFusedShadowIt ),
            0x013C,

            // Second Fused Shadow
            secondFusedShadowIt,
            sizeof( secondFusedShadowIt ),
            0x013D,

            // Third Fused Shadow
            thirdFusedShadowIt,
            sizeof( thirdFusedShadowIt ),
            0x013E,

            // Second Mirror Shard
            secondMirrorShardIt,
            sizeof( secondMirrorShardIt ),
            0x0109,

            // Third Mirror Shard
            thirdMirrorShardIt,
            sizeof( thirdMirrorShardIt ),
            0x010A,

            // Fourth Mirror Shard
            fourthMirrorShardIt,
            sizeof( fourthMirrorShardIt ),
            0x010B,

            // Foolish Item
            foolishItemIt,
            sizeof( foolishItemIt ),
            0x0077,

            // Talking to Midna
            talkToMidnaIt,
            sizeof( talkToMidnaIt ),
            0x0BBB,

            // Big Wallet
            bigWalletIt,
            sizeof( bigWalletIt ),
            0x0099,

            // Giant Wallet
            giantWalletIt,
            sizeof( giantWalletIt ),
            0x009A,

            // Small Wallet Menu Text
            smallWalletPauseIt,
            sizeof( smallWalletPauseIt ),
            0x0298,

            // Big Wallet Menu Text
            bigWalletPauseIt,
            sizeof( bigWalletPauseIt ),
            0x0299,

            // Giant Wallet Menu Text
            giantWalletPauseIt,
            sizeof( giantWalletPauseIt ),
            0x029a,

            // Recognition text
            recognitionIt,
            sizeof( recognitionIt ),
            0x0b44,
    };

    const MsgEntry charloDonationEntryIt = { charloDonationIt, sizeof( charloDonationIt ), 0x0355 };

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

            // Bulblin Camp
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