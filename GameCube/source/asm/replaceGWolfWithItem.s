.global asmReplaceGWolfWithItem
.hidden asmReplaceGWolfWithItem

asmReplaceGWolfWithItem:
# r3 already contains l_delFlag
lbz %r4,0xE11(%r31) # flagIndex
mr %r5,%r31 # daNpcGWolf
b handleReplaceGWolfWithItem