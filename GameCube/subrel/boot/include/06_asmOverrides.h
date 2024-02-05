#ifndef RANDO_06_ASMOVERRIDES_H
#define RANDO_06_ASMOVERRIDES_H

#include <cstdint>

namespace libtp::boot
{
    extern "C" {
        extern uint32_t enableCrashScreen;
        extern uint32_t patchMessageCalculation;
    }
} // namespace libtp::boot


#endif