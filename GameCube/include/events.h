
/**	@file events.h
 *  @brief Custom events
 *
 *	@author AECX
 *	@bug No known bugs.
 *  @todo Expand this to allow dynamic addition/removal of functions to be executed within the event function
 */

#ifndef EVENTS_H
#define EVENTS_H

#include "data/items.h"
#include "rando/randomizer.h"
#include "tp/dynamic_link.h"
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
     * @brief Runs after a module has been linked
     *
     * @param randomizer Pointer to mod::randomizer
     * @param dmc DynamicModuleControl
     */
    void onRELLink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc );

    /**
     * @brief Runs when one of the DZX init functions run
     *
     * @param randomizer Pointer to mod::randomizer
     * @param chunkTypeInfo ChunkTypeInfo of DZX entries
     */
    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );

    /**
     * @brief Runs when a Poe (e_hp, e_po) is killed
     *
     * @param flag Save flag for e_hp (normal Poes) for AG poes its [probably] the event ID; Both are unique identifiers within
     * their respective Area
     */
    int32_t onPoe( rando::Randomizer* randomizer, uint8_t flag );
}     // namespace mod::events
#endif