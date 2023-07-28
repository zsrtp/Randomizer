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

    void setHUDCosmetics(rando::Randomizer* randomizer)
    {
        using namespace libtp::tp::d_meter2_info;
        using namespace libtp::data::items;
        using namespace libtp::tp::d_a_alink;

        // Make sure the randomizer is loaded/enabled and a seed is loaded
        if (!getCurrentSeed(randomizer))
        {
            return;
        }

        libtp::tp::d_meter2_draw::dMeter2Draw_c* mpMeterDraw = g_meter2_info.mMeterClass->mpMeterDraw;
        rando::RawRGBTable* rawRGBListPtr = randomizer->m_Seed->m_RawRGBTable;

        uint32_t mWindowARaw = reinterpret_cast<uint32_t>(mpMeterDraw->mpButtonA->mWindow);
        uint32_t mWindowBRaw = reinterpret_cast<uint32_t>(mpMeterDraw->mpButtonB->mWindow);
        uint32_t mWindowXRaw = reinterpret_cast<uint32_t>(mpMeterDraw->mpButtonXY[0]->mWindow);
        uint32_t mWindowYRaw = reinterpret_cast<uint32_t>(mpMeterDraw->mpButtonXY[1]->mWindow);
        uint32_t mWindowZRaw = reinterpret_cast<uint32_t>(mpMeterDraw->mpButtonXY[2]->mWindow);

        const uint32_t aButtonColor = rawRGBListPtr->aButtonColor;
        const uint32_t bButtonColor = rawRGBListPtr->bButtonColor;
        const uint32_t xButtonColor = rawRGBListPtr->xButtonColor;
        const uint32_t yButtonColor = rawRGBListPtr->yButtonColor;
        const uint32_t zButtonColor = rawRGBListPtr->zButtonColor;
        const uint32_t heartColorRGBA = rawRGBListPtr->heartColor;

        uint8_t* lanternColor = reinterpret_cast<uint8_t*>(&rawRGBListPtr->lanternColor);

        for (uint32_t i = 0x248; i <= 0x254; i += 0x4)
        {
            // Patch the A Button Color
            if (mWindowARaw)
            {
                *reinterpret_cast<uint32_t*>(mWindowARaw + i) = aButtonColor | 0xFF;
            }

            // Patch the B Button Color
            if (mWindowBRaw)
            {
                *reinterpret_cast<uint32_t*>(mWindowBRaw + i) = bButtonColor;
            }

            // Patch the X Button Color
            if (mWindowXRaw)
            {
                *reinterpret_cast<uint32_t*>(mWindowXRaw + i) = xButtonColor;
            }

            // Patch the Y Button Color
            if (mWindowYRaw)
            {
                *reinterpret_cast<uint32_t*>(mWindowYRaw + i) = yButtonColor;
            }

            // Patch the Z Button Color
            if (mWindowZRaw)
            {
                *reinterpret_cast<uint32_t*>(mWindowZRaw + i) = zButtonColor;
            }
        }

        // Patch Heart Color
        uint32_t mWindowRaw;

        for (uint32_t i = 0; i < 20; i++)
        {
            libtp::tp::d_pane_class::CPaneMgr* currentLifeTexture = mpMeterDraw->mpLifeTexture[i][1];
            if (!currentLifeTexture)
            {
                continue;
            }

            mWindowRaw = reinterpret_cast<uint32_t>(currentLifeTexture->mWindow);
            if (!mWindowRaw)
            {
                continue;
            }

            for (uint32_t j = 0x138; j <= 0x144; j += 0x4)
            {
                *reinterpret_cast<uint32_t*>(mWindowRaw + j) = heartColorRGBA;
            }
        }

        // Patch the Big Heart and Rupee colors
        uint32_t currentWallet;
        uint32_t rupeeColor;

        if (events::haveItem(Item::Giant_Wallet))
        {
            currentWallet = Wallets::GIANT_WALLET;
            rupeeColor = 0xaf00ffff;
        }
        else if (events::haveItem(Item::Big_Wallet))
        {
            currentWallet = Wallets::BIG_WALLET;
            rupeeColor = 0xff0000ff;
        }
        else
        {
            currentWallet = Wallets::WALLET;
            rupeeColor = 0;
        }

        mWindowRaw = reinterpret_cast<uint32_t>(mpMeterDraw->mpBigHeart->mWindow);
        if (mWindowRaw)
        {
            for (uint32_t i = 0x3F8, rupee = 0x1038; i <= 0x404; i += 0x4, rupee += 0x4)
            {
                // Patch the Big Heart color
                *reinterpret_cast<uint32_t*>(mWindowRaw + i) = heartColorRGBA;
                *reinterpret_cast<uint32_t*>(mWindowRaw + (i + (0x1B0))) = heartColorRGBA;
                *reinterpret_cast<uint32_t*>(mWindowRaw + (i + (0x1B0 * 2))) = heartColorRGBA;
                *reinterpret_cast<uint32_t*>(mWindowRaw + (i + (0x1B0 * 3))) = heartColorRGBA;

                // Patch the Rupee color
                if (currentWallet != Wallets::WALLET)
                {
                    *reinterpret_cast<uint32_t*>(mWindowRaw + rupee) = rupeeColor;
                }
            }
        }

        if (*reinterpret_cast<uint32_t*>(lanternColor) != 0x502814ff) // Don't set the value if it is already vanilla
        {
            // Set lantern variables
            daAlinkHIO_kandelaar_c0* tempLanternVars = &lanternVars;
            daAlinkHIO_huLight_c0* tempHuLightVars = &huLightVars;

            tempLanternVars->innerSphereR = lanternColor[0];
            tempLanternVars->innerSphereG = lanternColor[1];
            tempLanternVars->innerSphereB = lanternColor[2];
            tempLanternVars->outerSphereR = lanternColor[0];
            tempLanternVars->outerSphereG = lanternColor[1];
            tempLanternVars->outerSphereB = lanternColor[2];
            tempHuLightVars->lanternAmbienceR = lanternColor[0];
            tempHuLightVars->lanternAmbienceG = lanternColor[1];
            tempHuLightVars->lanternAmbienceB = lanternColor[2];
        }
    }
} // namespace mod::user_patch