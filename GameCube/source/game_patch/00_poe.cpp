#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"
#include "data/flags.h"

namespace mod::game_patch
{
    KEEP_FUNC void _00_handle_poeItem()
    {
        libtp::tp::d_save::dSv_save_c* saveFilePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file;

        uint8_t* poeCountPtr = &saveFilePtr->player.player_collect.poe_count;
        const uint32_t newPoeCount = *poeCountPtr + 1;
        *poeCountPtr = static_cast<uint8_t>(newPoeCount);

        // The vanilla poe functions set a flag if the new count is exactly 20
        if (newPoeCount == 20)
        {
            libtp::tp::d_save::onEventBit(&saveFilePtr->mEvent, libtp::data::flags::EventFlags::UNK_3840);
        }
    }
} // namespace mod::game_patch