.global asmTransformOokWolf
.hidden asmTransformOokWolf

asmTransformOokWolf:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x24(%sp)
stw %r3,0x8(%sp)
stw %r4,0xC(%sp)

bl handleTransformFromWolf

li %r5, 5
# Pop stack
lwz %r4,0xC(%sp)
lwz %r3,0x8(%sp)
lwz %r0,0x24(%sp)
mtlr %r0
addi %sp,%sp,0x10
blr