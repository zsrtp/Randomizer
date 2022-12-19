#ifndef ITEM_WHEEL_MENU_H
#define ITEM_WHEEL_MENU_H

#include <cstdint>

namespace mod::item_wheel_menu
{
    // Set up an enum for accessing specific areas
    enum TrackedAreas
    {
        FOREST_TEMPLE = 0,
        GORON_MINES,
        LAKEBED_TEMPLE,
        ARBITERS_GROUNDS,
        SNOWPEAK_RUINS,
        TEMPLE_OF_TIME,
        CITY_IN_THE_SKY,
        PALACE_OF_TWILIGHT,
        HYRULE_CASTLE,
        FARON_WOODS,
        BULBLIN_CAMP,
        TRACKED_AREAS_END
    };

    // Set up a struct for holding the strings
    struct ItemWheelMenuStrings
    {
        // Areas being tracked
        const char* areasBeingTracked[TRACKED_AREAS_END];

        // Seed:
        const char* seedIsLoaded;

        // Seed is not currently loaded
        const char* seedIsNotLoaded;

        // Yes/No
        const char* yes;
        const char* no;

        // Fused Shadows\nMirror Shards
        const char* shadowsShards;

        const char* pumpkin;
        const char* cheese;
        const char* gateKeys;
        const char* areas;
        const char* smallKeys;
        const char* bigKeys;
        const char* maps;
        const char* compasses;

        // Press buttons to display/hide menu
        const char* helpText;
    };

    // Set up a struct for holding the offsets
    struct ItemWheelMenuOffsets
    {
        // Fused Shadows
        uint8_t shadowsShardsOffset;     // Fused Shadows text to the start of the values

        // Pumpkin
        uint8_t pumpkinOffset;        // Fused Shadows values to the start of the text
        uint8_t pumpkinYesOffset;     // Pumpkin text to the start of the value
        uint8_t pumpkinNoOffset;      // Pumpkin text to the start of the value

        // Cheese
        uint8_t cheeseOffset;        // Pumpkin text to the start of the text
        uint8_t cheeseYesOffset;     // Cheese text to the start of the value
        uint8_t cheeseNoOffset;      // Cheese text to the start of the value

        // Gate Keys
        uint8_t gateKeysOffset;        // Cheese text to the start of the text
        uint8_t gateKeysYesOffset;     // Gate Keys text to the start of the value
        uint8_t gateKeysNoOffset;      // Gate Keys text to the start of the value

        // Headers
        uint8_t headerSmallKeysOffset;     // Areas text to the start of the text
        uint8_t headerBigKeysOffset;       // Small keys text to the start of the text
        uint8_t headerMapsOffset;          // Big keys text to the start of the text
        uint8_t headerCompassesOffset;     // Maps text to the start of the text

        // Header values
        // Small Keys
        uint8_t valuesSmallKeysOffset;     // Small keys text to the start of the values

        // Big Keys
        uint8_t valuesBigKeysYesOffset;       // Big keys text to the start of the values
        uint8_t valuesBigKeysNoOffset;        // Big keys text to the start of the values
        uint8_t valuesBigKeysMinesOffset;     // Big keys text to the start of the values

        // Maps
        uint8_t valuesMapsYesOffset;     // Maps text to the start of the values
        uint8_t valuesMapsNoOffset;      // Maps text to the start of the values

        // Compasses
        uint8_t valuesCompassesYesOffset;     // Compasses text to the start of the values
        uint8_t valuesCompassesNoOffset;      // Compasses text to the start of the values
    };

    // Set up a struct for holding the strings and offsets
    struct ItemWheelMenuData
    {
        // Pointer to all of the dynamic text
        // This is allocated memory
        const char* textData;

        // Strings used within the menu
        ItemWheelMenuStrings strings;

        // Offsets used within the menu
        ItemWheelMenuOffsets offsets;
    };

    extern ItemWheelMenuData itemWheelMenuData;

    // The ring is drawn more than once per frame, so this is set to true on the first draw
    extern bool ringDrawnThisFrame;

    // Handles whether the menu should be displayed or not
    extern bool displayMenu;

    // Function hook handlers & trampolines
    extern void ( *return_dMenuRing__create )( void* dMenuRing );
    extern void ( *return_dMenuRing__delete )( void* dMenuRing );
    extern void ( *return_dMenuRing__draw )( void* dMenuRing );
    void handle_dMenuRing__create( void* dMenuRing );
    void handle_dMenuRing__delete( void* dMenuRing );
    void handle_dMenuRing__draw( void* dMenuRing );
}     // namespace mod::item_wheel_menu

#endif