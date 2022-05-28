#include "main.h"
#include "patch.h"

#include "tp/resource.h"

#include <cstdint>

namespace mod::customMessages
{
    MSG_BEGIN( forestSmallKey )
    MSG_SPEED( MSG_SPEED_FAST )
    "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au \n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "Temple Sylvestre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( minesSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée aux\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Mines Goron"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( lakebedSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au \n"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Temple Abyssal"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( arbitersSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée dans la\n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Tour du Jugement"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( snowpeakSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée aux\n"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Ruines des Pics Blancs"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( timeSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au \n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Temple du Temps"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( citySmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée à\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Célestia"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( palaceSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Palais du Crépuscule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( hyruleSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Château d'Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( campSmallKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "petite clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Camp Bulblin"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( shadowCrystal )
        MSG_SPEED(MSG_SPEED_SLOW)
        "Vous obtenez le "
        MSG_COLOR(MSG_COLOR_RED)
        "Crystal Maudit"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nLa sombre manifestation des\npouvoirs de Xanto qui permet\nde se transformer à volonté!"
    MSG_END()
    MSG_BEGIN( forestDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient au\n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "Temple Sylvestre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( minesDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient aux\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Mines Goron"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( lakebedDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Temple Abyssal"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( arbitersDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient à la\n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Tour du Jugement"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( snowpeakDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient aux\n"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Ruines des Pics Blancs"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( timeDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Temple du Temps"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( cityDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient à\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Célestia"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( palaceDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient au\n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Palais du Crépuscule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( hyruleDungeonMap )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "carte de\ndonjon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Elle appartient au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Château d'Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( forestCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient au \n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "Temple Sylvestre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( minesCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient aux \n"
        MSG_COLOR(MSG_COLOR_RED)
        "Mines Goron"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( lakebedCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient au \n"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Temple Abyssal"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( arbitersCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient à la \n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Tour du Jugement"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( snowpeakCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient aux \n"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "Ruines des Pics Blancs"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( timeCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient au \n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Temple du Temps"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( cityCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient à "
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Célestia"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( palaceCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient au \n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Palais du Crépuscule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( hyruleCompass )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez une "
        MSG_COLOR(MSG_COLOR_RED)
        "boussole"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle appartient au \n"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Château d'Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( forestBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(MSG_COLOR_GREEN)
        "Temple Sylvestre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( lakebedBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "Temple Abyssal"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( arbitersBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée dans la\n"
        MSG_COLOR(MSG_COLOR_ORANGE)
        "Tour du Jugement"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( timeBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "Temple du Temps"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( cityBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée à\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "Célestia"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( palaceBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "Palais du Crépuscule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( hyruleBigKey )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez "
        MSG_COLOR(MSG_COLOR_RED)
        "la grande clé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut être utilisée au\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_SILVER)
        "Château d'Hyrule"
        MSG_COLOR(MSG_COLOR_WHITE)
        "."
    MSG_END()
    MSG_BEGIN( endingBlow )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris le "
        MSG_COLOR(MSG_COLOR_RED)
        "Coup de\nGrâce"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( shieldAttack )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris la "
        MSG_COLOR(MSG_COLOR_RED)
        "Charge\nBouclier"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( backSlice )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris le "
        MSG_COLOR(MSG_COLOR_RED)
        "Coup à\nRevers"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( helmSplitter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris le "
        MSG_COLOR(MSG_COLOR_RED)
        "\nBrise-Casque"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( mortalDraw )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris le "
        MSG_COLOR(MSG_COLOR_RED)
        "Coup\nÉclair"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( jumpStrike )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris le "
        MSG_COLOR(MSG_COLOR_RED)
        "Coup\nPlongé"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( greatSpin )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez appris "
        MSG_COLOR(MSG_COLOR_RED)
        "l'Attaque\nTourbillon"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( poweredRod )
        MSG_SPEED(MSG_SPEED_FAST)
        "Le "
        MSG_COLOR(MSG_COLOR_RED)
        "bâton Anima "
        MSG_COLOR(MSG_COLOR_WHITE)
        "a recouvré ses\npouvoirs magiques! Il peut\nmaintenant être utilisé pour\ninsuffler la vie aux statues\ndans le présent!"
    MSG_END()
    MSG_BEGIN( firstCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez trouvé le premier\n"
        MSG_COLOR(MSG_COLOR_RED)
        "glyphe célestien"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Vous avez\ndéchiffré un des mots manquants\ndes anciens écrits célestiens!"
    MSG_END()
    MSG_BEGIN( secondCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez trouvé le second\n"
        MSG_COLOR(MSG_COLOR_RED)
        "glyphe célestien"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Vous avez\ndéchiffré un des mots manquants\ndes anciens écrits célestiens!"
    MSG_END()
    MSG_BEGIN( thirdCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez trouvé le troisième\n"
        MSG_COLOR(MSG_COLOR_RED)
        "glyphe célestien"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Vous avez\ndéchiffré un des mots manquants\ndes anciens écrits célestiens!"
    MSG_END()
    MSG_BEGIN( fourthCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez trouvé le quatrième\n"
        MSG_COLOR(MSG_COLOR_RED)
        "glyphe célestien"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Vous avez\ndéchiffré un des mots manquants\ndes anciens écrits célestiens!"
    MSG_END()
    MSG_BEGIN( fifthCharacter )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous avez trouvé le cinquième\n"
        MSG_COLOR(MSG_COLOR_RED)
        "glyphe célestien"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Vous avez\ndéchiffré un des mots manquants\ndes anciens écrits célestiens!"
    MSG_END()
    MSG_BEGIN( firstFusedShadow )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez un "
        MSG_COLOR(MSG_COLOR_RED)
        "Cristal d'Ombre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nSa surface semble être\nrecouverte par "
        MSG_COLOR(MSG_COLOR_GREEN)
        "de la mousse"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END()
    MSG_BEGIN( secondFusedShadow )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez un second\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Cristal d'Ombre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Il émane "
        MSG_COLOR(MSG_COLOR_RED)
        "une\ndouce chaleur "
        MSG_COLOR(MSG_COLOR_WHITE)
        "sur vos mains.."
    MSG_END()
    MSG_BEGIN( thirdFusedShadow )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez le dernier\n"
        MSG_COLOR(MSG_COLOR_RED)
        "Cristal d'Ombre"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Une forte\n"
        MSG_COLOR(CUSTOM_MSG_COLOR_BLUE)
        "odeur de poisson "
        MSG_COLOR(MSG_COLOR_WHITE)
        "s'en dégage.."
    MSG_END()
    MSG_BEGIN( secondMirrorShard )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez le second fragment\ndu "
        MSG_COLOR(MSG_COLOR_RED)
        "Miroir des Ombres"
        MSG_COLOR(MSG_COLOR_WHITE)
        "! Il est\n"
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "un peu froid "
        MSG_COLOR(MSG_COLOR_WHITE)
        "et brille de\nmille feux.."
    MSG_END()
    MSG_BEGIN( thirdMirrorShard )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez le troisième\nfragment du "
        MSG_COLOR(MSG_COLOR_RED)
        "Miroir des Ombres"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nIl est très sale et "
        MSG_COLOR(CUSTOM_MSG_COLOR_DARK_GREEN)
        "recouvert\nde toiles"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END()
    MSG_BEGIN( fourthMirrorShard )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez le dernier\nfragment du "
        MSG_COLOR(MSG_COLOR_RED)
        "Miroir des Ombres"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nIl est encore plus\n"
        MSG_COLOR(MSG_COLOR_YELLOW)
        "léger que l'air"
        MSG_COLOR(MSG_COLOR_WHITE)
        ".."
    MSG_END()
    MSG_BEGIN( foolishItem )
        MSG_SPEED(MSG_SPEED_FAST)
        "Le "
        MSG_COLOR(MSG_COLOR_LIGHT_BLUE)
        "blizzard "
        MSG_COLOR(MSG_COLOR_WHITE)
        "souffle.."
    MSG_END()
    MSG_BEGIN( talkToMidna )
        "Qu'est-ce qu'il y a, "
        MSG_PLYR_NAME
        "?"
        MSG_OPTION_LIST(MSG_OPTION_1)
        "Je veux me transformer\n"
        MSG_OPTION_LIST(MSG_OPTION_2)
        "Je veux me téléporter\n"
        MSG_OPTION_LIST(MSG_OPTION_3)
        "Changer l'heure de la journée"
    MSG_END()
    MSG_BEGIN( bigWallet )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez la "
        MSG_COLOR(MSG_COLOR_RED)
        "Grande Bourse"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut contenir jusqu'à\n"
        MSG_COLOR(MSG_COLOR_RED)
        "5,000 rubis"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()
    MSG_BEGIN( giantWallet )
        MSG_SPEED(MSG_SPEED_FAST)
        "Vous obtenez la "
        MSG_COLOR(MSG_COLOR_RED)
        "Bourse Géante"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!\nElle peut contenir jusqu'à\n"
        MSG_COLOR(MSG_COLOR_PURPLE)
        "9,999 rubis"
        MSG_COLOR(MSG_COLOR_WHITE)
        "!"
    MSG_END()

}     // namespace mod::customMessages