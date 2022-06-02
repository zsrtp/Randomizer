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
        GERUDO_DESERT,
        TRACKED_AREAS_END
    };

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