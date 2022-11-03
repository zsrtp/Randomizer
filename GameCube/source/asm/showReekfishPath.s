.global asmShowReekfishPath
# asmShowReekfishPath needs to be used in at least one subrel, so it cannot be set to hidden

asmShowReekfishPath:
# Push stack
stwu %sp,-0x10(%sp)
mflr %r0
stw %r0,0x14(%sp)

# Backup important register values
stw %r3,0x8(%sp)

lbz %r3,0x16(%r3) # scent
bl handleShowReekfishPath
mr %r0,%r3 # scent
mr %r4,%r3 # scent

# Restore important register values
lwz %r3,0x8(%sp)

# Pop stack
lwz %r5,0x14(%sp)
mtlr %r5
addi %sp,%sp,0x10
blr