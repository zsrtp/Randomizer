#include <cstdint>
#include <cstring>

#include "game_patch/game_patch.h"
#include "data/items.h"
#include "tp/d_item_data.h"
#include "tp/d_a_alink.h"
#include "tp/d_item.h"
#include "rando/customItems.h"

namespace mod::game_patch
{
    static const uint8_t itemsWithNoFieldModel[] = {libtp::data::items::Bombs_5,
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
                                                    rando::customItems::Forest_Temple_Small_Key,
                                                    rando::customItems::Goron_Mines_Small_Key,
                                                    rando::customItems::Lakebed_Temple_Small_Key,
                                                    rando::customItems::Arbiters_Grounds_Small_Key,
                                                    rando::customItems::Snowpeak_Ruins_Small_Key,
                                                    rando::customItems::Temple_of_Time_Small_Key,
                                                    rando::customItems::City_in_The_Sky_Small_Key,
                                                    rando::customItems::Palace_of_Twilight_Small_Key,
                                                    rando::customItems::Hyrule_Castle_Small_Key,
                                                    rando::customItems::Bulblin_Camp_Key,
                                                    rando::customItems::Foolish_Item_1,
                                                    rando::customItems::Foolish_Item_2,
                                                    rando::customItems::Foolish_Item_3,
                                                    rando::customItems::Foolish_Item_4,
                                                    rando::customItems::Foolish_Item_5,
                                                    rando::customItems::Foolish_Item_6,
                                                    libtp::data::items::Aurus_Memo,
                                                    libtp::data::items::Asheis_Sketch,
                                                    rando::customItems::Forest_Temple_Big_Key,
                                                    rando::customItems::Lakebed_Temple_Big_Key,
                                                    rando::customItems::Arbiters_Grounds_Big_Key,
                                                    rando::customItems::Temple_of_Time_Big_Key,
                                                    rando::customItems::City_in_The_Sky_Big_Key,
                                                    rando::customItems::Palace_of_Twilight_Big_Key,
                                                    rando::customItems::Hyrule_Castle_Big_Key,
                                                    rando::customItems::Forest_Temple_Compass,
                                                    rando::customItems::Goron_Mines_Compass,
                                                    rando::customItems::Lakebed_Temple_Compass,
                                                    libtp::data::items::Coro_Bottle,
                                                    libtp::data::items::Bee_Larva_Shop,
                                                    libtp::data::items::Vessel_Of_Light_Faron,
                                                    libtp::data::items::Vessel_Of_Light_Eldin,
                                                    libtp::data::items::Vessel_Of_Light_Lanayru,
                                                    rando::customItems::Arbiters_Grounds_Compass,
                                                    rando::customItems::Snowpeak_Ruins_Compass,
                                                    rando::customItems::Temple_of_Time_Compass,
                                                    rando::customItems::City_in_The_Sky_Compass,
                                                    rando::customItems::Palace_of_Twilight_Compass,
                                                    rando::customItems::Hyrule_Castle_Compass,
                                                    rando::customItems::Forest_Temple_Dungeon_Map,
                                                    rando::customItems::Goron_Mines_Dungeon_Map,
                                                    rando::customItems::Lakebed_Temple_Dungeon_Map,
                                                    rando::customItems::Arbiters_Grounds_Dungeon_Map,
                                                    rando::customItems::Snowpeak_Ruins_Dungeon_Map,
                                                    rando::customItems::Temple_of_Time_Dungeon_Map,
                                                    rando::customItems::City_in_The_Sky_Dungeon_Map,
                                                    rando::customItems::Palace_of_Twilight_Dungeon_Map,
                                                    rando::customItems::Hyrule_Castle_Dungeon_Map,
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
                                                    rando::customItems::Ending_Blow,
                                                    rando::customItems::Shield_Attack,
                                                    rando::customItems::Back_Slice,
                                                    rando::customItems::Helm_Splitter,
                                                    rando::customItems::Mortal_Draw,
                                                    rando::customItems::Jump_Strike,
                                                    rando::customItems::Great_Spin,
                                                    libtp::data::items::Ancient_Sky_Book_Empty,
                                                    rando::customItems::Ancient_Sky_Book_First_Character,
                                                    rando::customItems::Ancient_Sky_Book_Second_Character,
                                                    rando::customItems::Ancient_Sky_Book_Third_Character,
                                                    rando::customItems::Ancient_Sky_Book_Fourth_Character,
                                                    rando::customItems::Ancient_Sky_Book_Fifth_Character,
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
                                                    rando::customItems::Fused_Shadow_1,
                                                    rando::customItems::Fused_Shadow_2,
                                                    rando::customItems::Fused_Shadow_3};

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

