
/**	@file main.h
 *  @brief Main structure of the Randomizer
 *
 *	@author AECX
 *	@bug No known bugs.
 */

#ifndef MAIN_H
#define MAIN_H
#include <cstdint>

#include "display/console.h"
#include "rando/randomizer.h"
#include "rando/seedlist.h"
#include "tp/d_save.h"
#include "tp/dynamic_link.h"
#include "tp/dzx.h"
#include "tp/J2DPicture.h"
#include "tp/d_a_alink.h"
#include "tp/control.h"
#include "events.h"

// Game States
#define GAME_BOOT 0       // Default; At startup (should only ever be active once)
#define GAME_TITLE 1      // When user is on title screen; let them choose their seed etc.
#define GAME_ACTIVE 2     // When user is ingame and rando should be active

#ifndef DVD
// Subrel module ids
#define SUBREL_SEED_ID 0X1001
#define SUBREL_BOOT_ID 0X1002
#endif

// Seed REL actions
#define SEED_ACTION_NONE 0
#define SEED_ACTION_LOAD_SEED 1
#define SEED_ACTION_CHANGE_SEED 2
#define SEED_ACTION_FATAL 255

// May be moved somewhere else later
// Required for keeping certain unused functions/variables from being removed
#define KEEP_FUNC __attribute__( ( used, visibility( "default" ) ) )
#define KEEP_VAR __attribute__( ( visibility( "default" ) ) )

namespace mod
{
    // General public objects
    extern libtp::display::Console console;
    extern rando::Randomizer* randomizer;
    extern rando::SeedList* seedList;

    // Variables
    extern uint8_t* m_MsgTableInfo;        // Custom message string data
    extern uint32_t m_TotalMsgEntries;     // Number of currently loaded custom string
    extern libtp::tp::J2DPicture::J2DPicture* bgWindow;
    extern uint32_t lastButtonInput;
    extern bool roomReloadingState;
    extern uint32_t nextVal;
    extern bool consoleState;
    extern uint8_t gameState;
    extern void* Z2ScenePtr;
    extern bool isFoolishTrapQueued;
    extern uint8_t seedRelAction;
    extern bool walletsPatched;
    extern const char* m_DonationText;

    void hookFunctions();
    void setScreen( bool state );     // Sets visibility of console
    uint32_t rand( uint32_t* seed );
    uint32_t ulRand( uint32_t* seed, uint32_t range );
    float intToFloat( int32_t value );
    void handleInput( uint32_t inputs );
    void handleFoolishItem();

    // Inline randoIsEnabled, as it's short enough to use less memory when inlined
    inline bool randoIsEnabled( rando::Randomizer* rando )
    {
        if ( !rando )
        {
            return false;
        }

        return rando->m_Enabled;
    }

    inline rando::Seed* getCurrentSeed( rando::Randomizer* rando )
    {
        if ( !randoIsEnabled( rando ) )
        {
            return nullptr;
        }

        return rando->m_Seed;
    }

    // Function hook handlers & trampolines
    void handle_fapGm_Execute( void );
    extern void ( *return_fapGm_Execute )( void );

    // DMC (REL) Hook
    bool handle_do_link( libtp::tp::dynamic_link::DynamicModuleControl* dmc );
    extern bool ( *return_do_Link )( libtp::tp::dynamic_link::DynamicModuleControl* dmc );

    bool handle_do_unlink( libtp::tp::dynamic_link::DynamicModuleControl* dmc );
    extern bool ( *return_do_unlink )( libtp::tp::dynamic_link::DynamicModuleControl* dmc );

    // DZX Functions; Handler is lambda -> randomizer::onDZX();
    bool handle_actorInit( void* mStatus_roomControl, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4 );

    extern bool ( *return_actorInit )( void* mStatus_roomControl,
                                       libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                       int32_t unk3,
                                       void* unk4 );

    bool handle_actorInit_always( void* mStatus_roomControl,
                                  libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                  int32_t unk3,
                                  void* unk4 );

    extern bool ( *return_actorInit_always )( void* mStatus_roomControl,
                                              libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                              int32_t unk3,
                                              void* unk4 );

    bool handle_actorCommonLayerInit( void* mStatus_roomControl,
                                      libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                      int32_t unk3,
                                      void* unk4 );

