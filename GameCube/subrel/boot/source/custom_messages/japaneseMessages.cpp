// This file should only be used for JP
#ifdef TP_JP

#include "customMessages.h"
#include "tp/resource.h"
#include "item_wheel_menu.h"
#include "game_patch/game_patch.h"

#include <cstdint>
#include <cstdio>
#include <cinttypes>

namespace mod::customMessages
{
    using namespace item_wheel_menu;

    // Disable formatting for the textbox messages because it makes things look weird.
    // clang-format off
    MSG_BEGIN_ARRAY(forestSmallKeyJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_GREEN)
        // Y
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        // の
        "\x82\xCC"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れ
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA"
    MSG_END();
    MSG_BEGIN_ARRAY(snowpeakSmallKeyJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        // 雪山の廃墟
        "\x90\xE1\x8E\x52\x82\xCC\x94\x70" MSG_SP_CHAR_KYO
        MSG_COLOR(MSG_COLOR_WHITE)
        // の
        "\x82\xCC"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れ
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA"
    MSG_END();
    MSG_BEGIN_ARRAY(shadowCrystalJp)
        MSG_SPEED(MSG_SPEED_SLOW)
        MSG_COLOR(MSG_COLOR_RED)
        // 影の結晶石
        "\x89\x65\x82\xCC\x8C\x8B\x8F\xBB\x90\xCE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！ ザントの魔力の塊 使えばいつでも獣になれる！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A\x83\x55\x83\x93\x83\x67\x82\xCC\x96\x82\x97\xCD\x82\xCC\x89\xF2\x0A\x8E\x67\x82\xA6\x82\xCE\x82\xA2\x82\xC2\x82\xC5\x82\xE0\x8F\x62\x82\xC9\x82\xC8\x82\xEA\x82\xE9\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(endingBlowJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その一、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x88\xEA\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // とどめ
        "\x82\xC6\x82\xC7\x82\xDF"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(shieldAttackJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その二、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x93\xF1\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // 盾アタック
        "\x8F\x82\x83\x41\x83\x5E\x83\x62\x83\x4E"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(backSliceJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その三、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x8E\x4F\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // 背面斬り
        "\x94\x77\x96\xCA\x8E\x61\x82\xE8"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(helmSplitterJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その四、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x8E\x6C\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // 兜割り
        "\x8A\x95\x8A\x84\x82\xE8"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(mortalDrawJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その五、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x8C\xDC\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // 居合い
        "\x8B\x8F\x8D\x87\x82\xA2"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(jumpStrikeJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その六、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x98\x5A\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // 大ジャンプ斬り
        "\x91\xE5\x83\x57\x83\x83\x83\x93\x83\x76\x8E\x61\x82\xE8"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(greatSpinJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 奥義その七、
        "\x89\x9C\x8B\x60\x82\xBB\x82\xCC\x8E\xB5\x81\x41"
        MSG_COLOR(MSG_COLOR_RED)
        // 大回転斬り
        "\x91\xE5\x89\xF1\x93\x5D\x8E\x61\x82\xE8"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を習得した！
        "\x82\xF0\x8F\x4B\x93\xBE\x82\xB5\x82\xBD\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(poweredRodJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // コピーロッド
        "\x83\x52\x83\x73\x81\x5B\x83\x8D\x83\x62\x83\x68"
        MSG_COLOR(MSG_COLOR_WHITE)
        // に魔力が戻った！太古の石像に命を吹き込む 不思議なロッド
        "\x82\xC9\x96\x82\x97\xCD\x82\xAA\x96\xDF\x82\xC1\x82\xBD\x81\x49\x0A\x91\xBE\x8C\xC3\x82\xCC\x90\xCE\x91\x9C\x82\xC9\x96\xBD\x82\xF0\x90\x81\x82\xAB\x8D\x9E\x82\xDE\x0A\x95\x73\x8E\x76\x8B\x63\x82\xC8\x83\x8D\x83\x62\x83\x68"
    MSG_END();
    MSG_BEGIN_ARRAY(skyBookCharacterJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 天空文字
        "\x93\x56\x8B\xF3\x95\xB6\x8E\x9A"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を1個 見つけた！\n
        "\x82\xF0\x31\x8C\xC2\x20\x8C\xA9\x82\xC2\x82\xAF\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // 個集まりました。
        "\x8C\xC2\x8F\x57\x82\xDC\x82\xE8\x82\xDC\x82\xB5\x82\xBD\x81\x42"
    MSG_END();
    MSG_BEGIN_ARRAY(firstFusedShadowJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 一つ目の影の結晶石
        "\x88\xEA\x82\xC2\x96\xDA\x82\xCC\x89\x65\x82\xCC\x8C\x8B\x8F\xBB\x90\xCE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_GREEN)
        // コケ
        "\x83\x52\x83\x50"
        MSG_COLOR(MSG_COLOR_WHITE)
        // ケが生えている...
        "\x82\xAA\x90\xB6\x82\xA6\x82\xC4\x82\xA2\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(secondFusedShadowJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 二つ目の影の結晶石
        "\x93\xF1\x82\xC2\x96\xDA\x82\xCC\x89\x65\x82\xCC\x8C\x8B\x8F\xBB\x90\xCE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // 温かい
        "\x89\xB7\x82\xA9\x82\xA2"
        MSG_COLOR(MSG_COLOR_WHITE)
        // 感じがする...
        "\x8A\xB4\x82\xB6\x82\xAA\x82\xB7\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(thirdFusedShadowJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 三つ目の影の結晶石
        "\x8E\x4F\x82\xC2\x96\xDA\x82\xCC\x89\x65\x82\xCC\x8C\x8B\x8F\xBB\x90\xCE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        // 魚
        "\x8B\x9B"
        MSG_COLOR(MSG_COLOR_WHITE)
        // の臭いがする...
        "\x82\xCC\x8F\x4C\x82\xA2\x82\xAA\x82\xB7\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(firstMirrorShardJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 一つ目の
        "\x88\xEA\x82\xC2\x96\xDA\x82\xCC"
        MSG_COLOR(MSG_COLOR_RED)
        // 陰りの鏡のかけら
        "\x89\x41\x82\xE8\x82\xCC\x8B\xBE\x82\xCC\x82\xA9\x82\xAF\x82\xE7"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_ORANGE)
        // 砂
        "\x8D\xBB"
        MSG_COLOR(MSG_COLOR_WHITE)
        // で覆われている・・・
        "\x82\xC5\x95\xA2\x82\xED\x82\xEA\x82\xC4\x82\xA2\x82\xE9\x81\x45\x81\x45\x81\x45"
    MSG_END();
    MSG_BEGIN_ARRAY(secondMirrorShardJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 二つ目の陰りの鏡
        "\x93\xF1\x82\xC2\x96\xDA\x82\xCC\x89\x41\x82\xE8\x82\xCC\x8B\xBE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        // 冷たい
        "\x97\xE2\x82\xBD\x82\xA2"
        MSG_COLOR(MSG_COLOR_WHITE)
        // 感じがする...
        "\x8A\xB4\x82\xB6\x82\xAA\x82\xB7\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(thirdMirrorShardJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 三つ目の陰りの鏡
        "\x8E\x4F\x82\xC2\x96\xDA\x82\xCC\x89\x41\x82\xE8\x82\xCC\x8B\xBE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        // 汚れ
        "\x89\x98\x82\xEA"
        MSG_COLOR(MSG_COLOR_WHITE)
        // が付着している...
        "\x82\xAA\x95\x74\x92\x85\x82\xB5\x82\xC4\x82\xA2\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(fourthMirrorShardJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 四つ目の陰りの鏡
        "\x8E\x6C\x82\xC2\x96\xDA\x82\xCC\x89\x41\x82\xE8\x82\xCC\x8B\xBE"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_YELLOW)
        // 空気
        "\x8B\xF3\x8B\x43"
        MSG_COLOR(MSG_COLOR_WHITE)
        // より軽く感じる...
        "\x82\xE6\x82\xE8\x8C\x79\x82\xAD\x8A\xB4\x82\xB6\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(foolishItemJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        // 冷たい
        "\x97\xE2\x82\xBD\x82\xA2"
        MSG_COLOR(MSG_COLOR_WHITE)
        // 感じがする...
        "\x8A\xB4\x82\xB6\x82\xAA\x82\xB7\x82\xE9\x2e\x2e\x2e"
    MSG_END();
    MSG_BEGIN_ARRAY(talkToMidnaJp)
        // どうした、
        "\x82\xC7\x82\xA4\x82\xB5\x82\xBD\x81\x41"
        MSG_PLYR_NAME
        // "?"
        "\x81\x48"
        MSG_OPTION_LIST(MSG_OPTION_1)
        // 獣になる
        "\x8F\x62\x82\xC9\x82\xC8\x82\xE9\x0A"
        MSG_OPTION_LIST(MSG_OPTION_2)
        // ワープ
        "\x83\x8F\x81\x5B\x83\x76\x0A"
        MSG_OPTION_LIST(MSG_OPTION_3)
        // 時間を変更する
        "\x8E\x9E\x8A\xD4\x82\xF0\x95\xCF\x8D\x58\x82\xB7\x82\xE9"
    MSG_END();
    MSG_BEGIN_ARRAY(bigWalletJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 大きなサイフ
        "\x91\xE5\x82\xAB\x82\xC8\x83\x54\x83\x43\x83\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を受け取った！
        "\x82\xF0\x8E\xF3\x82\xAF\x8E\xE6\x82\xC1\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // ５０００ルピー
        "\x82\x54\x82\x4F\x82\x4F\x82\x4F\x83\x8B\x83\x73\x81\x5B"
        MSG_COLOR(MSG_COLOR_WHITE)
        // まで入れられる！
        "\x82\xDC\x82\xC5\x93\xFC\x82\xEA\x82\xE7\x82\xEA\x82\xE9\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(giantWalletJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // 最大のサイフ
        "\x8D\xC5\x91\xE5\x82\xCC\x83\x54\x83\x43\x83\x74"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を受け取った！
        "\x82\xF0\x8E\xF3\x82\xAF\x8E\xE6\x82\xC1\x82\xBD\x81\x49\x0A"
        MSG_COLOR(MSG_COLOR_PURPLE)
        // ９９９９ルピー
        "\x82\x58\x82\x58\x82\x58\x82\x58\x83\x8B\x83\x73\x81\x5B"
        MSG_COLOR(MSG_COLOR_WHITE)
        // まで入れられる！
        "\x82\xDC\x82\xC5\x93\xFC\x82\xEA\x82\xE7\x82\xEA\x82\xE9\x81\x49"
    MSG_END();
    MSG_BEGIN_ARRAY(smallWalletPauseJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // ようしょう幼少じだい時代からのあい愛ようひん用品 １０００ルピーまでい入れられる
        "\x1A\x10\xFF\x00\x02\x02\x82\xE6\x82\xA4\x82\xB5\x82\xE5\x82\xA4\x97\x63\x8F\xAD\x1A\x0C\xFF\x00\x02\x02\x82\xB6\x82\xBE\x82\xA2\x8E\x9E\x91\xE3\x82\xA9\x82\xE7\x82\xCC\x1A\x0A\xFF\x00\x02\x01\x82\xA0\x82\xA2\x88\xA4\x1A\x0E\xFF\x00\x02\x02\x82\xE6\x82\xA4\x82\xD0\x82\xF1\x97\x70\x95\x69\x0A\x82\x50\x82\x4F\x82\x4F\x82\x4F\x83\x8B\x83\x73\x81\x5B\x82\xDC\x82\xC5\x1A\x08\xFF\x00\x02\x01\x82\xA2\x93\xFC\x82\xEA\x82\xE7\x82\xEA\x82\xE9"
    MSG_END();
    MSG_BEGIN_ARRAY(bigWalletPauseJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // むし虫さんおうこく王国のおうじょ王女、アゲハからもらったサイフ ５０００ルピーまでい入れられる
        "\x1A\x0A\xFF\x00\x02\x01\x82\xDE\x82\xB5\x92\x8E\x82\xB3\x82\xF1\x1A\x0E\xFF\x00\x02\x02\x82\xA8\x82\xA4\x82\xB1\x82\xAD\x89\xA4\x8D\x91\x82\xCC\x1A\x0E\xFF\x00\x02\x02\x82\xA8\x82\xA4\x82\xB6\x82\xE5\x89\xA4\x8F\x97\x81\x41\x83\x41\x83\x51\x83\x6E\x82\xA9\x82\xE7\x82\xE0\x82\xE7\x82\xC1\x82\xBD\x83\x54\x83\x43\x83\x74\x0A\x82\x54\x82\x4F\x82\x4F\x82\x4F\x83\x8B\x83\x73\x81\x5B\x82\xDC\x82\xC5\x1A\x08\xFF\x00\x02\x01\x82\xA2\x93\xFC\x82\xEA\x82\xE7\x82\xEA\x82\xE9"
    MSG_END();
    MSG_BEGIN_ARRAY(giantWalletPauseJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // むし虫さんおうこく王国のおうじょ王女、アゲハからもらったサイフおうこく王国にこうけん貢献したもの者だけにあた与えられる ９９９９ルピーまでい入れられる
        "\x1A\x0A\xFF\x00\x02\x01\x82\xDE\x82\xB5\x92\x8E\x82\xB3\x82\xF1\x1A\x0E\xFF\x00\x02\x02\x82\xA8\x82\xA4\x82\xB1\x82\xAD\x89\xA4\x8D\x91\x82\xCC\x1A\x0E\xFF\x00\x02\x02\x82\xA8\x82\xA4\x82\xB6\x82\xE5\x89\xA4\x8F\x97\x81\x41\x83\x41\x83\x51\x83\x6E\x82\xA9\x82\xE7\x82\xE0\x82\xE7\x82\xC1\x82\xBD\x83\x54\x83\x43\x83\x74\x0A\x1A\x0E\xFF\x00\x02\x02\x82\xA8\x82\xA4\x82\xB1\x82\xAD\x89\xA4\x8D\x91\x82\xC9\x1A\x0E\xFF\x00\x02\x02\x82\xB1\x82\xA4\x82\xAF\x82\xF1\x8D\x76\x8C\xA3\x82\xB5\x82\xBD\x1A\x0A\xFF\x00\x02\x01\x82\xE0\x82\xCC\x8E\xD2\x82\xBE\x82\xAF\x82\xC9\x1A\x0A\xFF\x00\x02\x01\x82\xA0\x82\xBD\x97\x5E\x82\xA6\x82\xE7\x82\xEA\x82\xE9\x0A\x82\x58\x82\x58\x82\x58\x82\x58\x83\x8B\x83\x73\x81\x5B\x82\xDC\x82\xC5\x1A\x08\xFF\x00\x02\x01\x82\xA2\x93\xFC\x82\xEA\x82\xE7\x82\xEA\x82\xE9"
    MSG_END();
    MSG_BEGIN_ARRAY(poeSoulJp)
        MSG_SPEED(MSG_SPEED_FAST)
        MSG_COLOR(MSG_COLOR_RED)
        // ゴーストの魂
        "\x83\x53\x81\x5B\x83\x58\x83\x67\x82\xCC\x8D\xB0"
        MSG_COLOR(MSG_COLOR_WHITE)
        // を手に入れた！
        "\x82\xF0\x8E\xE8\x82\xC9\x93\xFC\x82\xEA\x82\xBD\x81\x49\x0a"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // 個集まりました。
        "\x8C\xC2\x8F\x57\x82\xDC\x82\xE8\x82\xDC\x82\xB5\x82\xBD\x81\x42"
    MSG_END();
    MSG_BEGIN_ARRAY(skyBookDescriptionJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // 古の天空語で 記された書物\nところどころ 言葉がか欠けている\n\n
        "\x8C\xC3\x82\xCC\x93\x56\x8B\xF3\x8C\xEA\x82\xC5\x20\x8B\x4C\x82\xB3\x82\xEA\x82\xBD\x8F\x91\x95\xA8\x0A\x82\xC6\x82\xB1\x82\xEB\x82\xC7\x82\xB1\x82\xEB\x20\x8C\xBE\x97\x74\x82\xAA\x82\xA9\x8C\x87\x82\xAF\x82\xC4\x82\xA2\x82\xE9\x0A\x0A"
        MSG_COLOR(MSG_COLOR_RED)
        // X
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        // 個集まりました。
        "\x8C\xC2\x8F\x57\x82\xDC\x82\xE8\x82\xDC\x82\xB5\x82\xBD\x81\x42"
    MSG_END();
    MSG_BEGIN_ARRAY(charloDonationJp)
        // ハイラルのへいわ平和のため・・・ほどこ施しをいただけませんかな・・・？
        "\x83\x6E\x83\x43\x83\x89\x83\x8B\x82\xCC\x1A\x0C\xFF\x00\x02\x02\x82\xD6\x82\xA2\x82\xED\x95\xBD\x98\x61\x82\xCC\x82\xBD\x82\xDF\x81\x45\x81\x45\x81\x45\x0A\x1A\x0C\xFF\x00\x02\x01\x82\xD9\x82\xC7\x82\xB1\x8E\x7B\x82\xB5\x82\xF0\x82\xA2\x82\xBD\x82\xBE\x82\xAF\x82\xDC\x82\xB9\x82\xF1\x82\xA9\x82\xC8\x81\x45\x81\x45\x81\x45\x81\x48" 
        MSG_OPTION_LIST(MSG_OPTION_1) 
        // １００ルピー
        "\x82\x50\x82\x4f\x82\x4F\x83\x8B\x83\x73\x81\x5B\x0A" 
        MSG_OPTION_LIST(MSG_OPTION_2) 
        // ５０ルピー
        "\x82\x54\x82\x4F\x83\x8B\x83\x73\x81\x5B\x0A" 
        MSG_OPTION_LIST(MSG_OPTION_3) 
        // 断る
        "\x1A\x0C\xFF\x00\x02\x01\x82\xB1\x82\xC6\x82\xED\x92\x66\x82\xE9";
    MSG_END();
    MSG_BEGIN_ARRAY(recognitionJp)
        MSG_SPEED(MSG_SPEED_FAST)
        // ベータテスターの皆様に感謝します。本当にありがとうございました
        "\x83\x78\x81\x5B\x83\x5E\x83\x65\x83\x58\x83\x5E\x81\x5B\x82\xCC\x8A\x46\x97\x6C\x82\xC9\x8A\xB4\x8E\xD3\x82\xB5\x82\xDC\n\x82\xB7\x81\x42\x96\x7B\x93\x96\x82\xC9\x82\xA0\x82\xE8\x82\xAA\x82\xC6\x82\xA4\x82\xB2\x82\xB4\x82\xA2\x82\xDC\x82\xB5\n\x82\xBD: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END();

    char smallKeyTextJp[] = "\x8F\xAC\x82\xB3\x82\xC8\x83\x4A\x83\x4D"; // 小さなカギ
    char dungeonMapTextJp[] = "\x83\x5F\x83\x93\x83\x57\x83\x87\x83\x93\x83\x7D\x83\x62\x83\x76\n"; // ダンジョンマップ
    char compassTextJp[] = "\x83\x52\x83\x93\x83\x70\x83\x58"; // コンパス
    char bigKeyTextJp[] = "\x83\x7B\x83\x58\x95\x94\x89\xAE\x82\xCC\x83\x4A\x83\x4D\n"; // ボス部屋のカギ
    char forestTempleTextJp[] = "\x90\x58\x82\xCC\x90\x5F\x93\x61"; // 森の神殿
    char goronMinesTextJp[] = "\x83\x53\x83\x8D\x83\x93\x8D\x7A\x8E\x52"; // ゴロン鉱山
    char lakebedTempleTextJp[] = "\x8C\xCE\x92\xEA\x82\xCC\x90\x5F\x93\x61"; // 湖底の神殿
    char arbitersGroundsTextJp[] = "\x8D\xBB\x94\x99\x82\xCC\x8F\x88\x8C\x59\x8F\xEA"; // 砂漠の処刑場
    char templeOfTimeTextJp[] = "\x8E\x9E\x82\xCC\x90\x5F\x93\x61"; // 時の神殿
    char cityInTheSkyTextJp[] = "\x93\x56\x8B\xF3\x93\x73\x8E\x73"; // 天空都市
    char palaceOfTwilightTextJp[] = "\x89\x65\x82\xCC\x8B\x7B\x93\x61"; // 影の宮殿
    char hyruleCastleTextJp[] = "\x83\x6E\x83\x43\x83\x89\x83\x8B\x8F\xE9"; // ハイラル城
    char bulblinCampTextJp[] = "\x83\x75\x83\x8B\x83\x75\x83\x8A\x83\x93\x82\xCC\x97\x76\x8D\xC7\n"; // ブルブリンの要塞
    // clang-format on

    const MsgEntry entriesJp[] = {
        // Forest Temple small key
        forestSmallKeyJp,
        sizeof(forestSmallKeyJp),
        0x00E9,

        // Snowpeak Ruins small key
        snowpeakSmallKeyJp,
        sizeof(snowpeakSmallKeyJp),
        0x00ED,

        // Shadow Crystal
        shadowCrystalJp,
        sizeof(shadowCrystalJp),
        0x0096,

        // Ending Blow hidden skill
        endingBlowJp,
        sizeof(endingBlowJp),
        0x0145,

        // Shield Attack hidden skill
        shieldAttackJp,
        sizeof(shieldAttackJp),
        0x0146,

        // Back Slice hidden skill
        backSliceJp,
        sizeof(backSliceJp),
        0x0147,

        // Helm Splitter hidden skill
        helmSplitterJp,
        sizeof(helmSplitterJp),
        0x0148,

        // Mortal Draw hidden skill
        mortalDrawJp,
        sizeof(mortalDrawJp),
        0x0149,

        // Jump Strike hidden skill
        jumpStrikeJp,
        sizeof(jumpStrikeJp),
        0x014A,

        // Great Spin hidden skill
        greatSpinJp,
        sizeof(greatSpinJp),
        0x014B,

        // Powered up Dominion Rod
        poweredRodJp,
        sizeof(poweredRodJp),
        0x00B0,

        // First Ancient Sky Book character
        skyBookCharacterJp,
        sizeof(skyBookCharacterJp),
        0x013F,

        // First Fused Shadow
        firstFusedShadowJp,
        sizeof(firstFusedShadowJp),
        0x013C,

        // Second Fused Shadow
        secondFusedShadowJp,
        sizeof(secondFusedShadowJp),
        0x013D,

        // Third Fused Shadow
        thirdFusedShadowJp,
        sizeof(thirdFusedShadowJp),
        0x013E,

        // First Mirror Shard
        firstMirrorShardJp,
        sizeof(firstMirrorShardJp),
        0x0B7,

        // Second Mirror Shard
        secondMirrorShardJp,
        sizeof(secondMirrorShardJp),
        0x0109,

        // Third Mirror Shard
        thirdMirrorShardJp,
        sizeof(thirdMirrorShardJp),
        0x010A,

        // Fourth Mirror Shard
        fourthMirrorShardJp,
        sizeof(fourthMirrorShardJp),
        0x010B,

        // Foolish Item
        foolishItemJp,
        sizeof(foolishItemJp),
        0x0077,

        // Talking to Midna
        talkToMidnaJp,
        sizeof(talkToMidnaJp),
        0x0BBB,

        // Big Wallet
        bigWalletJp,
        sizeof(bigWalletJp),
        0x0099,

        // Giant Wallet
        giantWalletJp,
        sizeof(giantWalletJp),
        0x009A,

        // Small Wallet Menu Text
        smallWalletPauseJp,
        sizeof(smallWalletPauseJp),
        0x0298,

        // Big Wallet Menu Text
        bigWalletPauseJp,
        sizeof(bigWalletPauseJp),
        0x0299,

        // Giant Wallet Menu Text
        giantWalletPauseJp,
        sizeof(giantWalletPauseJp),
        0x029a,

        // Poe Soul
        poeSoulJp,
        sizeof(poeSoulJp),
        0x0144,

        // Sky Book Item Wheel Description
        skyBookDescriptionJp,
        sizeof(skyBookDescriptionJp),
        0x34d,

        // Recognition text
        recognitionJp,
        sizeof(recognitionJp),
        0x0b44,

        // Special invalid-id texts
        // Small Key
        smallKeyTextJp,
        sizeof(smallKeyTextJp),
        game_patch::SpecialMessageIds::SMALL_KEY,

        // Dungeon Map
        dungeonMapTextJp,
        sizeof(dungeonMapTextJp),
        game_patch::SpecialMessageIds::DUNGEON_MAP,

        // Compass
        compassTextJp,
        sizeof(compassTextJp),
        game_patch::SpecialMessageIds::COMPASS,

        // Big Key
        bigKeyTextJp,
        sizeof(bigKeyTextJp),
        game_patch::SpecialMessageIds::BIG_KEY,

        // Forest Temple
        forestTempleTextJp,
        sizeof(forestTempleTextJp),
        game_patch::SpecialMessageIds::FOREST_TEMPLE,

        // Goron Mines
        goronMinesTextJp,
        sizeof(goronMinesTextJp),
        game_patch::SpecialMessageIds::GORON_MINES,

        // Lakebed Temple
        lakebedTempleTextJp,
        sizeof(lakebedTempleTextJp),
        game_patch::SpecialMessageIds::LAKEBED_TEMPLE,

        // Arbiter's Grounds
        arbitersGroundsTextJp,
        sizeof(arbitersGroundsTextJp),
        game_patch::SpecialMessageIds::ARBITERS_GROUNDS,

        // Temple of Time
        templeOfTimeTextJp,
        sizeof(templeOfTimeTextJp),
        game_patch::SpecialMessageIds::TEMPLE_OF_TIME,

        // City in the Sky
        cityInTheSkyTextJp,
        sizeof(cityInTheSkyTextJp),
        game_patch::SpecialMessageIds::CITY_IN_THE_SKY,

        // Palace of Twilight
        palaceOfTwilightTextJp,
        sizeof(palaceOfTwilightTextJp),
        game_patch::SpecialMessageIds::PALACE_OF_TWILIGHT,

        // Hyrule Castle
        hyruleCastleTextJp,
        sizeof(hyruleCastleTextJp),
        game_patch::SpecialMessageIds::HYRULE_CASTLE,

        // Bulblin Camp
        bulblinCampTextJp,
        sizeof(bulblinCampTextJp),
        game_patch::SpecialMessageIds::BULBLIN_CAMP,

        // This is an extra section that should go unused, and is only needed for _05_getMsgById in 05_itemMsgFunctions.cpp to
        // ensure that it can properly calculate sizeOut
        "",
        0,
        0xFFFF,
    };

    const uint32_t totalCustomMessagesJp = sizeof(entriesJp) / sizeof(MsgEntry);
    const MsgEntry charloDonationEntryJp = {charloDonationJp, sizeof(charloDonationJp), 0x0355};

    const ItemWheelMenuStrings itemWheelMenuStringsJp = {
        // areasBeingTracked
        {
            // Forest Temple
            // 森の神殿
            "\x90\x58\x82\xCC\x90\x5F\x93\x61",

            // Goron Mines
            // ゴロン鉱山
            "\x83\x53\x83\x8D\x83\x93\x8D\x7A\x8E\x52",

            // Lakebed Temple
            // 湖底の神殿
            "\x8C\xCE\x92\xEA\x82\xCC\x90\x5F\x93\x61",

            // Arbiter's Grounds
            // 砂漠の処刑場
            "\x8D\xBB\x94\x99\x82\xCC\x8F\x88\x8C\x59\x8F\xEA",

            // Snowpeak Ruins
            // 雪山の廃
            "\x90\xE1\x8E\x52\x82\xCC\x94\x70",

            // Temple of Time
            // 時の神殿
            "\x8E\x9E\x82\xCC\x90\x5F\x93\x61",

            // City in the Sky
            // 天空都市
            "\x93\x56\x8B\xF3\x93\x73\x8E\x73",

            // Palace of Twilight
            // 影の宮殿
            "\x89\x65\x82\xCC\x8B\x7B\x93\x61",

            // Hyrule Castle
            // ハイラル城
            "\x83\x6E\x83\x43\x83\x89\x83\x8B\x8F\xE9",

            // Faron Woods
            // フィローネの森
            "\x83\x74\x83\x42\x83\x8D\x81\x5B\x83\x6C\x82\xCC\x90\x58",

            // Bulblin Camp
            // ブルブリンの要塞
            "\x83\x75\x83\x8B\x83\x75\x83\x8A\x83\x93\x82\xCC\x97\x76\x8D\xC7",
        },

        // seedIsLoaded
        // シード
        "\x83\x56\x81\x5B\x83\x68",

        // seedIsNotLoaded
        // シードは読み込まれません
        "\x83\x56\x81\x5B\x83\x68\x82\xCD\x93\xC7\x82\xDD\x8D\x9E\x82\xDC\x82\xEA\x82\xDC\x82\xB9\x82\xF1",

        // yes/no
        // あり
        "\x82\xA0\x82\xE8",

        // ない
        "\x82\xC8\x82\xA2",

        // shadowsShards
        // 影の結晶石\n陰りの鏡
        "\x89\x65\x82\xCC\x8C\x8B\x8F\xBB\x90\xCE\x0A\x89\x41\x82\xE8\x82\xCC\x8B\xBE",

        // Pumpkin
        // トアルカボチャ
        "\x83\x67\x83\x41\x83\x8B\x83\x4A\x83\x7B\x83\x60\x83\x83",

        // Cheese
        // トアル山羊のチーズ
        "\x83\x67\x83\x41\x83\x8B\x8E\x52\x97\x72\x82\xCC\x83\x60\x81\x5B\x83\x59",

        // Gate Keys
        // 門の小さなカギ
        "\x96\xE5\x82\xCC\x8F\xAC\x82\xB3\x82\xC8\x83\x4A\x83\x4D",

        // Areas
        // 領域
        "\x97\xCC\x88\xE6",

        // Small Keys
        // 小さなカギ
        "\x8F\xAC\x82\xB3\x82\xC8\x83\x4A\x83\x4D",

        // Big Keys
        // ボス部屋のカギ
        "\x83\x7B\x83\x58\x95\x94\x89\xAE\x82\xCC\x83\x4A\x83\x4D",

        // Maps
        // ダンジョンマップ
        "\x83\x5F\x83\x93\x83\x57\x83\x87\x83\x93\x83\x7D\x83\x62\x83\x76",

        // Compasses
        // コンパス
        "\x83\x52\x83\x93\x83\x70\x83\x58",

        // helpText
        // SかZボタン押すと\n情報が表示される
        "\x53\x82\xA9\x5a\x83\x7B\x83\x5E\x83\x93\x89\x9F\x82\xB7\x82\xC6\x0A"
        "\x8F\xEE\x95\xF1\x82\xAA\x95\x5C\x8E\xA6\x82\xB3\x82\xEA\x82\xE9",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsJp {
        // Fused Shadows/Mirror Shards
        80,

        // Pumpkin
        50,

        // Yes/No
        34,
        34,

        // Cheese
        111,

        // Yes/No
        49,
        49,

        // Gate Keys
        143,

        // Yes/No
        34,
        34,

        // Headers
        // Small Keys
        115,

        // Big Keys
        90,

        // Maps
        117,

        // Compasses
        128,

        // Header values
        // Small Keys values
        28,

        // Big keys values
        // Yes/No
        33,
        33,

        // Goron Mines
        41,

        // Maps values
        // Yes/No
        40,
        40,

        // Compasses values
        // Yes/No
        13,
        13,
    };
} // namespace mod::customMessages
#endif