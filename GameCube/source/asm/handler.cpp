/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "data/stages.h"
#include "events.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_meter2_info.h"
#include "tp/d_msg_object.h"
#include "tp/f_op_msg_mng.h"

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

    uint8_t handleAdjustSkyCharacter() { return events::onSkyCharacter( mod::randomizer ); }

    void handleAdjustFieldItemParams( void* fopAC, void* daObjLife )
    {
        *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x7c ) = 2.0f;     // scale

        if ( libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[Stage_Hyrule_Field] ) ||
             libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[Stage_Upper_Zoras_River] ) )
        {
            *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( fopAC ) + 0x530 ) = 0.0f;     // gravity
        }
        else
        {
            *reinterpret_cast<float*>( reinterpret_cast<uint32_t>( daObjLife ) + 0x61C ) = 2.0f;     // height
        }
    }
}     // namespace mod::assembly