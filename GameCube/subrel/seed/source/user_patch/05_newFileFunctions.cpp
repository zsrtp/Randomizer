#include "main.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "user_patch/user_patch.h"

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
        uint32_t skipperFunctionAddress = reinterpret_cast<uint32_t>(libtp::tp::d_event::skipper);
        if (set)
        {
            // Modifies the 'skipper' function to automatically attempt to skip all major cutscenes
            *reinterpret_cast<uint32_t*>(skipperFunctionAddress + 0x54) = 0x281e0000; // cmplwi r30, 0
        }
        else
        {
            // Vanilla instruction
            *reinterpret_cast<uint32_t*>(skipperFunctionAddress + 0x54) = 540004e7; // rlwinm r0,r0,0,19,19
        }
    }
} // namespace mod::user_patch