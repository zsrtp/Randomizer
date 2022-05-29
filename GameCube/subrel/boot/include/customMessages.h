#ifndef CUSTOM_MESSAGES_H
#define CUSTOM_MESSAGES_H

#include <cstdint>

namespace mod::customMessages
{
#define TOTAL_CUSTOM_MESSAGES 59

    struct MsgEntry
    {
        const char* msg;
        uint32_t size;
        uint16_t id;
    };

    void createMsgTable();

#ifndef TP_JP
    // English
    extern MsgEntry entriesUs[TOTAL_CUSTOM_MESSAGES];
#else
    // Japanese
    extern MsgEntry entriesJp[TOTAL_CUSTOM_MESSAGES];
#endif

#ifdef TP_EU
    // German
    extern MsgEntry entriesDe[TOTAL_CUSTOM_MESSAGES];

    // French
    extern MsgEntry entriesFr[TOTAL_CUSTOM_MESSAGES];

    // Spanish
    extern MsgEntry entriesSp[TOTAL_CUSTOM_MESSAGES];

    // Italian
    extern MsgEntry entriesIt[TOTAL_CUSTOM_MESSAGES];
#endif
}     // namespace mod::customMessages
#endif