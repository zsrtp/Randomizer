/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "tp/dynamic_link.h"
#include "events.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"
#include "data/items.h"
#include "data/flags.h"
#include "tp/d_a_npc.h"

namespace mod::assembly
{
    void handleDoLinkHook( libtp::tp::dynamic_link::DynamicModuleControl* dmc )
    {
        if ( dmc->moduleInfo )
        {
            events::onRELLink( mod::randomizer, dmc );
        }
    }

    int32_t handleAdjustPoeItem( void* e_hp_class )
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( e_hp_class ) + 0x77B );
        return events::onPoe( mod::randomizer, flag );
    }

    int32_t handleAdjustAGPoeItem( void* e_po_class )
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( e_po_class ) + 0x5BD );
        return events::onPoe( mod::randomizer, flag );
    }

    void handleAdjustBugReward( uint32_t msgEventAddress, uint8_t bugID )
    {
        events::onBugReward( mod::randomizer, msgEventAddress, bugID );
    }

    uint8_t handleAdjustSkyCharacter()
    {
        return events::onSkyCharacter( mod::randomizer );
    }

    void handleAdjustFieldItemParams( libtp::tp::f_op_actor::fopAc_ac_c* fopAC, void* daObjLife )
    {
        events::onAdjustFieldItemParams( fopAC, daObjLife );
    }

    void handleTransformFromWolf()
    {
        if ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentForm == 1 )
        {
            libtp::tp::d_a_alink::procCoMetamorphoseInit( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mPlayer );
        }
    }

    void handleAdjustIzaWolf( int32_t flag )
    {
        // We check to see if the flag being set is for the Upper Zora's River Portal as a safety precaution since we don't want
        // to set the flags too early.
        if ( ( flag == 0x15 ) &&
             ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentForm == 1 ) )
        {
            // Set the event flag to make Iza 1 available and set the memory bit for having talked to her after opening the
            // portal as human.
            events::setSaveFileEventFlag( 0xB02 );
            libtp::tp::d_save::onSwitch_dSv_memBit( &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x37 );
        }
    }

    uint8_t handleShowReekfishPath( uint8_t scent )
    {
        if ( ( libtp::tp::d_a_alink::checkStageName(
                 libtp::data::stage::allStages[libtp::data::stage::stageIDs::Snowpeak] ) ) &&
             libtp::tp::d_a_alink::dComIfGs_isEventBit(
                 libtp::data::flags::GOT_REEKFISH_SCENT ) )     // If we are currently at Snowpeak and the flag for having
                                                                // smelled a Reekfish is set
        {
            return libtp::data::items::Item::Reekfish_Scent;
        }
        else
        {
            return scent;
        }
    }

    void handleAdjustCreateItemParams( void* daDitem )
    {
        events::onAdjustCreateItemParams( daDitem );
    }

    bool handleCheck60PoeReward( uint8_t poeCount )
    {
        // Check if we are getting the 60 Poe Check and that we have already gotten the 20 Poe Check.
        return ( ( poeCount >= 60 ) &&
                 libtp::tp::d_a_alink::dComIfGs_isEventBit( libtp::data::flags::GOT_BOTTLE_FROM_JOVANI ) );
    }

    bool handleReplaceGWolfWithItem( const int16_t* l_delFlag, uint32_t flagIndex, void* daNpcGWolf )
    {
        int16_t delFlag = l_delFlag[flagIndex];
        const bool flagIsSet = libtp::tp::d_a_npc::daNpcT_chkEvtBit( delFlag );

        if ( !flagIsSet )
        {
            // Check if the player has howled at the statue for the current golden wolf
            // l_warpAppearFlag is 0xEC before l_delFlag
            const int16_t* l_warpAppearFlag =
                reinterpret_cast<const int16_t*>( reinterpret_cast<uint32_t>( l_delFlag ) - 0xEC );

            // If the appear flag is -1, then the wolf should be spawned without howling. This is used for the Faron wolf.
            int16_t appearFlag = l_warpAppearFlag[flagIndex];
            if ( ( appearFlag == -1 ) || libtp::tp::d_a_npc::daNpcT_chkEvtBit( appearFlag ) )
            {
                events::onHiddenSkill( mod::randomizer, daNpcGWolf, delFlag );
            }
        }
        return flagIsSet;
    }

#ifdef TP_JP
    void unpatchMapGlitch( libtp::tp::d_a_alink::daAlink* d_a_alink )
    {
        d_a_alink->mNoResetFlg0 |= 0x4000;
    }
#endif
}     // namespace mod::assembly