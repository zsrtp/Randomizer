.global asmAdjustBugRewardStart
.global asmAdjustBugRewardEnd

.hidden asmAdjustBugRewardStart
.hidden asmAdjustBugRewardEnd

asmAdjustBugRewardStart:
#ifdef PLATFORM_WII
mr %r4,%r30 # bugID
#else
mr %r4,%r29 # bugID
#endif

# r3 already contains msgEventAddress
bl handleAdjustBugReward

# The value previously in r3 goes unused in the function that it gets passed to, so it does not need to be restored
# Restore the original instruction
#ifdef PLATFORM_WII
mr %r4,%r30
#else
mr %r4,%r29
#endif

asmAdjustBugRewardEnd:
b 0