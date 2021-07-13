/**	@file asm.h
 *  @brief ASM functions
 *
 *	@author AECX
 *  @author Zephiles
 *	@bug No known bugs.
 */
#ifndef RANDO_ASM_H
#define RANDO_ASM_H

#include <cstdint>

// Original: li 0xE0
// Normally loads the poesoul item id into r4
#define e_hp_ExecDead_liOffset 0x247C
#define e_po_ExecDead_liOffset 0x3C9C

namespace mod::assembly
{
    extern "C"
    {
        // d_e_hp.rel
        void asmAdjustPoeItem( void );
        int32_t handleAdjustPoeItem( void* );

        // d_e_po.rel
        void asmAdjustAGPoeItem( void );
        int32_t handleAdjustAGPoeItem( void* );
    }
}     // namespace mod::assembly

#endif