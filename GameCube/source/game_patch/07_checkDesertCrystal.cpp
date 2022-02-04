#include <cstring>

#include "data/items.h"
#include "data/stages.h"
#include "game_patch/game_patch.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"

namespace mod::game_patch
{
    void _07_checkDesertCrystal()
    {
        using namespace libtp::tp::d_com_inf_game;
        using namespace libtp::data;
        if ( libtp::tp::d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Gerudo_Desert] ) )
        {
            if ( libtp::tp::d_item::checkItemGet( items::Shadow_Crystal, 1 ) )
            {
                strncpy( dComIfG_gameInfo.save.save_file.player.player_return_place.link_current_stage,
                         stage::allStages[stage::stageIDs::Lake_Hylia],
                         sizeof( dComIfG_gameInfo.save.save_file.player.player_return_place.link_current_stage ) - 1 );
                dComIfG_gameInfo.save.save_file.player.player_return_place.link_spawn_point_id = 0x85;
                dComIfG_gameInfo.save.save_file.player.player_return_place.link_room_id = 0x0;
            }
        }
    }
}     // namespace mod::game_patch