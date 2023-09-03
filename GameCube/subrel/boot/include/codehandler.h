#ifndef RANDO_CODEHANDLER_H
#define RANDO_CODEHANDLER_H

#include <cstdint>

// Set up a define for the start of the hardware registers
// Set the name to a small amount of characters to avoid breaking formatting
#ifdef PLATFORM_WII
#define HRSA 0xCD
#else
#define HRSA 0xCC
#endif

namespace mod::codehandler
{
    extern const uint8_t codehandler[];
    extern const uint16_t codehandlerSize;
} // namespace mod::codehandler

#endif