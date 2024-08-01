#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cinttypes>

#include "item_wheel_menu.h"
#include "main.h"
#include "tp/resource.h"
#include "data/stages.h"
#include "tp/d_meter_HIO.h"
#include "data/items.h"
#include "tp/m_do_controller_pad.h"
#include "events.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_a_alink.h"
#include "tp/d_msg_class.h"
#include "data/flags.h"

namespace mod::item_wheel_menu
{
    using namespace libtp::data::stage;

    ItemWheelMenuData itemWheelMenuData;
    bool ringDrawnThisFrame = false;
    bool displayMenu = false;

    KEEP_VAR void (*return_dMenuRing__create)(void* dMenuRing) = nullptr;
    KEEP_VAR void (*return_dMenuRing__delete)(void* dMenuRing) = nullptr;
    KEEP_VAR void (*return_dMenuRing__draw)(void* dMenuRing) = nullptr;

    // Set up an array to hold each area's color id
    const uint8_t areaColorIds[] = {MSG_COLOR_GREEN_HEX,
                                    MSG_COLOR_RED_HEX,
                                    CUSTOM_MSG_COLOR_BLUE_HEX,
                                    MSG_COLOR_ORANGE_HEX,
                                    MSG_COLOR_LIGHT_BLUE_HEX,
                                    CUSTOM_MSG_COLOR_DARK_GREEN_HEX,
                                    MSG_COLOR_YELLOW_HEX,
                                    MSG_COLOR_PURPLE_HEX,
                                    CUSTOM_MSG_COLOR_SILVER_HEX,
                                    MSG_COLOR_GREEN_HEX,
                                    MSG_COLOR_ORANGE_HEX};

    // Set up an array with all of the area node ids that small keys are tracked
    const AreaNodesID smallKeyAreaNodes[] = {AreaNodesID::Forest_Temple,
                                             AreaNodesID::Goron_Mines,
                                             AreaNodesID::Lakebed_Temple,
                                             AreaNodesID::Arbiters_Grounds,
                                             AreaNodesID::Snowpeak_Ruins,
                                             AreaNodesID::Temple_of_Time,
                                             AreaNodesID::City_in_the_Sky,
                                             AreaNodesID::Palace_of_Twilight,
                                             AreaNodesID::Hyrule_Castle,
                                             AreaNodesID::Faron,
                                             AreaNodesID::Gerudo_Desert};

    void setHUDButtonsAlpha(bool menuIsDisplayed)
    {
        float* mMainHUDButtonsAlpha = &libtp::tp::d_meter_hio::g_drawHIO.mMainHUDButtonsAlpha;
        if (!menuIsDisplayed)
        {
            // Display the HUD
            *mMainHUDButtonsAlpha = 1.f;
        }
        else
        {
            // Don't display the HUD
            *mMainHUDButtonsAlpha = 0.f;
        }
    }

    KEEP_FUNC void handle_dMenuRing__create(void* dMenuRing)
    {
        // Handle whether the controller buttons should be displayed or not
        setHUDButtonsAlpha(displayMenu);

        // Call the original function
        return_dMenuRing__create(dMenuRing);
    }

    KEEP_FUNC void handle_dMenuRing__delete(void* dMenuRing)
    {
        (void)dMenuRing;

        // Handle whether the controller buttons should be displayed or not
        // Hardcode false since the ring isn't being drawn anymore
        setHUDButtonsAlpha(false);

        // If the item wheel is being closed, we also want to close the menu. This way, if the player forgets to close it or
        // cannot remember how, closing the item wheel will also close the menu.
        displayMenu = false;

        // dMenuRing__delete is an empty function, so don't need to call the original function
    }

