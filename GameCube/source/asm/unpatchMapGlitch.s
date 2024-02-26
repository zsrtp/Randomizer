#if defined TP_GJP || defined TP_WUS2

.global asmUnpatchMapGlitchStart
.global asmUnpatchMapGlitchEnd
# asmUnpatchMapGlitchStart and asmUnpatchMapGlitchEnd both need to be used in at least one subrel, so they cannot be set to hidden

asmUnpatchMapGlitchStart:
#ifdef TP_WUS2
mr %r3,%r31 # d_a_alink
#else
mr %r3,%r30 # d_a_alink
#endif
bl unpatchMapGlitch

# Restore the original instruction
#ifdef TP_WUS2
lis %r4,0x804A
#else
lbz %r0,0xC0(%r29)
#endif

asmUnpatchMapGlitchEnd:
b 0

#endif