.global asmAdjustPoeItemStart
.global asmAdjustPoeItemEnd

.hidden asmAdjustPoeItemStart
.hidden asmAdjustPoeItemEnd

asmAdjustPoeItemStart:
mr %r3,%r31 # e_hp_class
bl handleAdjustPoeItem
mr %r4,%r3 #The item to give

# Restore important register values
addi %r3,%r31,0x4D0

asmAdjustPoeItemEnd:
b 0