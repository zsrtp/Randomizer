// This file should not be used for JP
#ifndef TP_JP

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
    MSG_BEGIN_ARRAY( forestSmallKeyEn )
        MSG_SPEED( MSG_SPEED_FAST )
        "You got "
        MSG_COLOR(MSG_COLOR_RED)
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        " %s %s\n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "%s"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( shadowCrystalEn )
        MSG_SPEED(MSG_SPEED_SLOW)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Shadow Crystal"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nThis is a dark manifestation\nof "
        MSG_COLOR(MSG_COLOR_RED)
        "Zant's "
        MSG_COLOR(MSG_COLOR_WHITE)
        "power that allows\nyou to transform at will!"
    MSG_END();
    MSG_BEGIN_ARRAY( endingBlowEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Ending Blow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( shieldAttackEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Shield Attack"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( backSliceEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Back Slice"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( helmSplitterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Helm Splitter"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( mortalDrawEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Mortal Draw"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( jumpStrikeEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Jump Strike"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( greatSpinEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You learned the "
        MSG_COLOR(MSG_COLOR_RED)
        "Great Spin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( poweredRodEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "Power has been restored to\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Dominion Rod"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Now it can\nbe used to imbue statues\nwith life in the present!"
    MSG_END();
    MSG_BEGIN_ARRAY( skyBookCharacterEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got a "
        MSG_COLOR(MSG_COLOR_RED)
        "Sky character"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nYou've collected "
        MSG_COLOR(MSG_COLOR_RED)
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        " so far."
    MSG_END();
    MSG_BEGIN_ARRAY( firstFusedShadowEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got a "
        MSG_COLOR(MSG_COLOR_RED)
        "Fused Shadow!\n"
        MSG_COLOR(MSG_COLOR_WHITE)
        "It seems to have some "
        MSG_COLOR(MSG_COLOR_GREEN)
        "moss"
        MSG_COLOR(MSG_COLOR_WHITE)
        "\ngrowing on it.."
    MSG_END();
    MSG_BEGIN_ARRAY( secondFusedShadowEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the second "
        MSG_COLOR(MSG_COLOR_RED)
        "Fused\nShadow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It feels "
        MSG_COLOR(MSG_COLOR_RED)
        "warm"
        MSG_COLOR(MSG_COLOR_WHITE)
        " to\nthe touch.."
    MSG_END();
    MSG_BEGIN_ARRAY( thirdFusedShadowEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the final "
        MSG_COLOR(MSG_COLOR_RED)
        "Fused\nShadow"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It feels "
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "wet"
        MSG_COLOR(MSG_COLOR_WHITE)
        " and\nsmells like fish.."
    MSG_END();
    MSG_BEGIN_ARRAY( secondMirrorShardEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the second shard of\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Mirror of Twilight"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It\nhas a beautiful shine to it\nand feels slightly "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "cold"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END();
    MSG_BEGIN_ARRAY( thirdMirrorShardEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the third shard of\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Mirror of Twilight"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It\nis covered in dirt and\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "webs"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END();
    MSG_BEGIN_ARRAY( fourthMirrorShardEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the final shard of\nthe "
        MSG_COLOR(MSG_COLOR_RED)
        "Mirror of Twilight"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! It\nfeels lighter than "
        MSG_COLOR(MSG_COLOR_YELLOW)
        "air"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END();
    MSG_BEGIN_ARRAY( foolishItemEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "A "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "cold"
        MSG_COLOR(MSG_COLOR_WHITE)
        " wind blows.."
    MSG_END();
    MSG_BEGIN_ARRAY( talkToMidnaEn )
        "What is it, "
        MSG_PLYR_NAME
        "?"
        MSG_OPTION_LIST(MSG_OPTION_1)
        "Transform\n"
        MSG_OPTION_LIST(MSG_OPTION_2)
        "Warp\n"
        MSG_OPTION_LIST(MSG_OPTION_3)
        "Change time of day"
    MSG_END();
    MSG_BEGIN_ARRAY( bigWalletEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Big Wallet"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nYou can now hold\n"
        MSG_COLOR(MSG_COLOR_RED)
        "5,000 Rupees"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( giantWalletEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "You got the "
        MSG_COLOR(MSG_COLOR_RED)
        "Giant Wallet"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nYou can now hold\n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "9,999 Rupees"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END();
    MSG_BEGIN_ARRAY( smallWalletPauseEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "A wallet from your childhood.\nIt holds up to 1,000 Rupees."
    MSG_END();
    MSG_BEGIN_ARRAY( bigWalletPauseEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "The wallet given to you by Agitha,\nprincess of the insect kingdom.\nIt can hold 5,000 Rupees."
    MSG_END();
    MSG_BEGIN_ARRAY( giantWalletPauseEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "The wallet given by Agitha to\nbenefactors of the insect kingdom.\nIt can hold up to 9,999 Rupees."
    MSG_END();
    MSG_BEGIN_ARRAY( poeSoulEn )
        MSG_SPEED( MSG_SPEED_FAST )
        "You got a "
        MSG_COLOR(MSG_COLOR_RED)
        "Poe's soul"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nYou've collected "
        MSG_COLOR(MSG_COLOR_RED)
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        " so far."
    MSG_END();
    MSG_BEGIN_ARRAY( skyBookDescriptionEn )
        MSG_SPEED(MSG_SPEED_FAST)
        "A book written in the ancient Sky language.\nCharacters are missing in areas.\n\nYou've collected "
        MSG_COLOR(MSG_COLOR_RED)
        "%" PRIu32
        MSG_COLOR(MSG_COLOR_WHITE)
        " character(s) so far."
    MSG_END();
    MSG_BEGIN_ARRAY( charloDonationEn )
        "For the sake of peace in Hyrule...\nWould you please make a donation?" 
        MSG_OPTION_LIST( MSG_OPTION_1 ) 
        "100 Rupees\n" 
        MSG_OPTION_LIST( MSG_OPTION_2 ) 
        "50 Rupees\n" 
        MSG_OPTION_LIST( MSG_OPTION_3 ) 
        "Sorry..."
    MSG_END();
    MSG_BEGIN_ARRAY( recognitionMsg )
        MSG_SPEED(MSG_SPEED_FAST)
        "The Randomizer Team would like\nto thank our amazing testers.\nWithout you, this project would\nnot be what it is today: Taka\nAnorakkis, Archer, Br00ty, Chris\nChrono, clabrus, Demon, EmperorP\nElinadrian, Empty, Fennec, Zushi\nFleakee, Foxhole Gaming, Luzagar\nHeartPiece, Hornlitz, IceStorm\nJanWegh, JD, jdflyer, Jeez, Oxy\nJustRyland, Lance H., link1183\nLinkman124, Luneyes, GameWyrm\nMattStrats, MultFij, NesmaN88\nXenoWars, Papy_Grant, Simikins\npokemongenius, Psi-Hate, Lars P\nRaziel_Stratton, Redriel, Revven\nSparky7198, Zach, SwiftIke, j_im\nZenith, Prince, The., TheBruce\nTreZc0_, Wameslo, WickedGligar\nDGod63 and Sushi."
    MSG_END();
    
    char forTextUs[] = "for";
    char theTextUs[] = "the";
    char smallKeyTextUs[] = "a small key";
    char dungeonMapTextUs[] = "the dungeon map";
    char compassTextUs[] = "the compass";
    char bigKeyTextUs[] = "the big key";
    char forestTempleTextUs[] = "Forest Temple";
    char goronMinesTextUs[] = "Goron Mines";
    char lakebedTempleTextUs[] = "Lakebed Temple";
    char arbitersGroundsTextUs[] = "Arbiter's Grounds";
    char snowpeakRuinsTextUs[] = "Snowpeak Ruins";
    char templeOfTimeTextUs[] = "Temple of Time";
    char cityInTheSkyTextUs[] = "City in the Sky";
    char palaceOfTwilightTextUs[] = "Palace of Twilight";
    char hyruleCastleTextUs[] = "Hyrule Castle";
    char bulblinCampTextUs[] = "Bulblin Camp";
    // clang-format on

    const MsgEntry entriesUs[] = {
        // Forest Temple small key
        // All other dungeon items will use this as a base
        forestSmallKeyEn,
        sizeof(forestSmallKeyEn),
        0x00E9,

        // Shadow Crystal
        shadowCrystalEn,
        sizeof(shadowCrystalEn),
        0x0096,

        // Ending Blow hidden skill
        endingBlowEn,
        sizeof(endingBlowEn),
        0x0145,

        // Shield Attack hidden skill
        shieldAttackEn,
        sizeof(shieldAttackEn),
        0x0146,

        // Back Slice hidden skill
        backSliceEn,
        sizeof(backSliceEn),
        0x0147,

        // Helm Splitter hidden skill
        helmSplitterEn,
        sizeof(helmSplitterEn),
        0x0148,

        // Mortal Draw hidden skill
        mortalDrawEn,
        sizeof(mortalDrawEn),
        0x0149,

        // Jump Strike hidden skill
        jumpStrikeEn,
        sizeof(jumpStrikeEn),
        0x014A,

        // Great Spin hidden skill
        greatSpinEn,
        sizeof(greatSpinEn),
        0x014B,

        // Powered up Dominion Rod
        poweredRodEn,
        sizeof(poweredRodEn),
        0x00B0,

        // First Ancient Sky Book character
        skyBookCharacterEn,
        sizeof(skyBookCharacterEn),
        0x013F,

        // First Fused Shadow
        firstFusedShadowEn,
        sizeof(firstFusedShadowEn),
        0x013C,

        // Second Fused Shadow
        secondFusedShadowEn,
        sizeof(secondFusedShadowEn),
        0x013D,

        // Third Fused Shadow
        thirdFusedShadowEn,
        sizeof(thirdFusedShadowEn),
        0x013E,

        // Second Mirror Shard
        secondMirrorShardEn,
        sizeof(secondMirrorShardEn),
        0x0109,

        // Third Mirror Shard
        thirdMirrorShardEn,
        sizeof(thirdMirrorShardEn),
        0x010A,

        // Fourth Mirror Shard
        fourthMirrorShardEn,
        sizeof(fourthMirrorShardEn),
        0x010B,

        // Foolish Item
        foolishItemEn,
        sizeof(foolishItemEn),
        0x0077,

        // Talking to Midna
        talkToMidnaEn,
        sizeof(talkToMidnaEn),
        0x0BBB,

        // Big Wallet
        bigWalletEn,
        sizeof(bigWalletEn),
        0x0099,

        // Giant Wallet
        giantWalletEn,
        sizeof(giantWalletEn),
        0x009A,

        // Small Wallet Menu Text
        smallWalletPauseEn,
        sizeof(smallWalletPauseEn),
        0x0298,

        // Big Wallet Menu Text
        bigWalletPauseEn,
        sizeof(bigWalletPauseEn),
        0x0299,

        // Giant Wallet Menu Text
        giantWalletPauseEn,
        sizeof(giantWalletPauseEn),
        0x029a,

        // Poe Soul
        poeSoulEn,
        sizeof(poeSoulEn),
        0x0144,

        // Sky Book Item Wheel Description
        skyBookDescriptionEn,
        sizeof(skyBookDescriptionEn),
        0x34d,

        // Recognition text
        recognitionMsg,
        sizeof(recognitionMsg),
        0x0b44,

        // Special invalid-id texts
        // for
        forTextUs,
        sizeof(forTextUs),
        game_patch::SpecialMessageIds::FOR,

        // the
        theTextUs,
        sizeof(theTextUs),
        game_patch::SpecialMessageIds::THE,

        // Small Key
        smallKeyTextUs,
        sizeof(smallKeyTextUs),
        game_patch::SpecialMessageIds::SMALL_KEY,

        // Dungeon Map
        dungeonMapTextUs,
        sizeof(dungeonMapTextUs),
        game_patch::SpecialMessageIds::DUNGEON_MAP,

        // Compass
        compassTextUs,
        sizeof(compassTextUs),
        game_patch::SpecialMessageIds::COMPASS,

        // Big Key
        bigKeyTextUs,
        sizeof(bigKeyTextUs),
        game_patch::SpecialMessageIds::BIG_KEY,

        // Forest Temple
        forestTempleTextUs,
        sizeof(forestTempleTextUs),
        game_patch::SpecialMessageIds::FOREST_TEMPLE,

        // Goron Mines
        goronMinesTextUs,
        sizeof(goronMinesTextUs),
        game_patch::SpecialMessageIds::GORON_MINES,

        // Lakebed Temple
        lakebedTempleTextUs,
        sizeof(lakebedTempleTextUs),
        game_patch::SpecialMessageIds::LAKEBED_TEMPLE,

        // Arbiter's Grounds
        arbitersGroundsTextUs,
        sizeof(arbitersGroundsTextUs),
        game_patch::SpecialMessageIds::ARBITERS_GROUNDS,

        // Snowpeak Ruins
        snowpeakRuinsTextUs,
        sizeof(snowpeakRuinsTextUs),
        game_patch::SpecialMessageIds::SNOWPEAK_RUINS,

        // Temple of Time
        templeOfTimeTextUs,
        sizeof(templeOfTimeTextUs),
        game_patch::SpecialMessageIds::TEMPLE_OF_TIME,

        // City in the Sky
        cityInTheSkyTextUs,
        sizeof(cityInTheSkyTextUs),
        game_patch::SpecialMessageIds::CITY_IN_THE_SKY,

        // Palace of Twilight
        palaceOfTwilightTextUs,
        sizeof(palaceOfTwilightTextUs),
        game_patch::SpecialMessageIds::PALACE_OF_TWILIGHT,

        // Hyrule Castle
        hyruleCastleTextUs,
        sizeof(hyruleCastleTextUs),
        game_patch::SpecialMessageIds::HYRULE_CASTLE,

        // Bulblin Camp
        bulblinCampTextUs,
        sizeof(bulblinCampTextUs),
        game_patch::SpecialMessageIds::BULBLIN_CAMP,

        // This is an extra section that should go unused, and is only needed for _05_getMsgById in 05_itemMsgFunctions.cpp to
        // ensure that it can properly calculate sizeOut
        "",
        0,
        0xFFFF,
    };

    const uint32_t totalCustomMessagesUs = sizeof(entriesUs) / sizeof(MsgEntry);
    const MsgEntry charloDonationEntryUs = {charloDonationEn, sizeof(charloDonationEn), 0x0355};

    const ItemWheelMenuStrings itemWheelMenuStringsUs = {
        // areasBeingTracked
        {
            "Forest Temple",
            "Goron Mines",
            "Lakebed Temple",
            "Arbiter's Grounds",
            "Snowpeak Ruins",
            "Temple of Time",
            "City in the Sky",
            "Palace of Twilight",
            "Hyrule Castle",
            "Faron Woods",
            "Bulblin Camp",
        },

        // seedIsLoaded
        "Seed",

        // seedIsNotLoaded
        "No seed is currently loaded",

        // yes/no
        "Yes",
        "No",

        // shadowsShards
        "Fused Shadows\nMirror Shards",

        // Pumpkin
        "Pumpkin",

        // Cheese
        "Cheese",

        // Gate Keys
        "Gate Keys",

        // Areas
        "Areas",

        // Small Keys
        "Small\nKeys",

        // Big Keys
        "Big\nKeys",

        // Maps
        "Maps",

        // Compasses
        "Compasses",

        // helpText
        "Press Start\nor Z to\ntoggle\nadditional\ndata",
    };

    const ItemWheelMenuOffsets itemWheelMenuOffsetsUs {
        // Fused Shadows/Mirror Shards
        135,

        // Pumpkin
        60,

        // Yes/No
        20,
        22,

        // Cheese
        90,

        // Yes/No
        15,
        17,

        // Gate Keys
        80,

        // Yes/No
        25,
        27,

        // Headers
        // Small Keys
        155,

        // Big Keys
        70,

        // Maps
        70,

        // Compasses
        70,

        // Header values
        // Small Keys values
        16,

        // Big keys values
        // Yes/No
        5,
        7,

        // Goron Mines
        13,

        // Maps values
        // Yes/No
        7,
        9,

        // Compasses values
        // Yes/No
        30,
        32,
    };
} // namespace mod::customMessages
#endif