    KEEP_FUNC void handle_dMenuRing__draw(void* dMenuRing)
    {
        using namespace libtp::tp::m_do_controller_pad;
        using namespace libtp::data::items;

        const ItemWheelMenuData* data = &itemWheelMenuData;

        // Failsafe: If textData is not defined, then none of the strings are loaded
        if (!data->textData)
        {
            // Call the original function before returning
            return return_dMenuRing__draw(dMenuRing);
        }

        // Check if the menu should be drawn
        bool shouldDisplayMenu = displayMenu;

        // If the ring was already drawn this frame, then dont check the buttons
        if (!ringDrawnThisFrame)
        {
            // Check if either Start or Z were pressed this frame
            if (checkButtonsPressedThisFrame(PadInputs::Button_Start | PadInputs::Button_Z))
            {
                shouldDisplayMenu = !shouldDisplayMenu;
                displayMenu = shouldDisplayMenu;
                ringDrawnThisFrame = true;

                // Handle whether the controller buttons should be displayed or not
                setHUDButtonsAlpha(shouldDisplayMenu);
            }
        }

        const ItemWheelMenuStrings* strings = &data->strings;
        const ItemWheelMenuOffsets* offsets = &data->offsets;

        // Get the current position of the ring
        const float* ringPos = reinterpret_cast<float*>(reinterpret_cast<uint32_t>(dMenuRing) + 0x568);

        const int32_t ringPosX = static_cast<int32_t>(ringPos[0]);
        const int32_t ringPosY = static_cast<int32_t>(ringPos[1]);

        // Get the size of the text
        constexpr float textSize = 16.f;

        // Get the increment amount for manual newlines
        constexpr int32_t increment = 16;

        // Draw the help text stating to press Start or Z to show the menu
        constexpr uint32_t mainTextColor = 0xFFFFFFFF; // White

        // Only draw the help text if the menu is not displayed
        if (!shouldDisplayMenu)
        {
            constexpr int32_t helpTextPosXOffset = 465;
            constexpr int32_t helpTextPosYOffset = 157;

            events::drawText(strings->helpText,
                             ringPosX + helpTextPosXOffset,
                             ringPosY + helpTextPosYOffset,
                             mainTextColor,
                             true,
                             textSize);
        }

        // Call the original function now, as everything else should be drawn on top of the vanilla stuff
        return_dMenuRing__draw(dMenuRing);

        // Everything after this point is only drawn in the menu
        if (!shouldDisplayMenu)
        {
            return;
        }

        // Draw the window
        constexpr int32_t windowPosXOffset = 40;
        constexpr int32_t windowPosYOffset = 34;
        constexpr int32_t windowWidth = 528;
        constexpr int32_t windowHeight = 380;
        constexpr uint32_t windowColor = 0x000000FF;
        events::drawWindow(ringPosX + windowPosXOffset, ringPosY + windowPosYOffset, windowWidth, windowHeight, windowColor);

        // Create a generic buffer to use for string formatting
        char buf[64];

        // Set up an auto function for getting Yes/No text
        auto getYesNoText = [&](bool flag)
        {
            if (flag)
            {
                return strings->yes;
            }
            else
            {
                return strings->no;
            }
        };

        // Get the current seed
        bool seedIsLoaded = false;
        rando::Randomizer* rando = randomizer;

        if (randoIsEnabled(rando))
        {
            rando::MinSeedInfo* minSeedInfo = rando->m_SeedInfo.minSeedInfo;
            if (minSeedInfo)
            {
                snprintf(buf, sizeof(buf), "%s: %s", strings->seedIsLoaded, minSeedInfo->fileName);
                seedIsLoaded = true;
            }
        }

        const char* seedText;
        if (seedIsLoaded)
        {
            seedText = buf;
        }
        else
        {
            seedText = strings->seedIsNotLoaded;
        }

        // Draw the current seed
        constexpr int32_t currentSeedPosXOffset = windowPosXOffset + 7;
        constexpr int32_t currentSeedPosYOffset = windowPosYOffset + 20;

        events::drawText(seedText, ringPosX + currentSeedPosXOffset, ringPosY + currentSeedPosYOffset, mainTextColor, textSize);

        // Draw the main text for the fused shadows and mirror shards
        constexpr int32_t shadowsAndShardsMainPosXOffset = currentSeedPosXOffset;
        constexpr int32_t shadowsAndShardsMainPosYOffset = currentSeedPosYOffset + 40;

        events::drawText(strings->shadowsShards,
                         ringPosX + shadowsAndShardsMainPosXOffset,
                         ringPosY + shadowsAndShardsMainPosYOffset,
                         mainTextColor,
                         textSize);

        // Get the counts for the fused shadows and mirror shards
        libtp::tp::d_save::dSv_player_collect_c* playerCollectPtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect;

        uint32_t shadowsCount = 0;
        uint32_t shardsCount = 0;
        const uint32_t collectedShadows = playerCollectPtr->crystal;
        const uint32_t collectedShards = playerCollectPtr->mirror;

        for (uint32_t b = 5; b < 8; b++)
        {
            if ((collectedShadows << b) & 0x80)
            {
                shadowsCount++;
            }
        }

        for (uint32_t b = 4; b < 8; b++)
        {
            if ((collectedShards << b) & 0x80)
            {
                shardsCount++;
            }
        }

        snprintf(buf, sizeof(buf), "%" PRIu32 "/3\n%" PRIu32 "/4", shadowsCount, shardsCount);

        // Draw the counts for the fused shadows and mirror shards
        const int32_t shadowsAndShardsCountsPosXOffset = shadowsAndShardsMainPosXOffset + offsets->shadowsShardsOffset;
        constexpr int32_t shadowsAndShardsCountsPosYOffset = shadowsAndShardsMainPosYOffset;

        events::drawText(buf,
                         ringPosX + shadowsAndShardsCountsPosXOffset,
                         ringPosY + shadowsAndShardsCountsPosYOffset,
                         mainTextColor,
                         textSize);

        // Draw the text for the pumpkin
        const int32_t pumpkinPosXOffset = shadowsAndShardsCountsPosXOffset + offsets->pumpkinOffset;
        constexpr int32_t pumpkinPosYOffset = shadowsAndShardsCountsPosYOffset;

        events::drawText(strings->pumpkin, ringPosX + pumpkinPosXOffset, ringPosY + pumpkinPosYOffset, mainTextColor, textSize);

        // Get the offset for the pumpkin value
        const bool hasPumpkin = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::TOLD_YETA_ABOUT_PUMPKIN);
        uint32_t pumpkinValueOffset;

