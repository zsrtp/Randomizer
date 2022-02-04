/** @file game_patch.h
 * @author AECX
 * @author Lunar Soap
 * @brief Game patches are always applied & mostly used to fix a bug/softlog.
 *
 * @bug No known bugs
 */
#ifndef RANDO_GAME_PATCH_H
#define RANDO_GAME_PATCH_H

#include <cstdint>

#include "rando/randomizer.h"
#include "tp/control.h"

namespace mod::game_patch
{
    void _00_poe( void );
    int32_t _01_getLayerNo( const char* stageName, int32_t roomId, int32_t layerOverride );
    void _02_modifyItemData();
    void _03_increaseClimbSpeed();
    uint32_t _04_verifyProgressiveItem( rando::Randomizer* randomizer, uint32_t itemID );
    void _05_setCustomItemMessage( libtp::tp::control::TControl* control,
                                   const void* TProcessor,
                                   uint16_t unk3,
                                   uint16_t msgId );
    uint32_t _05_getCustomMsgColor( uint8_t colorId );
    void _06_patchMDHWolfReturn();
    void _06_patchSaveBitFlags();
    void _07_checkDesertCrystal();
}     // namespace mod::game_patch
#endif