#include "main.h"

#include <cstdint>
#include <cstring>

#include "display/console.h"
#include "patch.h"

namespace mod
{
    void main()
    {
        libtp::display::Console cout {};

        cout << "Hello world";
    }
}     // namespace mod