/**
 *  @brief Handler functions used by ASM injects
 */

#include "asm.h"
#include "tp/dynamic_link.h"
#include "events.h"
#include "main.h"
#include "tp/d_a_alink.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"
#include "data/items.h"
#include "data/flags.h"
#include "tp/d_a_npc.h"
#include "game_patch/game_patch.h"

namespace mod::assembly
{
    void handleDoLinkHook(libtp::tp::dynamic_link::DynamicModuleControl* dmc)
    {
        if (dmc->mModule)
        {
            events::onRELLink(randomizer, dmc);
        }
    }

    int32_t handleAdjustPoeItem(void* e_hp_class)
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(e_hp_class) + 0x77B);
        return events::onPoe(randomizer, flag);
    }

    int32_t handleAdjustAGPoeItem(void* e_po_class)
    {
        uint8_t flag = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(e_po_class) + 0x5BD);
        return events::onPoe(randomizer, flag);
    }

    void handleAdjustBugReward(uint32_t msgEventAddress, uint8_t bugID)
    {
        events::onBugReward(randomizer, msgEventAddress, bugID);
    }

    uint8_t handleAdjustSkyCharacter()
    {
        return events::onSkyCharacter(randomizer);
    }

    void handleAdjustFieldItemParams(libtp::tp::f_op_actor::fopAc_ac_c* fopAC, void* daObjLife)
    {
        events::onAdjustFieldItemParams(fopAC, daObjLife);
    }

    void handleTransformFromWolf()
    {
        libtp::tp::d_com_inf_game::dComIfG_inf_c* gameInfoPtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo;
        if (gameInfoPtr->save.save_file.player.player_status_a.currentForm == 1)
        {
            libtp::tp::d_a_alink::procCoMetamorphoseInit(gameInfoPtr->play.mPlayer);
        }
    }

    void handleAdjustIzaWolf(int32_t flag)
    {
        // We check to see if the flag being set is for the Upper Zora's River Portal as a safety precaution since we don't want
        // to set the flags too early.
        libtp::tp::d_save::dSv_info_c* savePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;
        if ((flag == 0x15) && (savePtr->save_file.player.player_status_a.currentForm == 1))
        {
            // Set the event flag to make Iza 1 available and set the memory bit for having talked to her after opening the
            // portal as human.
            events::setSaveFileEventFlag(0xB02);
            libtp::tp::d_save::onSwitch_dSv_memBit(&savePtr->memory.temp_flags, 0x37);
        }
    }

    uint8_t handleShowReekfishPath(uint8_t scent)
    {
        if ((libtp::tp::d_a_alink::checkStageName(libtp::data::stage::allStages[libtp::data::stage::StageIDs::Snowpeak])) &&
            libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                libtp::data::flags::GOT_REEKFISH_SCENT)) // If we are currently at Snowpeak and the flag for having
                                                         // smelled a Reekfish is set
        {
            return libtp::data::items::Item::Reekfish_Scent;
        }
        else
        {
            return scent;
        }
    }

    void handleAdjustCreateItemParams(void* daDitem)
    {
        events::onAdjustCreateItemParams(daDitem);
    }

    bool handleCheck60PoeReward(uint8_t poeCount)
    {
        // Check if we are getting the 60 Poe Check and that we have already gotten the 20 Poe Check.
        return ((poeCount >= 60) && libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::GOT_BOTTLE_FROM_JOVANI));
    }

    bool handleReplaceGWolfWithItem(const int16_t* l_delFlag, void* daNpcGWolf)
    {
        // The flag index is signed, but it should always be positive if this code runs
        const uint32_t flagIndex = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(daNpcGWolf) + 0xE11);
        const int16_t delFlag = l_delFlag[flagIndex];

        const bool flagIsSet = libtp::tp::d_a_npc::daNpcT_chkEvtBit(delFlag);
        if (flagIsSet)
        {
            return flagIsSet;
        }

        // Check if the player has howled at the statue for the current golden wolf
        // l_warpAppearFlag is 0xEC before l_delFlag
        const int16_t* l_warpAppearFlag = reinterpret_cast<const int16_t*>(reinterpret_cast<uint32_t>(l_delFlag) - 0xEC);

        // If appearFlag is -1, then the wolf should be spawned without howling. This is used for the Faron wolf.
        const int16_t appearFlag = l_warpAppearFlag[flagIndex];
        if ((appearFlag == -1) || libtp::tp::d_a_npc::daNpcT_chkEvtBit(appearFlag))
        {
            const uint32_t markerFlag = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(daNpcGWolf) + 0xE1E);
            events::onHiddenSkill(mod::randomizer, daNpcGWolf, delFlag, markerFlag);
        }

        return flagIsSet;
    }

    void handleGiveMasterSwordItems()
    {
        using namespace libtp::data;

        // Give the player the Master Sword replacement
        uint32_t itemToGive = randomizer->getEventItem(items::Master_Sword);
        randomizer->addItemToEventQueue(itemToGive);

        // Give the player the Shadow Crystal replacement
        itemToGive = randomizer->getEventItem(items::Shadow_Crystal);
        randomizer->addItemToEventQueue(itemToGive);

        // Set the local event flag to make the sword de-spawn and set the save file event flag.
        libtp::tp::d_save::dSv_info_c* savePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;
        libtp::tp::d_save::onEventBit(&savePtr->mTmp, 0x820);
        libtp::tp::d_save::onEventBit(&savePtr->save_file.mEvent, 0x2120);
    }

#ifdef TP_JP
    void unpatchMapGlitch(libtp::tp::d_a_alink::daAlink* d_a_alink)
    {
        d_a_alink->mNoResetFlg0 |= 0x4000;
    }
#endif
} // namespace mod::assembly