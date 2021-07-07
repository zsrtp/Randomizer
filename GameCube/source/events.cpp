#include "events.h"

#include <cinttypes>

#include "main.h"
#include "rando/randomizer.h"
#include "tp/dzx.h"

namespace mod::events
{
    void onLoad( rando::Randomizer* randomizer )
    {
        if ( randomizer )
        {
            randomizer->onStageLoad();
        }
    }

    void offLoad( rando::Randomizer* randomizer ) { return; }

    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        if ( randomizer )
        {
            randomizer->replaceDZX( chunkTypeInfo );
        }
    }
}     // namespace mod::events