#include <cstdint>
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

namespace mod::item_wheel_menu
{
    using namespace libtp::data::stage;

    bool ringDrawnThisFrame = false;
    bool displayMenu = false;

    KEEP_VAR void ( *return_dMenuRing__create )( void* dMenuRing ) = nullptr;
    KEEP_VAR void ( *return_dMenuRing__delete )( void* dMenuRing ) = nullptr;
    KEEP_VAR void ( *return_dMenuRing__draw )( void* dMenuRing ) = nullptr;

    // Set up an array to hold each area, as they will use different colors
    const char* areas[] = { "Forest Temple",
                            "Goron Mines",
                            "Lakebed Temple",
                            "Arbiter's Grounds",
                            "Snowpeak Ruins",
                            "Temple of Time",
                            "City in the Sky",
                            "Palace of Twilight",
                            "Hyrule Castle",
                            "Faron Woods",
                            "Bublin Camp" };

    // Set up an array to hold each area's color id
    const uint8_t areaColorIds[] = { MSG_COLOR_GREEN_HEX,
                                     MSG_COLOR_RED_HEX,
                                     CUSTOM_MSG_COLOR_BLUE_HEX,
                                     MSG_COLOR_ORANGE_HEX,
                                     MSG_COLOR_LIGHT_BLUE_HEX,
                                     CUSTOM_MSG_COLOR_DARK_GREEN_HEX,
                                     MSG_COLOR_YELLOW_HEX,
                                     MSG_COLOR_PURPLE_HEX,
                                     CUSTOM_MSG_COLOR_SILVER_HEX,
                                     MSG_COLOR_GREEN_HEX,
                                     MSG_COLOR_ORANGE_HEX };

    // Set up an array with all of the area node ids that small keys are tracked
    const AreaNodesID smallKeyAreaNodes[] = { AreaNodesID::Forest_Temple,
                                              AreaNodesID::Goron_Mines,
                                              AreaNodesID::Lakebed_Temple,
                                              AreaNodesID::Arbiters_Grounds,
                                              AreaNodesID::Snowpeak_Ruins,
                                              AreaNodesID::Temple_of_Time,
                                              AreaNodesID::City_in_the_Sky,
                                              AreaNodesID::Palace_of_Twilight,
                                              AreaNodesID::Hyrule_Castle,
                                              AreaNodesID::Faron,
                                              AreaNodesID::Gerudo_Desert };

    void setHUDOpacity( bool menuIsDisplayed )
    {
        float* mHUDAlpha = &libtp::tp::d_meter_hio::g_drawHIO.mHUDAlpha;
        if ( !menuIsDisplayed )
        {
            // Display the HUD
            *mHUDAlpha = 1.f;
        }
        else
        {
            // Don't display the HUD
            *mHUDAlpha = 0.f;
        }
    }

    KEEP_FUNC void handle_dMenuRing__create( void* dMenuRing )
    {
        // Handle whether the controller buttons should be displayed or not
        setHUDOpacity( displayMenu );

        // Call the original function
        return_dMenuRing__create( dMenuRing );
    }

    KEEP_FUNC void handle_dMenuRing__delete( void* dMenuRing )
    {
        // Handle whether the controller buttons should be displayed or not
        // Hardcode false since the ring isn't being drawn anymore
        setHUDOpacity( false );

        // dMenuRing__delete is an empty function, so don't need to call the original function
    }

