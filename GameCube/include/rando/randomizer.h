/**	@file randomizer.h
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_RANDOMIZER_H
#define RANDO_RANDOMIZER_H

#include <cinttypes>

#include "rando/data.h"
#include "rando/seed.h"
#include "rando/seedlist.h"
#include "tp/dzx.h"

namespace mod::rando
{
    class Randomizer
    {
       public:
        Randomizer( SeedInfo* seedInfo );
        ~Randomizer();

        void onStageLoad( void );
        void replaceDZX( libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );

       private:
        Seed* m_Seed;
    };
}     // namespace mod::rando
#endif