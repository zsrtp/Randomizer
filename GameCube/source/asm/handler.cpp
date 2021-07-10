/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "main.h"

namespace mod::assembly
{
    int32_t handleAdjustPoeItem( void )
    {
        if ( mod::randomizer )
        {
            // TODO: implementation
        }
        // Default
        return 0xE0;
    }
}