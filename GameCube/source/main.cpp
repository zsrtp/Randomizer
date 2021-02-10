#include "main.h"

#include <tp/JFWSystem.h>

#include <cstdint>
#include <cstring>

namespace mod
{
    void main()
    {
        libtp::tp::jfw_system::systemConsole->consoleEnabled = true;
        libtp::tp::jfw_system::systemConsole->consoleLine[0].showLine = true;
        strcpy( libtp::tp::jfw_system::systemConsole->consoleLine[0].line, "Hello World" );
        return;
    }
}     // namespace mod