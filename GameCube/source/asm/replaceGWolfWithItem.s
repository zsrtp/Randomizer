.global asmReplaceGWolfWithItemStart
.global asmReplaceGWolfWithItemEnd

.hidden asmReplaceGWolfWithItemStart
.hidden asmReplaceGWolfWithItemEnd

asmReplaceGWolfWithItemStart:
# r3 already contains the flag
mr %r4,%r31 # daNpcGWolf
bl handleReplaceGWolfWithItem

asmReplaceGWolfWithItemEnd:
b 0