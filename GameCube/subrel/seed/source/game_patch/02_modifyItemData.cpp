#include <cstdint>

#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"

namespace mod::game_patch
{
    void _02_modifyFoolishShopModel( uint16_t shopID )
    {
        using namespace libtp::tp::d_a_shop_item_static;

        // Set the shop model of the Foolish Item ID to the model of a random important item.
        constexpr uint32_t modelListSize = TOTAL_FOOLISH_ITEM_MODELS;
        uint32_t randomIndex = ulRand( &randNext, modelListSize );
        uint32_t shopModelItemID = _04_verifyProgressiveItem( randomizer, foolishModelItemList[randomIndex] );

        libtp::tp::d_item_data::ItemResource* fieldItemResPtr = &libtp::tp::d_item_data::item_resource[shopModelItemID];
        ShopItemData* shopItemDataPtr = &shopItemData[shopID];

        shopItemDataPtr->arcName = fieldItemResPtr->arcName;
        shopItemDataPtr->modelResIdx = fieldItemResPtr->modelResIdx;
        shopItemDataPtr->wBckResIdx = fieldItemResPtr->bckResIdx;
        shopItemDataPtr->wBrkResIdx = fieldItemResPtr->brkResIdx;
        shopItemDataPtr->wBtpResIdx = fieldItemResPtr->btpResIdx;
        shopItemDataPtr->tevFrm = fieldItemResPtr->tevFrm;

        // Clear the cache for the modified values
        libtp::gc_wii::os_cache::DCFlushRange( reinterpret_cast<void*>( shopItemDataPtr ),
                                               sizeof( libtp::tp::d_a_shop_item_static::ShopItemData ) );
    }
}     // namespace mod::game_patch