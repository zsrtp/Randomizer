/** @file 04_removeIBLimit.cpp
 * @author Lunar Soap
 * @author Zephiles
 * @brief Patches the heavy state function to remove Iron Boots speed limit
 *
 * @bug No known bugs
 */
#include <cinttypes>

#include "rando/randomizer.h"
#include "tp/d_a_alink.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    void removeIBLimit( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            // li 0
            uint32_t li = 0x38600000;
            // b +4C
            uint32_t b = 0x4800004C;

            // CheckHeavyState overwrite
            uint32_t checkHeavyStateOnAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_a_alink::checkHeavyStateOn );
            *reinterpret_cast<uint32_t*>( checkHeavyStateOnAddress + 0x84 ) = li;

            uint32_t setStickDataAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_a_alink::setStickData );
            *reinterpret_cast<uint32_t*>( setStickDataAddress + 0x5FC ) = b;
        }
    }
}     // namespace mod::user_patch