#include <cstdint>
#include <cstring>

#include "game_patch/game_patch.h"
#include "data/items.h"
#include "tp/d_item_data.h"
#include "tp/d_a_alink.h"
#include "tp/d_item.h"

namespace mod::game_patch
{
    static const uint8_t itemsWithNoFieldModel[] = { libtp::data::items::Bombs_5,
                                                     libtp::data::items::Bombs_10,
                                                     libtp::data::items::Bombs_20,
                                                     libtp::data::items::Bombs_30,
                                                     libtp::data::items::Water_Bombs_5,
                                                     libtp::data::items::Water_Bombs_10,
                                                     libtp::data::items::Water_Bombs_15,
                                                     libtp::data::items::Water_Bombs_3,
                                                     libtp::data::items::Bomblings_5,
                                                     libtp::data::items::Bomblings_10,
                                                     libtp::data::items::Bomblings_3,
                                                     libtp::data::items::Bombling_1,
                                                     libtp::data::items::Magic_Armor,
                                                     libtp::data::items::Zora_Armor,
                                                     libtp::data::items::Wooden_Sword,
                                                     libtp::data::items::Master_Sword,
                                                     libtp::data::items::Ordon_Shield,
                                                     libtp::data::items::Wooden_Shield,
                                                     libtp::data::items::Hylian_Shield,
                                                     libtp::data::items::Shadow_Crystal,
                                                     libtp::data::items::Big_Wallet,
                                                     libtp::data::items::Giant_Wallet,
                                                     libtp::data::items::Coral_Earring,
                                                     libtp::data::items::Hawkeye,
                                                     libtp::data::items::Boomerang,
                                                     libtp::data::items::Spinner,
                                                     libtp::data::items::Ball_and_Chain,
                                                     libtp::data::items::Heros_Bow,
                                                     libtp::data::items::Clawshot,
                                                     libtp::data::items::Ordon_Sword,
                                                     libtp::data::items::Iron_Boots,
                                                     libtp::data::items::Dominion_Rod,
                                                     libtp::data::items::Double_Clawshots,
                                                     libtp::data::items::Master_Sword_Light,
                                                     libtp::data::items::Fishing_Rod,
                                                     libtp::data::items::Slingshot,
                                                     libtp::data::items::Dominion_Rod_Uncharged,
                                                     libtp::data::items::Giant_Bomb_Bag,
                                                     libtp::data::items::Empty_Bomb_Bag,
                                                     libtp::data::items::Goron_Bomb_Bag,
                                                     libtp::data::items::Bomb_Bag_Regular_Bombs,
                                                     libtp::data::items::Big_Quiver,
                                                     libtp::data::items::Giant_Quiver,
                                                     libtp::data::items::Empty_Bottle,
                                                     libtp::data::items::Red_Potion_Shop,
                                                     libtp::data::items::Blue_Potion,
                                                     libtp::data::items::Milk,
                                                     libtp::data::items::Sera_Bottle,
                                                     libtp::data::items::Lantern_Oil_Shop,
                                                     libtp::data::items::Water,
                                                     libtp::data::items::Hot_Spring_Water_Shop,
                                                     libtp::data::items::Lantern_Refill_Shop,
                                                     libtp::data::items::Jovani_Bottle,
                                                     libtp::data::items::Renardos_Letter,
                                                     libtp::data::items::Invoice,
                                                     libtp::data::items::Ilias_Charm,
                                                     libtp::data::items::Horse_Call,
                                                     libtp::data::items::Forest_Temple_Small_Key,
                                                     libtp::data::items::Goron_Mines_Small_Key,
                                                     libtp::data::items::Lakebed_Temple_Small_Key,
                                                     libtp::data::items::Arbiters_Grounds_Small_Key,
                                                     libtp::data::items::Snowpeak_Ruins_Small_Key,
                                                     libtp::data::items::Temple_of_Time_Small_Key,
                                                     libtp::data::items::City_in_The_Sky_Small_Key,
                                                     libtp::data::items::Palace_of_Twilight_Small_Key,
                                                     libtp::data::items::Hyrule_Castle_Small_Key,
                                                     libtp::data::items::Bulblin_Camp_Key,
                                                     libtp::data::items::Foolish_Item,
                                                     libtp::data::items::Aurus_Memo,
                                                     libtp::data::items::Asheis_Sketch,
                                                     libtp::data::items::Forest_Temple_Big_Key,
                                                     libtp::data::items::Lakebed_Temple_Big_Key,
                                                     libtp::data::items::Arbiters_Grounds_Big_Key,
                                                     libtp::data::items::Temple_of_Time_Big_Key,
                                                     libtp::data::items::City_in_The_Sky_Big_Key,
                                                     libtp::data::items::Palace_of_Twilight_Big_Key,
                                                     libtp::data::items::Hyrule_Castle_Big_Key,
                                                     libtp::data::items::Forest_Temple_Compass,
                                                     libtp::data::items::Goron_Mines_Compass,
                                                     libtp::data::items::Lakebed_Temple_Compass,
                                                     libtp::data::items::Coro_Bottle,
                                                     libtp::data::items::Bee_Larva_Shop,
                                                     libtp::data::items::Vessel_Of_Light_Faron,
                                                     libtp::data::items::Vessel_Of_Light_Eldin,
                                                     libtp::data::items::Vessel_Of_Light_Lanayru,
                                                     libtp::data::items::Arbiters_Grounds_Compass,
                                                     libtp::data::items::Snowpeak_Ruins_Compass,
                                                     libtp::data::items::Temple_of_Time_Compass,
                                                     libtp::data::items::City_in_The_Sky_Compass,
                                                     libtp::data::items::Palace_of_Twilight_Compass,
                                                     libtp::data::items::Hyrule_Castle_Compass,
                                                     libtp::data::items::Forest_Temple_Dungeon_Map,
                                                     libtp::data::items::Goron_Mines_Dungeon_Map,
                                                     libtp::data::items::Lakebed_Temple_Dungeon_Map,
                                                     libtp::data::items::Arbiters_Grounds_Dungeon_Map,
                                                     libtp::data::items::Snowpeak_Ruins_Dungeon_Map,
                                                     libtp::data::items::Temple_of_Time_Dungeon_Map,
                                                     libtp::data::items::City_in_The_Sky_Dungeon_Map,
                                                     libtp::data::items::Palace_of_Twilight_Dungeon_Map,
                                                     libtp::data::items::Hyrule_Castle_Dungeon_Map,
                                                     libtp::data::items::Male_Beetle,
                                                     libtp::data::items::Female_Beetle,
                                                     libtp::data::items::Male_Butterfly,
                                                     libtp::data::items::Female_Butterfly,
                                                     libtp::data::items::Male_Stag_Beetle,
                                                     libtp::data::items::Female_Stag_Beetle,
                                                     libtp::data::items::Male_Grasshopper,
                                                     libtp::data::items::Female_Grasshopper,
                                                     libtp::data::items::Male_Phasmid,
                                                     libtp::data::items::Female_Phasmid,
                                                     libtp::data::items::Male_Pill_Bug,
                                                     libtp::data::items::Female_Pill_Bug,
                                                     libtp::data::items::Male_Mantis,
                                                     libtp::data::items::Female_Mantis,
                                                     libtp::data::items::Male_Ladybug,
                                                     libtp::data::items::Female_Ladybug,
                                                     libtp::data::items::Male_Snail,
                                                     libtp::data::items::Female_Snail,
                                                     libtp::data::items::Male_Dragonfly,
                                                     libtp::data::items::Female_Dragonfly,
                                                     libtp::data::items::Male_Ant,
                                                     libtp::data::items::Female_Ant,
                                                     libtp::data::items::Male_Dayfly,
                                                     libtp::data::items::Female_Dayfly,
                                                     libtp::data::items::Poe_Soul,
                                                     libtp::data::items::Ending_Blow,
                                                     libtp::data::items::Shield_Attack,
                                                     libtp::data::items::Back_Slice,
                                                     libtp::data::items::Helm_Splitter,
                                                     libtp::data::items::Mortal_Draw,
                                                     libtp::data::items::Jump_Strike,
                                                     libtp::data::items::Great_Spin,
                                                     libtp::data::items::Ancient_Sky_Book_Empty,
                                                     libtp::data::items::Ancient_Sky_Book_First_Character,
                                                     libtp::data::items::Ancient_Sky_Book_Second_Character,
                                                     libtp::data::items::Ancient_Sky_Book_Third_Character,
                                                     libtp::data::items::Ancient_Sky_Book_Fourth_Character,
                                                     libtp::data::items::Ancient_Sky_Book_Fifth_Character,
                                                     libtp::data::items::Ancient_Sky_Book_Completed,
                                                     libtp::data::items::Purple_Rupee_Links_House,
                                                     libtp::data::items::Small_Key_N_Faron_Gate,
                                                     libtp::data::items::Gate_Keys,
                                                     libtp::data::items::Ordon_Pumpkin,
                                                     libtp::data::items::Ordon_Goat_Cheese,
                                                     libtp::data::items::Bed_Key,
                                                     libtp::data::items::Key_Shard_1,
                                                     libtp::data::items::Key_Shard_2,
                                                     libtp::data::items::Key_Shard_3,
                                                     libtp::data::items::Big_Key_Goron_Mines,
                                                     libtp::data::items::Coro_Key,
                                                     libtp::data::items::Mirror_Piece_2,
                                                     libtp::data::items::Mirror_Piece_3,
                                                     libtp::data::items::Mirror_Piece_4,
                                                     libtp::data::items::Fused_Shadow_1,
                                                     libtp::data::items::Fused_Shadow_2,
                                                     libtp::data::items::Fused_Shadow_3 };

