#include "game_patch/game_patch.h"
#include "main.h"
#include "data/stages.h"
#include "events.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/d_save.h"
#include "data/flags.h"
#include "rando/customItems.h"

namespace mod::game_patch
{
    int32_t getCurrentStageId()
    {
        const auto stagesPtr = &libtp::data::stage::allStages[0];
        constexpr int32_t loopCount = sizeof(libtp::data::stage::allStages) / sizeof(libtp::data::stage::allStages[0]);

        for (int32_t i = 0; i < loopCount; i++)
        {
            if (libtp::tp::d_a_alink::checkStageName(stagesPtr[i]))
            {
                return i;
            }
        }

        // Didn't find the current stage for some reason
        return -1;
    }

    KEEP_FUNC int32_t _01_getLayerNo(const char* stageName, int32_t roomId, int32_t layerOverride)
    {
        using namespace libtp::data;
        using namespace libtp::data::flags;

        int32_t chosenLayer;
        int32_t stageID;
        bool darkIsClear;
        bool condition;

        libtp::tp::d_save::dSv_player_status_b_c* playerStatusBPtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b;

        chosenLayer = layerOverride;
        stageID = getCurrentStageId();

        if (layerOverride < 0)
        {
            condition = libtp::tp::d_kankyo::dKy_darkworld_stage_check(stageName, roomId);
            if (condition == true)
            {
                chosenLayer = stage::TwilightStateIDs::Default_Twilight_State;
            }

            if (chosenLayer < 0xD)
            {
                switch (stageID)
                {
                    case stage::StageIDs::Snowpeak_Ruins:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(SNOWPEAK_RUINS_CLEARED); // Snowpeak Ruins Completed

                        if (condition)
                        {
                            chosenLayer = stage::SnowpeakStateIDs::SPR_Dungeon_Completed;
                        }
                        break;
                    }
                    case stage::StageIDs::Snowpeak:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(SNOWPEAK_RUINS_CLEARED); // Snowpeak Ruins Completed

                        if (condition && (roomId != 0))
                        {
                            chosenLayer = stage::SnowpeakStateIDs::SPR_Dungeon_Completed;
                        }
                        break;
                    }

                    case stage::StageIDs::Faron_Woods:
                    case stage::StageIDs::Faron_Woods_Interiors:
                    {
                        if ((roomId == 5) || (roomId == 6)) // North Faron or Mist Area
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo Saved
                            if (condition)
                            {
                                chosenLayer = stage::FaronStateIDs::Faron_MDH_Completed;
                            }
                            else
                            {
                                chosenLayer = stage::FaronStateIDs::Faron_Talo_Captured;
                            }
                        }
                        else
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo Saved
                            if (condition)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    FOREST_TEMPLE_CLEARED); // Forest Temple Completed

                                if (condition)
                                {
                                    chosenLayer = stage::FaronStateIDs::Faron_Snowpeak_Completed;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::FaronStateIDs::Faron_Talo_Captured;
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Kakariko_Village:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                            WATCHED_CUTSCENE_AFTER_GORON_MINES); // Cutscene after GM Watched

                        if (condition == false)
                        {
                            condition =
                                libtp::tp::d_com_inf_game::dComIfGs_isEventBit(GORON_MINES_CLEARED); // Goron Mines Completed

                            if (condition == false)
                            {
                                chosenLayer = stage::KakarikoStateIDs::Kakariko_KB1_Completed;

                                // If it is night, the layer is different.
                                libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                            }
                            else
                            {
                                chosenLayer = stage::KakarikoStateIDs::Kakariko_Goron_Mines_Completed;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::KakarikoStateIDs::Kakariko_KB1_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                        }

                        break;
                    }
                    case stage::StageIDs::Kakariko_Graveyard:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                            GOT_ZORA_ARMOR_FROM_RUTELA); // Got Zora Armor from Rutela

                        if (condition == false)
                        {
                            condition =
                                libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ZORA_ESCORT_CLEARED); // Zora Escort Cleared

