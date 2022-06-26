.global asmAdjustSkyCharacter
.hidden asmAdjustSkyCharacter

asmAdjustSkyCharacter:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)
stw %r31,0x8(%sp)
mr %r31, %r3

bl handleAdjustSkyCharacter
mr %r27,%r3

# Restore value to r3
mr %r3, %r31

# Pop stack
lwz %r31,0x8(%sp)
lwz %r0,0x14(%sp)
mtlr %r0
addi %sp,%sp,0x10
blr