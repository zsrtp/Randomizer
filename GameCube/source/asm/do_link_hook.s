.global asmDoLinkHookStart
.global asmDoLinkHookEnd

.hidden asmDoLinkHookStart
.hidden asmDoLinkHookEnd

asmDoLinkHookStart:
mr %r3,%r31 # dmc
bl handleDoLinkHook

# Restore the original instruction
lwz %r3,0x10(%r31)

asmDoLinkHookEnd:
b 0