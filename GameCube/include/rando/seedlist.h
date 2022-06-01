/**	@file seedselector.h
 *  @brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SEEDLIST_H
#define RANDO_SEEDLIST_H

#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"

#define SEED_MAX_ENTRIES 10
#define _VERSION_MAJOR 1
#define _VERSION_MINOR 0

namespace mod::rando
{
    class SeedList
    {
       public:
        SeedList( void );
        ~SeedList( void );

        SeedInfo FindSeed( uint64_t seed );

        uint8_t m_numSeeds;
        uint8_t m_selectedSeed;

        SeedInfo* m_seedInfo = nullptr;
    };
}     // namespace mod::rando
#endif