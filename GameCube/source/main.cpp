#include "main.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "patch.h"
#include "tp/f_ap_game.h"
#include "tp/m_do_controller_pad.h"

namespace mod
{
    // Bind extern global variables
    libtp::display::Console* console = new libtp::display::Console();
    rando::SeedSelector* seedSelector = new rando::SeedSelector();
    rando::Randomizer* randomizer = nullptr;

    bool consoleState = true;
    void ( *return_fapGm_Execute )( void ) = nullptr;

    uint32_t lastButtonInput = 0;

    void main() { hookFunctions(); }

    void hookFunctions()
    {
        // Hook functions
        return_fapGm_Execute = libtp::patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, mod::handle_fapGm_Execute );
        *console << "Functions have been hooked\n";
    }

    // TODO: Depending on the current state of the game we want this function to behave differently; i.e. there is no
    // seedselector (required) when we're ingame; instead we will have the Randomizer
    void handle_fapGm_Execute()
    {
        using namespace libtp;
        using namespace tp::m_do_controller_pad;
        uint32_t buttonInput = tp::m_do_controller_pad::cpadInfo.buttonInput;

        // handle button inputs only if buttons are being held that weren't held last time
        if ( buttonInput && buttonInput != lastButtonInput )
        {
            if ( ( buttonInput & ( PadInputs::Button_R | PadInputs::Button_Z ) ) ==
                 ( PadInputs::Button_R | PadInputs::Button_Z ) )
            {
                consoleState = !consoleState;
                display::setConsole( consoleState, 0 );
            }

            // Handle Inputs if console is active
            if ( consoleState )
            {
                if ( seedSelector->HandleInputs( buttonInput ) )
                {
                    // print information
                    *console << seedSelector->m_StatusText << "\n";
                }
            }
        }

        lastButtonInput = buttonInput;
        return return_fapGm_Execute();
    }
}     // namespace mod