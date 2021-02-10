#include "main.h"

#include <tp/JFWSystem.h>

#include <cstdint>
#include <cstring>

namespace mod
{
    void main()
    {
        // Enable the console and set the individual lines to be shown
        libtp::tp::jfw_system::systemConsole->consoleEnabled = true;
        libtp::tp::jfw_system::systemConsole->consoleLine[0].showLine = true;
        libtp::tp::jfw_system::systemConsole->consoleLine[1].showLine = true;

        // Copy text data into the console line buffer
        strcpy( libtp::tp::jfw_system::systemConsole->consoleLine[0].line, "Build: " );
        strcpy( &libtp::tp::jfw_system::systemConsole->consoleLine[0].line[7], _BUILDID );
        strcpy( libtp::tp::jfw_system::systemConsole->consoleLine[1].line, "Hello World" );
        return;
    }
}     // namespace mod