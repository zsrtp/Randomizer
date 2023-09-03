.global asmCallCodehandler
# asmCallCodehandler needs to be used in at least one subrel, so it cannot be set to hidden

asmCallCodehandler:
# Restore the original instruction immediately, as the codehandler backs it up and restores it
addi %r7,%r31,320

b codehandlerStartAddress