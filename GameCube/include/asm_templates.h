#ifndef RANDO_ASM_TEMPLATES_H
#define RANDO_ASM_TEMPLATES_H

#include <cstdint>

#define ASM_NOP (0x60000000)
#define ASM_LOAD_IMMEDIATE(register, value) ((0x38000000 + (register * 0x200000)) | (value & 0xFFFF))
#define ASM_COMPARE_WORD_IMMEDIATE(register, value) ((0x2C000000 + (register * 0x10000)) | (value & 0xFFFF))
#define ASM_COMPARE_LOGICAL_WORD_IMMEDIATE(register, value) ((0x28000000 + (register * 0x10000)) | (value & 0xFFFF))
#define ASM_BRANCH(length) (0x48000000 + (static_cast<uint32_t>(length) & 0x3FFFFFC))

#define ASM_BRANCH_CONDITIONAL(branchOption, conditionBit, value) \
    (0x40000000 + (branchOption * 0x200000) + (conditionBit * 0x10000) + (value & 0xFFFF))

inline uint32_t ASM_BRANCH_EQUAL_PLUS(int32_t value)
{
    int16_t tempValue = value & 0xFFFF;
    if (tempValue >= 0)
    {
        return ASM_BRANCH_CONDITIONAL(13, 2, tempValue);
    }
    else
    {
        return ASM_BRANCH_CONDITIONAL(12, 2, tempValue);
    }
}

inline uint32_t ASM_BRANCH_EQUAL_MINUS(int32_t value)
{
    int16_t tempValue = value & 0xFFFF;
    if (tempValue >= 0)
    {
        return ASM_BRANCH_CONDITIONAL(12, 2, tempValue);
    }
    else
    {
        return ASM_BRANCH_CONDITIONAL(13, 2, tempValue);
    }
}

#endif