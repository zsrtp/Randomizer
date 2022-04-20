#include "events.h"

#include <cinttypes>
#include <cstring>

#include "asm.h"
#include "data/items.h"
#include "data/stages.h"
#include "main.h"
#include "patch.h"
#include "rando/randomizer.h"
#include "tp/d_a_alink.h"
#include "tp/d_a_player.h"
#include "tp/d_camera.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/d_kankyo.h"
#include "tp/d_map_path_dmap.h"
#include "tp/d_meter2_info.h"
#include "tp/dzx.h"
#include "tp/rel/d_a_obj_Lv5Key.h"
#include "user_patch/03_customCosmetics.h"

namespace mod::events
{
    // REL patching trampolines
    void ( *return_daObjLv5Key_c__Wait )( libtp::tp::rel::d_a_obj_Lv5Key::daObjLv5Key_c* _this ) = nullptr;

    void onLoad( rando::Randomizer* randomizer )
    {
        if ( randomizer )
        {
            randomizer->onStageLoad();
        }
    }

    void offLoad( rando::Randomizer* randomizer )
    {
        if ( randomizer )
        {
            // Check if the seed is already applied to the save-file (flags etc.)
            // Try to do it otherwise
            if ( !randomizer->m_SeedInit &&
                 ( strcmp( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mStage, "F_SP108" ) == 0 ) &&
                 ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mRoomNo == 1 ) &&
                 ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mPoint == 0x15 ) )
            {
                randomizer->initSave();
            }
            randomizer->overrideEventARC();
            user_patch::setHUDCosmetics( randomizer );
            user_patch::setLanternColor( randomizer );
        }
    }

    void onRELLink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        if ( randomizer )
        {
            randomizer->overrideREL();
        }

        // Static REL overrides and patches
        uint32_t relPtrRaw = reinterpret_cast<uint32_t>( dmc->moduleInfo );

        switch ( dmc->moduleInfo->id )
        {
            // d_a_e_hp.rel
            // Generic Poe
            case 0x00C8:
                libtp::patch::writeBranchLR( reinterpret_cast<void*>( relPtrRaw + e_hp_ExecDead_liOffset ),
                                             reinterpret_cast<void*>( assembly::asmAdjustPoeItem ) );

                // Disable Poe increment (handled through item_get_func; see game_patches)
                *reinterpret_cast<uint32_t*>( relPtrRaw + e_hp_ExecDead_incOffset ) = 0x60000000;

                break;
            // d_a_e_po.rel
            // Arbiter's Poe
            case 0x00DD:
                libtp::patch::writeBranchLR( reinterpret_cast<void*>( relPtrRaw + e_po_ExecDead_liOffset ),
                                             reinterpret_cast<void*>( assembly::asmAdjustAGPoeItem ) );

                // Disable Poe increment (handled through item_get_func; see game_patches)
                *reinterpret_cast<uint32_t*>( relPtrRaw + e_po_ExecDead_incOffset ) = 0x60000000;
                break;
            // d_a_obj_kshutter.rel
            // Lakebed Temple Boss Door
            case 0x1FA:
                // Nop out the instruction that stores the new total small key value when the game attempts to
                // remove a small key from the inventory when opening the boss door
                if ( libtp::tp::d_a_alink::checkStageName(
                         libtp::data::stage::allStages[libtp::data::stage::stageIDs::Lakebed_Temple] ) &&
                     libtp::tp::d_kankyo::env_light.currentRoom == 3 )
                {
                    *reinterpret_cast<uint32_t*>( relPtrRaw + 0x1198 ) = 0x60000000;     // Previous: 0x3803ffff
                }
                break;
            // d_a_npc_kn.rel
            // Hero's Shade
            case 0x147:
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x34D0 ),
                                             reinterpret_cast<void*>( assembly::asmAdjustHiddenSkillItem ) );
                // Give a an item based on which Golden Wolf you learned a skill from.
                break;
            // d_a_npc_ins.rel
            // Agitha
            case 0x141:
            {
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x21B8 ),
                                             reinterpret_cast<void*>( assembly::asmAdjustBugReward ) );
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
                // replace sky character
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0xB7C ) = 0x48000020;     // b 0x20
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0xB9C ),
                                             reinterpret_cast<void*>( assembly::asmAdjustSkyCharacter ) );

                break;
            }
            // d_a_obj_life_container.rel
            // Heart Pieces/Containers
            case 0x35:
            {
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x1804 ),
                                             reinterpret_cast<void*>( assembly::asmAdjustFieldItemParams ) );
                break;
            }
            // d_a_obj_bosswarp.rel
            // Post-Boss Cutscene
            case 0x5B:
            {
                libtp::patch::writeBranchBL( reinterpret_cast<void*>( relPtrRaw + 0x1884 ),
                                             reinterpret_cast<void*>( libtp::tp::d_item::execItemGet ) );
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0x1888 ) = 0x480000A8;     // b 0xA8
                // Replace dungeon reward that is given after beating a boss and show the appropriate text.
                break;
            }
            // d_a_npc_bouS.rel
            // Inside Bo's House
            case 0x121:
            {
                // Prevent Bo from talking after the chest has been opened
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0x1A44 ) = 0x48000028;     // b 0x28
                break;
            }
            // d_a_npc_ykm.rel
            // Yeto
            case 0x17F:
            {
                // Prevent Yeto from leaving the dungeon if the player has the boss key
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0x1524 ) = 0x38600000;     // li r3,0
                break;
            }
            // d_a_npc_ykw.rel
            // Yeta
            case 0x180:
            {
                // Prevent Yeta from leaving the dungeon if the player has the boss key
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0x1038 ) = 0x38600000;     // li r3,0
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
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0xB50 ) = 0x60000000;
                break;
            }
            // d_a_npc_rafrel.rel
            // Auru
            case 0x15F:
            {
                // Allow Auru to spawn, even if you have raised the Mirror.
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0x6C4 ) =
                    0x38600131;     // set auru to check for whether he gave the player the item to spawn.
                break;
            }
            // d_a_obj_smallkey.rel
            // Freestanding Small Keys
            case 0x26D:
            {
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0xC88 ) =
                    0x48000058;     // patch instruction to prevent game from removing bulblin camp key.
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
        }
    }

    void onRELUnlink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        switch ( dmc->moduleInfo->id )
        {
            // d_a_obj_Lv5Key.rel
            // Snowpeak Ruins Small Key Lock
            case 0x189:
            {
                return_daObjLv5Key_c__Wait = libtp::patch::unhookFunction( return_daObjLv5Key_c__Wait );
                break;
            }
        }
    }

    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        if ( randomizer )
        {
            randomizer->overrideDZX( chunkTypeInfo );
        }
        loadCustomActors();
    }

    int32_t onPoe( rando::Randomizer* randomizer, uint8_t flag )
    {
        if ( randomizer )
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
        if ( randomizer )
        {
            return randomizer->getSkyCharacter();
        }
        else
        {
            // Default item
            return static_cast<int32_t>( libtp::data::items::Ancient_Sky_Book_Partly_Filled );
        }
    }

    void onARC( rando::Randomizer* randomizer, void* data, int roomNo, rando::FileDirectory fileDirectory )
    {
        if ( randomizer )
        {
            randomizer->overrideARC( reinterpret_cast<uint32_t>( data ), fileDirectory, roomNo );
        }
    }

    void onBugReward( rando::Randomizer* randomizer, uint32_t msgEventAddress, uint8_t bugID )
    {
        if ( randomizer )
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
        if ( randomizer )
        {
            libtp::tp::d_item::execItemGet( randomizer->getHiddenSkillItem( eventIndex ) );
        }
    }

    void setSaveFileEventFlag( uint16_t flag )
    {
        libtp::tp::d_save::onEventBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.event_flags, flag );
    }

    void onAdjustFieldItemParams( void* fopAC, void* daObjLife )
    {
        using namespace libtp::data::stage;
        *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x7c ) = 2.0f;     // scale

        if ( libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Hyrule_Field] ) ||
             libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Upper_Zoras_River] ) ||
             libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Sacred_Grove] ) )
        {
            *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( fopAC ) + 0x530 ) = 0.0f;     // gravity
        }
        /*else if ( !libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Gerudo_Desert] ) )
        {
            *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x61C ) = 2.0f;     // height
        }  Causes crashing in some areas*/
    }

    void handleDungeonHeartContainer()
    {
        using namespace libtp::data::stage;
        const char* bossStages[8] = { allStages[stageIDs::Morpheel],
                                      allStages[stageIDs::Fyrus],
                                      allStages[stageIDs::Diababa],
                                      allStages[stageIDs::Armogohma],
                                      allStages[stageIDs::Argorok],
                                      allStages[stageIDs::Zant_Main_Room],
                                      allStages[stageIDs::Stallord],
                                      allStages[stageIDs::Blizzeta] };
        // Set the flag for the dungeon heart container if we are on a boss stage since this is the function that gets
        // called when the player picks up a heart container.
        uint32_t totalDungeonStages = sizeof( bossStages ) / sizeof( bossStages[0] );
        for ( uint32_t i = 0; i < totalDungeonStages; i++ )
        {
            if ( libtp::tp::d_a_alink::checkStageName( bossStages[i] ) )
            {
                libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags.memoryFlags[0x1D] |= 0x10;
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

    bool proc_query023( void* unk1, void* unk2, int32_t unk3 )
    {
        // Check to see if currently in one of the Kakariko interiors
        if ( libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Kakariko_Village_Interiors] ) &&
             libtp::tp::d_kankyo::env_light.currentRoom == 1 )
        {
            // If player has not bought Barnes' Bomb Bag, we want to allow them to be able to get the check.
            if ( ( !libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x908 ) ) )
            {
                return false;
            }
            // If the player has bought the bomb bag check, we won't allow them to get the check, regardless of if they
            // have bombs or not
            else
            {
                return true;
            }
        }

        // Call original function
        return mod::return_query023( unk1, unk2, unk3 );
    }

    bool proc_query042( void* unk1, void* unk2, int32_t unk3 )
    {
        // Check to see if currently in one of the Ordon interiors
        if ( randomizer )
        {
            if ( randomizer->m_Seed->m_Header->transformAnywhere )
            {
                return 0;
            }
        }
        return mod::return_query042( unk1, unk2, unk3 );
    }

    bool proc_isDungeonItem( libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int memBit )
    {
        using namespace libtp::data::stage;

        switch ( memBit )
        {
            case 3:
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

            case 7:
            {
                if ( libtp::tp::d_a_alink::checkStageName( allStages[stageIDs::Forest_Temple] ) )
                {
                    if ( ( ( libtp::tp::d_kankyo::env_light.currentRoom == 3 ) ||
                           ( libtp::tp::d_kankyo::env_light.currentRoom == 1 ) ) &&
                         ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mEvtManager.mRoomNo != 0 ) )
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
            libtp::tp::dzx::ACTR EponaActr = { "Horse", 0x00000F0D, 0.f, 0.f, 0.f, 0, -180, 0, 0xFFFF };
            tools::SpawnActor( 0, EponaActr );
        }
    }

    void loadCustomRoomActors()
    {
        using namespace libtp;
        if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Lake_Hylia] ) &&
             libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x3b08 ) )
        {
            libtp::tp::dzx::ACTR AuruActr =
                { "Rafrel", 0x00001D01, -116486.945f, -13860.f, 58533.0078f, 0, static_cast<int16_t>( 0xCCCD ), 0, 0xFFFF };
            tools::SpawnActor( 0, AuruActr );
        }
    }

    void loadCustomRoomSCOBs()
    {
        using namespace libtp;
        if ( tp::d_a_alink::checkStageName( data::stage::allStages[data::stage::stageIDs::Hyrule_Field] ) &&
             libtp::tp::d_a_alink::dComIfGs_isEventBit( 0x1E08 ) )
        {
            libtp::tp::dzx::SCOB HJumpActr = { "Hjump",
                                               0x044FFF02,
                                               5600.f,
                                               -5680.f,
                                               52055.f,
                                               0,
                                               static_cast<int16_t>( 0x4000 ),
                                               0,
                                               0xFFFF,
                                               0x20,
                                               0x2D,
                                               0x2D,
                                               0xFF };
            tools::SpawnSCOB( 3, HJumpActr );
        }
    }

    bool haveItem( uint8_t item ) { return libtp::tp::d_item::checkItemGet( item, 1 ); }

    void handleQuickTransform()
    {
        uint32_t zButtonAlphaPtr = reinterpret_cast<uint32_t>( libtp::tp::d_meter2_info::wZButtonPtr );
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

        // Ensure there is a proper pointer to the Z Button Alpha.
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

        // Check to see if Link has the ability to transform.
        if ( !libtp::tp::d_a_alink::dComIfGs_isEventBit( 0xD04 ) )
        {
            return;
        }

        if ( linkMapPtr->mEquipItem == libtp::data::items::Ball_and_Chain )
        {
            return;
        }

        if ( libtp::tp::d_camera::checkRide( linkMapPtr ) )
        {
            return;
        }

        uint32_t m_midnaActorPtr =
            *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( libtp::tp::d_a_player::m_midnaActor ) + 0x890 );

        if ( randomizer )
        {
            if ( randomizer->m_Seed->m_Header->transformAnywhere )
            {
                libtp::tp::d_a_alink::procCoMetamorphoseInit( linkMapPtr );
            }
        }

        if ( ( m_midnaActorPtr & 0x100000 ) != 0 )
        {
            return;
        }

        if ( ( m_midnaActorPtr & 0x40000 ) != 0 )
        {
            return;
        }

        if ( ( libtp::tp::d_kankyo::env_light.mEvilPacketEnabled & 0x80 ) != 0 )
        {
            return;
        }

        libtp::tp::d_a_alink::procCoMetamorphoseInit( linkMapPtr );
    }
}     // namespace mod::events