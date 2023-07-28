/**	@file customItems.h
 *  @brief Contains structs and definitions for all code related to custom items
 *
 *	@author Lunar Soap
 *	@bug No known bugs.
 */
#ifndef RANDO_CUSTOMITEMS_H
#define RANDO_CUSTOMITEMS_H

#include <cstdint>

// Maximum expected number of spawned ice traps in any given area
#define MAX_SPAWNED_FOOLISH_ITEMS 6

namespace mod::rando::customItems
{

    enum CustomItemIDs : uint8_t
    {
        Foolish_Item_1 = 0x13,                    // Custom Item added for the Randomizer.
        Foolish_Item_2 = 0x14,                    // Custom Item added for the Randomizer.
        Foolish_Item_3 = 0x15,                    // Custom Item added for the Randomizer.
        Foolish_Item_4 = 0x4D,                    // Custom Item added for the Randomizer.
        Foolish_Item_5 = 0x4E,                    // Custom Item added for the Randomizer.
        Foolish_Item_6 = 0x57,                    // Custom Item added for the Randomizer.
        Forest_Temple_Small_Key = 0x85,           // Custom Item added for the Randomizer.
        Goron_Mines_Small_Key = 0x86,             // Custom Item added for the Randomizer.
        Lakebed_Temple_Small_Key = 0x87,          // Custom Item added for the Randomizer.
        Arbiters_Grounds_Small_Key = 0x88,        // Custom Item added for the Randomizer.
        Snowpeak_Ruins_Small_Key = 0x89,          // Custom Item added for the Randomizer.
        Temple_of_Time_Small_Key = 0x8A,          // Custom Item added for the Randomizer.
        City_in_The_Sky_Small_Key = 0x8B,         // Custom Item added for the Randomizer.
        Palace_of_Twilight_Small_Key = 0x8C,      // Custom Item added for the Randomizer.
        Hyrule_Castle_Small_Key = 0x8D,           // Custom Item added for the Randomizer.
        Bulblin_Camp_Key = 0x8E,                  // Custom Item added for the Randomizer.
        Forest_Temple_Big_Key = 0x92,             // Custom Item added for the Randomizer.
        Lakebed_Temple_Big_Key = 0x93,            // Custom Item added for the Randomizer.
        Arbiters_Grounds_Big_Key = 0x94,          // Custom Item added for the Randomizer.
        Temple_of_Time_Big_Key = 0x95,            // Custom Item added for the Randomizer.
        City_in_The_Sky_Big_Key = 0x96,           // Custom Item added for the Randomizer.
        Palace_of_Twilight_Big_Key = 0x97,        // Custom Item added for the Randomizer.
        Hyrule_Castle_Big_Key = 0x98,             // Custom Item added for the Randomizer.
        Forest_Temple_Compass = 0x99,             // Custom Item added for the Randomizer.
        Goron_Mines_Compass = 0x9A,               // Custom Item added for the Randomizer.
        Lakebed_Temple_Compass = 0x9B,            // Custom Item added for the Randomizer.
        Arbiters_Grounds_Compass = 0xA8,          // Custom Item added for the Randomizer.
        Snowpeak_Ruins_Compass = 0xA9,            // Custom Item added for the Randomizer.
        Temple_of_Time_Compass = 0xAA,            // Custom Item added for the Randomizer.
        City_in_The_Sky_Compass = 0xAB,           // Custom Item added for the Randomizer.
        Palace_of_Twilight_Compass = 0xAC,        // Custom Item added for the Randomizer.
        Hyrule_Castle_Compass = 0xAD,             // Custom Item added for the Randomizer.
        Forest_Temple_Dungeon_Map = 0xB6,         // Custom Item added for the Randomizer.
        Goron_Mines_Dungeon_Map = 0xB7,           // Custom Item added for the Randomizer.
        Lakebed_Temple_Dungeon_Map = 0xB8,        // Custom Item added for the Randomizer.
        Arbiters_Grounds_Dungeon_Map = 0xB9,      // Custom Item added for the Randomizer.
        Snowpeak_Ruins_Dungeon_Map = 0xBA,        // Custom Item added for the Randomizer.
        Temple_of_Time_Dungeon_Map = 0xBB,        // Custom Item added for the Randomizer.
        City_in_The_Sky_Dungeon_Map = 0xBC,       // Custom Item added for the Randomizer.
        Palace_of_Twilight_Dungeon_Map = 0xBD,    // Custom Item added for the Randomizer.
        Hyrule_Castle_Dungeon_Map = 0xBE,         // Custom Item added for the Randomizer.
        Fused_Shadow_1 = 0xD8,                    // Custom Item added for the Randomizer.
        Fused_Shadow_2 = 0xD9,                    // Custom Item added for the Randomizer.
        Fused_Shadow_3 = 0xDA,                    // Custom Item added for the Randomizer.
        Ancient_Sky_Book_First_Character = 0xDB,  // Custom Item added for the Randomizer.
        Ancient_Sky_Book_Second_Character = 0xDC, // Custom Item added for the Randomizer.
        Ancient_Sky_Book_Third_Character = 0xDD,  // Custom Item added for the Randomizer.
        Ancient_Sky_Book_Fourth_Character = 0xDE, // Custom Item added for the Randomizer.
        Ancient_Sky_Book_Fifth_Character = 0xDF,  // Custom Item added for the Randomizer.
        Ending_Blow = 0xE1,                       // Custom Item added for the Randomizer.
        Shield_Attack = 0xE2,                     // Custom Item added for the Randomizer.
        Back_Slice = 0xE3,                        // Custom Item added for the Randomizer.
        Helm_Splitter = 0xE4,                     // Custom Item added for the Randomizer.
        Mortal_Draw = 0xE5,                       // Custom Item added for the Randomizer.
        Jump_Strike = 0xE6,                       // Custom Item added for the Randomizer.
        Great_Spin = 0xE7,                        // Custom Item added for the Randomizer.
    };

    struct FoolishItems
    {
        static constexpr const uint8_t itemIds[MAX_SPAWNED_FOOLISH_ITEMS] = {
            Foolish_Item_1,
            Foolish_Item_2,
            Foolish_Item_3,
            Foolish_Item_4,
            Foolish_Item_5,
            Foolish_Item_6};                            // Array holding the IDs of all the ice traps

        uint8_t itemModelId[MAX_SPAWNED_FOOLISH_ITEMS]; // Array holding the IDs of the item that the ice trap is copying

        uint8_t spawnCount;                             // How many ice traps are currently spawned
        uint8_t triggerCount;                           // How many ice traps have been triggered and have yet to occur
    };

    extern int32_t lookupTable[DvdEntryNumIdSize];

} // namespace mod::rando::customItems
#endif