/**	@file seedselector.h
 *  @brief Selection tool to select the desired data-gci
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_SELECTOR_H
#define RANDO_SELECTOR_H
#include <cinttypes>

#include "rando/seed.h"
#include "rando/seedselector.h"

#define SEED_MAX_ENTRIES 10

namespace mod::rando
{
    class SeedSelector
    {
       public:
        SeedSelector( void );
        ~SeedSelector( void );

        /**
         *  @brief Button Input handler
         *
         *  @param buttonInput The buttons to be parsed
         *  @return True if the input was relevant
         */
        bool HandleInputs( uint32_t buttonInput );

        uint8_t m_selectedSeed;
        char* m_StatusText;

       private:
        gci::data::Header* m_Headers = new gci::data::Header[SEED_MAX_ENTRIES];
        uint8_t m_totalSeeds;
    };
}     // namespace mod::rando
#endif