    KEEP_FUNC void handle_dMenuRing__draw( void* dMenuRing )
    {
        using namespace libtp::tp::m_do_controller_pad;
        using namespace libtp::data::items;

        // Get the current position of the ring
        const float* ringPos = reinterpret_cast<float*>( reinterpret_cast<uint32_t>( dMenuRing ) + 0x568 );

        const int32_t ringPosX = static_cast<int32_t>( ringPos[0] );
        const int32_t ringPosY = static_cast<int32_t>( ringPos[1] );

        // Get the size of the text
        constexpr float textSize = 16.f;

        // Get the increment amount for manual newlines
        constexpr int32_t increment = 16;

        // Draw the help text stating to press Start or Z to show the menu
        constexpr int32_t helpTextPosXOffset = 465;
        constexpr int32_t helpTextPosYOffset = 157;
        constexpr uint32_t mainTextColor = 0xFFFFFFFF;     // White

        events::drawText( "Press Start\nor Z to\ntoggle\nadditional\ndata",
                          ringPosX + helpTextPosXOffset,
                          ringPosY + helpTextPosYOffset,
                          mainTextColor,
                          textSize );

        // Call the original function now, as everything else should be drawn on top of the vanilla stuff
        return_dMenuRing__draw( dMenuRing );

        // Check if the menu should be drawn
        bool shouldDisplayMenu = displayMenu;

        // If the ring was already drawn this frame, then dont check the buttons
        if ( !ringDrawnThisFrame )
        {
            // Check if either Start or Z is pressed
            if ( cpadInfo.buttonInputTrg & ( PadInputs::Button_Start | PadInputs::Button_Z ) )
            {
                shouldDisplayMenu = !shouldDisplayMenu;
                displayMenu = shouldDisplayMenu;
                ringDrawnThisFrame = true;

                // Handle whether the controller buttons should be displayed or not
                setHUDOpacity( shouldDisplayMenu );
            }
        }

        if ( !shouldDisplayMenu )
        {
            return;
        }

        // Draw the window
        constexpr int32_t windowPosXOffset = 40;
        constexpr int32_t windowPosYOffset = 34;
        constexpr int32_t windowWidth = 528;
        constexpr int32_t windowHeight = 380;
        constexpr uint32_t windowColor = 0x000000FF;

        events::drawWindow( ringPosX + windowPosXOffset, ringPosY + windowPosYOffset, windowWidth, windowHeight, windowColor );

        // Create a generic buffer to use for string formatting
        char buf[32];

        // Set up an auto function for getting Yes or No text
        auto getYesNoText = []( bool flag ) {
            if ( flag )
            {
                return "Yes";
            }
            else
            {
                return "No";
            }
        };

        // Get the current seed
        bool seedIsLoaded = false;
        if ( randoIsEnabled( randomizer ) )
        {
            rando::SeedInfo* seedInfo = randomizer->m_SeedInfo;
            if ( seedInfo )
            {
                snprintf( buf, sizeof( buf ), "Seed: 0x%016" PRIx64, seedInfo->header.seed );
                seedIsLoaded = true;
            }
        }

        const char* seedText;
        if ( seedIsLoaded )
        {
            seedText = buf;
        }
        else
        {
            seedText = "No seed is currently loaded";
        }

        // Draw the current seed
        constexpr int32_t currentSeedPosXOffset = windowPosXOffset + 15;
        constexpr int32_t currentSeedPosYOffset = windowPosYOffset + 28;

        events::drawText( seedText,
                          ringPosX + currentSeedPosXOffset,
                          ringPosY + currentSeedPosYOffset,
                          mainTextColor,
                          textSize );

        // Draw the main text for the fused shadows and mirror shards
        constexpr int32_t shadowsAndShardsMainPosXOffset = currentSeedPosXOffset;
        constexpr int32_t shadowsAndShardsMainPosYOffset = currentSeedPosYOffset + 40;

        events::drawText( "Fused Shadows\nMirror Shards",
                          ringPosX + shadowsAndShardsMainPosXOffset,
                          ringPosY + shadowsAndShardsMainPosYOffset,
                          mainTextColor,
                          textSize );

        // Get the counts for the fused shadows and mirror shards
        libtp::tp::d_save::dSv_player_collect_c* playerCollectPtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_collect;

        uint32_t shadowsCount = 0;
        uint32_t shardsCount = 0;
        uint8_t collectedShadows = playerCollectPtr->crystal;
        uint8_t collectedShards = playerCollectPtr->mirror;

        for ( uint32_t b = 5; b < 8; b++ )
        {
            if ( ( collectedShadows << b ) & 0x80 )
            {
                shadowsCount++;
            }
        }
        for ( uint32_t b = 4; b < 7; b++ )
        {
            if ( ( collectedShards << b ) & 0x80 )
            {
                shardsCount++;
            }
        }

        snprintf( buf, sizeof( buf ), "%" PRIu32 "/3\n%" PRIu32 "/3", shadowsCount, shardsCount );

        // Draw the counts for the fused shadows and mirror shards
        constexpr int32_t shadowsAndShardsCountsPosXOffset = shadowsAndShardsMainPosXOffset + 135;
        constexpr int32_t shadowsAndShardsCountsPosYOffset = shadowsAndShardsMainPosYOffset;

        events::drawText( buf,
                          ringPosX + shadowsAndShardsCountsPosXOffset,
                          ringPosY + shadowsAndShardsCountsPosYOffset,
                          mainTextColor,
                          textSize );

        // Get the text for the pumpkin
        snprintf( buf, sizeof( buf ), "Pumpkin\n%s", getYesNoText( events::haveItem( Item::Ordon_Pumpkin ) ) );

        // Draw the text for the pumpkin
        constexpr int32_t pumpkinPosXOffset = shadowsAndShardsCountsPosXOffset + 60;
        constexpr int32_t pumpkinPosYOffset = shadowsAndShardsCountsPosYOffset;

        events::drawText( buf, ringPosX + pumpkinPosXOffset, ringPosY + pumpkinPosYOffset, mainTextColor, textSize );

        // Get the text for the cheese
        snprintf( buf, sizeof( buf ), "Cheese\n%s", getYesNoText( events::haveItem( Item::Ordon_Goat_Cheese ) ) );

        // Draw the text for the cheese
        constexpr int32_t cheesePosXOffset = pumpkinPosXOffset + 90;
        constexpr int32_t cheesePosYOffset = pumpkinPosYOffset;

        events::drawText( buf, ringPosX + cheesePosXOffset, ringPosY + cheesePosYOffset, mainTextColor, textSize );

        // Get the text for the gate keys
        snprintf( buf, sizeof( buf ), "Gate Keys\n%s", getYesNoText( libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x810 ) ) );

