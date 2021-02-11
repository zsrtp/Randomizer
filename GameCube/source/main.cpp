#include "main.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "display/console.h"
namespace mod
{
    void main()
    {
        // New custom console
        libtp::display::Console c = libtp::display::Console();
        c << "Hello World!\n"
          << "How do you like " _PROJECT_NAME "?";

        return;
    }
}     // namespace mod