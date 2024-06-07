/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include <cstring>
#include <cstdio>

#include "cxx.h"
#include "rando/randomizer.h"
#include "data/items.h"
#include "data/stages.h"
#include "events.h"
#include "game_patch/game_patch.h"
#include "gc_wii/OSModule.h"
#include "main.h"
#include "rando/data.h"
#include "rando/seed.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_kankyo.h"
#include "tp/d_meter2_info.h"
#include "tp/dzx.h"
#include "memory.h"
#include "tp/JKRArchive.h"
#include "util/color_utils.h"
#include "util/texture_utils.h"
#include "tools.h"
#include "rando/customItems.h"

namespace mod::rando
{
    int32_t lookupTable[DvdEntryNumIdSize];

    customItems::FoolishItems foolishItems;
    GoldenWolfItemReplacement goldenWolfItemReplacement;

    uint8_t getFoolishItemModelId(uint8_t originalItem)
    {
        customItems::FoolishItems* foolishItemsPtr = &foolishItems;
        const uint8_t* foolishItemIds = foolishItemsPtr->itemIds;

        for (uint32_t i = 0; i < MAX_SPAWNED_FOOLISH_ITEMS; i++)
        {
            if (originalItem == foolishItemIds[i])
            {
                return foolishItemsPtr->itemModelId[i];
            }
        }

        return originalItem;
    }

    // Currrently unused, so will leave here
    Randomizer::~Randomizer(void)
    {
        // getConsole() << "Rando unloading...\n";

        // Clear Seed
        delete m_Seed;
    }

    KEEP_FUNC void Randomizer::onStageLoad(void)
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if (seed = getCurrentSeed(this), !seed)
        {
            return;
        }

        const char* stage = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mNextStage.mStage;
        seed->LoadChecks(stage);

        // Make sure the foolish items spawn count is reset before randomizing foolish item models
        foolishItems.spawnCount = 0;

