.global asmAdjustFieldItemParams
.hidden asmAdjustFieldItemParams

#ifdef PLATFORM_WII
REGISTER_INCREMENT = 0x10
#else
REGISTER_INCREMENT = 0x20
#endif

asmAdjustFieldItemParams:
# Push stack
stwu %sp,(-REGISTER_INCREMENT)(%sp)
mflr %r0
stw %r0,(REGISTER_INCREMENT + 0x4)(%sp)

# Backup important register values
stw %r3,0x8(%sp)

#ifndef PLATFORM_WII
stw %r4,0xC(%sp)
stw %r6,0x10(%sp)
#endif

#ifdef PLATFORM_WII
mr %r3,%r31 # fopAC
mr %r4,%r30 # daObjLife
#else
mr %r3,%r30 # fopAC
mr %r4,%r31 # daObjLife
#endif

bl handleAdjustFieldItemParams

# Restore important register values
lwz %r3,0x8(%sp)

#ifndef PLATFORM_WII
lwz %r4,0xC(%sp)
lwz %r6,0x10(%sp)
#endif

# Pop stack
lwz %r0,(REGISTER_INCREMENT + 0x4)(%sp)
mtlr %r0
addi %sp,%sp,REGISTER_INCREMENT

# Restore the original instruction
#ifdef PLATFORM_WII
addi %r4,%r31,0x4F8
#else
lbz %r0,0(%r6)
#endif

blr