        if (hasPumpkin)
        {
            pumpkinValueOffset = offsets->pumpkinYesOffset;
        }
        else
        {
            pumpkinValueOffset = offsets->pumpkinNoOffset;
        }

        // Draw the value for the pumpkin
        events::drawText(getYesNoText(hasPumpkin),
                         ringPosX + pumpkinPosXOffset + pumpkinValueOffset,
                         ringPosY + pumpkinPosYOffset + increment,
                         mainTextColor,
                         textSize);

        // Draw the text for the cheese
        const int32_t cheesePosXOffset = pumpkinPosXOffset + offsets->cheeseOffset;
        constexpr int32_t cheesePosYOffset = pumpkinPosYOffset;
        events::drawText(strings->cheese, ringPosX + cheesePosXOffset, ringPosY + cheesePosYOffset, mainTextColor, textSize);

        // Get the offset for the cheese value
        const bool hasCheese = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::TOLD_YETA_ABOUT_CHEESE);
        uint32_t cheeseValueOffset;

        if (hasCheese)
        {
            cheeseValueOffset = offsets->cheeseYesOffset;
        }
        else
        {
            cheeseValueOffset = offsets->cheeseNoOffset;
        }

        // Draw the value for the cheese
        events::drawText(getYesNoText(hasCheese),
                         ringPosX + cheesePosXOffset + cheeseValueOffset,
                         ringPosY + cheesePosYOffset + increment,
                         mainTextColor,
                         textSize);

        // Draw the text for the gate keys
        const int32_t gateKeysPosXOffset = cheesePosXOffset + offsets->gateKeysOffset;
        constexpr int32_t gateKeysPosYOffset = cheesePosYOffset;

        events::drawText(strings->gateKeys,
                         ringPosX + gateKeysPosXOffset,
                         ringPosY + gateKeysPosYOffset,
                         mainTextColor,
                         textSize);

        // Get the offset for the gate keys value
        const bool hasGateKeys = events::haveItem(libtp::data::items::Gate_Keys);
        uint32_t gateKeysValueOffset;

        if (hasGateKeys)
        {
            gateKeysValueOffset = offsets->gateKeysYesOffset;
        }
        else
        {
            gateKeysValueOffset = offsets->gateKeysNoOffset;
        }

        // Draw the value for the gate keys
        events::drawText(getYesNoText(hasGateKeys),
                         ringPosX + gateKeysPosXOffset + gateKeysValueOffset,
                         ringPosY + gateKeysPosYOffset + increment,
                         mainTextColor,
                         textSize);

        // Draw the header text for the areas, small keys, big keys, dungeon maps, and compasses
        // Areas
        constexpr int32_t areasMainPosXOffset = shadowsAndShardsMainPosXOffset;
        constexpr int32_t areasMainPosYOffset = shadowsAndShardsMainPosYOffset + 60;

        events::drawText(strings->areas,
                         ringPosX + areasMainPosXOffset,
                         ringPosY + areasMainPosYOffset,
                         mainTextColor,
                         textSize);

        // Small keys
        const int32_t smallKeysMainPosXOffset = areasMainPosXOffset + offsets->headerSmallKeysOffset;
        constexpr int32_t smallKeysMainPosYOffset = areasMainPosYOffset;

        events::drawText(strings->smallKeys,
                         ringPosX + smallKeysMainPosXOffset,
                         ringPosY + smallKeysMainPosYOffset,
                         mainTextColor,
                         textSize);

        // Big keys
        const int32_t bigKeysMainPosXOffset = smallKeysMainPosXOffset + offsets->headerBigKeysOffset;
        constexpr int32_t bigKeysMainPosYOffset = smallKeysMainPosYOffset;

        events::drawText(strings->bigKeys,
                         ringPosX + bigKeysMainPosXOffset,
                         ringPosY + bigKeysMainPosYOffset,
                         mainTextColor,
                         textSize);

        // Dungeon maps
        const int32_t dungeonMapsMainPosXOffset = bigKeysMainPosXOffset + offsets->headerMapsOffset;
        constexpr int32_t dungeonMapsMainPosYOffset = bigKeysMainPosYOffset;

        events::drawText(strings->maps,
                         ringPosX + dungeonMapsMainPosXOffset,
                         ringPosY + dungeonMapsMainPosYOffset,
                         mainTextColor,
                         textSize);

        // Compasses
        const int32_t compassesMainPosXOffset = dungeonMapsMainPosXOffset + offsets->headerCompassesOffset;
        constexpr int32_t compassesMainPosYOffset = dungeonMapsMainPosYOffset;

        events::drawText(strings->compasses,
                         ringPosX + compassesMainPosXOffset,
                         ringPosY + compassesMainPosYOffset,
                         mainTextColor,
                         textSize);

        // Draw the areas, small key counts, big key counts, dungeon map counts, and compass counts
        // Areas position
        constexpr int32_t areasPosXOffset = areasMainPosXOffset;
        int32_t areasPosYOffset = areasMainPosYOffset + increment;

        // Check if the small key header text uses two lines, as all languages that use two lines will have two lines for small
        // keys
        if (strchr(strings->smallKeys, '\n'))
        {
            areasPosYOffset += increment;
        }

        // Small key counts position
        const int32_t smallKeyCountsPosXOffset = smallKeysMainPosXOffset + offsets->valuesSmallKeysOffset;
        // constexpr int32_t smallKeyCountsPosYOffset = areasPosYOffset;

        // Big key counts position
        const int32_t bigKeyCountsPosXOffset = bigKeysMainPosXOffset;
        // constexpr int32_t bigKeyCountsPosYOffset = areasPosYOffset;

        // Dungeon map counts position
        const int32_t dungeonMapCountsPosXOffset = dungeonMapsMainPosXOffset;
        // constexpr int32_t dungeonMapCountsPosYOffset = areasPosYOffset;

        // Compass counts position
        const int32_t compassCountsPosXOffset = compassesMainPosXOffset;
        // constexpr int32_t compassCountsPosYOffset = areasPosYOffset;

        // Get the node id for the current area
        const int32_t currentAreaNodeId = events::getCurrentAreaNodeId();

        // Temporary variable to keep track of current y coordinate
        int32_t tempPosY = ringPosY + areasPosYOffset;

        const char* const* areas = strings->areasBeingTracked;
        const uint8_t* areaColorsPtr = &areaColorIds[0];

        for (uint32_t i = 0; i < TrackedAreas::TRACKED_AREAS_END; i++)
        {
            const uint32_t currentColor = libtp::tp::d_msg_class::getFontGCColorTable(areaColorsPtr[i], 0);

            // Draw the current area
            events::drawText(areas[i], ringPosX + areasPosXOffset, tempPosY, currentColor, textSize);

            // Make sure the node id is valid
            if (currentAreaNodeId >= 0)
            {
                // Get the small key count for the current area
                const uint8_t* memoryFlags =
                    events::getNodeMemoryFlags(smallKeyAreaNodes[i], static_cast<AreaNodesID>(currentAreaNodeId));

                const uint32_t smallKeyCount = memoryFlags[0x1C];
                const uint32_t dungeonBits = memoryFlags[0x1D];

                snprintf(buf, sizeof(buf), "%" PRIu32, smallKeyCount);

                // Draw the small key count for the current area
                events::drawText(buf, ringPosX + smallKeyCountsPosXOffset, tempPosY, currentColor, textSize);

                // Do not show big keys, dungeon maps, or compasses for Faron Woods or Bulblin Camp
                if (i < TrackedAreas::FARON_WOODS)
                {
                    // Get the big key text
                    // Goron Mines has its big key split into 3 parts
                    const bool hasBigKey = dungeonBits & 0x4;
                    int32_t bigKeyValueOffset;
                    const char* bigKeyText;

                    if (i == TrackedAreas::GORON_MINES)
                    {
                        bigKeyValueOffset = static_cast<int32_t>(offsets->valuesBigKeysMinesOffset);
                        uint32_t bigKeyCount = 0;

                        // If the big key dungeon flag is set, then assume all 3 pieces have been obtained
                        if (hasBigKey)
                        {
                            bigKeyCount = 3;
                        }
                        else
                        {
                            // Only need to track the first two key shards
                            if (events::haveItem(Item::Key_Shard_1))
                            {
                                bigKeyCount++;
                            }

                            if (events::haveItem(Item::Key_Shard_2))
                            {
                                bigKeyCount++;
                            }
                        }

                        snprintf(buf, sizeof(buf), "%" PRIu32, bigKeyCount);
                        bigKeyText = buf;
                    }
                    else
                    {
                        if (hasBigKey)
                        {
                            bigKeyValueOffset = offsets->valuesBigKeysYesOffset;
                        }
                        else
                        {
                            bigKeyValueOffset = offsets->valuesBigKeysNoOffset;
                        }

                        bigKeyText = getYesNoText(hasBigKey);
                    }

                    // Draw the big key text
                    events::drawText(bigKeyText,
                                     ringPosX + bigKeyCountsPosXOffset + bigKeyValueOffset,
                                     tempPosY,
                                     currentColor,
                                     textSize);

                    // Get the value for the dungeon map
                    const bool hasMap = dungeonBits & 0x1;
                    uint32_t mapValueOffset;

                    if (hasMap)
                    {
                        mapValueOffset = offsets->valuesMapsYesOffset;
                    }
                    else
                    {
                        mapValueOffset = offsets->valuesMapsNoOffset;
                    }

                    // Draw the dungeon map count
                    events::drawText(getYesNoText(hasMap),
                                     ringPosX + dungeonMapCountsPosXOffset + mapValueOffset,
                                     tempPosY,
                                     currentColor,
                                     textSize);

                    // Get the value for the compass
                    const bool hasCompass = dungeonBits & 0x2;
                    uint32_t compassValueOffset;

                    if (hasCompass)
                    {
                        compassValueOffset = offsets->valuesCompassesYesOffset;
                    }
                    else
                    {
                        compassValueOffset = offsets->valuesCompassesNoOffset;
                    }

                    // Draw the compass count
                    events::drawText(getYesNoText(hasCompass),
                                     ringPosX + compassCountsPosXOffset + compassValueOffset,
                                     tempPosY,
                                     currentColor,
                                     textSize);
                }
            }

            tempPosY += increment;
        }
    }
} // namespace mod::item_wheel_menu