    void modifyItemModels()
    {
        using namespace libtp::data;
        using namespace libtp::tp;
        d_item_data::ItemInfo* itemInfoPtr = &d_item_data::item_info[0];
        d_item_data::FieldItemRes* fieldItemResPtr = &d_item_data::field_item_res[0];
        d_item_data::ItemResource* itemResourcePtr = &d_item_data::item_resource[0];
        uint8_t* getSeTypePtr = &libtp::tp::d_a_alink::getSeType[0];
        d_item_data::ItemInfo* yellowRupeeInfoPtr = &d_item_data::item_info[items::Yellow_Rupee];

        int16_t bombBagIcon = itemResourcePtr[items::Bomb_Bag_Regular_Bombs].ringTexResIdx;

        memcpy( &itemResourcePtr[items::Bomb_Bag_Regular_Bombs],
                &itemResourcePtr[items::Goron_Bomb_Bag],
                sizeof( d_item_data::ItemResource ) );

        itemResourcePtr[items::Bomb_Bag_Regular_Bombs].ringTexResIdx = bombBagIcon;

        // First we copy over the Ordon Sword data to the Master/Light Sword as a base and then modify the model appropriately
        memcpy( &itemResourcePtr[items::Master_Sword],
                &itemResourcePtr[items::Ordon_Sword],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Master_Sword_Light],
                &itemResourcePtr[items::Ordon_Sword],
                sizeof( d_item_data::ItemResource ) );
        itemResourcePtr[items::Master_Sword].arcName = _02_masterSwordArc;
        itemResourcePtr[items::Master_Sword_Light].arcName = _02_masterSwordArc;
        itemResourcePtr[items::Master_Sword].modelResIdx = 0x5;
        itemResourcePtr[items::Master_Sword_Light].modelResIdx = 0x5;

