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

namespace mod::assembly
{
    extern "C"
    {
        void asmAdjustPoeItem( void );
        int32_t handleAdjustPoeItem( void );
    }
}     // namespace mod::assembly

#endif