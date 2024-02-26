#ifndef LINKHOUSESIGN_H
#define LINKHOUSESIGN_H

#include "rando/seed.h"

#include <cstdint>

namespace mod::link_house_sign
{
#define TOTAL_POSSIBLE_DUNGEONS 8

    void createRequiredDungeonsString(rando::Seed* seed, uint32_t requiredDungeonFlags);

#ifndef TP_JP
    // English
    extern const char* dungeonsUs[TOTAL_POSSIBLE_DUNGEONS];
    extern const char* noDungeonsRequiredUs;
#else
    // Japanese
    extern const char* snowpeakRuinsJp;
    extern const char* dungeonsJp[TOTAL_POSSIBLE_DUNGEONS];
    extern const char* noDungeonsRequiredJp;
#endif

#if defined TP_EU || defined TP_WUS2
    // French
    extern const char* dungeonsFr[TOTAL_POSSIBLE_DUNGEONS];
    extern const char* noDungeonsRequiredFr;

    // Spanish
    extern const char* dungeonsSp[TOTAL_POSSIBLE_DUNGEONS];
    extern const char* noDungeonsRequiredSp;

#ifndef TP_WUS2
    // German
    extern const char* dungeonsDe[TOTAL_POSSIBLE_DUNGEONS];
    extern const char* noDungeonsRequiredDe;

    // Italian
    extern const char* dungeonsIt[TOTAL_POSSIBLE_DUNGEONS];
    extern const char* noDungeonsRequiredIt;
#endif
#endif
} // namespace mod::link_house_sign

#endif