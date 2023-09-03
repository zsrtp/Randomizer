.global asmAdjustFieldItemParams
.hidden asmAdjustFieldItemParams

asmAdjustFieldItemParams:
# Push stack
stwu %sp,-0x20(%sp)
mflr %r0
stw %r0,0x24(%sp)

# Backup important register values
stw %r3,0x8(%sp)
stw %r4,0xC(%sp)
stw %r6,0x10(%sp)

mr %r3,%r30 # fopAC
mr %r4,%r31 # daObjLife
bl handleAdjustFieldItemParams

# Restore important register values
lwz %r3,0x8(%sp)
lwz %r4,0xC(%sp)
lwz %r6,0x10(%sp)

# Pop stack
lwz %r0,0x24(%sp)
mtlr %r0
addi %sp,%sp,0x20

# Restore the original instruction
lbz %r0,0(%r6)
blr