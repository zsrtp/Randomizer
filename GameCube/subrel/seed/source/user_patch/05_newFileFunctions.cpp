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
} // namespace mod::user_patch