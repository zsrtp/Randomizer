#include <string.h>

#include <cstdint>
#include <cstdio>

#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"
#include "tp/d_save.h"

namespace mod::game_patch
{
    void giveNodeDungeonItems( const libtp::data::stage::AreaNodesID nodeId,
                               const char* stage,
                               const libtp::data::items::NodeDungeonItemType type )
    {
        using namespace libtp::data::items;
        libtp::tp::d_save::dSv_info_c* gameInfoPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        // If the key is for the current area, then update the local node
        // Only check the first 4 characters, since those are what determine each area
        if ( strncmp( gameInfoPtr->save_file.player.player_return_place.link_current_stage, stage, 4 ) == 0 )
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

    void modifyItemModels()
    {
        using namespace libtp::data;
        using namespace libtp::tp;
        d_item_data::ItemInfo* itemInfoPtr = &d_item_data::item_info[0];
        d_item_data::FieldItemRes* fieldItemResPtr = &d_item_data::field_item_res[0];
        d_item_data::ItemResource* itemResourcePtr = &d_item_data::item_resource[0];
        uint8_t* getSeTypePtr = &libtp::tp::d_a_alink::getSeType[0];
        d_item_data::ItemInfo* yellowRupeeInfoPtr = &d_item_data::item_info[items::Yellow_Rupee];
        uint8_t itemsWithNoFieldModel[] = { items::Bombs_5,
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
                                            items::Ancient_Sky_Book_Empty,
                                            items::Ancient_Sky_Book_First_Character,
                                            items::Ancient_Sky_Book_Second_Character,
                                            items::Ancient_Sky_Book_Third_Character,
                                            items::Ancient_Sky_Book_Fourth_Character,
                                            items::Ancient_Sky_Book_Fifth_Character,
                                            items::Ancient_Sky_Book_Completed,
                                            items::Purple_Rupee_Links_House,
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
            const char* stage = stage::allStages[stage::stageIDs::Forest_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Forest_Temple_Small_Key] = onGetForestTempleSmallKey;

        d_item::ItemFunc onGetForestTempleDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Forest_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Forest_Temple_Dungeon_Map] = onGetForestTempleDungeonMap;

        d_item::ItemFunc onGetForestTempleCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Forest_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Forest_Temple_Compass] = onGetForestTempleCompass;

        d_item::ItemFunc onGetForestTempleBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Forest_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Forest_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Forest_Temple_Big_Key] = onGetForestTempleBigKey;

