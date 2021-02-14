#include "main.h"

#include <cstdint>
#include <cstring>

#include "display/console.h"
#include "patch.h"
#include "patches/changeFieldModels.h"

namespace mod
{
    void main()
    {
        libtp::display::Console cout {};

        libtp::patches::changeFieldModels();

        cout << "Field models have been patched!\n";
    }
}     // namespace mod