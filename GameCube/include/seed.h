/**	@file seed.h
 *  @brief Seed class to access seed-data
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#pragma once
#include <cstdint>

#include "gci_data/check.h"
#include "tools.h"

#define SEED_STATUS_INITIALIZED 1
#define SEED_STATUS_PATCHED 2
#define SEED_STATUS_EVENTFLG 4
#define SEED_STATUS_REGIONFLG 8
#define SEED_STATUS_DZXLOAD 16
#define SEED_STATUS_RELLOAD 32
#define SEED_STATUS_SHOPLOAD 64

namespace mod::rando
{
    class Seed
    {
        // Member vars
       public:
        int32_t m_CARDResult;     //< Most recent status from the CARDApi functions
        uint32_t m_SeedStatus = 0;

        uint32_t m_PatchesApplied = 0;
        uint32_t m_EventFlagsModified = 0;
        uint32_t m_AreaFlagsModified = 0;

        gci_data::Header* m_Header = nullptr;

        gci_data::dzxCheck* m_DZXChecks = nullptr;       //< DZX replacement checks for current stage
        gci_data::RELCheck* m_RELChecks = nullptr;       //< REL Modifications for current stage
        gci_data::shopCheck* m_ShopChecks = nullptr;     //< Shop replacements for current stage

        // Member functions
       public:
        /**
         *  @brief Class to dynamically load required data from a given seed
         *
         *  @param fileName gci filename (rando-data0, rando-data1, ...)
         */
        Seed( int32_t chan, const char* fileName );
        ~Seed();

        /**
         *  @brief Applies patches, event & region flags according to this seed to the current savefile
         */
        void InitSeed( void );

        /**
         *  @brief Load check data for a given stage
         */
        void LoadChecks( const char* stage );

       private:
        const char* m_FileName = nullptr;
        int32_t m_CardSlot = 0;     //< Selected Card slot
        void ClearChecks( void );

        void applyPatches( void );
        void applyEventFlags( void );
        void applyRegionFlags( void );

        void LoadDZX( void );
        void LoadREL( void );
        void LoadSHOP( void );
    };
}     // namespace mod::rando