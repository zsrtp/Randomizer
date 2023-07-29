.global asmTransformDiababaWolfStart
.global asmTransformDiababaWolfEnd

.hidden asmTransformDiababaWolfStart
.hidden asmTransformDiababaWolfEnd

asmTransformDiababaWolfStart:
bl handleTransformFromWolf

# Restore the original instruction
li %r0,1

asmTransformDiababaWolfEnd:
b 0