    extern bool ( *return_actorCommonLayerInit )( void* mStatus_roomControl,
                                                  libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                                  int32_t unk3,
                                                  void* unk4 );

    int32_t handle_tgscInfoInit( void* stageDt, void* i_data, int32_t entryNum, void* param_3 );
    extern int32_t ( *return_tgscInfoInit )( void* stageDt, void* i_data, int32_t entryNum, void* param_3 );

    void handle_roomLoader( void* data, void* stageDt, int32_t roomNo );
    extern void ( *return_roomLoader )( void* data, void* stageDt, int32_t roomNo );

    void handle_stageLoader( void* data, void* stageDt );
    extern void ( *return_stageLoader )( void* data, void* stageDt );

    // State functions
    extern int32_t ( *return_getLayerNo_common_common )( const char* stageName, int32_t roomId, int32_t layerOverride );

    // Item creation functions. These are ran when the game displays an item though various means.
    int32_t handle_createItemForBoss( const float pos[3],
                                      int32_t item,
                                      int32_t roomNo,
                                      const int16_t rot[3],
                                      const float scale[3],
                                      float unk6,
                                      float unk7,
                                      int32_t parameters );

    extern int32_t ( *return_createItemForBoss )( const float pos[3],
                                                  int32_t item,
                                                  int32_t roomNo,
                                                  const int16_t rot[3],
                                                  const float scale[3],
                                                  float unk6,
                                                  float unk7,
                                                  int32_t parameters );

    int32_t handle_createItemForPresentDemo( const float pos[3],
                                             int32_t item,
                                             uint8_t unk3,
                                             int32_t unk4,
                                             int32_t unk5,
                                             const float unk6[3],
                                             const float unk7[3] );
    extern int32_t ( *return_createItemForPresentDemo )( const float pos[3],
                                                         int32_t item,
                                                         uint8_t unk3,
                                                         int32_t unk4,
                                                         int32_t unk5,
                                                         const float unk6[3],
                                                         const float unk7[3] );

    int32_t handle_createItemForTrBoxDemo( const float pos[3],
                                           int32_t item,
                                           int32_t itemPickupFlag,
                                           int32_t roomNo,
                                           const int16_t rot[3],
                                           const float scale[3] );

    extern int32_t ( *return_createItemForTrBoxDemo )( const float pos[3],
                                                       int32_t item,
                                                       int32_t itemPickupFlag,
                                                       int32_t roomNo,
                                                       const int16_t rot[3],
                                                       const float scale[3] );

    int32_t handle_createItemForMidBoss( const float pos[3],
                                         int32_t item,
                                         int32_t roomNo,
                                         const int16_t rot[3],
                                         const float scale[3],
                                         int32_t unk6,
                                         int32_t itemPickupFlag );

    extern int32_t ( *return_createItemForMidBoss )( const float pos[3],
                                                     int32_t item,
                                                     int32_t roomNo,
                                                     const int16_t rot[3],
                                                     const float scale[3],
                                                     int32_t unk6,
                                                     int32_t itemPickupFlag );

    // Item Wheel functions
    void handle_setLineUpItem( libtp::tp::d_save::dSv_player_item_c* );
    extern void ( *return_setLineUpItem )( libtp::tp::d_save::dSv_player_item_c* );

    // ItemGet functions. These functions handle the player and the flags set for their inventory
    int32_t handle_execItemGet( uint8_t item );
    extern int32_t ( *return_execItemGet )( uint8_t item );

    int32_t handle_checkItemGet( uint8_t item, int32_t defaultValue );
    extern int32_t ( *return_checkItemGet )( uint8_t item, int32_t defaultValue );

    // Message functions
    bool handle_setMessageCode_inSequence( libtp::tp::control::TControl* control,
                                           const void* TProcessor,
                                           uint16_t unk3,
                                           uint16_t msgId );

    extern bool ( *return_setMessageCode_inSequence )( libtp::tp::control::TControl* control,
                                                       const void* TProcessor,
                                                       uint16_t unk3,
                                                       uint16_t msgId );

    uint32_t handle_getFontCCColorTable( uint8_t colorId, uint8_t unk );
    extern uint32_t ( *return_getFontCCColorTable )( uint8_t colorId, uint8_t unk );

