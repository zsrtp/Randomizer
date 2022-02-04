#include "game_patch/game_patch.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_save.h"
namespace mod::game_patch
{
    void _06_patchMDHWolfReturn()
    {
        // Modify dComIfGs_Wolf_Change_Check to return true when checking to see if mdh is complete
        uint32_t wolfChangeCheckAddress = reinterpret_cast<uint32_t>( &libtp::tp::d_com_inf_game::dComIfGs_Wolf_Change_Check );
        *reinterpret_cast<uint32_t*>( wolfChangeCheckAddress + 0x108 ) = 0x3be00000;     // Previous 0x3be00001
    }

    void _06_patchSaveBitFlags()
    {
        libtp::tp::d_save::saveBitLabels[0x152] = 0x00;     // Shield Attack flag.
        libtp::tp::d_save::saveBitLabels[0x153] = 0x00;     // Ending Blow flag.
        libtp::tp::d_save::saveBitLabels[0x154] = 0x00;     // Back Slice flag.
        libtp::tp::d_save::saveBitLabels[0x155] = 0x00;     // Helm Splitter flag.
        libtp::tp::d_save::saveBitLabels[0x156] = 0x00;     // Mortal Draw flag.
        libtp::tp::d_save::saveBitLabels[0x157] = 0x00;     // Jump Strike flag.
        libtp::tp::d_save::saveBitLabels[0x158] = 0x00;     // Great Spin flag.
    }
}     // namespace mod::game_patch