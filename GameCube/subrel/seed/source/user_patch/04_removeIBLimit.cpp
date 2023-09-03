/** @file 04_removeIBLimit.cpp
 * @author Lunar Soap
 * @author Zephiles
 * @brief Patches the heavy state function to remove Iron Boots speed limit
 *
 * @bug No known bugs
 */

#include "rando/randomizer.h"
#include "tp/d_a_alink.h"
#include "user_patch/user_patch.h"
#include "gc_wii/OSCache.h"

namespace mod::user_patch
{
    void removeIBLimit(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        float* heavyStateSpeed = &libtp::tp::d_a_alink::ironBootsVars.heavyStateSpeed;
        if (set)
        {
            // Set the float that Link's actor references when heavy to be the default value.
            *heavyStateSpeed = 1.f;
        }
        else
        {
            *heavyStateSpeed = 0.4f;
        }

        // Clear the cache for the modified value
        libtp::gc_wii::os_cache::DCFlushRange(heavyStateSpeed, sizeof(float));
    }
} // namespace mod::user_patch