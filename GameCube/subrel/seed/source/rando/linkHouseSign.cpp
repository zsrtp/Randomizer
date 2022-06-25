#include "rando/linkHouseSign.h"
#include "rando/seed.h"
#include "tp/resource.h"
#include "cxx.h"

#ifdef TP_EU
#include "tp/d_s_logo.h"
#endif

#include <cstdint>
#include <cstring>

namespace mod::link_house_sign
{
    // Set up an array to hold each area's color id
    const uint8_t areaColorIds[TOTAL_POSSIBLE_DUNGEONS] = { MSG_COLOR_GREEN_HEX,
                                                            MSG_COLOR_RED_HEX,
                                                            CUSTOM_MSG_COLOR_BLUE_HEX,
                                                            MSG_COLOR_ORANGE_HEX,
                                                            MSG_COLOR_LIGHT_BLUE_HEX,
                                                            CUSTOM_MSG_COLOR_DARK_GREEN_HEX,
                                                            MSG_COLOR_YELLOW_HEX,
                                                            MSG_COLOR_PURPLE_HEX };

#ifndef TP_JP
    // English
    const char* dungeonsUs[TOTAL_POSSIBLE_DUNGEONS] = {
        "Forest Temple",
        "Goron Mines",
        "Lakebed Temple",
        "Arbiter's Grounds",
        "Snowpeak Ruins",
        "Temple of Time",
        "City in the Sky",
        "Palace of Twilight",
    };

    const char* noDungeonsRequiredUs = "No dungeons required";
#else
    // Japanese
    const char* dungeonsJp[TOTAL_POSSIBLE_DUNGEONS] = {
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
    };

    // ダンジョンは必要ない
    const char* noDungeonsRequiredJp = "\x83\x5F\x83\x93\x83\x57\x83\x87\x83\x93\x82\xCD\x95\x4B\x97\x76\x82\xC8\x82\xA2";
#endif

#ifdef TP_EU
    // German
    const char* dungeonsDe[TOTAL_POSSIBLE_DUNGEONS] = {
        // Forest Temple
        // Waldschrein
        "\x57\x61\x6c\x64\x73\x63\x68\x72\x65\x69\x6e",

        // Goron Mines
        // Minen der Goronen
        "\x4d\x69\x6e\x65\x6e\x20\x64\x65\x72\x20\x47\x6f\x72\x6f\x6e\x65\x6e",

        // Lakebed Temple
        // Seeschrein
        "\x53\x65\x65\x73\x63\x68\x72\x65\x69\x6e",

        // Arbiter's Grounds
        // Wüstenburg
        "\x57\xfc\x73\x74\x65\x6e\x62\x75\x72\x67",

        // Snowpeak Ruins
        // Bergruine
        "\x42\x65\x72\x67\x72\x75\x69\x6e\x65",

        // Temple of Time
        // Zeitschrein
        "\x5a\x65\x69\x74\x73\x63\x68\x72\x65\x69\x6e",

        // City in the Sky
        // Kumula
        "\x4b\x75\x6d\x75\x6c\x61",

        // Palace of Twilight
        // Schattenpalast
        "\x53\x63\x68\x61\x74\x74\x65\x6e\x70\x61\x6c\x61\x73\x74",
    };

    // Kein Dungeon erforderlich
    const char* noDungeonsRequiredDe =
        "\x4B\x65\x69\x6E\x20\x44\x75\x6E\x67\x65\x6F\x6E\x20\x65\x72\x66\x6F\x72\x64\x65\x72\x6C\x69\x63\x68";

    // French
    const char* dungeonsFr[TOTAL_POSSIBLE_DUNGEONS] = {
        // Forest Temple
        // Temple Sylvestre
        "\x54\x65\x6d\x70\x6c\x65\x20\x53\x79\x6c\x76\x65\x73\x74\x72\x65",

        // Goron Mines
        // Mine Goron
        "\x4d\x69\x6e\x65\x20\x47\x6f\x72\x6f\x6e",

        // Lakebed Temple
        // Temple Abyssal
        "\x54\x65\x6d\x70\x6c\x65\x20\x41\x62\x79\x73\x73\x61\x6c",

        // Arbiter's Grounds
        // Tour du Jugement
        "\x54\x6f\x75\x72\x20\x64\x75\x20\x4a\x75\x67\x65\x6d\x65\x6e\x74",

        // Snowpeak Ruins
        // Ruines des Pics Blancs
        "\x52\x75\x69\x6e\x65\x73\x20\x64\x65\x73\x20\x50\x69\x63\x73\x20\x42\x6c\x61\x6e\x63\x73",

        // Temple of Time
        // Temple du Temps
        "\x54\x65\x6d\x70\x6c\x65\x20\x64\x75\x20\x54\x65\x6d\x70\x73",

        // City in the Sky
        // Célestia
        "\x43\xe9\x6c\x65\x73\x74\x69\x61",

        // Palace of Twilight
        // Palais du Crépuscule
        "\x50\x61\x6c\x61\x69\x73\x20\x64\x75\x20\x43\x72\xe9\x70\x75\x73\x63\x75\x6c\x65",
    };

