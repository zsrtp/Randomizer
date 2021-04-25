
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
#include "rando/seedselector.h"

namespace mod
{
    extern libtp::display::Console* console;
    extern rando::SeedSelector* seedSelector;
    extern rando::Randomizer* randomizer;

    // Variables
    extern uint32_t lastButtonInput;
    extern bool consoleState;

    void main();
    void hookFunctions();

    // Function hook handlers & trampolines
    void handle_fapGm_Execute( void );
    extern void ( *return_fapGm_Execute )( void );

}     // namespace mod
#endif