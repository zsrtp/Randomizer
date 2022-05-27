#include <string.h>

#include <cstdint>
#include <cstdio>
#include <cinttypes>

#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"
#include "tp/d_meter2_info.h"
#include "tp/d_save.h"

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
                                                     libtp::data::items::Master_Sword,
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
                                                     libtp::data::items::Ordon_Shield,
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
                                                     libtp::data::items::Coro_Key };

    static const uint8_t foolishModelItemList[] = {
        libtp::data::items::Magic_Armor,
        libtp::data::items::Master_Sword,
        libtp::data::items::Ordon_Shield,
        libtp::data::items::Hylian_Shield,
        libtp::data::items::Shadow_Crystal,
        libtp::data::items::Coral_Earring,
        libtp::data::items::Hawkeye,
        libtp::data::items::Boomerang,
        libtp::data::items::Spinner,
        libtp::data::items::Ball_and_Chain,
        libtp::data::items::Heros_Bow,
        libtp::data::items::Clawshot,
        libtp::data::items::Iron_Boots,
        libtp::data::items::Dominion_Rod,
        libtp::data::items::Master_Sword_Light,
        libtp::data::items::Fishing_Rod,
        libtp::data::items::Slingshot,
        libtp::data::items::Dominion_Rod_Uncharged,
        libtp::data::items::Empty_Bomb_Bag,
        libtp::data::items::Ancient_Sky_Book_Empty,
    };

    void giveNodeDungeonItems( const libtp::data::stage::AreaNodesID nodeId,
                               const libtp::data::items::NodeDungeonItemType type )
    {
        using namespace libtp::data::items;
        libtp::tp::d_save::dSv_info_c* gameInfoPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        // If the key is for the current area, then update the local node
        int32_t stageIndex = libtp::tools::getStageIndex( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mStage );
        if ( stageIndex != -1 )
        {
            uint8_t* memoryFlags;
            if ( nodeId == static_cast<libtp::data::stage::AreaNodesID>( libtp::data::stage::regionID[stageIndex] ) )
            {
                memoryFlags = gameInfoPtr->memory.temp_flags.memoryFlags;
            }
            else     // Key is not for the current area, so update the appropriate node
            {
                memoryFlags = gameInfoPtr->save_file.area_flags[static_cast<uint32_t>( nodeId )].temp_flags.memoryFlags;
            }

            switch ( type )
            {
                case NodeDungeonItemType::Small_Key:
                {
                    // The vanilla code caps the key count at 100
                    uint8_t smallKeyCount = memoryFlags[0x1C];
                    if ( smallKeyCount < 100 )
                    {
                        memoryFlags[0x1C] = smallKeyCount + 1;
                    }
                    break;
                }
                case NodeDungeonItemType::Dungeon_Map:
                    memoryFlags[0x1D] |= 0x1;
                    break;
                case NodeDungeonItemType::Compass:
                    memoryFlags[0x1D] |= 0x2;
                    break;
                case NodeDungeonItemType::Big_Key:
                    memoryFlags[0x1D] |= 0x4;
                    break;
                default:
                    break;
            }
        }
    }

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

        memcpy( &itemResourcePtr[items::Master_Sword],
                &itemResourcePtr[items::Ordon_Sword],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Master_Sword_Light],
                &itemResourcePtr[items::Ordon_Sword],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Horse_Call],
                &itemResourcePtr[items::Ilias_Charm],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Purple_Rupee_Links_House],
                &itemResourcePtr[items::Purple_Rupee],
                sizeof( d_item_data::ItemResource ) );

        uint32_t loopCount = sizeof( itemsWithNoFieldModel ) / sizeof( itemsWithNoFieldModel[0] );
        for ( uint32_t i = 0; i < loopCount; i++ )
        {
            uint32_t item = itemsWithNoFieldModel[i];
            // Set the item's field model to use the getItem model.
            itemInfoPtr[item].mShadowSize = yellowRupeeInfoPtr->mShadowSize;
            itemInfoPtr[item].mCollisionH = yellowRupeeInfoPtr->mCollisionH;
            itemInfoPtr[item].mCollisionR = yellowRupeeInfoPtr->mCollisionR;
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
            itemResourcePtr[customHiddenSkillItemIDs[i]].arcName = "O_gD_memo";
            itemResourcePtr[customHiddenSkillItemIDs[i]].ringTexResIdx = 0x003D;
            itemResourcePtr[customHiddenSkillItemIDs[i]].modelResIdx = 0x0003;
            itemResourcePtr[customHiddenSkillItemIDs[i]].brkResIdx = 0xFFFF;
            itemResourcePtr[customHiddenSkillItemIDs[i]].tevFrm = 0x00;
            getSeTypePtr[customHiddenSkillItemIDs[i]] = 0x2;
        }
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

        // City in The Sky
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
        itemFuncPtr[items::Heart_Container] = _02_heartContainerItemFunc;
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

    void _02_modifyFoolishFieldModel()
    {
        // Set the field model of the Foolish Item ID to the model of a random important item.
        libtp::tp::d_item_data::FieldItemRes* fieldItemResPtr = &libtp::tp::d_item_data::field_item_res[0];
        uint32_t modelListSize = sizeof( foolishModelItemList ) / sizeof( foolishModelItemList[0] );
        uint32_t randomIndex = mod::ulRand( modelListSize );
        uint32_t fieldModelItemID = _04_verifyProgressiveItem( randomizer, foolishModelItemList[randomIndex] );
        memcpy( &fieldItemResPtr[libtp::data::items::Foolish_Item],
                &fieldItemResPtr[fieldModelItemID],
                sizeof( libtp::tp::d_item_data::FieldItemRes ) );
    }
    void _02_modifyFoolishShopModel( uint16_t shopID )
    {
        // Set the shop model of the Foolish Item ID to the model of a random important item.
        using namespace libtp::tp::d_a_shop_item_static;
        libtp::tp::d_item_data::ItemResource* itemResourcePtr = &libtp::tp::d_item_data::item_resource[0];
        uint32_t modelListSize = sizeof( foolishModelItemList ) / sizeof( foolishModelItemList[0] );
        uint32_t randomIndex = mod::ulRand( modelListSize );
        uint32_t shopModelItemID = _04_verifyProgressiveItem( randomizer, foolishModelItemList[randomIndex] );
        shopItemData[shopID].arcName = itemResourcePtr[shopModelItemID].arcName;
        shopItemData[shopID].modelResIdx = itemResourcePtr[shopModelItemID].modelResIdx;
        shopItemData[shopID].wBckResIdx = itemResourcePtr[shopModelItemID].bckResIdx;
        shopItemData[shopID].wBrkResIdx = itemResourcePtr[shopModelItemID].brkResIdx;
        shopItemData[shopID].wBtpResIdx = itemResourcePtr[shopModelItemID].btpResIdx;
        shopItemData[shopID].tevFrm = itemResourcePtr[shopModelItemID].tevFrm;
    }

    void _02_forestSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_forestMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_forestCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_forestBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_minesSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_minesMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_minesCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_minesBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
        libtp::tp::d_item::execItemGet( libtp::data::items::Key_Shard_3 );
    }

    void _02_lakebedSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_lakebedMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_lakebedCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_lakebedBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_arbitersSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_arbitersMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_arbitersCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_arbitersBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_snowpeakSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_snowpeakMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_snowpeakCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_snowpeakBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_totSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_totMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_totCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_totBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_citySmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_cityMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_cityCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_cityBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_palaceSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_palaceMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_palaceCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_palaceBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_hyruleSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_hyruleMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map );
    }

    void _02_hyruleCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Compass );
    }

    void _02_hyruleBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Big_Key );
    }

    void _02_campSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Gerudo_Desert;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_faronSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Faron;
        giveNodeDungeonItems( nodeId, libtp::data::items::NodeDungeonItemType::Small_Key );
    }

    void _02_shadowCrystalItemFunc()
    {
        events::setSaveFileEventFlag( 0xD04 );     // Can transform at will
    }

    void _02_poweredDominionRodItemFunc() { events::setSaveFileEventFlag( 0x2580 ); }     // Dominion Rod powered up.

    void _02_auruMemoItemFunc()
    {
        libtp::tp::d_save::setItem( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_item,
                                    0x7,
                                    libtp::data::items::Aurus_Memo );
    }     // Put Auru's Memo in slot 7 because it is unused

    void _02_ordonPumpkinItemFunc()
    {
        events::setSaveFileEventFlag( 0x480 );      // Told Yeta about Pumpkin
        events::setSaveFileEventFlag( 0x002 );      // Yeto put Pumpkin in soup
        events::setSaveFileEventFlag( 0x1440 );     // SPR Lobby Door Unlocked
        if ( libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Snowpeak_Ruins] ) ||
             libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[libtp::data::stage::stageIDs::Darkhammer] ) ||
             libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[libtp::data::stage::stageIDs::Blizzeta] ) )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags.memoryFlags[0x9] |= 0x4;
        }
        else
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x14].temp_flags.memoryFlags[0x9] |= 0x4;
        }
    }

    void _02_ordonGoatCheeseItemFunc()
    {
        events::setSaveFileEventFlag( 0x120 );      // Told Yeta about Cheese
        events::setSaveFileEventFlag( 0x01 );       // Yeto put cheese in soup
        events::setSaveFileEventFlag( 0x1420 );     // SPR Lobby West Door Unlocked
        if ( libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Snowpeak_Ruins] ) ||
             libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[libtp::data::stage::stageIDs::Darkhammer] ) ||
             libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[libtp::data::stage::stageIDs::Blizzeta] ) )
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags.memoryFlags[0x9] |= 0x8;
        }
        else
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x14].temp_flags.memoryFlags[0x9] |= 0x8;
        }
    }

    void _02_filledSkybookItemFunc()
    {
        events::setSaveFileEventFlag( 0x3B08 );     // Repaired Cannon at Lake
    }

    void _02_bigWalletItemFunc()
    {
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentWallet =
            libtp::data::items::BIG_WALLET;
        for ( uint16_t rupee = 0x1038; rupee <= 0x1044; rupee += 0x4 )
        {
            if ( libtp::tp::d_meter2_info::g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>(
                        libtp::tp::d_meter2_info::g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                    rupee ) ) = 0xff0000ff;
            }
        }
    }

    void _02_giantWalletItemFunc()
    {
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentWallet =
            libtp::data::items::GIANT_WALLET;
        for ( uint16_t rupee = 0x1038; rupee <= 0x1044; rupee += 0x4 )
        {
            if ( libtp::tp::d_meter2_info::g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>(
                        libtp::tp::d_meter2_info::g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                    rupee ) ) = 0xaf00ffff;
            }
        }
    }

    void _02_gateKeysItemFunc()
    {
        events::setSaveFileEventFlag( 0x840 );     // Started Zora Escort
        events::setSaveFileEventFlag( 0x810 );     // Completed Zora Escort
        if ( libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Kakariko_Village] ) ||
             libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Kakariko_Graveyard] ) ||
             libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Death_Mountain] ) ||
             libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Hidden_Village] ) )
        {
            libtp::tp::d_save::onSwitch_dSv_memBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x69 );
            libtp::tp::d_save::onSwitch_dSv_memBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x65 );
        }
        else
        {
            libtp::tp::d_save::onSwitch_dSv_memBit(
                &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x3].temp_flags,
                0x69 );
            libtp::tp::d_save::onSwitch_dSv_memBit(
                &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x3].temp_flags,
                0x65 );
        }
    }

    void _02_heartContainerItemFunc()
    {
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.maxHealth += 5;
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentHealth =
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.maxHealth;
    }

    void _02_firstFusedShadowItemFunc()
    {
        libtp::tp::d_save::onCollectCrystal( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                             '\0' );
    }     // Give player first fused shadow.

    void _02_secondFusedShadowItemFunc()
    {
        libtp::tp::d_save::onCollectCrystal( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                             '\x01' );
    }     // Give player second fused shadow.

    void _02_thirdFusedShadowItemFunc()
    {
        libtp::tp::d_save::onCollectCrystal( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                             '\x02' );
        if ( randoIsEnabled( randomizer ) )
        {
            // If the player has the castle requirement set to Fused Shadows.
            if ( randomizer->m_Seed->m_Header->castleRequirements == 1 )
            {
                libtp::tp::d_save::onSwitch_dSv_memBit(
                    &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[9].temp_flags,
                    0x0F );
                events::setSaveFileEventFlag( 0x4208 );
            }
            // If the player has the palace requirement set to Fused Shadows.
            if ( randomizer->m_Seed->m_Header->palaceRequirements == 1 )
            {
                events::setSaveFileEventFlag( 0x2B08 );
            }
        }
    }     // Give player third fused shadow.

    void _02_secondMirrorShardItemFunc()
    {
        libtp::tp::d_save::onCollectMirror( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                            '\x01' );
    }     // Give player second mirror shard.

    void _02_thirdMirrorShardItemFunc()
    {
        libtp::tp::d_save::onCollectMirror( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                            '\x02' );
    }     // Give player third mirror shard.

    void _02_fourthMirrorShardItemFunc()
    {
        libtp::tp::d_save::onCollectMirror( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                            '\x03' );
        if ( randoIsEnabled( randomizer ) )
        {
            // If the player has the castle requirement set to Mirror Shards.
            if ( randomizer->m_Seed->m_Header->castleRequirements == 2 )
            {
                libtp::tp::d_save::onSwitch_dSv_memBit(
                    &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[9].temp_flags,
                    0x0F );
                events::setSaveFileEventFlag( 0x4208 );
            }
            // If the player has the palace requirement set to Mirror Shards.
            if ( randomizer->m_Seed->m_Header->palaceRequirements == 2 )
            {
                events::setSaveFileEventFlag( 0x2B08 );
            }
        }
    }     // Give player fourth mirror shard.

    void _02_endingBlowItemFunc() { events::setSaveFileEventFlag( 0x2904 ); }     // Learned Ending Blow.

    void _02_shieldAttackItemFunc() { events::setSaveFileEventFlag( 0x2908 ); }     // Learned Shield Attack.

    void _02_backSliceItemFunc() { events::setSaveFileEventFlag( 0x2902 ); }     // Learned Back Slice.

    void _02_helmSplitterItemFunc() { events::setSaveFileEventFlag( 0x2901 ); }     // Learned Helm Splitter.

    void _02_mortalDrawItemFunc() { events::setSaveFileEventFlag( 0x2A80 ); }     // Learned Mortal Draw.

    void _02_jumpStrikeItemFunc() { events::setSaveFileEventFlag( 0x2A40 ); }     // Learned Jump Strike.

    void _02_greatSpinItemFunc() { events::setSaveFileEventFlag( 0x2A20 ); }     // Learned Great Spin.

    void _02_lanayruVesselItemFunc()
    {
        // Set the flag for lanayru twilight to be cleared.
        libtp::tp::d_save::onLightDropGetFlag( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop,
                                               '\x02' );
        events::setSaveFileEventFlag( 0x1E80 );     // Enable Malo Mart Donation
    }

    void _02_foolishItemFunc() { mod::isFoolishTrapQueued = true; }

    int32_t _02_firstSkybookItemGetCheck()
    {
        bool result =
            libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Ancient_Sky_Book_First_Character );
        return static_cast<int32_t>( result );
    }

    int32_t _02_secondSkybookItemGetCheck()
    {
        bool result =
            libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Ancient_Sky_Book_Second_Character );
        return static_cast<int32_t>( result );
    }

    int32_t _02_thirdSkybookItemGetCheck()
    {
        bool result =
            libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Ancient_Sky_Book_Third_Character );
        return static_cast<int32_t>( result );
    }

    int32_t _02_fourthSkybookItemGetCheck()
    {
        bool result =
            libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Ancient_Sky_Book_Fourth_Character );
        return static_cast<int32_t>( result );
    }

    int32_t _02_fifthSkybookItemGetCheck()
    {
        bool result =
            libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Ancient_Sky_Book_Fifth_Character );
        return static_cast<int32_t>( result );
    }

    int32_t _02_bigWalletItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Big_Wallet );
        return static_cast<int32_t>( result );
    }

    int32_t _02_giantWalletItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Giant_Wallet );
        return static_cast<int32_t>( result );
    }

    int32_t _02_firstFusedShadowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Fused_Shadow_1 );
        return static_cast<int32_t>( result );
    }

    int32_t _02_secondFusedShadowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Fused_Shadow_2 );
        return static_cast<int32_t>( result );
    }

    int32_t _02_thirdFusedShadowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Fused_Shadow_3 );
        return static_cast<int32_t>( result );
    }

    int32_t _02_secondMirrorShardItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Mirror_Piece_2 );
        return static_cast<int32_t>( result );
    }

    int32_t _02_thirdMirrorShardItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Mirror_Piece_3 );
        return static_cast<int32_t>( result );
    }

    int32_t _02_fourthMirrorShardItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Mirror_Piece_4 );
        return static_cast<int32_t>( result );
    }

    int32_t _02_shadowCrystalItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Shadow_Crystal );
        return static_cast<int32_t>( result );
    }

    int32_t _02_endingBlowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Ending_Blow );
        return static_cast<int32_t>( result );
    }

    int32_t _02_shieldAttackItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Shield_Attack );
        return static_cast<int32_t>( result );
    }

    int32_t _02_backSliceItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Back_Slice );
        return static_cast<int32_t>( result );
    }

    int32_t _02_helmSplitterItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Helm_Splitter );
        return static_cast<int32_t>( result );
    }

    int32_t _02_mortalDrawItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Mortal_Draw );
        return static_cast<int32_t>( result );
    }

    int32_t _02_jumpStrikeItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Jump_Strike );
        return static_cast<int32_t>( result );
    }

    int32_t _02_campSmallKeyItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( libtp::data::items::Bulblin_Camp_Key );
        return static_cast<int32_t>( result );
    }
}     // namespace mod::game_patch