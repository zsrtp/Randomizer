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
# The Wii hook skips initializing both r3 and r4, so that must be done here
li %r3,47

#ifdef PLATFORM_WII
li %r4,0
#endif

asmGiveMasterSwordItemsEnd:
b 0