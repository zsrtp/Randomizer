
/**	@file events.h
 *  @brief Custom events
 *
 *  @author AECX
 *  @author Isaac
 *  @bug No known bugs.
 *  @todo Expand this to allow dynamic addition/removal of functions to be executed within the event function
 */

#ifndef EVENTS_H
#define EVENTS_H

#include "data/stages.h"
#include "rando/randomizer.h"
#include "tp/d_resource.h"
#include "tp/d_save.h"
#include "tp/dynamic_link.h"
#include "tp/dzx.h"
#include "tp/f_op_actor.h"

namespace mod::events
{
    typedef bool ( *CMEB )( void* );
    extern CMEB checkNpcTransform;
    /**
     * @brief Runs when loading just started
     *
     * @param randomizer Pointer to mod::randomizer
     */
    void onLoad( rando::Randomizer* randomizer );

    /**
     * @brief Runs when loading just finished
     *
     * @param randomizer Pointer to mod::randomizer
     */
    void offLoad( rando::Randomizer* randomizer );

    /**
     * @brief Runs after a module has been linked
     *
     * @param randomizer Pointer to mod::randomizer
     * @param dmc DynamicModuleControl
     */
    void onRELLink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc );

    /**
     * @brief Runs right before a module is unlinked
     *
     * @param randomizer Pointer to mod::randomizer
     * @param dmc DynamicModuleControl
     */
    void onRELUnlink( rando::Randomizer* randomizer, libtp::tp::dynamic_link::DynamicModuleControl* dmc );

    /**
     * @brief Runs when one of the DZX init functions run
     *
     * @param randomizer Pointer to mod::randomizer
     * @param chunkTypeInfo ChunkTypeInfo of DZX entries
     */
    void onDZX( rando::Randomizer* randomizer, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo );

    /**
     * @brief Runs when a Poe (e_hp, e_po) is killed
     *
     * @param flag Save flag for e_hp (normal Poes) for AG poes its [probably] the event ID; Both are unique identifiers within
     * their respective Area
     */
    int32_t onPoe( rando::Randomizer* randomizer, uint8_t flag );

    /**
     * @brief Runs when the randomizer is trying to set a flag related to learning a hidden skill.
     *
     * @param randomizer Pointer to mod::randomizer
     * @param eventIndex The offset from saveBitLabels that contains the flag being set.
     */
    void onHiddenSkill( rando::Randomizer* randomizer, uint16_t eventIndex );

    /**
     * @brief Runs when the game loads the ARC files from the game disc.
     *
     * @param randomizer Pointer to mod::randomizer.
     * @param filePtr Pointer to the file being read.
     * @param fileIndex Index of the file being read.
     */
    void onARC( rando::Randomizer* randomizer, void* data, int roomNo, rando::FileDirectory fileDirectory );

    /**
     * @brief Runs when the player selects a bug to give to Agitha
     *
     * @param randomizer Pointer to mod::randomizer.
     * @param msgEventAddress The address for the message events for the specified actor.
     * @param bugID The item ID of the bug being presented.
     */
    void onBugReward( rando::Randomizer* randomizer, uint32_t msgEventAddress, uint8_t bugID );

    /**
     * @brief Runs when the game attempts to give the player a sky character
     *
     * @param randomizer Pointer to mod::randomizer.
     */
    uint8_t onSkyCharacter( rando::Randomizer* randomizer );

    /**
     * @brief Sets a specified event bit given a specific flag
     *
     * @param flag The event flag that we want to set
     */
    void setSaveFileEventFlag( uint16_t flag );

    void onAdjustFieldItemParams( libtp::tp::f_op_actor::fopAc_ac_c* fopAC, void* daObjLife );

    void handleDungeonHeartContainer();

    bool proc_query022( void* unk1, void* unk2, int32_t unk3 );

    int32_t proc_query023( void* unk1, void* unk2, int32_t unk3 );

    bool proc_query042( void* unk1, void* unk2, int32_t unk3 );

    bool proc_isDungeonItem( libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int memBit );

    void loadCustomActors();
    void loadCustomRoomActors();
    void loadCustomRoomSCOBs();
    void handleQuickTransform();
    void handleTimeOfDayChange();
    bool checkFoolItemFreeze();

    uint16_t getPauseRupeeMax( libtp::tp::d_save::dSv_player_status_a_c* plyrStatus );

    libtp::tp::d_resource::dRes_info_c* getObjectResInfo( const char* arcName );
    bool haveItem( uint8_t item );
    bool checkMembitSaveSwitchFlag( int32_t flag );
    void drawWindow( int32_t x, int32_t y, int32_t width, int32_t height, uint32_t color );
    void drawText( const char* text, int32_t x, int32_t y, uint32_t color, float textSize );
    int32_t getCurrentAreaNodeId();
    uint8_t* getNodeMemoryFlags( const libtp::data::stage::AreaNodesID nodeId,
                                 const libtp::data::stage::AreaNodesID currentAreaNodeId );
}     // namespace mod::events
#endif