    // Aucuns donjons requis
    const char* noDungeonsRequiredFr = "\x41\x75\x63\x75\x6E\x73\x20\x64\x6F\x6E\x6A\x6F\x6E\x73\x20\x72\x65\x71\x75\x69\x73";

    // Spanish
    const char* dungeonsSp[TOTAL_POSSIBLE_DUNGEONS] = {
        // Forest Temple
        // Templo del Bosque
        "\x54\x65\x6D\x70\x6C\x6F\x20\x64\x65\x6C\x20\x42\x6F\x73\x71\x75\x65",

        // Goron Mines
        // Minas de los Goron
        "\x4D\x69\x6E\x61\x73\x20\x64\x65\x20\x6C\x6F\x73\x20\x47\x6F\x72\x6F\x6E",

        // Lakebed Temple
        // Santuario del Lago
        "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x20\x4C\x61\x67\x6F",

        // Arbiter's Grounds
        // Patíbulo del Desierto
        "\x50\x61\x74\xED\x62\x75\x6C\x6F\x20\x64\x65\x6C\x20\x44\x65\x73\x69\x65\x72\x74\x6F",

        // Snowpeak Ruins
        // Ruinas del Pico Nevado
        "\x52\x75\x69\x6E\x61\x73\x20\x64\x65\x6C\x20\x50\x69\x63\x6F\x20\x4E\x65\x76\x61\x64\x6F",

        // Temple of Time
        // Templo del Tiempo
        "\x54\x65\x6D\x70\x6C\x6F\x20\x64\x65\x6C\x20\x54\x69\x65\x6D\x70\x6F",

        // City in the Sky
        // Celestia
        "\x43\x65\x6C\x65\x73\x74\x69\x61",

        // Palace of Twilight
        // Palacio del Crepúsculo
        "\x50\x61\x6C\x61\x63\x69\x6F\x20\x64\x65\x6C\x20\x43\x72\x65\x70\xFA\x73\x63\x75\x6C\x6F",
    };

    // Sin mazmorras requeridas
    const char* noDungeonsRequiredSp =
        "\x53\x69\x6E\x20\x6D\x61\x7A\x6D\x6F\x72\x72\x61\x73\x20\x72\x65\x71\x75\x65\x72\x69\x64\x61\x73";

    // Italian
    const char* dungeonsIt[TOTAL_POSSIBLE_DUNGEONS] = {
        // Forest Temple
        // Santuario della foresta
        "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x6C\x61\x20\x66\x6F\x72\x65\x73\x74\x61",

        // Goron Mines
        // Miniera dei Goron
        "\x4D\x69\x6E\x69\x65\x72\x61\x20\x64\x65\x69\x20\x47\x6F\x72\x6F\x6E",

        // Lakebed Temple
        // Santuario nel lago
        "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x6E\x65\x6C\x20\x6C\x61\x67\x6F",

        // Arbiter's Grounds
        // Patibolo del deserto
        "\x50\x61\x74\x69\x62\x6F\x6C\x6F\x20\x64\x65\x6C\x20\x64\x65\x73\x65\x72\x74\x6F",

        // Snowpeak Ruins
        // Rovine sul ghiacciaio
        "\x52\x6F\x76\x69\x6E\x65\x20\x73\x75\x6C\x20\x67\x68\x69\x61\x63\x63\x69\x61\x69\x6F",

        // Temple of Time
        // Santuario del tempo
        "\x53\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x64\x65\x6C\x20\x74\x65\x6D\x70\x6F",

        // City in the Sky
        // Città eterea
        "\x43\x69\x74\x74\xE0\x20\x65\x74\x65\x72\x65\x61",

        // Palace of Twilight
        // Palazzo del crepuscolo
        "\x50\x61\x6C\x61\x7A\x7A\x6F\x20\x64\x65\x6C\x20\x63\x72\x65\x70\x75\x73\x63\x6F\x6C\x6F",
    };

    // Nessun santuario richiesto
    const char* noDungeonsRequiredIt =
        "\x4E\x65\x73\x73\x75\x6E\x20\x73\x61\x6E\x74\x75\x61\x72\x69\x6F\x20\x72\x69\x63\x68\x69\x65\x73\x74\x6F";
#endif