        memcpy( &itemResourcePtr[items::Horse_Call],
                &itemResourcePtr[items::Ilias_Charm],
                sizeof( d_item_data::ItemResource ) );

        uint32_t loopCount = sizeof( itemsWithNoFieldModel ) / sizeof( itemsWithNoFieldModel[0] );
        for ( uint32_t i = 0; i < loopCount; i++ )
        {
            uint32_t item = itemsWithNoFieldModel[i];
            // Set the shadow size to 0xFF for items that don't cast a proper shadow.
            switch ( item )
            {
                case items::Ordon_Shield:
                case items::Boomerang:
                {
                    itemInfoPtr[item].mShadowSize = 0xFF;
                    break;
                }
                default:
                {
                    break;
                }
            }

            itemInfoPtr[item].mCollisionH = yellowRupeeInfoPtr->mCollisionH;
            itemInfoPtr[item].mCollisionR = yellowRupeeInfoPtr->mCollisionR;
            // Set the item's field model to use the getItem model.
            fieldItemResPtr[item].arcName = itemResourcePtr[item].arcName;
            fieldItemResPtr[item].modelResIdx = itemResourcePtr[item].modelResIdx;
        }

        itemResourcePtr[items::Master_Sword].ringTexResIdx = 0x0042;
        itemResourcePtr[items::Shadow_Crystal].ringTexResIdx = 0x002E;
        itemResourcePtr[items::Master_Sword_Light].ringTexResIdx = 0x0042;