    uint32_t handle_getFontGCColorTable( uint8_t colorId, uint8_t unk );
    extern uint32_t ( *return_getFontGCColorTable )( uint8_t colorId, uint8_t unk );

    char handle_parseCharacter_1Byte( const char** text );
    extern char ( *return_parseCharacter_1Byte )( const char** text );

    // Query/Event functions. Various uses
    bool handle_query022( void* unk1, void* unk2, int32_t unk3 );
    extern bool ( *return_query022 )( void* unk1, void* unk2, int32_t unk3 );

    int32_t handle_query023( void* unk1, void* unk2, int32_t unk3 );
    extern int32_t ( *return_query023 )( void* unk1, void* unk2, int32_t unk3 );

    bool handle_query025( void* unk1, void* unk2, int32_t unk3 );
    extern bool ( *return_query025 )( void* unk1, void* unk2, int32_t unk3 );

    bool handle_query042( void* unk1, void* unk2, int32_t unk3 );
    extern bool ( *return_query042 )( void* unk1, void* unk2, int32_t unk3 );

    int32_t handle_query004( void* unk1, void* unk2, int32_t unk3 );
    extern int32_t ( *return_query004 )( void* unk1, void* unk2, int32_t unk3 );

    int32_t handle_query037( void* unk1, void* unk2, int32_t unk3 );
    extern int32_t ( *return_query037 )( void* unk1, void* unk2, int32_t unk3 );

    uint32_t handle_event000( void* messageFlow, void* nodeEvent, void* actrPtr );
    extern uint32_t ( *return_event000 )( void* messageFlow, void* nodeEvent, void* actrPtr );

    int32_t handle_event017( void* messageFlow, void* nodeEvent, void* actrPtr );
    extern int32_t ( *return_event017 )( void* messageFlow, void* nodeEvent, void* actrPtr );

    int32_t handle_event003( void* messageFlow, void* nodeEvent, void* actrPtr );
    extern int32_t ( *return_event003 )( void* messageFlow, void* nodeEvent, void* actrPtr );

    int32_t handle_event041( void* messageFlow, void* nodeEvent, void* actrPtr );
    extern int32_t ( *return_event041 )( void* messageFlow, void* nodeEvent, void* actrPtr );

    // Save flag functions
    bool handle_isDungeonItem( libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit );
    extern bool ( *return_isDungeonItem )( libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit );

    bool handle_chkEvtBit( uint32_t flag );
    extern bool ( *return_chkEvtBit )( uint32_t flag );

    bool handle_isEventBit( libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag );
    extern bool ( *return_isEventBit )( libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag );

    void handle_onEventBit( libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag );
    extern void ( *return_onEventBit )( libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag );

    bool handle_isSwitch_dSv_memBit( libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag );
    extern bool ( *return_isSwitch_dSv_memBit )( libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag );

    void handle_onSwitch_dSv_memBit( libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag );
    extern void ( *return_onSwitch_dSv_memBit )( libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag );

    bool handle_checkTreasureRupeeReturn( void* unk1, int32_t item );
    extern bool ( *return_checkTreasureRupeeReturn )( void* unk1, int32_t item );

    // Pause menu functions
    void handle_collect_save_open_init( uint8_t param_1 );
    extern void ( *return_collect_save_open_init )( uint8_t param_1 );

    // Link functions
    bool handle_checkBootsMoveAnime( libtp::tp::d_a_alink::daAlink* d_a_alink, int32_t param_1 );
    extern bool ( *return_checkBootsMoveAnime )( libtp::tp::d_a_alink::daAlink* d_a_alink, int32_t param_1 );

    void handle_setGetItemFace( libtp::tp::d_a_alink::daAlink* daALink, uint16_t itemID );
    extern void ( *return_setGetItemFace )( libtp::tp::d_a_alink::daAlink* daALink, uint16_t itemID );

    // Audio functions
    void handle_loadSeWave( void* Z2SceneMgr, uint32_t waveID );
    extern void ( *return_loadSeWave )( void* Z2SceneMgr, uint32_t waveID );

    // Title Screen functions
    void* handle_dScnLogo_c_dt( void* dScnLogo_c, int16_t bFreeThis );
    extern void* ( *return_dScnLogo_c_dt )( void* dScnLogo_c, int16_t bFreeThis );

}     // namespace mod
#endif