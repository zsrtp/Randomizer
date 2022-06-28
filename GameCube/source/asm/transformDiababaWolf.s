.global asmTransformDiababaWolf
.hidden asmTransformDiababaWolf

asmTransformDiababaWolf:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

bl handleTransformFromWolf

#Pop stack
lwz %r0,0x14(%sp)
mtlr %r0
li %r0, 1
addi %sp,%sp,0x10
blr