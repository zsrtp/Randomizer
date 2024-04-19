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
#include "tp/m_do_controller_pad.h"
#include "tp/d_a_npc.h"
#include "asm_templates.h"
#include "tp/rel/ids.h"
#include "rando/customItems.h"
#include "tp/f_op_actor_iter.h"
#include "tp/d_pane_class.h"
#include "game_patch/game_patch.h"
#include "tp/m_do_printf.h"

namespace mod::events
{
    // REL patching trampolines
    daObjLv5Key_Wait_Def return_daObjLv5Key_c__Wait = nullptr;
    daObjLifeContainer_Create_Def return_daObjLifeContainer_c__Create = nullptr;
    daObjLifeContainer_setEffect_Def return_daObjLifeContainer_c__setEffect = nullptr;
    daObjLifeContainer_initActionOrderGetDemo_Def return_daObjLifeContainer_c__initActionOrderGetDemo = nullptr;
    daMidna_checkMetamorphoseEnableBase_Def daMidna_c__checkMetamorphoseEnableBase = nullptr;

    // Custom Ganon Barrier to prevent the player from trying to enter Lanayru Twilight during Eldin Twilight
    libtp::tp::dzx::ACTR GanonBarrierActor =
        {"Obj_gb", 0x800F0601, 10778.207f, 3096.82666f, -62651.0078f, static_cast<int16_t>(-164), 0x4000, 0, 0xFFFF};

    // Auru actor that is added to the Post-Cannon repair state of Lake Hylia
    libtp::tp::dzx::ACTR AuruActr =
        {"Rafrel", 0x00001D01, -116486.945f, -13860.f, 58533.0078f, 0, static_cast<int16_t>(0xCCCD), 0, 0xFFFF};

    // item actor template
    libtp::tp::dzx::ACTR ItemActr =
        {"item", 0xF3FFFF04, -108290.086f, -18654.748f, 45935.2969f, 0, static_cast<int16_t>(0x1), 0x3F, 0xFFFF};

    // Epona actor template
    libtp::tp::dzx::ACTR EponaActr = {"Horse", 0x00000F0D, -1200.f, 367.f, 6100.f, 0, -180, 0, 0xFFFF};

    // Horse jump SCOB template
    libtp::tp::dzx::SCOB HorseJumpScob =
        {"Hjump", 0x044FFF02, 5600.f, -5680.f, 52055.f, 0, static_cast<int16_t>(0x4000), 0, 0xFFFF, 0x20, 0x2D, 0x2D, 0xFF};

    // Golden Wolf actor placed in Faron Woods.
    libtp::tp::dzx::ACTR ForestGWolfActr = {"GWolf", 0x05FF01FF, -36714.9023f, 424.03894f, -23698.0273f, 0, 0, 0xFF, 0xFFFF};

    // Poe actor template
    libtp::tp::dzx::ACTR ImpPoeActr = {"E_hp", 0xFF031E00, 4531.19f, -30.f, 2631.961f, 0, 0, 0x0, 0xFFFF};

    // Boar actor template
    libtp::tp::dzx::ACTR CampBoarActr = {"E_wb", 0xFFFFFFFF, 1650.f, 0.f, 1250.f, 0, static_cast<int16_t>(0xA000), 0x0, 0xFFFF};

    // Custom shop sold out actors for shop checks. using actor template: 0x48 bytes in memory due to instructions
    // Creating new actors uses less memory than modifying a template due to the amount of memory used by instructions.
    // (0x28 vs 0x48 bytes)
    libtp::tp::dzx::ACTR KakShopSlot2Actr =
        {"TGSPITM", 0x02FFFFFF, -650.f, 450.f, -500.f, 0x147, static_cast<int16_t>(0x8000), 0x3AFF, 0xFFFF};

    // Sign Actors
    libtp::tp::dzx::ACTR SignActor = {"Obj_kn2",
                                      0xFFFFFFFF,
                                      -2088.f,
                                      0.8535f,
                                      7535.77f,
                                      static_cast<int16_t>(0xFFFE), // Flow Node ID
                                      static_cast<int16_t>(0xD556),
                                      0,
                                      0xFFFF};

    libtp::tp::dzx::ACTR MstrSrdActr = {"mstrsrd", 0x000020110, 0.f, 1700.f, -5435.f, 0x147, 0x0, 0x0, 0xFFFF};

    uint8_t timeChange = 0;

    void onLoad(rando::Randomizer* randomizer)
    {
        randomizer->onStageLoad();
        timeChange = 0;
        rando::goldenWolfItemReplacement.itemActorId = -1;
    }

    void offLoad(rando::Randomizer* randomizer)
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        if (!getCurrentSeed(randomizer))
        {
            return;
        }

        using namespace libtp::tp;
        using namespace libtp::data;

        libtp::tp::d_com_inf_game::dComIfG_play* playPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.play;
        d_save::dSv_info_c* savePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;
        d_stage::dStage_startStage* startStagePtr = &playPtr->mStartStage;

        const char* currentStage = startStagePtr->mStage;
        const int32_t currentRoom = startStagePtr->mRoomNo;
        const int32_t currentPoint = startStagePtr->mPoint;

        // Check if the seed is already applied to the save-file (flags etc.)
        // Try to do it otherwise
        if (!randomizer->m_SeedInit && (strcmp(currentStage, "F_SP108") == 0) && (currentRoom == 1) && (currentPoint == 0x15))
        {
            randomizer->initSave();
        }

        if ((strcmp(playPtr->mNextStage.mStage, "F_SP103") == 0) && (currentRoom == 1) &&
            (currentPoint == 0x1)) // If we are spawning in Ordon for the first time.
        {
            float* skyAnglePtr = &savePtr->save_file.player.player_status_b.skyAngle;

            switch (randomizer->m_Seed->m_Header->startingTimeOfDay)
            {
                case rando::StartingTimeOfDay::Morning:
                {
                    *skyAnglePtr = 105.f;
                    break;
                }
                case rando::StartingTimeOfDay::Noon:
                {
                    *skyAnglePtr = 180.f;
                    break;
                }
                case rando::StartingTimeOfDay::Night:
                {
                    *skyAnglePtr = 0.f;
                    break;
                }
                default: // Evening
                {
                    break;
                }
            }

            if (d_com_inf_game::dComIfGs_isEventBit(flags::ORDON_DAY_2_OVER))
            {
                savePtr->save_file.player.horse_place.mPos.y = -1000.f; // Place Epona out of bounds in Faron if Talo has been
                                                                        // rescued since the game will spawn her in the air.
            }
        }

        // Check to see if currently in City and our last visited stage was not City.
        if ((strcmp(currentStage, stage::allStages[stage::StageIDs::City_in_the_Sky]) == 0) && (currentRoom == 0x0) &&
            (currentPoint == 0x3))
        {
            d_save::offSwitch_dSv_memBit(&savePtr->memory.temp_flags,
                                         0xA); // Fan in main room active

            d_save::offSwitch_dSv_memBit(&savePtr->memory.temp_flags,
                                         0xF); // Main Room 1F explored
        }

