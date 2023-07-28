#include "game_patch/game_patch.h"
#include "data/items.h"
#include "tp/d_item.h"

namespace mod::game_patch
{
    void _00_poe(void)
    {
        libtp::tp::d_item::item_func_ptr[libtp::data::items::Poe_Soul] = _00_handle_poeItem;
    }
} // namespace mod::game_patch