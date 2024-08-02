.global asmGiveMasterSwordItemsStart
.global asmGiveMasterSwordItemsEnd

.hidden asmGiveMasterSwordItemsStart
.hidden asmGiveMasterSwordItemsEnd

asmGiveMasterSwordItemsStart:
bl handleGiveMasterSwordItems

# Clear the current actor status for the Master Sword actor since we set the flag to delete it in the handle function.
# Specifically clear the lower 16 bits of fopAc_ac_c::mStatus
li %r3,0
sth %r3,0x49E(%r26) # fopAc_ac_c::mStatus

# Restore the original instruction
li %r3,47

asmGiveMasterSwordItemsEnd:
b 0