.global asmAdjustCreateItemParamsStart
.global asmAdjustCreateItemParamsEnd

.hidden asmAdjustCreateItemParamsStart
.hidden asmAdjustCreateItemParamsEnd

asmAdjustCreateItemParamsStart:
mr %r3,%r30 # daDitem
bl handleAdjustCreateItemParams

# Restore the original instruction
li %r3,1

asmAdjustCreateItemParamsEnd:
b 0