        const int32_t stageIDX = libtp::tools::getStageIndex(stage);
        switch (stageIDX)
        {
            case libtp::data::stage::StageIDs::Hyrule_Field:
            case libtp::data::stage::StageIDs::Kakariko_Village:
            case libtp::data::stage::StageIDs::Kakariko_Graveyard:
            case libtp::data::stage::StageIDs::Fishing_Pond:
            case libtp::data::stage::StageIDs::Zoras_Domain:
            case libtp::data::stage::StageIDs::Sacred_Grove:
            case libtp::data::stage::StageIDs::Lake_Hylia:
            case libtp::data::stage::StageIDs::Bulblin_Camp:
            case libtp::data::stage::StageIDs::Outside_Castle_Town:
            case libtp::data::stage::StageIDs::Gerudo_Desert:
            case libtp::data::stage::StageIDs::Upper_Zoras_River:
            case libtp::data::stage::StageIDs::Hidden_Village:
            {
                game_patch::_02_modifyFoolishFieldModel();
                break;
            }

            case libtp::data::stage::StageIDs::Ordon_Village_Interiors:
            case libtp::data::stage::StageIDs::Kakariko_Village_Interiors:
            case libtp::data::stage::StageIDs::Castle_Town_Shops:
            case libtp::data::stage::StageIDs::Death_Mountain:
            {
                if (modifyShopModels)
                {
                    seed->loadShopModels();
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }

    void Randomizer::initSave(void)
    {
        m_SeedInit = m_Seed->InitSeed();
    }

    void Randomizer::overrideREL()
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if (seed = getCurrentSeed(this), !seed)
        {
            return;
        }

        // Local vars
        const uint32_t numReplacements = seed->m_numLoadedRELChecks;
        RELCheck* relReplacements = seed->m_RELChecks;

        // If we don't have replacements just leave
        if (!numReplacements)
            return;

        // Loop through all loaded OSModuleInfo entries and apply the specified values to the RELs already loaded.
        libtp::gc_wii::os_module::OSModuleInfo* rel = libtp::gc_wii::os_module::osModuleList.first;
        for (; rel; rel = rel->next)
        {
            for (uint32_t i = 0; i < numReplacements; i++)
            {
                RELCheck* currentRelReplacement = &relReplacements[i];
                if (rel->id == currentRelReplacement->moduleID)
                {
                    uint32_t relOverride = currentRelReplacement->override;
                    switch (static_cast<rando::ReplacementType>(currentRelReplacement->replacementType))
                    {
                        case rando::ReplacementType::Item:
                        {
                            uint32_t itemID = relOverride & 0xFF;
                            itemID = game_patch::_04_verifyProgressiveItem(this, itemID);
                            relOverride = (relOverride & 0xFFFFFF00) | itemID;
                            break;
                        }
                        case rando::ReplacementType::ItemMessage:
                        {
                            const uint32_t msgId = relOverride & 0xFFFF;
                            int32_t itemID = msgId - 0x65;
                            if ((itemID < 0) || (itemID > 0xFF))
                            {
                                itemID = 0;
                            }

                            itemID = static_cast<int32_t>(
                                game_patch::_04_verifyProgressiveItem(this, static_cast<uint32_t>(itemID)));

                            relOverride = (relOverride & 0xFFFF0000) | (itemID + 0x65);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    uint32_t offset = reinterpret_cast<uint32_t>(rel) + currentRelReplacement->offset;
                    events::performStaticASMReplacement(offset, relOverride);
                }
            }
        }
    }

    void Randomizer::overrideDZX(libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo)
    {
        using namespace libtp::tp::dzx;

        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if (seed = getCurrentSeed(this), !seed)
        {
            return;
        }

        // Local vars
        const uint32_t numReplacements = seed->m_numLoadedDZXChecks;
        DZXCheck* dzxReplacements = seed->m_DZXChecks;

        const uint32_t numChunks = chunkTypeInfo->numChunks;
        ACTR* dzxData = reinterpret_cast<ACTR*>(chunkTypeInfo->chunkDataPtr);

        // Check if we have DZX checks to work with
        if (numReplacements == 0)
        {
            return;
        }

        // Loop through all chunks the game is currently loading/setting
        for (uint32_t i = 0; i < numChunks; i++)
        {
            // The hash in RAM right now
            const uint32_t actorHash = libtp::tools::fletcher16(reinterpret_cast<uint8_t*>(&dzxData[i]), sizeof(ACTR));

            // Compare to all available replacements
            for (uint32_t j = 0; j < numReplacements; j++)
            {
                rando::DZXCheck* currentDzxReplacement = &dzxReplacements[j];
                if (currentDzxReplacement->hash == actorHash)
                {
                    // Temporary enum for actor types
                    enum ActorTypes
                    {
                        NONE = 0,
                        HEART_PIECE,
                        TBOX,
                    };

                    // Bytearray of target ACTR struct
                    uint8_t* target = reinterpret_cast<uint8_t*>(&dzxData[i]);

                    // Replace target Actor with replacement values if != FF
                    for (uint8_t b = 0; b < sizeof(ACTR); b++)
                    {
                        // Fetch replacement byte
                        const uint8_t newByte = currentDzxReplacement->data[b];

                        if (newByte != currentDzxReplacement->magicByte)
                        {
                            target[b] = newByte;
                        }
                    }

                    // Placeholders for item replacements
                    int32_t actortype = ActorTypes::NONE;
                    uint32_t item = 0xFF;

                    // Check if there is an item replacement to perform
                    if (strncmp(dzxData[i].objectName, "htPiece", 7) == 0)
                    {
                        actortype = ActorTypes::HEART_PIECE;
                        item = reinterpret_cast<ITEM*>(target)->item;
                    }
                    else if (strncmp(dzxData[i].objectName, "tbox", 4) == 0)
                    {
                        actortype = ActorTypes::TBOX;
                        item = reinterpret_cast<TRES*>(target)->item;
                    }

                    // Perform the item replacement
                    switch (actortype)
                    {
                        case ActorTypes::HEART_PIECE:
                        {
                            reinterpret_cast<ITEM*>(target)->item = game_patch::_04_verifyProgressiveItem(this, item);
                            break;
                        }
                        case ActorTypes::TBOX:
                        {
                            reinterpret_cast<TRES*>(target)->item = game_patch::_04_verifyProgressiveItem(this, item);
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    libtp::gc_wii::os_cache::DCFlushRange(&dzxData[i], sizeof(ACTR));
                }
            }
        }
    }

    int32_t Randomizer::getPoeItem(uint8_t flag)
    {
        const uint32_t numLoadedPOEChecks = m_Seed->m_numLoadedPOEChecks;
        PoeCheck* poeChecks = &m_Seed->m_PoeChecks[0];

        for (uint32_t i = 0; i < numLoadedPOEChecks; i++)
        {
            PoeCheck* currentPOECheck = &poeChecks[i];
            if (flag == currentPOECheck->flag)
            {
                // Return new item
                return static_cast<int32_t>(currentPOECheck->item);
            }
        }

        // Default
        return libtp::data::items::Poe_Soul;
    }

    uint8_t Randomizer::getSkyCharacter()
    {
        // Return the item id if we only have one item to pick from, otherwise, check the room to get the character we want.
        const uint32_t numSkyBookChecks = m_Seed->m_numSkyBookChecks;
        SkyCharacter* skyBookChecks = &m_Seed->m_SkyBookChecks[0];

        if (numSkyBookChecks == 1)
        {
            return skyBookChecks[0].itemID;
        }
        else
        {
            const int32_t currentRoom = libtp::tools::getCurrentRoomNo();
            for (uint32_t i = 0; i < numSkyBookChecks; i++)
            {
                SkyCharacter* currentSkyBookCheck = &skyBookChecks[i];
                if (currentSkyBookCheck->roomID == static_cast<uint32_t>(currentRoom))
                {
                    return currentSkyBookCheck->itemID;
                }
            }
        }

        // Default
        return libtp::data::items::Ancient_Sky_Book_Partly_Filled;
    }

    uint8_t Randomizer::getBossItem(int32_t originalItem)
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if (seed = getCurrentSeed(this), !seed)
        {
            return static_cast<uint8_t>(originalItem);
        }
        else
        {
            // There is (currently) never a situation where there are multiple boss checks on the same stage, so just return
            // the item
            return seed->m_BossChecks[0].item;
        }
    }

    uint8_t Randomizer::getEventItem(uint8_t flag)
    {
        const uint32_t numLoadedEventChecks = m_Seed->m_numLoadedEventChecks;
        const EventItem* eventChecks = &m_Seed->m_EventChecks[0];

        for (uint32_t i = 0; i < numLoadedEventChecks; i++)
        {
            const EventItem* currentEventCheck = &eventChecks[i];
            if (flag == currentEventCheck->flag)
            {
                // Return new item
                return currentEventCheck->itemID;
            }
        }

        // Currently we just use the vanilla item ID as the flag since the scope of these checks are limited at the moment.
        return flag;
    }

    void Randomizer::overrideARC(uint32_t fileAddr, FileDirectory fileDirectory, int32_t roomNo)
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        rando::Seed* seed;
        if (seed = getCurrentSeed(this), !seed)
        {
            return;
        }

        const uint8_t stageIdx = seed->m_StageIDX;
        seed->LoadARCChecks(stageIdx, fileDirectory, roomNo);

        if ((stageIdx == libtp::data::stage::StageIDs::Ordon_Village) && (fileDirectory == FileDirectory::Room))
        {
            // Unlock the right door to Bo's House
            uint32_t replacementAddress = fileAddr + 0x2F58;
            *reinterpret_cast<uint16_t*>((replacementAddress)) = 0xFFFF;
            libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint16_t));

            // Unlock the left door to Bo's House
            replacementAddress = fileAddr + 0x2F7C;
            *reinterpret_cast<uint16_t*>((replacementAddress)) = 0xFFFF;
            libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint16_t));
        }

