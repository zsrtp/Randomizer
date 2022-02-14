#include "game_patch/game_patch.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_msg_flow.h"
#include "tp/d_save.h"
namespace mod::game_patch
{
    void _06_writeASMPatches()
    {
        // Modify dComIfGs_Wolf_Change_Check to return true when checking to see if mdh is complete
        uint32_t wolfChangeCheckAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_com_inf_game::dComIfGs_Wolf_Change_Check );
        *reinterpret_cast<uint32_t*>( wolfChangeCheckAddress + 0x108 ) = 0x3be00000;     // Previous 0x3be00001

        // Modify event035 to not remove Auru's Memo from inventory after talking to Fyer.
        uint32_t event035MemoAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_msg_flow::event035 );
        *reinterpret_cast<uint32_t*>( event035MemoAddress + 0x40 ) = 0x2c040091;     // Previous 0x2c040090
    }
}     // namespace mod::game_patch