.global asmDoLinkHook
.hidden asmDoLinkHook

asmDoLinkHook:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

mr %r3,%r31 # dmc
bl handleDoLinkHook

# Restore the original instruction
lwz %r3,0x10(%r31)

# Pop stack
lwz %r0,0x14(%sp)
mtlr %r0
addi %sp,%sp,0x10
blr