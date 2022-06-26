.global asmAdjustIzaWolf
.hidden asmAdjustIzaWolf

asmAdjustIzaWolf:
# Restore the original instruction immediately
extsb %r5,%r0

# Push stack
stwu %sp,-0x20(%sp)
mflr %r0
stw %r0,0x24(%sp)
stw %r3,0x10(%sp)
stw %r4,0xC(%sp)
stw %r5,0x8(%sp)

bl handleAdjustIzaWolf

# Pop stack
lwz %r5,0x8(%sp)
lwz %r4,0xC(%sp)
lwz %r3,0x10(%sp)
lwz %r0,0x24(%sp)
mtlr %r0
addi %sp,%sp,0x20
blr