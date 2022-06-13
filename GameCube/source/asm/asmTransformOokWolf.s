.global asmTransformOokWolf

asmTransformOokWolf:
# Push stack
stwu %sp,-0x20(%sp)
mflr %r0
stw %r0,0x24(%sp)
stw %r3,0xC(%sp)
stw %r4,0x10(%sp)

bl handleTransformFromWolf

li %r5, 5
# Pop stack
lwz %r4,0x10(%sp)
lwz %r3,0xC(%sp)
lwz %r0,0x24(%sp)
mtlr %r0
addi %sp,%sp,0x20
blr