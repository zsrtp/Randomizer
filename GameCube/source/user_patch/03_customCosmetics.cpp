/** @file 03_customCosmetics.cpp
 * @author Lunar Soap
 * @brief Contains function definitions for patching cosmetics.
 *
 * @bug No known bugs
 */
#include "user_patch/03_customCosmetics.h"

#include <cinttypes>

#include "tp/d_meter2_info.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    // Color definitions for different icons.
    uint32_t heartColorRGBA[] = {
        0x00F3FFFF,     // Teal
        0xFFA0FFFF,     // Pink
        0xFFFF40FF,     // Orange
        0x00AAFFFF,     // Blue
        0x00E87BFF,     // Green
        0x6078FFFF,     // Purple
        0x000000FF      // Black
    };

    uint32_t aButtonColorRGBA[] = {
        0xFF0000FF,     // Red
        0xFF5000FF,     // Orange
        0xFFAF00FF,     // Yellow
        0x0080FFFF,     // Dark Green
        0x0000FFFF,     // Blue
        0x8000FFFF,     // Purple
        0x000000FF,     // Black
        0x5555FFFF,     // Grey
        0xFF20FFFF,     // Pink
    };

    uint32_t bButtonColorRGBA[] = {
        0xFFFF40FF,     // Orange
        0xFFA0FFFF,     // Pink
        0x00E87BFF,     // Green
        0x00AAFFFF,     // Blue
        0x6078FFFF,     // Purple
        0x000000FF,     // Black
        0x00F3FFFF,     // Teal
    };

    uint32_t xyButtonColorRGBA[] = {
        0xFF0000FF,     // Red
        0xFF8200FF,     // Orange
        0xF7DF00FF,     // Yellow
        0x70FF00FF,     // Lime Green
        0x00BD11FF,     // Dark Green
        0x0000FFFF,     // Blue
        0x880088FF,     // Purple
        0x000000FF,     // Black
        0xFF00AAFF,     // Pink
        0x00FFFFFF      // Cyan
    };

    uint32_t zButtonColorRGBA[] = {
        0xFF0000FF,     // Red
        0xFF8200FF,     // Orange
        0xF7DF00FF,     // Yellow
        0x70FF00FF,     // Lime Green
        0x00BD11FF,     // Dark Green
        0x880088FF,     // Purple
        0x000000FF,     // Black
        0x00FFFFFF      // Light Blue
    };

    void setHUDCosmetics()
    {
        using namespace libtp::tp::d_meter2_info;

        for ( uint16_t i = 0x248; i <= 0x254; i += 0x4 )
        {
            // Patch the A Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow ) + i ) ) =
                    aButtonColorRGBA[4];
            }

            // Patch the B Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonB->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonB->mWindow ) + i ) ) =
                    bButtonColorRGBA[6];
            }

            // Patch the X Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[0]->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[0]->mWindow ) + i ) ) =
                    xyButtonColorRGBA[8];
            }

            // Patch the Y Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[1]->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[1]->mWindow ) + i ) ) =
                    xyButtonColorRGBA[8];
            }

            // Patch the Z Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[2]->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[2]->mWindow ) + i ) ) =
                    zButtonColorRGBA[0];
            }
        }

        for ( uint16_t i = 0x908; i <= 0x914; i += 0x4 )
        {
            // Patch the A Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) + i ) ) =
                    heartColorRGBA[0];
            }
        }

        // Patch Heart Color
        for ( uint8_t i = 0; i < 20; i++ )
        {
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpLifeTexture[i][1] != nullptr )
            {
                for ( uint16_t j = 0x138; j <= 0x144; j += 0x4 )
                {
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpLifeTexture[i][1]->mWindow ) +
                        j ) ) = heartColorRGBA[0];
                }
            }
        }
    }
}     // namespace mod::user_patch