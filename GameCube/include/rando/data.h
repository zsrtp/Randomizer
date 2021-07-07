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
        uint32_t fileSize;       // Total number of bytes including the header
        uint64_t seed;           // Current seed
        uint16_t minVersion;     // minimal required REL version, u8 Major and u8 Minor
        uint16_t maxVersion;     // maximum supported REL version, u8 Major and u8 Minor

        entryInfo patchInfo;     // bitArray where each bit represents a patch/modification to be applied for this playthrough
        entryInfo eventFlagsInfo;      // eventFlags that need to be set for this seed
        entryInfo regionFlagsInfo;     // regionFlags that need to be set, alternating

        entryInfo dzxCheckInfo;
        entryInfo relCheckInfo;
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
        uint16_t stageIDX;
        uint8_t data[0x20];
    } __attribute__( ( __packed__ ) );

    struct shopCheck
    {
        uint16_t stageIDX;
        uint16_t hash;
        uint16_t actor;      // New actor for the dzx
        uint8_t target;      // target item id
        uint8_t replace;     // replacement item id
    } __attribute__( ( __packed__ ) );

    struct RELCheck
    {
        uint32_t stageIDX;
        uint32_t moduleID;
        uint32_t offset;
        uint32_t data[2];
    } __attribute__( ( __packed__ ) );
}     // namespace mod::rando
#endif