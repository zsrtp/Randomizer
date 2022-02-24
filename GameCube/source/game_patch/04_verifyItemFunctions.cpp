#include <cinttypes>
#include <cstring>

#include "data/items.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "tp/d_a_alink.h"
#include "tp/d_item.h"

namespace mod::game_patch
{
    auto getProgressiveSword = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveSwordsList[] = { Wooden_Sword, Ordon_Sword, Master_Sword };

        const uint32_t listLength = sizeof( progressiveSwordsList ) / sizeof( progressiveSwordsList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveSwordsList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Master_Sword_Light );
    };

    auto getProgressiveBow = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveBowsList[] = { Heros_Bow, Big_Quiver };

        const uint32_t listLength = sizeof( progressiveBowsList ) / sizeof( progressiveBowsList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveBowsList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Giant_Quiver );
    };

    auto getProgressiveSkill = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveSkillsList[] =
            { Ending_Blow, Shield_Attack, Back_Slice, Helm_Splitter, Mortal_Draw, Jump_Strike };

        const uint32_t listLength = sizeof( progressiveSkillsList ) / sizeof( progressiveSkillsList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveSkillsList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Great_Spin );
    };

    auto getProgressiveSkyBook = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveSkyBooksList[] = { Ancient_Sky_Book_Empty,
                                                    Ancient_Sky_Book_First_Character,
                                                    Ancient_Sky_Book_Second_Character,
                                                    Ancient_Sky_Book_Third_Character,
                                                    Ancient_Sky_Book_Fourth_Character,
                                                    Ancient_Sky_Book_Fifth_Character };

        const uint32_t listLength = sizeof( progressiveSkyBooksList ) / sizeof( progressiveSkyBooksList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveSkyBooksList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Ancient_Sky_Book_Completed );
    };

    auto getProgressiveBombBag = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveBombBagsList[] = { Empty_Bomb_Bag, Goron_Bomb_Bag, Bomb_Bag_Regular_Bombs };

        const uint32_t listLength = sizeof( progressiveBombBagsList ) / sizeof( progressiveBombBagsList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveBombBagsList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Giant_Bomb_Bag );
    };

    auto getProgressiveKeyShard = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveKeyShardsList[] { Key_Shard_1, Key_Shard_2 };

        const uint32_t listLength = sizeof( progressiveKeyShardsList ) / sizeof( progressiveKeyShardsList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveKeyShardsList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Big_Key_Goron_Mines );
    };

    auto getProgressiveMirrorShard = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveMirrorShardsList[] { Mirror_Piece_2, Mirror_Piece_3, Mirror_Piece_4 };

        const uint32_t listLength = sizeof( progressiveMirrorShardsList ) / sizeof( progressiveMirrorShardsList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveMirrorShardsList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Mirror_Piece_4 );
    };

    auto getProgressiveFusedShadow = []()
    {
        using namespace libtp::data::items;
        const uint8_t progressiveFusedShadowList[] { Fused_Shadow_1, Fused_Shadow_2, Fused_Shadow_3 };

        const uint32_t listLength = sizeof( progressiveFusedShadowList ) / sizeof( progressiveFusedShadowList[0] );
        for ( uint32_t i = 0; i < listLength; i++ )
        {
            uint32_t item = progressiveFusedShadowList[i];
            if ( !events::haveItem( item ) )
            {
                return item;
            }
        }

        // All previous obtained, so return last upgrade
        return static_cast<uint32_t>( Fused_Shadow_3 );
    };

    uint32_t _04_verifyProgressiveItem( rando::Randomizer* randomizer, uint32_t itemID )
    {
        using namespace libtp::data::items;
        if ( randomizer )
        {
            switch ( itemID )
            {
                case Wooden_Sword:
                case Ordon_Sword:
                case Master_Sword:
                case Master_Sword_Light:
                {
                    itemID = getProgressiveSword();
                    break;
                }

                case Heros_Bow:
                case Big_Quiver:
                case Giant_Quiver:
                {
                    itemID = getProgressiveBow();
                    break;
                }

                case Big_Wallet:
                case Giant_Wallet:
                {
                    if ( libtp::tp::d_item::checkItemGet( Big_Wallet, 1 ) )
                    {
                        itemID = Giant_Wallet;
                    }
                    else
                    {
                        itemID = Big_Wallet;
                    }
                    break;
                }

                case Ending_Blow:
                case Shield_Attack:
                case Back_Slice:
                case Helm_Splitter:
                case Mortal_Draw:
                case Jump_Strike:
                case Great_Spin:
                {
                    itemID = getProgressiveSkill();
                    break;
                }

                case Clawshot:
                case Double_Clawshots:
                {
                    if ( libtp::tp::d_item::checkItemGet( Clawshot, 1 ) )
                    {
                        itemID = Double_Clawshots;
                    }
                    else
                    {
                        itemID = Clawshot;
                    }
                    break;
                }

                case Ancient_Sky_Book_Empty:
                case Ancient_Sky_Book_First_Character:
                case Ancient_Sky_Book_Second_Character:
                case Ancient_Sky_Book_Third_Character:
                case Ancient_Sky_Book_Fourth_Character:
                case Ancient_Sky_Book_Fifth_Character:
                case Ancient_Sky_Book_Completed:
                {
                    itemID = getProgressiveSkyBook();
                    break;
                }

                case Empty_Bomb_Bag:
                case Goron_Bomb_Bag:
                case Giant_Bomb_Bag:
                {
                    itemID = getProgressiveBombBag();
                    break;
                }

                case Key_Shard_1:
                case Key_Shard_2:
                case Big_Key_Goron_Mines:
                {
                    itemID = getProgressiveKeyShard();
                    break;
                }

                case Dominion_Rod_Uncharged:
                case Dominion_Rod:
                {
                    if ( libtp::tp::d_item::checkItemGet( Dominion_Rod_Uncharged, 1 ) )
                    {
                        itemID = Dominion_Rod;
                    }
                    else
                    {
                        itemID = Dominion_Rod_Uncharged;
                    }
                    break;
                }

                case Fishing_Rod:
                case Coral_Earring:
                {
                    if ( libtp::tp::d_item::checkItemGet( Fishing_Rod, 1 ) )
                    {
                        itemID = Coral_Earring;
                    }
                    else
                    {
                        itemID = Fishing_Rod;
                    }
                    break;
                }

                case Mirror_Piece_2:
                case Mirror_Piece_3:
                case Mirror_Piece_4:
                {
                    itemID = getProgressiveMirrorShard();
                    break;
                }

                case Fused_Shadow_1:
                case Fused_Shadow_2:
                case Fused_Shadow_3:
                {
                    itemID = getProgressiveFusedShadow();
                    break;
                }

                default:
                {
                    return itemID;
                }
            }
        }
        return itemID;
    }
}     // namespace mod::game_patch