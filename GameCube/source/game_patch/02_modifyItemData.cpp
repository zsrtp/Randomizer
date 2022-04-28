#include <string.h>

#include <cstdint>
#include <cstdio>

#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_a_alink.h"
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

    void giveNodeDungeonItems( const libtp::data::stage::AreaNodesID nodeId,
                               const libtp::data::items::NodeDungeonItemType type )
    {
        using namespace libtp::data::items;
        libtp::tp::d_save::dSv_info_c* gameInfoPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        // If the key is for the current area, then update the local node
        int32_t stageIndex = libtp::tools::getStageIndex( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mStage );
        if ( stageIndex != -1 )
        {
            if ( nodeId == static_cast<libtp::data::stage::AreaNodesID>( libtp::data::stage::regionID[stageIndex] ) )
            {
                switch ( type )
                {
                    case NodeDungeonItemType::Small_Key:
                        gameInfoPtr->memory.temp_flags.memoryFlags[0x1C]++;
                        break;
                    case NodeDungeonItemType::Dungeon_Map:
                        gameInfoPtr->memory.temp_flags.memoryFlags[0x1D] |= 0x1;
                        break;
                    case NodeDungeonItemType::Compass:
                        gameInfoPtr->memory.temp_flags.memoryFlags[0x1D] |= 0x2;
                        break;
                    case NodeDungeonItemType::Big_Key:
                        gameInfoPtr->memory.temp_flags.memoryFlags[0x1D] |= 0x4;
                        break;

                    default:
                        break;
                }
            }
            else     // Key is not for the current area, so update the appropriate node
            {
                libtp::tp::d_save::dSv_memory_c* node =
                    reinterpret_cast<libtp::tp::d_save::dSv_memory_c*>( &gameInfoPtr->save_file.area_flags[0] );

                switch ( type )
                {
                    case NodeDungeonItemType::Small_Key:
                        node[static_cast<uint32_t>( nodeId )].temp_flags.memoryFlags[0x1C]++;
                        break;
                    case NodeDungeonItemType::Dungeon_Map:
                        node[static_cast<uint32_t>( nodeId )].temp_flags.memoryFlags[0x1D] |= 0x1;
                        break;
                    case NodeDungeonItemType::Compass:
                        node[static_cast<uint32_t>( nodeId )].temp_flags.memoryFlags[0x1D] |= 0x2;
                        break;
                    case NodeDungeonItemType::Big_Key:
                        node[static_cast<uint32_t>( nodeId )].temp_flags.memoryFlags[0x1D] |= 0x4;
                        break;
                    default:
                        break;
                }
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

        memcpy( &itemResourcePtr[items::Master_Sword],
                &itemResourcePtr[items::Ordon_Sword],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Master_Sword_Light],
                &itemResourcePtr[items::Ordon_Sword],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Horse_Call],
                &itemResourcePtr[items::Ilias_Charm],
                sizeof( d_item_data::ItemResource ) );
        memcpy( &itemResourcePtr[items::Bomb_Bag_Regular_Bombs],
                &itemResourcePtr[items::Goron_Bomb_Bag],
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
        d_item::ItemFunc onGetForestTempleSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Forest_Temple_Small_Key] = onGetForestTempleSmallKey;

        d_item::ItemFunc onGetForestTempleDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Forest_Temple_Dungeon_Map] = onGetForestTempleDungeonMap;

        d_item::ItemFunc onGetForestTempleCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Forest_Temple_Compass] = onGetForestTempleCompass;

        d_item::ItemFunc onGetForestTempleBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Forest_Temple_Big_Key] = onGetForestTempleBigKey;

        // Goron Mines
        d_item::ItemFunc onGetGoronMinesSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Goron_Mines_Small_Key] = onGetGoronMinesSmallKey;

        d_item::ItemFunc onGetGoronMinesDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Goron_Mines_Dungeon_Map] = onGetGoronMinesDungeonMap;

        d_item::ItemFunc onGetGoronMinesCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Goron_Mines_Compass] = onGetGoronMinesCompass;

        d_item::ItemFunc onGetGoronMinesBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
            d_item::execItemGet( items::Key_Shard_3 );
        };
        itemFuncPtr[items::Big_Key_Goron_Mines] = onGetGoronMinesBigKey;

        // Lakebed Temple
        d_item::ItemFunc onGetLakebedTempleSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Lakebed_Temple_Small_Key] = onGetLakebedTempleSmallKey;

        d_item::ItemFunc onGetLakebedTempleDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Lakebed_Temple_Dungeon_Map] = onGetLakebedTempleDungeonMap;

        d_item::ItemFunc onGetLakebedTempleCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Lakebed_Temple_Compass] = onGetLakebedTempleCompass;

        d_item::ItemFunc onGetLakebedTempleBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Lakebed_Temple_Big_Key] = onGetLakebedTempleBigKey;

        // Arbiters Grounds
        d_item::ItemFunc onGetArbitersGroundsSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Arbiters_Grounds_Small_Key] = onGetArbitersGroundsSmallKey;

        d_item::ItemFunc onGetArbitersGroundsDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Arbiters_Grounds_Dungeon_Map] = onGetArbitersGroundsDungeonMap;

        d_item::ItemFunc onGetArbitersGroundsCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Arbiters_Grounds_Compass] = onGetArbitersGroundsCompass;

        d_item::ItemFunc onGetArbitersGroundsBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Arbiters_Grounds_Big_Key] = onGetArbitersGroundsBigKey;

        // Snowpeak Ruins
        d_item::ItemFunc onGetSnowpeakRuinsSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Snowpeak_Ruins_Small_Key] = onGetSnowpeakRuinsSmallKey;

        d_item::ItemFunc onGetSnowpeakRuinsDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Snowpeak_Ruins_Dungeon_Map] = onGetSnowpeakRuinsDungeonMap;

        d_item::ItemFunc onGetSnowpeakRuinsCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Snowpeak_Ruins_Compass] = onGetSnowpeakRuinsCompass;

        d_item::ItemFunc onGetSnowpeakRuinsBedroomKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Bed_Key] = onGetSnowpeakRuinsBedroomKey;

        // Temple of Time
        d_item::ItemFunc onGetTempleofTimeSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Temple_of_Time_Small_Key] = onGetTempleofTimeSmallKey;

        d_item::ItemFunc onGetTempleofTimeDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Temple_of_Time_Dungeon_Map] = onGetTempleofTimeDungeonMap;

        d_item::ItemFunc onGetTempleofTimeCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Temple_of_Time_Compass] = onGetTempleofTimeCompass;

        d_item::ItemFunc onGetTempleofTimeBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Temple_of_Time_Big_Key] = onGetTempleofTimeBigKey;

        // City in The Sky
        d_item::ItemFunc onGetCityinTheSkySmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::City_in_The_Sky_Small_Key] = onGetCityinTheSkySmallKey;

        d_item::ItemFunc onGetCityinTheSkyDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::City_in_The_Sky_Dungeon_Map] = onGetCityinTheSkyDungeonMap;

        d_item::ItemFunc onGetCityinTheSkyCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::City_in_The_Sky_Compass] = onGetCityinTheSkyCompass;

        d_item::ItemFunc onGetCityinTheSkyBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::City_in_The_Sky_Big_Key] = onGetCityinTheSkyBigKey;

        // Palace of Twilight
        d_item::ItemFunc onGetPalaceofTwilightSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Palace_of_Twilight_Small_Key] = onGetPalaceofTwilightSmallKey;

        d_item::ItemFunc onGetPalaceofTwilightDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Palace_of_Twilight_Dungeon_Map] = onGetPalaceofTwilightDungeonMap;

        d_item::ItemFunc onGetPalaceofTwilightCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Palace_of_Twilight_Compass] = onGetPalaceofTwilightCompass;

        d_item::ItemFunc onGetPalaceofTwilightBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Palace_of_Twilight_Big_Key] = onGetPalaceofTwilightBigKey;

        // Hyrule Castle
        d_item::ItemFunc onGetHyruleCastleSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Hyrule_Castle_Small_Key] = onGetHyruleCastleSmallKey;

        d_item::ItemFunc onGetHyruleCastleDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Hyrule_Castle_Dungeon_Map] = onGetHyruleCastleDungeonMap;

        d_item::ItemFunc onGetHyruleCastleCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Hyrule_Castle_Compass] = onGetHyruleCastleCompass;

        d_item::ItemFunc onGetHyruleCastleBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Hyrule_Castle_Big_Key] = onGetHyruleCastleBigKey;

        // Bulblin Camp
        d_item::ItemFunc onGetBublinCampKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Gerudo_Desert;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Bulblin_Camp_Key] = onGetBublinCampKey;

        // Faron Key
        d_item::ItemFunc onGetFaronKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Faron;
            giveNodeDungeonItems( nodeId, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Small_Key_N_Faron_Gate] = onGetFaronKey;

        // Shadow Crystal
        d_item::ItemFunc onGetShadowCrystal = []()
        {
            events::setSaveFileEventFlag( 0xD04 );     // Can transform at will
            events::setSaveFileEventFlag( 0xC10 );     // Midna Accompanies Wolf
            events::setSaveFileEventFlag( 0x501 );     // Midna Charge Unlocked
        };
        itemFuncPtr[items::Shadow_Crystal] = onGetShadowCrystal;

        // Charged Dominion Rod
        d_item::ItemFunc onGetPoweredDominionRod = []()
        { events::setSaveFileEventFlag( 0x2580 ); };     // Dominion Rod powered up.
        itemFuncPtr[items::Dominion_Rod] = onGetPoweredDominionRod;

        // Auru's Memo
        d_item::ItemFunc onGetMemo = []()
        {
            d_save::setItem( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_item, 0x7, items::Aurus_Memo );
        };     // Put Auru's Memo in slot 7 because it is unused
        itemFuncPtr[items::Aurus_Memo] = onGetMemo;

        // Ordon Pumpkin
        d_item::ItemFunc onGetOrdonPumpkin = []()
        {
            events::setSaveFileEventFlag( 0x480 );      // Told Yeta about Pumpkin
            events::setSaveFileEventFlag( 0x002 );      // Yeto put Pumpkin in soup
            events::setSaveFileEventFlag( 0x1440 );     // SPR Lobby Door Unlocked
            if ( d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Snowpeak_Ruins] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Darkhammer] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Blizzeta] ) )
            {
                d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags.memoryFlags[0x9] |= 0x4;
            }
            else
            {
                d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x14].temp_flags.memoryFlags[0x9] |= 0x4;
            }
        };
        itemFuncPtr[items::Ordon_Pumpkin] = onGetOrdonPumpkin;

        // Ordon Goat Cheese
        d_item::ItemFunc onGetOrdonGoatCheese = []()
        {
            events::setSaveFileEventFlag( 0x120 );      // Told Yeta about Cheese
            events::setSaveFileEventFlag( 0x01 );       // Yeto put cheese in soup
            events::setSaveFileEventFlag( 0x1420 );     // SPR Lobby West Door Unlocked
            if ( d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Snowpeak_Ruins] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Darkhammer] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Blizzeta] ) )
            {
                d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags.memoryFlags[0x9] |= 0x8;
            }
            else
            {
                d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x14].temp_flags.memoryFlags[0x9] |= 0x8;
            }
        };
        itemFuncPtr[items::Ordon_Goat_Cheese] = onGetOrdonGoatCheese;

        // Completed Skybook
        d_item::ItemFunc onGetFilledSkybook = []()
        {
            events::setSaveFileEventFlag( 0x3B08 );     // Repaired Cannon at Lake
        };
        itemFuncPtr[items::Ancient_Sky_Book_Completed] = onGetFilledSkybook;

        // Change rupee color for big wallet
        d_item::ItemFunc onGetBigWallet = []()
        {
            d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentWallet = items::BIG_WALLET;
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
        };
        itemFuncPtr[items::Big_Wallet] = onGetBigWallet;

        // Change rupee color for giant wallet
        d_item::ItemFunc onGetGiantWallet = []()
        {
            d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentWallet = items::GIANT_WALLET;
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
        };
        itemFuncPtr[items::Giant_Wallet] = onGetGiantWallet;

        // Gate Keys
        d_item::ItemFunc onGetGateKeys = []()
        {
            events::setSaveFileEventFlag( 0x840 );     // Started Zora Escort
            events::setSaveFileEventFlag( 0x810 );     // Completed Zora Escort
            if ( d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Kakariko_Village] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Kakariko_Graveyard] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Death_Mountain] ) ||
                 d_a_alink::checkStageName( stage::allStages[stage::stageIDs::Hidden_Village] ) )
            {
                d_save::onSwitch_dSv_memBit( &d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x69 );
                d_save::onSwitch_dSv_memBit( &d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x65 );
            }
            else
            {
                d_save::onSwitch_dSv_memBit( &d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x3].temp_flags,
                                             0x69 );
                d_save::onSwitch_dSv_memBit( &d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x3].temp_flags,
                                             0x65 );
            }
        };
        itemFuncPtr[items::Gate_Keys] = onGetGateKeys;

        d_item::ItemFunc onCollectHeartContainer = []()
        {
            d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.maxHealth += 5;
            d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentHealth =
                d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.maxHealth;
        };
        itemFuncPtr[items::Heart_Container] = onCollectHeartContainer;

        // Fused Shadows/Mirror Shards
        d_item::ItemFunc onGetFusedShadow1 = []()
        {
            d_save::onCollectCrystal( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect, '\0' );
        };     // Give player first fused shadow.
        itemFuncPtr[items::Fused_Shadow_1] = onGetFusedShadow1;
        d_item::ItemFunc onGetFusedShadow2 = []()
        {
            d_save::onCollectCrystal( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect, '\x01' );
        };     // Give player second fused shadow.
        itemFuncPtr[items::Fused_Shadow_2] = onGetFusedShadow2;
        d_item::ItemFunc onGetFusedShadow3 = []()
        {
            d_save::onCollectCrystal( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect, '\x02' );
            if ( randomizer )
            {
                if ( randomizer->m_Seed->m_Header->castleRequirements == 1 )
                {
                    libtp::tp::d_save::onSwitch_dSv_memBit(
                        &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[9].temp_flags,
                        0x0F );
                    events::setSaveFileEventFlag( 0x4208 );
                }
                if ( randomizer->m_Seed->m_Header->palaceRequirements == 1 )
                {
                    events::setSaveFileEventFlag( 0x2B08 );
                }
            }
        };     // Give player third fused shadow.
        itemFuncPtr[items::Fused_Shadow_3] = onGetFusedShadow3;

        d_item::ItemFunc onGetMirrorShard2 = []()
        {
            d_save::onCollectMirror( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect, '\x01' );
        };     // Give player second mirror shard.
        itemFuncPtr[items::Mirror_Piece_2] = onGetMirrorShard2;
        d_item::ItemFunc onGetMirrorShard3 = []()
        {
            d_save::onCollectMirror( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect, '\x02' );
        };     // Give player third mirror shard.
        itemFuncPtr[items::Mirror_Piece_3] = onGetMirrorShard3;
        d_item::ItemFunc onGetMirrorShard4 = []()
        {
            d_save::onCollectMirror( &d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect, '\x03' );
            if ( randomizer )
            {
                if ( randomizer->m_Seed->m_Header->castleRequirements == 2 )
                {
                    libtp::tp::d_save::onSwitch_dSv_memBit(
                        &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[9].temp_flags,
                        0x0F );
                    events::setSaveFileEventFlag( 0x4208 );
                }
                if ( randomizer->m_Seed->m_Header->palaceRequirements == 2 )
                {
                    events::setSaveFileEventFlag( 0x2B08 );
                }
            }
        };     // Give player fourth mirror shard.
        itemFuncPtr[items::Mirror_Piece_4] = onGetMirrorShard4;

        // Ending Blow
        d_item::ItemFunc onGetEndingBlow = []() { events::setSaveFileEventFlag( 0x2904 ); };     // Learned Ending Blow.
        itemFuncPtr[items::Ending_Blow] = onGetEndingBlow;

        // Shield Attack
        d_item::ItemFunc onGetShieldAttack = []() { events::setSaveFileEventFlag( 0x2908 ); };     // Learned Shield Attack.
        itemFuncPtr[items::Shield_Attack] = onGetShieldAttack;

        // Back Slice
        d_item::ItemFunc onGetBackSlice = []() { events::setSaveFileEventFlag( 0x2902 ); };     // Learned Back Slice.
        itemFuncPtr[items::Back_Slice] = onGetBackSlice;

        // Helm Splitter
        d_item::ItemFunc onGetHelmSplitter = []() { events::setSaveFileEventFlag( 0x2901 ); };     // Learned Helm Splitter.
        itemFuncPtr[items::Helm_Splitter] = onGetHelmSplitter;

        // Mortal Draw
        d_item::ItemFunc onGetMortalDraw = []() { events::setSaveFileEventFlag( 0x2A80 ); };     // Learned Mortal Draw.
        itemFuncPtr[items::Mortal_Draw] = onGetMortalDraw;

        // Jump Strike
        d_item::ItemFunc onGetJumpStrike = []() { events::setSaveFileEventFlag( 0x2A40 ); };     // Learned Jump Strike.
        itemFuncPtr[items::Jump_Strike] = onGetJumpStrike;

        // Great Spin
        d_item::ItemFunc onGetGreatSpin = []() { events::setSaveFileEventFlag( 0x2A20 ); };     // Learned Great Spin.
        itemFuncPtr[items::Great_Spin] = onGetGreatSpin;

        // Lanayru Vessel of Light
        d_item::ItemFunc onGetLanayruVessel = []()
        {
            libtp::tp::d_save::onLightDropGetFlag(
                &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop,
                '\x02' );
            events::setSaveFileEventFlag( 0x1E80 );     // Enable Malo Mart Donation
        };
        itemFuncPtr[items::Vessel_Of_Light_Lanayru] = onGetLanayruVessel;

        // Some items need a valid getCheckFunc definition.
        d_item::ItemGetCheckFunc item_getcheck_func_first_character = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Ancient_Sky_Book_First_Character ); };
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_First_Character] = item_getcheck_func_first_character;

        d_item::ItemGetCheckFunc item_getcheck_func_second_character = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Ancient_Sky_Book_Second_Character ); };
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Second_Character] = item_getcheck_func_second_character;

        d_item::ItemGetCheckFunc item_getcheck_func_third_character = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Ancient_Sky_Book_Third_Character ); };
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Third_Character] = item_getcheck_func_third_character;

        d_item::ItemGetCheckFunc item_getcheck_func_fourth_character = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Ancient_Sky_Book_Fourth_Character ); };
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Fourth_Character] = item_getcheck_func_fourth_character;

        d_item::ItemGetCheckFunc item_getcheck_func_fifth_character = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Ancient_Sky_Book_Fifth_Character ); };
        itemGetCheckFuncPtr[items::Ancient_Sky_Book_Fifth_Character] = item_getcheck_func_fifth_character;

        d_item::ItemGetCheckFunc item_getcheck_func_big_wallet = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Big_Wallet ); };
        itemGetCheckFuncPtr[items::Big_Wallet] = item_getcheck_func_big_wallet;

        d_item::ItemGetCheckFunc item_getcheck_func_giant_wallet = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Giant_Wallet ); };
        itemGetCheckFuncPtr[items::Giant_Wallet] = item_getcheck_func_giant_wallet;

        d_item::ItemGetCheckFunc item_getcheck_func_first_fused_shadow = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Fused_Shadow_1 ); };
        itemGetCheckFuncPtr[items::Fused_Shadow_1] = item_getcheck_func_first_fused_shadow;

        d_item::ItemGetCheckFunc item_getcheck_func_second_fused_shadow = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Fused_Shadow_2 ); };
        itemGetCheckFuncPtr[items::Fused_Shadow_2] = item_getcheck_func_second_fused_shadow;

        d_item::ItemGetCheckFunc item_getcheck_func_third_fused_shadow = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Fused_Shadow_3 ); };
        itemGetCheckFuncPtr[items::Fused_Shadow_3] = item_getcheck_func_third_fused_shadow;

        d_item::ItemGetCheckFunc item_getcheck_func_second_mirror_shard = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Mirror_Piece_2 ); };
        itemGetCheckFuncPtr[items::Mirror_Piece_2] = item_getcheck_func_second_mirror_shard;

        d_item::ItemGetCheckFunc item_getcheck_func_third_mirror_shard = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Mirror_Piece_3 ); };
        itemGetCheckFuncPtr[items::Mirror_Piece_3] = item_getcheck_func_third_mirror_shard;

        d_item::ItemGetCheckFunc item_getcheck_func_fourth_mirror_shard = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Mirror_Piece_4 ); };
        itemGetCheckFuncPtr[items::Mirror_Piece_4] = item_getcheck_func_fourth_mirror_shard;

        d_item::ItemGetCheckFunc item_getcheck_func_shadow_crystal = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Shadow_Crystal ); };
        itemGetCheckFuncPtr[items::Shadow_Crystal] = item_getcheck_func_shadow_crystal;

        d_item::ItemGetCheckFunc item_getcheck_func_ending_blow = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Ending_Blow ); };
        itemGetCheckFuncPtr[items::Ending_Blow] = item_getcheck_func_ending_blow;

        d_item::ItemGetCheckFunc item_getcheck_func_shield_attack = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Shield_Attack ); };
        itemGetCheckFuncPtr[items::Shield_Attack] = item_getcheck_func_shield_attack;

        d_item::ItemGetCheckFunc item_getcheck_func_back_slice = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Back_Slice ); };
        itemGetCheckFuncPtr[items::Back_Slice] = item_getcheck_func_back_slice;

        d_item::ItemGetCheckFunc item_getcheck_func_helm_splitter = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Helm_Splitter ); };
        itemGetCheckFuncPtr[items::Helm_Splitter] = item_getcheck_func_helm_splitter;

        d_item::ItemGetCheckFunc item_getcheck_func_mortal_draw = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Mortal_Draw ); };
        itemGetCheckFuncPtr[items::Mortal_Draw] = item_getcheck_func_mortal_draw;

        d_item::ItemGetCheckFunc item_getcheck_func_jump_strike = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Jump_Strike ); };
        itemGetCheckFuncPtr[items::Jump_Strike] = item_getcheck_func_jump_strike;

        d_item::ItemGetCheckFunc item_getcheck_func_bulblin_camp_key = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Bulblin_Camp_Key ); };
        itemGetCheckFuncPtr[items::Bulblin_Camp_Key] = item_getcheck_func_bulblin_camp_key;
    }
    void _02_modifyItemData()
    {
        setCustomItemResourceData();
        modifyItemModels();
        setCustomItemFunctions();
    }
}     // namespace mod::game_patch