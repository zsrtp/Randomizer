#include <cstring>

#include "game_patch/game_patch.h"
#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"

namespace mod::game_patch
{
    void _07_checkPlayerStageReturn()
    {
        using namespace libtp::tp::d_com_inf_game;
        using namespace libtp::data;

        // If we are in the desert and cannot transform/warp, we set link's save point to Lake Hylia.
        const auto stagesPtr = &stage::allStages[0];

        libtp::tp::d_save::dSv_player_c* playerPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player;
        libtp::tp::d_save::dSv_player_return_place_c* playerReturnPlacePtr = &playerPtr->player_return_place;

        if (libtp::tp::d_a_alink::checkStageName(stagesPtr[stage::stageIDs::Gerudo_Desert]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[stage::stageIDs::Bulblin_Camp]))
        {
            if (!events::haveItem(items::Shadow_Crystal))
            {
                strncpy(playerReturnPlacePtr->link_current_stage,
                        stagesPtr[stage::stageIDs::Lake_Hylia],
                        sizeof(playerReturnPlacePtr->link_current_stage) - 1);

                playerReturnPlacePtr->link_spawn_point_id = 0x85;
                playerReturnPlacePtr->link_room_id = 0x0;
            }
        }
        // If we are in Lake Hylia during Lanayru Twilight and we cannot transform, set link's spawn point to Hyrule Field.
        else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[stage::stageIDs::Lake_Hylia]))
        {
            if (events::haveItem(items::Shadow_Crystal) || libtp::tp::d_save::isDarkClearLV(&playerPtr->player_status_b, 2))
            {
                return;
            }
            else
            {
                strncpy(playerReturnPlacePtr->link_current_stage,
                        stagesPtr[stage::stageIDs::Hyrule_Field],
                        sizeof(playerReturnPlacePtr->link_current_stage) - 1);

                playerReturnPlacePtr->link_spawn_point_id = 0x0;
                playerReturnPlacePtr->link_room_id = 0x6;
            }
        }
        else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[stage::stageIDs::Sacred_Grove]))
        {
            if (!events::haveItem(items::Shadow_Crystal))
            {
                strncpy(playerReturnPlacePtr->link_current_stage,
                        stagesPtr[stage::stageIDs::Faron_Woods],
                        sizeof(playerReturnPlacePtr->link_current_stage) - 1);

                playerReturnPlacePtr->link_spawn_point_id = 0xFE;
                playerReturnPlacePtr->link_room_id = 0x6;
            }
        }
    }
} // namespace mod::game_patch