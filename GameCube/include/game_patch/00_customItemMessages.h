/** @file 00_customItemMessages.h
 * @author Lunar Soap
 * @brief Contains definitions for custom messages.
 *
 * @bug No known bugs
 */
#ifndef RANDO_ITEM_MESSAGE_PATCH_H
#define RANDO_ITEM_MESSAGE_PATCH_H

#include "rando/randomizer.h"
#include "tp/resource.h"

namespace mod::game_patch
{
    // Custom strings that are used for text search. Need a better way to do this.
    const char* talkToMidnaText = { "Talk to Midna" };
    const char* smallDonationText = { "30 Rupees" };
}     // namespace mod::game_patch
#endif