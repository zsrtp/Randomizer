/** @file 03_customCosmetics.cpp
 * @author Lunar Soap
 * @brief Contains function definitions for patching cosmetics.
 *
 * @bug No known bugs
 */
#include "user_patch/03_customCosmetics.h"

#include "events.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_meter2_info.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    // Color definitions for different icons.
    uint32_t heartColorRGBA[] = {
        0xFFFFFFFF,     // Default
        0xFFA0FFFF,     // Pink
        0xFFFF40FF,     // Orange
        0x00E87BFF,     // Green
        0x00F3FFFF,     // Teal
        0x00AAFFFF,     // Blue
        0x6078FFFF,     // Purple
        0x000000FF      // Black
    };

    uint32_t aButtonColorRGBA[] = {
        0xFFFFFFFF,     // Default
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
        0xFFFFFFFF,     // Default
        0xFFFF40FF,     // Orange
        0xFFA0FFFF,     // Pink
        0x00E87BFF,     // Green
        0x00AAFFFF,     // Blue
        0x6078FFFF,     // Purple
        0x000000FF,     // Black
        0x00F3FFFF,     // Teal
    };

    uint32_t xyButtonColorRGBA[] = {
        0xFFFFFFFF,     // Default
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
        0xFFFFFFFF,     // Default
        0xFF0000FF,     // Red
        0xFF8200FF,     // Orange
        0xF7DF00FF,     // Yellow
        0x70FF00FF,     // Lime Green
        0x00BD11FF,     // Dark Green
        0x880088FF,     // Purple
        0x000000FF,     // Black
        0x00FFFFFF      // Light Blue
    };

    uint8_t lanternColors[][6] = {
        { 0x50, 0x28, 0x14, 0x28, 0x1E, 0x0A },     // Default
        { 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00 },     // Red
        { 0xF6, 0x88, 0x21, 0xF6, 0x88, 0x21 },     // Orange
        { 0xF6, 0xF3, 0x21, 0xF6, 0xF3, 0x21 },     // Yellow
        { 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00 },     // Green
        { 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF },     // Blue
        { 0x80, 0x00, 0xFF, 0x80, 0x00, 0xFF },     // Purple
        { 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0 },     // White
        { 0x30, 0xD0, 0xD0, 0x30, 0xD0, 0xD0 },     // Cyan
    };

    void setHUDCosmetics( rando::Randomizer* randomizer )
    {
        using namespace libtp::tp::d_meter2_info;
        uint8_t heartColorIndex = randomizer->m_SeedInfo->header.heartColor;
        uint8_t aButtonColorIndex = randomizer->m_SeedInfo->header.aButtonColor;
        uint8_t bButtonColorIndex = randomizer->m_SeedInfo->header.bButtonColor;
        uint8_t xButtonColorIndex = randomizer->m_SeedInfo->header.xButtonColor;
        uint8_t yButtonColorIndex = randomizer->m_SeedInfo->header.yButtonColor;
        uint8_t zButtonColorIndex = randomizer->m_SeedInfo->header.zButtonColor;
        uint32_t heartListSize = sizeof( heartColorRGBA ) / sizeof( heartColorRGBA[0] );

        for ( uint16_t i = 0x248; i <= 0x254; i += 0x4 )
        {
            // Patch the A Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow ) + i ) ) =
                    aButtonColorRGBA[aButtonColorIndex];
            }

            // Patch the B Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonB->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonB->mWindow ) + i ) ) =
                    bButtonColorRGBA[bButtonColorIndex];
            }

            // Patch the X Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[0]->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[0]->mWindow ) + i ) ) =
                    xyButtonColorRGBA[xButtonColorIndex];
            }

            // Patch the Y Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[1]->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[1]->mWindow ) + i ) ) =
                    xyButtonColorRGBA[yButtonColorIndex];
            }

            // Patch the Z Button Color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[2]->mWindow != nullptr )
            {
                ( *reinterpret_cast<uint32_t*>(
                    reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonXY[2]->mWindow ) + i ) ) =
                    zButtonColorRGBA[zButtonColorIndex];
            }
        }

        // get random color for big heart
        uint32_t randomHeartIndex = mod::ulRand( heartListSize );
        for ( uint16_t i = 0x3F8, rupee = 0x1038; i <= 0x404; i += 0x4, rupee += 0x4 )
        {
            // Patch the Big Heart color
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow != nullptr )
            {
                if ( heartColorIndex == 8 )
                {
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) + i ) ) =
                        heartColorRGBA[randomHeartIndex];
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                        ( i + ( 0x1B0 ) ) ) ) = heartColorRGBA[randomHeartIndex];
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                        ( i + ( 0x1B0 * 2 ) ) ) ) = heartColorRGBA[randomHeartIndex];
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                        ( i + ( 0x1B0 * 3 ) ) ) ) = heartColorRGBA[randomHeartIndex];
                }
                else
                {
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) + i ) ) =
                        heartColorRGBA[heartColorIndex];
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                        ( i + ( 0x1B0 ) ) ) ) = heartColorRGBA[heartColorIndex];
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                        ( i + ( 0x1B0 * 2 ) ) ) ) = heartColorRGBA[heartColorIndex];
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) +
                        ( i + ( 0x1B0 * 3 ) ) ) ) = heartColorRGBA[heartColorIndex];
                }

                if ( events::haveItem( libtp::data::items::Giant_Wallet ) )
                {
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) + rupee ) ) =
                        0xaf00ffff;
                }
                else if ( events::haveItem( libtp::data::items::Big_Wallet ) )
                {
                    ( *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpBigHeart->mWindow ) + rupee ) ) =
                        0xff0000ff;
                }
            }
        }

        // Patch Heart Color
        for ( uint8_t i = 0, heartIndex = 0; i < 20; i++, heartIndex++ )
        {
            if ( g_meter2_info.mMeterClass->mpMeterDraw->mpLifeTexture[i][1] != nullptr )
            {
                if ( heartColorIndex == 8 )
                {
                    for ( uint16_t j = 0x138; j <= 0x144; j += 0x4 )
                    {
                        ( *reinterpret_cast<uint32_t*>(
                            reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpLifeTexture[i][1]->mWindow ) +
                            j ) ) = heartColorRGBA[heartIndex];
                    }
                    if ( heartIndex == heartListSize )
                    {
                        heartIndex = 0;
                    }
                }
                else
                {
                    for ( uint16_t j = 0x138; j <= 0x144; j += 0x4 )
                    {
                        ( *reinterpret_cast<uint32_t*>(
                            reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpLifeTexture[i][1]->mWindow ) +
                            j ) ) = heartColorRGBA[heartColorIndex];
                    }
                }
            }
        }
    }

    void setLanternColor( rando::Randomizer* randomizer )
    {
        using namespace libtp::tp::d_a_alink;
        // set lantern variables
        lanternVars.innerSphereR = lanternColors[randomizer->m_SeedInfo->header.lanternColor][0];
        lanternVars.innerSphereG = lanternColors[randomizer->m_SeedInfo->header.lanternColor][1];
        lanternVars.innerSphereB = lanternColors[randomizer->m_SeedInfo->header.lanternColor][2];
        lanternVars.outerSphereR = lanternColors[randomizer->m_SeedInfo->header.lanternColor][3];
        lanternVars.outerSphereG = lanternColors[randomizer->m_SeedInfo->header.lanternColor][4];
        lanternVars.outerSphereB = lanternColors[randomizer->m_SeedInfo->header.lanternColor][5];
    }
}     // namespace mod::user_patch