.global asmAdjustAGPoeItemStart
.global asmAdjustAGPoeItemEnd

.hidden asmAdjustAGPoeItemStart
.hidden asmAdjustAGPoeItemEnd

asmAdjustAGPoeItemStart:
mr %r3,%r31 #e_po_class
bl handleAdjustAGPoeItem
mr %r4,%r3 #The item to give

# Restore important register values
addi %r3,%r31,0x4D0

asmAdjustAGPoeItemEnd:
b 0