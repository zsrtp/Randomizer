#include "main.h"

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "chronos/timer.h"
#include "patch.h"
#include "tp/JFWSystem.h"
#include "tp/f_ap_game.h"

namespace mod
{
    using namespace libtp::chronos;
    void main()
    {
        // Initialise rando-system
        return_fapGm_Execute = libtp::patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, []() {
            mod::t->tick();

            mod::return_fapGm_Execute();
        } );

        libtp::tp::jfw_system::systemConsole->consoleEnabled = true;

        t = new IntervalTimer( 120, []( Timer* timer ) {
            libtp::tp::jfw_system::systemConsole->consoleLine[timer->m_ExecCount].showLine = true;
            sprintf( libtp::tp::jfw_system::systemConsole->consoleLine[timer->m_ExecCount].line,
                     "Timer Handler: #%" PRId32,
                     timer->m_ExecCount );
        } );

        return;
    }
}     // namespace mod