        randomizer->overrideEventARC();
    }

    void onRELLink(rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc)
    {
        using namespace libtp::tp::rel::relIDs;
        randomizer->overrideREL();

        // Static REL overrides and patches
        const libtp::gc_wii::os_module::OSModuleInfo* modulePtr = dmc->mModule;
        const uint32_t relPtrRaw = reinterpret_cast<uint32_t>(modulePtr);
        const auto stagesPtr = &libtp::data::stage::allStages[0];

        switch (modulePtr->id)
        {
            // Door - Shutter
            case D_A_DOOR_SHUTTER:
            {
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Snowpeak_Ruins]))
                {
                    // Set the call to checkOpenDoor to always return true when in SPR
                    performStaticASMReplacement(relPtrRaw + 0xD68, ASM_LOAD_IMMEDIATE(3, 1));
                }

                break;
            }

            // Treasure Chests
            case D_A_TBOX:
            {
                // Nop out the bne- that causes chests to play the cutscene for big items.
                performStaticASMReplacement(relPtrRaw + 0xA58, ASM_NOP);
                break;
            }

            // d_kankyo tag 11
            case D_A_KYTAG11:
            {
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Hyrule_Field]))
                {
                    // Nop out the instruction that causes the time flow to not consider the mTimeSpeed variable in Field.
                    performStaticASMReplacement(relPtrRaw + 0x2CC, ASM_NOP);
                }

                break;
            }

            // Generic Poe
            case D_A_E_HP:
            {
                libtp::patch::writeStandardBranches(relPtrRaw + e_hp_ExecDead_liOffset,
                                                    assembly::asmAdjustPoeItemStart,
                                                    assembly::asmAdjustPoeItemEnd);

                // Disable Poe increment (handled through item_get_func; see game_patches)
                performStaticASMReplacement(relPtrRaw + e_hp_ExecDead_incOffset, ASM_NOP);

                break;
            }

            // Arbiter's Poe
            case D_A_E_PO:
            {
                libtp::patch::writeStandardBranches(relPtrRaw + e_po_ExecDead_liOffset,
                                                    assembly::asmAdjustAGPoeItemStart,
                                                    assembly::asmAdjustAGPoeItemEnd);

                // Disable Poe increment (handled through item_get_func; see game_patches)
                performStaticASMReplacement(relPtrRaw + e_po_ExecDead_incOffset, ASM_NOP);
                break;
            }

            // Lakebed Temple Boss Door
            case D_A_OBJ_KSHUTTER:
            {
                // Nop out the instruction that stores the new total small key value when the game attempts to
                // remove a small key from the inventory when opening the boss door
                if (libtp::tools::playerIsInRoomStage(2, stagesPtr[libtp::data::stage::StageIDs::Lakebed_Temple]))
                {
                    performStaticASMReplacement(relPtrRaw + 0x1198, ASM_NOP); // Previous: subi r0,r3,1
                }
                break;
            }

            // Puppet Zelda
            case D_A_E_HZELDA:
            {
                // nop out the greater than branch so that Zelda will always throw a Ball if she is able to
                performStaticASMReplacement(relPtrRaw + 0xA94, ASM_NOP); // Previous: bge

                // nop out the addition of f1 (the random number of frames) to f0 (the base number of frames) so that there is
                // always only 100 frames between each of Zelda's attacks.
                performStaticASMReplacement(relPtrRaw + 0x8EC, ASM_NOP); // Previous: bfadds f0,f0,f1
                break;
            }

            // Agitha
            case D_A_NPC_INS:
            {
                mod::rando::Seed* seed;
                if (seed = getCurrentSeed(randomizer), seed)
                {
                    if (seed->m_numBugRewardChecks > 0)
                    {
                        libtp::patch::writeStandardBranches(relPtrRaw + 0x21B8,
                                                            assembly::asmAdjustBugRewardStart,
                                                            assembly::asmAdjustBugRewardEnd);
                    }
                }
                break;
            }

            // Fishing Hole Rod
            case D_A_MG_ROD:
            {
                libtp::patch::writeBranchBL(relPtrRaw + 0xB2B0, libtp::tp::d_item::execItemGet);

                // Branch over rng check instructions from uki_main for 100% bottle guarantee
                performStaticASMReplacement(relPtrRaw + 0xBFAC, ASM_BRANCH(0x18));
                break;
            }

            // Owl Statues
            case D_A_TAG_STATUE_EVT:
            {
                // Replace sky character
                performStaticASMReplacement(relPtrRaw + 0xB7C, ASM_BRANCH(0x20));

                libtp::patch::writeStandardBranches(relPtrRaw + 0xB9C,
                                                    assembly::asmAdjustSkyCharacterStart,
                                                    assembly::asmAdjustSkyCharacterEnd);
                break;
            }

            // Heart Pieces/Containers
            case D_A_OBJ_LIFE_CONTAINER:
            {
                // Adjust freestanding heart field model height based on the current item being created
                return_daObjLifeContainer_c__Create = libtp::patch::hookFunction(
                    reinterpret_cast<daObjLifeContainer_Create_Def>(relPtrRaw + 0x5D0),
                    [](void* daObjLifePtr)
                    {
                        using namespace libtp::data;
                        using namespace rando;

                        uint32_t itemID = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x92A);

                        // Must check for foolish items first, as they will use the item id of the item they are copying
                        itemID = rando::getFoolishItemModelId(static_cast<uint8_t>(itemID));

                        const float height = *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4);
                        switch (itemID)
                        {
                            case items::Master_Sword:
                            case items::Master_Sword_Light:
                            case items::Wooden_Shield:
                            case items::Hylian_Shield:
                            case items::Ordon_Shield:
                            case items::Spinner:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 30.f;
                                break;
                            }
                            case items::Wooden_Sword:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 60.f;
                                break;
                            }
                            case items::Ordon_Sword:
                            case customItems::Mirror_Piece_1:
                            case items::Mirror_Piece_2:
                            case items::Mirror_Piece_3:
                            case items::Mirror_Piece_4:
                            case customItems::Fused_Shadow_1:
                            case customItems::Fused_Shadow_2:
                            case customItems::Fused_Shadow_3:
                            case items::Dominion_Rod_Uncharged:
                            case items::Dominion_Rod:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 50.f;
                                break;
                            }

                            case items::Heros_Bow:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 55.f;
                                break;
                            }
                            case items::Boomerang:
                            case items::Fishing_Rod:
                            case items::Big_Quiver:
                            case items::Giant_Quiver:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 40.f;
                                break;
                            }
                            case customItems::Forest_Temple_Small_Key:
                            case customItems::Goron_Mines_Small_Key:
                            case customItems::Lakebed_Temple_Small_Key:
                            case customItems::Arbiters_Grounds_Small_Key:
                            case customItems::Snowpeak_Ruins_Small_Key:
                            case customItems::Temple_of_Time_Small_Key:
                            case customItems::City_in_The_Sky_Small_Key:
                            case customItems::Palace_of_Twilight_Small_Key:
                            case customItems::Hyrule_Castle_Small_Key:
                            case customItems::Forest_Temple_Big_Key:
                            case customItems::Lakebed_Temple_Big_Key:
                            case customItems::Arbiters_Grounds_Big_Key:
                            case customItems::Temple_of_Time_Big_Key:
                            case customItems::City_in_The_Sky_Big_Key:
                            case customItems::Palace_of_Twilight_Big_Key:
                            case customItems::Hyrule_Castle_Big_Key:
                            case items::Small_Key_N_Faron_Gate:
                            case items::Bed_Key:
                            case customItems::Bulblin_Camp_Key:
                            case items::Gate_Keys:
                            case items::Slingshot:
                            case items::Giant_Bomb_Bag:
                            case items::Empty_Bomb_Bag:
                            case items::Goron_Bomb_Bag:
                            case items::Bomb_Bag_Regular_Bombs:
                            case items::Poe_Soul:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 20.f;
                                break;
                            }

                            case items::Magic_Armor:
                            {
                                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4D4) = height + 25.f;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }

                        // Call the original function
                        return return_daObjLifeContainer_c__Create(daObjLifePtr);
                    });

                // Remove glow and sparkle from rupees and Poe Souls
                return_daObjLifeContainer_c__setEffect = libtp::patch::hookFunction(
                    reinterpret_cast<daObjLifeContainer_setEffect_Def>(relPtrRaw + 0x764),
                    [](void* daObjLifePtr)
                    {
                        using namespace libtp::data;

                        const uint32_t itemID = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x92A);

                        switch (itemID)
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
                                // Call the original function
                                return return_daObjLifeContainer_c__setEffect(daObjLifePtr);
                            }
                        }
                    });

                // Handle misc flags when obtaining items
                return_daObjLifeContainer_c__initActionOrderGetDemo = libtp::patch::hookFunction(
                    reinterpret_cast<daObjLifeContainer_initActionOrderGetDemo_Def>(relPtrRaw + 0x1224),
                    [](void* daObjLifePtr)
                    {
                        // Call the original function immediately
                        const bool ret = return_daObjLifeContainer_c__initActionOrderGetDemo(daObjLifePtr);

                        // Check if the golden wolf item is spawned
                        rando::GoldenWolfItemReplacement* goldenWolfItemReplacementPtr = &rando::goldenWolfItemReplacement;
                        int32_t actorId = goldenWolfItemReplacementPtr->itemActorId;

                        if (actorId != -1)
                        {
                            // Check if the golden wolf item was collected
                            if (actorId == *reinterpret_cast<int32_t*>(reinterpret_cast<uint32_t>(daObjLifePtr) + 0x4))
                            {
                                // The golden wolf item was collected, so set the flag for it and clear the map marker for it
                                goldenWolfItemReplacementPtr->itemActorId = -1;
                                libtp::tp::d_a_npc::daNpcT_onEvtBit(goldenWolfItemReplacementPtr->flag);

                                libtp::tp::d_com_inf_game::dComIfG_inf_c* gameInfoPtr =
                                    &libtp::tp::d_com_inf_game::dComIfG_gameInfo;

                                libtp::tp::d_save::offSwitch_dSv_info(
                                    &gameInfoPtr->save,
                                    static_cast<int32_t>(goldenWolfItemReplacementPtr->markerFlag),
                                    libtp::tools::getCurrentRoomNo());
                            }
                        }

                        return ret;
                    });

                libtp::patch::writeBranchBL(relPtrRaw + 0x1804, assembly::asmAdjustFieldItemParams);
                break;
            }

            // Item held in Link's hand upon giving/recieving it
            case D_A_DEMO_ITEM:
            {
                libtp::patch::writeStandardBranches(relPtrRaw + 0x1E50,
                                                    assembly::asmAdjustCreateItemParamsStart,
                                                    assembly::asmAdjustCreateItemParamsEnd);
                break;
            }

            // Post-Boss Portal
            case D_A_OBJ_BOSSWARP:
            {
                // Replace dungeon reward that is given after beating a boss and show the appropriate text.
                libtp::patch::writeBranchBL(relPtrRaw + 0x1884, libtp::tp::d_item::execItemGet);
                performStaticASMReplacement(relPtrRaw + 0x1888, ASM_BRANCH(0xA8));
                break;
            }

            // Bo - Sumo
            case D_A_NPC_BOUS:
            {
                // Prevent Bo from talking after the chest has been opened
                performStaticASMReplacement(relPtrRaw + 0x1A44, ASM_BRANCH(0x28));
                break;
            }

            // Jovani
            case D_A_NPC_POUYA:
            {
                // Branch to a custom function that checks for the 20 soul flag as well as soul count.
                libtp::patch::writeBranchBL(relPtrRaw + 0x14D4, assembly::asmCheck60PoeReward);
                break;
            }

            // Yeto
            case D_A_NPC_YKM:
            {
                // Prevent Yeto from leaving the dungeon if the player has the boss key
                performStaticASMReplacement(relPtrRaw + 0x1524, ASM_LOAD_IMMEDIATE(3, 0));
                break;
            }

            // Yeta
            case D_A_NPC_YKW:
            {
                // Prevent Yeta from leaving the dungeon if the player has the boss key
                performStaticASMReplacement(relPtrRaw + 0x1038, ASM_LOAD_IMMEDIATE(3, 0)); // li r3,0
                break;
            }

            // SPR Suit of Armor
            case D_A_E_MD:
            {
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Snowpeak_Ruins]))
                {
                    // Branch to code to create actor if we are in snowpeak ruins, regardless of BossFlags value.
                    performStaticASMReplacement(relPtrRaw + 0x14B8, ASM_BRANCH(0x1C));
                }

                break;
            }

            // Ook
            case D_A_E_MK:
            {
                // Transform back into link if you are wolf when defeating Ook
                libtp::patch::writeBranchBL(relPtrRaw + 0x4A88, assembly::asmTransformOokWolf);
                break;
            }

            // Light Sword Cutscene
            case D_A_OBJ_SWBALLC:
            {
                // The cutscene gives link the MS during the cutscene by default, so we just nop out the link to the function.
                performStaticASMReplacement(relPtrRaw + 0xB50, ASM_NOP);
                break;
            }

            // Auru
            case D_A_NPC_RAFREL:
            {
                performStaticASMReplacement(
                    relPtrRaw + 0x6C4,
                    ASM_LOAD_IMMEDIATE(3, 0x131)); // set auru to check for whether he gave the player the item to spawn.
                break;
            }

            // Freestanding Small Keys
            case D_A_OBJ_SMALLKEY:
            {
                performStaticASMReplacement(
                    relPtrRaw + 0xC88,
                    ASM_BRANCH(0x58)); // patch instruction to prevent game from removing bulblin camp key.
                break;
            }

            // Diababa
            case D_A_B_BQ:
            {
                // Transform back into link if you are wolf when defeating Diababa
                libtp::patch::writeStandardBranches(relPtrRaw + 0x21B8,
                                                    assembly::asmTransformDiababaWolfStart,
                                                    assembly::asmTransformDiababaWolfEnd);

                break;
            }

            // Snowpeak Ruins Small Key Lock
            case D_A_OBJ_LV5KEY:
            {
                // Prevent Snowpeak Ruins Small Key softlock
                return_daObjLv5Key_c__Wait =
                    libtp::patch::hookFunction(reinterpret_cast<daObjLv5Key_Wait_Def>(relPtrRaw + d_a_obj_Lv5Key__Wait_offset),
                                               [](libtp::tp::rel::d_a_obj_Lv5Key::daObjLv5Key_c* lv5KeyPtr)
                                               {
                                                   float playerPos[3];
                                                   libtp::tp::d_map_path_dmap::getMapPlayerPos(playerPos);

                                                   // Will compare xPos if 0x4000 & yRot is nonzero (lock is on x-axis).
                                                   // Will compare zPos if 0x4000 & yRot is zero (lock is on z-axis).
                                                   // Will compare greater if 0x8000 & yRot is nonzero.
                                                   // This implementation reduces instruction count to 49 compared to naive
                                                   // approach's 86.

                                                   const int32_t collisionRotY = lv5KeyPtr->mCollisionRot.y;
                                                   const bool isCompareX = collisionRotY & 0x4000;
                                                   const bool isCompareGreater = collisionRotY & 0x8000;

                                                   float* playerAxisPos = nullptr;
                                                   float* lockPos = nullptr;

                                                   if (isCompareX)
                                                   {
                                                       playerAxisPos = &playerPos[0];
                                                       lockPos = &lv5KeyPtr->mCurrent.mPosition.x;
                                                   }
                                                   else
                                                   {
                                                       playerAxisPos = &playerPos[2];
                                                       lockPos = &lv5KeyPtr->mCurrent.mPosition.z;
                                                   }

                                                   bool swapDoorSides = false;

                                                   if (isCompareGreater)
                                                   {
                                                       if (*playerAxisPos > *lockPos + 17.f)
                                                       {
                                                           swapDoorSides = true;
                                                           *lockPos += 34.f;
                                                       }
                                                   }
                                                   else if (*playerAxisPos < *lockPos - 17.f)
                                                   {
                                                       swapDoorSides = true;
                                                       *lockPos -= 34.f;
                                                   }

                                                   if (swapDoorSides)
                                                   {
                                                       lv5KeyPtr->mCollisionRot.y ^= 0x8000;   // facing
                                                       lv5KeyPtr->mCurrent.mAngle.y ^= 0x8000; // speed direction
                                                   }

                                                   // Call original function
                                                   return_daObjLv5Key_c__Wait(lv5KeyPtr);
                                               });
                break;
            }

            // Midna
            case D_A_MIDNA:
            {
                daMidna_c__checkMetamorphoseEnableBase =
                    reinterpret_cast<daMidna_checkMetamorphoseEnableBase_Def>(relPtrRaw + 0x8A0C);

                // Adjust checkMetamorphoseEnableBase to not check for nearby NPCs if transformAnywhere is enabled
                libtp::patch::writeBranchBL(relPtrRaw + 0x8A64, events::handleTransformAnywhere);
                break;
            }

            // Shadow Beast
            case D_A_E_S1:
            {
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Upper_Zoras_River]))
                {
                    // Set human flags After Defeating Shadow Beasts By Iza
                    libtp::patch::writeBranchBL(relPtrRaw + 0x407C, assembly::asmAdjustIzaWolf);
                }
                break;
            }

            // Tear of Light
            case D_A_OBJ_DROP:
            {
                // set wait timer to 1
                performStaticASMReplacement(relPtrRaw + 0x0FCC, ASM_LOAD_IMMEDIATE(0, 1));
                performStaticASMReplacement(relPtrRaw + 0x1038, ASM_LOAD_IMMEDIATE(0, 1));

                // set y_pos of drop to be at ground level
                performStaticASMReplacement(relPtrRaw + 0x2474, 0x00000000);
                break;
            }

            case D_A_KYTAG03:
            {
                // Modify draw function to draw the Reekfish path so long as we have smelled the fish once.
                libtp::patch::writeBranchBL(relPtrRaw + 0x66C, assembly::asmShowReekfishPath);
                break;
            }

            // Red Bow Monkey
            case D_A_NPC_KS:
            {
                // Prevent the game from triggering the 4 monkeys cutscene in the lobby.
                performStaticASMReplacement(relPtrRaw + 0x9CE8, ASM_COMPARE_WORD_IMMEDIATE(3, 1));
                break;
            }

            // d_a_npc_gwolf.rel
            // Golden Wolf
            case D_A_NPC_GWOLF:
            {
                // Change the flag that the faron wolf checks for when it spawns. The original value, is structured like this:
                // XXXXYYYY  where XXXX is the flag for the Ending Blow and YYYY is for having howled at the DMT stone. Since we
                // don't want the wolf to disappear once we have the ending blow, it was changed to use an unused flag in the
                // event bit list.
                performStaticASMReplacement(relPtrRaw + 0x5B80,
                                            0x01EB01EC); // static values. 0x01EB for faron wolf and 0x01EC for ordon wolf

                // If a seed is not loaded, then use vanilla behavior
                if (!getCurrentSeed(randomizer))
                {
                    break;
                }

                // Apply an ASM patch to d_a_npc_GWolf::isDelete that checks for if the wolf should spawn and spawn a
                // freestanding item in it's place.
                libtp::patch::writeBranchBL(relPtrRaw + 0x20AC, assembly::asmReplaceGWolfWithItem);

                // Remove the instruction after the asm patch, as it is no longer needed
                performStaticASMReplacement(relPtrRaw + 0x20B0, ASM_NOP);

                // Branch to have isDelete return if the return value condition listed in asmReplaceGWolfWithItem is not met
                performStaticASMReplacement(relPtrRaw + 0x20B8, ASM_BRANCH_EQUAL_MINUS(0x38));
                break;
            }

            // d_obj_master_sword.rel
            // Master Sword Freestanding Actor
            case D_A_OBJ_MASTER_SWORD:
            {
                // If a seed is not loaded, then use vanilla behavior
                if (!getCurrentSeed(randomizer))
                {
                    break;
                }

                // Apply an ASM patch to d_a_Obj_Master_Sword::executeWait to give the player two items and delete the Master
                // Sword actor instead of trying to play the purification cutscene.
                libtp::patch::writeStandardBranches(relPtrRaw + 0x254,
                                                    assembly::asmGiveMasterSwordItemsStart,
                                                    assembly::asmGiveMasterSwordItemsEnd);

                // Branch over the code that gives Link the master sword if it has been pulled
                performStaticASMReplacement(relPtrRaw + 0xCA0, ASM_BRANCH(0x80));
                break;
            }
        }
    }

    void onRELUnlink(rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc)
    {
        (void)randomizer;
        using namespace libtp::tp::rel::relIDs;

        switch (dmc->mModule->id)
        {
            // Snowpeak Ruins Small Key Lock
            case D_A_OBJ_LV5KEY:
            {
                return_daObjLv5Key_c__Wait = libtp::patch::unhookFunction(return_daObjLv5Key_c__Wait);
                break;
            }

            // Midna
            case D_A_MIDNA:
            {
                daMidna_c__checkMetamorphoseEnableBase = nullptr;
                break;
            }

            // Heart Pieces/Containers
            case D_A_OBJ_LIFE_CONTAINER:
            {
                return_daObjLifeContainer_c__Create = libtp::patch::unhookFunction(return_daObjLifeContainer_c__Create);
                return_daObjLifeContainer_c__setEffect = libtp::patch::unhookFunction(return_daObjLifeContainer_c__setEffect);

                return_daObjLifeContainer_c__initActionOrderGetDemo =
                    libtp::patch::unhookFunction(return_daObjLifeContainer_c__initActionOrderGetDemo);
                break;
            }
        }
    }

    void onDZX(rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo)
    {
        randomizer->overrideDZX(chunkTypeInfo);
    }

    int32_t onPoe(rando::Randomizer* randomizer, uint8_t flag)
    {
        if (getCurrentSeed(randomizer))
        {
            return randomizer->getPoeItem(flag);
        }
        else
        {
            // Default item
            return static_cast<int32_t>(libtp::data::items::Poe_Soul);
        }
    }

    uint8_t onSkyCharacter(rando::Randomizer* randomizer)
    {
        if (getCurrentSeed(randomizer))
        {
            return randomizer->getSkyCharacter();
        }
        else
        {
            // Default item
            return static_cast<int32_t>(libtp::data::items::Ancient_Sky_Book_Partly_Filled);
        }
    }

    void onARC(rando::Randomizer* randomizer, void* data, int32_t roomNo, rando::FileDirectory fileDirectory)
    {
        randomizer->overrideARC(reinterpret_cast<uint32_t>(data), fileDirectory, roomNo);
    }

    void onBugReward(rando::Randomizer* randomizer, uint32_t msgEventAddress, uint8_t bugID)
    {
        if (getCurrentSeed(randomizer))
        {
            const uint8_t itemID = randomizer->overrideBugReward(bugID);
            uint32_t addressRaw = *reinterpret_cast<uint32_t*>(msgEventAddress + 0xA04);

            *reinterpret_cast<uint16_t*>((addressRaw + 0x3580) + 0x6) = itemID; // Change Big Wallet Item
            *reinterpret_cast<uint16_t*>((addressRaw + 0x3628) + 0x6) = itemID; // Change Giant Wallet Item
            *reinterpret_cast<uint16_t*>((addressRaw + 0x35c8) + 0x6) = itemID; // Change Purple Rupee Item
            *reinterpret_cast<uint16_t*>((addressRaw + 0x35F0) + 0x6) = itemID; // Change Orange Rupee Item
        }
    }

    void onHiddenSkill(rando::Randomizer* randomizer, void* daNpcGWolfPtr, int16_t flag, uint32_t markerFlag)
    {
        randomizer->getHiddenSkillItem(daNpcGWolfPtr, flag, markerFlag);
    }

    void setSaveFileEventFlag(uint16_t flag)
    {
        libtp::tp::d_save::onEventBit(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.mEvent, flag);
    }

    void onAdjustFieldItemParams(libtp::tp::f_op_actor::fopAc_ac_c* fopAC, void* daObjLife)
    {
        using namespace libtp::data::stage;
        using namespace libtp::data::items;
        using namespace rando::customItems;

        if (!getCurrentSeed(randomizer))
        {
            return;
        }

        const auto stagesPtr = &libtp::data::stage::allStages[0];

        if (libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Hyrule_Field]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Upper_Zoras_River]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Sacred_Grove]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Stallord]) ||
            libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Zant_Main_Room]))
        {
            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(fopAC) + 0x962) =
                0x226; // Y Rotation Speed modifier. 0x226 is the value used when the item is on the ground.

            fopAC->mGravity = 0.0f; // gravity
        }
        uint32_t itemID = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(fopAC) + 0x92A);

        // Must check for foolish items first, as they will use the item id of the item they are copying
        itemID = rando::getFoolishItemModelId(static_cast<uint8_t>(itemID));

        switch (itemID)
        {
            case Heart_Container:
            case Piece_of_Heart:
            case Arrows_10:
            case Arrows_20:
            case Arrows_30:
            {
                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLife) + 0x7c) = 1.0f; // scale
                break;
            }

            case Heros_Bow:
            {
                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLife) + 0x7c) = 1.5f; // scale
                break;
            }

            case Master_Sword:
            case Master_Sword_Light:
            case Mirror_Piece_1:
            case Mirror_Piece_2:
            case Mirror_Piece_3:
            case Mirror_Piece_4:
            {
                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLife) + 0x7c) = 0.7f; // scale
                break;
            }
            default:
            {
                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daObjLife) + 0x7c) = 2.0f; // scale
                break;
            }
        }
    }

    void onAdjustCreateItemParams(void* daDitem)
    {
        if (!getCurrentSeed(randomizer))
        {
            return;
        }

        using namespace libtp::data::items;
        using namespace rando::customItems;

        const uint32_t itemID = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(daDitem) + 0x92A);
        switch (itemID)
        {
            case Mirror_Piece_1:
            case Mirror_Piece_2:
            case Mirror_Piece_3:
            case Mirror_Piece_4:
            {
                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daDitem) + 0x4EC) = 0.05f; // scale
                break;
            }

            case Master_Sword:
            case Master_Sword_Light:
            {
                *reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daDitem) + 0x4EC) = 0.001f; // scale
                break;
            }
            default:
            {
                break;
            }
        }
    }

    int32_t proc_query022(void* unk1, void* unk2, int32_t unk3)
    {
        using namespace libtp::data;
        using namespace libtp::tp;

        // Check to see if currently in one of the Ordon interiors
        if (d_a_alink::checkStageName(stage::allStages[stage::StageIDs::Ordon_Village_Interiors]))
        {
            // Check to see if checking for the Iron Boots
            const uint32_t item = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(unk2) + 0x4);

            if (item == items::Iron_Boots)
            {
                // Return false so that the door in Bo's house can be opened without having the
                // Iron Boots
                return 0;
            }
        }

        return mod::return_query022(unk1, unk2, unk3);
    }

    int32_t proc_query023(void* unk1, void* unk2, int32_t unk3)
    {
        // Call the original function immediately as we need its value
        const int32_t numBombs = mod::return_query023(unk1, unk2, unk3);

        // Check to see if currently in one of the Kakariko interiors
        if (libtp::tools::playerIsInRoomStage(
                1,
                libtp::data::stage::allStages[libtp::data::stage::StageIDs::Kakariko_Village_Interiors]))
        {
            // If player has not bought Barnes' Bomb Bag, we want to allow them to be able to get the check.
            if ((!libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::BOUGHT_BARNES_BOMB_BAG)))
            {
                return 0;
            }

            // If the player has bought the bomb bag check, we won't allow them to get the check, regardless of if they
            // have bombs or not
            else if (numBombs == 0)
            {
                return 1;
            }
        }

        return numBombs;
    }

    int32_t proc_query025(void* unk1, void* unk2, int32_t unk3)
    {
        using namespace libtp::data::stage;

        const auto stagesPtr = &allStages[0];

        // Check to see if currently in one of the Ordon interiors
        if (libtp::tools::playerIsInRoomStage(3, stagesPtr[StageIDs::Kakariko_Village_Interiors]))
        {
            // Return 0 so the player can buy the red potion item from the shop.
            return 0;
        }

        return mod::return_query025(unk1, unk2, unk3);
    }

    int32_t proc_query042(void* unk1, void* unk2, int32_t unk3)
    {
        if (checkValidTransformAnywhere())
        {
            // Return false to allow transforming infront of NPCs using Midna's transform option
            return 0;
        }

        return mod::return_query042(unk1, unk2, unk3);
    }

    bool proc_isDungeonItem(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit)
    {
        using namespace libtp::data::stage;
        using namespace libtp::data::flags;

        switch (memBit)
        {
            case BOSS_DEFEATED:
            {
                static const char* dungeonStages[] = {allStages[StageIDs::Forest_Temple],
                                                      allStages[StageIDs::Ook],
                                                      allStages[StageIDs::Goron_Mines],
                                                      allStages[StageIDs::Dangoro],
                                                      allStages[StageIDs::Lakebed_Temple],
                                                      allStages[StageIDs::Deku_Toad],
                                                      allStages[StageIDs::Arbiters_Grounds],
                                                      allStages[StageIDs::Death_Sword],
                                                      allStages[StageIDs::Snowpeak_Ruins],
                                                      allStages[StageIDs::Darkhammer],
                                                      allStages[StageIDs::Temple_of_Time],
                                                      allStages[StageIDs::Darknut],
                                                      allStages[StageIDs::City_in_the_Sky],
                                                      allStages[StageIDs::Aeralfos],
                                                      allStages[StageIDs::Palace_of_Twilight],
                                                      allStages[StageIDs::Phantom_Zant_1],
                                                      allStages[StageIDs::Phantom_Zant_2]};

                constexpr uint32_t totalDungeonStages = sizeof(dungeonStages) / sizeof(dungeonStages[0]);
                for (uint32_t i = 0; i < totalDungeonStages; i++)
                {
                    if (libtp::tp::d_a_alink::checkStageName(dungeonStages[i]))
                    {
                        return false;
                    }
                }
                break;
            }

            case HEART_CONTAINER_COLLECTED:
            {
                return false;
            }

            case MINIBOSS_DEFEATED:
            {
                if (libtp::tp::d_a_alink::checkStageName(allStages[StageIDs::Forest_Temple]))
                {
                    if (libtp::tools::getCurrentRoomNo() < 4)
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
        return mod::return_isDungeonItem(memBitPtr, memBit);
    }

    void proc_onDungeonItem(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit)
    {
        using namespace libtp;
        using namespace libtp::data::flags;
        using namespace libtp::data::stage;

        // Make sure the randomizer is loaded/enabled and a seed is loaded
        rando::Seed* seedPtr;
        if (seedPtr = getCurrentSeed(randomizer), !seedPtr)
        {
            return mod::return_onDungeonItem(memBitPtr, memBit);
        }

        const auto stagesPtr = &allStages[0];
        tp::d_save::dSv_info_c* savePtr = &tp::d_com_inf_game::dComIfG_gameInfo.save;

        if (memBitPtr == &savePtr->memory.temp_flags)
        {
            switch (memBit)
            {
                case BOSS_DEFEATED:
                {
                    if (seedPtr->m_Header->castleRequirements ==
                        rando::CastleEntryRequirements::HC_All_Dungeons) // All Dungeons
                    {
                        // Check to see if the player has completed all of the other dungeons, if so, destroy the barrier.
                        libtp::tp::d_save::dSv_memory_c* mSavePtr = savePtr->save_file.mSave;
                        uint32_t numDungeons = 0;

                        for (int32_t i = 0x10; i < 0x18; i++)
                        {
                            if (libtp::tp::d_save::isDungeonItem(&mSavePtr[i].temp_flags, 3))
                            {
                                numDungeons++;
                            }
                        }

                        if (numDungeons == 7) // We check for 7 instead of 8 because when this code runs, the temp_flags for
                                              // the current stage has not been updated with the boss flag value yet.
                        {
                            events::setSaveFileEventFlag(libtp::data::flags::BARRIER_GONE);
                        }
                    }
                    if (tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Stallord]))
                    {
                        uint32_t agDungeonReward = randomizer->getEventItem(rando::customItems::Mirror_Piece_1);
                        randomizer->addItemToEventQueue(agDungeonReward);
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        mod::return_onDungeonItem(memBitPtr, memBit);
    }

    void loadCustomActors(void* mStatus_roomControl)
    {
        using namespace libtp;
        using namespace libtp::data::stage;

        const auto stagesPtr = &allStages[0];
        tp::dzx::ACTR localSignActor;
        memcpy(&localSignActor, &SignActor, sizeof(tp::dzx::ACTR));

        if (tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Faron_Woods]))
        {
            tools::spawnActor(0, EponaActr);
        }
        else if (libtp::tools::playerIsInRoomStage(0, stagesPtr[libtp::data::stage::StageIDs::Ordon_Village]))
        {
            tp::dzx::ACTR localEponaActor;
            memcpy(&localEponaActor, &EponaActr, sizeof(tp::dzx::ACTR));

            localEponaActor.parameters = 0x148;
            tools::spawnActor(0, localEponaActor);
        }

        // The actors in this case are actors who need to be spawned in even if the area is in a specific set state no matter
        // what (i.e PoT, HC, etc. and cannot be spawned in with the mStageData actors due to checking for angles and the like,
        // which causes a crash.)
        if (randomizer && (reinterpret_cast<uint32_t>(mStatus_roomControl) !=
                           reinterpret_cast<uint32_t>(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStageData)))
        {
            switch (randomizer->m_Seed->m_StageIDX)
            {
                case StageIDs::Palace_of_Twilight:
                {
                    localSignActor.pos.x = 1808.76245f;
                    localSignActor.pos.y = -208.901459f;
                    localSignActor.pos.z = 11813.2744f;
                    localSignActor.rot[1] = static_cast<int16_t>(0xA971);
                    tools::spawnActor(0, localSignActor);
                    break;
                }

                case StageIDs::Hyrule_Castle:
                {
                    localSignActor.pos.x = 0.0f;
                    localSignActor.pos.y = 25.f;
                    localSignActor.pos.z = 11625.f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                    tools::spawnActor(11, localSignActor);
                    break;
                }
            }
        }
    }

    void loadCustomRoomActors(rando::Randomizer* randomizer)
    {
        using namespace libtp;
        using namespace libtp::data::stage;

        if (!getCurrentSeed(randomizer))
        {
            return;
        }

        tp::dzx::ACTR localSignActor;
        memcpy(&localSignActor, &SignActor, sizeof(tp::dzx::ACTR));

        const int32_t roomIDX = tools::getCurrentRoomNo();
        switch (randomizer->m_Seed->m_StageIDX)
        {
            case StageIDs::Lake_Hylia:
            {
                if (tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::SKY_CANNON_REPAIRED))
                {
                    // Manually spawn Auru if the Lake is in the Repaired Cannon state as his actor is not in the DZX for that
                    // layer.
                    tools::spawnActor(0, AuruActr);
                }

                // Spawn a red rupee behind Fyer's house that allows the player to use his cannon to leave the lake which
                // prevents a softlock.
                tools::spawnActor(0, ItemActr);

                localSignActor.pos.x = -109203.461f;
                localSignActor.pos.y = -7220.f;
                localSignActor.pos.z = 33083.7344f;
                localSignActor.rot[1] = static_cast<int16_t>(0x64B5);
                tools::spawnActor(0, localSignActor);

                if (roomIDX == 1) // Lanayru Spring
                {
                    localSignActor.pos.x = -309.997833f;
                    localSignActor.pos.y = -1614.82178f;
                    localSignActor.pos.z = 157.970795f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x8000);
                    tools::spawnActor(1, localSignActor);
                }
                break;
            }

            case StageIDs::Hyrule_Field:
            {
                if (roomIDX == 0) // Eldin Field
                {
                    if (!tp::d_save::isEventBit(&tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.mEvent,
                                                data::flags::CLEARED_ELDIN_TWILIGHT))
                    {
                        libtp::tp::dzx::ACTR localGanonBarrierActor;
                        memcpy(&localGanonBarrierActor, &GanonBarrierActor, sizeof(libtp::tp::dzx::ACTR));

                        tools::spawnActor(7, localGanonBarrierActor);

                        localGanonBarrierActor.pos.z -= 270.f;
                        tools::spawnActor(7, localGanonBarrierActor);

                        localGanonBarrierActor.pos.z -= 270.f;
                        tools::spawnActor(7, localGanonBarrierActor);
                    }
                    localSignActor.pos.x = -12433.2744f;
                    localSignActor.pos.y = -1075.2218f;
                    localSignActor.pos.z = 20885.7129f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x8000);
                    tools::spawnActor(0, localSignActor);
                }

                if (roomIDX == 6) // Faron Field
                {
                    localSignActor.pos.x = -46039.4922f;
                    localSignActor.pos.y = -9250.f;
                    localSignActor.pos.z = 81859.2891f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x8000);
                    tools::spawnActor(6, localSignActor);
                }

                if (roomIDX == 3) // Kakariko Gorge
                {
                    localSignActor.pos.x = -11394.7832f;
                    localSignActor.pos.y = -3258.73096f;
                    localSignActor.pos.z = 39702.91995f;
                    localSignActor.rot[1] = static_cast<int16_t>(0xAC70);
                    tools::spawnActor(3, localSignActor);
                }

                if (roomIDX == 7) // North Eldin Hint Sign
                {
                    localSignActor.pos.x = 29691.0742f;
                    localSignActor.pos.y = 661.668;
                    localSignActor.pos.z = -53367.16f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x742B);
                    tools::spawnActor(7, localSignActor);
                }

                if (roomIDX == 10) // Lanayru Field
                {
                    localSignActor.pos.x = -46711.957f;
                    localSignActor.pos.y = 268.4848f;
                    localSignActor.pos.z = -55505.5508f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x85B9);
                    tools::spawnActor(10, localSignActor);
                }

                if (roomIDX == 13) // Great Bridge of Hylia
                {
                    localSignActor.pos.x = -94678.8672f;
                    localSignActor.pos.y = -3900.f;
                    localSignActor.pos.z = 18410.543f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                    tools::spawnActor(13, localSignActor);
                }

                break;
            }

            case StageIDs::Faron_Woods:
            {
                if (tp::d_save::isEventBit(&tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.mEvent,
                                           data::flags::ORDON_DAY_2_OVER))
                {
                    tools::spawnActor(6, ForestGWolfActr);
                }

                if (roomIDX == 4)
                {
                    localSignActor.pos.x = -12423.8467f;
                    localSignActor.pos.y = 273.277985f;
                    localSignActor.pos.z = -11518.958f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x9228);
                    tools::spawnActor(4, localSignActor);
                }
                break;
            }

            case StageIDs::Castle_Town_Shops:
            {
                tools::spawnActor(6, ImpPoeActr);
                break;
            }

            case StageIDs::Bulblin_Camp:
            {
                if (!libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::ESCAPED_BURNING_TENT_IN_BULBLIN_CAMP))
                {
                    tools::spawnActor(1, CampBoarActr);
                }

                localSignActor.pos.x = -568.556152f;
                localSignActor.pos.y = 260.f;
                localSignActor.pos.z = -3969.31f;
                localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                tools::spawnActor(1, localSignActor);
                break;
            }

            case StageIDs::Kakariko_Village_Interiors:
            {
                tools::spawnActor(3, KakShopSlot2Actr);
                break;
            }

            case StageIDs::Kakariko_Village:
            {
                localSignActor.pos.x = -6277.372f;
                localSignActor.pos.y = 2850.f;
                localSignActor.pos.z = -2197.14331f;
                localSignActor.rot[1] = static_cast<int16_t>(0x4000);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Ordon_Village:
            {
                localSignActor.pos.x = 687.89f;
                localSignActor.pos.y = 800.f;
                localSignActor.pos.z = -1424.16f;
                localSignActor.rot[1] = static_cast<int16_t>(0xA019);
                tools::spawnActor(1, localSignActor);
                break;
            }

            case StageIDs::Sacred_Grove:
            {
                localSignActor.pos.x = -1543.f;
                localSignActor.pos.y = 1725.f;
                localSignActor.pos.z = 7964.85498f;
                localSignActor.rot[1] = static_cast<int16_t>(0x4000);
                tools::spawnActor(1, localSignActor);

                if (roomIDX == 1)
                {
                    tools::spawnActor(1, MstrSrdActr);
                }
                break;
            }

            case StageIDs::Kakariko_Graveyard:
            {
                localSignActor.pos.x = 21765.9863f;
                localSignActor.pos.y = 500.f;
                localSignActor.pos.z = -62.247f;
                localSignActor.rot[1] = static_cast<int16_t>(0xC000);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Death_Mountain:
            {
                localSignActor.pos.x = 920.583069f;
                localSignActor.pos.y = 0.745985091f;
                localSignActor.pos.z = 1227.39978f;
                localSignActor.rot[1] = static_cast<int16_t>(0x35A5);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Hidden_Village:
            {
                localSignActor.pos.x = 5161.03f;
                localSignActor.pos.y = 0.f;
                localSignActor.pos.z = -5264.33f;
                localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Outside_Castle_Town:
            {
                if (roomIDX == 8) // Beside Castle Town
                {
                    localSignActor.pos.x = -68194.2109f;
                    localSignActor.pos.y = -1050.f;
                    localSignActor.pos.z = 5603.60645f;
                    localSignActor.rot[1] = static_cast<int16_t>(0xC000);
                    tools::spawnActor(8, localSignActor);
                }
                else if (roomIDX == 16) // South of CT
                {
                    localSignActor.pos.x = -51500.f;
                    localSignActor.pos.y = -5500.f;
                    localSignActor.pos.z = 27368.3086f;
                    localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                    tools::spawnActor(16, localSignActor);
                }
                break;
            }

            case StageIDs::Lake_Hylia_Long_Cave:
            {
                localSignActor.pos.x = -2897.38672f;
                localSignActor.pos.y = -1636.68994f;
                localSignActor.pos.z = -17674.8691f;
                localSignActor.rot[1] = static_cast<int16_t>(0x3E21);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Zoras_Domain:
            {
                localSignActor.pos.x = -2964.84839f;
                localSignActor.pos.y = -2500.f;
                localSignActor.pos.z = 17146.2676f;
                localSignActor.rot[1] = static_cast<int16_t>(0xAF09);
                tools::spawnActor(1, localSignActor);
                break;
            }

            case StageIDs::Fishing_Pond:
            {
                localSignActor.pos.x = -2924.74585f;
                localSignActor.pos.y = 35.f;
                localSignActor.pos.z = 8386.28906f;
                localSignActor.rot[1] = static_cast<int16_t>(0x8000);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Gerudo_Desert:
            {
                localSignActor.pos.x = 20356.23f;
                localSignActor.pos.y = 556.7;
                localSignActor.pos.z = 38694.8047f;
                localSignActor.rot[1] = static_cast<int16_t>(0x0099);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Snowpeak:
            {
                localSignActor.pos.x = 15931.9238f;
                localSignActor.pos.y = -14389.4912f;
                localSignActor.pos.z = -17388.1992f;
                localSignActor.rot[1] = static_cast<int16_t>(0x2C5A);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Cave_of_Ordeals:
            {
                localSignActor.pos.x = -1191.42f;
                localSignActor.pos.y = 1100.f;
                localSignActor.pos.z = -260.65f;
                localSignActor.rot[1] = static_cast<int16_t>(0xE483);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Forest_Temple:
            {
                localSignActor.pos.x = -1972.11682f;
                localSignActor.pos.y = 3150.f;
                localSignActor.pos.z = 7610.9751f;
                localSignActor.rot[1] = static_cast<int16_t>(0x6000);
                tools::spawnActor(0, localSignActor);
                break;
            }

            case StageIDs::Goron_Mines:
            {
                localSignActor.pos.x = 11394.1855f;
                localSignActor.pos.y = 2878.65;
                localSignActor.pos.z = -17913.05f;
                localSignActor.rot[1] = static_cast<int16_t>(0xD556);
                tools::spawnActor(17, localSignActor);
                break;
            }

            case StageIDs::Lakebed_Temple:
            {
                localSignActor.pos.x = -4765.38037f;
                localSignActor.pos.y = -1.21f;
                localSignActor.pos.z = 272.192261f;
                localSignActor.rot[1] = static_cast<int16_t>(0x46B9);
                tools::spawnActor(3, localSignActor);
                break;
            }

            case StageIDs::Arbiters_Grounds:
            {
                localSignActor.pos.x = -349.4044f;
                localSignActor.pos.y = 450.f;
                localSignActor.pos.z = -2876.90771f;
                localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                tools::spawnActor(2, localSignActor);
                break;
            }

            case StageIDs::Snowpeak_Ruins:
            {
                localSignActor.pos.x = -530.f;
                localSignActor.pos.y = 0.f;
                localSignActor.pos.z = -669.69f;
                localSignActor.rot[1] = static_cast<int16_t>(0x0000);
                tools::spawnActor(1, localSignActor);
                break;
            }

            case StageIDs::Temple_of_Time:
            {
                localSignActor.pos.x = -618.9335f;
                localSignActor.pos.y = 725.f;
                localSignActor.pos.z = 3112.2f;
                localSignActor.rot[1] = static_cast<int16_t>(0x8000);
                tools::spawnActor(0, localSignActor);

                // ToT midpoint sign
                tp::dzx::ACTR localSignActor2;
                memcpy(&localSignActor2, &SignActor, sizeof(tp::dzx::ACTR));
                localSignActor2.pos.x = -3885.2157f;
                localSignActor2.pos.y = 4450.f;
                localSignActor2.pos.z = -6353.38135f;
                localSignActor2.rot[1] = static_cast<int16_t>(0x2000);
                tools::spawnActor(4, localSignActor2);
                break;
            }

            case StageIDs::City_in_the_Sky:
            {
                localSignActor.pos.x = 3376.54f;
                localSignActor.pos.y = 0.f;
                localSignActor.pos.z = -12709.0352f;
                localSignActor.rot[1] = static_cast<int16_t>(0xC846);
                tools::spawnActor(2, localSignActor);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    void loadCustomRoomSCOBs()
    {
        using namespace libtp;
        if (tp::d_a_alink::checkStageName(data::stage::allStages[data::stage::StageIDs::Hyrule_Field]) &&
            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::MIDNAS_DESPERATE_HOUR_COMPLETED))
        {
            tools::spawnSCOB(3, HorseJumpScob);
        }
    }

    bool haveItem(uint32_t item)
    {
        return libtp::tp::d_item::checkItemGet(static_cast<uint8_t>(item), 1);
    }

    void handleQuickTransform()
    {
        using namespace libtp::tp::d_com_inf_game;

        rando::Seed* seed;
        if (seed = getCurrentSeed(randomizer), !seed)
        {
            return;
        }

        if (!seed->m_Header->quickTransform)
        {
            return;
        }

        // Ensure that Link is loaded on the map.
        libtp::tp::d_a_alink::daAlink* linkMapPtr = dComIfG_gameInfo.play.mPlayer;
        if (!linkMapPtr)
        {
            return;
        }

        // Ensure that link is not in a cutscene.
        if (libtp::tp::d_a_alink::checkEventRun(linkMapPtr))
        {
            return;
        }

        // Check to see if Link has the ability to transform.
        if (!libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::TRANSFORMING_UNLOCKED))
        {
            return;
        }

        // Ensure there is a proper pointer to the mMeterClass and mpMeterDraw structs in g_meter2_info.
        const libtp::tp::d_meter2::dMeter2_c* meterClassPtr = libtp::tp::d_meter2_info::g_meter2_info.mMeterClass;
        if (!meterClassPtr)
        {
            return;
        }

        const libtp::tp::d_meter2_draw::dMeter2Draw_c* meterDrawPtr = meterClassPtr->mpMeterDraw;
        if (!meterDrawPtr)
        {
            return;
        }

        // Ensure that the Z Button is not dimmed
        const float zButtonAlpha = meterDrawPtr->mZButtonAlpha;
        if (zButtonAlpha != 1.f)
        {
            return;
        }

        // Make sure Link is not underwater or talking to someone.
        switch (linkMapPtr->mProcID)
        {
            case libtp::tp::d_a_alink::PROC_TALK:
            case libtp::tp::d_a_alink::PROC_SWIM_UP:
            case libtp::tp::d_a_alink::PROC_SWIM_DIVE:
            {
                return;
            }
            default:
            {
                break;
            }
        }

        // The game will crash if trying to quick transform while holding the Ball and Chain
        if (linkMapPtr->mEquipItem == libtp::data::items::Ball_and_Chain)
        {
            return;
        }

        // Make sure Link isn't riding anything (horse, boar, etc.)
        if (libtp::tp::d_camera::checkRide(linkMapPtr))
        {
            return;
        }

        if (!checkValidTransformAnywhere())
        {
            if (daMidna_c__checkMetamorphoseEnableBase)
            {
                // Use the game's default checks for if the player can currently transform
                if (!daMidna_c__checkMetamorphoseEnableBase(libtp::tp::d_a_player::m_midnaActor))
                {
                    return;
                }
            }

            // Check if the player has scared someone in the current area in wolf form
            if ((libtp::tp::d_kankyo::env_light.mEvilPacketEnabled & 0x80) != 0)
            {
                return;
            }
        }

        libtp::tp::d_a_alink::procCoMetamorphoseInit(linkMapPtr);
    }

    libtp::tp::d_resource::dRes_info_c* getObjectResInfo(const char* arcName)
    {
        return getResInfo(arcName, libtp::tp::d_com_inf_game::dComIfG_gameInfo.mResControl.mObjectInfo, 0x80);
    }

    void handleTimeOfDayChange()
    {
        using namespace libtp::tp::d_com_inf_game;

        if (libtp::tp::d_stage::GetTimePass())
        {
            if (timeChange == 0) // No point in changing the values if we are already changing the time
            {
                libtp::tp::d_kankyo::EnvLight* envLightPtr = &libtp::tp::d_kankyo::env_light;

                if (!libtp::tp::d_kankyo::dKy_daynight_check()) // Day time
                {
                    timeChange = 1;                // Changing to night
                    envLightPtr->mTimeSpeed = 1.f; // Increase time speed
                }
                else
                {
                    timeChange = 2;                // Changing to day
                    envLightPtr->mTimeSpeed = 1.f; // Increase time speed
                }
            }
        }
        else
        {
            float* skyAnglePtr = &dComIfG_gameInfo.save.save_file.player.player_status_b.skyAngle;

            if (!libtp::tp::d_kankyo::dKy_daynight_check()) // Day time
            {
                *skyAnglePtr = 285.f;
            }
            else
            {
                *skyAnglePtr = 105.f;
            }

            dComIfG_gameInfo.play.mNextStage.enabled |= 0x1;
        }
    }

    void handleTimeSpeed()
    {
        using namespace libtp::tp::d_com_inf_game;

        libtp::tp::d_kankyo::EnvLight* envLightPtr = &libtp::tp::d_kankyo::env_light;
        if (!libtp::tp::d_kankyo::dKy_daynight_check()) // Day time
        {
            if (timeChange == 2) // We want it to be day time
            {
                envLightPtr->mTimeSpeed = 0.012f; // Set time speed to normal
                timeChange = 0;
            }
        }
        else
        {
            if (timeChange == 1) // We want it to be night time
            {
                envLightPtr->mTimeSpeed = 0.012f; // Set time speed to normal
                timeChange = 0;
            }
        }
    }

    bool checkFoolItemFreeze()
    {
        libtp::tp::d_a_alink::daAlink* linkMapPtr = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mPlayer;

        // Ensure that Link is loaded on the map.
        if (!linkMapPtr)
        {
            return false;
        }

        // Ensure that link is not in a cutscene.
        if (libtp::tp::d_a_alink::checkEventRun(linkMapPtr))
        {
            return false;
        }

        // Make sure Link isn't riding anything (horse, boar, etc.)
        if (libtp::tp::d_camera::checkRide(linkMapPtr))
        {
            return false;
        }

        // Check if Midna has actually been unlocked and is on the Z button
        // This is needed because the Z button will always be dimmed if she has not been unlocked
        if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::MIDNA_ACCOMPANIES_WOLF))
        {
            // Ensure there is a proper pointer to the mMeterClass and mpMeterDraw structs in g_meter2_info.
            const libtp::tp::d_meter2::dMeter2_c* meterClassPtr = libtp::tp::d_meter2_info::g_meter2_info.mMeterClass;
            if (!meterClassPtr)
            {
                return false;
            }

            const libtp::tp::d_meter2_draw::dMeter2Draw_c* meterDrawPtr = meterClassPtr->mpMeterDraw;
            if (!meterDrawPtr)
            {
                return false;
            }

            // Ensure that the Z Button is not dimmed
            const float zButtonAlpha = meterDrawPtr->mZButtonAlpha;
            if (zButtonAlpha != 1.f)
            {
                return false;
            }
        }

        // Make sure Link is not underwater or talking to someone.
        switch (linkMapPtr->mProcID)
        {
            case libtp::tp::d_a_alink::PROC_TALK:
            case libtp::tp::d_a_alink::PROC_WOLF_SWIM_MOVE:
            case libtp::tp::d_a_alink::PROC_SWIM_MOVE:
            case libtp::tp::d_a_alink::PROC_SWIM_WAIT:
            case libtp::tp::d_a_alink::PROC_WOLF_SWIM_WAIT:
            case libtp::tp::d_a_alink::PROC_SWIM_UP:
            case libtp::tp::d_a_alink::PROC_SWIM_DIVE:
            {
                return false;
            }
            default:
            {
                break;
            }
        }

        return true;
    }

    void drawWindow(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color)
    {
        // Make sure the background window exists
        libtp::tp::J2DPicture::J2DPicture* tempBgWindow = bgWindow;
        if (!tempBgWindow)
        {
            return;
        }

        // Set the window color
        tempBgWindow->setWhiteColor(color);
        tempBgWindow->setBlackColor(color);

        // Convert x, y, width, and height to floats
        constexpr int32_t numValues = 4;
        const int32_t values[numValues] = {x, y, width, height};
        float valuesOut[numValues];

        for (int32_t i = 0; i < numValues; i++)
        {
            valuesOut[i] = intToFloat(values[i]);
        }

        // Draw the window
        libtp::tp::J2DPicture::J2DPicture_draw(tempBgWindow,
                                               valuesOut[0],
                                               valuesOut[1],
                                               valuesOut[2],
                                               valuesOut[3],
                                               false,
                                               false,
                                               false);
    }

    void drawText(const char* text, int32_t x, int32_t y, uint32_t color, bool drawBorder, float textSize)
    {
        // The font takes a bit to load, so it won't be loaded immediately at boot
        void* font = libtp::tp::m_Do_ext::mDoExt_getMesgFont();
        if (!font)
        {
            return;
        }

        if (drawBorder)
        {
            const uint8_t alpha = color & 0xFF;
            uint32_t borderColor;

            if (color < 0x80000000)
            {
                borderColor = 0xFFFFFF00 | alpha; // White
            }
            else
            {
                borderColor = 0x00000000 | alpha; // Black
            }

            for (int32_t i = -1, j = -1; i <= 1; j++)
            {
                drawText(text, x + i, y + j, borderColor, textSize);
                if (j == 1)
                {
                    i += 2;
                    j = -2;
                }
            }
        }

        using namespace libtp::tp::J2DTextBox;

        // Allocate the memory to the back of the heap to avoid possible fragmentation
        // Align to uint64_t, as it is the largest variable type used in the J2DPane class
        J2DTextBox* tempTextBox = new (-sizeof(uint64_t)) J2DTextBox;

        tempTextBox->setSolidColor(color);
        tempTextBox->setLineSpacing(textSize);
        tempTextBox->setFontSize(textSize, textSize);
        tempTextBox->setString(text);
        J2DTextBox_setFont(tempTextBox, font);

        J2DTextBox_draw1(tempTextBox, intToFloat(x), intToFloat(y));

        // Must manually call the destructor, as it takes auto-generated parameters
        // The destructor clears the memory used by tempTextBox if true is passed in
        J2DTextBox_dt(tempTextBox, static_cast<int16_t>(true));
    }

    void drawText(const char* text, int32_t x, int32_t y, uint32_t color, float textSize)
    {
        drawText(text, x, y, color, false, textSize);
    }

    int32_t getCurrentAreaNodeId()
    {
        int32_t stageIndex = libtp::tools::getStageIndex(libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mStage);
        if (stageIndex >= 0)
        {
            return static_cast<int32_t>(libtp::data::stage::regionID[stageIndex]);
        }
        else
        {
            return -1;
        }
    }

    uint8_t* getNodeMemoryFlags(const libtp::data::stage::AreaNodesID nodeId,
                                const libtp::data::stage::AreaNodesID currentAreaNodeId)
    {
        using namespace libtp::data::items;
        libtp::tp::d_save::dSv_info_c* saveDataPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        uint8_t* memoryFlags;
        if (nodeId == currentAreaNodeId)
        {
            memoryFlags = saveDataPtr->memory.temp_flags.memoryFlags;
        }
        else // We are not in the correct node, so use the appropriate region node
        {
            memoryFlags = saveDataPtr->save_file.mSave[static_cast<uint32_t>(nodeId)].temp_flags.memoryFlags;
        }

        return memoryFlags;
    }

    KEEP_FUNC uint16_t getPauseRupeeMax(libtp::tp::d_save::dSv_player_status_a_c* plyrStatus)
    {
        using namespace libtp::data::items;
        Wallets current_wallet;

        current_wallet = plyrStatus->currentWallet;
        if (current_wallet < (Wallets::BIG_WALLET | Wallets::GIANT_WALLET))
        {
            if (current_wallet == Wallets::BIG_WALLET)
            {
                return 600;
            }
            if (current_wallet == Wallets::WALLET)
            {
                return 300;
            }
            if (current_wallet < (Wallets::BIG_WALLET | Wallets::GIANT_WALLET))
            {
                return 1000;
            }
        }
        return 0;
    }

    KEEP_FUNC uint32_t autoMashThroughText(libtp::tp::m_do_controller_pad::CPadInfo* padInfo)
    {
        using namespace libtp::tp::m_do_controller_pad;

        if (instantTextEnabled)
        {
            // Automash through text if B is held
            if (padInfo->mButtonFlags & PadInputs::Button_B)
            {
                // Return A to immediately jump to the return value in the function
                return PadInputs::Button_A;
            }
        }

        // Restore the overwritten instruction
        return padInfo->mPressedButtonFlags;
    }

    void* handleTransformAnywhere(libtp::tp::f_op_actor_iter::fopAcIt_JudgeFunc unk1, void* unk2)
    {
        if (checkValidTransformAnywhere())
        {
            // Return nullptr to make the calling function return true
            return nullptr;
        }

        // Restore the overwritten instruction
        return libtp::tp::f_op_actor_iter::fopAcIt_Judge(unk1, unk2);
    }

    bool checkValidTransformAnywhere()
    {
        using namespace libtp::data::stage;
        using namespace libtp::tp::d_com_inf_game;

        if (!transformAnywhereEnabled)
        {
            return false;
        }

        // Check if the player is currently playing the Goats minigame
        if (libtp::tp::d_a_alink::checkStageName(allStages[StageIDs::Ordon_Ranch]))
        {
            switch (dComIfG_gameInfo.play.mStartStage.mLayer)
            {
                // Layer 4 or 5 is used when the minigame is taking place
                case 4:
                case 5:
                {
                    // Return false, as the game will crash if the player is in wolf form after the minigame ends
                    return false;
                }
                default:
                {
                    break;
                }
            }
        }

        // Return true, as the bool is set and there are no conflicting scenarios to prevent transformation
        return true;
    }

    KEEP_FUNC void modifyLanternMeterColor(libtp::tp::d_pane_class::CPaneMgr* panePtr,
                                           libtp::tp::JUtility::TColor* color1,
                                           libtp::tp::JUtility::TColor* color2)
    {
        mod::rando::Seed* seed;

        if (seed = getCurrentSeed(randomizer), seed)
        {
            rando::RawRGBTable* rawRGBListPtr = randomizer->m_Seed->m_RawRGBTable;

            uint8_t* lanternColor = reinterpret_cast<uint8_t*>(&rawRGBListPtr->lanternColor);

            if (*reinterpret_cast<uint32_t*>(lanternColor) != 0x502814ff) // Don't set the value if it is already vanilla
            {
                color1->r = lanternColor[0];
                color1->g = lanternColor[1];
                color1->b = lanternColor[2];
                color2->r = lanternColor[0];
                color2->g = lanternColor[1];
                color2->b = lanternColor[2];
            }
        }
        libtp::tp::d_pane_class::setBlackWhite(panePtr, color1, color2);
    }

    KEEP_FUNC void performStaticASMReplacement(uint32_t memoryOffset, uint32_t value)
    {
        *reinterpret_cast<uint32_t*>(memoryOffset) = value;

        // Clear the cache for the modified value
        // Assembly instructions need to clear the instruction cache as well
        libtp::memory::clear_DC_IC_Cache(reinterpret_cast<uint32_t*>(memoryOffset), sizeof(uint32_t));
    }

} // namespace mod::events