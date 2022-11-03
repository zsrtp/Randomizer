.global asmAdjustHiddenSkillItemStart
.global asmAdjustHiddenSkillItemEnd

.hidden asmAdjustHiddenSkillItemStart
.hidden asmAdjustHiddenSkillItemEnd

asmAdjustHiddenSkillItemStart:
addi %r3,%r30,490
rlwinm %r3,%r3,1,0,30 # eventIndex
bl handleAdjustHiddenSkillItem

# Restore the original instruction
addi %r3,%r30,490

asmAdjustHiddenSkillItemEnd:
b 0