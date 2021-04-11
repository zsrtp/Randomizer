/** @file 00__wallet.cpp
 * @author AECX
 * @brief Patches Links wallet to be bigger.
 *
 * @bug No known bugs
 */
#include <cinttypes>

#include "game_patch/game_patch.h"
#include "gc/OSCache.h"
#include "tp/d_menu_collect.h"
#include "tp/d_save.h"

namespace mod::game_patch
{
    void patchWallet( bool set )
    {
        using namespace libtp;

        uint32_t getRupeeMaxPtr = reinterpret_cast<uint32_t>( &tp::d_save::getRupeeMax );
        uint32_t setWalletMaxNumPtr = reinterpret_cast<uint32_t>( &tp::d_menu_collect::setWalletMaxNum );

        uint32_t values[3] = { 1000, 5000, 9999 };

        if ( !set )
        {
            values[0] = 300;
            values[1] = 600;
            values[2] = 1000;
        }

        // 300 -> 1000
        *reinterpret_cast<uint32_t*>( getRupeeMaxPtr + 0x30 ) = asm_li | values[0];
        // 600 -> 5000
        *reinterpret_cast<uint32_t*>( getRupeeMaxPtr + 0x38 ) = asm_li | values[1];
        // 1000 -> 9999 (> 4 digit not good)
        *reinterpret_cast<uint32_t*>( getRupeeMaxPtr + 0x40 ) = asm_li | values[2];

        // 600 -> 5000
        *reinterpret_cast<uint32_t*>( setWalletMaxNumPtr + 0x18 ) = asm_cmpwi | values[0];
        // 300 -> 1000
        *reinterpret_cast<uint32_t*>( setWalletMaxNumPtr + 0x24 ) = asm_cmpwi | values[1];
        // 1000 -> 9999
        *reinterpret_cast<uint32_t*>( setWalletMaxNumPtr + 0x30 ) = asm_cmpwi | values[2];

        // Update the cache
        gc::os_cache::DCFlushRange( reinterpret_cast<void*>( getRupeeMaxPtr ), 0x41 );
        gc::os_cache::DCFlushRange( reinterpret_cast<void*>( setWalletMaxNumPtr ), 0x31 );
    }
}     // namespace mod::game_patch