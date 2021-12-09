#include <string.h>

#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/d_save.h"
#include "data/stages.h"

namespace mod::game_patch
{
    int32_t getCurrentStageId()
    {
        int32_t loopCount = sizeof( libtp::data::stage::allStages ) / sizeof( libtp::data::stage::allStages[0] );
        for ( int32_t i = 0; i < loopCount; i++ )
        {
            if ( libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[i] ) )
            {
                return i;
            }
        }
        // Didn't find the current stage for some reason
        return -1;
    }
    int32_t _01_getLayerNo( const char* stageName, int roomId, int layerOverride )
    {
        int chosenLayer;
        bool condition;
        int32_t stageID;
        unsigned int uVar2;
        libtp::tp::d_save::dSv_player_status_b_c* playerStatusBPtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b;
        using namespace libtp::data;

        chosenLayer = layerOverride;
        stageID = getCurrentStageId();

        if ( layerOverride < 0 )
        {
            condition = libtp::tp::d_kankyo::dKy_darkworld_stage_check( stageName, roomId );
            if ( condition == true )
            {
                chosenLayer = stage::twilightStateIDs::Default_Twilight_State;
            }

            if ( chosenLayer < 0xD )
            {
                switch ( stageID )
                {
                    case stage::stageIDs::Snowpeak_Ruins:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                            libtp::tp::d_save::saveBitLabels[0x10A] );     // Snowpeak Ruins Completed
                        if ( condition)
                        {
                             chosenLayer = stage::snowpeakStateIDs::SPR_Dungeon_Completed;
                        }
                        break;
                    }
                    case stage::stageIDs::Snowpeak:
                    {
                        //TODO need to set a condition that checks for the portal before updating the state as this can lose the portal
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                            libtp::tp::d_save::saveBitLabels[0x10A] );     // Snowpeak Ruins Completed
                        if ( condition == false )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                libtp::tp::d_save::saveBitLabels[0xA3] );     // Yeta unlocks the West door in SPR
                            if ( condition == false )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                    libtp::tp::d_save::saveBitLabels[0xA2] );     // Yeta unlocks the North-West door in SPR
                                if ( condition != false )
                                {
                                    chosenLayer = stage::snowpeakStateIDs::SPR_Northwest_Door_Unlocked;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::snowpeakStateIDs::SPR_West_Door_Unlocked;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::snowpeakStateIDs::SPR_Dungeon_Completed;
                        }
                        break;
                    }

                    case stage::stageIDs::Faron_Woods:
                    case stage::stageIDs::Faron_Woods_Interiors:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xD4 );     // Can Transform at Will
                        if ( condition == false )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x602 );     // Forest Temple Completed
                            if ( condition == false )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4510 );     // Talo Saved
                                if ( condition == false )
                                {
                                    chosenLayer = stage::faronStateIDs::Faron_Talo_Captured;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::faronStateIDs::Faron_Forest_Temple_Completed;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::faronStateIDs::Faron_Snowpeak_Completed;
                        }
                        break;
                    }

                    case stage::stageIDs::Kakariko_Village:
                    case stage::stageIDs::Kakariko_Graveyard:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x804 );     // Got Zora Armor from Rutela
                        if ( condition == false )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x810 );     // Zora Escort Cleared
                            if ( condition == false )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1320 );     // Cutscene after GM
                                                                                                     // Watched
                                if ( condition == false )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x701 );     // Goron Mines Completed
                                    if ( condition == false )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xa08 );     // KB1 Beaten
                                        if ( condition == false )
                                        {
                                            condition =
                                                libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x608 );     // KB1 Trigger Tripped
                                            if ( condition != false )
                                            {
                                                chosenLayer = stage::kakarikoStateIDs::Kakariko_KB1_Active;
                                            }
                                        }
                                        else
                                        {
                                            chosenLayer = stage::kakarikoStateIDs::Kakariko_KB1_Completed;
                                            // If it is night, the layer is different.
                                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::kakarikoStateIDs::Kakariko_Goron_Mines_Completed;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::kakarikoStateIDs::Kakariko_KB1_Completed;
                                    libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                                }
                            }
                            else
                            {
                                chosenLayer = stage::kakarikoStateIDs::Kakariko_Zora_Escort_Cleared;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::kakarikoStateIDs::Kakariko_KB1_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                        }
                    }

                    case stage::stageIDs::Kakariko_Village_Interiors:
                    case stage::stageIDs::Kakariko_Graveyard_Interiors:
                    {
                        if ( ( ( roomId == 1 && ( condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x904 ),
                                                  condition != false ) ) ) )     // Lakebed Completed
                        {
                            chosenLayer = stage::kakarikoInteriorStateIDs::Kakariko_Int_Lakebed_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                        }
                        else
                        {
                            chosenLayer = stage::kakarikoInteriorStateIDs::Kakariko_Int_KB1_Completed;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                        }
                        break;
                    }

                    case stage::stageIDs::Death_Mountain:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                            libtp::tp::d_save::saveBitLabels[0x40] );     // Goron Mines Completed
                        if ( condition != false )
                        {
                            chosenLayer = stage::deathMountainStateIDs::Death_Mountain_Goron_Mines_Completed;
                        }
                        break;
                    }

                    case stage::stageIDs::Death_Mountain_Interiors:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x2320 );     // Ilia shown Horse Call
                        if ( condition == false )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x2004 );     // Temple of Time Completed
                            if ( condition == false )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                    0x2020 );     // Master Sword Story Progression Flag
                                if ( condition == false )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x701 );     // Goron Mines Completed
                                    if ( condition != false )
                                    {
                                        chosenLayer = stage::deathMountainInteriorStateIDs::Death_Mountain_Int_Goron_Mines_Completed;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::deathMountainInteriorStateIDs::Death_Mountain_Int_Master_Sword_CS_Watched;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::deathMountainInteriorStateIDs::Death_Mountain_Int_Temple_of_Time_Completed;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::deathMountainInteriorStateIDs::Death_Mountain_Int_Ilia_Given_Charm;
                        }
                        break;
                    }

                    case stage::stageIDs::Lake_Hylia:
                    {
                        if ( roomId == 1 )     // Lanayru Spring
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xc01 );     // MDH has been started
                            if ( condition == false )
                            {
                                chosenLayer = stage::lakeHyliaStateIDs::Lake_Int_Lakebed_Completed;
                            }
                            else
                            {
                                chosenLayer = stage::lakeHyliaStateIDs::Lake_Int_MDH_Started;
                            }
                        }
                        else
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x3b08 );     // Sky Cannon Repaired
                            if ( condition == false )
                            {
                                condition =
                                    libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x3120 );     // Sky Cannon Warped to Lake Hylia
                                if ( condition == false )
                                {
                                    condition =
                                        libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x904 );     // Lakebed Temple Completed
                                    if ( condition != false )
                                    {
                                        chosenLayer = stage::lakeHyliaStateIDs::Lake_Hylia_Lakebed_Completed;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::lakeHyliaStateIDs::Lake_Hylia_Warped_Cannon_To_Lake;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::lakeHyliaStateIDs::Lake_Hylia_Cannon_Repaired;
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Castle_Town_Interiors:
                    {
                        if ( roomId == 5 )     // Telma's Bar
                        {
                            chosenLayer = stage::castleTownInteriorsStateIDs::Castle_Town_Int_Watched_MS_Cutscene;
                        }
                        if ( condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x904 ),
                             condition )     // Lakebed Temple Completed
                        {
                            chosenLayer = stage::castleTownInteriorsStateIDs::Castle_Town_Int_Lakebed_Completed;
                            if ( condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 ),
                                 condition )     // MDH Completed
                            {
                                chosenLayer = stage::castleTownInteriorsStateIDs::Castle_Town_Int_Twilight_Cleared;
                                if ( roomId == 5 )     // Telma's Bar
                                {
                                    chosenLayer = stage::castleTownInteriorsStateIDs::Castle_Town_Int_Watched_MS_Cutscene;
                                }
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Castle_Town:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 );     // MDH Completed
                        if ( ( condition == false ) )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x904 );     // Lakebed Temple Completed
                            if ( condition == false )
                            {
                                if ( ( roomId == 3 ) && ( condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                                              libtp::tp::d_save::saveBitLabels[0x44] ),
                                                          condition != false ) )     // Zora Escort Cleared
                                {
                                    chosenLayer = stage::castleTownStateIDs::Castle_Town_Finished_Zora_Escort;
                                }
                            }
                        }
                        else
                        {
                            if ( ( ( roomId == 4 ) || ( roomId == 3 ) ) || ( roomId == 1 ) )
                            {
                                chosenLayer = stage::castleTownStateIDs::Castle_Town_MDH_Clear;
                            }
                            else
                            {
                                chosenLayer = stage::castleTownStateIDs::Castle_Town_West_MDH_Clear;
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Zoras_Domain:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x2008 );     // Snowpeak Ruins Completed
                        if ( condition != false )
                        {
                            chosenLayer = stage::zorasDomainStateIDs::Domain_Snowpeak_Ruins_Completed;
                        }
                        break;
                    }

                    case stage::stageIDs::Upper_Zoras_River:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                            libtp::tp::d_save::saveBitLabels[0x5F] );     // Iza 1 Unlocked
                        if ( condition != false )
                        {
                            chosenLayer = stage::upperZorasRiverStateIDs::Upper_Zoras_River_Iza_1_Started;
                        }
                        break;
                    }

                    case stage::stageIDs::Gerudo_Desert:
                    {
                        chosenLayer = stage::gerudoDesertStateIDs::Desert_Entrance_Cutscene_Not_Watched;
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4008 );     // Have been to desert
                        if ( condition != false )
                        {
                            chosenLayer = stage::gerudoDesertStateIDs::Desert_Entrance_Cutscene_Watched;
                        }
                        break;
                    }

                    case stage::stageIDs::Zoras_River:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xb01 );     // Iza 1 Minigame Completed
                        if ( condition == false )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x902 );     // Iza 1 Minigame Started
                            if ( condition != false )
                            {
                                chosenLayer = stage::zorasRiverStateIDs::Zoras_River_Iza_1_Started;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::zorasRiverStateIDs::Zoras_River_Iza_1_Completed;
                        }
                        break;
                    }

                    case stage::stageIDs::Ordon_Village:
                    {
                        if ( roomId == 0 )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                libtp::tp::d_save::saveBitLabels[0x38] );     // Epona Tamed
                            if ( condition == false )
                            {
                                uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                                if ( uVar2 == 0 )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                        libtp::tp::d_save::saveBitLabels[0x2F] );     // First Trip to Sewers Done
                                    if ( condition == false )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4510 );     // Talo Saved
                                        if ( condition == false )
                                        {
                                            condition =
                                                libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4a40 );     // Ordon Day 1 done
                                            if ( condition == false )
                                            {
                                                chosenLayer = stage::ordonVillageStateIDs::Ordon_New_Game;
                                            }
                                            else
                                            {
                                                chosenLayer = stage::ordonVillageStateIDs::Ordon_Goats_1_Completed;
                                            }
                                        }
                                        else
                                        {
                                            chosenLayer = stage::ordonVillageStateIDs::Ordon_Talo_Rescued;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::ordonVillageStateIDs::Ordon_Finished_Sewers;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::ordonVillageStateIDs::Ordon_Faron_Twilight_Cleared;
                                    libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                                }
                            }
                            else
                            {
                                chosenLayer = stage::ordonVillageStateIDs::Ordon_Epona_Tamed;
                                libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                            }
                        }
                        else
                        {
                            if ( roomId == 1 )
                            {
                                uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                                if ( uVar2 == 0 )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                        libtp::tp::d_save::saveBitLabels[0x2F] );     // First trip to Sewers done
                                    if ( condition == false )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4510 );     // Talo Saved
                                        if ( condition == false )
                                        {
                                            condition =
                                                libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4a40 );     // Ordon Day 1 done
                                            if ( condition == false )
                                            {
                                                chosenLayer = stage::ordonVillageStateIDs::Ordon_Link_House_New_Game;
                                            }
                                            else
                                            {
                                                chosenLayer = stage::ordonVillageStateIDs::Ordon_Link_House_Goats_1_Completed;
                                            }
                                        }
                                        else
                                        {
                                            chosenLayer = stage::ordonVillageStateIDs::Ordon_Link_House_Talo_Rescued;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::ordonVillageStateIDs::Ordon_Finished_Sewers;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::ordonVillageStateIDs::Ordon_Faron_Twilight_Cleared;
                                }
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Ordon_Village_Interiors:
                    {
                        if ( roomId == 1 )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4902 ); //Bought slinghot from Sera
                            if ( condition )
                                {
                                    chosenLayer = stage::ordonInteriorsStateIDs::Ordon_Int_Faron_Twilight_Cleared;
                                }
                            /* This is the original code, which updates the state of the shop once you've cleared Faron Twilight.
                            * We modify this in rando to instead update once you've bought the Slingshot as to not lose the check and to 
                            * help prevent logical linearity/softlocks in the early game.
                            uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                            if ( uVar2 != 0 )
                            {
                                chosenLayer = stage::ordonInteriorsStateIDs::Ordon_Int_Faron_Twilight_Cleared;
                            }*/
                        }
                        else
                        {
                            if ( roomId == 2 )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x780 );     // Watched Colin CS after
                                                                                                    // KB1
                                if ( condition == false )
                                {
                                    uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                                    if ( uVar2 == 0 )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                            libtp::tp::d_save::saveBitLabels[0x2F] );     // First Trip to Sewers done
                                        if ( condition != false )
                                        {
                                            chosenLayer = stage::ordonInteriorsStateIDs::Ordon_Int_Finished_Sewers;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::ordonInteriorsStateIDs::Ordon_Int_Faron_Twilight_Cleared;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::ordonInteriorsStateIDs::Ordon_Int_KB1_Completed;
                                }
                            }
                            else
                            {
                                if ( roomId == 5 )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x601 );     // Epona Tamed
                                    if ( condition == false )
                                    {
                                        uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                                        if ( uVar2 != 0 )
                                        {
                                            chosenLayer = stage::ordonInteriorsStateIDs::Ordon_Int_Faron_Twilight_Cleared;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::ordonVillageStateIDs::Ordon_Epona_Tamed;
                                    }
                                }
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Ordon_Spring:
                    {
                        if ( roomId == 1 )
                        {
                            uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                            if ( uVar2 == 0 )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                    libtp::tp::d_save::saveBitLabels[0x2F] );     // First trip to Sewers done
                                if ( condition == false )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4510 );     // Talo saved
                                    if ( condition == false )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                            0x4a20 );     // Sword training done on Ordon Day 2
                                        if ( condition == false )
                                        {
                                            chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_New_Game;
                                        }
                                        else
                                        {
                                            chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_Sword_Tutorial_Completed;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_Talo_Rescued;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_Finished_Sewers;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_Faron_Twilight_Cleared;
                            }
                        }
                        else
                        {
                            uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                            if ( uVar2 == 0 )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                    libtp::tp::d_save::saveBitLabels[0x2F] );     // First trip to Sewers done
                                if ( condition != false )
                                {
                                    chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_Finished_Sewers;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::ordonSpringStateIDs::Ordon_Spring_Faron_Twilight_Cleared;
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Ordon_Ranch:
                    {
                        uVar2 = libtp::tp::d_save::isDarkClearLV( playerStatusBPtr, 0 );
                        if ( uVar2 == 0 )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                libtp::tp::d_save::saveBitLabels[0x2F] );     // First trip to Sewers done
                            if ( condition == false )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                    libtp::tp::d_save::saveBitLabels[0xA9] );     // Saw CS after Goats 2 done
                                if ( condition == false )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4510 );     // Talo Saved
                                    if ( condition == false )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4a40 );     // Day 1 done
                                        if ( condition == false )
                                        {
                                            chosenLayer = stage::ordonRanchStateIDs::Ordon_Ranch_New_Game;
                                        }
                                        else
                                        {
                                            chosenLayer = stage::ordonRanchStateIDs::Ordon_Ranch_Goats_1_Completed;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::ordonRanchStateIDs::Ordon_Ranch_Talo_Rescued;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::ordonRanchStateIDs::Ordon_Ranch_Goats_2_Completed;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::ordonRanchStateIDs::Ordon_Ranch_Finished_Sewers;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::ordonRanchStateIDs::Ordon_Ranch_Faron_Twilight_Cleared;
                            libtp::tp::d_com_inf_game::dComIfG_get_timelayer( &chosenLayer );
                        }
                        break;
                    }

                    case stage::stageIDs::Hyrule_Field:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 );     // MDH Completed
                        if ( condition == false )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xc01 );     // MDH State Activated
                            if ( condition == false )
                            {
                                chosenLayer = stage::hyruleFieldStateIDs::Hyrule_Field_New_Game;
                            }
                            else
                            {
                                chosenLayer = stage::hyruleFieldStateIDs::Hyrule_Field_MDH_Started;
                            }
                        }
                        else
                        {
                            chosenLayer = stage::hyruleFieldStateIDs::Hyrule_Field_MDH_Completed;
                        }
                        break;
                    }

                    case stage::stageIDs::Outside_Castle_Town:
                    {
                        if ( roomId == 8 )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 );     // MDH Completed
                            if ( condition == false )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xc01 );     // MDH State Activated
                                if ( condition != false )
                                {
                                    chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_MDH_Started;
                                }
                            }
                            else
                            {
                                chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed;
                            }
                        }
                        else
                        {
                            if ( roomId == 0x10 )
                            {
                                condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x2204 );     // Wooden Statue Gotten
                                if ( condition == false )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                                        0x2102 );     // Talked to Louise after Medicine Scent
                                    if ( condition == false )
                                    {
                                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 );     // MDH Completed
                                        if ( condition == false )
                                        {
                                            condition =
                                                libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xc01 );     // MDH State Activated
                                            if ( condition != false )
                                            {
                                                chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_MDH_Started;
                                            }
                                        }
                                        else
                                        {
                                            chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_Talked_To_Louise_Before_Statue;
                                    }
                                }
                                else
                                {
                                    chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_Got_Wooden_Statue_South;
                                }
                            }
                            else
                            {
                                if ( roomId == 0x11 )
                                {
                                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 );     // MDH Completed
                                    if ( condition == false )
                                    {
                                        condition =
                                            libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xc01 );     // MDH State Activated
                                        if ( condition != false )
                                        {
                                            chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_MDH_Started;
                                        }
                                    }
                                    else
                                    {
                                        chosenLayer = stage::outsideCastleTownStateIDs::Outside_Castle_Town_MDH_Completed_East;
                                    }
                                }
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Hidden_Village:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x2320 );     // Ilia shown Ilia's Charm
                        if ( condition != false )
                        {
                            chosenLayer = stage::hiddenVillageStateIDs::Hidden_Village_Showed_Ilia_Charm;
                        }
                        break;
                    }

                    case stage::stageIDs::Castle_Town_Shops:
                    {
                        if ( roomId == 5 )
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1e08 );     // MDH Completed
                            if ( condition == false )
                            {
                                chosenLayer = stage::castleTownShopsStateIDs::Castle_Town_Int_Jovani_New_Game;
                            }
                            else
                            {
                                chosenLayer = stage::castleTownShopsStateIDs::Castle_Town_Int_Jovani_MDH_Completed;
                            }
                        }
                        else
                        {
                            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x2210 );     // CT Shop is Malo Mart
                            if ( condition != false )
                            {
                                chosenLayer = stage::castleTownShopsStateIDs::Castle_Town_Int_Malo_Mart;
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Sacred_Grove:
                    {
                        chosenLayer = stage::sacredGroveStateIDs::Grove_2;
                        break;
                    }

                    case stage::stageIDs::Bulblin_Camp:
                    {
                        condition =
                            libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xb40 );     // Escaped Burning Tent in Bublin Camp
                        if ( condition )
                        {
                            if ( roomId ==
                                 3 )     // Other states for this room are very similar, but do not have the boar in the dzx.
                            {            // Setting state 1 solves for any potential softlocks regarding the boar in that area.
                                chosenLayer = stage::bulblinCampStateIDs::Bulblin_Camp_KB3_Completed;
                            }
                            else
                            {
                                chosenLayer = stage::bulblinCampStateIDs::Bulblin_Camp_Watched_Mirror_Cutscene;
                            }
                        }
                        break;
                    }

                    case stage::stageIDs::Faron_Woods_Cave:
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x4510 );     // Talo saved
                        if ( condition != false )
                        {
                            chosenLayer = stage::faronWoodsCaveStateIDs::Faron_Woods_Cave_Talo_Rescued;
                        }
                        break;
                    }

                    case stage::stageIDs::Hyrule_Castle_Sewers:
                    {
                        condition = libtp::tp::d_save::isTransformLV( playerStatusBPtr, 3 );     // Midna on Back
                        if ( condition != false )
                        {
                            chosenLayer = stage::sewersStateIDs::Sewers_Midna_On_Back;
                        }
                        break;
                    }

                    case stage::stageIDs::Hyrule_Castle:
                    {
                        if ( ( ( roomId != 0xb ) && ( roomId != 0xd ) ) && ( roomId != 0xe ) )
                        {
                            chosenLayer = stage::hyruleCastleStateIDs::Hyrule_Castle_Interior_State;
                        }
                        break;
                    }

                    case stage::stageIDs::Fishing_Pond:
                    case stage::stageIDs::Fishing_Pond_Interiors:
                    {
                        if ( libtp::tp::d_kankyo::env_light.unk_98d[0x971] == 3 )
                        {
                            chosenLayer = stage::fishingHoleStateIDs::Fishing_Hole_Autumn;
                        }
                        else
                        {
                            if ( libtp::tp::d_kankyo::env_light.unk_98d[0x971] < 3 )
                            {
                                if ( libtp::tp::d_kankyo::env_light.unk_98d[0x971] == 1 )
                                {
                                    chosenLayer = stage::fishingHoleStateIDs::Fishing_Hole_Spring;
                                }
                                else
                                {
                                    if ( libtp::tp::d_kankyo::env_light.unk_98d[0x971] != 0 )
                                    {
                                        chosenLayer = stage::fishingHoleStateIDs::Fishing_Hole_Summer;
                                    }
                                }
                            }
                            else
                            {
                                if ( libtp::tp::d_kankyo::env_light.unk_98d[0x971] < 5 )
                                {
                                    chosenLayer = stage::fishingHoleStateIDs::Fishing_Hole_Winter;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }

        if ( chosenLayer == stage::twilightStateIDs::Default_Twilight_State )
        {
            condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                libtp::tp::d_save::saveBitLabels[0x41] );     // Warped meteor to Zora's Domain
            switch ( stageID )
            {
                case stage::stageIDs::Zoras_River:
                case stage::stageIDs::Zoras_Domain:
                case stage::stageIDs::Lake_Hylia:
                case stage::stageIDs::Castle_Town:
                case stage::stageIDs::Castle_Town_Interiors:
                case stage::stageIDs::Upper_Zoras_River:
                case stage::stageIDs::Outside_Castle_Town:
                {
                    if ( condition != false )
                    {
                        chosenLayer = stage::zorasDomainStateIDs::Domain_Meteor_Warped;
                    }
                    break;
                }

                case stage::stageIDs::Hyrule_Field:
                {
                    if ( ( 8 < roomId ) && ( roomId < 0xf ) && ( condition != false ) )
                    {
                        chosenLayer = stage::hyruleFieldStateIDs::Hyrule_Field_Meteor_Warped;
                    }
                    break;
                }

                case stage::stageIDs::Hyrule_Castle_Sewers:
                {
                    condition = libtp::tp::d_a_alink::dComIfGs_isEventBit(
                        0x4d08 );     // Watched CS after being captured in Faron Twilight
                    if ( condition == false )
                    {
                        chosenLayer = stage::sewersStateIDs::Sewers_First_Time;
                    }
                    break;
                }

                case stage::stageIDs::Zant_Main_Room:
                {
                    if ( roomId == 10 )
                    {
                        condition = libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x5410 );     // Zant Defeated
                        if ( condition == false )
                        {
                            chosenLayer = stage::twilightStateIDs::Palace_of_Twilight_Zant_Fight;
                        }
                        else
                        {
                            chosenLayer = stage::twilightStateIDs::Palace_of_Twilight_Zant_Defeated;
                        }
                    }
                    break;
                }
            }
        }
        return chosenLayer;
    }
}     // namespace mod::game_patch