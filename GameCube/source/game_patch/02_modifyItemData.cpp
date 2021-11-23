#include <string.h>

#include <cstdint>
#include <cstdio>

#include "data/items.h"
#include "game_patch/game_patch.h"
#include "tp/d_a_alink.h"
#include "tp/d_item_data.h"
#include "tp/d_save.h"

namespace mod::game_patch
{
    void _02_modifyItemData()
    {
        using namespace libtp::data;
        libtp::tp::d_item_data::ItemResource* itemResPtr = &libtp::tp::d_item_data::item_resource[0];
        libtp::tp::d_item_data::FieldItemRes* fieldItemResPtr = &libtp::tp::d_item_data::field_item_res[0];

        uint8_t itemsWithNoFieldModel[0x92] = { items::Bombs_5,
                                                items::Bombs_10,
                                                items::Bombs_20,
                                                items::Bombs_30,
                                                items::Water_Bombs_5,
                                                items::Water_Bombs_10,
                                                items::Water_Bombs_15,
                                                items::Water_Bombs_3,
                                                items::Bomblings_5,
                                                items::Bomblings_10,
                                                items::Bomblings_3,
                                                items::Bombling_1,
                                                items::Master_Sword,
                                                items::Wooden_Shield,
                                                items::Hylian_Shield,
                                                items::Shadow_Crystal,
                                                items::Big_Wallet,
                                                items::Giant_Wallet,
                                                items::Coral_Earring,
                                                items::Hawkeye,
                                                items::Boomerang,
                                                items::Spinner,
                                                items::Ball_and_Chain,
                                                items::Heros_Bow,
                                                items::Clawshot,
                                                items::Iron_Boots,
                                                items::Dominion_Rod,
                                                items::Double_Clawshots,
                                                items::Master_Sword_Light,
                                                items::Fishing_Rod,
                                                items::Slingshot,
                                                items::Dominion_Rod_Uncharged,
                                                items::Giant_Bomb_Bag,
                                                items::Empty_Bomb_Bag,
                                                items::Goron_Bomb_Bag,
                                                items::Big_Quiver,
                                                items::Giant_Quiver,
                                                items::Empty_Bottle,
                                                items::Red_Potion_Shop,
                                                items::Blue_Potion,
                                                items::Milk,
                                                items::Sera_Bottle,
                                                items::Lantern_Oil_Shop,
                                                items::Water,
                                                items::Hot_Spring_Water_Shop,
                                                items::Lantern_Refill_Shop,
                                                items::Jovani_Bottle,
                                                items::Renardos_Letter,
                                                items::Invoice,
                                                items::Ilias_Charm,
                                                items::Horse_Call,
                                                items::Forest_Temple_Small_Key,
                                                items::Goron_Mines_Small_Key,
                                                items::Lakebed_Temple_Small_Key,
                                                items::Arbiters_Grounds_Small_Key,
                                                items::Snowpeak_Ruins_Small_Key,
                                                items::Temple_of_Time_Small_Key,
                                                items::City_in_The_Sky_Small_Key,
                                                items::Palace_of_Twilight_Small_Key,
                                                items::Hyrule_Castle_Small_Key,
                                                items::Bulblin_Camp_Key,
                                                items::Foolish_Item,
                                                items::Aurus_Memo,
                                                items::Asheis_Sketch,
                                                items::Forest_Temple_Big_Key,
                                                items::Lakebed_Temple_Big_Key,
                                                items::Arbiters_Grounds_Big_Key,
                                                items::Temple_of_Time_Big_Key,
                                                items::City_in_The_Sky_Big_Key,
                                                items::Palace_of_Twilight_Big_Key,
                                                items::Hyrule_Castle_Big_Key,
                                                items::Forest_Temple_Compass,
                                                items::Goron_Mines_Compass,
                                                items::Lakebed_Temple_Compass,
                                                items::Coro_Bottle,
                                                items::Bee_Larva_Shop,
                                                items::Vessel_Of_Light_Faron,
                                                items::Vessel_Of_Light_Eldin,
                                                items::Vessel_Of_Light_Lanayru,
                                                items::Arbiters_Grounds_Compass,
                                                items::Snowpeak_Ruins_Compass,
                                                items::Temple_of_Time_Compass,
                                                items::City_in_The_Sky_Compass,
                                                items::Palace_of_Twilight_Compass,
                                                items::Hyrule_Castle_Compass,
                                                items::Forest_Temple_Dungeon_Map,
                                                items::Goron_Mines_Dungeon_Map,
                                                items::Lakebed_Temple_Dungeon_Map,
                                                items::Arbiters_Grounds_Dungeon_Map,
                                                items::Snowpeak_Ruins_Dungeon_Map,
                                                items::Temple_of_Time_Dungeon_Map,
                                                items::City_in_The_Sky_Dungeon_Map,
                                                items::Palace_of_Twilight_Dungeon_Map,
                                                items::Hyrule_Castle_Dungeon_Map,
                                                items::Male_Beetle,
                                                items::Female_Beetle,
                                                items::Male_Butterfly,
                                                items::Female_Butterfly,
                                                items::Male_Stag_Beetle,
                                                items::Female_Stag_Beetle,
                                                items::Male_Grasshopper,
                                                items::Female_Grasshopper,
                                                items::Male_Phasmid,
                                                items::Female_Phasmid,
                                                items::Male_Pill_Bug,
                                                items::Female_Pill_Bug,
                                                items::Male_Mantis,
                                                items::Female_Mantis,
                                                items::Male_Ladybug,
                                                items::Female_Ladybug,
                                                items::Male_Snail,
                                                items::Female_Snail,
                                                items::Male_Dragonfly,
                                                items::Female_Dragonfly,
                                                items::Male_Ant,
                                                items::Female_Ant,
                                                items::Male_Dayfly,
                                                items::Female_Dayfly,
                                                items::Poe_Soul,
                                                items::Ending_Blow,
                                                items::Shield_Attack,
                                                items::Back_Slice,
                                                items::Helm_Splitter,
                                                items::Mortal_Draw,
                                                items::Jump_Strike,
                                                items::Great_Spin,
                                                items::Ancient_Sky_Book_empty,
                                                items::Ancient_Sky_Book_partly_filled,
                                                items::Ancient_Sky_Book_completed,
                                                items::Purple_Rupee_Links_house,
                                                items::Small_Key_N_Faron_Gate,
                                                items::Gate_Keys,
                                                items::Ordon_Pumpkin,
                                                items::Ordon_Goat_Cheese,
                                                items::Bed_Key,
                                                items::Key_Shard_1,
                                                items::Key_Shard_2,
                                                items::Key_Shard_3,
                                                items::Big_Key_Goron_Mines,
                                                items::Coro_Key };

        uint8_t customSmallKeyItemIDs[10] = { items::Forest_Temple_Small_Key,
                                              items::Goron_Mines_Small_Key,
                                              items::Lakebed_Temple_Small_Key,
                                              items::Arbiters_Grounds_Small_Key,
                                              items::Snowpeak_Ruins_Small_Key,
                                              items::Temple_of_Time_Small_Key,
                                              items::City_in_The_Sky_Small_Key,
                                              items::Palace_of_Twilight_Small_Key,
                                              items::Hyrule_Castle_Small_Key,
                                              items::Bulblin_Camp_Key };

        uint8_t customBigKeyItemIDs[7] = { items::Forest_Temple_Big_Key,
                                           items::Lakebed_Temple_Big_Key,
                                           items::Arbiters_Grounds_Big_Key,
                                           items::Temple_of_Time_Big_Key,
                                           items::City_in_The_Sky_Big_Key,
                                           items::Palace_of_Twilight_Big_Key,
                                           items::Hyrule_Castle_Big_Key };

        uint8_t customDungeonMapItemIDs[9] = { items::Forest_Temple_Dungeon_Map,
                                               items::Goron_Mines_Dungeon_Map,
                                               items::Lakebed_Temple_Dungeon_Map,
                                               items::Arbiters_Grounds_Dungeon_Map,
                                               items::Snowpeak_Ruins_Dungeon_Map,
                                               items::Temple_of_Time_Dungeon_Map,
                                               items::City_in_The_Sky_Dungeon_Map,
                                               items::Palace_of_Twilight_Dungeon_Map,
                                               items::Hyrule_Castle_Dungeon_Map };

        uint8_t customCompassItemIDs[9] = { items::Forest_Temple_Compass,
                                            items::Goron_Mines_Compass,
                                            items::Lakebed_Temple_Compass,
                                            items::Arbiters_Grounds_Compass,
                                            items::Snowpeak_Ruins_Compass,
                                            items::Temple_of_Time_Compass,
                                            items::City_in_The_Sky_Compass,
                                            items::Palace_of_Twilight_Compass,
                                            items::Hyrule_Castle_Compass };

        uint8_t customHiddenSkillItemIDs[7] = { items::Ending_Blow,
                                                items::Shield_Attack,
                                                items::Back_Slice,
                                                items::Helm_Splitter,
                                                items::Mortal_Draw,
                                                items::Jump_Strike,
                                                items::Great_Spin };

        // Generic item variables
        libtp::tp::d_item_data::ItemResource* itemResourcePtr = &libtp::tp::d_item_data::item_resource[0];
		libtp::tp::d_item_data::ItemInfo* itemInfoPtr = &libtp::tp::d_item_data::item_info[0];
		uint8_t* getSeTypePtr = &libtp::tp::d_a_alink::getSeType[0];

		libtp::tp::d_item_data::ItemInfo* yellowRupeeInfoPtr = &libtp::tp::d_item_data::item_info[items::Yellow_Rupee];

		libtp::tp::d_item_data::ItemResource* smallKeyItemResourcePtr = &itemResourcePtr[items::Small_Key];
		libtp::tp::d_item_data::ItemResource* bigKeyItemResourcePtr = &itemResourcePtr[items::Big_Key];
		libtp::tp::d_item_data::ItemResource* dungeonMapItemResourcePtr = &itemResourcePtr[items::Dungeon_Map];
		libtp::tp::d_item_data::ItemResource* compassItemResourcePtr = &itemResourcePtr[items::Compass];
        
		uint32_t smallKeyItemInfo = *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Small_Key] ) );
		uint32_t bigKeyItemInfo = *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Big_Key] ) );
		uint32_t dungeonMapItemInfo = *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Dungeon_Map] ) );
		uint32_t compassItemInfo = *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Compass] ) );
        
		uint8_t smallKeySeType = getSeTypePtr[items::Small_Key];
		uint8_t bigKeySeType = getSeTypePtr[items::Big_Key];
		uint8_t dungeonMapSeType = getSeTypePtr[items::Dungeon_Map];
		uint8_t compassSeType = getSeTypePtr[items::Compass];
        

        // Set the item info for the custom small keys to that of the current Small Key
        for ( uint32_t i = 0; i < sizeof( customSmallKeyItemIDs ) / sizeof( customSmallKeyItemIDs[0] ); i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customSmallKeyItemIDs[i]] ) ) =
                smallKeyItemInfo;

            getSeTypePtr[customSmallKeyItemIDs[i]] = smallKeySeType;

            memcpy( &itemResourcePtr[customSmallKeyItemIDs[i]],
                    smallKeyItemResourcePtr,
                    sizeof( libtp::tp::d_item_data::ItemResource ) );
        }

        // Set the item info for the custom big keys to that of the current Big Key
        for ( uint32_t i = 0; i < sizeof( customBigKeyItemIDs ) / sizeof( customBigKeyItemIDs[0] ); i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customBigKeyItemIDs[i]] ) ) = bigKeyItemInfo;

            getSeTypePtr[customBigKeyItemIDs[i]] = bigKeySeType;

            memcpy( &itemResourcePtr[customBigKeyItemIDs[i]],
                    bigKeyItemResourcePtr,
                    sizeof( libtp::tp::d_item_data::ItemResource ) );
        }

        // Set the item info for the custom dungeon map to that of the current Dungeon Map
        for ( uint32_t i = 0; i < sizeof( customDungeonMapItemIDs ) / sizeof( customDungeonMapItemIDs[0] ); i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customDungeonMapItemIDs[i]] ) ) =
                dungeonMapItemInfo;

            getSeTypePtr[customDungeonMapItemIDs[i]] = dungeonMapSeType;

            memcpy( &itemResourcePtr[customDungeonMapItemIDs[i]],
                    dungeonMapItemResourcePtr,
                    sizeof( libtp::tp::d_item_data::ItemResource ) );
        }

        // Set the item info for the custom compass to that of the current compass
        for ( uint32_t i = 0; i < sizeof( customCompassItemIDs ) / sizeof( customCompassItemIDs[0] ); i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customCompassItemIDs[i]] ) ) =
                compassItemInfo;

            getSeTypePtr[customCompassItemIDs[i]] = compassSeType;

            memcpy( &itemResourcePtr[customCompassItemIDs[i]],
                    compassItemResourcePtr,
                    sizeof( libtp::tp::d_item_data::ItemResource ) );
        }

        // Set the item info for the custom hidden skill items
        for ( uint32_t i = 0; i < sizeof( customHiddenSkillItemIDs ) / sizeof( customHiddenSkillItemIDs[0] ); i++ )
        {
            itemResourcePtr[customHiddenSkillItemIDs[i]].arcName = "O_gD_memo";
            itemResourcePtr[customHiddenSkillItemIDs[i]].ringTexResIdx = 0x003D;
            itemResourcePtr[customHiddenSkillItemIDs[i]].modelResIdx = 0x0003;
            itemResourcePtr[customHiddenSkillItemIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customHiddenSkillItemIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customHiddenSkillItemIDs[i]] = 0x2;
        }

        // Set the Model and SeType for the Master/Light Swords. We will use the Ordon Sword for now.
        memcpy( &itemResourcePtr[items::Master_Sword],&itemResourcePtr[items::Ordon_Sword],sizeof( libtp::tp::d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Master_Sword_Light], &itemResourcePtr[items::Ordon_Sword], sizeof( libtp::tp::d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Horse_Call],&itemResourcePtr[items::Ilias_Charm],sizeof( libtp::tp::d_item_data::ItemResource ) );   
		memcpy( &itemResourcePtr[items::Bomb_Bag_Regular_Bombs],&itemResourcePtr[items::Goron_Bomb_Bag],sizeof( libtp::tp::d_item_data::ItemResource ) );

        // Set the model and SeType for all other items that need it.
		itemResourcePtr[items::Master_Sword].ringTexResIdx = 0x0042;
        itemResourcePtr[items::Shadow_Crystal].ringTexResIdx = 0x002E;
		itemResourcePtr[items::Master_Sword_Light].ringTexResIdx = 0x0042;

		getSeTypePtr[items::Master_Sword] = getSeTypePtr[items::Clawshot];
		getSeTypePtr[items::Master_Sword_Light] = getSeTypePtr[items::Clawshot];
		getSeTypePtr[items::Shadow_Crystal] = getSeTypePtr[items::Clawshot];
        getSeTypePtr[items::Bomb_Bag_Regular_Bombs] = getSeTypePtr[items::Goron_Bomb_Bag];
		getSeTypePtr[items::Horse_Call] = getSeTypePtr[items::Clawshot];

        
        

        // Get the size of the array that contains the list of items without a field model then iterate through each entry,
        // applying the appropriate item resource values to the field item resource values.
        // For items that dont have a field model, we will use a yellow rupee as this allows for the item to be collected
        // without modifying too much.
        uint32_t loopCount = sizeof( itemsWithNoFieldModel ) / sizeof( itemsWithNoFieldModel[0] );
        for ( uint32_t i = 0; i < loopCount; i++ )
        {
            uint32_t item = itemsWithNoFieldModel[i];
            // Set the item's field model to use the getItem model.
            itemInfoPtr[item].mShadowSize = yellowRupeeInfoPtr->mShadowSize;
            itemInfoPtr[item].mCollisionH = yellowRupeeInfoPtr->mCollisionH;
            itemInfoPtr[item].mCollisionR = yellowRupeeInfoPtr->mCollisionR;
            fieldItemResPtr[item].arcName = itemResPtr[item].arcName;
            fieldItemResPtr[item].modelResIdx = itemResPtr[item].modelResIdx;
        }
    }
}     // namespace mod::game_patch