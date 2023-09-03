/** @file 00__wallet.cpp
 * @author AECX
 * @brief Patches Links wallet to be bigger.
 *
 * @bug No known bugs
 */

#include "user_patch/user_patch.h"
#include "asm_templates.h"
#include "main.h"
#include "rando/randomizer.h"
#include "tp/d_menu_collect.h"
#include "tp/d_save.h"
#include "memory.h"

namespace mod::user_patch
{
    void patchWallet(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        using namespace libtp;

        // getConsole() << "[0] WalletPatch [" << ( set ? "x" : " " ) << "]\n";

        uint32_t getRupeeMaxPtr = reinterpret_cast<uint32_t>(&tp::d_save::getRupeeMax);
        uint32_t setWalletMaxNumPtr = reinterpret_cast<uint32_t>(&tp::d_menu_collect::setWalletMaxNum);

        uint16_t values[3] = {1000, 5000, 9999};

        if (!set)
        {
            values[0] = 300;
            values[1] = 600;
            values[2] = 1000;
        }
        mod::walletsPatched = set;

        // 300 -> 1000
        *reinterpret_cast<uint32_t*>(getRupeeMaxPtr + 0x30) = ASM_LOAD_IMMEDIATE(3, values[0]);
        // 600 -> 5000
        *reinterpret_cast<uint32_t*>(getRupeeMaxPtr + 0x38) = ASM_LOAD_IMMEDIATE(3, values[1]);
        // 1000 -> 9999 (> 4 digit not good)
        *reinterpret_cast<uint32_t*>(getRupeeMaxPtr + 0x40) = ASM_LOAD_IMMEDIATE(3, values[2]);

        // 300 -> 1000
        *reinterpret_cast<uint32_t*>(setWalletMaxNumPtr + 0x24) = ASM_COMPARE_WORD_IMMEDIATE(0, values[0]);
        // 600 -> 5000
        *reinterpret_cast<uint32_t*>(setWalletMaxNumPtr + 0x18) = ASM_COMPARE_WORD_IMMEDIATE(0, values[1]);
        // 1000 -> 9999
        *reinterpret_cast<uint32_t*>(setWalletMaxNumPtr + 0x30) = ASM_COMPARE_WORD_IMMEDIATE(0, values[2]);

        // Clear the cache for the modified values
        // Assembly instructions need to clear the instruction cache as well
        libtp::memory::clear_DC_IC_Cache(reinterpret_cast<void*>(getRupeeMaxPtr), 0x41);
        libtp::memory::clear_DC_IC_Cache(reinterpret_cast<void*>(setWalletMaxNumPtr), 0x31);
    }
} // namespace mod::user_patch