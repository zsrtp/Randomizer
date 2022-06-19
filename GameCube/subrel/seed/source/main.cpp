#include "main.h"

#include <cstdint>

namespace mod
{
    void main()
    {
        uint8_t selectedSeed = seedList->m_selectedSeed;
        switch ( seedRelAction )
        {
            case SEED_ACTION_LOAD_SEED:
            {
                // The randomizer constructor sets m_Enabled to true
                randomizer = new rando::Randomizer( &seedList->m_seedInfo[selectedSeed], selectedSeed );

                // One-time patches need to be applied whenever a seed is loaded
                mod::console << "Applying one-time patches:\n";
                randomizer->m_Seed->applyOneTimePatches( true );

                seedRelAction = SEED_ACTION_NONE;
                break;
            }
            case SEED_ACTION_CHANGE_SEED:
            {
                randomizer->changeSeed( &seedList->m_seedInfo[selectedSeed], selectedSeed );

                // One-time patches need to be applied whenever a seed is loaded
                mod::console << "Applying one-time patches:\n";
                randomizer->m_Seed->applyOneTimePatches( true );

                seedRelAction = SEED_ACTION_NONE;
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