/** @file 05_clearRegionTwilights.cpp
 * @author Lunar Soap
 * @brief Clears the Twilight for each region based on user settings.
 *
 * @bug No known bugs
 */
#include <cinttypes>

#include "events.h"
#include "rando/randomizer.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    void clearFaronTwilight( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop.faron_tear_count = 0x10;
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |= 0x1;
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_last_stay_info.player_last_region |= 0x4;
            libtp::tp::d_item::execItemGet( libtp::data::items::Vessel_Of_Light_Faron );
            libtp::tp::d_item::execItemGet( libtp::data::items::Heros_Clothes );
        }
    }

    void clearEldinTwilight( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop.eldin_tear_count = 0x10;
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.transform_level_flag |= 0x1;
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |= 0x2;
            libtp::tp::d_item::execItemGet( libtp::data::items::Vessel_Of_Light_Eldin );
        }
    }

    void clearLanayruTwilight( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop.lanayru_tear_count = 0x10;
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |= 0x4;
            libtp::tp::d_item::execItemGet( libtp::data::items::Vessel_Of_Light_Lanayru );
        }
    }
}     // namespace mod::user_patch