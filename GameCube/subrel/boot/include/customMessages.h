#ifndef CUSTOM_MESSAGES_H
#define CUSTOM_MESSAGES_H

#include "item_wheel_menu.h"

#include <cstdint>

namespace mod::customMessages
{
    using namespace item_wheel_menu;

    struct MsgEntry
    {
        const char* msg;
        uint16_t size;
        uint16_t id;
    };

#ifdef TP_EU
    void getCurrentLanguage();
#endif
    void createMsgTable();
    void setDungeonItemAreaColorIndex();
    void createItemWheelMenuData();
    void createCharloDonationMessage();

#ifndef TP_JP
    // English
    extern const MsgEntry entriesUs[];
    extern const uint32_t totalCustomMessagesUs;
    extern const MsgEntry charloDonationEntryUs;
    extern const ItemWheelMenuStrings itemWheelMenuStringsUs;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsUs;
#else
    // Japanese
    extern const MsgEntry entriesJp[];
    extern const uint32_t totalCustomMessagesJp;
    extern const MsgEntry charloDonationEntryJp;
    extern const ItemWheelMenuStrings itemWheelMenuStringsJp;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsJp;
#endif

#ifdef TP_EU
    // German
    extern const MsgEntry entriesDe[];
    extern const uint32_t totalCustomMessagesDe;
    extern const MsgEntry charloDonationEntryDe;
    extern const ItemWheelMenuStrings itemWheelMenuStringsDe;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsDe;

    // French
    extern const MsgEntry entriesFr[];
    extern const uint32_t totalCustomMessagesFr;
    extern const MsgEntry charloDonationEntryFr;
    extern const ItemWheelMenuStrings itemWheelMenuStringsFr;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsFr;

    // Spanish
    extern const MsgEntry entriesSp[];
    extern const uint32_t totalCustomMessagesSp;
    extern const MsgEntry charloDonationEntrySp;
    extern const ItemWheelMenuStrings itemWheelMenuStringsSp;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsSp;

    // Italian
    extern const MsgEntry entriesIt[];
    extern const uint32_t totalCustomMessagesIt;
    extern const MsgEntry charloDonationEntryIt;
    extern const ItemWheelMenuStrings itemWheelMenuStringsIt;
    extern const ItemWheelMenuOffsets itemWheelMenuOffsetsIt;
#endif
} // namespace mod::customMessages
#endif