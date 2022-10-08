/**	@file check.h
 *  @brief Contains structs for different types of checks.
 *
 *  StageIDX are different size on purpose for alignment/padding, they should never exceed 0xFF.
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#ifndef RANDO_DATA_H
#define RANDO_DATA_H

#include "gc_wii/card.h"
#include <cstdint>

namespace mod::rando
{
    /**
     *  @brief Optional functions that have to be executed once and patch/modify the game code
     */
    struct entryInfo
    {
        uint16_t numEntries;
        uint16_t dataOffset;
    } __attribute__( ( __packed__ ) );

    struct Header
    {
        /* 0x00 */ uint16_t versionMajor;         // SeedData version major
        /* 0x02 */ uint16_t versionMinor;         // SeedData version minor
        /* 0x04 */ uint16_t headerSize;           // Total size of the header in bytes
        /* 0x06 */ uint16_t dataSize;             // Total number of bytes of seed data
        /* 0x08 */ uint32_t totalSize;            // Total number of bytes in the GCI
        /* 0x0C */ uint32_t requiredDungeons;     // Bitfield containing which dungeons are required to beat the seed. Only 8
                                                  // bits are used, while the rest are reserved for future updates

        // BitArray where each bit represents a patch/modification to be applied for this
        // playthrough; these patchs/modifications must be applied every time a file is loaded
        /* 0x10 */ entryInfo volatilePatchInfo;

        // BitArray where each bit represents a patch/modification to be applied for this
        // playthrough; these patchs/modifications must be applied only when a seed is loaded
        /* 0x14 */ entryInfo oneTimePatchInfo;

        /* 0x18 */ entryInfo eventFlagsInfo;      // eventFlags that need to be set for this seed
        /* 0x1C */ entryInfo regionFlagsInfo;     // regionFlags that need to be set, alternating

        /* 0x20 */ entryInfo dzxCheckInfo;
        /* 0x24 */ entryInfo relCheckInfo;
        /* 0x28 */ entryInfo poeCheckInfo;
        /* 0x2C */ entryInfo arcCheckInfo;
        /* 0x30 */ entryInfo objectArcCheckInfo;
        /* 0x34 */ entryInfo bossCheckInfo;
        /* 0x38 */ entryInfo hiddenSkillCheckInfo;
        /* 0x3C */ entryInfo bugRewardCheckInfo;
        /* 0x40 */ entryInfo skyCharacterCheckInfo;
        /* 0x44 */ entryInfo shopItemCheckInfo;
        /* 0x48 */ entryInfo startingItemInfo;
        /* 0x4C */ uint16_t bgmHeaderOffset;
        /* 0x4E */ uint16_t clr0Offset;
        /* 0x50 */ uint8_t transformAnywhere;
        /* 0x51 */ uint8_t quickTransform;
        /* 0x52 */ uint8_t castleRequirements;
        /* 0x53 */ uint8_t palaceRequirements;
    } __attribute__( ( __packed__ ) );

    // Minimum amount of data needed for keeping track of a seed
    struct MinSeedInfo
    {
        uint16_t versionMajor;     // SeedData version major
        uint16_t versionMinor;     // SeedData version minor
        uint32_t totalSize;        // Total number of bytes in the GCI
        uint8_t fileIndex;         // (0-126)
        char fileName[CARD_FILENAME_MAX + 1];
        uint8_t padding[2];
    } __attribute__( ( __packed__ ) );

    struct SeedInfo
    {
        Header header;
        MinSeedInfo* minSeedInfo;
    };

    struct bgmHeader
    {
        uint16_t bgmTableSize;
        uint16_t fanfareTableSize;
        uint16_t bgmTableOffset;
        uint16_t fanfareTableOffset;
        uint8_t bgmTableNumEntries;
        uint8_t fanfareTableNumEntries;
        uint8_t padding[2];
    } __attribute__( ( __packed__ ) );

    struct bgmReplacement
    {
        uint8_t originalBgmTrack;
        uint8_t replacementBgmTrack;
        uint8_t replacementBgmWave;
        uint8_t padding;
    };

    struct regionFlag
    {
        uint8_t region_id;
        uint8_t bit_id;
    } __attribute__( ( __packed__ ) );

    struct eventFlag
    {
        uint8_t offset;
        uint8_t flag;
    } __attribute__( ( __packed__ ) );

    struct dzxCheck
    {
        uint16_t hash;
        uint8_t stageIDX;
        uint8_t magicByte;     // ignore this byte in data[]
        uint8_t data[0x20];
    } __attribute__( ( __packed__ ) );

    struct shopCheck
    {
        uint16_t shopItemID;            // target item id
        uint16_t replacementItemID;     // replacement item id
    } __attribute__( ( __packed__ ) );

    struct RELCheck
    {
        uint16_t replacementType;
        uint16_t stageIDX;
        uint32_t moduleID;
        uint32_t offset;
        uint32_t override;
    } __attribute__( ( __packed__ ) );

    struct POECheck
    {
        uint8_t stageIDX;
        uint8_t flag;      // Flag used for identification
        uint16_t item;     // New item id
    } __attribute__( ( __packed__ ) );

    enum class FileDirectory : uint8_t
    {
        Room = 0x0,
        Message = 0x1,
        Object = 0x2,
        Stage = 0x3,
    };

    enum class ReplacementType : uint8_t
    {
        Item = 0x0,                // Standard item replacement
        HiddenSkill = 0x1,         // Hidden Skill checks check for the room last loaded into.
        ItemMessage = 0x2,         // Replaces messages for item IDs
        Instruction = 0x3,         // Replaces a u32 instruction
        AlwaysLoaded = 0x4,        // Replaces values specifically in the bmgres archive which is always loaded.
        MessageResource = 0x5,     // Replaces values in the MESG section of a bmgres archive file.
    };

    struct ARCReplacement
    {
        int32_t offset;                      // The offset where the item is stored from the message flow header.
        uint32_t replacementValue;           // Used to be item, but can be more now.
        FileDirectory directory;             // The type of directory where the check is stored.
        ReplacementType replacementType;     // The type of replacement that is taking place.
        uint8_t stageIDX;                    // The name of the file where the check is stored
        uint8_t roomID;                      // The room number for chests/room based dzr checks.
    } __attribute__( ( __packed__ ) );

    struct ObjectArchiveReplacement
    {
        int32_t offset;                // The offset where the item is stored from the message flow header.
        uint32_t replacementValue;     // Used to be item, but can be more now.
        char fileName[15];
        uint8_t stageIDX;     // The name of the file where the check is stored
    } __attribute__( ( __packed__ ) );

    struct BOSSCheck
    {
        uint16_t stageIDX;     // The stage where the replacement is taking place.
        uint16_t item;         // New item id
    } __attribute__( ( __packed__ ) );

    struct HiddenSkillCheck
    {
        uint16_t indexNumber;     // The flag that is trying to be set for the specific Golden Wolf that the skill has been
                                  // learned from.
        uint16_t itemID;          // The item to be given when the above flag is set.
        uint16_t stageIDX;        // The ID of the stage that Golden Wolf was located in
        uint16_t roomID;          // The room of the stage that the Golden Wolf was located in.
    } __attribute__( ( __packed__ ) );

    struct BugReward
    {
        uint16_t bugID;      // The bug that link is showing to Agitha
        uint16_t itemID;     // The item that Agitha will give Link.
    } __attribute__( ( __packed__ ) );

    struct SkyCharacter
    {
        uint8_t itemID;        // The item to be given.
        uint16_t stageIDX;     // The stage that the Owl Statue is located.
        uint8_t roomID;        // The room that the Owl Statue is located in.
    } __attribute__( ( __packed__ ) );

    struct CustomMessageEntryInfo
    {
        uint8_t language;
        uint8_t padding[1];
        uint16_t totalEntries;
        uint32_t msgTableSize;
        uint32_t msgIdTableOffset;
    } __attribute__( ( __packed__ ) );

    struct CustomMessageHeaderInfo
    {
        uint16_t headerSize;
        uint8_t totalLanguages;
        uint8_t padding[1];
        CustomMessageEntryInfo entry[];     // Size is totalLanguages
    } __attribute__( ( __packed__ ) );

    struct CLR0Header
    {
        /* 0x00 */ uint32_t totalByteLength;      // Total byte size of the entire CLR0 chunk
        /* 0x04 */ uint32_t numBmdEntries;        // Total number of bmd replacement entries.
        /* 0x08 */ uint16_t bmdEntriesOffset;     // Offset to the list of bmd entries
        /* 0x0A */ uint16_t rawRGBOffset;         // Offset to the list of raw RGB entries
    } __attribute__( ( __packed__ ) );

    struct BmdEntry
    {
        /* 0x00 */ uint8_t recolorType;            // 0: CMPR, 1: MAT, etc.
        /* 0x01 */ uint8_t archiveIndex;           // The index of the archive used to load the texture replacement.
        /* 0x02 */ uint16_t numTextures;           // number of textures that are being recolored in this bmd file.
        /* 0x04 */ uint16_t textureListOffset;     // offset to the list of textures being recolored.
        /* 0x06 */ char bmdRes[0x12];              // names are of varying size, but I haven't seen one over 0x10 yet.
    } __attribute__( ( __packed__ ) );

    struct CMPRTextureEntry
    {
        /* 0x00 */ uint32_t rgba;
        /* 0x04 */ char textureName[0xC];
    } __attribute__( ( __packed__ ) );

    enum RecolorType : uint8_t
    {
        CMPR = 0,
        MAT = 1,
        Invalid = 0xFF,
    };

    enum RawRGBId : uint8_t
    {
        LanternGlow,
        Hearts,
        ABtn,
        BBtn,
        XBtn,
        YBtn,
        ZBtn
    };

    struct RawRGBTable
    {
        uint32_t lanternColor;
        uint32_t heartColor;
        uint32_t aButtonColor;
        uint32_t bButtonColor;
        uint32_t xButtonColor;
        uint32_t yButtonColor;
        uint32_t zButtonColor;
    } __attribute__( ( __packed__ ) );

    enum DvdEntryNumId : uint8_t
    {
        // DO NOT set any of these enums to a specific value. The exact values
        // and the order are irrelevant (other than `DvdEntryNumIdSize` which
        // must go last).
        ResObjectKmdl,     // Link wearing Hero's Clothes
        ResObjectZmdl,     // Link wearing Zora Armor
                           // ResObjectWmdl,      // Wolf Link and Midna on back
                           // ResObjectCWShd,     // Ordon Shield
                           // ResObjectSWShd,     // Wooden Shield
                           // ResObjectHyShd,     // Hylian Shield

        DvdEntryNumIdSize,
        // DvdEntryNumIdSize MUST GO LAST. When adding a new enum, put it above
        // this one and don't forget to actually add the lookup in the
        // `dvdentrynum.cpp` file!
    };

    extern int32_t lookupTable[DvdEntryNumIdSize];

}     // namespace mod::rando
#endif