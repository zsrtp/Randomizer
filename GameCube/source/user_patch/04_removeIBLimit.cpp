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
            uint32_t ironBootsVars = reinterpret_cast<uint32_t>( &libtp::tp::d_a_alink::ironBootsVars );
            *reinterpret_cast<float*>( ironBootsVars + 0x14 ) = 1.f;
        }
    }
}     // namespace mod::user_patch