        // Draw the text for the cheese
        constexpr int32_t gateKeysPosXOffset = cheesePosXOffset + 80;
        constexpr int32_t gateKeysPosYOffset = cheesePosYOffset;

        events::drawText( buf, ringPosX + gateKeysPosXOffset, ringPosY + gateKeysPosYOffset, mainTextColor, textSize );

        // Draw the header text for the areas being tracked, small keys, big keys, dungeon maps, and compasses
        // Areas being tracked
        constexpr int32_t areasMainPosXOffset = shadowsAndShardsMainPosXOffset;
        constexpr int32_t areasMainPosYOffset = shadowsAndShardsMainPosYOffset + 60;

        events::drawText( "Areas", ringPosX + areasMainPosXOffset, ringPosY + areasMainPosYOffset, mainTextColor, textSize );

        // Small keys
        constexpr int32_t smallKeysMainPosXOffset = areasMainPosXOffset + 155;
        constexpr int32_t smallKeysMainPosYOffset = areasMainPosYOffset;

        events::drawText( "Small\nKeys",
                          ringPosX + smallKeysMainPosXOffset,
                          ringPosY + smallKeysMainPosYOffset,
                          mainTextColor,
                          textSize );

        // Big keys
        constexpr int32_t bigKeysMainPosXOffset = smallKeysMainPosXOffset + 70;
        constexpr int32_t bigKeysMainPosYOffset = smallKeysMainPosYOffset;

        events::drawText( "Big\nKeys",
                          ringPosX + bigKeysMainPosXOffset,
                          ringPosY + bigKeysMainPosYOffset,
                          mainTextColor,
                          textSize );

        // Dungeon maps
        constexpr int32_t dungeonMapsMainPosXOffset = bigKeysMainPosXOffset + 70;
        constexpr int32_t dungeonMapsMainPosYOffset = bigKeysMainPosYOffset;

        events::drawText( "Maps",
                          ringPosX + dungeonMapsMainPosXOffset,
                          ringPosY + dungeonMapsMainPosYOffset,
                          mainTextColor,
                          textSize );

        // Compasses
        constexpr int32_t compassesMainPosXOffset = dungeonMapsMainPosXOffset + 70;
        constexpr int32_t compassesMainPosYOffset = dungeonMapsMainPosYOffset;

        events::drawText( "Compasses",
                          ringPosX + compassesMainPosXOffset,
                          ringPosY + compassesMainPosYOffset,
                          mainTextColor,
                          textSize );

        // Draw the areas, small key counts, big key counts, dungeon map counts, and compass counts
        // Areas position
        constexpr int32_t areasPosXOffset = areasMainPosXOffset;
        constexpr int32_t areasPosYOffset = areasMainPosYOffset + ( increment * 2 );

