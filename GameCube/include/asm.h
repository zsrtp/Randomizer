/**	@file asm.h
 *  @brief ASM functions
 *
 *  @author AECX
 *  @author Zephiles
 *  @author Lunar Soap
 *  @author Isaac
 *  @bug No known bugs.
 */
#ifndef RANDO_ASM_H
#define RANDO_ASM_H

#include <cstddef>
#include <cstdint>
#include <cstdarg>
#include "tp/dynamic_link.h"
#include "tp/f_op_actor.h"
#include "tp/d_a_alink.h"

// Original: li 0xE0
// Normally loads the poesoul item id into r4
#define e_hp_ExecDead_liOffset 0x247C
#define e_po_ExecDead_liOffset 0x3C9C

// Original:
// stb r0, 0x10c( r4 ) = > numPoeSouls
// Normally increments poe count
#define e_hp_ExecDead_incOffset 0x2354
#define e_po_ExecDead_incOffset 0x36A8

// d_a_obj_Lv5Key__Wait_offset:
// 0xBC is offset to the text section relative to the start of the decompressed
// REL. 0x4E4 is offset to Wait function relative to the start of the text
// section (as seen on line 14 of d_a_obj_Lv5Key.map).
#define d_a_obj_Lv5Key__Wait_offset 0xBC + 0x4E4

namespace mod::assembly
{
    extern "C"
    {
        int32_t asm_handle_snprintf(char* buffer, std::size_t bufferSize, const char* format, ...);
        int32_t asm_handle_vsnprintf(char* buffer, std::size_t bufferSize, const char* format, va_list args);

        void asmDoLinkHookStart(void);
        void asmDoLinkHookEnd(void);
        void handleDoLinkHook(libtp::tp::dynamic_link::DynamicModuleControl* dmc);

        // d_e_hp.rel
        void asmAdjustPoeItemStart(void);
        void asmAdjustPoeItemEnd(void);
        int32_t handleAdjustPoeItem(void*);

        // d_e_po.rel
        void asmAdjustAGPoeItemStart(void);
        void asmAdjustAGPoeItemEnd(void);
        int32_t handleAdjustAGPoeItem(void*);

        // d_a_npc_ins.rel
        void asmAdjustBugRewardStart();
        void asmAdjustBugRewardEnd();
        void handleAdjustBugReward(uint32_t msgEventAddress, uint8_t bugID);

        void asmAdjustSkyCharacterStart();
        void asmAdjustSkyCharacterEnd();
        uint8_t handleAdjustSkyCharacter();

        // d_a_obj_life_container.rel
        void asmAdjustFieldItemParams();
        void handleAdjustFieldItemParams(libtp::tp::f_op_actor::fopAc_ac_c* fopAC, void* daObjLife);

        // d_a_e_mk.rel
        void asmTransformOokWolf();
        void handleTransformFromWolf();

        // d_a_b_bq.rel
        void asmTransformDiababaWolfStart();
        void asmTransformDiababaWolfEnd();

        // d_a_npc_hoz.rel
        void asmAdjustIzaWolf();
        void handleAdjustIzaWolf(int32_t flag);

        // d_kankyo_rain.o
        void asmShowReekfishPath();
        uint8_t handleShowReekfishPath(uint8_t scent);

        // d_a_demo_item.o
        void asmAdjustCreateItemParamsStart();
        void asmAdjustCreateItemParamsEnd();
        void handleAdjustCreateItemParams(void* daDitem);

        // d_a_npc_pouya.o
        void asmCheck60PoeReward();
        bool handleCheck60PoeReward(uint8_t poeCount);

        // d_a_npc_GWolf.o
        void asmReplaceGWolfWithItem(void);
        bool handleReplaceGWolfWithItem(const int16_t* l_delFlag, void* daNpcGWolf);

        // vi.o
        void asmCallCodehandler();

        // d_a_alink.o
#ifdef TP_JP
        void asmUnpatchMapGlitchStart();
        void asmUnpatchMapGlitchEnd();
        void unpatchMapGlitch(libtp::tp::d_a_alink::daAlink* d_a_alink);
#endif
    }
} // namespace mod::assembly

#endif