.global asmAdjustAGPoeItem
.hidden asmAdjustAGPoeItem

asmAdjustAGPoeItem:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

mr %r3,%r31
bl handleAdjustAGPoeItem
mr %r4,%r3

# Restore value to r3
addi %r3,%r31,0x4D0

# Pop stack
lwz %r0,0x14(%sp)
mtlr %r0
addi %sp,%sp,0x10
blr