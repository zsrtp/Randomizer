.global asmAdjustSkyCharacterStart
.global asmAdjustSkyCharacterEnd

.hidden asmAdjustSkyCharacterStart
.hidden asmAdjustSkyCharacterEnd

asmAdjustSkyCharacterStart:
bl handleAdjustSkyCharacter

#ifdef PLATFORM_WII
mr %r28,%r3 # The item to give
#else
mr %r27,%r3 # The item to give
#endif

asmAdjustSkyCharacterEnd:
b 0