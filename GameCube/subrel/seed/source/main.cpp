#include "main.h"
#include "cxx.h"

#include <cstdint>

namespace mod
{
    void handleSeedPatches( rando::Randomizer* rando )
    {
        rando::Seed* seed;
        if ( seed = getCurrentSeed( rando ), seed )
        {
            getConsole() << "Applying one-time patches:\n";
            seed->applyOneTimePatches( true );
            seedRelAction = SEED_ACTION_NONE;
        }
        else
        {
            getConsole() << "FATAL: Seed failed to load\n";
            seedRelAction = SEED_ACTION_FATAL;
        }
    }

    void main()
    {
        uint8_t selectedSeed = seedList->m_selectedSeed;
        switch ( seedRelAction )
        {
            case SEED_ACTION_LOAD_SEED:
            {
                // Make sure the randomizer doesn't already have memory allocated
                if ( randomizer )
                {
                    delete randomizer;
                }

                // The randomizer constructor sets m_Enabled to true
                // Align to void*, as pointers use the largest variable type in the Randomizer class
                randomizer = new ( sizeof( void* ) ) rando::Randomizer( &seedList->m_seedInfo[selectedSeed], selectedSeed );

                // One-time patches need to be applied whenever a seed is loaded
                handleSeedPatches( randomizer );
                break;
            }
            case SEED_ACTION_CHANGE_SEED:
            {
                randomizer->changeSeed( &seedList->m_seedInfo[selectedSeed], selectedSeed );

                // One-time patches need to be applied whenever a seed is loaded
                handleSeedPatches( randomizer );
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void exit() {}

}     // namespace mod