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
#include "tp/d_a_shop_item_static.h"
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
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_last_stay_info.player_last_region |= 0x8;
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

    void loadShopModels( rando::Randomizer* randomizer, bool set )
    {
        if ( set )
        {
            using namespace libtp::tp;

            uint32_t num_shopItems = randomizer->m_Seed->m_Header->shopItemCheckInfo.numEntries;
            uint32_t gci_offset = randomizer->m_Seed->m_Header->shopItemCheckInfo.dataOffset;

            // Set the pointer as offset into our buffer
            mod::rando::shopCheck* allSHOP =
                reinterpret_cast<mod::rando::shopCheck*>( &randomizer->m_Seed->m_GCIData[gci_offset] );

            d_item_data::ItemResource* itemResourcePtr = &d_item_data::item_resource[0];
            for ( uint32_t i = 0; i < num_shopItems; i++ )
            {
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].arcName =
                    itemResourcePtr[allSHOP[i].replacementItemID].arcName;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].modelResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].modelResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBckResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].bckResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBrkResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].brkResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].wBtpResIdx =
                    itemResourcePtr[allSHOP[i].replacementItemID].btpResIdx;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].tevFrm =
                    itemResourcePtr[allSHOP[i].replacementItemID].tevFrm;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].btpFrm = 0xFF;
                d_a_shop_item_static::shopItemData[allSHOP[i].shopItemID].posY = 15.0f;
            }
        }
    }
}     // namespace mod::user_patch