        memcpy(&itemResourcePtr[items::Bomb_Bag_Regular_Bombs],
               &itemResourcePtr[items::Goron_Bomb_Bag],
               sizeof(d_item_data::ItemResource));

        itemResourcePtr[items::Bomb_Bag_Regular_Bombs].ringTexResIdx = bombBagIcon;

        // First we copy over the Ordon Sword data to the Master/Light Sword as a base and then modify the model appropriately
        memcpy(&itemResourcePtr[items::Master_Sword], &itemResourcePtr[items::Ordon_Sword], sizeof(d_item_data::ItemResource));
        memcpy(&itemResourcePtr[items::Master_Sword_Light],
               &itemResourcePtr[items::Ordon_Sword],
               sizeof(d_item_data::ItemResource));
        itemResourcePtr[items::Master_Sword].arcName = _02_masterSwordArc;
        itemResourcePtr[items::Master_Sword_Light].arcName = _02_masterSwordArc;
        itemResourcePtr[items::Master_Sword].modelResIdx = 0x5;
        itemResourcePtr[items::Master_Sword_Light].modelResIdx = 0x5;

        memcpy(&itemResourcePtr[items::Horse_Call], &itemResourcePtr[items::Ilias_Charm], sizeof(d_item_data::ItemResource));

        memcpy(&itemResourcePtr[items::Purple_Rupee_Links_House],
               &itemResourcePtr[items::Purple_Rupee],
               sizeof(d_item_data::ItemResource));

