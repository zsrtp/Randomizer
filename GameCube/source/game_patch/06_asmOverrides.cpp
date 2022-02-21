#include "game_patch/game_patch.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_msg_flow.h"
#include "tp/d_save.h"
namespace mod::game_patch
{
    void _06_writeASMPatches()
    {
        // Default to US/JP
        uint32_t* enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B8A4 );

// Get the addresses to overwrit
#ifdef TP_US
        enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B8A4 );
#elif defined TP_EU
        enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B878 );
#elif defined TP_JP
        enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B8A4 );
#endif

        // Perform the overwrites

        /* If the address is loaded into the cache before the overwrite is made,
        then the cache will need to be cleared after the overwrite */

        // Enable the crash screen
        *enableCrashScreen = 0x48000014;     // b 0x14

        // Modify dComIfGs_Wolf_Change_Check to return true when checking to see if mdh is complete
        uint32_t wolfChangeCheckAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_com_inf_game::dComIfGs_Wolf_Change_Check );
        *reinterpret_cast<uint32_t*>( wolfChangeCheckAddress + 0x108 ) = 0x3be00000;     // Previous 0x3be00001

        // Modify event035 to not remove Auru's Memo from inventory after talking to Fyer.
        uint32_t event035MemoAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_msg_flow::event035 );
        *reinterpret_cast<uint32_t*>( event035MemoAddress + 0x40 ) = 0x2c040091;     // Previous 0x2c040090
    }
}     // namespace mod::game_patch