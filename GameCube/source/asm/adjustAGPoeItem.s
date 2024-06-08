.global asmAdjustAGPoeItemStart
.global asmAdjustAGPoeItemEnd

.hidden asmAdjustAGPoeItemStart
.hidden asmAdjustAGPoeItemEnd

asmAdjustAGPoeItemStart:
#ifdef PLATFORM_WII
mr %r3,%r28 # e_po_class
#else
mr %r3,%r31 # e_po_class
#endif

bl handleAdjustAGPoeItem
mr %r4,%r3 # The item to give

# Restore important register values
#ifdef PLATFORM_WII
addi %r3,%r28,0x4D0
#else
addi %r3,%r31,0x4D0
#endif

asmAdjustAGPoeItemEnd:
b 0