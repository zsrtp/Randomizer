.global asmAdjustSkyCharacterStart
.global asmAdjustSkyCharacterEnd

.hidden asmAdjustSkyCharacterStart
.hidden asmAdjustSkyCharacterEnd

asmAdjustSkyCharacterStart:
bl handleAdjustSkyCharacter
mr %r27,%r3 #The item to give

asmAdjustSkyCharacterEnd:
b 0