#include "main.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "user_patch/user_patch.h"
#include "asm_templates.h"
#include "memory.h"

namespace mod::user_patch
{
    void loadShopModels(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;
        modifyShopModels = set;
    }

    void setInstantText(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;
        instantTextEnabled = set;
    }

    void increaseSpinnerVelocity(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;
        increaseSpinnerSpeed = set;
    }

    void skipMajorCutscenes(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        uint32_t* skipperFunctionAddress =
            reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(libtp::tp::d_event::skipper) + 0x54);

        if (set)
        {
            // Modifies the 'skipper' function to automatically attempt to skip all major cutscenes
            *skipperFunctionAddress = ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(30, 0);
        }
        else
        {
            // Vanilla instruction
            *skipperFunctionAddress = 0x540004e7; // rlwinm r0,r0,0,19,19
        }

        libtp::memory::clear_DC_IC_Cache(skipperFunctionAddress, sizeof(uint32_t));
    }
} // namespace mod::user_patch