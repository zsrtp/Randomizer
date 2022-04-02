/**	@file asm.h
 *  @brief ASM functions
 *
 *	@author AECX
 *  @author Zephiles
 *  @author Lunar Soap
 *	@bug No known bugs.
 */
#ifndef RANDO_ASM_H
#define RANDO_ASM_H

#include <cstdint>

// Original: li 0xE0
// Normally loads the poesoul item id into r4
#define e_hp_ExecDead_liOffset 0x247C
#define e_po_ExecDead_liOffset 0x3C9C

// Original:
// stb r0, 0x10c( r4 ) = > numPoeSouls
// Normally increments poe count
#define e_hp_ExecDead_incOffset 0x2354
#define e_po_ExecDead_incOffset 0x36A8

// abc
#define fish 0xBC + 0x4E4

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

        // d_a_npc_kn.rel
        void asmAdjustHiddenSkillItem();
        void handleAdjustHiddenSkillItem( uint16_t eventIndex );

        // d_a_npc_ins.rel
        void asmAdjustBugReward();
        void handleAdjustBugReward( uint32_t msgEventAddress, uint8_t bugID );

        void asmAdjustSkyCharacter();
        uint8_t handleAdjustSkyCharacter();

        // d_a_obj_life_container.rel
        void asmAdjustFieldItemParams();
        void handleAdjustFieldItemParams( void* fopAc_ac_c, void* daObjLife_c );

        // d_a_e_mk.rel
        void asmTransformOokWolf();
        void handleTransformOokWolf();
    }
}     // namespace mod::assembly

#endif