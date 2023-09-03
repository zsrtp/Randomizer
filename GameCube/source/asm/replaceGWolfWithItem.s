.global asmReplaceGWolfWithItem
.hidden asmReplaceGWolfWithItem

asmReplaceGWolfWithItem:
# r3 already contains l_delFlag
mr %r4,%r31 # daNpcGWolf
b handleReplaceGWolfWithItem