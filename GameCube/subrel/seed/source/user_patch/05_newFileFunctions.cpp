#include "main.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    void loadShopModels( rando::Randomizer* randomizer, bool set )
    {
        if ( set && seedIsLoaded( randomizer ) )
        {
            randomizer->m_Seed->loadShopModels();
        }
    }
}     // namespace mod::user_patch