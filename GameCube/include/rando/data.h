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
        uint16_t minVersion;     // minimal required REL version, u8 Major and u8 Minor
        uint16_t maxVersion;     // maximum supported REL version, u8 Major and u8 Minor
        uint16_t headerSize;     // Total size of the header in bytes
        uint16_t dataSize;       // Total number of bytes of seed data
        uint64_t seed;           // Current seed
        uint32_t totalSize;      // Total number of bytes in the gci.

        entryInfo patchInfo;     // bitArray where each bit represents a patch/modification to be applied for this playthrough
        entryInfo eventFlagsInfo;      // eventFlags that need to be set for this seed
        entryInfo regionFlagsInfo;     // regionFlags that need to be set, alternating

        entryInfo dzxCheckInfo;
        entryInfo relCheckInfo;
        entryInfo poeCheckInfo;
        entryInfo arcCheckInfo;
        entryInfo objectArcCheckInfo;
        entryInfo bossCheckInfo;
        entryInfo hiddenSkillCheckInfo;
        entryInfo bugRewardCheckInfo;
        entryInfo skyCharacterCheckInfo;
        entryInfo shopItemCheckInfo;
        entryInfo startingItemInfo;
        uint16_t customTextHeaderSize;
        uint16_t customTextHeaderOffset;
        uint8_t heartColor;
        uint8_t aButtonColor;
        uint8_t bButtonColor;
        uint8_t xButtonColor;
        uint8_t yButtonColor;
        uint8_t zButtonColor;
        uint8_t lanternColor;
        uint8_t transformAnywhere;
        uint8_t quickTransform;
        uint8_t castleRequirements;
        uint8_t palaceRequirements;
        uint8_t padding[0x3];
    } __attribute__( ( __packed__ ) );

    // Seed with index
    struct SeedInfo
    {
        Header header;
        uint8_t fileIndex;     // (0-9) rando-dataX
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
        uint32_t stageIDX;
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

    enum class ArcReplacementType : uint8_t
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
        int32_t offset;                         // The offset where the item is stored from the message flow header.
        uint32_t replacementValue;              // Used to be item, but can be more now.
        FileDirectory directory;                // The type of directory where the check is stored.
        ArcReplacementType replacementType;     // The type of replacement that is taking place.
        uint8_t stageIDX;                       // The name of the file where the check is stored
        uint8_t roomID;                         // The room number for chests/room based dzr checks.
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
        uint16_t minVersion;
        uint16_t maxVersion;
        uint16_t headerSize;
        uint8_t totalLanguages;
        uint8_t padding[1];
        CustomMessageEntryInfo entry[];     // Size is totalLanguages
    } __attribute__( ( __packed__ ) );

}     // namespace mod::rando
#endif