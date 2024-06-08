.global asmCheck60PoeReward
.hidden asmCheck60PoeReward

asmCheck60PoeReward:
# Move r0 to r3 since it contains the value we need
mr %r3,%r0

# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

# Backup important register values
stw %r3,0xC(%sp)

bl handleCheck60PoeReward
cmplwi %r3,1

# Restore important register values
lwz %r0,0xC(%sp)

# Pop stack
lwz %r3,0x14(%sp)
mtlr %r3
lwz %r3,0xC(%sp)
addi %sp,%sp,0x10
blr