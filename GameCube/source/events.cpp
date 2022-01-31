#include "events.h"

#include <cinttypes>
#include <cstring>

#include "asm.h"
#include "data/items.h"
#include "main.h"
#include "patch.h"
#include "rando/randomizer.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_item.h"
#include "tp/dzx.h"
#include "user_patch/03_customCosmetics.h"

namespace mod::events
{
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
                 !strcmp( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mStartStage.mStage, "F_SP103" ) )
            {
                randomizer->initSave();
            }
        }
        randomizer->overrideREL();

        user_patch::setHUDCosmetics();
    }

    void onRELLink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        // Old Code
        /*if ( randomizer )
        {
            randomizer->overrideREL( dmc );
        }*/

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
                *reinterpret_cast<uint32_t*>( relPtrRaw + 0x1198 ) = 0x60000000;     // Previous: 0x3803ffff
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
        }
    }

    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        if ( randomizer )
        {
            randomizer->overrideDZX( chunkTypeInfo );
        }
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

    void onARC( rando::Randomizer* randomizer, void* filePtr, int32_t fileIndex )
    {
        if ( randomizer )
        {
            randomizer->overrideARC( filePtr, fileIndex );
        }
    }

    void onBugReward( rando::Randomizer* randomizer, uint32_t msgEventAddress, uint8_t bugID )
    {
        if ( randomizer )
        {
            uint8_t itemID = randomizer->overrideBugReward( bugID );
            *reinterpret_cast<uint16_t*>( ( *reinterpret_cast<uint32_t*>( msgEventAddress + 0xA04 ) + 0x3580 ) + 0x6 ) =
                itemID;     // Change Big Wallet Item
            *reinterpret_cast<uint16_t*>( ( *reinterpret_cast<uint32_t*>( msgEventAddress + 0xA04 ) + 0x35c8 ) + 0x6 ) =
                itemID;     // Change Purple Rupee Item
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
        libtp::tp::d_save::onEventBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.events, flag );
    }
}     // namespace mod::events