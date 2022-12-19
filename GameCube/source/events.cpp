#include <cstring>

#include "events.h"
#include "asm.h"
#include "data/items.h"
#include "data/stages.h"
#include "main.h"
#include "patch.h"
#include "rando/randomizer.h"
#include "tp/J2DTextBox.h"
#include "cxx.h"
#include "tp/d_a_alink.h"
#include "tp/d_a_player.h"
#include "tp/d_camera.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_kankyo.h"
#include "tp/d_map_path_dmap.h"
#include "tp/d_meter2_info.h"
#include "tp/d_resource.h"
#include "tp/dzx.h"
#include "tp/m_do_ext.h"
#include "tp/rel/d_a_obj_Lv5Key.h"
#include "user_patch/03_customCosmetics.h"
#include "tp/J2DPicture.h"
#include "data/flags.h"

namespace mod::events
{
    // REL patching trampolines
    void ( *return_daObjLv5Key_c__Wait )( libtp::tp::rel::d_a_obj_Lv5Key::daObjLv5Key_c* _this ) = nullptr;
    void ( *return_daObjLifeContainer_c__Create )( void* _this ) = nullptr;
    void ( *return_daObjLifeContainer_c__setEffect )( void* _this ) = nullptr;
    CMEB checkNpcTransform = nullptr;
    uint8_t timeChange = 0;

    libtp::tp::dzx::ACTR GanonBarrierActor =
        { "Obj_gb", 0x800F0601, 10778.207f, 3096.82666f, -62651.0078f, static_cast<int16_t>( -164.7121 ), 0x4000, 0, 0xFFFF };

    libtp::tp::dzx::ACTR AuruActr =
        { "Rafrel", 0x00001D01, -116486.945f, -13860.f, 58533.0078f, 0, static_cast<int16_t>( 0xCCCD ), 0, 0xFFFF };
    libtp::tp::dzx::ACTR ItemActr =
        { "item", 0xF3FFFF04, -108290.086f, -18654.748f, 45935.2969f, 0, static_cast<int16_t>( 0x1 ), 0x3F, 0xFFFF };
    libtp::tp::dzx::ACTR EponaActr = { "Horse", 0x00000F0D, 0.f, 0.f, 0.f, 0, -180, 0, 0xFFFF };
    libtp::tp::dzx::SCOB HorseJumpScob =
        { "Hjump", 0x044FFF02, 5600.f, -5680.f, 52055.f, 0, static_cast<int16_t>( 0x4000 ), 0, 0xFFFF, 0x20, 0x2D, 0x2D, 0xFF };
    libtp::tp::dzx::ACTR ForestGWolfActr = { "GWolf", 0x05FF01FF, -35178.f, 430.21f, -21503.6f, 0, -0x4000, 0xFF, 0xFFFF };
    libtp::tp::dzx::ACTR ImpPoeActr = { "E_hp", 0xFF031E00, 4531.19f, -30.f, 2631.961f, 0, 0, 0x0, 0xFFFF };
    libtp::tp::dzx::ACTR CampBoarActr =
        { "E_wb", 0xFFFFFFFF, 1650.f, 0.f, 1250.f, 0, static_cast<int16_t>( 0xA000 ), 0x0, 0xFFFF };

    void onLoad( rando::Randomizer* randomizer )
    {
        randomizer->onStageLoad();
        timeChange = 0;
    }

    void offLoad( rando::Randomizer* randomizer )
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        if ( !getCurrentSeed( randomizer ) )
        {
            return;
        }

        libtp::tp::d_com_inf_game::dComIfG_play* playPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.play;
        libtp::tp::d_stage::dStage_startStage* startStagePtr = &playPtr->mStartStage;

        const char* currentStage = startStagePtr->mStage;
        int32_t currentRoom = startStagePtr->mRoomNo;
        int32_t currentPoint = startStagePtr->mPoint;

        // Check if the seed is already applied to the save-file (flags etc.)
        // Try to do it otherwise
        if ( !randomizer->m_SeedInit && ( strcmp( currentStage, "F_SP108" ) == 0 ) && ( currentRoom == 1 ) &&
             ( currentPoint == 0x15 ) )
        {
            randomizer->initSave();
        }