                            if (condition == false)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    WATCHED_CUTSCENE_AFTER_GORON_MINES); // Cutscene after GM Watched

                                if (condition == false)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                        GORON_MINES_CLEARED); // Goron Mines Completed

                                    if (condition == false)
                                    {
                                        chosenLayer = stage::KakarikoStateIDs::Kakariko_KB1_Completed;

                                        // If it is night, the layer is different.
                                        libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                                    }
                                    else
                                    {
                                        chosenLayer = stage::KakarikoStateIDs::Kakariko_Goron_Mines_Completed;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::KakarikoStateIDs::Kakariko_KB1_Completed;
                                    libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                                }
                            }
                            else
                            {
                                chosenLayer = stage::KakarikoStateIDs::Kakariko_Zora_Escort_Cleared;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::KakarikoStateIDs::Kakariko_KB1_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                        }
                        break;
                    }

                    case stage::StageIDs::Kakariko_Graveyard_Interiors:
                    {
                        if (((roomId == 1 &&
                              (condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(LAKEBED_TEMPLE_CLEARED),
                               condition != false)))) // Lakebed Completed
                        {
                            chosenLayer = stage::KakarikoInteriorStateIDs::Kakariko_Int_Lakebed_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                        }
                        else
                        {
                            chosenLayer = stage::KakarikoInteriorStateIDs::Kakariko_Int_KB1_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                        }
                        break;
                    }

                    case stage::StageIDs::Kakariko_Village_Interiors:
                    {
                        if (roomId == 1) // Lakebed Completed
                        {
                            chosenLayer = stage::KakarikoInteriorStateIDs::Kakariko_Int_Lakebed_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                        }
                        else
                        {
                            chosenLayer = stage::KakarikoInteriorStateIDs::Kakariko_Int_KB1_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                        }
                        break;
                    }

                    case stage::StageIDs::Death_Mountain:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(GORON_MINES_CLEARED); // Goron Mines Completed

                        if (condition)
                        {
                            chosenLayer = stage::DeathMountainStateIDs::Death_Mountain_Goron_Mines_Completed;
                        }
                        break;
                    }

                    case stage::StageIDs::Death_Mountain_Interiors:
                    {
                        chosenLayer = 0;
                        break;
                    }

                    case stage::StageIDs::Lake_Hylia:
                    {
                        if (roomId == 1) // Lanayru Spring
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                LAKEBED_TEMPLE_CLEARED); // Lakebed Temple has been completed

                            if (condition)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    MIDNAS_DESPERATE_HOUR_STARTED); // MDH has been started

                                if (condition == false)
                                {
                                    chosenLayer = stage::LakeHyliaStateIDs::Lake_Int_Lakebed_Completed;
                                }
                                else
                                {
                                    chosenLayer = stage::LakeHyliaStateIDs::Lake_Int_MDH_Started;
                                }
                            }
                        }
                        else
                        {
                            condition =
                                libtp::tp::d_com_inf_game::dComIfGs_isEventBit(SKY_CANNON_REPAIRED); // Sky Cannon Repaired

                            if (condition == false)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    WARPED_SKY_CANNON_TO_LAKE_HYLIA); // Sky Cannon Warped to Lake Hylia

                                if (condition == false)
                                {
                                    chosenLayer = stage::LakeHyliaStateIDs::Lake_Hylia_Lakebed_Completed;
                                }
                                else
                                {
                                    chosenLayer = stage::LakeHyliaStateIDs::Lake_Hylia_Warped_Cannon_To_Lake;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::LakeHyliaStateIDs::Lake_Hylia_Cannon_Repaired;
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Castle_Town_Interiors:
                    {
                        if (condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(LAKEBED_TEMPLE_CLEARED),
                            condition) // Lakebed Temple Completed
                        {
                            chosenLayer = stage::CastleTownInteriorsStateIDs::Castle_Town_Int_Lakebed_Completed;
                            if (condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_COMPLETED),
                                condition) // MDH Completed
                            {
                                chosenLayer = stage::CastleTownInteriorsStateIDs::Castle_Town_Int_Twilight_Cleared;
                            }
                        }
                        if (roomId == 5) // Telma's Bar
                        {
                            chosenLayer = stage::CastleTownInteriorsStateIDs::Castle_Town_Int_Watched_MS_Cutscene;
                        }
                        break;
                    }

                    case stage::StageIDs::Castle_Town:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_COMPLETED); // MDH Completed

                        if ((condition == false))
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                LAKEBED_TEMPLE_CLEARED); // Lakebed Temple Completed

                            if (condition == false)
                            {
                                if ((roomId == 3) &&
                                    (condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ZORA_ESCORT_CLEARED),
                                     condition != false)) // Zora Escort Cleared
                                {
                                    chosenLayer = stage::CastleTownStateIDs::Castle_Town_Finished_Zora_Escort;
                                }
                                else if (roomId == 4)
                                {
                                    chosenLayer = stage::CastleTownStateIDs::Castle_Town_MDH_Clear;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::CastleTownStateIDs::Castle_Town_Lakebed_Completed;
                            }
                        }
                        else
                        {
                            if (((roomId == 4) || (roomId == 3)) || (roomId == 1))
                            {
                                chosenLayer = stage::CastleTownStateIDs::Castle_Town_MDH_Clear;
                            }
                            else
                            {
                                chosenLayer = stage::CastleTownStateIDs::Castle_Town_West_MDH_Clear;
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Zoras_Domain:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(SNOWPEAK_RUINS_CLEARED); // Snowpeak Ruins Completed

                        if (condition != false)
                        {
                            chosenLayer = stage::ZorasDomainStateIDs::Domain_Snowpeak_Ruins_Completed;
                        }
                        break;
                    }

                    case stage::StageIDs::Upper_Zoras_River:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(IZA_1_MINIGAME_UNLOCKED); // Iza 1 Unlocked
                        if (condition != false)
                        {
                            chosenLayer = stage::UpperZorasRiverStateIDs::Upper_Zoras_River_Iza_1_Started;
                        }
                        break;
                    }

                    case stage::StageIDs::Gerudo_Desert:
                    {
                        chosenLayer = stage::GerudoDesertStateIDs::Desert_Entrance_Cutscene_Not_Watched;

                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                            VISITED_DESERT_FOR_THE_FIRST_TIME); // Have been to desert

                        if (condition != false)
                        {
                            chosenLayer = stage::GerudoDesertStateIDs::Desert_Entrance_Cutscene_Watched;
                        }
                        break;
                    }

                    case stage::StageIDs::Zoras_River:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(IZA_1_MINIGAME_DONE); // Iza 1 Minigame Completed

                        if (condition == false)
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                STARTED_IZA_1_MINIGAME); // Iza 1 Minigame Started

                            if (condition != false)
                            {
                                chosenLayer = stage::ZorasRiverStateIDs::Zoras_River_Iza_1_Started;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::ZorasRiverStateIDs::Zoras_River_Iza_1_Completed;
                        }
                        break;
                    }

                    case stage::StageIDs::Ordon_Village:
                    {
                        if (roomId == 0)
                        {
                            condition =
                                libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_1_FINISHED); // Ordon Day 1 done

                            if (condition)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo Saved
                                if (condition)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                        FINISHED_SEWERS); // First trip to Sewers done

                                    if (condition)
                                    {
                                        darkIsClear = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
                                        if (darkIsClear == false)
                                        {
                                            chosenLayer = stage::OrdonVillageStateIDs::Ordon_Finished_Sewers;
                                        }
                                        else
                                        {
                                            if (!libtp::tp::d_kankyo::dKy_daynight_check())
                                            {
                                                chosenLayer = stage::OrdonVillageStateIDs::Ordon_Goats_1_Completed;
                                            }
                                            else
                                            {
                                                chosenLayer = stage::OrdonVillageStateIDs::Ordon_Epona_Tamed_Night;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::OrdonVillageStateIDs::Ordon_Talo_Rescued;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::OrdonVillageStateIDs::Ordon_Goats_1_Completed;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::OrdonVillageStateIDs::Ordon_New_Game;
                            }
                        }
                        else
                        {
                            if (roomId == 1)
                            {
                                condition =
                                    libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_1_FINISHED); // Ordon Day 1 done

                                if (condition)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo Saved
                                    if (condition)
                                    {
                                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                            FINISHED_SEWERS); // First trip to Sewers done

                                        if (condition)
                                        {
                                            darkIsClear = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
                                            if (darkIsClear == false)
                                            {
                                                chosenLayer = stage::OrdonVillageStateIDs::Ordon_Finished_Sewers;
                                            }
                                            else
                                            {
                                                chosenLayer = stage::OrdonVillageStateIDs::Ordon_Faron_Twilight_Cleared;
                                            }
                                        }
                                        else
                                        {
                                            chosenLayer = stage::OrdonVillageStateIDs::Ordon_Link_House_Talo_Rescued;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::OrdonVillageStateIDs::Ordon_Link_House_Goats_1_Completed;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::OrdonVillageStateIDs::Ordon_Link_House_New_Game;
                                }
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Ordon_Village_Interiors:
                    {
                        /* not used in randomizer anymore. keeping for documentation sake
                        if ( roomId == 1 )     // Sera's Shop
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                BOUGHT_SLINGSHOT_FROM_SERA );     // Bought slinghot from Sera

                            if ( condition )
                            {
                                chosenLayer = stage::OrdonInteriorsStateIDs::Ordon_Int_Faron_Twilight_Cleared;
                            }
                        }*/
                        if (roomId == 2) // Jaggle's House
                        {
                            darkIsClear = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
                            if (darkIsClear == false)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    FINISHED_SEWERS); // First Trip to Sewers done

                                if (condition != false)
                                {
                                    chosenLayer = stage::OrdonInteriorsStateIDs::Ordon_Int_Finished_Sewers;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::OrdonInteriorsStateIDs::Ordon_Int_Finished_Sewers;
                            }
                        }
                        /* not used in randomizer anymore. keeping for documentation sake
                        else
                        {
                            if ( roomId == 5 )     // Rusl's House
                            {
                                darkIsClear = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                                if ( darkIsClear != false )
                                {
                                    chosenLayer = stage::OrdonInteriorsStateIDs::Ordon_Int_Faron_Twilight_Cleared;
                                }
                            }
                        }*/

                        break;
                    }

                    case stage::StageIDs::Ordon_Spring:
                    {
                        if (roomId == 1)
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                TALO_CHASES_MONKEY); // Sword training done on Ordon Day 2

                            if (condition)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo saved
                                if (condition)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                        FINISHED_SEWERS); // First trip to Sewers done

                                    if (condition)
                                    {
                                        darkIsClear = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
                                        if (darkIsClear != false)
                                        {
                                            chosenLayer = stage::OrdonSpringStateIDs::Ordon_Spring_Faron_Twilight_Cleared;
                                        }
                                        else
                                        {
                                            chosenLayer = stage::OrdonSpringStateIDs::Ordon_Spring_Finished_Sewers;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::OrdonSpringStateIDs::Ordon_Spring_Talo_Rescued;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::OrdonSpringStateIDs::Ordon_Spring_Sword_Tutorial_Completed;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::OrdonSpringStateIDs::Ordon_Spring_New_Game;
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Ordon_Ranch:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_1_FINISHED); // Day 1 done
                        if (condition)
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo Saved
                            if (condition)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    WATCHED_CUTSCENE_AFTER_GOATS_2); // Saw CS after Goats 2 done

                                if (condition)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                        FINISHED_SEWERS); // First trip to Sewers done

                                    if (condition)
                                    {
                                        darkIsClear = libtp::tp::d_save::isDarkClearLV(playerStatusBPtr, 0);
                                        if (darkIsClear == true)
                                        {
                                            chosenLayer = stage::OrdonRanchStateIDs::Ordon_Ranch_Faron_Twilight_Cleared;
                                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer(&chosenLayer);
                                        }
                                        else
                                        {
                                            chosenLayer = stage::OrdonRanchStateIDs::Ordon_Ranch_Finished_Sewers;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::OrdonRanchStateIDs::Ordon_Ranch_Faron_Twilight_Cleared;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::OrdonRanchStateIDs::Ordon_Ranch_Talo_Rescued;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::OrdonRanchStateIDs::Ordon_Ranch_Faron_Twilight_Cleared;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::OrdonRanchStateIDs::Ordon_Ranch_New_Game;
                        }
                        break;
                    }

                    case stage::StageIDs::Hyrule_Field:
                    {
                        if (libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b
                                .dark_clear_level_flag >= 0x7)
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                MIDNAS_DESPERATE_HOUR_STARTED); // MDH State Activated

                            if (condition)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    MIDNAS_DESPERATE_HOUR_COMPLETED); // MDH Completed

                                if (condition)
                                {
                                    chosenLayer = stage::HyruleFieldStateIDs::Hyrule_Field_MDH_Completed;
                                }
                                else
                                {
                                    chosenLayer = stage::HyruleFieldStateIDs::Hyrule_Field_MDH_Started;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::HyruleFieldStateIDs::Hyrule_Field_New_Game;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::HyruleFieldStateIDs::Hyrule_Field_New_Game;
                        }
                        break;
                    }

                    case stage::StageIDs::Outside_Castle_Town:
                    {
                        if (roomId == 8)
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                MIDNAS_DESPERATE_HOUR_COMPLETED); // MDH Completed

                            if (condition == false)
                            {
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                    MIDNAS_DESPERATE_HOUR_STARTED); // MDH State Activated

                                if (condition != false)
                                {
                                    chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Started;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed;
                            }
                        }
                        else
                        {
                            if (roomId == 0x10)
                            {
                                condition =
                                    libtp::tp::d_com_inf_game::dComIfGs_isEventBit(GOT_WOOD_STATUE); // Wooden Statue Gotten

                                if (condition == false)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                        TALKED_TO_LOUISE_ABOUT_THE_STOLEN_STATUE); // Talked to Louise after Medicine Scent

                                    if (condition == false)
                                    {
                                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                            MIDNAS_DESPERATE_HOUR_COMPLETED); // MDH Completed

                                        if (condition == false)
                                        {
                                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                                MIDNAS_DESPERATE_HOUR_STARTED); // MDH State Activated

                                            if (condition != false)
                                            {
                                                chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Started;
                                            }
                                            else
                                            {
                                                chosenLayer =
                                                    stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed;
                                            }
                                        }
                                        else
                                        {
                                            chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::OutsideCastleTownStateIDs::
                                            Outside_Castle_Town_Talked_To_Louise_Before_Statue;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_Got_Wooden_Statue_South;
                                }
                            }
                            else
                            {
                                if (roomId == 0x11)
                                {
                                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                        MIDNAS_DESPERATE_HOUR_COMPLETED); // MDH Completed

                                    if (condition == false)
                                    {
                                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                            MIDNAS_DESPERATE_HOUR_STARTED); // MDH State Activated

                                        if (condition != false)
                                        {
                                            chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Started;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::OutsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed_East;
                                    }
                                }
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Hidden_Village:
                    {
                        condition =
                            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(GAVE_ILIA_HER_CHARM); // Ilia shown Ilia's Charm

                        if (condition != false)
                        {
                            chosenLayer = stage::HiddenVillageStateIDs::Hidden_Village_Showed_Ilia_Charm;
                        }
                        break;
                    }

                    case stage::StageIDs::Castle_Town_Shops:
                    {
                        if (roomId == 5)
                        {
                            chosenLayer = stage::CastleTownShopsStateIDs::Castle_Town_Int_Jovani_MDH_Completed;
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_STARTED);
                            if (condition)
                            {
                                chosenLayer = stage::CastleTownShopsStateIDs::Castle_Town_Int_Jovani_New_Game;
                                condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_COMPLETED);
                                if (condition)
                                {
                                    chosenLayer = stage::CastleTownShopsStateIDs::Castle_Town_Int_Jovani_MDH_Completed;
                                }
                            }
                        }
                        else
                        {
                            condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                                MALO_MART_CASTLE_TOWN_BRANCH_IS_OPEN); // CT Shop is Malo Mart

                            if (condition != false)
                            {
                                chosenLayer = stage::CastleTownShopsStateIDs::Castle_Town_Int_Malo_Mart;
                            }
                        }
                        break;
                    }

                    case stage::StageIDs::Sacred_Grove:
                    {
                        chosenLayer = stage::SacredGroveStateIDs::Grove_2;
                        break;
                    }

                    case stage::StageIDs::Bulblin_Camp:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                            ESCAPED_BURNING_TENT_IN_BULBLIN_CAMP); // Escaped Burning Tent in Bulblin Camp

                        uint8_t* memoryFlagsPtr =
                            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags.memoryFlags[0];

                        if (condition)
                        {
                            if (roomId == 3) // Other states for this room are very similar, but do not have the boar
                                             // in the dzx.
                            { // Setting state 1 solves for any potential softlocks regarding the boar in that area.
                                chosenLayer = stage::BulblinCampStateIDs::Bulblin_Camp_KB3_Completed;
                            }
                            else
                            {
                                chosenLayer = stage::BulblinCampStateIDs::Bulblin_Camp_Watched_Mirror_Cutscene;
                                memoryFlagsPtr[0x1C] = 0x0;
                            }
                        }
                        else
                        {
                            if (events::haveItem(rando::customItems::Bulblin_Camp_Key))
                            {
                                memoryFlagsPtr[0x1C] = 0x1;
                            }
                        }

                        break;
                    }

                    case stage::StageIDs::Faron_Woods_Cave:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(ORDON_DAY_2_OVER); // Talo saved
                        if (condition != false)
                        {
                            chosenLayer = stage::FaronWoodsCaveStateIDs::Faron_Woods_Cave_Talo_Rescued;
                        }
                        break;
                    }

                    case stage::StageIDs::Hyrule_Castle_Sewers:
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(FINISHED_SEWERS); // Sewers Finished
                        if (condition)
                        {
                            chosenLayer = stage::SewersStateIDs::Sewers_Midna_On_Back;
                        }
                        else
                        {
                            chosenLayer = stage::TwilightStateIDs::Default_Twilight_State;
                        }
                        break;
                    }

                    case stage::StageIDs::Hyrule_Castle:
                    {
                        if (((roomId != 0xb) && (roomId != 0xd)) && (roomId != 0xe))
                        {
                            chosenLayer = stage::HyruleCastleStateIDs::Hyrule_Castle_Interior_State;
                        }
                        break;
                    }

                    case stage::StageIDs::Fishing_Pond:
                    case stage::StageIDs::Fishing_Pond_Interiors:
                    {
                        const uint32_t envLightVar = libtp::tp::d_kankyo::env_light.unk_1250[0xAE];
                        if (envLightVar == 3)
                        {
                            chosenLayer = stage::FishingHoleStateIDs::Fishing_Hole_Autumn;
                        }
                        else
                        {
                            if (envLightVar < 3)
                            {
                                if (envLightVar == 1)
                                {
                                    chosenLayer = stage::FishingHoleStateIDs::Fishing_Hole_Spring;
                                }
                                else
                                {
                                    if (envLightVar != 0)
                                    {
                                        chosenLayer = stage::FishingHoleStateIDs::Fishing_Hole_Summer;
                                    }
                                }
                            }
                            else
                            {
                                if (envLightVar < 5)
                                {
                                    chosenLayer = stage::FishingHoleStateIDs::Fishing_Hole_Winter;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }

        if (chosenLayer == stage::TwilightStateIDs::Default_Twilight_State)
        {
            condition =
                libtp::tp::d_com_inf_game::dComIfGs_isEventBit(WARPED_METEOR_TO_ZORAS_DOMAIN); // Warped meteor to Zora's Domain

            switch (stageID)
            {
                case stage::StageIDs::Zoras_River:
                case stage::StageIDs::Zoras_Domain:
                case stage::StageIDs::Lake_Hylia:
                case stage::StageIDs::Castle_Town:
                case stage::StageIDs::Castle_Town_Interiors:
                case stage::StageIDs::Upper_Zoras_River:
                case stage::StageIDs::Outside_Castle_Town:
                {
                    if (condition != false)
                    {
                        chosenLayer = stage::ZorasDomainStateIDs::Domain_Meteor_Warped;
                    }
                    break;
                }

                case stage::StageIDs::Hyrule_Field:
                {
                    if ((8 < roomId) && (roomId < 0xf) && (condition != false))
                    {
                        chosenLayer = stage::HyruleFieldStateIDs::Hyrule_Field_Meteor_Warped;
                    }
                    break;
                }

                case stage::StageIDs::Hyrule_Castle_Sewers:
                {
                    condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                        WATCHED_CUTSCENE_AFTER_BEING_CAPTURED_IN_FARON_TWILIGHT); // Watched CS after being captured in
                                                                                  // Faron Twilight
                    if (condition == false)
                    {
                        chosenLayer = stage::SewersStateIDs::Sewers_First_Time;
                    }
                    break;
                }

                case stage::StageIDs::Zant_Main_Room:
                {
                    if (roomId == 10)
                    {
                        condition = libtp::tp::d_com_inf_game::dComIfGs_isEventBit(PALACE_OF_TWILIGHT_CLEARED); // Zant Defeated

                        if (condition == false)
                        {
                            chosenLayer = stage::TwilightStateIDs::Palace_of_Twilight_Zant_Fight;
                        }
                        else
                        {
                            chosenLayer = stage::TwilightStateIDs::Palace_of_Twilight_Zant_Defeated;
                        }
                    }
                    break;
                }
            }
        }
        return chosenLayer;
    }
} // namespace mod::game_patch