        getSeTypePtr[items::Master_Sword] = getSeTypePtr[items::Clawshot];
        getSeTypePtr[items::Master_Sword_Light] = getSeTypePtr[items::Clawshot];
        getSeTypePtr[items::Shadow_Crystal] = getSeTypePtr[items::Clawshot];
        getSeTypePtr[items::Bomb_Bag_Regular_Bombs] = getSeTypePtr[items::Goron_Bomb_Bag];
        getSeTypePtr[items::Horse_Call] = getSeTypePtr[items::Clawshot];
    }

    void setCustomItemResourceData()
    {
        using namespace libtp::data;
        using namespace libtp::tp;
        d_item_data::ItemInfo* itemInfoPtr = &d_item_data::item_info[0];
        d_item_data::ItemResource* itemResourcePtr = &d_item_data::item_resource[0];
        d_item_data::ItemResource* smallKeyItemResourcePtr = &itemResourcePtr[items::Small_Key];
        d_item_data::ItemResource* bigKeyItemResourcePtr = &itemResourcePtr[items::Big_Key];
        d_item_data::ItemResource* dungeonMapItemResourcePtr = &itemResourcePtr[items::Dungeon_Map];
        d_item_data::ItemResource* compassItemResourcePtr = &itemResourcePtr[items::Compass];
        d_item_data::ItemResource* skybookItemResourcePtr = &itemResourcePtr[items::Ancient_Sky_Book_Empty];
        uint8_t* getSeTypePtr = &libtp::tp::d_a_alink::getSeType[0];

        uint8_t listLength = 0;
        uint8_t smallKeySeType = getSeTypePtr[items::Small_Key];
        uint8_t bigKeySeType = getSeTypePtr[items::Big_Key];
        uint8_t dungeonMapSeType = getSeTypePtr[items::Dungeon_Map];
        uint8_t compassSeType = getSeTypePtr[items::Compass];
        uint8_t skyBookSeType = getSeTypePtr[items::Ancient_Sky_Book_Empty];

        uint8_t customSmallKeyItemIDs[] = { items::Forest_Temple_Small_Key,
                                            items::Goron_Mines_Small_Key,
                                            items::Lakebed_Temple_Small_Key,
                                            items::Arbiters_Grounds_Small_Key,
                                            items::Snowpeak_Ruins_Small_Key,
                                            items::Temple_of_Time_Small_Key,
                                            items::City_in_The_Sky_Small_Key,
                                            items::Palace_of_Twilight_Small_Key,
                                            items::Hyrule_Castle_Small_Key,
                                            items::Bulblin_Camp_Key };

        uint8_t customBigKeyItemIDs[] = { items::Forest_Temple_Big_Key,
                                          items::Lakebed_Temple_Big_Key,
                                          items::Arbiters_Grounds_Big_Key,
                                          items::Temple_of_Time_Big_Key,
                                          items::City_in_The_Sky_Big_Key,
                                          items::Palace_of_Twilight_Big_Key,
                                          items::Hyrule_Castle_Big_Key };

        uint8_t customDungeonMapItemIDs[] = { items::Forest_Temple_Dungeon_Map,
                                              items::Goron_Mines_Dungeon_Map,
                                              items::Lakebed_Temple_Dungeon_Map,
                                              items::Arbiters_Grounds_Dungeon_Map,
                                              items::Snowpeak_Ruins_Dungeon_Map,
                                              items::Temple_of_Time_Dungeon_Map,
                                              items::City_in_The_Sky_Dungeon_Map,
                                              items::Palace_of_Twilight_Dungeon_Map,
                                              items::Hyrule_Castle_Dungeon_Map };

        uint8_t customCompassItemIDs[] = { items::Forest_Temple_Compass,
                                           items::Goron_Mines_Compass,
                                           items::Lakebed_Temple_Compass,
                                           items::Arbiters_Grounds_Compass,
                                           items::Snowpeak_Ruins_Compass,
                                           items::Temple_of_Time_Compass,
                                           items::City_in_The_Sky_Compass,
                                           items::Palace_of_Twilight_Compass,
                                           items::Hyrule_Castle_Compass };

        uint8_t customHiddenSkillItemIDs[] = { items::Ending_Blow,
                                               items::Shield_Attack,
                                               items::Back_Slice,
                                               items::Helm_Splitter,
                                               items::Mortal_Draw,
                                               items::Jump_Strike,
                                               items::Great_Spin };

        uint8_t customSkyCharacterItemIDs[] = { items::Ancient_Sky_Book_First_Character,
                                                items::Ancient_Sky_Book_Second_Character,
                                                items::Ancient_Sky_Book_Third_Character,
                                                items::Ancient_Sky_Book_Fourth_Character,
                                                items::Ancient_Sky_Book_Fifth_Character };

        uint8_t customShardsIDs[] = {
            items::Mirror_Piece_2,
            items::Mirror_Piece_3,
            items::Mirror_Piece_4,
        };

        uint8_t customShadowsIDs[] = {
            items::Fused_Shadow_1,
            items::Fused_Shadow_2,
            items::Fused_Shadow_3,
        };

        // Set the item info for the custom small keys to that of the current Small Key
        listLength = ( sizeof( customSmallKeyItemIDs ) / sizeof( customSmallKeyItemIDs[0] ) );
        uint32_t smallKeyItemInfo =
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Small_Key] ) );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customSmallKeyItemIDs[i]] ) ) =
                smallKeyItemInfo;
            getSeTypePtr[customSmallKeyItemIDs[i]] = smallKeySeType;
            memcpy( &itemResourcePtr[customSmallKeyItemIDs[i]], smallKeyItemResourcePtr, sizeof( d_item_data::ItemResource ) );
        }

        // Set the item info for the custom big keys to that of the current Big Key
        listLength = ( sizeof( customBigKeyItemIDs ) / sizeof( customBigKeyItemIDs[0] ) );
        uint32_t bigKeyItemInfo = *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Big_Key] ) );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customBigKeyItemIDs[i]] ) ) = bigKeyItemInfo;
            getSeTypePtr[customBigKeyItemIDs[i]] = bigKeySeType;
            memcpy( &itemResourcePtr[customBigKeyItemIDs[i]], bigKeyItemResourcePtr, sizeof( d_item_data::ItemResource ) );
        }

        // Set the item info for the custom dungeon map to that of the current Dungeon Map
        listLength = ( sizeof( customDungeonMapItemIDs ) / sizeof( customDungeonMapItemIDs[0] ) );
        uint32_t dungeonMapItemInfo =
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Dungeon_Map] ) );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customDungeonMapItemIDs[i]] ) ) =
                dungeonMapItemInfo;
            getSeTypePtr[customDungeonMapItemIDs[i]] = dungeonMapSeType;
            memcpy( &itemResourcePtr[customDungeonMapItemIDs[i]],
                    dungeonMapItemResourcePtr,
                    sizeof( d_item_data::ItemResource ) );
        }

        // Set the item info for the custom compass to that of the current compass
        listLength = ( sizeof( customCompassItemIDs ) / sizeof( customCompassItemIDs[0] ) );
        uint32_t compassItemInfo = *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Compass] ) );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customCompassItemIDs[i]] ) ) =
                compassItemInfo;
            getSeTypePtr[customCompassItemIDs[i]] = compassSeType;
            memcpy( &itemResourcePtr[customCompassItemIDs[i]], compassItemResourcePtr, sizeof( d_item_data::ItemResource ) );
        }

        // Set the item info for the custom skybook characters to that of the current Sky Book
        listLength = ( sizeof( customSkyCharacterItemIDs ) / sizeof( customSkyCharacterItemIDs[0] ) );
        uint32_t skybookItemInfo =
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[items::Ancient_Sky_Book_Empty] ) );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( &itemInfoPtr[customSkyCharacterItemIDs[i]] ) ) =
                skybookItemInfo;
            getSeTypePtr[customSkyCharacterItemIDs[i]] = skyBookSeType;
            memcpy( &itemResourcePtr[customSkyCharacterItemIDs[i]],
                    skybookItemResourcePtr,
                    sizeof( d_item_data::ItemResource ) );
        }

        // Set the item info for the custom hidden skill items
        listLength = sizeof( customHiddenSkillItemIDs ) / sizeof( customHiddenSkillItemIDs[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            itemResourcePtr[customHiddenSkillItemIDs[i]].arcName = _02_hiddenSkillArc;
            itemResourcePtr[customHiddenSkillItemIDs[i]].ringTexResIdx = 0x003D;
            itemResourcePtr[customHiddenSkillItemIDs[i]].modelResIdx = 0x0003;
            itemResourcePtr[customHiddenSkillItemIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customHiddenSkillItemIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customHiddenSkillItemIDs[i]] = 0x2;
        }

        listLength = sizeof( customShardsIDs ) / sizeof( customShardsIDs[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            itemResourcePtr[customShardsIDs[i]].arcName = _02_mirrorShardArc;
            itemResourcePtr[customShardsIDs[i]].modelResIdx = 0x0009;
            itemResourcePtr[customShardsIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customShardsIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customShardsIDs[i]] = 0x2;
        }

        listLength = sizeof( customShadowsIDs ) / sizeof( customShadowsIDs[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            itemResourcePtr[customShadowsIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customShadowsIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customShadowsIDs[i]] = 0x2;
        }

        itemResourcePtr[libtp::data::items::Fused_Shadow_1].arcName = _02_firstShadowArc;
        itemResourcePtr[libtp::data::items::Fused_Shadow_2].arcName = _02_secondShadowArc;
        itemResourcePtr[libtp::data::items::Fused_Shadow_3].arcName = _02_thirdShadowArc;
    }

    void setCustomItemFunctions()
    {
        using namespace libtp::data;
        using namespace libtp::tp;
        d_item::ItemFunc* itemFuncPtr = &d_item::item_func_ptr[0];
        d_item::ItemGetCheckFunc* itemGetCheckFuncPtr = &d_item::item_getcheck_func_ptr[0];

        // Forest Temple
        itemFuncPtr[items::Forest_Temple_Small_Key] = _02_forestSmallKeyItemFunc;
        itemFuncPtr[items::Forest_Temple_Dungeon_Map] = _02_forestMapItemFunc;
        itemFuncPtr[items::Forest_Temple_Compass] = _02_forestCompassItemFunc;
        itemFuncPtr[items::Forest_Temple_Big_Key] = _02_forestBigKeyItemFunc;

        // Goron Mines
        itemFuncPtr[items::Goron_Mines_Small_Key] = _02_minesSmallKeyItemFunc;
        itemFuncPtr[items::Goron_Mines_Dungeon_Map] = _02_minesMapItemFunc;
        itemFuncPtr[items::Goron_Mines_Compass] = _02_minesCompassItemFunc;
        itemFuncPtr[items::Big_Key_Goron_Mines] = _02_minesBigKeyItemFunc;

        // Lakebed Temple
        itemFuncPtr[items::Lakebed_Temple_Small_Key] = _02_lakebedSmallKeyItemFunc;
        itemFuncPtr[items::Lakebed_Temple_Dungeon_Map] = _02_lakebedMapItemFunc;
        itemFuncPtr[items::Lakebed_Temple_Compass] = _02_lakebedCompassItemFunc;
        itemFuncPtr[items::Lakebed_Temple_Big_Key] = _02_lakebedBigKeyItemFunc;

        // Arbiters Grounds
        itemFuncPtr[items::Arbiters_Grounds_Small_Key] = _02_arbitersSmallKeyItemFunc;
        itemFuncPtr[items::Arbiters_Grounds_Dungeon_Map] = _02_arbitersMapItemFunc;
        itemFuncPtr[items::Arbiters_Grounds_Compass] = _02_arbitersCompassItemFunc;
        itemFuncPtr[items::Arbiters_Grounds_Big_Key] = _02_arbitersBigKeyItemFunc;

        // Snowpeak Ruins
        itemFuncPtr[items::Snowpeak_Ruins_Small_Key] = _02_snowpeakSmallKeyItemFunc;
        itemFuncPtr[items::Snowpeak_Ruins_Dungeon_Map] = _02_snowpeakMapItemFunc;
        itemFuncPtr[items::Snowpeak_Ruins_Compass] = _02_snowpeakCompassItemFunc;
        itemFuncPtr[items::Bed_Key] = _02_snowpeakBigKeyItemFunc;

        // Temple of Time
        itemFuncPtr[items::Temple_of_Time_Small_Key] = _02_totSmallKeyItemFunc;
        itemFuncPtr[items::Temple_of_Time_Dungeon_Map] = _02_totMapItemFunc;
        itemFuncPtr[items::Temple_of_Time_Compass] = _02_totCompassItemFunc;
        itemFuncPtr[items::Temple_of_Time_Big_Key] = _02_totBigKeyItemFunc;

        // City in the Sky
        itemFuncPtr[items::City_in_The_Sky_Small_Key] = _02_citySmallKeyItemFunc;
        itemFuncPtr[items::City_in_The_Sky_Dungeon_Map] = _02_cityMapItemFunc;
        itemFuncPtr[items::City_in_The_Sky_Compass] = _02_cityCompassItemFunc;
        itemFuncPtr[items::City_in_The_Sky_Big_Key] = _02_cityBigKeyItemFunc;

        // Palace of Twilight
        itemFuncPtr[items::Palace_of_Twilight_Small_Key] = _02_palaceSmallKeyItemFunc;
        itemFuncPtr[items::Palace_of_Twilight_Dungeon_Map] = _02_palaceMapItemFunc;
        itemFuncPtr[items::Palace_of_Twilight_Compass] = _02_palaceCompassItemFunc;
        itemFuncPtr[items::Palace_of_Twilight_Big_Key] = _02_palaceBigKeyItemFunc;

        // Hyrule Castle
        itemFuncPtr[items::Hyrule_Castle_Small_Key] = _02_hyruleSmallKeyItemFunc;
        itemFuncPtr[items::Hyrule_Castle_Dungeon_Map] = _02_hyruleMapItemFunc;
        itemFuncPtr[items::Hyrule_Castle_Compass] = _02_hyruleCompassItemFunc;
        itemFuncPtr[items::Hyrule_Castle_Big_Key] = _02_hyruleBigKeyItemFunc;

        // Fused Shadows/Mirror Shards
        itemFuncPtr[items::Fused_Shadow_1] = _02_firstFusedShadowItemFunc;
        itemFuncPtr[items::Fused_Shadow_2] = _02_secondFusedShadowItemFunc;
        itemFuncPtr[items::Fused_Shadow_3] = _02_thirdFusedShadowItemFunc;
        itemFuncPtr[items::Mirror_Piece_2] = _02_secondMirrorShardItemFunc;
        itemFuncPtr[items::Mirror_Piece_3] = _02_thirdMirrorShardItemFunc;
        itemFuncPtr[items::Mirror_Piece_4] = _02_fourthMirrorShardItemFunc;

        // Other Items
        itemFuncPtr[items::Bulblin_Camp_Key] = _02_campSmallKeyItemFunc;
        itemFuncPtr[items::Small_Key_N_Faron_Gate] = _02_faronSmallKeyItemFunc;
        itemFuncPtr[items::Shadow_Crystal] = _02_shadowCrystalItemFunc;
        itemFuncPtr[items::Dominion_Rod] = _02_poweredDominionRodItemFunc;
        itemFuncPtr[items::Aurus_Memo] = _02_auruMemoItemFunc;
        itemFuncPtr[items::Ordon_Pumpkin] = _02_ordonPumpkinItemFunc;
        itemFuncPtr[items::Ordon_Goat_Cheese] = _02_ordonGoatCheeseItemFunc;
        itemFuncPtr[items::Ancient_Sky_Book_Completed] = _02_filledSkybookItemFunc;
        itemFuncPtr[items::Big_Wallet] = _02_bigWalletItemFunc;
        itemFuncPtr[items::Giant_Wallet] = _02_giantWalletItemFunc;
        itemFuncPtr[items::Gate_Keys] = _02_gateKeysItemFunc;
        itemFuncPtr[items::Ending_Blow] = _02_endingBlowItemFunc;
        itemFuncPtr[items::Shield_Attack] = _02_shieldAttackItemFunc;
        itemFuncPtr[items::Back_Slice] = _02_backSliceItemFunc;
        itemFuncPtr[items::Helm_Splitter] = _02_helmSplitterItemFunc;
        itemFuncPtr[items::Mortal_Draw] = _02_mortalDrawItemFunc;
        itemFuncPtr[items::Jump_Strike] = _02_jumpStrikeItemFunc;
        itemFuncPtr[items::Great_Spin] = _02_greatSpinItemFunc;
        itemFuncPtr[items::Vessel_Of_Light_Lanayru] = _02_lanayruVesselItemFunc;
        itemFuncPtr[items::Foolish_Item] = _02_foolishItemFunc;

        // Some items need a valid getCheckFunc definition.
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_First_Character] = _02_firstSkybookItemGetCheck;
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Second_Character] = _02_secondSkybookItemGetCheck;
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Third_Character] = _02_thirdSkybookItemGetCheck;
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Fourth_Character] = _02_fourthSkybookItemGetCheck;
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Fifth_Character] = _02_fifthSkybookItemGetCheck;
        itemGetCheckFuncPtr[items::Big_Wallet] = _02_bigWalletItemGetCheck;
        itemGetCheckFuncPtr[items::Giant_Wallet] = _02_giantWalletItemGetCheck;
        itemGetCheckFuncPtr[items::Fused_Shadow_1] = _02_firstFusedShadowItemGetCheck;
        itemGetCheckFuncPtr[items::Fused_Shadow_2] = _02_secondFusedShadowItemGetCheck;
        itemGetCheckFuncPtr[items::Fused_Shadow_3] = _02_thirdFusedShadowItemGetCheck;
        itemGetCheckFuncPtr[items::Mirror_Piece_2] = _02_secondMirrorShardItemGetCheck;
        itemGetCheckFuncPtr[items::Mirror_Piece_3] = _02_thirdMirrorShardItemGetCheck;
        itemGetCheckFuncPtr[items::Mirror_Piece_4] = _02_fourthMirrorShardItemGetCheck;
        itemGetCheckFuncPtr[items::Shadow_Crystal] = _02_shadowCrystalItemGetCheck;
        itemGetCheckFuncPtr[items::Ending_Blow] = _02_endingBlowItemGetCheck;
        itemGetCheckFuncPtr[items::Shield_Attack] = _02_shieldAttackItemGetCheck;
        itemGetCheckFuncPtr[items::Back_Slice] = _02_backSliceItemGetCheck;
        itemGetCheckFuncPtr[items::Helm_Splitter] = _02_helmSplitterItemGetCheck;
        itemGetCheckFuncPtr[items::Mortal_Draw] = _02_mortalDrawItemGetCheck;
        itemGetCheckFuncPtr[items::Jump_Strike] = _02_jumpStrikeItemGetCheck;
        itemGetCheckFuncPtr[items::Bulblin_Camp_Key] = _02_campSmallKeyItemGetCheck;
    }

    void _02_modifyItemData()
    {
        setCustomItemResourceData();
        modifyItemModels();
        setCustomItemFunctions();
    }
}     // namespace mod::game_patch