        if ( ( strcmp( playPtr->mNextStage.stageValues.mStage, "F_SP103" ) == 0 ) && ( currentRoom == 1 ) &&
             ( currentPoint == 0x1 ) )     // If we are spawning in Ordon for the first time.
        {
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_b.skyAngle = 180;

            if ( libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::CLEARED_FARON_TWILIGHT ) )
            {
                libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.horse_place.mPos.y =
                    -1000.f;     // Place Epona out of bounds in Faron if the twilight has been cleared since the game will
                                 // spawn her in the air.
            }
        }

        // Check to see if currently in Snowpeak Ruins
        if ( strcmp( currentStage, libtp::data::stage::allStages[libtp::data::stage::stageIDs::City_in_the_Sky] ) == 0 )
        {
            libtp::tp::d_save::offSwitch_dSv_memBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags,
                                                     0xA );     // Fan in main room active
            libtp::tp::d_save::offSwitch_dSv_memBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags,
                                                     0xF );     // Main Room 1F explored
        }

        randomizer->overrideEventARC();
    }

    void onRELLink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        randomizer->overrideREL();

        // Static REL overrides and patches
        uint32_t relPtrRaw = reinterpret_cast<uint32_t>( dmc->moduleInfo );

        switch ( dmc->moduleInfo->id )
        {
            // d_a_door_shutter.rel
            // Door - Shutter
            case 0x8:
            {
                if ( libtp::tp::d_a_alink::checkStageName(
                         libtp::data::stage::allStages[libtp::data::stage::stageIDs::Snowpeak_Ruins] ) )
                {
                    // Set the call to checkOpenDoor to always return true when in SPR
                    performStaticASMReplacement( relPtrRaw + 0xD68, 0x38600001 );     // li r3, 1
                }

                break;
            }
            // d_a_tbox.rel
            // Treasure Chests
            case 0x29:
            {
                // Nop out the bne- that causes chests to play the cutscene for big items.
                performStaticASMReplacement( relPtrRaw + 0xA58, 0x60000000 );
                break;
            }
            // d_a_kytag11.rel
            // d_kankyo tag 11
            case 0x4c:
            {
                if ( libtp::tp::d_a_alink::checkStageName(
                         libtp::data::stage::allStages[libtp::data::stage::stageIDs::Hyrule_Field] ) )
                {
                    // Nop out the instruction that causes the time flow to not consider the mTimeSpeed variable in Field.
                    performStaticASMReplacement( relPtrRaw + 0x2CC, 0x60000000 );     // nop
                }

                break;
            }
            // d_a_e_hp.rel
            // Generic Poe
            case 0x00C8:
            {
                libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + e_hp_ExecDead_liOffset ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustPoeItemStart ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustPoeItemEnd ) );

                // Disable Poe increment (handled through item_get_func; see game_patches)
                performStaticASMReplacement( relPtrRaw + e_hp_ExecDead_incOffset, 0x60000000 );

                break;
            }
            // d_a_e_po.rel
            // Arbiter's Poe
            case 0x00DD:
            {
                libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + e_po_ExecDead_liOffset ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustAGPoeItemStart ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustAGPoeItemEnd ) );

                // Disable Poe increment (handled through item_get_func; see game_patches)
                performStaticASMReplacement( relPtrRaw + e_po_ExecDead_incOffset, 0x60000000 );
                break;
            }
            // d_a_obj_kshutter.rel
            // Lakebed Temple Boss Door
            case 0x1FA:
            {
                // Nop out the instruction that stores the new total small key value when the game attempts to
                // remove a small key from the inventory when opening the boss door
                if ( libtp::tools::playerIsInRoomStage(
                         2,
                         libtp::data::stage::allStages[libtp::data::stage::stageIDs::Lakebed_Temple] ) )
                {
                    performStaticASMReplacement( relPtrRaw + 0x1198, 0x60000000 );     // Previous: 0x3803ffff
                }
                break;
            }
            // d_a_npc_kn.rel
            // Hero's Shade
            case 0x147:
            {
                // Give a an item based on which Golden Wolf you learned a skill from.
                libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + 0x34D0 ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustHiddenSkillItemStart ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustHiddenSkillItemEnd ) );
                break;
            }
            // d_a_npc_ins.rel
            // Agitha
            case 0x141:
            {
                mod::rando::Seed* seed;
                if ( seed = getCurrentSeed( randomizer ), seed )
                {
                    if ( seed->m_numBugRewardChecks > 0 )
                    {
                        libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + 0x21B8 ),
                                                             reinterpret_cast<void*>( assembly::asmAdjustBugRewardStart ),
                                                             reinterpret_cast<void*>( assembly::asmAdjustBugRewardEnd ) );
                    }
                }
                break;
            }
            // d_a_mg_rod.rel
            // Fishing Hole Rod
            case 0x32:
            {
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0xB2B0 ),
                                             reinterpret_cast<void*>( libtp::tp::d_item::execItemGet ) );

                break;
            }
            // d_a_Statue_Tag.rel
            // Owl Statues
            case 0x85:     // d_a_Tag_Statue - Owl Statues
            {
                // Replace sky character
                performStaticASMReplacement( relPtrRaw + 0xB7C, 0x48000020 );     // b 0x20

                libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + 0xB9C ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustSkyCharacterStart ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustSkyCharacterEnd ) );

                break;
            }
            // d_a_obj_life_container.rel
            // Heart Pieces/Containers
            case 0x35:
            {
                // Adjust freestanding heart field model height based on the current item being created
                return_daObjLifeContainer_c__Create = libtp::patch::hookFunction(
                    reinterpret_cast<void ( * )( void* )>( relPtrRaw + 0x5D0 ),
                    []( void* daObjLifePtr )
                    {
                        using namespace libtp::data;
                        uint8_t itemID = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x92A );

                        // Must check for foolish items first, as they will use the item id of the item they are copying
                        itemID = rando::getFoolishItemModelId( itemID );

                        switch ( itemID )
                        {
                            case items::Master_Sword:
                            case items::Master_Sword_Light:
                            case items::Wooden_Shield:
                            case items::Hylian_Shield:
                            case items::Ordon_Shield:
                            case items::Spinner:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 30.f;
                                break;
                            }
                            case items::Wooden_Sword:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 60.f;
                                break;
                            }
                            case items::Ordon_Sword:
                            case items::Mirror_Piece_2:
                            case items::Mirror_Piece_3:
                            case items::Mirror_Piece_4:
                            case items::Fused_Shadow_1:
                            case items::Fused_Shadow_2:
                            case items::Fused_Shadow_3:
                            case items::Dominion_Rod_Uncharged:
                            case items::Dominion_Rod:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 50.f;
                                break;
                            }

                            case items::Heros_Bow:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 55.f;
                                break;
                            }
                            case items::Boomerang:
                            case items::Fishing_Rod:
                            case items::Big_Quiver:
                            case items::Giant_Quiver:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 40.f;
                                break;
                            }
                            case items::Forest_Temple_Small_Key:
                            case items::Goron_Mines_Small_Key:
                            case items::Lakebed_Temple_Small_Key:
                            case items::Arbiters_Grounds_Small_Key:
                            case items::Snowpeak_Ruins_Small_Key:
                            case items::Temple_of_Time_Small_Key:
                            case items::City_in_The_Sky_Small_Key:
                            case items::Palace_of_Twilight_Small_Key:
                            case items::Hyrule_Castle_Small_Key:
                            case items::Forest_Temple_Big_Key:
                            case items::Lakebed_Temple_Big_Key:
                            case items::Arbiters_Grounds_Big_Key:
                            case items::Temple_of_Time_Big_Key:
                            case items::City_in_The_Sky_Big_Key:
                            case items::Palace_of_Twilight_Big_Key:
                            case items::Hyrule_Castle_Big_Key:
                            case items::Small_Key_N_Faron_Gate:
                            case items::Bed_Key:
                            case items::Bulblin_Camp_Key:
                            case items::Gate_Keys:
                            case items::Slingshot:
                            case items::Giant_Bomb_Bag:
                            case items::Empty_Bomb_Bag:
                            case items::Goron_Bomb_Bag:
                            case items::Bomb_Bag_Regular_Bombs:
                            case items::Poe_Soul:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 20.f;
                                break;
                            }

                            case items::Magic_Armor:
                            {
                                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x4D4 ) += 25.f;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                        return_daObjLifeContainer_c__Create( daObjLifePtr );
                    } );

                // Remove glow and sparkle from rupees and Poe Souls
                return_daObjLifeContainer_c__setEffect = libtp::patch::hookFunction(
                    reinterpret_cast<void ( * )( void* )>( relPtrRaw + 0x764 ),
                    []( void* daObjLifePtr )
                    {
                        using namespace libtp::data;
                        uint8_t itemID = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( daObjLifePtr ) + 0x92A );
                        switch ( itemID )
                        {
                            case items::Green_Rupee:
                            case items::Red_Rupee:
                            case items::Blue_Rupee:
                            case items::Yellow_Rupee:
                            case items::Purple_Rupee:
                            case items::Purple_Rupee_Links_House:
                            case items::Orange_Rupee:
                            case items::Silver_Rupee:
                            case items::Poe_Soul:
                            {
                                return;
                            }
                            default:
                            {
                                return return_daObjLifeContainer_c__setEffect( daObjLifePtr );
                            }
                        }
                    } );
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x1804 ),
                                             reinterpret_cast<void*>( assembly::asmAdjustFieldItemParams ) );
                break;
            }

            // d_a_demo_item.rel
            // Item held in Link's hand upon giving/recieving it
            case 0x3F:
            {
                libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + 0x1E50 ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustCreateItemParamsStart ),
                                                     reinterpret_cast<void*>( assembly::asmAdjustCreateItemParamsEnd ) );
                break;
            }
            // d_a_obj_bosswarp.rel
            // Post-Boss Cutscene
            case 0x5B:
            {
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x1884 ),
                                             reinterpret_cast<void*>( libtp::tp::d_item::execItemGet ) );
                performStaticASMReplacement( relPtrRaw + 0x1888, 0x480000A8 );     // b 0xA8
                // Replace dungeon reward that is given after beating a boss and show the appropriate text.
                break;
            }
            // d_a_npc_bouS.rel
            // Inside Bo's House
            case 0x121:
            {
                // Prevent Bo from talking after the chest has been opened
                performStaticASMReplacement( relPtrRaw + 0x1A44, 0x48000028 );     // b 0x28
                break;
            }
            // d_a_npc_pouya.rel
            // Jovani
            case 0x15C:
            {
                // Branch to a custom function that checks for the 20 soul flag as well as soul count.
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x14D4 ),
                                             reinterpret_cast<void*>( assembly::asmCheck60PoeReward ) );
                break;
            }
            // d_a_npc_ykm.rel
            // Yeto
            case 0x17F:
            {
                // Prevent Yeto from leaving the dungeon if the player has the boss key
                performStaticASMReplacement( relPtrRaw + 0x1524, 0x38600000 );     // li r3,0
                break;
            }
            // d_a_npc_ykw.rel
            // Yeta
            case 0x180:
            {
                // Prevent Yeta from leaving the dungeon if the player has the boss key
                performStaticASMReplacement( relPtrRaw + 0x1038, 0x38600000 );

                performStaticASMReplacement( relPtrRaw + 0x1000, 0x386000ED );     // li r3,0
                break;
            }
            // d_a_e_md.rel
            // SPR Suit of Armor
            case 0xD0:
            {
                if ( libtp::tp::d_a_alink::checkStageName(
                         libtp::data::stage::allStages[libtp::data::stage::stageIDs::Snowpeak_Ruins] ) )
                {
                    // Branch to code to create actor if we are in snowpeak ruins, regardless of BossFlags value.
                    performStaticASMReplacement( relPtrRaw + 0x14B8, 0x4800001c );     // b 0x1C
                }

                break;
            }
            // d_a_e_mk.rel
            // Ook
            case 0xD2:
            {
                // Transform back into link if you are wolf when defeating Ook
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x4A88 ),
                                             reinterpret_cast<void*>( assembly::asmTransformOokWolf ) );

                break;
            }
            // d_a_obj_swBallC.rel
            // Light Sword Cutscene
            case 0x280:
            {
                // The cutscene gives link the MS during the cutscene by default, so we just nop out the link to the function.
                performStaticASMReplacement( relPtrRaw + 0xB50, 0x60000000 );
                break;
            }
            // d_a_npc_rafrel.rel
            // Auru
            case 0x15F:
            {
                performStaticASMReplacement(
                    relPtrRaw + 0x6C4,
                    0x38600131 );     // set auru to check for whether he gave the player the item to spawn.
                break;
            }
            // d_a_obj_smallkey.rel
            // Freestanding Small Keys
            case 0x26D:
            {
                performStaticASMReplacement(
                    relPtrRaw + 0xC88,
                    0x48000058 );     // patch instruction to prevent game from removing bulblin camp key.
                break;
            }
            // d_a_b_bq.rel
            // Diababa
            case 0x8B:
            {
                // Transform back into link if you are wolf when defeating Diababa
                libtp::patch::writeStandardBranches( reinterpret_cast<void*>( relPtrRaw + 0x21B8 ),
                                                     reinterpret_cast<void*>( assembly::asmTransformDiababaWolfStart ),
                                                     reinterpret_cast<void*>( assembly::asmTransformDiababaWolfEnd ) );

                break;
            }

            // d_a_obj_Lv5Key.rel
            // Snowpeak Ruins Small Key Lock
            case 0x189:
            {
                // Prevent Snowpeak Ruins Small Key softlock
                return_daObjLv5Key_c__Wait =
                    libtp::patch::hookFunction( reinterpret_cast<void ( * )( libtp::tp::rel::d_a_obj_Lv5Key::daObjLv5Key_c* )>(
                                                    relPtrRaw + d_a_obj_Lv5Key__Wait_offset ),
                                                []( libtp::tp::rel::d_a_obj_Lv5Key::daObjLv5Key_c* lv5KeyPtr )
                                                {
                                                    float playerPos[3];
                                                    libtp::tp::d_map_path_dmap::getMapPlayerPos( playerPos );

                                                    // Will compare xPos if 0x4000 & yRot is nonzero (lock is on x-axis).
                                                    // Will compare zPos if 0x4000 & yRot is zero (lock is on z-axis).
                                                    // Will compare greater if 0x8000 & yRot is nonzero.
                                                    // This implementation reduces instruction count to 49 compared to naive
                                                    // approach's 86.

                                                    bool isCompareX = lv5KeyPtr->mCollisionRot.y & 0x4000;
                                                    bool isCompareGreater = lv5KeyPtr->mCollisionRot.y & 0x8000;

                                                    float* playerAxisPos = nullptr;
                                                    float* lockPos = nullptr;

                                                    if ( isCompareX )
                                                    {
                                                        playerAxisPos = &playerPos[0];
                                                        lockPos = &( lv5KeyPtr->mCurrent.mPosition.x );
                                                    }
                                                    else
                                                    {
                                                        playerAxisPos = &playerPos[2];
                                                        lockPos = &( lv5KeyPtr->mCurrent.mPosition.z );
                                                    }

                                                    bool swapDoorSides = false;

                                                    if ( isCompareGreater )
                                                    {
                                                        if ( *playerAxisPos > *lockPos + 17 )
                                                        {
                                                            swapDoorSides = true;
                                                            *lockPos += 34;
                                                        }
                                                    }
                                                    else if ( *playerAxisPos < *lockPos - 17 )
                                                    {
                                                        swapDoorSides = true;
                                                        *lockPos -= 34;
                                                    }

                                                    if ( swapDoorSides )
                                                    {
                                                        lv5KeyPtr->mCollisionRot.y ^= 0x8000;       // facing
                                                        lv5KeyPtr->mCurrent.mAngle.y ^= 0x8000;     // speed direction
                                                    }

                                                    // Call original function
                                                    return_daObjLv5Key_c__Wait( lv5KeyPtr );
                                                } );
                break;
            }
            // d_a_midna.rel
            // Midna
            case 0x33:
            {
                checkNpcTransform = reinterpret_cast<CMEB>( relPtrRaw + 0x8A0C );
                break;
            }
            // d_a_e_s1.rel
            // Shadow Beast
            case 0xE2:
            {
                if ( libtp::tp::d_a_alink::checkStageName(
                         libtp::data::stage::allStages[libtp::data::stage::stageIDs::Upper_Zoras_River] ) )
                {
                    // Set human flags After Defeating Shadow Beasts By Iza
                    libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x407C ),
                                                 reinterpret_cast<void*>( assembly::asmAdjustIzaWolf ) );
                }
                break;
            }
            // d_a_obj_drop.rel
            // Tear of Light
            case 0x1B7:
            {
                // set wait timer to 1
                performStaticASMReplacement( relPtrRaw + 0x0FCC, 0x38000001 );     // li r4, 1
                performStaticASMReplacement( relPtrRaw + 0x1038, 0x38000001 );     // li r4, 1

                // set y_pos of drop to be at ground level
                performStaticASMReplacement( relPtrRaw + 0x2474, 0x00000000 );
                break;
            }

            // d_a_kytag03.rel
            case 0x10C:
            {
                // Modify draw function to draw the Reekfish path so long as we have smelled the fish once.
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x66C ),
                                             reinterpret_cast<void*>( assembly::asmShowReekfishPath ) );
                break;
            }
            // d_a_npc_ks.rel
            // Red Bow Monkey
            case 0x14A:
            {
                // Prevent the game from triggering the 4 monkeys cutscene in the lobby.
                performStaticASMReplacement( relPtrRaw + 0x9CE8, 0x2c030001 );     // cmpwi r3,1
                break;
            }
            // d_a_npc_gwolf.rel
            // Golden Wolf
            case 0x13B:
            {
                // Change the flag that the faron wolf checks for when it spawns.
                performStaticASMReplacement( relPtrRaw + 0x5B80,
                                             0x01EB01EC );     // static values. 0x01EB for faron wolf and 0x01EC for ordon wolf
                break;
            }
        }
    }

    void onRELUnlink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        (void) randomizer;

        switch ( dmc->moduleInfo->id )
        {
            // d_a_obj_Lv5Key.rel
            // Snowpeak Ruins Small Key Lock
            case 0x189:
            {
                return_daObjLv5Key_c__Wait = libtp::patch::unhookFunction( return_daObjLv5Key_c__Wait );
                break;
            }
            // d_a_midna.rel
            // Midna
            case 0x33:
            {
                checkNpcTransform = nullptr;
                break;
            }
            // d_a_obj_life_container.rel
            // Heart Pieces/Containers
            case 0x35:
            {
                return_daObjLifeContainer_c__Create = libtp::patch::unhookFunction( return_daObjLifeContainer_c__Create );
                return_daObjLifeContainer_c__setEffect = libtp::patch::unhookFunction( return_daObjLifeContainer_c__setEffect );
                break;
            }
        }
    }

    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        randomizer->overrideDZX( chunkTypeInfo );
        loadCustomActors();
    }

    int32_t onPoe( rando::Randomizer* randomizer, uint8_t flag )
    {
        if ( getCurrentSeed( randomizer ) )
        {
            return randomizer->getPoeItem( flag );
        }
        else
        {
            // Default item
            return static_cast<int32_t>( libtp::data::items::Poe_Soul );
        }
    }

    uint8_t onSkyCharacter( rando::Randomizer* randomizer )
    {
        if ( getCurrentSeed( randomizer ) )
        {
            return randomizer->getSkyCharacter();
        }
        else
        {
            // Default item
            return static_cast<int32_t>( libtp::data::items::Ancient_Sky_Book_Partly_Filled );
        }
    }

    void onARC( rando::Randomizer* randomizer, void* data, int32_t roomNo, rando::FileDirectory fileDirectory )
    {
        randomizer->overrideARC( reinterpret_cast<uint32_t>( data ), fileDirectory, roomNo );
    }

    void onBugReward( rando::Randomizer* randomizer, uint32_t msgEventAddress, uint8_t bugID )
    {
        if ( getCurrentSeed( randomizer ) )
        {
            uint8_t itemID = randomizer->overrideBugReward( bugID );
            *reinterpret_cast<uint16_t*>( ( *reinterpret_cast<uint32_t*>( msgEventAddress + 0xA04 ) + 0x3580 ) + 0x6 ) =
                itemID;     // Change Big Wallet Item
            *reinterpret_cast<uint16_t*>( ( *reinterpret_cast<uint32_t*>( msgEventAddress + 0xA04 ) + 0x3628 ) + 0x6 ) =
                itemID;     // Change Giant Wallet Item
            *reinterpret_cast<uint16_t*>( ( *reinterpret_cast<uint32_t*>( msgEventAddress + 0xA04 ) + 0x35c8 ) + 0x6 ) =
                itemID;     // Change Purple Rupee Item
            *reinterpret_cast<uint16_t*>( ( *reinterpret_cast<uint32_t*>( msgEventAddress + 0xA04 ) + 0x35F0 ) + 0x6 ) =
                itemID;     // Change Orange Rupee Item
        }
    }

    void onHiddenSkill( rando::Randomizer* randomizer, uint16_t eventIndex )
    {
        if ( getCurrentSeed( randomizer ) )
        {
            libtp::tp::d_item::execItemGet( randomizer->getHiddenSkillItem( eventIndex ) );
        }
    }

    void setSaveFileEventFlag( uint16_t flag )
    {
        libtp::tp::d_save::onEventBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.event_flags, flag );
    }

    void onAdjustFieldItemParams( libtp::tp::f_op_actor::fopAc_ac_c* fopAC, void* daObjLife )
    {
        if ( !getCurrentSeed( randomizer ) )
        {
            return;
        }

        using namespace libtp::data::stage;
        using namespace libtp::data::items;

        if ( libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Hyrule_Field] ) ||
             libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Upper_Zoras_River] ) ||
             libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Sacred_Grove] ) ||
             libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Stallord] ) ||
             libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Zant_Main_Room] ) )
        {
            *reinterpret_cast<uint16_t*>( reinterpret_cast<uint32_t>( fopAC ) + 0x962 ) =
                0x226;                  // Y Rotation Speed modifier. 0x226 is the value used when the item is on the ground.
            fopAC->mGravity = 0.0f;     // gravity
        }
        uint8_t itemID = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( fopAC ) + 0x92A );

        // Must check for foolish items first, as they will use the item id of the item they are copying
        itemID = rando::getFoolishItemModelId( itemID );

        switch ( itemID )
        {
            case Heart_Container:
            case Piece_of_Heart:
            case Arrows_10:
            case Arrows_20:
            case Arrows_30:
            {
                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x7c ) = 1.0f;     // scale
                break;
            }

            case Heros_Bow:
            {
                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x7c ) = 1.5f;     // scale
                break;
            }

            case Master_Sword:
            case Master_Sword_Light:
            case Mirror_Piece_2:
            case Mirror_Piece_3:
            case Mirror_Piece_4:
            {
                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x7c ) = 0.7;     // scale
                break;
            }
            default:
            {
                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x7c ) = 2.0f;     // scale
                break;
            }
        }
    }

    void onAdjustCreateItemParams( void* daDitem )
    {
        if ( !getCurrentSeed( randomizer ) )
        {
            return;
        }

        using namespace libtp::data::items;

        uint8_t itemID = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( daDitem ) + 0x92A );
        switch ( itemID )
        {
            case Mirror_Piece_2:
            case Mirror_Piece_3:
            case Mirror_Piece_4:
            {
                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daDitem ) + 0x4EC ) = 0.05f;     // scale
                break;
            }

            case Master_Sword:
            case Master_Sword_Light:
            {
                *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daDitem ) + 0x4EC ) = 0.001f;     // scale
                break;
            }
            default:
            {
                break;
            }
        }
    }

    bool proc_query022( void* unk1, void* unk2, int32_t unk3 )
    {
        // Check to see if currently in one of the Ordon interiors
        if ( libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Ordon_Village_Interiors] ) )
        {
            // Check to see if ckecking for the Iron Boots
            uint16_t item = *reinterpret_cast<uint16_t*>( reinterpret_cast<uint32_t>( unk2 ) + 0x4 );

            if ( item == libtp::data::items::Iron_Boots )
            {
                // Return false so that the door in Bo's house can be opened without having the
                // Iron Boots
                return false;
            }
        }
        return mod::return_query022( unk1, unk2, unk3 );
    }

    int32_t proc_query023( void* unk1, void* unk2, int32_t unk3 )
    {
        // return the original function as we need its value
        int32_t numBombs = mod::return_query023( unk1, unk2, unk3 );
        // Check to see if currently in one of the Kakariko interiors
        if ( libtp::tools::playerIsInRoomStage(
                 1,
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Kakariko_Village_Interiors] ) )
        {
            // If player has not bought Barnes' Bomb Bag, we want to allow them to be able to get the check.
            if ( ( !libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::BOUGHT_BARNES_BOMB_BAG ) ) )
            {
                return false;
            }
            // If the player has bought the bomb bag check, we won't allow them to get the check, regardless of if they
            // have bombs or not
            else
            {
                if ( numBombs == 0 )
                {
                    return 1;
                }
                else
                {
                    return mod::return_query023( unk1, unk2, unk3 );
                }
            }
        }

        // Call original function
        return mod::return_query023( unk1, unk2, unk3 );
    }

    bool proc_query042( void* unk1, void* unk2, int32_t unk3 )
    {
        // Check to see if currently in one of the Ordon interiors
        rando::Seed* seed;
        if ( seed = getCurrentSeed( randomizer ), seed )
        {
            if ( seed->m_Header->transformAnywhere )
            {
                return 0;
            }
        }
        return mod::return_query042( unk1, unk2, unk3 );
    }

    bool proc_isDungeonItem( libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit )
    {
        using namespace libtp::data::stage;

        switch ( memBit )
        {
            case 3:     // Boss Defeated
            {
                const char* dungeonStages[] = { allStages[stageIDs::Forest_Temple],
                                                allStages[stageIDs::Ook],
                                                allStages[stageIDs::Goron_Mines],
                                                allStages[stageIDs::Dangoro],
                                                allStages[stageIDs::Lakebed_Temple],
                                                allStages[stageIDs::Deku_Toad],
                                                allStages[stageIDs::Arbiters_Grounds],
                                                allStages[stageIDs::Death_Sword],
                                                allStages[stageIDs::Snowpeak_Ruins],
                                                allStages[stageIDs::Darkhammer],
                                                allStages[stageIDs::Temple_of_Time],
                                                allStages[stageIDs::Darknut],
                                                allStages[stageIDs::City_in_the_Sky],
                                                allStages[stageIDs::Aeralfos],
                                                allStages[stageIDs::Palace_of_Twilight],
                                                allStages[stageIDs::Phantom_Zant_1],
                                                allStages[stageIDs::Phantom_Zant_2] };
                uint32_t totalDungeonStages = sizeof( dungeonStages ) / sizeof( dungeonStages[0] );
                for ( uint32_t i = 0; i < totalDungeonStages; i++ )
                {
                    if ( libtp::tp::d_a_alink::checkStageName( dungeonStages[i] ) )
                    {
                        return false;
                    }
                }
                break;
            }

            case 4:     // Heart Container Collected
            {
                return false;
            }

            case 7:     // Miniboss defeated
            {
                if ( libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Forest_Temple] ) )
                {
                    const uint8_t currentRoom = libtp::tp::d_kankyo::env_light.currentRoom;

                    if ( ( ( currentRoom == 3 ) || ( currentRoom == 1 ) ) &&
                         ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mEvtManager.mRoomNo != 0 ) )
                    {
                        return false;
                    }
                    else if ( currentRoom == 2 )
                    {
                        return false;
                    }
                }
                break;
            }

            default:
            {
                break;
            }
        }
        // Call original function
        return mod::return_isDungeonItem( memBitPtr, memBit );
    }

    void loadCustomActors()
    {
        using namespace libtp;
        if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Faron_Woods] ) )
        {
            tools::SpawnActor( 0, EponaActr );
        }
    }

    void loadCustomRoomActors()
    {
        using namespace libtp;
        if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Lake_Hylia] ) )
        {
            if ( libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::SKY_CANNON_REPAIRED ) )
            {
                // Manually spawn Auru if the Lake is in the Repaired Cannon state as his actor is not in the DZX for that
                // layer.
                tools::SpawnActor( 0, AuruActr );
            }

            // Spawn a red rupee behind Fyer's house that allows the player to use his cannon to leave the lake which prevents a
            // softlock.
            tools::SpawnActor( 0, ItemActr );
        }
        else if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Hyrule_Field] ) &&
                  ( !tp::d_save::isEventBit( &tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.event_flags,
                                             data::flags::CLEARED_ELDIN_TWILIGHT ) ) )
        {
            libtp::tp::dzx::ACTR localGanonBarrierActor;
            memcpy( &localGanonBarrierActor, &GanonBarrierActor, sizeof( libtp::tp::dzx::ACTR ) );
            tools::SpawnActor( 7, localGanonBarrierActor );
            localGanonBarrierActor.pos[2] -= 270.f;
            tools::SpawnActor( 7, localGanonBarrierActor );
            localGanonBarrierActor.pos[2] -= 270.f;
            tools::SpawnActor( 7, localGanonBarrierActor );
        }
        else if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Faron_Woods] ) &&
                  ( tp::d_save::isEventBit( &tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.event_flags,
                                            data::flags::ORDON_DAY_2_OVER ) ) )
        {
            tools::SpawnActor( 6, ForestGWolfActr );
        }
        else if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Castle_Town_Shops] ) )
        {
            tools::SpawnActor( 6, ImpPoeActr );
        }
        else if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Bulblin_Camp] ) &&
                  !libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::ESCAPED_BURNING_TENT_IN_BULBLIN_CAMP ) )
        {
            tools::SpawnActor( 1, CampBoarActr );
        }
    }

    void loadCustomRoomSCOBs()
    {
        using namespace libtp;
        if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Hyrule_Field] ) &&
             libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::MIDNAS_DESPERATE_HOUR_COMPLETED ) )
        {
            tools::SpawnSCOB( 3, HorseJumpScob );
        }
    }

    bool haveItem( uint8_t item )
    {
        return libtp::tp::d_item::checkItemGet( item, 1 );
    }

    void handleQuickTransform()
    {
        libtp::tp::d_a_alink::daAlink* linkMapPtr = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mPlayer;

        // Ensure that Link is loaded on the map.
        if ( !linkMapPtr )
        {
            return;
        }

        // Ensure that link is not in a cutscene.
        if ( libtp::tp::d_a_alink::checkEventRun( linkMapPtr ) )
        {
            return;
        }

        // Check to see if Link has the ability to transform.
        if ( !libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::TRANSFORMING_UNLOCKED ) )
        {
            return;
        }

        // Ensure there is a proper pointer to the Z Button Alpha.
        uint32_t zButtonAlphaPtr = reinterpret_cast<uint32_t>( libtp::tp::d_meter2_info::wZButtonPtr );
        if ( !zButtonAlphaPtr )
        {
            return;
        }

        zButtonAlphaPtr = *reinterpret_cast<uint32_t*>( zButtonAlphaPtr + 0x10C );
        if ( !zButtonAlphaPtr )
        {
            return;
        }

        // Ensure that the Z Button is not dimmed
        float zButtonAlpha = *reinterpret_cast<float*>( zButtonAlphaPtr + 0x720 );
        if ( zButtonAlpha != 1.f )
        {
            return;
        }

        // Make sure Link is not underwater or talking to someone.
        if ( libtp::tp::d_a_alink::linkStatus->status != 0x1 )
        {
            return;
        }

        // The game will crash if trying to quick transform while holding the Ball and Chain
        if ( linkMapPtr->mEquipItem == libtp::data::items::Ball_and_Chain )
        {
            return;
        }

        // Make sure Link isn't riding anything (horse, boar, etc.)
        if ( libtp::tp::d_camera::checkRide( linkMapPtr ) )
        {
            return;
        }

        if ( randoIsEnabled( randomizer ) )
        {
            if ( randomizer->m_Seed->m_Header->transformAnywhere )
            {
                // Allow transforming regardless of whether there are people around
                libtp::tp::d_a_alink::procCoMetamorphoseInit( linkMapPtr );
                return;
            }
            else
            {
                CMEB tempCMEB = checkNpcTransform;
                if ( tempCMEB )
                {
                    // Use the game's default checks for if the player can currently transform
                    if ( !tempCMEB( libtp::tp::d_a_player::m_midnaActor ) )
                    {
                        return;
                    }
                }
            }
        }

        // Check if the player has scared someone in the current area in wolf form
        if ( ( libtp::tp::d_kankyo::env_light.mEvilPacketEnabled & 0x80 ) != 0 )
        {
            return;
        }

        libtp::tp::d_a_alink::procCoMetamorphoseInit( linkMapPtr );
    }

    libtp::tp::d_resource::dRes_info_c* getObjectResInfo( const char* arcName )
    {
        return getResInfo( arcName, libtp::tp::d_com_inf_game::dComIfG_gameInfo.mResControl.mObjectInfo, 0x80 );
    }

    void handleTimeOfDayChange()
    {
        using namespace libtp::tp::d_com_inf_game;
        if ( libtp::tp::d_stage::GetTimePass() )
        {
            if ( timeChange == 0 )     // No point in changing the values if we are already changing the time
            {
                if ( !libtp::tp::d_kankyo::dKy_daynight_check() )     // Day time
                {
                    timeChange = 1;                                      // Changing to night
                    libtp::tp::d_kankyo::env_light.mTimeSpeed = 1.f;     // Increase time speed
                }
                else
                {
                    timeChange = 2;                                      // Changing to day
                    libtp::tp::d_kankyo::env_light.mTimeSpeed = 1.f;     // Increase time speed
                }
            }
        }
        else
        {
            if ( !libtp::tp::d_kankyo::dKy_daynight_check() )     // Day time
            {
                dComIfG_gameInfo.save.save_file.player.player_status_b.skyAngle = 285;
            }
            else
            {
                dComIfG_gameInfo.save.save_file.player.player_status_b.skyAngle = 105;
            }
            dComIfG_gameInfo.play.mNextStage.enabled |= 0x1;
        }
    }

    void handleTimeSpeed()
    {
        using namespace libtp::tp::d_com_inf_game;
        if ( !libtp::tp::d_kankyo::dKy_daynight_check() )     // Day time
        {
            if ( timeChange == 2 )     // We want it to be day time
            {
                libtp::tp::d_kankyo::env_light.mTimeSpeed = 0.012f;     // Set time speed to normal
                timeChange = 0;
            }
        }
        else
        {
            if ( timeChange == 1 )     // We want it to be night time
            {
                libtp::tp::d_kankyo::env_light.mTimeSpeed = 0.012f;     // Set time speed to normal
                timeChange = 0;
            }
        }
    }

    bool checkFoolItemFreeze()
    {
        libtp::tp::d_a_alink::daAlink* linkMapPtr = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mPlayer;

        // Ensure that Link is loaded on the map.
        if ( !linkMapPtr )
        {
            return false;
        }

        // Ensure that link is not in a cutscene.
        if ( libtp::tp::d_a_alink::checkEventRun( linkMapPtr ) )
        {
            return false;
        }

        // Make sure Link isn't riding anything (horse, boar, etc.)
        if ( libtp::tp::d_camera::checkRide( linkMapPtr ) )
        {
            return false;
        }

        // Check if Midna has actually been unlocked and is on the Z button
        // This is needed because the Z button will always be dimmed if she has not been unlocked
        if ( libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::MIDNA_ACCOMPANIES_WOLF ) )
        {
            // Ensure there is a proper pointer to the Z Button Alpha.
            uint32_t zButtonAlphaPtr = reinterpret_cast<uint32_t>( libtp::tp::d_meter2_info::wZButtonPtr );
            if ( !zButtonAlphaPtr )
            {
                return false;
            }

            zButtonAlphaPtr = *reinterpret_cast<uint32_t*>( zButtonAlphaPtr + 0x10C );
            if ( !zButtonAlphaPtr )
            {
                return false;
            }

            // Ensure that the Z Button is not dimmed
            float zButtonAlpha = *reinterpret_cast<float*>( zButtonAlphaPtr + 0x720 );
            if ( zButtonAlpha != 1.f )
            {
                return false;
            }
        }

        // Make sure Link is not underwater or talking to someone.
        if ( libtp::tp::d_a_alink::linkStatus->status != 0x1 )
        {
            return false;
        }

        return true;
    }

    void drawWindow( int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color )
    {
        // Make sure the background window exists
        libtp::tp::J2DPicture::J2DPicture* tempBgWindow = bgWindow;
        if ( !tempBgWindow )
        {
            return;
        }

        // Set the window color
        tempBgWindow->setWhiteColor( color );
        tempBgWindow->setBlackColor( color );

        // Convert x, y, width, and height to floats
        constexpr int32_t numValues = 4;
        int32_t values[numValues] = { x, y, width, height };
        float valuesOut[numValues];

        for ( int32_t i = 0; i < numValues; i++ )
        {
            valuesOut[i] = intToFloat( values[i] );
        }

        // Draw the window
        libtp::tp::J2DPicture::J2DPicture_draw( tempBgWindow,
                                                valuesOut[0],
                                                valuesOut[1],
                                                valuesOut[2],
                                                valuesOut[3],
                                                false,
                                                false,
                                                false );
    }

    void drawText( const char* text, int32_t x, int32_t y, uint32_t color, bool drawBorder, float textSize )
    {
        // The font takes a bit to load, so it won't be loaded immediately at boot
        void* font = libtp::tp::m_Do_ext::mDoExt_getMesgFont();
        if ( !font )
        {
            return;
        }

        if ( drawBorder )
        {
            uint8_t alpha = color & 0xFF;
            uint32_t borderColor;

            if ( color < 0x80000000 )
            {
                borderColor = 0xFFFFFF00 | alpha;     // White
            }
            else
            {
                borderColor = 0x00000000 | alpha;     // Black
            }

            for ( int32_t i = -1, j = -1; i <= 1; j++ )
            {
                drawText( text, x + i, y + j, borderColor, textSize );
                if ( j == 1 )
                {
                    i += 2;
                    j = -2;
                }
            }
        }

        using namespace libtp::tp::J2DTextBox;

        // Allocate the memory to the back of the heap to avoid possible fragmentation
        // Align to uint64_t, as it is the largest variable type used in the J2DPane class
        J2DTextBox* tempTextBox = new ( -sizeof( uint64_t ) ) J2DTextBox;

        tempTextBox->setSolidColor( color );
        tempTextBox->setLineSpacing( textSize );
        tempTextBox->setFontSize( textSize, textSize );
        tempTextBox->setString( text );
        J2DTextBox_setFont( tempTextBox, font );

        J2DTextBox_draw1( tempTextBox, intToFloat( x ), intToFloat( y ) );

        // Must manually call the destructor, as it takes auto-generated parameters
        // The destructor clears the memory used by tempTextBox if true is passed in
        J2DTextBox_dt( tempTextBox, static_cast<int16_t>( true ) );
    }

    void drawText( const char* text, int32_t x, int32_t y, uint32_t color, float textSize )
    {
        drawText( text, x, y, color, false, textSize );
    }

    int32_t getCurrentAreaNodeId()
    {
        int32_t stageIndex = libtp::tools::getStageIndex( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mStage );
        if ( stageIndex >= 0 )
        {
            return static_cast<int32_t>( libtp::data::stage::regionID[stageIndex] );
        }
        else
        {
            return -1;
        }
    }

    uint8_t* getNodeMemoryFlags( const libtp::data::stage::AreaNodesID nodeId,
                                 const libtp::data::stage::AreaNodesID currentAreaNodeId )
    {
        using namespace libtp::data::items;
        libtp::tp::d_save::dSv_info_c* saveDataPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        uint8_t* memoryFlags;
        if ( nodeId == currentAreaNodeId )
        {
            memoryFlags = saveDataPtr->memory.temp_flags.memoryFlags;
        }
        else     // We are not in the correct node, so use the appropriate region node
        {
            memoryFlags = saveDataPtr->save_file.area_flags[static_cast<uint32_t>( nodeId )].temp_flags.memoryFlags;
        }

        return memoryFlags;
    }

    KEEP_FUNC uint16_t getPauseRupeeMax( libtp::tp::d_save::dSv_player_status_a_c* plyrStatus )
    {
        using namespace libtp::data::items;
        Wallets current_wallet;

        current_wallet = plyrStatus->currentWallet;
        if ( current_wallet < ( Wallets::BIG_WALLET | Wallets::GIANT_WALLET ) )
        {
            if ( current_wallet == Wallets::BIG_WALLET )
            {
                return 600;
            }
            if ( current_wallet == Wallets::WALLET )
            {
                return 300;
            }
            if ( current_wallet < ( Wallets::BIG_WALLET | Wallets::GIANT_WALLET ) )
            {
                return 1000;
            }
        }
        return 0;
    }

    KEEP_FUNC void performStaticASMReplacement( uint32_t memoryOffset, uint32_t value )
    {
        *reinterpret_cast<uint32_t*>( memoryOffset ) = value;

        // Clear the cache for the modified value
        // Assembly instructions need to clear the instruction cache as well
        libtp::memory::clear_DC_IC_Cache( reinterpret_cast<uint32_t*>( memoryOffset ), sizeof( uint32_t ) );
    }

}     // namespace mod::events