        // Small key counts position
        constexpr int32_t smallKeyCountsPosXOffset = smallKeysMainPosXOffset + 6;
        // constexpr int32_t smallKeyCountsPosYOffset = areasPosYOffset;

        // Big key counts position
        constexpr int32_t bigKeyCountsPosXOffset = bigKeysMainPosXOffset + 5;
        // constexpr int32_t bigKeyCountsPosYOffset = areasPosYOffset;

        // Dungeon map counts position
        constexpr int32_t dungeonMapCountsPosXOffset = dungeonMapsMainPosXOffset + 6;
        // constexpr int32_t dungeonMapCountsPosYOffset = areasPosYOffset;

        // Compass counts position
        constexpr int32_t compassCountsPosXOffset = compassesMainPosXOffset + 30;
        // constexpr int32_t compassCountsPosYOffset = areasPosYOffset;

        // Get the node id for the current area
        int32_t currentAreaNodeId = events::getCurrentAreaNodeId();

        // Temporary variable to keep track of current y coordinate
        int32_t tempPosY = ringPosY + areasPosYOffset;

        uint32_t loopCount = sizeof( areas ) / sizeof( areas[0] );
        for ( uint32_t i = 0; i < loopCount; i++ )
        {
            uint32_t currentColor = libtp::tp::d_msg_class::getFontGCColorTable( areaColorIds[i], 0 );

            // Draw the current area
            events::drawText( areas[i], ringPosX + areasPosXOffset, tempPosY, currentColor, textSize );

            // Make sure the node id is valid
            if ( currentAreaNodeId >= 0 )
            {
                // Get the small key count for the current area
                uint8_t* memoryFlags =
                    events::getNodeMemoryFlags( smallKeyAreaNodes[i], static_cast<AreaNodesID>( currentAreaNodeId ) );

                uint8_t smallKeyCount = memoryFlags[0x1C];
                uint8_t dungeonBits = memoryFlags[0x1D];

                snprintf( buf, sizeof( buf ), "%" PRIu8, smallKeyCount );

                // Draw the small key count for the current area
                events::drawText( buf, ringPosX + smallKeyCountsPosXOffset, tempPosY, currentColor, textSize );

                // Do not show big keys, dungeon maps, or compasses for Faron Woods or Bublin Camp
                if ( i < TrackedAreas::FARON_WOODS )
                {
                    // Draw the big key text
                    // Goron Mines has its big key split into 3 parts
                    int32_t bigKeyPosXIncrement = 0;
                    const char* bigKeyText;

                    if ( i == TrackedAreas::GORON_MINES )
                    {
                        bigKeyPosXIncrement = 8;
                        uint32_t bigKeyCount = 0;

                        // If the big key dungeon flag is set, then assume all 3 pieces have been obtained
                        if ( dungeonBits & 0x4 )
                        {
                            bigKeyCount = 3;
                        }
                        else
                        {
                            // Only need to track the first two key shards
                            if ( events::haveItem( Item::Key_Shard_1 ) )
                            {
                                bigKeyCount++;
                            }
                            if ( events::haveItem( Item::Key_Shard_2 ) )
                            {
                                bigKeyCount++;
                            }
                        }

                        snprintf( buf, sizeof( buf ), "%" PRIu32, bigKeyCount );

                        bigKeyText = buf;
                    }
                    else
                    {
                        bigKeyText = getYesNoText( dungeonBits & 0x4 );
                    }

                    events::drawText( bigKeyText,
                                      ringPosX + bigKeyCountsPosXOffset + bigKeyPosXIncrement,
                                      tempPosY,
                                      currentColor,
                                      textSize );

                    // Draw the dungeon map count
                    events::drawText( getYesNoText( dungeonBits & 0x1 ),
                                      ringPosX + dungeonMapCountsPosXOffset,
                                      tempPosY,
                                      currentColor,
                                      textSize );

                    // Draw the compass count
                    events::drawText( getYesNoText( dungeonBits & 0x2 ),
                                      ringPosX + compassCountsPosXOffset,
                                      tempPosY,
                                      currentColor,
                                      textSize );
                }
            }

            tempPosY += increment;
        }
    }
}     // namespace mod::item_wheel_menu