.global asmReplaceGWolfWithItemStart
.global asmReplaceGWolfWithItemEnd

.hidden asmReplaceGWolfWithItemStart
.hidden asmReplaceGWolfWithItemEnd

asmReplaceGWolfWithItemStart:
# r3 already contains the flag
mr %r4,%r31 # daNpcGWolf
bl handleReplaceGWolfWithItem
cmplwi %r3,0

asmReplaceGWolfWithItemEnd:
b 0