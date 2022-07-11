.global asmAdjustCreateItemParams
.hidden asmAdjustCreateItemParams

asmAdjustCreateItemParams:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

mr %r3, %r30
bl handleAdjustCreateItemParams

# Pop stack
lwz %r0,0x14(%sp)
mtlr %r0
li %r3, 1
addi %sp,%sp,0x10
blr