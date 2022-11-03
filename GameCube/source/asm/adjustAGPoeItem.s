.global asmAdjustAGPoeItemStart
.global asmAdjustAGPoeItemEnd

.hidden asmAdjustAGPoeItemStart
.hidden asmAdjustAGPoeItemEnd

asmAdjustAGPoeItemStart:
mr %r3,%r31
bl handleAdjustAGPoeItem
mr %r4,%r3

# Restore important register values
addi %r3,%r31,0x4D0

asmAdjustAGPoeItemEnd:
b 0