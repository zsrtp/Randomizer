/** @file 05_clearRegionTwilights.cpp
 * @author Lunar Soap
 * @brief Clears the Twilight for each region based on user settings.
 *
 * @bug No known bugs
 */
#include <cinttypes>

#include "events.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    void clearFaronTwilight( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop.faron_tear_count =
                0x10;     // Set number of tears to fill the vessel.
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |=
                0x1;     // Set the flag for having completed Faron Twilight.
            libtp::tp::d_item::execItemGet( libtp::data::items::Vessel_Of_Light_Faron );
            libtp::tp::d_item::execItemGet( libtp::data::items::Heros_Clothes );
        }
    }

    void clearEldinTwilight( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop.eldin_tear_count =
                0x10;     // Set number of tears to fill the vessel.
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |=
                0x2;     // Set the flag for having completed Eldin Twilight.
            libtp::tp::d_item::execItemGet( libtp::data::items::Vessel_Of_Light_Eldin );
        }
    }

    void clearLanayruTwilight( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop.lanayru_tear_count =
                0x10;     // Set number of tears to fill the vessel.
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |=
                0x4;     // Set the flag for having completed Lanayru Twilight.
            libtp::tp::d_item::execItemGet( libtp::data::items::Vessel_Of_Light_Lanayru );
        }
    }

    void loadShopModels( rando::Randomizer* randomizer, bool set )
    {
        if ( set && randomizer )
        {
            randomizer->m_Seed->loadShopModels();
        }
    }

    void setMinorCutsceneValues( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            // Set the flag for rupee cutscenes.
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_get_item.mItemsFlags[0] |= 0x7E;
            // Set the flag for having recieved all of the postman's letters.
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.letter_info.letter_get_bitfields[0] |= 0xFFFF;
            // Set the flags for having read all of the Postman's Letters.
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.letter_info.letter_read_bitfields[0] |= 0xFFFF;
        }
    }

    void clearMDH( rando::Randomizer* randomizer, bool set )
    {
        if ( set &&
             libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag == 0x7 )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.transform_level_flag |=
                0x8;     // Set the flag for the last transformed twilight. Also puts Midna on the player's back
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.dark_clear_level_flag |= 0x8;
        }
    }
}     // namespace mod::user_patch