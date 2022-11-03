.global asmAdjustSkyCharacterStart
.global asmAdjustSkyCharacterEnd

.hidden asmAdjustSkyCharacterStart
.hidden asmAdjustSkyCharacterEnd

asmAdjustSkyCharacterStart:
bl handleAdjustSkyCharacter
mr %r27,%r3

asmAdjustSkyCharacterEnd:
b 0