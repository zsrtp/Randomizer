#include "main.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    void clearFaronTwilight(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        if (set)
        {
            libtp::tp::d_save::dSv_player_c* playerPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player;
            playerPtr->light_drop.faron_tear_count = 0x10;           // Set number of tears to fill the vessel.
            playerPtr->player_status_b.dark_clear_level_flag |= 0x1; // Set the flag for having completed Faron Twilight.

            libtp::tp::d_item::execItemGet(libtp::data::items::Vessel_Of_Light_Faron);

            if (!events::haveItem(libtp::data::items::Heros_Clothes))
            {
                libtp::tp::d_item::execItemGet(libtp::data::items::Heros_Clothes);
            }
        }
    }

    void clearEldinTwilight(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        if (set)
        {
            libtp::tp::d_save::dSv_player_c* playerPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player;
            playerPtr->light_drop.eldin_tear_count = 0x10;           // Set number of tears to fill the vessel.
            playerPtr->player_status_b.dark_clear_level_flag |= 0x2; // Set the flag for having completed Eldin Twilight.

            libtp::tp::d_item::execItemGet(libtp::data::items::Vessel_Of_Light_Eldin);
        }
    }

    void clearLanayruTwilight(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        if (set)
        {
            libtp::tp::d_save::dSv_player_c* playerPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player;
            playerPtr->light_drop.lanayru_tear_count = 0x10;         // Set number of tears to fill the vessel.
            playerPtr->player_status_b.dark_clear_level_flag |= 0x4; // Set the flag for having completed Lanayru Twilight.

            libtp::tp::d_item::execItemGet(libtp::data::items::Vessel_Of_Light_Lanayru);
        }
    }

    void setMinorCutsceneValues(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        if (set)
        {
            libtp::tp::d_save::dSv_player_c* playerPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player;

            // Set the flag for rupee cutscenes.
            playerPtr->player_get_item.mItemsFlags[0] |= 0x7E;

            // Set the flag for having recieved all of the postman's letters.
            libtp::tp::d_save::dSv_letter_info_c* letterInfoPtr = &playerPtr->letter_info;
            letterInfoPtr->letter_get_bitfields[0] |= 0xFFFF;

            // Set the flags for having read all of the Postman's Letters.
            letterInfoPtr->letter_read_bitfields[0] |= 0xFFFF;
        }
    }

    void clearMDH(rando::Randomizer* randomizer, bool set)
    {
        (void)randomizer;

        libtp::tp::d_save::dSv_player_status_b_c* playerStatusPtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b;

        if (set && playerStatusPtr->dark_clear_level_flag == 0x7)
        {
            playerStatusPtr->transform_level_flag |=
                0x8; // Set the flag for the last transformed twilight. Also puts Midna on the player's back

            playerStatusPtr->dark_clear_level_flag |= 0x8;
        }
    }

    void setMapRegionBits(rando::Randomizer* randomizer, bool set)
    {
        if (set)
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_last_stay_info.player_last_region |=
                randomizer->m_Seed->m_Header->mapClearBits;
        }
    }
} // namespace mod::user_patch