        uint32_t loopCount = sizeof(itemsWithNoFieldModel) / sizeof(itemsWithNoFieldModel[0]);
        for (uint32_t i = 0; i < loopCount; i++)
        {
            uint32_t item = itemsWithNoFieldModel[i];
            // Set the shadow size to 0xFF for items that don't cast a proper shadow.
            switch (item)
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

        // Change the itemGet fanfare for custom items.
        getSeTypePtr[items::Wooden_Sword] = getSeTypePtr[items::Clawshot];
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
        using namespace rando;
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

        uint8_t customSmallKeyItemIDs[] = {customItems::Forest_Temple_Small_Key,
                                           customItems::Goron_Mines_Small_Key,
                                           customItems::Lakebed_Temple_Small_Key,
                                           customItems::Arbiters_Grounds_Small_Key,
                                           customItems::Snowpeak_Ruins_Small_Key,
                                           customItems::Temple_of_Time_Small_Key,
                                           customItems::City_in_The_Sky_Small_Key,
                                           customItems::Palace_of_Twilight_Small_Key,
                                           customItems::Hyrule_Castle_Small_Key,
                                           customItems::Bulblin_Camp_Key};

        uint8_t customBigKeyItemIDs[] = {customItems::Forest_Temple_Big_Key,
                                         customItems::Lakebed_Temple_Big_Key,
                                         customItems::Arbiters_Grounds_Big_Key,
                                         customItems::Temple_of_Time_Big_Key,
                                         customItems::City_in_The_Sky_Big_Key,
                                         customItems::Palace_of_Twilight_Big_Key,
                                         customItems::Hyrule_Castle_Big_Key};

        uint8_t customDungeonMapItemIDs[] = {customItems::Forest_Temple_Dungeon_Map,
                                             customItems::Goron_Mines_Dungeon_Map,
                                             customItems::Lakebed_Temple_Dungeon_Map,
                                             customItems::Arbiters_Grounds_Dungeon_Map,
                                             customItems::Snowpeak_Ruins_Dungeon_Map,
                                             customItems::Temple_of_Time_Dungeon_Map,
                                             customItems::City_in_The_Sky_Dungeon_Map,
                                             customItems::Palace_of_Twilight_Dungeon_Map,
                                             customItems::Hyrule_Castle_Dungeon_Map};

        uint8_t customCompassItemIDs[] = {customItems::Forest_Temple_Compass,
                                          customItems::Goron_Mines_Compass,
                                          customItems::Lakebed_Temple_Compass,
                                          customItems::Arbiters_Grounds_Compass,
                                          customItems::Snowpeak_Ruins_Compass,
                                          customItems::Temple_of_Time_Compass,
                                          customItems::City_in_The_Sky_Compass,
                                          customItems::Palace_of_Twilight_Compass,
                                          customItems::Hyrule_Castle_Compass};

        uint8_t customHiddenSkillItemIDs[] = {customItems::Ending_Blow,
                                              customItems::Shield_Attack,
                                              customItems::Back_Slice,
                                              customItems::Helm_Splitter,
                                              customItems::Mortal_Draw,
                                              customItems::Jump_Strike,
                                              customItems::Great_Spin};

        uint8_t customSkyCharacterItemIDs[] = {customItems::Ancient_Sky_Book_First_Character,
                                               customItems::Ancient_Sky_Book_Second_Character,
                                               customItems::Ancient_Sky_Book_Third_Character,
                                               customItems::Ancient_Sky_Book_Fourth_Character,
                                               customItems::Ancient_Sky_Book_Fifth_Character};

        uint8_t customShardsIDs[] = {
            items::Mirror_Piece_2,
            items::Mirror_Piece_3,
            items::Mirror_Piece_4,
        };

        uint8_t customShadowsIDs[] = {
            customItems::Fused_Shadow_1,
            customItems::Fused_Shadow_2,
            customItems::Fused_Shadow_3,
        };

        // Set the item info for the custom small keys to that of the current Small Key
        listLength = (sizeof(customSmallKeyItemIDs) / sizeof(customSmallKeyItemIDs[0]));
        uint32_t smallKeyItemInfo = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[items::Small_Key]));
        for (uint32_t i = 0; i < listLength; i++)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[customSmallKeyItemIDs[i]])) = smallKeyItemInfo;
            getSeTypePtr[customSmallKeyItemIDs[i]] = smallKeySeType;
            memcpy(&itemResourcePtr[customSmallKeyItemIDs[i]], smallKeyItemResourcePtr, sizeof(d_item_data::ItemResource));
        }

        // Set the item info for the custom big keys to that of the current Big Key
        listLength = (sizeof(customBigKeyItemIDs) / sizeof(customBigKeyItemIDs[0]));
        uint32_t bigKeyItemInfo = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[items::Big_Key]));
        for (uint32_t i = 0; i < listLength; i++)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[customBigKeyItemIDs[i]])) = bigKeyItemInfo;
            getSeTypePtr[customBigKeyItemIDs[i]] = bigKeySeType;
            memcpy(&itemResourcePtr[customBigKeyItemIDs[i]], bigKeyItemResourcePtr, sizeof(d_item_data::ItemResource));
        }

        // Set the item info for the custom dungeon map to that of the current Dungeon Map
        listLength = (sizeof(customDungeonMapItemIDs) / sizeof(customDungeonMapItemIDs[0]));
        uint32_t dungeonMapItemInfo =
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[items::Dungeon_Map]));
        for (uint32_t i = 0; i < listLength; i++)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[customDungeonMapItemIDs[i]])) =
                dungeonMapItemInfo;
            getSeTypePtr[customDungeonMapItemIDs[i]] = dungeonMapSeType;
            memcpy(&itemResourcePtr[customDungeonMapItemIDs[i]], dungeonMapItemResourcePtr, sizeof(d_item_data::ItemResource));
        }

        // Set the item info for the custom compass to that of the current compass
        listLength = (sizeof(customCompassItemIDs) / sizeof(customCompassItemIDs[0]));
        uint32_t compassItemInfo = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[items::Compass]));
        for (uint32_t i = 0; i < listLength; i++)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[customCompassItemIDs[i]])) = compassItemInfo;
            getSeTypePtr[customCompassItemIDs[i]] = compassSeType;
            memcpy(&itemResourcePtr[customCompassItemIDs[i]], compassItemResourcePtr, sizeof(d_item_data::ItemResource));
        }

        // Set the item info for the custom skybook characters to that of the current Sky Book
        listLength = (sizeof(customSkyCharacterItemIDs) / sizeof(customSkyCharacterItemIDs[0]));
        uint32_t skybookItemInfo =
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[items::Ancient_Sky_Book_Empty]));
        for (uint32_t i = 0; i < listLength; i++)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(&itemInfoPtr[customSkyCharacterItemIDs[i]])) =
                skybookItemInfo;
            getSeTypePtr[customSkyCharacterItemIDs[i]] = skyBookSeType;
            memcpy(&itemResourcePtr[customSkyCharacterItemIDs[i]], skybookItemResourcePtr, sizeof(d_item_data::ItemResource));
        }

        // Set the item info for the custom hidden skill items
        listLength = sizeof(customHiddenSkillItemIDs) / sizeof(customHiddenSkillItemIDs[0]);
        for (uint32_t i = 0; i < listLength; i++)
        {
            itemResourcePtr[customHiddenSkillItemIDs[i]].arcName = _02_hiddenSkillArc;
            itemResourcePtr[customHiddenSkillItemIDs[i]].ringTexResIdx = 0x003D;
            itemResourcePtr[customHiddenSkillItemIDs[i]].modelResIdx = 0x0003;
            itemResourcePtr[customHiddenSkillItemIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customHiddenSkillItemIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customHiddenSkillItemIDs[i]] = 0x2;
        }

        listLength = sizeof(customShardsIDs) / sizeof(customShardsIDs[0]);
        for (uint32_t i = 0; i < listLength; i++)
        {
            itemResourcePtr[customShardsIDs[i]].arcName = _02_mirrorShardArc;
            itemResourcePtr[customShardsIDs[i]].modelResIdx = 0x0009;
            itemResourcePtr[customShardsIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customShardsIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customShardsIDs[i]] = getSeTypePtr[items::Clawshot];
        }

        listLength = sizeof(customShadowsIDs) / sizeof(customShadowsIDs[0]);
        for (uint32_t i = 0; i < listLength; i++)
        {
            itemResourcePtr[customShadowsIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customShadowsIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customShadowsIDs[i]] = getSeTypePtr[items::Clawshot];
        }

        itemResourcePtr[customItems::Fused_Shadow_1].arcName = _02_firstShadowArc;
        itemResourcePtr[customItems::Fused_Shadow_2].arcName = _02_secondShadowArc;
        itemResourcePtr[customItems::Fused_Shadow_3].arcName = _02_thirdShadowArc;
    }

    void setCustomItemFunctions()
    {
        using namespace libtp::data;
        using namespace libtp::tp;
        using namespace rando;
        d_item::ItemFunc* itemFuncPtr = &d_item::item_func_ptr[0];
        d_item::ItemGetCheckFunc* itemGetCheckFuncPtr = &d_item::item_getcheck_func_ptr[0];

        // Forest Temple
        itemFuncPtr[customItems::Forest_Temple_Small_Key] = _02_forestSmallKeyItemFunc;
        itemFuncPtr[customItems::Forest_Temple_Dungeon_Map] = _02_forestMapItemFunc;
        itemFuncPtr[customItems::Forest_Temple_Compass] = _02_forestCompassItemFunc;
        itemFuncPtr[customItems::Forest_Temple_Big_Key] = _02_forestBigKeyItemFunc;

        // Goron Mines
        itemFuncPtr[customItems::Goron_Mines_Small_Key] = _02_minesSmallKeyItemFunc;
        itemFuncPtr[customItems::Goron_Mines_Dungeon_Map] = _02_minesMapItemFunc;
        itemFuncPtr[customItems::Goron_Mines_Compass] = _02_minesCompassItemFunc;
        itemFuncPtr[items::Big_Key_Goron_Mines] = _02_minesBigKeyItemFunc;

        // Lakebed Temple
        itemFuncPtr[customItems::Lakebed_Temple_Small_Key] = _02_lakebedSmallKeyItemFunc;
        itemFuncPtr[customItems::Lakebed_Temple_Dungeon_Map] = _02_lakebedMapItemFunc;
        itemFuncPtr[customItems::Lakebed_Temple_Compass] = _02_lakebedCompassItemFunc;
        itemFuncPtr[customItems::Lakebed_Temple_Big_Key] = _02_lakebedBigKeyItemFunc;

        // Arbiters Grounds
        itemFuncPtr[customItems::Arbiters_Grounds_Small_Key] = _02_arbitersSmallKeyItemFunc;
        itemFuncPtr[customItems::Arbiters_Grounds_Dungeon_Map] = _02_arbitersMapItemFunc;
        itemFuncPtr[customItems::Arbiters_Grounds_Compass] = _02_arbitersCompassItemFunc;
        itemFuncPtr[customItems::Arbiters_Grounds_Big_Key] = _02_arbitersBigKeyItemFunc;

        // Snowpeak Ruins
        itemFuncPtr[customItems::Snowpeak_Ruins_Small_Key] = _02_snowpeakSmallKeyItemFunc;
        itemFuncPtr[customItems::Snowpeak_Ruins_Dungeon_Map] = _02_snowpeakMapItemFunc;
        itemFuncPtr[customItems::Snowpeak_Ruins_Compass] = _02_snowpeakCompassItemFunc;
        itemFuncPtr[items::Bed_Key] = _02_snowpeakBigKeyItemFunc;

        // Temple of Time
        itemFuncPtr[customItems::Temple_of_Time_Small_Key] = _02_totSmallKeyItemFunc;
        itemFuncPtr[customItems::Temple_of_Time_Dungeon_Map] = _02_totMapItemFunc;
        itemFuncPtr[customItems::Temple_of_Time_Compass] = _02_totCompassItemFunc;
        itemFuncPtr[customItems::Temple_of_Time_Big_Key] = _02_totBigKeyItemFunc;

        // City in the Sky
        itemFuncPtr[customItems::City_in_The_Sky_Small_Key] = _02_citySmallKeyItemFunc;
        itemFuncPtr[customItems::City_in_The_Sky_Dungeon_Map] = _02_cityMapItemFunc;
        itemFuncPtr[customItems::City_in_The_Sky_Compass] = _02_cityCompassItemFunc;
        itemFuncPtr[customItems::City_in_The_Sky_Big_Key] = _02_cityBigKeyItemFunc;

        // Palace of Twilight
        itemFuncPtr[customItems::Palace_of_Twilight_Small_Key] = _02_palaceSmallKeyItemFunc;
        itemFuncPtr[customItems::Palace_of_Twilight_Dungeon_Map] = _02_palaceMapItemFunc;
        itemFuncPtr[customItems::Palace_of_Twilight_Compass] = _02_palaceCompassItemFunc;
        itemFuncPtr[customItems::Palace_of_Twilight_Big_Key] = _02_palaceBigKeyItemFunc;

        // Hyrule Castle
        itemFuncPtr[customItems::Hyrule_Castle_Small_Key] = _02_hyruleSmallKeyItemFunc;
        itemFuncPtr[customItems::Hyrule_Castle_Dungeon_Map] = _02_hyruleMapItemFunc;
        itemFuncPtr[customItems::Hyrule_Castle_Compass] = _02_hyruleCompassItemFunc;
        itemFuncPtr[customItems::Hyrule_Castle_Big_Key] = _02_hyruleBigKeyItemFunc;

        // Fused Shadows/Mirror Shards
        itemFuncPtr[customItems::Fused_Shadow_1] = _02_firstFusedShadowItemFunc;
        itemFuncPtr[customItems::Fused_Shadow_2] = _02_secondFusedShadowItemFunc;
        itemFuncPtr[customItems::Fused_Shadow_3] = _02_thirdFusedShadowItemFunc;
        itemFuncPtr[items::Mirror_Piece_2] = _02_secondMirrorShardItemFunc;
        itemFuncPtr[items::Mirror_Piece_3] = _02_thirdMirrorShardItemFunc;
        itemFuncPtr[items::Mirror_Piece_4] = _02_fourthMirrorShardItemFunc;

        // Other Items
        itemFuncPtr[customItems::Bulblin_Camp_Key] = _02_campSmallKeyItemFunc;
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
        itemFuncPtr[customItems::Ending_Blow] = _02_endingBlowItemFunc;
        itemFuncPtr[customItems::Shield_Attack] = _02_shieldAttackItemFunc;
        itemFuncPtr[customItems::Back_Slice] = _02_backSliceItemFunc;
        itemFuncPtr[customItems::Helm_Splitter] = _02_helmSplitterItemFunc;
        itemFuncPtr[customItems::Mortal_Draw] = _02_mortalDrawItemFunc;
        itemFuncPtr[customItems::Jump_Strike] = _02_jumpStrikeItemFunc;
        itemFuncPtr[customItems::Great_Spin] = _02_greatSpinItemFunc;
        itemFuncPtr[items::Vessel_Of_Light_Lanayru] = _02_lanayruVesselItemFunc;
        itemFuncPtr[customItems::Foolish_Item_1] = _02_foolishItemFunc;
        itemFuncPtr[customItems::Foolish_Item_2] = _02_foolishItemFunc;
        itemFuncPtr[customItems::Foolish_Item_3] = _02_foolishItemFunc;
        itemFuncPtr[customItems::Foolish_Item_4] = _02_foolishItemFunc;
        itemFuncPtr[customItems::Foolish_Item_5] = _02_foolishItemFunc;
        itemFuncPtr[customItems::Foolish_Item_6] = _02_foolishItemFunc;

        // Some items need a valid getCheckFunc definition.
        itemGetCheckFuncPtr[customItems::Ancient_Sky_Book_First_Character] = _02_firstSkybookItemGetCheck;
        itemGetCheckFuncPtr[customItems::Ancient_Sky_Book_Second_Character] = _02_secondSkybookItemGetCheck;
        itemGetCheckFuncPtr[customItems::Ancient_Sky_Book_Third_Character] = _02_thirdSkybookItemGetCheck;
        itemGetCheckFuncPtr[customItems::Ancient_Sky_Book_Fourth_Character] = _02_fourthSkybookItemGetCheck;
        itemGetCheckFuncPtr[customItems::Ancient_Sky_Book_Fifth_Character] = _02_fifthSkybookItemGetCheck;
        itemGetCheckFuncPtr[items::Big_Wallet] = _02_bigWalletItemGetCheck;
        itemGetCheckFuncPtr[items::Giant_Wallet] = _02_giantWalletItemGetCheck;
        itemGetCheckFuncPtr[customItems::Fused_Shadow_1] = _02_firstFusedShadowItemGetCheck;
        itemGetCheckFuncPtr[customItems::Fused_Shadow_2] = _02_secondFusedShadowItemGetCheck;
        itemGetCheckFuncPtr[customItems::Fused_Shadow_3] = _02_thirdFusedShadowItemGetCheck;
        itemGetCheckFuncPtr[items::Mirror_Piece_2] = _02_secondMirrorShardItemGetCheck;
        itemGetCheckFuncPtr[items::Mirror_Piece_3] = _02_thirdMirrorShardItemGetCheck;
        itemGetCheckFuncPtr[items::Mirror_Piece_4] = _02_fourthMirrorShardItemGetCheck;
        itemGetCheckFuncPtr[items::Shadow_Crystal] = _02_shadowCrystalItemGetCheck;
        itemGetCheckFuncPtr[customItems::Ending_Blow] = _02_endingBlowItemGetCheck;
        itemGetCheckFuncPtr[customItems::Shield_Attack] = _02_shieldAttackItemGetCheck;
        itemGetCheckFuncPtr[customItems::Back_Slice] = _02_backSliceItemGetCheck;
        itemGetCheckFuncPtr[customItems::Helm_Splitter] = _02_helmSplitterItemGetCheck;
        itemGetCheckFuncPtr[customItems::Mortal_Draw] = _02_mortalDrawItemGetCheck;
        itemGetCheckFuncPtr[customItems::Jump_Strike] = _02_jumpStrikeItemGetCheck;
        itemGetCheckFuncPtr[customItems::Bulblin_Camp_Key] = _02_campSmallKeyItemGetCheck;
        itemGetCheckFuncPtr[items::Gate_Keys] = _02_gateKeysItemGetCheck;
    }

    void _02_modifyItemData()
    {
        setCustomItemResourceData();
        modifyItemModels();
        setCustomItemFunctions();
    }
} // namespace mod::game_patch