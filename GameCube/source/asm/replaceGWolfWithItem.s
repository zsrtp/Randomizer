.global asmReplaceGWolfWithItem
.hidden asmReplaceGWolfWithItem

asmReplaceGWolfWithItem:
# r3 already contains the flag
mr %r4,%r31 # daNpcGWolf
b handleReplaceGWolfWithItem