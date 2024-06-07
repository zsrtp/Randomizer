.global asmAdjustPoeItem
.hidden asmAdjustPoeItem

asmAdjustPoeItem:
# r4 normally would need to be backed up here, but a different patch is skipping the code that would use the value in r4, so we don't need to back it up
mr %r3,%r31 # e_hp_class
b handleAdjustPoeItem