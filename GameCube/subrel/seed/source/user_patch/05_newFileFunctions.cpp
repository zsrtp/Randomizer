#include "main.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "user_patch/user_patch.h"
#include "asm_templates.h"
#include "memory.h"
#include "asm_templates.h"

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

#ifndef PLATFORM_WII
        uint32_t* skipperFunctionAddress =
            reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(libtp::tp::d_event::skipper) + 0x54);
#else
        uint32_t* skipperFunctionAddress =
            reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(libtp::tp::d_event::skipper) + 0x74);
#endif

        if (set)
        {
            // Modifies the 'skipper' function to automatically attempt to skip all major cutscenes
#ifndef PLATFORM_WII
            *skipperFunctionAddress = ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(30, 0); // cmplwi r30, 0
#else
            *skipperFunctionAddress = ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(29, 0); // cmplwi r29, 0
#endif
        }
        else
        {
            // Vanilla instruction
#ifndef PLATFORM_WII
            *skipperFunctionAddress = ASM_ROTATE_LEFT_WORD_IMMIDEATE_THEN_AND_WITH_MASK(0, 0, 0, 19, 19) + 1; // rlwinm r0,r0,0,19,19
#else
            *skipperFunctionAddress = ASM_COMPARE_WORD_IMMEDIATE(3, 0); // cmpwi r3,0x0
#endif
        }

        libtp::memory::clear_DC_IC_Cache(skipperFunctionAddress, sizeof(uint32_t));
    }
} // namespace mod::user_patch