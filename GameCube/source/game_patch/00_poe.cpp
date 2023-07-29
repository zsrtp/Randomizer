#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_com_inf_game.h"

namespace mod::game_patch
{
    KEEP_FUNC void _00_handle_poeItem()
    {
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect.poe_count++;
    }
} // namespace mod::game_patch