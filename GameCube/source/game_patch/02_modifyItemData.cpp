#include <cstdint>
#include <cstring>

#include "game_patch/game_patch.h"
#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"
#include "tp/d_meter2_info.h"
#include "tp/d_save.h"
#include "data/flags.h"
#include "rando/data.h"
#include "rando/customItems.h"
#include "tools.h"

namespace mod::game_patch
{
    const uint8_t foolishModelItemList[TOTAL_FOOLISH_ITEM_MODELS] = {
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

    void giveNodeDungeonItems(const libtp::data::stage::AreaNodesID nodeId, const libtp::data::items::NodeDungeonItemType type)
    {
        using namespace libtp::data::items;
        const int32_t currentAreaNodeId = events::getCurrentAreaNodeId();

        // Make sure the node id is valid
        if (currentAreaNodeId >= 0)
        {
            uint8_t* memoryFlags =
                events::getNodeMemoryFlags(nodeId, static_cast<libtp::data::stage::AreaNodesID>(currentAreaNodeId));

            switch (type)
            {
                case NodeDungeonItemType::Small_Key:
                {
                    // The vanilla code caps the key count at 100
                    uint8_t* memoryFlagAddress = &memoryFlags[0x1C];
                    uint8_t smallKeyCount = *memoryFlagAddress;

                    if (smallKeyCount < 100)
                    {
                        *memoryFlagAddress = smallKeyCount + 1;
                        libtp::gc_wii::os_cache::DCFlushRange(memoryFlagAddress, sizeof(uint8_t));
                    }
                    break;
                }
                case NodeDungeonItemType::Dungeon_Map:
                {
                    uint8_t* memoryFlagAddress = &memoryFlags[0x1D];
                    *memoryFlagAddress |= 0x1;
                    libtp::gc_wii::os_cache::DCFlushRange(memoryFlagAddress, sizeof(uint8_t));
                    break;
                }
                case NodeDungeonItemType::Compass:
                {
                    uint8_t* memoryFlagAddress = &memoryFlags[0x1D];
                    *memoryFlagAddress |= 0x2;
                    libtp::gc_wii::os_cache::DCFlushRange(memoryFlagAddress, sizeof(uint8_t));
                    break;
                }
                case NodeDungeonItemType::Big_Key:
                {
                    uint8_t* memoryFlagAddress = &memoryFlags[0x1D];
                    *memoryFlagAddress |= 0x4;
                    libtp::gc_wii::os_cache::DCFlushRange(memoryFlagAddress, sizeof(uint8_t));
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    uint32_t getFoolishModelRandomIndex(uint8_t* foolishModelIndexes, uint32_t loopCurrentCount)
    {
        constexpr uint32_t modelListSize = sizeof(foolishModelItemList) / sizeof(foolishModelItemList[0]);
        uint32_t randomIndex = libtp::tools::ulRand(&randState, modelListSize);

        uint32_t i = 0;
        while (i < loopCurrentCount)
        {
            // Make sure no duplicate indexes are used
            if (randomIndex == foolishModelIndexes[i])
            {
                // Get a new index and restart the loop
                randomIndex = libtp::tools::ulRand(&randState, modelListSize);
                i = 0;
                continue;
            }
            i++;
        }

        foolishModelIndexes[loopCurrentCount] = static_cast<uint8_t>(randomIndex);
        return randomIndex;
    }

    void _02_modifyFoolishFieldModel()
    {
        // Set the field model of the Foolish Item ID to the model of a random important item.
        libtp::tp::d_item_data::FieldItemRes* fieldItemResPtr = &libtp::tp::d_item_data::field_item_res[0];
        rando::customItems::FoolishItems* foolishItemsPtr = &rando::foolishItems;

        const uint8_t* foolishItemIds = foolishItemsPtr->itemIds;
        uint8_t* itemModelIds = foolishItemsPtr->itemModelId;

        constexpr uint32_t loopCount = MAX_SPAWNED_FOOLISH_ITEMS;
        uint8_t foolishModelIndexes[loopCount];

        for (uint32_t i = 0; i < loopCount; i++)
        {
            const uint32_t randomIndex = getFoolishModelRandomIndex(foolishModelIndexes, i);
            const uint32_t fieldModelItemID = _04_verifyProgressiveItem(randomizer, foolishModelItemList[randomIndex]);
            itemModelIds[i] = static_cast<uint8_t>(fieldModelItemID);

            libtp::tp::d_item_data::FieldItemRes* currentFieldItemPtr = &fieldItemResPtr[foolishItemIds[i]];

            memcpy(currentFieldItemPtr, &fieldItemResPtr[fieldModelItemID], sizeof(libtp::tp::d_item_data::FieldItemRes));

            // Clear the cache for the modified values
            libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(currentFieldItemPtr),
                                                  sizeof(libtp::tp::d_item_data::FieldItemRes));
        }
    }

    void _02_modifyFoolishShopModel(uint8_t* foolishModelIndexes, uint32_t loopCurrentCount, uint32_t shopID)
    {
        using namespace libtp::tp::d_a_shop_item_static;

        // Set the shop model of the Foolish Item ID to the model of a random important item.
        const uint32_t randomIndex = getFoolishModelRandomIndex(foolishModelIndexes, loopCurrentCount);
        const uint32_t shopModelItemID = _04_verifyProgressiveItem(randomizer, foolishModelItemList[randomIndex]);

        libtp::tp::d_item_data::ItemResource* fieldItemResPtr = &libtp::tp::d_item_data::item_resource[shopModelItemID];
        ShopItemData* shopItemDataPtr = &shopItemData[shopID];

        shopItemDataPtr->arcName = fieldItemResPtr->arcName;
        shopItemDataPtr->modelResIdx = fieldItemResPtr->modelResIdx;
        shopItemDataPtr->wBckResIdx = fieldItemResPtr->bckResIdx;
        shopItemDataPtr->wBrkResIdx = fieldItemResPtr->brkResIdx;
        shopItemDataPtr->wBtpResIdx = fieldItemResPtr->btpResIdx;
        shopItemDataPtr->tevFrm = fieldItemResPtr->tevFrm;

        _02_modifyShopModelScale(shopID, shopModelItemID);

        // Clear the cache for the modified values
        libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(shopItemDataPtr), sizeof(ShopItemData));
    }

    void _02_modifyShopModelScale(uint32_t shopID, uint32_t itemID)
    {
        using namespace libtp::tp::d_a_shop_item_static;

        ShopItemData* shopItemDataPtr = &shopItemData[shopID];
        const uint32_t shopModelItemID = _04_verifyProgressiveItem(randomizer, itemID);

        switch (shopModelItemID)
        {
            case libtp::data::items::Master_Sword:
            case libtp::data::items::Master_Sword_Light:
            {
                shopItemDataPtr->scale = 0.35f;
                break;
            }
            default:
            {
                // Assume no changes are being made, so the cache does not need to be cleared
                return;
            }
        }

        // Clear the cache for the modified value
        libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(&shopItemDataPtr->scale), sizeof(float));
    }

    KEEP_VAR const char* _02_hiddenSkillArc = "O_gD_memo";
    KEEP_VAR const char* _02_mirrorShardArc = "MirrorB";
    KEEP_VAR const char* _02_firstShadowArc = "N_gD_mskF";
    KEEP_VAR const char* _02_secondShadowArc = "N_gD_mskB";
    KEEP_VAR const char* _02_thirdShadowArc = "N_gD_mskT";
    KEEP_VAR const char* _02_masterSwordArc = "MstrSword";

    KEEP_FUNC void _02_forestSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_forestMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_forestCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_forestBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Forest_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_minesSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_minesMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_minesCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_minesBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Goron_Mines;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
        libtp::tp::d_item::execItemGet(libtp::data::items::Key_Shard_3);
    }

    KEEP_FUNC void _02_lakebedSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_lakebedMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_lakebedCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_lakebedBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Lakebed_Temple;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_arbitersSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_arbitersMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_arbitersCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_arbitersBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Arbiters_Grounds;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_snowpeakSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_snowpeakMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_snowpeakCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_snowpeakBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Snowpeak_Ruins;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_totSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_totMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_totCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_totBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Temple_of_Time;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_citySmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_cityMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_cityCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_cityBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::City_in_the_Sky;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_palaceSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_palaceMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_palaceCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_palaceBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Palace_of_Twilight;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_hyruleSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_hyruleMapItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Dungeon_Map);
    }

    KEEP_FUNC void _02_hyruleCompassItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Compass);
    }

    KEEP_FUNC void _02_hyruleBigKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Hyrule_Castle;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Big_Key);
    }

    KEEP_FUNC void _02_campSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Gerudo_Desert;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_faronSmallKeyItemFunc()
    {
        const libtp::data::stage::AreaNodesID nodeId = libtp::data::stage::AreaNodesID::Faron;
        giveNodeDungeonItems(nodeId, libtp::data::items::NodeDungeonItemType::Small_Key);
    }

    KEEP_FUNC void _02_shadowCrystalItemFunc()
    {
        events::setSaveFileEventFlag(libtp::data::flags::TRANSFORMING_UNLOCKED);  // Can transform at will
        events::setSaveFileEventFlag(libtp::data::flags::MIDNA_CHARGE_UNLOCKED);  // Midna Charge Unlocked
        events::setSaveFileEventFlag(libtp::data::flags::MIDNA_ACCOMPANIES_WOLF); // Put Midna on Z
    }

    KEEP_FUNC void _02_poweredDominionRodItemFunc()
    {
        // Dominion Rod powered up.
        events::setSaveFileEventFlag(libtp::data::flags::SHAD_CASTS_UNFINISHED_SPELL_ON_STATUE);
    }

    KEEP_FUNC void _02_auruMemoItemFunc()
    {
        // Put Auru's Memo in slot 7 because it is unused
        libtp::tp::d_save::setItem(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_item,
                                   0x7,
                                   libtp::data::items::Aurus_Memo);
    }

    KEEP_FUNC void _02_ordonPumpkinItemFunc()
    {
        events::setSaveFileEventFlag(libtp::data::flags::TOLD_YETA_ABOUT_PUMPKIN);               // Told Yeta about Pumpkin
        events::setSaveFileEventFlag(libtp::data::flags::PUMPKIN_PUT_IN_SOUP);                   // Yeto put Pumpkin in soup

        events::setSaveFileEventFlag(libtp::data::flags::TALKED_WITH_YETA_AFTER_GIVING_PUMPKIN); // SPR Lobby Door Unlocked

        const auto stagesPtr = &libtp::data::stage::allStages[0];
        libtp::tp::d_save::dSv_info_c* savePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Snowpeak_Ruins]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Darkhammer]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Blizzeta]))
        {
            savePtr->memory.temp_flags.memoryFlags[0x9] |= 0x4;
        }
        else
        {
            savePtr->save_file.area_flags[0x14].temp_flags.memoryFlags[0x9] |= 0x4;
        }
    }

    KEEP_FUNC void _02_ordonGoatCheeseItemFunc()
    {
        events::setSaveFileEventFlag(libtp::data::flags::TOLD_YETA_ABOUT_CHEESE);               // Told Yeta about Cheese
        events::setSaveFileEventFlag(libtp::data::flags::CHEESE_PUT_IN_SOUP);                   // Yeto put cheese in soup

        events::setSaveFileEventFlag(libtp::data::flags::TALKED_WITH_YETA_AFTER_GIVING_CHEESE); // SPR Lobby West Door Unlocked

        const auto stagesPtr = &libtp::data::stage::allStages[0];
        libtp::tp::d_save::dSv_info_c* savePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Snowpeak_Ruins]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Darkhammer]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Blizzeta]))
        {
            savePtr->memory.temp_flags.memoryFlags[0x9] |= 0x8;
        }
        else
        {
            savePtr->save_file.area_flags[0x14].temp_flags.memoryFlags[0x9] |= 0x8;
        }
    }

    KEEP_FUNC void _02_filledSkybookItemFunc()
    {
        events::setSaveFileEventFlag(libtp::data::flags::SKY_CANNON_REPAIRED); // Repaired Cannon at Lake

        libtp::tp::d_save::setItem(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_item,
                                   22,
                                   libtp::data::items::Ancient_Sky_Book_Completed); // Add Skybook to the Item Wheel
    }

    KEEP_FUNC void _02_bigWalletItemFunc()
    {
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentWallet =
            libtp::data::items::BIG_WALLET;

        libtp::tp::J2DWindow::J2DWindow* windowPtr =
            libtp::tp::d_meter2_info::g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow;

        if (!windowPtr)
        {
            return;
        }

        for (uint32_t rupee = 0x1038; rupee <= 0x1044; rupee += 0x4)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(windowPtr) + rupee) = 0xff0000ff;
        }
    }

    KEEP_FUNC void _02_giantWalletItemFunc()
    {
        libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentWallet =
            libtp::data::items::GIANT_WALLET;

        libtp::tp::J2DWindow::J2DWindow* windowPtr =
            libtp::tp::d_meter2_info::g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow;

        if (!windowPtr)
        {
            return;
        }

        for (uint32_t rupee = 0x1038; rupee <= 0x1044; rupee += 0x4)
        {
            *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(windowPtr) + rupee) = 0xaf00ffff;
        }
    }

    KEEP_FUNC void _02_gateKeysItemFunc()
    {
        events::setSaveFileEventFlag(libtp::data::flags::WAGON_ESCORT_STARTED); // Started Zora Escort
        events::setSaveFileEventFlag(libtp::data::flags::ZORA_ESCORT_CLEARED);  // Completed Zora Escort

        const auto stagesPtr = &libtp::data::stage::allStages[0];
        if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Kakariko_Village]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Kakariko_Graveyard]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Death_Mountain]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Hidden_Village]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::stageIDs::Kakariko_Village_Interiors]))
        {
            libtp::tp::d_save::dSv_memBit_c* tempFlagsPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags;

            libtp::tp::d_save::onSwitch_dSv_memBit(tempFlagsPtr, 0x69);
            libtp::tp::d_save::onSwitch_dSv_memBit(tempFlagsPtr, 0x65);
        }
        else
        {
            libtp::tp::d_save::dSv_memBit_c* tempFlagsPtr =
                &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.area_flags[0x3].temp_flags;

            libtp::tp::d_save::onSwitch_dSv_memBit(tempFlagsPtr, 0x69);
            libtp::tp::d_save::onSwitch_dSv_memBit(tempFlagsPtr, 0x65);
        }
    }

    KEEP_FUNC void _02_firstFusedShadowItemFunc()
    {
        // Give player first fused shadow.
        libtp::tp::d_save::onCollectCrystal(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                            '\0');
    }

    KEEP_FUNC void _02_secondFusedShadowItemFunc()
    {
        // Give player second fused shadow.
        libtp::tp::d_save::onCollectCrystal(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                            '\x01');
    }

    KEEP_FUNC void _02_thirdFusedShadowItemFunc()
    {
        // Give player third fused shadow.
        libtp::tp::d_save::onCollectCrystal(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                            '\x02');

        rando::Randomizer* rando = randomizer;
        if (randoIsEnabled(rando))
        {
            rando::Header* headerPtr = rando->m_Seed->m_Header;

            // If the player has the castle requirement set to Fused Shadows.
            if (headerPtr->castleRequirements == 1)
            {
                events::setSaveFileEventFlag(libtp::data::flags::BARRIER_GONE);
            }

            // If the player has the palace requirement set to Fused Shadows.
            if (headerPtr->palaceRequirements == 1)
            {
                events::setSaveFileEventFlag(libtp::data::flags::FIXED_THE_MIRROR_OF_TWILIGHT);
            }
        }
    }

    KEEP_FUNC void _02_secondMirrorShardItemFunc()
    {
        // Give player second mirror shard.
        libtp::tp::d_save::onCollectMirror(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                           '\x01');
    }

    KEEP_FUNC void _02_thirdMirrorShardItemFunc()
    {
        // Give player third mirror shard.
        libtp::tp::d_save::onCollectMirror(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                           '\x02');
    }

    KEEP_FUNC void _02_fourthMirrorShardItemFunc()
    {
        // Give player fourth mirror shard.
        libtp::tp::d_save::onCollectMirror(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect,
                                           '\x03');

        rando::Randomizer* rando = randomizer;
        if (randoIsEnabled(rando))
        {
            rando::Header* headerPtr = rando->m_Seed->m_Header;

            // If the player has the castle requirement set to Mirror Shards.
            if (headerPtr->castleRequirements == 2)
            {
                events::setSaveFileEventFlag(libtp::data::flags::BARRIER_GONE);
            }
            // If the player has the palace requirement set to Mirror Shards.
            if (headerPtr->palaceRequirements == 2)
            {
                events::setSaveFileEventFlag(libtp::data::flags::FIXED_THE_MIRROR_OF_TWILIGHT);
            }
        }
    }

    KEEP_FUNC void _02_endingBlowItemFunc()
    {
        // Learned Ending Blow.
        events::setSaveFileEventFlag(libtp::data::flags::ENDING_BLOW_UNLOCKED);
    }

    KEEP_FUNC void _02_shieldAttackItemFunc()
    {
        // Learned Shield Attack.
        events::setSaveFileEventFlag(libtp::data::flags::SHIELD_ATTACK_UNLOCKED);
    }

    KEEP_FUNC void _02_backSliceItemFunc()
    {
        // Learned Back Slice.
        events::setSaveFileEventFlag(libtp::data::flags::BACKSLICE_UNLOCKED);
    }

    KEEP_FUNC void _02_helmSplitterItemFunc()
    {
        // Learned Helm Splitter.
        events::setSaveFileEventFlag(libtp::data::flags::HELM_SPLITTER_UNLOCKED);
    }

    KEEP_FUNC void _02_mortalDrawItemFunc()
    {
        // Learned Mortal Draw.
        events::setSaveFileEventFlag(libtp::data::flags::MORTAL_DRAW_UNLOCKED);
    }

    KEEP_FUNC void _02_jumpStrikeItemFunc()
    {
        // Learned Jump Strike.
        events::setSaveFileEventFlag(libtp::data::flags::JUMP_STRIKE_UNLOCKED);
    }

    KEEP_FUNC void _02_greatSpinItemFunc()
    {
        // Learned Great Spin.
        events::setSaveFileEventFlag(libtp::data::flags::GREAT_SPIN_UNLOCKED);
    }

    KEEP_FUNC void _02_lanayruVesselItemFunc()
    {
        // Set the flag for lanayru twilight to be cleared.
        libtp::tp::d_save::onLightDropGetFlag(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.light_drop,
                                              '\x02');

        events::setSaveFileEventFlag(libtp::data::flags::MALO_MART_FUNDRAISING_STARTS); // Enable Malo Mart Donation
    }

    KEEP_FUNC void _02_foolishItemFunc()
    {
        // Failsafe: Make sure the count does not somehow exceed 100
        uint8_t* triggerCount = &rando::foolishItems.triggerCount;
        const uint32_t count = *triggerCount;
        if (count < 100)
        {
            *triggerCount = count + 1;
        }
    }

    KEEP_FUNC int32_t _02_firstSkybookItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Ancient_Sky_Book_First_Character);

        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_secondSkybookItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Ancient_Sky_Book_Second_Character);

        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_thirdSkybookItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Ancient_Sky_Book_Third_Character);

        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_fourthSkybookItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Ancient_Sky_Book_Fourth_Character);

        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_fifthSkybookItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Ancient_Sky_Book_Fifth_Character);

        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_bigWalletItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Big_Wallet);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_giantWalletItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Giant_Wallet);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_firstFusedShadowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Fused_Shadow_1);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_secondFusedShadowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Fused_Shadow_2);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_thirdFusedShadowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Fused_Shadow_3);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_secondMirrorShardItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Mirror_Piece_2);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_thirdMirrorShardItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Mirror_Piece_3);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_fourthMirrorShardItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Mirror_Piece_4);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_shadowCrystalItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Shadow_Crystal);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_endingBlowItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Ending_Blow);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_shieldAttackItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Shield_Attack);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_backSliceItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Back_Slice);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_helmSplitterItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Helm_Splitter);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_mortalDrawItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Mortal_Draw);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_jumpStrikeItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Jump_Strike);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_campSmallKeyItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(rando::customItems::Bulblin_Camp_Key);
        return static_cast<int32_t>(result);
    }

    KEEP_FUNC int32_t _02_gateKeysItemGetCheck()
    {
        bool result = libtp::tp::d_com_inf_game::dComIfGs_isItemFirstBit(libtp::data::items::Gate_Keys);
        return static_cast<int32_t>(result);
    }
} // namespace mod::game_patch