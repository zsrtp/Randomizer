.global asmGiveMasterSwordItems
.hidden asmGiveMasterSwordItems

asmGiveMasterSwordItems:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

# Backup important register values
stw %r4,0x8(%sp)
stw %r26,0xC(%sp)

bl handleGiveMasterSwordItems

# Restore important register values
lwz %r26,0xC(%sp)
lwz %r4,0x8(%sp)

# Clear the current actor status for the Master Sword actor since we set the flag to delete it in the handle function.
li %r3, 0x0
sth %r3, 0x49E(%r26)

# Pop stack
lwz %r0,0x14(%sp)
mtlr %r0
addi %sp,%sp,0x10

# Restore the original instruction
li %r3,47
blr