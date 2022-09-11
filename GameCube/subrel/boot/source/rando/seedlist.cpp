/**	@file seedselector.cpp
 *  @brief Selection tool to select the desired data-GCI
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cinttypes>

#ifdef DVD
#include "gc_wii/dvd.h"
#else
#include "gc_wii/card.h"
#endif

#include "rando/seedlist.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "tools.h"
#include "memory.h"
#include "cxx.h"

namespace mod::rando
{
    SeedList::SeedList()
    {
        using namespace libtp;

        // Store header data so we don't have to open the files again later
        // Allocate the memory to the back of the heap to avoid fragmentation
        // Align to uint32_t, as it is the largest variable type used in the Header struct
        Header* headerBuffer = new ( -sizeof( uint32_t ) ) Header[SEED_MAX_ENTRIES];

        // Allocate the memory to the back of the heap to avoid fragmentation
        // Align to char, as strings don't have specific alignment requirements
        // The filenames are not NULL terminated
        char* fileNameArray = new ( -sizeof( char ) ) char[SEED_MAX_ENTRIES * CARD_FILENAME_MAX];

        // Get a list of all seeds available
#ifdef DVD
        GetSeedFiles( "/mod/seed", headerBuffer, fileNameArray );
#else
        // The memory card should already be mounted
        GetSeedFiles( CARD_SLOT_A, headerBuffer, fileNameArray );
#endif
        uint32_t numSeeds = m_numSeeds;
        if ( numSeeds > 0 )
        {
            // Align to uint32_t, as it is the largest variable type used in the Header struct
            m_seedInfo = new ( sizeof( uint32_t ) ) SeedInfo[numSeeds];

            for ( uint32_t i = 0; i < numSeeds; i++ )
            {
                SeedInfo* currentSeedInfo = &m_seedInfo[i];

                // Copy the main header data
                memcpy( &currentSeedInfo->header, &headerBuffer[i], sizeof( Header ) );

                // Copy the file index
                currentSeedInfo->fileIndex = i;

                // Copy the filename and make sure it is NULL terminated
                char* fileName = currentSeedInfo->fileName;
                strncpy( fileName, &fileNameArray[i * CARD_FILENAME_MAX], CARD_FILENAME_MAX );
                fileName[CARD_FILENAME_MAX] = '\0';
            }
        }

        getConsole() << static_cast<int32_t>( numSeeds ) << " seed(s) available.\n";

        // Cleanup
        delete[] headerBuffer;
        delete[] fileNameArray;
    }

    SeedList::~SeedList()
    {
        delete[] m_seedInfo;
    }

#ifdef DVD
    void SeedList::GetSeedFiles( const char* seedDirectory, Header* headerBuffer, char* namesOut )
    {
        using namespace libtp::gc_wii::dvd;

        DVDDir dir;
        DVDDirEntry dirEnt;
        char filePath[96];
#else
    // This function assumes that the memory card is already mounted
    void SeedList::GetSeedFiles( int32_t chan, Header* headerBuffer, char* namesOut )
    {
        using namespace libtp::gc_wii::card;

        CARDStat stat;
        int32_t result;
#endif
        Header header;
        const char* fileName;

        // Starting index
        uint32_t index = 0;

#ifdef DVD
        // Try to open the directory that has the seeds
        if ( !DVDOpenDir( seedDirectory, &dir ) )
        {
            // Make sure m_numSeeds is set to 0
            m_numSeeds = 0;
            return;
        }

        // Loop through all of the files in the directory
        // DVDReadDir will return false once all files have been looped through
        while ( DVDReadDir( &dir, &dirEnt ) )
        {
            // Currently only supporting a single folder
            if ( dirEnt.bIsDir )
            {
                // Entry is a directory
                continue;
            }

            // Try to open the file and get the header data
            // dirEnt does not contain the full file path
            fileName = dirEnt.fileName;
            snprintf( filePath, sizeof( filePath ), "/mod/seed/%s", fileName );

            // Try to open the file and get the header data
            if ( DVD_STATE_END == libtp::tools::ReadFile( filePath, sizeof( header ), 0, &header ) )
            {
#else
        // Loop through all possible files on the memory card
        for ( int32_t i = 0; i < SEED_MAX_ENTRIES; i++ )
        {
            // Try to get the status of an arbitrary file slot
            result = CARDGetStatus( chan, i, &stat );
            if ( result != CARD_RESULT_READY )
            {
                // No file is in the current slot
                continue;
            }

            // If the file is for the vanilla game save or the rando's REL save, then skip it
            fileName = stat.fileName;
            if ( ( strcmp( fileName, "gczelda2" ) == 0 ) || ( strcmp( fileName, "Custom REL File" ) == 0 ) )
            {
                continue;
            }

            // Try to open the file and get the header data
            if ( CARD_RESULT_READY == libtp::tools::ReadGCIMounted( chan, fileName, sizeof( header ), 0, &header, true ) )
            {
#endif
                // Make sure the seed version is supported
                const uint16_t versionMajor = header.versionMajor;

                if ( CHECK_MIN_SUPPORTED_SEED_DATA_VER_MAJOR( versionMajor ) &&
                     CHECK_MIN_SUPPORTED_SEED_DATA_VER_MINOR( header.versionMinor ) &&
                     CHECK_MAX_FULLY_SUPPORTED_SEED_DATA_VER_MAJOR( versionMajor ) )
                {
                    // Copy the filename to the buffer
                    // The filenames are not NULL terminated
                    strncpy( &namesOut[index * CARD_FILENAME_MAX], fileName, CARD_FILENAME_MAX );

                    // Copy the header to the main buffer
                    memcpy( &headerBuffer[index], &header, sizeof( Header ) );

                    // Done with the current file, so increment the index
                    index++;
                }
            }
        }

#ifdef DVD
        // Close the directory that has the seeds
        DVDCloseDir( &dir );
#endif
        // Update m_numSeeds
        m_numSeeds = static_cast<uint8_t>( index );
    }
}     // namespace mod::rando