        // Goron Mines
        d_item::ItemFunc onGetGoronMinesSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            const char* stage = stage::allStages[stage::stageIDs::Goron_Mines];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Goron_Mines_Small_Key] = onGetGoronMinesSmallKey;

        d_item::ItemFunc onGetGoronMinesDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            const char* stage = stage::allStages[stage::stageIDs::Goron_Mines];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Goron_Mines_Dungeon_Map] = onGetGoronMinesDungeonMap;

        d_item::ItemFunc onGetGoronMinesCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            const char* stage = stage::allStages[stage::stageIDs::Goron_Mines];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Goron_Mines_Compass] = onGetGoronMinesCompass;

        d_item::ItemFunc onGetGoronMinesBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Goron_Mines;
            const char* stage = stage::allStages[stage::stageIDs::Goron_Mines];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
            d_item::execItemGet( items::Key_Shard_3 );
        };
        itemFuncPtr[items::Big_Key_Goron_Mines] = onGetGoronMinesBigKey;

        // Lakebed Temple
        d_item::ItemFunc onGetLakebedTempleSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Lakebed_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Lakebed_Temple_Small_Key] = onGetLakebedTempleSmallKey;

        d_item::ItemFunc onGetLakebedTempleDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Lakebed_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Lakebed_Temple_Dungeon_Map] = onGetLakebedTempleDungeonMap;

        d_item::ItemFunc onGetLakebedTempleCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Lakebed_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Lakebed_Temple_Compass] = onGetLakebedTempleCompass;

        d_item::ItemFunc onGetLakebedTempleBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Lakebed_Temple;
            const char* stage = stage::allStages[stage::stageIDs::Lakebed_Temple];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Lakebed_Temple_Big_Key] = onGetLakebedTempleBigKey;

        // Arbiters Grounds
        d_item::ItemFunc onGetArbitersGroundsSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            const char* stage = stage::allStages[stage::stageIDs::Arbiters_Grounds];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Arbiters_Grounds_Small_Key] = onGetArbitersGroundsSmallKey;

        d_item::ItemFunc onGetArbitersGroundsDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            const char* stage = stage::allStages[stage::stageIDs::Arbiters_Grounds];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Arbiters_Grounds_Dungeon_Map] = onGetArbitersGroundsDungeonMap;

        d_item::ItemFunc onGetArbitersGroundsCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            const char* stage = stage::allStages[stage::stageIDs::Arbiters_Grounds];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Arbiters_Grounds_Compass] = onGetArbitersGroundsCompass;

        d_item::ItemFunc onGetArbitersGroundsBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Arbiters_Grounds;
            const char* stage = stage::allStages[stage::stageIDs::Arbiters_Grounds];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Arbiters_Grounds_Big_Key] = onGetArbitersGroundsBigKey;

        // Snowpeak Ruins
        d_item::ItemFunc onGetSnowpeakRuinsSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            const char* stage = stage::allStages[stage::stageIDs::Snowpeak_Ruins];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Snowpeak_Ruins_Small_Key] = onGetSnowpeakRuinsSmallKey;

        d_item::ItemFunc onGetSnowpeakRuinsDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            const char* stage = stage::allStages[stage::stageIDs::Snowpeak_Ruins];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Snowpeak_Ruins_Dungeon_Map] = onGetSnowpeakRuinsDungeonMap;

        d_item::ItemFunc onGetSnowpeakRuinsCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            const char* stage = stage::allStages[stage::stageIDs::Snowpeak_Ruins];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Snowpeak_Ruins_Compass] = onGetSnowpeakRuinsCompass;

        d_item::ItemFunc onGetSnowpeakRuinsBedroomKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Snowpeak_Ruins;
            const char* stage = stage::allStages[stage::stageIDs::Snowpeak_Ruins];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Bed_Key] = onGetSnowpeakRuinsBedroomKey;

        // Temple of Time
        d_item::ItemFunc onGetTempleofTimeSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            const char* stage = stage::allStages[stage::stageIDs::Temple_of_Time];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Temple_of_Time_Small_Key] = onGetTempleofTimeSmallKey;

        d_item::ItemFunc onGetTempleofTimeDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            const char* stage = stage::allStages[stage::stageIDs::Temple_of_Time];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Temple_of_Time_Dungeon_Map] = onGetTempleofTimeDungeonMap;

        d_item::ItemFunc onGetTempleofTimeCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            const char* stage = stage::allStages[stage::stageIDs::Temple_of_Time];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Temple_of_Time_Compass] = onGetTempleofTimeCompass;

        d_item::ItemFunc onGetTempleofTimeBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Temple_of_Time;
            const char* stage = stage::allStages[stage::stageIDs::Temple_of_Time];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Temple_of_Time_Big_Key] = onGetTempleofTimeBigKey;

        // City in The Sky
        d_item::ItemFunc onGetCityinTheSkySmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            const char* stage = stage::allStages[stage::stageIDs::City_in_the_Sky];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::City_in_The_Sky_Small_Key] = onGetCityinTheSkySmallKey;

        d_item::ItemFunc onGetCityinTheSkyDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            const char* stage = stage::allStages[stage::stageIDs::City_in_the_Sky];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::City_in_The_Sky_Dungeon_Map] = onGetCityinTheSkyDungeonMap;

        d_item::ItemFunc onGetCityinTheSkyCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            const char* stage = stage::allStages[stage::stageIDs::City_in_the_Sky];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::City_in_The_Sky_Compass] = onGetCityinTheSkyCompass;

        d_item::ItemFunc onGetCityinTheSkyBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::City_in_the_Sky;
            const char* stage = stage::allStages[stage::stageIDs::City_in_the_Sky];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::City_in_The_Sky_Big_Key] = onGetCityinTheSkyBigKey;

        // Palace of Twilight
        d_item::ItemFunc onGetPalaceofTwilightSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            const char* stage = stage::allStages[stage::stageIDs::Palace_of_Twilight];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Palace_of_Twilight_Small_Key] = onGetPalaceofTwilightSmallKey;

        d_item::ItemFunc onGetPalaceofTwilightDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            const char* stage = stage::allStages[stage::stageIDs::Palace_of_Twilight];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Palace_of_Twilight_Dungeon_Map] = onGetPalaceofTwilightDungeonMap;

        d_item::ItemFunc onGetPalaceofTwilightCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            const char* stage = stage::allStages[stage::stageIDs::Palace_of_Twilight];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Palace_of_Twilight_Compass] = onGetPalaceofTwilightCompass;

        d_item::ItemFunc onGetPalaceofTwilightBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Palace_of_Twilight;
            const char* stage = stage::allStages[stage::stageIDs::Palace_of_Twilight];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Palace_of_Twilight_Big_Key] = onGetPalaceofTwilightBigKey;

        // Hyrule Castle
        d_item::ItemFunc onGetHyruleCastleSmallKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            const char* stage = stage::allStages[stage::stageIDs::Hyrule_Castle];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Hyrule_Castle_Small_Key] = onGetHyruleCastleSmallKey;

        d_item::ItemFunc onGetHyruleCastleDungeonMap = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            const char* stage = stage::allStages[stage::stageIDs::Hyrule_Castle];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Dungeon_Map );
        };
        itemFuncPtr[items::Hyrule_Castle_Dungeon_Map] = onGetHyruleCastleDungeonMap;

        d_item::ItemFunc onGetHyruleCastleCompass = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            const char* stage = stage::allStages[stage::stageIDs::Hyrule_Castle];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Compass );
        };
        itemFuncPtr[items::Hyrule_Castle_Compass] = onGetHyruleCastleCompass;

        d_item::ItemFunc onGetHyruleCastleBigKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Hyrule_Castle;
            const char* stage = stage::allStages[stage::stageIDs::Hyrule_Castle];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Big_Key );
        };
        itemFuncPtr[items::Hyrule_Castle_Big_Key] = onGetHyruleCastleBigKey;

        // Bublin Camp
        d_item::ItemFunc onGetBublinCampKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Gerudo_Desert;
            const char* stage = stage::allStages[stage::stageIDs::Bulblin_Camp];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Bulblin_Camp_Key] = onGetBublinCampKey;

        // Faron Key
        d_item::ItemFunc onGetFaronKey = []()
        {
            const stage::AreaNodesID nodeId = stage::AreaNodesID::Faron;
            const char* stage = stage::allStages[stage::stageIDs::Faron_Woods];
            giveNodeDungeonItems( nodeId, stage, items::NodeDungeonItemType::Small_Key );
        };
        itemFuncPtr[items::Small_Key_N_Faron_Gate] = onGetFaronKey;

        // Shadow Crystal
        d_item::ItemFunc onGetShadowCrystal = []() { events::setSaveFileEventFlag( 0xD04 ); };     // Can transform at will
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
            events::setSaveFileEventFlag( 0x020 );      // Yeto took Pumpkin
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
            events::setSaveFileEventFlag( 0x010 );      // Yeto took Cheese
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
        };     // Give player fourth mirror shard.
        itemFuncPtr[items::Mirror_Piece_4] = onGetMirrorShard4;

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

        d_item::ItemGetCheckFunc item_getcheck_func_first_fused_shadow = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Fused_Shadow_1 ); };
        itemGetCheckFuncPtr[items::Fused_Shadow_1] = item_getcheck_func_first_fused_shadow;

        d_item::ItemGetCheckFunc item_getcheck_func_second_fused_shadow = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Fused_Shadow_2 ); };
        itemGetCheckFuncPtr[items::Fused_Shadow_2] = item_getcheck_func_second_fused_shadow;

        d_item::ItemGetCheckFunc item_getcheck_func_second_mirror_shard = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Mirror_Piece_2 ); };
        itemGetCheckFuncPtr[items::Mirror_Piece_2] = item_getcheck_func_second_mirror_shard;

        d_item::ItemGetCheckFunc item_getcheck_func_third_mirror_shard = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Mirror_Piece_3 ); };
        itemGetCheckFuncPtr[items::Mirror_Piece_3] = item_getcheck_func_third_mirror_shard;

        d_item::ItemGetCheckFunc item_getcheck_func_shadow_crystal = []()
        { return libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit( items::Shadow_Crystal ); };
        itemGetCheckFuncPtr[items::Shadow_Crystal] = item_getcheck_func_shadow_crystal;
    }
    void _02_modifyItemData()
    {
        setCustomItemResourceData();
        modifyItemModels();
        setCustomItemFunctions();
    }
}     // namespace mod::game_patch