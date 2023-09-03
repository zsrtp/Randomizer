#ifdef TP_JP

.global asmUnpatchMapGlitchStart
.global asmUnpatchMapGlitchEnd
# asmUnpatchMapGlitchStart and asmUnpatchMapGlitchEnd both need to be used in at least one subrel, so they cannot be set to hidden

asmUnpatchMapGlitchStart:
mr %r3,%r30 # d_a_alink
bl unpatchMapGlitch

# Restore the original instruction
lbz %r0,0xC0(%r29)

asmUnpatchMapGlitchEnd:
b 0

#endif