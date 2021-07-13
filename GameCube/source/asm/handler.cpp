/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "main.h"

namespace mod::assembly
{
    int32_t handleAdjustPoeItem( void* e_hp_class )
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( e_hp_class ) + 0x77B );

        if ( mod::randomizer )
        {
            return mod::randomizer->getPoeItem( flag );
        }
        else
        {
            // Default item
            return 0xE0;
        }
    }

    int32_t handleAdjustAGPoeItem( void* e_po_class )
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>( reinterpret_cast<uint32_t>( e_po_class ) + 0x5BD );

        if ( mod::randomizer )
        {
            return mod::randomizer->getPoeItem( flag );
        }
        else
        {
            // Default item
            return 0xE0;
        }
    }
}     // namespace mod::assembly