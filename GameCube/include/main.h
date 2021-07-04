
/**	@file main.h
 *  @brief Main structure of the Randomizer
 *
 *	@author AECX
 *	@bug No known bugs.
 */

#ifndef MAIN_H
#define MAIN_H
#include <cstdint>

#include "display/console.h"
#include "rando/randomizer.h"
#include "rando/seedlist.h"

// Game States
#define GAME_BOOT 0       // Default; At startup (should only ever be active once)
#define GAME_TITLE 1      // When user is on title screen; let them choose their seed etc.
#define GAME_ACTIVE 2     // When user is ingame and rando should be active

namespace mod
{
    // General public objects
    extern libtp::display::Console console;
    extern rando::Randomizer* randomizer;
    extern rando::SeedList seedList;

    // Variables
    extern uint32_t lastButtonInput;
    extern bool consoleState;
    extern uint8_t gameState;

    void main();
    void hookFunctions();
    void setScreen( bool state );     // Sets visibility of console

    void handleInput( uint32_t inputs );

    // Function hook handlers & trampolines
    void handle_fapGm_Execute( void );
    extern void ( *return_fapGm_Execute )( void );

}     // namespace mod
#endif