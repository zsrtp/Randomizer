.global asmAdjustBugReward
.hidden asmAdjustBugReward

asmAdjustBugReward:
stwu %sp,-0x10(%sp)
stw %r20,0x8(%sp)
mr %r20, %r0
mflr %r0
stw %r0,0x14(%sp)

mr %r4, %r29
bl handleAdjustBugReward

lwz %r0,0x14(%sp)
mtlr %r0
lwz %r20,0x8(%sp)
mr %r0, %r20
mr %r4, %r29
addi %sp,%sp,0x10
blr