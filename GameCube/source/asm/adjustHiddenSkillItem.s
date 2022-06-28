.global asmAdjustHiddenSkillItem
.hidden asmAdjustHiddenSkillItem

asmAdjustHiddenSkillItem:
stwu %sp,-0x20(%sp)
stmw %r26, 0x8(%sp)
mr %r26, %r0
mflr %r0
stw %r0,0x24(%sp)
mr %r27, %r3
mr %r28, %r4
mr %r29, %r5
mr %r31, %r6

addi %r3, %r30, 490
rlwinm %r3, %r3, 1, 0, 30
lis %r4, 0x803A
addi %r4, %r4, 29320
lhzx %r4, %r4, %r3
mr %r3, %r4
bl handleAdjustHiddenSkillItem

mr %r3, %r27
mr %r4, %r28
mr %r5, %r29
mr %r6, %r31
lwz %r0,0x24(%sp)
mtlr %r0
mr %r0, %r26
lmw %r26, 0x8(%sp)
addi %r3, %r30, 490
addi %sp,%sp,0x20
blr