#include "data/items.h"
#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"

namespace mod::game_patch
{
    void _00_poe( void )
    {
        libtp::tp::d_item::item_func_ptr[libtp::data::items::Poe_Soul] = []( void )
        {
            // Increase poe count
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.scratchPad.wQuestLogData[0x10C]++;
        };
    }
}     // namespace mod::game_patch