/** @file 03_customCosmetics.cpp
 * @author Lunar Soap
 * @brief Contains function definitions for patching cosmetics.
 *
 * @bug No known bugs
 */
#include "user_patch/03_customCosmetics.h"

#include "events.h"
#include "main.h"
#include "data/items.h"
#include "tp/d_a_alink.h"
#include "tp/d_meter2_info.h"
#include "user_patch/user_patch.h"

namespace mod::user_patch
{
    // Color definitions for different icons.
    const uint32_t heartColorRGBA[] = {
        0xFFFFFFFF,     // Default
        0xFFA0FFFF,     // Pink
        0xFFFF40FF,     // Orange
        0x00E87BFF,     // Green
        0x00F3FFFF,     // Teal
        0x00AAFFFF,     // Blue
        0x6078FFFF,     // Purple
        0x000000FF      // Black
    };

    const uint32_t aButtonColorRGBA[] = {
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

    const uint32_t bButtonColorRGBA[] = {
        0xFFFFFFFF,     // Default
        0xFFFF40FF,     // Orange
        0xFFA0FFFF,     // Pink
        0x00E87BFF,     // Green
        0x00AAFFFF,     // Blue
        0x6078FFFF,     // Purple
        0x000000FF,     // Black
        0x00F3FFFF,     // Teal
    };

    const uint32_t xyButtonColorRGBA[] = {
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

    const uint32_t zButtonColorRGBA[] = {
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

    const uint8_t lanternColors[][6] = {
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
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        if ( !getCurrentSeed( randomizer ) )
        {
            return;
        }

        using namespace libtp::tp::d_meter2_info;
        using namespace libtp::data::items;

        const rando::Header* seedHeader = &randomizer->m_SeedInfo->header;
        const uint8_t heartColorIndex = seedHeader->heartColor;
        const uint8_t aButtonColorIndex = seedHeader->aButtonColor;
        const uint8_t bButtonColorIndex = seedHeader->bButtonColor;
        const uint8_t xButtonColorIndex = seedHeader->xButtonColor;
        const uint8_t yButtonColorIndex = seedHeader->yButtonColor;
        const uint8_t zButtonColorIndex = seedHeader->zButtonColor;

        libtp::tp::d_meter2_draw::dMeter2Draw_c* mpMeterDraw = g_meter2_info.mMeterClass->mpMeterDraw;

        uint32_t mWindowARaw = reinterpret_cast<uint32_t>( mpMeterDraw->mpButtonA->mWindow );
        uint32_t mWindowBRaw = reinterpret_cast<uint32_t>( mpMeterDraw->mpButtonB->mWindow );
        uint32_t mWindowXRaw = reinterpret_cast<uint32_t>( mpMeterDraw->mpButtonXY[0]->mWindow );
        uint32_t mWindowYRaw = reinterpret_cast<uint32_t>( mpMeterDraw->mpButtonXY[1]->mWindow );
        uint32_t mWindowZRaw = reinterpret_cast<uint32_t>( mpMeterDraw->mpButtonXY[2]->mWindow );

        const uint32_t aButtonColor = aButtonColorRGBA[aButtonColorIndex];
        const uint32_t bButtonColor = bButtonColorRGBA[bButtonColorIndex];
        const uint32_t xButtonColor = xyButtonColorRGBA[xButtonColorIndex];
        const uint32_t yButtonColor = xyButtonColorRGBA[yButtonColorIndex];
        const uint32_t zButtonColor = zButtonColorRGBA[zButtonColorIndex];

        for ( uint32_t i = 0x248; i <= 0x254; i += 0x4 )
        {
            // Patch the A Button Color
            if ( mWindowARaw )
            {
                *reinterpret_cast<uint32_t*>( mWindowARaw + i ) = aButtonColor;
            }

            // Patch the B Button Color
            if ( mWindowBRaw )
            {
                *reinterpret_cast<uint32_t*>( mWindowBRaw + i ) = bButtonColor;
            }

            // Patch the X Button Color
            if ( mWindowXRaw )
            {
                *reinterpret_cast<uint32_t*>( mWindowXRaw + i ) = xButtonColor;
            }

            // Patch the Y Button Color
            if ( mWindowYRaw )
            {
                *reinterpret_cast<uint32_t*>( mWindowYRaw + i ) = yButtonColor;
            }

            // Patch the Z Button Color
            if ( mWindowZRaw )
            {
                *reinterpret_cast<uint32_t*>( mWindowZRaw + i ) = zButtonColor;
            }
        }

        // Patch Heart Color
        // uint32_t bigHeartColor = 0;
        uint32_t mWindowRaw;

        const uint32_t* tempHeartColorRGBA = heartColorRGBA;
        constexpr uint32_t heartListSize = sizeof( heartColorRGBA ) / sizeof( heartColorRGBA[0] );

        // Failsafe: Make sure heartColorIndex is valid
        uint32_t heartColor;
        if ( heartColorIndex < heartListSize )
        {
            heartColor = tempHeartColorRGBA[heartColorIndex];
        }
        else
        {
            heartColor = 0;
        }

        /*
        const uint32_t maxHeart =
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.maxHealth / 5;
        */

        const bool heartColorIsRainbow = heartColorIndex == 8;
        for ( uint32_t i = 0, heartIndex = 0; i < 20; i++, heartIndex++ )
        {
            libtp::tp::d_pane_class::CPaneMgr* currentLifeTexture = mpMeterDraw->mpLifeTexture[i][1];
            if ( !currentLifeTexture )
            {
                continue;
            }

            mWindowRaw = reinterpret_cast<uint32_t>( currentLifeTexture->mWindow );
            if ( !mWindowRaw )
            {
                continue;
            }

            if ( heartColorIsRainbow )
            {
                const uint32_t currentHeartIndexColor = tempHeartColorRGBA[heartIndex];
                for ( uint32_t j = 0x138; j <= 0x144; j += 0x4 )
                {
                    *reinterpret_cast<uint32_t*>( mWindowRaw + j ) = currentHeartIndexColor;
                }

                /*
                if ( i == maxHeart )
                {
                    // Failsafe: Make sure heartIndex is at least 1 for accessing tempHeartColorRGBA
                    if ( heartIndex < 1 )
                    {
                        heartIndex = 1;
                    }

                    bigHeartColor = tempHeartColorRGBA[( heartIndex - 1 )];
                }
                */

                if ( heartIndex >= heartListSize )
                {
                    heartIndex = 0;
                }
            }
            else
            {
                for ( uint32_t j = 0x138; j <= 0x144; j += 0x4 )
                {
                    *reinterpret_cast<uint32_t*>( mWindowRaw + j ) = heartColor;
                }
            }
        }

        // Patch the Big Heart and Rupee colors
        uint32_t currentWallet;
        uint32_t rupeeColor;

        if ( events::haveItem( Item::Giant_Wallet ) )
        {
            currentWallet = Wallets::GIANT_WALLET;
            rupeeColor = 0xaf00ffff;
        }
        else if ( events::haveItem( Item::Big_Wallet ) )
        {
            currentWallet = Wallets::BIG_WALLET;
            rupeeColor = 0xff0000ff;
        }
        else
        {
            currentWallet = Wallets::WALLET;
            rupeeColor = 0;
        }

        uint32_t tempBigHeartColor;
        if ( heartColorIsRainbow )
        {
            // tempBigHeartColor = bigHeartColor;
            tempBigHeartColor = tempHeartColorRGBA[ulRand( &nextVal, heartListSize )];
        }
        else
        {
            tempBigHeartColor = heartColor;
        }

        mWindowRaw = reinterpret_cast<uint32_t>( mpMeterDraw->mpBigHeart->mWindow );
        if ( mWindowRaw )
        {
            for ( uint32_t i = 0x3F8, rupee = 0x1038; i <= 0x404; i += 0x4, rupee += 0x4 )
            {
                // Patch the Big Heart color
                *reinterpret_cast<uint32_t*>( mWindowRaw + i ) = tempBigHeartColor;
                *reinterpret_cast<uint32_t*>( mWindowRaw + ( i + ( 0x1B0 ) ) ) = tempBigHeartColor;
                *reinterpret_cast<uint32_t*>( mWindowRaw + ( i + ( 0x1B0 * 2 ) ) ) = tempBigHeartColor;
                *reinterpret_cast<uint32_t*>( mWindowRaw + ( i + ( 0x1B0 * 3 ) ) ) = tempBigHeartColor;

                // Patch the Rupee color
                if ( currentWallet != Wallets::WALLET )
                {
                    *reinterpret_cast<uint32_t*>( mWindowRaw + rupee ) = rupeeColor;
                }
            }
        }
    }

    void setLanternColor( rando::Randomizer* randomizer )
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        if ( !getCurrentSeed( randomizer ) )
        {
            return;
        }

        using namespace libtp::tp::d_a_alink;

        // Set lantern variables
        daAlinkHIO_kandelaar_c0* tempLanternVars = &lanternVars;
        const uint8_t* lanternColor = &lanternColors[randomizer->m_SeedInfo->header.lanternColor][0];

        tempLanternVars->innerSphereR = lanternColor[0];
        tempLanternVars->innerSphereG = lanternColor[1];
        tempLanternVars->innerSphereB = lanternColor[2];
        tempLanternVars->outerSphereR = lanternColor[3];
        tempLanternVars->outerSphereG = lanternColor[4];
        tempLanternVars->outerSphereB = lanternColor[5];
    }
}     // namespace mod::user_patch