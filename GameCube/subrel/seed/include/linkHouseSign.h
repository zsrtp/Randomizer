#ifndef LINKHOUSESIGN_H
#define LINKHOUSESIGN_H

#include "rando/seed.h"

#include <cstdint>

namespace mod::link_house_sign
{
#define TOTAL_POSSIBLE_DUNGEONS 8

    void createRequiredDungeonsString( rando::Seed* seed, uint32_t requiredDungeonFlags );

#ifndef TP_JP
    // English
    extern const char* dungeonsUs[TOTAL_POSSIBLE_DUNGEONS];
#else
    // Japanese
    extern const char* dungeonsJP[TOTAL_POSSIBLE_DUNGEONS];
#endif

#ifdef TP_EU
    // German
    extern const char* dungeonsDe[TOTAL_POSSIBLE_DUNGEONS];

    // French
    extern const char* dungeonsFr[TOTAL_POSSIBLE_DUNGEONS];

    // Spanish
    extern const char* dungeonsSp[TOTAL_POSSIBLE_DUNGEONS];

    // Italian
    extern const char* dungeonsIt[TOTAL_POSSIBLE_DUNGEONS];
#endif
}     // namespace mod::link_house_sign

#endif