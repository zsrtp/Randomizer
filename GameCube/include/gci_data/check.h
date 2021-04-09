/**	@file check.h
 *  @brief Contains structs for different types of checks.
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#pragma once
#include <cstdint>

namespace mod::gci_data
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
        uint32_t fileSize;       //< Total gci data size including this header
        uint64_t seed;           //< Current seed
        uint16_t minVersion;     //< minimal required REL version, u8 Major and u8 Minor
        uint16_t maxVersion;     //< maximum supported REL version, u8 Major and u8 Minor

        entryInfo patchInfo;     //< bitArray where each bit represents a patch/modification to be applied for this playthrough
        entryInfo eventFlagsInfo;      //< eventFlags that need to be set for this seed
        entryInfo regionFlagsInfo;     //< regionFlags that need to be set, alternating

        entryInfo dzxCheckInfo;
        entryInfo relCheckInfo;
        entryInfo shopCheckInfo;
    } __attribute__( ( __packed__ ) );

    struct regionFlag
    {
        uint8_t region_id;
        uint8_t bit_id;
    } __attribute__( ( __packed__ ) );

    struct eventFlag
    {
        uint16_t flag;
    } __attribute__( ( __packed__ ) );

    /**
     *  @brief Check that can be replaced at stage+room load by replacing an Actor identified by hash
     */
    struct dzxCheck
    {
        uint16_t hash;
        uint16_t stageID;
        uint8_t data[0x20];
    } __attribute__( ( __packed__ ) );

    struct shopCheck
    {
        uint16_t stageID;
        uint16_t hash;
        uint16_t actor;      //< New actor for the dzx
        uint8_t target;      //< target item id
        uint8_t replace;     //< replacement item id
    } __attribute__( ( __packed__ ) );

    struct RELCheck
    {
        uint32_t moduleID;
        uint32_t offset;
        uint32_t replacement;
    } __attribute__( ( __packed__ ) );
}     // namespace mod::gci_data