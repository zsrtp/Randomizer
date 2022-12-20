#ifndef CUSTOM_MESSAGES_H
#define CUSTOM_MESSAGES_H

#include "item_wheel_menu.h"

#include <cstdint>

namespace mod::customMessages
{
    using namespace item_wheel_menu;

#define TOTAL_CUSTOM_MESSAGES 45

    struct MsgEntry
    {
        const char* msg;
        uint16_t size;
        uint16_t id;
    };

    void createMsgTable();
    void createItemWheelMenuData();
    void createCharloDonationMessage();

#ifndef TP_JP
    // English
    extern MsgEntry entriesUs[TOTAL_CUSTOM_MESSAGES];
    extern const MsgEntry charloDonationEntryUs;
    extern const ItemWheelMenuStrings itemWheelMenuStringsUs;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsUs;
#else
    // Japanese
    extern MsgEntry entriesJp[TOTAL_CUSTOM_MESSAGES];
    extern const MsgEntry charloDonationEntryJp;
    extern const ItemWheelMenuStrings itemWheelMenuStringsJp;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsJp;
#endif

#ifdef TP_EU
    // German
    extern MsgEntry entriesDe[TOTAL_CUSTOM_MESSAGES];
    extern const MsgEntry charloDonationEntryDe;
    extern const ItemWheelMenuStrings itemWheelMenuStringsDe;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsDe;

    // French
    extern MsgEntry entriesFr[TOTAL_CUSTOM_MESSAGES];
    extern const MsgEntry charloDonationEntryFr;
    extern const ItemWheelMenuStrings itemWheelMenuStringsFr;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsFr;

    // Spanish
    extern MsgEntry entriesSp[TOTAL_CUSTOM_MESSAGES];
    extern const MsgEntry charloDonationEntrySp;
    extern const ItemWheelMenuStrings itemWheelMenuStringsSp;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsSp;

    // Italian
    extern MsgEntry entriesIt[TOTAL_CUSTOM_MESSAGES];
    extern const MsgEntry charloDonationEntryIt;
    extern const ItemWheelMenuStrings itemWheelMenuStringsIt;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsIt;
#endif
}     // namespace mod::customMessages
#endif