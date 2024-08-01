#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_com_inf_game.h"

namespace mod::game_patch
{
    KEEP_FUNC void _00_handle_poeItem()
    {
        uint8_t* poeCountPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect.poe_count;

        // Do not increment the poe count if it is already at 60
        const uint32_t currentPoeCount = *poeCountPtr;
        if (currentPoeCount >= 60)
        {
            return;
        }

        // Increment the poe count
        *poeCountPtr = static_cast<uint8_t>(currentPoeCount + 1);
    }
} // namespace mod::game_patch