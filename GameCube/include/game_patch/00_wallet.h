/** @file 00_wallet.h
 * @author AECX
 * @brief Patches Links wallet to be bigger.
 *
 * @bug No known bugs
 */
#ifndef RANDO_WALLET_PATCH_H
#define RANDO_WALLET_PATCH_H

namespace mod::game_patch
{
    /**
     *  @brief Sets new limits to your wallet
     *
     *  Patched: 1000, 5000, 9999
     *  Unpatched: 300, 600, 1000
     */
    void patchWallet( bool set );
}     // namespace mod::game_patch
#endif