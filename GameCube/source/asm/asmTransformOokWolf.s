.global asmTransformOokWolf

asmTransformOokWolf:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)
stw %r3,0x18(%sp)
stw %r4,0x1C(%sp)

bl handleTransformOokWolf

li %r5, 5
# Pop stack
lwz %r4,0x1C(%sp)
lwz %r3,0x18(%sp)
lwz %r0,0x14(%sp)
mtlr %r0
addi %sp,%sp,0x10
blr