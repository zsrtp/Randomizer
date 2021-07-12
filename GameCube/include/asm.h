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

namespace mod::assembly
{
    extern "C"
    {
        void asmAdjustPoeItem( void );
        int32_t handleAdjustPoeItem( void );
    }
}     // namespace mod::assembly

#endif