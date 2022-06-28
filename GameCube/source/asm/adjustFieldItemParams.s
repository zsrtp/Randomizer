.global asmAdjustFieldItemParams
.hidden asmAdjustFieldItemParams

asmAdjustFieldItemParams:
stwu %sp,-0x20(%sp)
stmw %r26,0xC(%sp)
mr %r29, %r0
mflr %r0
stw %r0,0x24(%sp)

mr %r26, %r3
mr %r27, %r4
mr %r28, %r6

mr %r3, %r30
mr %r4,%r31 #The pointer to the struct
bl handleAdjustFieldItemParams

mr %r3, %r26
mr %r4, %r27
mr %r6, %r28

lwz %r0,0x24(%sp)
mtlr %r0
mr %r0, %r29
lbz %r0,0(%r6)
lmw %r26,0xC(%sp)
addi %sp,%sp,0x20
blr