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
    void setHUDCosmetics()
    {
        using namespace libtp::tp::d_meter2_info;

        // Patch the A Button Color
        if ( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow != nullptr )
        {
            ( *reinterpret_cast<uint32_t*>(
                reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow ) + 0x248 ) ) =
                0x0000FFFF;
            ( *reinterpret_cast<uint32_t*>(
                reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow ) + 0x24C ) ) =
                0x0000FFFF;
            ( *reinterpret_cast<uint32_t*>(
                reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow ) + 0x250 ) ) =
                0x0000FFFF;
            ( *reinterpret_cast<uint32_t*>(
                reinterpret_cast<uint32_t>( g_meter2_info.mMeterClass->mpMeterDraw->mpButtonA->mWindow ) + 0x254 ) ) =
                0x0000FFFF;
        }
    }
}     // namespace mod::user_patch