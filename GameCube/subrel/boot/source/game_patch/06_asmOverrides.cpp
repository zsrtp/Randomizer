#include "game_patch/game_patch.h"
#include "tp/d_item.h"
#include "tp/d_msg_flow.h"
namespace mod::game_patch
{
    void _06_writeASMPatches()
    {
        // Default to US
        uint32_t* enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B8A4 );
        uint32_t* patchMessageCalculation = reinterpret_cast<uint32_t*>( 0x80238F58 );
        uint32_t woodenSwordFunctionAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_item::item_func_WOOD_STICK );
        uint32_t event035MemoAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_msg_flow::event035 );

// Get the addresses to overwrite
#ifdef TP_US
        enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B8A4 );
        patchMessageCalculation = reinterpret_cast<uint32_t*>( 0x80238F58 );
#elif defined TP_EU
        enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B878 );
        patchMessageCalculation = reinterpret_cast<uint32_t*>( 0x802395D8 );
#elif defined TP_JP
        enableCrashScreen = reinterpret_cast<uint32_t*>( 0x8000B8A4 );
        patchMessageCalculation = reinterpret_cast<uint32_t*>( 0x802398E0 );
#endif

        // Perform the overwrites

        /* If the address is loaded into the cache before the overwrite is made,
        then the cache will need to be cleared after the overwrite */

        // Enable the crash screen
        *enableCrashScreen = 0x48000014;     // b 0x14

        // Nop out the instruction that causes a miscalculation in message resources.
        *patchMessageCalculation = 0x60000000;     // nop

        // Modify the Wooden Sword function to not set a region flag by default by nopping out the function call to isSwitch
        *reinterpret_cast<uint32_t*>( woodenSwordFunctionAddress + 0x40 ) = 0x60000000;     // Previous 0x4bf9cafd

        // Modify event035 to not remove Auru's Memo from inventory after talking to Fyer.
        *reinterpret_cast<uint32_t*>( event035MemoAddress + 0x40 ) = 0x2c040091;     // Previous 0x2c040090
    }
}     // namespace mod::game_patch