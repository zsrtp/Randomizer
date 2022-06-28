/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "events.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"
#include "data/items.h"

namespace mod::assembly
{
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

    void handleAdjustHiddenSkillItem( uint16_t eventIndex )
    {
        events::onHiddenSkill( mod::randomizer, eventIndex );
        return;
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

    void handleAdjustIzaWolf()
    {
        if ( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentForm == 1 )
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
                 0x6120 ) )     // If we are currently at Snowpeak and the flag for having smelled a Reekfish is set
        {
            return libtp::data::items::Item::Reekfish_Scent;
        }
        else
        {
            return scent;
        }
    }
}     // namespace mod::assembly