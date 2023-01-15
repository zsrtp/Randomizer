.global asmCallCodehandlerStart
.global asmCallCodehandlerEnd

# asmCallCodehandlerStart and asmCallCodehandlerEnd both need to be used in at least one subrel, so they cannot be set to hidden

asmCallCodehandlerStart:
bl codehandlerStartAddress

# Restore the original instruction
addi %r7,%r31,320

asmCallCodehandlerEnd:
b 0