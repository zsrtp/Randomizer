/**	@file randomizer.cpp
 *  @brief Randomizer main class
 *
 *	@author AECX
 *	@bug No known bugs.
 */
#include <cstring>

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

namespace mod::rando
{
    // Currrently unused, so will leave here
    Randomizer::~Randomizer( void )
    {
        getConsole() << "Rando unloading...\n";

        // Clear Seed
        delete m_Seed;
    }

    KEEP_FUNC void Randomizer::onStageLoad( void )
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if ( seed = getCurrentSeed( this ), !seed )
        {
            return;
        }

        const char* stage = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mNextStage.stageValues.mStage;
        seed->LoadChecks( stage );
        game_patch::_02_modifyFoolishFieldModel();
    }

    void Randomizer::initSave( void )
    {
        m_SeedInit = m_Seed->InitSeed();
    }

    void Randomizer::overrideREL()
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if ( seed = getCurrentSeed( this ), !seed )
        {
            return;
        }

        // Local vars
        uint32_t numReplacements = seed->m_numLoadedRELChecks;
        RELCheck* relReplacements = seed->m_RELChecks;

        // If we don't have replacements just leave
        if ( !numReplacements )
            return;

        // Loop through all loaded OSModuleInfo entries and apply the specified values to the RELs already loaded.
        libtp::gc_wii::os_module::OSModuleInfo* rel = libtp::gc_wii::os_module::osModuleList.first;
        for ( ; rel; rel = rel->next )
        {
            for ( uint32_t i = 0; i < numReplacements; i++ )
            {
                if ( rel->id == relReplacements[i].moduleID )
                {
                    uint32_t offset = reinterpret_cast<uint32_t>( rel ) + relReplacements[i].offset;
                    events::performStaticASMReplacement( offset, relReplacements[i].override );
                }
            }
        }
    }

    void Randomizer::overrideDZX( libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo )
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if ( seed = getCurrentSeed( this ), !seed )
        {
            return;
        }

        using namespace libtp::tp::dzx;

        // Local vars
        uint32_t numReplacements = seed->m_numLoadedDZXChecks;
        dzxCheck* dzxReplacements = seed->m_DZXChecks;

        uint32_t numChunks = chunkTypeInfo->numChunks;
        ACTR* dzxData = reinterpret_cast<ACTR*>( chunkTypeInfo->chunkDataPtr );

        // Check if we have DZX checks to work with
        if ( numReplacements == 0 )
        {
            return;
        }

        // Loop through all chunks the game is currently loading/setting
        for ( uint32_t i = 0; i < numChunks; i++ )
        {
            // The hash in RAM right now
            uint16_t actorHash = libtp::tools::fletcher16( reinterpret_cast<uint8_t*>( &dzxData[i] ), sizeof( ACTR ) );

            // Compare to all available replacements
            for ( uint32_t j = 0; j < numReplacements; j++ )
            {
                if ( dzxReplacements[j].hash == actorHash )
                {
                    // Temporary enum for actor types
                    enum ActorTypes
                    {
                        NONE = 0,
                        HEART_PIECE,
                        TBOX,
                    };

                    // Bytearray of target ACTR struct
                    uint8_t* target = reinterpret_cast<uint8_t*>( &dzxData[i] );

                    // Replace target Actor with replacement values if != FF
                    for ( uint8_t b = 0; b < sizeof( ACTR ); b++ )
                    {
                        // Fetch replacement byte
                        uint8_t newByte = dzxReplacements[j].data[b];

                        if ( newByte != dzxReplacements[j].magicByte )
                        {
                            target[b] = newByte;
                        }
                    }

                    // Placeholders for item replacements
                    int32_t actortype = ActorTypes::NONE;
                    uint32_t item = 0xFF;

                    // Check if there is an item replacement to perform
                    if ( strncmp( dzxData[i].objectName, "htPiece", 7 ) == 0 )
                    {
                        actortype = ActorTypes::HEART_PIECE;
                        item = reinterpret_cast<ITEM*>( target )->item;
                    }
                    else if ( strncmp( dzxData[i].objectName, "tbox", 4 ) == 0 )
                    {
                        actortype = ActorTypes::TBOX;
                        item = reinterpret_cast<TRES*>( target )->item;
                    }

                    // Perform the item replacement
                    switch ( actortype )
                    {
                        case ActorTypes::HEART_PIECE:
                        {
                            reinterpret_cast<ITEM*>( target )->item = game_patch::_04_verifyProgressiveItem( this, item );
                            break;
                        }
                        case ActorTypes::TBOX:
                        {
                            reinterpret_cast<TRES*>( target )->item = game_patch::_04_verifyProgressiveItem( this, item );
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    int32_t Randomizer::getPoeItem( uint8_t flag )
    {
        for ( uint32_t i = 0; i < m_Seed->m_numLoadedPOEChecks; i++ )
        {
            if ( flag == m_Seed->m_POEChecks[i].flag )
            {
                // Return new item
                return static_cast<int32_t>( m_Seed->m_POEChecks[i].item );
            }
        }

        // Default
        return libtp::data::items::Poe_Soul;
    }

    uint8_t Randomizer::getSkyCharacter()
    {
        // Return the item id if we only have one item to pick from, otherwise, check the room to get the character we want.
        if ( m_Seed->m_numSkyBookChecks == 1 )
        {
            return m_Seed->m_SkyBookChecks[0].itemID;
        }
        else
        {
            for ( uint32_t i = 0; i < m_Seed->m_numSkyBookChecks; i++ )
            {
                if ( m_Seed->m_SkyBookChecks[i].roomID == libtp::tp::d_kankyo::env_light.currentRoom )
                {
                    return m_Seed->m_SkyBookChecks[i].itemID;
                }
            }
        }
        // default
        return libtp::data::items::Ancient_Sky_Book_Partly_Filled;
    }

    uint8_t Randomizer::getBossItem( int32_t originalItem )
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        Seed* seed;
        if ( seed = getCurrentSeed( this ), !seed )
        {
            return static_cast<uint8_t>( originalItem );
        }
        else
        {
            // There is (currently) never a situation where there are multiple boss checks on the same stage, so just return
            // the item
            return seed->m_BossChecks[0].item;
        }
    }

    void Randomizer::overrideARC( uint32_t fileAddr, FileDirectory fileDirectory, int roomNo )
    {
        // Make sure the randomizer is loaded/enabled and a seed is loaded
        rando::Seed* seed;
        if ( seed = getCurrentSeed( this ), !seed )
        {
            return;
        }

        seed->LoadARCChecks( seed->m_StageIDX, fileDirectory, roomNo );
        uint32_t numReplacements = seed->m_numLoadedArcReplacements;
        // Loop through all ArcChecks and replace the item at an offset given the fileIndex.
        for ( uint32_t i = 0; i < numReplacements; i++ )
        {
            switch ( seed->m_ArcReplacements[i].replacementType )
            {
                case rando::ArcReplacementType::Item:
                {
                    uint32_t replacementValue =
                        game_patch::_04_verifyProgressiveItem( this, seed->m_ArcReplacements[i].replacementValue );
                    *reinterpret_cast<uint8_t*>( ( fileAddr + seed->m_ArcReplacements[i].offset ) ) = replacementValue;
                    break;
                }
                case rando::ArcReplacementType::HiddenSkill:
                {
                    uint32_t adjustedFilePtr =
                        reinterpret_cast<uint32_t>( libtp::tp::d_meter2_info::g_meter2_info.mStageMsgResource );
                    uint8_t stageIDX;
                    for ( stageIDX = 0;
                          stageIDX < sizeof( libtp::data::stage::allStages ) / sizeof( libtp::data::stage::allStages[0] );
                          stageIDX++ )
                    {
                        if ( !strcmp( libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_last_stay_info
                                          .player_last_stage,
                                      libtp::data::stage::allStages[stageIDX] ) )
                        {
                            break;
                        }
                    }

                    for ( uint32_t j = 0; j < seed->m_numHiddenSkillChecks; j++ )
                    {
                        if ( ( seed->m_HiddenSkillChecks[j].stageIDX == stageIDX ) &&
                             ( seed->m_HiddenSkillChecks[j].roomID == libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file
                                                                          .player.player_return_place.link_room_id ) )
                        {
                            uint16_t msgID = game_patch::_04_verifyProgressiveItem( this, seed->m_HiddenSkillChecks[j].itemID );
                            *reinterpret_cast<uint16_t*>( adjustedFilePtr + seed->m_ArcReplacements[i].offset ) = msgID + 0x65;
                        }
                    }
                    break;
                }
                case rando::ArcReplacementType::ItemMessage:
                {
                    uint32_t replacementValue =
                        game_patch::_04_verifyProgressiveItem( this, seed->m_ArcReplacements[i].replacementValue );
                    *reinterpret_cast<uint16_t*>( ( fileAddr + seed->m_ArcReplacements[i].offset ) ) = replacementValue + 0x65;
                    break;
                }

                case rando::ArcReplacementType::AlwaysLoaded:
                {
                    // The pointer to the start of bmgres.arc is located at the value stored in mMsgDtArchive[0] + an offset
                    // of 0x64
                    uint32_t adjustedFilePtr = *reinterpret_cast<uint32_t*>(
                        reinterpret_cast<uint32_t>( libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mMsgDtArchive[0] ) +
                        0x64 );
                    uint32_t replacementValue =
                        game_patch::_04_verifyProgressiveItem( this, seed->m_ArcReplacements[i].replacementValue );
                    *reinterpret_cast<uint16_t*>( ( adjustedFilePtr + seed->m_ArcReplacements[i].offset ) ) =
                        replacementValue + 0x65;

                    break;
                }

                case rando::ArcReplacementType::MessageResource:
                {
                    uint32_t adjustedFilePtr =
                        reinterpret_cast<uint32_t>( libtp::tp::d_meter2_info::g_meter2_info.mStageMsgResource );

                    uint32_t replacementValue =
                        game_patch::_04_verifyProgressiveItem( this, seed->m_ArcReplacements[i].replacementValue );
                    *reinterpret_cast<uint16_t*>( ( adjustedFilePtr + seed->m_ArcReplacements[i].offset ) ) =
                        replacementValue + 0x65;
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    void Randomizer::overrideObjectARC( libtp::tp::d_resource::dRes_info_c* resourcePtr, const char* fileName )
    {
        m_Seed->LoadObjectARCChecks();
        uint32_t numReplacements = m_Seed->m_numLoadedObjectArcReplacements;
        uint8_t fileSize = strlen( fileName );

        // Just because the game fetches the resource info doesn't mean that it got a match.
        if ( resourcePtr->mArchive )
        {
            // Loop through all ArcChecks and replace the item at an offset given the fileIndex.
            for ( uint32_t i = 0; i < numReplacements; i++ )
            {
                if ( strncmp( fileName, m_Seed->m_ObjectArcReplacements[i].fileName, fileSize ) == 0 )
                {
                    uint32_t replacementValue =
                        game_patch::_04_verifyProgressiveItem( this, m_Seed->m_ObjectArcReplacements[i].replacementValue );

                    uint32_t archiveData =
                        *reinterpret_cast<uint32_t*>( reinterpret_cast<uint32_t>( resourcePtr->mArchive ) + 0x28 );
                    *reinterpret_cast<uint8_t*>( ( archiveData + m_Seed->m_ObjectArcReplacements[i].offset ) ) =
                        replacementValue;
                }
            }
        }
    }

    void Randomizer::overrideEventARC()
    {
        uint32_t bmgHeaderLocation = reinterpret_cast<uint32_t>( libtp::tp::d_meter2_info::g_meter2_info.mStageMsgResource );
        uint32_t messageFlowOffset = bmgHeaderLocation + *reinterpret_cast<uint32_t*>( bmgHeaderLocation + 0x8 );

        this->overrideARC( messageFlowOffset, rando::FileDirectory::Message, 0xFF );
    }

    uint8_t Randomizer::overrideBugReward( uint8_t bugID )
    {
        for ( uint32_t i = 0; i < m_Seed->m_numBugRewardChecks; i++ )
        {
            if ( bugID == m_Seed->m_BugRewardChecks[i].bugID )
            {
                // Return new item
                return m_Seed->m_BugRewardChecks[i].itemID;
            }
        }
        // Default
        return bugID;
    }

    uint8_t Randomizer::getHiddenSkillItem( uint16_t eventIndex )
    {
        for ( uint32_t i = 0; i < m_Seed->m_numHiddenSkillChecks; i++ )
        {
            if ( eventIndex == m_Seed->m_HiddenSkillChecks[i].indexNumber )
            {
                // Return new item
                return m_Seed->m_HiddenSkillChecks[i].itemID;
            }
        }
        // Default
        return libtp::data::items::Recovery_Heart;
    }
}     // namespace mod::rando