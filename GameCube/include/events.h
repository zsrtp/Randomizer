
/**	@file events.h
 *  @brief Custom events
 *
 *	@author AECX
 *	@bug No known bugs.
 *  @todo Expand this to allow dynamic addition/removal of functions to be executed within the event function
 */

#ifndef EVENTS_H
#define EVENTS_H
#include <cinttypes>

#include "rando/randomizer.h"
#include "tp/dzx.h"

namespace mod::events
{
    /**
     * @brief Runs when loading just started
     *
     * @param randomizer Pointer to mod::randomizer
     */
    void onLoad( rando::Randomizer* randomizer );

    /**
     * @brief Runs when loading just finished
     *
     * @param randomizer Pointer to mod::randomizer
     */
    void offLoad( rando::Randomizer* randomizer );

    /**
     * @brief Runs when one of the DZX init functions run
     *
     * @param randomizer Pointer to mod::randomizer
     * @param chunkTypeInfo ChunkTypeInfo of DZX entries
     */
    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );
}     // namespace mod::events
#endif