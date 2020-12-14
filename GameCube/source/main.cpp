#include "main.h"

#include <display/console.h>
#include <patch.h>
#include <tp/JFWSystem.h>
#include <tp/d_stage.h>
#include <tp/f_ap_game.h>
#include <tp/m_do_controller_pad.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace mod
{
    void main()
    {     // Hook function that runs each frame
        fapGm_Execute_return = libtp::patch::hookFunction( libtp::tp::f_ap_game::fapGm_Execute, run );

        actorCommonLayerInit_return = libtp::patch::hookFunction(
            libtp::tp::d_stage::actorCommonLayerInit,
            []( void* mStatus_roomControl, libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 ) {
                // pass relevant information to our custom event
                onActorInit( chunkTypeInfo );
                // Call original function
                return actorCommonLayerInit_return( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
            } );

        actorInit_return = libtp::patch::hookFunction(
            libtp::tp::d_stage::actorInit,
            []( void* mStatus_roomControl, libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 ) {
                // pass relevant information to our custom event
                onActorInit( chunkTypeInfo );
                // Call original function
                return actorInit_return( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
            } );

        actorInit_always_return = libtp::patch::hookFunction(
            libtp::tp::d_stage::actorInit_always,
            []( void* mStatus_roomControl, libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 ) {
                // pass relevant information to our custom event
                onActorInit( chunkTypeInfo );
                // Call original function
                return actorInit_always_return( mStatus_roomControl, chunkTypeInfo, unk3, unk4 );
            } );

        libtp::tp::jfw_system::systemConsole->consoleEnabled = true;
        // libtp::tp::jfw_system::systemConsole->consoleLine[0].showLine = true;

        libtp::display::setConsole( true, 25 );
    }

    void onActorInit( libtp::tp::d_stage::dzxChunkTypeInfo* chunkTypeInfo )
    {
        // Display info and create unique hash for this check
        delayCounter = 0;

        if ( hashCounter == 0 )
        {
            // First call of this function for this load so clear the console output
            libtp::display::clearConsole( 0, 0 );
        }

        uint8_t numACTR = chunkTypeInfo->numChunks;
        libtp::tp::d_stage::Actr* actor = reinterpret_cast<libtp::tp::d_stage::Actr*>( chunkTypeInfo->chunkDataPtr );

        for ( uint8_t i = 0; i < numACTR; i++ )
        {
            if ( strncmp( actor[i].objectName, "tboxXX", 4 ) == 0 || strncmp( actor[i].objectName, "htPiece", 7 ) == 0 ||
                 strncmp( actor[i].objectName, "htCase", 6 ) == 0 )
            {
                // This actor is relevant to rando and thus should be hashed
                uint16_t hash = fletcher16( reinterpret_cast<uint8_t*>( &actor[i] ), 0x20 );
                uint8_t item = ( actor[i].rot[2] >> 8 );

                sprintf( libtp::tp::jfw_system::systemConsole->consoleLine[hashCounter].line,
                         "%04x: %02x %02x %04.4f %04.4f %04.4f",
                         reinterpret_cast<uint32_t>( &actor[i] ),
                         hash,
                         item,
                         actor[i].pos[0],
                         actor[i].pos[1],
                         actor[i].pos[2] );

                hashCounter++;
            }
        }
    }

    void run()
    {
        // Do stuff
        uint32_t buttonCombo = libtp::tp::m_do_controller_pad::Button_Z | libtp::tp::m_do_controller_pad::Button_R;

        if ( lastInput != libtp::tp::m_do_controller_pad::cpadInfo.buttonInput &&
             buttonCombo == ( libtp::tp::m_do_controller_pad::cpadInfo.buttonInput & buttonCombo ) )
        {
            state = !state;
            libtp::display::setConsole( state, 0 );
        }

        if ( hashCounter > 0 && delayCounter == 0xFF )
        {
            // Assume the load has ended and reset
            hashCounter = 0;
        }

        delayCounter++;

        lastInput = libtp::tp::m_do_controller_pad::cpadInfo.buttonInput;
        // Call original game function
        return fapGm_Execute_return();
    }

    uint16_t fletcher16( uint8_t* data, int32_t count )
    {
        uint16_t sum1 = 0;
        uint16_t sum2 = 0;

        for ( int32_t index = 0; index < count; ++index )
        {
            sum1 = ( sum1 + data[index] ) % 0xFF;
            sum2 = ( sum2 + sum1 ) % 0xFF;
        }

        return ( sum2 << 8 ) | sum1;
    }
}     // namespace mod