        // Loop through all ArcChecks and replace the item at an offset given the fileIndex.
        const uint32_t numReplacements = seed->m_numLoadedArcReplacements;
        for (uint32_t i = 0; i < numReplacements; i++)
        {
            ARCReplacement* arcReplacement = &seed->m_ArcReplacements[i];
            uint32_t replacementValue = arcReplacement->replacementValue;
            const uint32_t replacementOffset = arcReplacement->offset;

            switch (seed->m_ArcReplacements[i].replacementType)
            {
                case rando::ReplacementType::Item:
                {
                    replacementValue = game_patch::_04_verifyProgressiveItem(this, replacementValue);

                    uint32_t replacementAddress = fileAddr + replacementOffset;
                    *reinterpret_cast<uint8_t*>((replacementAddress)) = replacementValue;

                    // Clear the cache for the modified value
                    libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint8_t));
                    break;
                }
                case rando::ReplacementType::ItemMessage:
                {
                    replacementValue = game_patch::_04_verifyProgressiveItem(this, replacementValue);

                    uint32_t replacementAddress = fileAddr + replacementOffset;
                    *reinterpret_cast<uint16_t*>((replacementAddress)) = replacementValue + 0x65;

                    // Clear the cache for the modified value
                    libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint16_t));
                    break;
                }
                case rando::ReplacementType::AlwaysLoaded:
                {
                    // The pointer to the start of bmgres.arc is located at the value stored in mMsgDtArchive[0] + an offset
                    // of 0x64
                    const uint32_t adjustedFilePtr = *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>(libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mMsgDtArchive[0]) + 0x64);

                    replacementValue = game_patch::_04_verifyProgressiveItem(this, replacementValue);
                    uint32_t replacementAddress = adjustedFilePtr + replacementOffset;
                    *reinterpret_cast<uint16_t*>((replacementAddress)) = replacementValue + 0x65;

                    // Clear the cache for the modified value
                    libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint16_t));

                    break;
                }
                case rando::ReplacementType::MessageResource:
                {
                    const uint32_t adjustedFilePtr =
                        reinterpret_cast<uint32_t>(libtp::tp::d_meter2_info::g_meter2_info.mStageMsgResource);

                    replacementValue = game_patch::_04_verifyProgressiveItem(this, replacementValue);
                    uint32_t replacementAddress = adjustedFilePtr + replacementOffset;
                    *reinterpret_cast<uint16_t*>((replacementAddress)) = replacementValue + 0x65;

                    // Clear the cache for the modified value
                    libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint16_t));
                    break;
                }
                case rando::ReplacementType::Instruction:
                {
                    const uint32_t replacementAddress = fileAddr + replacementOffset;
                    *reinterpret_cast<uint32_t*>((replacementAddress)) = replacementValue;

                    // Clear the cache for the modified value
                    // Assembly instructions need to clear the instruction cache as well
                    libtp::memory::clear_DC_IC_Cache(reinterpret_cast<void*>(replacementAddress), sizeof(uint32_t));
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    void Randomizer::overrideObjectARC(libtp::tp::d_resource::dRes_info_c* resourcePtr, const char* fileName)
    {
        m_Seed->LoadObjectARCChecks();
        const uint32_t fileSize = strlen(fileName);

        const uint32_t numReplacements = m_Seed->m_numLoadedObjectArcReplacements;
        ObjectArchiveReplacement* objectArcReplacements = &m_Seed->m_ObjectArcReplacements[0];

        // Just because the game fetches the resource info doesn't mean that it got a match.
        const void* mArchive = resourcePtr->mArchive;
        if (mArchive)
        {
            // Loop through all ArcChecks and replace the item at an offset given the fileIndex.
            for (uint32_t i = 0; i < numReplacements; i++)
            {
                ObjectArchiveReplacement* currentObjectArcReplacement = &objectArcReplacements[i];

                if (strncmp(fileName, currentObjectArcReplacement->fileName, fileSize) == 0)
                {
                    const uint32_t replacementValue =
                        game_patch::_04_verifyProgressiveItem(this, currentObjectArcReplacement->replacementValue);

                    const uint32_t archiveData = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(mArchive) + 0x28);

                    uint32_t replacementAddress = archiveData + currentObjectArcReplacement->offset;
                    *reinterpret_cast<uint8_t*>((replacementAddress)) = replacementValue;

                    libtp::gc_wii::os_cache::DCFlushRange(reinterpret_cast<void*>(replacementAddress), sizeof(uint8_t));
                }
            }
        }
    }

    void Randomizer::overrideEventARC()
    {
        const uint32_t bmgHeaderLocation =
            reinterpret_cast<uint32_t>(libtp::tp::d_meter2_info::g_meter2_info.mStageMsgResource);

        const uint32_t messageFlowOffset = bmgHeaderLocation + *reinterpret_cast<uint32_t*>(bmgHeaderLocation + 0x8);

        this->overrideARC(messageFlowOffset, rando::FileDirectory::Message, 0xFF);
    }

    uint8_t Randomizer::overrideBugReward(uint8_t bugID)
    {
        const uint32_t numBugRewardChecks = m_Seed->m_numBugRewardChecks;
        BugReward* bugRewardChecks = &m_Seed->m_BugRewardChecks[0];

        for (uint32_t i = 0; i < numBugRewardChecks; i++)
        {
            BugReward* currentBugRewardCheck = &bugRewardChecks[i];
            if (bugID == currentBugRewardCheck->bugID)
            {
                // Return new item
                return currentBugRewardCheck->itemID;
            }
        }

        // Default
        return bugID;
    }

    void Randomizer::getHiddenSkillItem(void* daNpcGWolfPtr, int16_t flag, uint32_t markerFlag)
    {
        const int32_t currentRoom = libtp::tools::getCurrentRoomNo();
        const uint32_t numHiddenSkillChecks = m_Seed->m_numHiddenSkillChecks;
        const uint32_t stageIDX = m_Seed->m_StageIDX;
        HiddenSkillCheck* hiddenSkillChecks = &m_Seed->m_HiddenSkillChecks[0];

        for (uint32_t i = 0; i < numHiddenSkillChecks; i++)
        {
            HiddenSkillCheck* currentHiddenSkillCheck = &hiddenSkillChecks[i];

            if (stageIDX != currentHiddenSkillCheck->stageIDX)
            {
                continue;
            }

            if (static_cast<uint32_t>(currentRoom) != currentHiddenSkillCheck->roomID)
            {
                continue;
            }

            GoldenWolfItemReplacement* goldenWolfItemReplacementPtr = &goldenWolfItemReplacement;

            // Create a freestanding actor in the Golden Wolf's place using the values from the loaded check.
            goldenWolfItemReplacementPtr->markerFlag = static_cast<uint8_t>(markerFlag);
            goldenWolfItemReplacementPtr->flag = flag;

            goldenWolfItemReplacementPtr->itemActorId =
                initCreatePlayerItem(game_patch::_04_verifyProgressiveItem(this, currentHiddenSkillCheck->itemID),
                                     0xFF,
                                     reinterpret_cast<float*>(reinterpret_cast<uint32_t>(daNpcGWolfPtr) + 0x4d0),
                                     currentRoom,
                                     nullptr,
                                     nullptr);
            break;
        }
    }

    // NOTE: This function returns dynamic memory
    BMDEntry* Randomizer::generateBmdEntries(DvdEntryNumId entryNum, uint32_t numEntries)
    {
        BMDEntry* allEntries = m_Seed->m_BmdEntries;
        BMDEntry* loadedBmdEntries = new (-sizeof(uint16_t)) BMDEntry[numEntries];
        uint32_t j = 0;

        for (uint32_t i = 0; i < numEntries; i++)
        {
            if (allEntries[i].archiveIndex == entryNum)
            {
                // Store the i'th BMDEntry into the j'th loaded BMDEntry if the entryNum matches
                memcpy(&loadedBmdEntries[j], &allEntries[i], sizeof(BMDEntry));
                j++;
            }
        }

        if (j == 0) // No matches were found or there are no entries in the seed.
        {
            delete[] loadedBmdEntries;
            return nullptr;
        }

        return loadedBmdEntries;
    }

    void Randomizer::recolorArchiveTextures(libtp::tp::m_Do_dvd_thread::mDoDvdThd_mountArchive_c* mountArchive)
    {
        using libtp::tp::JKRArchive::JKRArchive;
        using libtp::tp::JKRArchive::JKRArchive_findFsResource;
        using libtp::util::texture::findTex1InBmd;
        using libtp::util::texture::recolorCmprTexture;

        CLR0Header* clr0Header = m_Seed->m_CLR0;
        const uint32_t numEntries = clr0Header->numBmdEntries;

        for (uint32_t res = 0; res < DvdEntryNumId::DvdEntryNumIdSize; res++)
        {
            if (mountArchive->mEntryNumber != getDvdEntryNum(static_cast<DvdEntryNumId>(res)))
            {
                continue;
            }

            // The currently loaded archive is an archive we are looking for
            BMDEntry* loadedBmdEntries = generateBmdEntries(static_cast<DvdEntryNumId>(res), numEntries);
            if (!loadedBmdEntries)
            {
                continue;
            }

            // If we have a populated list, this means we have textures that we can recolor.
            for (uint32_t i = 0; i < numEntries; i++)
            {
                BMDEntry* currentBmdEntry = &loadedBmdEntries[i];
                char buf[64]; // A little extra to be safe

                switch (currentBmdEntry->archiveIndex)
                {
                    case DvdEntryNumId::ResObjectOgZORA:
                    {
                        snprintf(buf, sizeof(buf), "bmdr/%s", currentBmdEntry->bmdRes);
                        break;
                    }
                    default:
                    {
                        snprintf(buf, sizeof(buf), "bmwr/%s", currentBmdEntry->bmdRes);
                        break;
                    }
                }

                const JKRArchive::SDIFileEntry* alBmdFileEntry = JKRArchive_findFsResource(mountArchive->mArchive, buf, 0);
                if (!alBmdFileEntry)
                {
                    continue;
                }

                uint8_t* tex1Addr = findTex1InBmd(mountArchive->mArchive->mArchiveData + alBmdFileEntry->data_offset);
                if (!tex1Addr)
                {
                    continue;
                }

                switch (currentBmdEntry->recolorType)
                {
                    case 0: // CMPR
                    {
                        CMPRTextureEntry* bmdTextures = reinterpret_cast<CMPRTextureEntry*>(
                            reinterpret_cast<uint32_t>(clr0Header) + currentBmdEntry->textureListOffset);

                        for (uint32_t j = 0; j < currentBmdEntry->numTextures; j++)
                        {
                            CMPRTextureEntry* currentTexture = &bmdTextures[j];

                            recolorCmprTexture(tex1Addr,
                                               currentTexture->textureName,
                                               reinterpret_cast<uint8_t*>(&currentTexture->rgba));
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }

            delete[] loadedBmdEntries;
        }
    }

    void Randomizer::replaceWolfLockDomeColor(libtp::tp::d_a_alink::daAlink* linkActrPtr)
    {
        RawRGBTable* rawRGBListPtr = m_Seed->m_RawRGBTable;
        if (rawRGBListPtr->wolfDomeAttackColor != 0xFFFFFFFF) // Don't do anything if the value is default
        {
            uint8_t* domeRGBA = reinterpret_cast<uint8_t*>(&rawRGBListPtr->wolfDomeAttackColor);
            uint8_t** chromaRegisterTable = reinterpret_cast<uint8_t**>(&linkActrPtr->tevRegKey->chromaRPtr);

            for (uint32_t i = 0; i < 3; i++)
            {
                uint8_t* currentTable = chromaRegisterTable[i];
                const uint8_t currentColor = domeRGBA[i];

                currentTable[0x3] = currentColor;  // Set Alpha for the ring base
                currentTable[0x13] = currentColor; // Set Alpha for ring wave 1
                currentTable[0x23] = currentColor; // Set Alpha for ring wave 2
                currentTable[0xB] = currentColor;  // Set Alpha for darkworld ring base
                currentTable[0x1B] = currentColor; // Set Alpha for darkworld ring wave 1
                currentTable[0x2B] = currentColor; // Set Alpha for darkworld ring wave 2
            }
        }
    }

    void Randomizer::addItemToEventQueue(uint32_t itemToAdd)
    {
        using namespace libtp::tp;

        uint8_t* reserveBytesPtr = d_com_inf_game::dComIfG_gameInfo.save.save_file.reserve.unk;
        for (uint32_t i = 0; i < GIVE_PLAYER_ITEM_RESERVED_BYTES; i++)
        {
            if (reserveBytesPtr[i] == 0)
            {
                reserveBytesPtr[i] = static_cast<uint8_t>(itemToAdd);
                break;
            }
        }
    }
} // namespace mod::rando