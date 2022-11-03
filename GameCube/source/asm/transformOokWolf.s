.global asmTransformOokWolf
.hidden asmTransformOokWolf

asmTransformOokWolf:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

# Backup important register values
stw %r3,0x8(%sp)
stw %r4,0xC(%sp)

bl handleTransformFromWolf

# Restore important register values
lwz %r4,0xC(%sp)
lwz %r3,0x8(%sp)

# Pop stack
lwz %r0,0x14(%sp)
mtlr %r0
addi %sp,%sp,0x10

# Restore the original instruction
li %r5,5
blr