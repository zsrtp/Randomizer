/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "events.h"
#include "main.h"

namespace mod::assembly
{
    int32_t handleAdjustPoeItem( void* e_hp_class )
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( e_hp_class ) + 0x77B );
        return events::onPoe( flag );
    }

    int32_t handleAdjustAGPoeItem( void* e_po_class )
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( e_po_class ) + 0x5BD );
        return events::onPoe( flag );
    }
}     // namespace mod::assembly