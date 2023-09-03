.global asmAdjustBugRewardStart
.global asmAdjustBugRewardEnd

.hidden asmAdjustBugRewardStart
.hidden asmAdjustBugRewardEnd

asmAdjustBugRewardStart:
# r3 already contains msgEventAddress
mr %r4,%r29 # bugID
bl handleAdjustBugReward

# The value previously in r3 goes unused in the function that it gets passed to, so it does not need to be restored
# Restore the original instruction
mr %r4,%r29

asmAdjustBugRewardEnd:
b 0