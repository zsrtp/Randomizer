#include "main.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    void loadShopModels( rando::Randomizer* randomizer, bool set )
    {
        rando::Seed* seed;
        if ( set && ( seed = getCurrentSeed( randomizer ), seed ) )
        {
            seed->loadShopModels();
        }
    }
}     // namespace mod::user_patch