    void createRequiredDungeonsString( rando::Seed* seed, uint32_t requiredDungeonFlags )
    {
        // Make sure a seed is actually loaded
        if ( !seed )
        {
            return;
        }

        // Get the dungeon strings array to use
        const char** dungeons;
        const char* noDungeonsRequired;
#ifdef TP_US
        dungeons = dungeonsUs;
        noDungeonsRequired = noDungeonsRequiredUs;
#elif defined TP_JP
        dungeons = dungeonsJp;
        noDungeonsRequired = noDungeonsRequiredJp;
#elif defined TP_EU
        using namespace libtp::tp::d_s_logo;

        Languages currentLanguage = getPalLanguage2( nullptr );
        switch ( currentLanguage )
        {
            case Languages::uk:
            default:     // The language is invalid/unsupported, so the game defaults to English
            {
                dungeons = dungeonsUs;
                noDungeonsRequired = noDungeonsRequiredUs;
                break;
            }
            case Languages::de:
            {
                dungeons = dungeonsDe;
                noDungeonsRequired = noDungeonsRequiredDe;
                break;
            }
            case Languages::fr:
            {
                dungeons = dungeonsFr;
                noDungeonsRequired = noDungeonsRequiredFr;
                break;
            }
            case Languages::it:
            {
                dungeons = dungeonsIt;
                noDungeonsRequired = noDungeonsRequiredIt;
                break;
            }
            case Languages::sp:
            {
                dungeons = dungeonsSp;
                noDungeonsRequired = noDungeonsRequiredSp;
                break;
            }
        }
#endif
        // Get the strings to write and the total length used for the strings
        const char* requiredDungeons[TOTAL_POSSIBLE_DUNGEONS];
        char requiredDungeonsColor[TOTAL_POSSIBLE_DUNGEONS];

        uint32_t requiredDungeonsLength = 0;
        uint32_t totalStringsLength = 0;

        const uint8_t* areaColors = areaColorIds;

        // It's possible that there will be no required dungeons
        constexpr uint32_t maxBitsValue = ( 1 << TOTAL_POSSIBLE_DUNGEONS ) - 1;
        if ( ( requiredDungeonFlags & maxBitsValue ) != 0 )
        {
            // At least one dungeon is required
            for ( uint32_t i = 0; i < TOTAL_POSSIBLE_DUNGEONS; i++ )
            {
                if ( requiredDungeonFlags & ( 1 << i ) )
                {
                    const char* currentDungeon = dungeons[i];

                    requiredDungeons[requiredDungeonsLength] = currentDungeon;
                    requiredDungeonsColor[requiredDungeonsLength] = static_cast<char>( areaColors[i] );
                    requiredDungeonsLength++;

                    totalStringsLength += strlen( currentDungeon );
                }
            }
        }
        else
        {
            // No dungeons are required
            requiredDungeons[0] = noDungeonsRequired;
            requiredDungeonsColor[0] = MSG_COLOR_WHITE_HEX;
            requiredDungeonsLength = 1;

            totalStringsLength += strlen( noDungeonsRequired );
        }

        // Get the font size command string and it's length
        // Subtract one to remove the NULL terminator since the command is not NULL terminated
        const char* fontSizeString = MSG_FONT_SIZE( "\x45" );
        constexpr uint32_t fontSizeStringLength = sizeof( MSG_FONT_SIZE( "\x45" ) ) - 1;

        // Account for the string having the size command
        totalStringsLength += fontSizeStringLength;

        // Get the size of the color command excluding the NULL terminator
        // Subtract one to remove the NULL terminator since the command is not NULL terminated
        constexpr uint32_t colorCommandLength = sizeof( MSG_COLOR( MSG_COLOR_WHITE ) ) - 1;

        // Account for each string having a color command
        totalStringsLength += requiredDungeonsLength * colorCommandLength;

        // Account for the newlines between each string
        totalStringsLength += requiredDungeonsLength - 1;

        // Allocate memory for the strings
        // Add one to account for the NULL terminator
        char* buf = new ( sizeof( char ) ) char[totalStringsLength + 1];

        // Set up a variable to keep track of how many characters were written to the buffer
        uint32_t writtenSize = 0;

        // Set the font size for the string
        // Subtract one to remove the NULL terminator since the command is not NULL terminated
        memcpy( buf, fontSizeString, fontSizeStringLength );

        // Increment writtenSize to go to the next string
        writtenSize += fontSizeStringLength;

        // Get the color command string
        // Must use memcpy instead of strncpy since message commands have NULL characters
        char colorCommand[colorCommandLength];
        memcpy( colorCommand, MSG_COLOR( MSG_COLOR_WHITE ), colorCommandLength );

        // Write each string to the buffer
        for ( uint32_t i = 0; i < requiredDungeonsLength; i++ )
        {
            // Replace the current color with the color for the current area
            colorCommand[colorCommandLength - 1] = requiredDungeonsColor[i];

            // Write the color command for the current string
            // Must use memcpy instead of strncpy since message commands have NULL characters
            memcpy( &buf[writtenSize], colorCommand, colorCommandLength );

            // Increment writtenSize to go to the next string
            writtenSize += colorCommandLength;

            // Get the length of the current string
            const char* currentString = requiredDungeons[i];
            uint32_t currentStringLength = strlen( currentString );

            // Copy the current string to the buffer
            // Must use memcpy instead of strncpy since message commands have NULL characters
            memcpy( &buf[writtenSize], currentString, currentStringLength );

            // Increment writtenSize to go to the next string
            writtenSize += currentStringLength;

            // Apply a newline to go to the next line
            buf[writtenSize++] = '\n';
        }

        // Make sure the string is properly NULL terminated
        // Subtract one to overwrite the extra newline
        buf[writtenSize - 1] = '\0';

        // Assign the buffer
        seed->m_RequiredDungeons = buf;
    }
}     // namespace mod::link_house_sign