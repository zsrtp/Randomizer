#include "events.h"

#include <cinttypes>
#include <cstring>

#include "main.h"
#include "rando/randomizer.h"
#include "tp/d_com_inf_game.h"
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

    void offLoad( rando::Randomizer* randomizer )
    {
        if ( randomizer )
        {
            // Check if the seed is already applied to the save-file (flags etc.)
            // Try to do it otherwise
            if ( !randomizer->m_SeedInit && !strcmp( libtp::tp::d_com_inf_game::dComIfG_gameInfo.currentStage, "F_SP103" ) )
            {
                randomizer->initSave();
            }
        }
    }

    void onRELLink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        if ( randomizer )
        {
            randomizer->overrideREL( dmc );
        }
    }

    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        if ( randomizer )
        {
            randomizer->overrideDZX( chunkTypeInfo );
        }
    }
}     // namespace mod::events