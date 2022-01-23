
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
#include "tp/d_save.h"
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

    /**
     * @brief Runs when the randomizer is trying to set a flag related to learning a hidden skill.
     *
     * @param randomizer Pointer to mod::randomizer
     * @param eventIndex The offset from saveBitLabels that contains the flag being set.
     */
    void onHiddenSkill( rando::Randomizer* randomizer, uint16_t eventIndex );

    /**
     * @brief Runs when the game loads the ARC files from the game disc.
     *
     * @param randomizer Pointer to mod::randomizer.
     * @param filePtr Pointer to the file being read.
     * @param fileIndex Index of the file being read.
     */
    void onARC( rando::Randomizer* randomizer, void* filePtr, int32_t fileIndex );

    /**
     * @brief Runs when the player selects a bug to give to Agitha
     *
     * @param randomizer Pointer to mod::randomizer.
     * @param msgEventAddress The address for the message events for the specified actor.
     * @param bugID The item ID of the bug being presented.
     */
    void onBugReward( rando::Randomizer* randomizer, uint32_t msgEventAddress, uint8_t bugID );

    /**
     * @brief Runs when the game attempts to give the player a sky character
     *
     * @param randomizer Pointer to mod::randomizer.
     */
    uint8_t onSkyCharacter( rando::Randomizer* randomizer );

    /**
     * @brief Runs when the game attempts to give the player an item
     *
     * @param randomizer Pointer to mod::randomizer.
     * @param itemID The ID of the item the game is trying to give
     */
    uint32_t verifyProgressiveItem( rando::Randomizer* randomizer, uint32_t itemID );
}     // namespace mod::events
#endif