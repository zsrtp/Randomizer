
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
#include "tp/d_stage.h"
#include "tp/control.h"
#include "Z2AudioLib/Z2SceneMgr.h"
#include "Z2AudioLib/Z2SeqMgr.h"
#include "events.h"
#include "tp/d_resource.h"
#include "tp/JKRMemArchive.h"
#include "tp/m_Do_dvd_thread.h"
#include "tp/d_meter2_info.h"
#include "tp/d_menu_fmap2D.h"
#include "tp/d_gameover.h"
#include "tp/d_shop_system.h"
#include "tp/f_op_actor.h"
#include "tp/d_msg_flow.h"

#ifdef TP_EU
#include "tp/d_s_logo.h"
#endif

// Number of lines that should not be cleared when flushing the screen
#define CONSOLE_PROTECTED_LINES 4

// Game States
#define GAME_BOOT 0   // Default; At startup (should only ever be active once)
#define GAME_TITLE 1  // When user is on title screen; let them choose their seed etc.
#define GAME_ACTIVE 2 // When user is ingame and rando should be active

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

// Converting item ids to msg ids and vice versa
#define ITEM_TO_ID(item) (item + 0x64)
#define ID_TO_ITEM(msgId) (msgId - 0x64)

// May be moved somewhere else later
// Required for keeping certain unused functions/variables from being removed
#define KEEP_FUNC __attribute__((used, visibility("default")))
#define KEEP_VAR __attribute__((visibility("default")))

namespace mod
{
    enum EventItemStatus : uint8_t
    {
        QUEUE_EMPTY = 0,
        ITEM_IN_QUEUE = 1,
        CLEAR_QUEUE = 2,
    };

    // General public objects
    extern libtp::display::Console* console;
    extern rando::Randomizer* randomizer;
    extern rando::SeedList* seedList;

    extern void* z2ScenePtr;
    extern uint32_t randState;

    // Variables
    extern uint8_t* m_MsgTableInfo;     // Custom message string data
    extern uint8_t* m_HintMsgTableInfo; // Custom message string data
    extern libtp::tp::J2DPicture::J2DPicture* bgWindow;
    extern uint16_t lastButtonInput;
    extern uint16_t m_TotalMsgEntries;     // Number of currently loaded custom string
    extern uint16_t m_TotalHintMsgEntries; // Number of currently loaded custom string
    extern bool roomReloadingState;
    extern bool consoleState;
    extern uint8_t gameState;
    extern bool walletsPatched;
    extern uint8_t seedRelAction;
    extern bool modifyShopModels;
    extern bool instantTextEnabled;
    extern bool increaseSpinnerSpeed;
    extern bool transformAnywhereEnabled;
    extern uint8_t damageMultiplier;
    extern bool bonksDoDamage;
    extern EventItemStatus giveItemToPlayer;

#ifdef TP_EU
    extern libtp::tp::d_s_logo::Languages currentLanguage;
#endif

    rando::Seed* getCurrentSeed(rando::Randomizer* rando);
    void setScreen(bool state); // Sets visibility of console
    bool checkButtonsPressedThisFrame(uint32_t buttons);
    bool checkButtonCombo(uint32_t combo, bool checkAnalog);
    float intToFloat(int32_t value);
    void handleInput(uint32_t inputs);
    void initGiveItemToPlayer(libtp::tp::d_a_alink::daAlink* linkMapPtr);
    void handleFoolishItem();
    void handleBonkDamage();

    // Inline getConsole, as it's just a shortcut to get a reference to the console variable
    inline libtp::display::Console& getConsole()
    {
        return *mod::console;
    }

    // Inline randoIsEnabled, as it's short enough to use less memory when inlined
    inline bool randoIsEnabled(rando::Randomizer* rando)
    {
        if (!rando)
        {
            return false;
        }

        return rando->m_Enabled;
    }

    int32_t initCreatePlayerItem(uint32_t itemID,
                                 uint32_t flag,
                                 const float pos[3],
                                 int32_t roomNo,
                                 const int16_t rot[3],
                                 const float scale[3]);

    // Subrel functions
    void hookFunctions();
    void initRandState();
    void initArcLookupTable();
    void writeCodehandlerToMemory();

    // Function hook handlers & trampolines
    void handle_fapGm_Execute(void);
    extern void (*return_fapGm_Execute)(void);

    // DMC (REL) Hook
    bool handle_do_unlink(libtp::tp::dynamic_link::DynamicModuleControl* dmc);
    extern bool (*return_do_unlink)(libtp::tp::dynamic_link::DynamicModuleControl* dmc);

    // DZX Functions; Handler is lambda -> randomizer::onDZX();
    bool handle_actorInit(void* mStatus_roomControl, libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo, int32_t unk3, void* unk4);

    extern bool (*return_actorInit)(void* mStatus_roomControl,
                                    libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                    int32_t unk3,
                                    void* unk4);

    bool handle_actorInit_always(void* mStatus_roomControl,
                                 libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                 int32_t unk3,
                                 void* unk4);

    extern bool (*return_actorInit_always)(void* mStatus_roomControl,
                                           libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                           int32_t unk3,
                                           void* unk4);

    bool handle_actorCommonLayerInit(void* mStatus_roomControl,
                                     libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                     int32_t unk3,
                                     void* unk4);

    extern bool (*return_actorCommonLayerInit)(void* mStatus_roomControl,
                                               libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                               int32_t unk3,
                                               void* unk4);

    void handle_dComIfGp_setNextStage(const char* stage,
                                      int16_t point,
                                      int8_t roomNo,
                                      int8_t layer,
                                      float lastSpeed,
                                      uint32_t lastMode,
                                      int32_t setPoint,
                                      int8_t wipe,
                                      int16_t lastAngle,
                                      int32_t param_9,
                                      int32_t wipSpeedT);

    extern void (*return_dComIfGp_setNextStage)(const char* stage,
                                                int16_t point,
                                                int8_t roomNo,
                                                int8_t layer,
                                                float lastSpeed,
                                                uint32_t lastMode,
                                                int32_t setPoint,
                                                int8_t wipe,
                                                int16_t lastAngle,
                                                int32_t param_9,
                                                int32_t wipSpeedT);

    int32_t handle_tgscInfoInit(void* stageDt, void* i_data, int32_t entryNum, void* param_3);
    extern int32_t (*return_tgscInfoInit)(void* stageDt, void* i_data, int32_t entryNum, void* param_3);

    void handle_roomLoader(void* data, void* stageDt, int32_t roomNo);
    extern void (*return_roomLoader)(void* data, void* stageDt, int32_t roomNo);

    // void handle_stageLoader( void* data, void* stageDt );
    // extern void ( *return_stageLoader )( void* data, void* stageDt );

    int32_t handle_dStage_playerInit(void* stageDt,
                                     libtp::tp::d_stage::stage_dzr_header_entry* i_data,
                                     int32_t num,
                                     void* raw_data);

    extern int32_t (*return_dStage_playerInit)(void* stageDt,
                                               libtp::tp::d_stage::stage_dzr_header_entry* i_data,
                                               int32_t num,
                                               void* raw_data);

    // State functions
    extern int32_t (*return_getLayerNo_common_common)(const char* stageName, int32_t roomId, int32_t layerOverride);

    // Item creation functions. These are ran when the game displays an item though various means.
    int32_t handle_createItemForBoss(const float pos[3],
                                     int32_t item,
                                     int32_t roomNo,
                                     const int16_t rot[3],
                                     const float scale[3],
                                     float unk6,
                                     float unk7,
                                     int32_t parameters);

    extern int32_t (*return_createItemForBoss)(const float pos[3],
                                               int32_t item,
                                               int32_t roomNo,
                                               const int16_t rot[3],
                                               const float scale[3],
                                               float unk6,
                                               float unk7,
                                               int32_t parameters);

    int32_t handle_createItemForPresentDemo(const float pos[3],
                                            int32_t item,
                                            uint8_t unk3,
                                            int32_t unk4,
                                            int32_t unk5,
                                            const float unk6[3],
                                            const float unk7[3]);

    extern int32_t (*return_createItemForPresentDemo)(const float pos[3],
                                                      int32_t item,
                                                      uint8_t unk3,
                                                      int32_t unk4,
                                                      int32_t unk5,
                                                      const float unk6[3],
                                                      const float unk7[3]);

    int32_t handle_createItemForTrBoxDemo(const float pos[3],
                                          int32_t item,
                                          int32_t itemPickupFlag,
                                          int32_t roomNo,
                                          const int16_t rot[3],
                                          const float scale[3]);

    extern int32_t (*return_createItemForTrBoxDemo)(const float pos[3],
                                                    int32_t item,
                                                    int32_t itemPickupFlag,
                                                    int32_t roomNo,
                                                    const int16_t rot[3],
                                                    const float scale[3]);

    int32_t handle_createItemForMidBoss(const float pos[3],
                                        int32_t item,
                                        int32_t roomNo,
                                        const int16_t rot[3],
                                        const float scale[3],
                                        int32_t unk6,
                                        int32_t itemPickupFlag);

    extern int32_t (*return_createItemForMidBoss)(const float pos[3],
                                                  int32_t item,
                                                  int32_t roomNo,
                                                  const int16_t rot[3],
                                                  const float scale[3],
                                                  int32_t unk6,
                                                  int32_t itemPickupFlag);

    void handle_CheckFieldItemCreateHeap(libtp::tp::f_op_actor::fopAc_ac_c* actor);
    extern void (*return_CheckFieldItemCreateHeap)(libtp::tp::f_op_actor::fopAc_ac_c* actor);

    // Item Wheel functions
    void handle_setLineUpItem(libtp::tp::d_save::dSv_player_item_c*);
    extern void (*return_setLineUpItem)(libtp::tp::d_save::dSv_player_item_c*);

    // ItemGet functions. These functions handle the player and the flags set for their inventory
    void handle_execItemGet(uint8_t item);
    extern void (*return_execItemGet)(uint8_t item);

    int32_t handle_checkItemGet(uint8_t item, int32_t defaultValue);
    extern int32_t (*return_checkItemGet)(uint8_t item, int32_t defaultValue);

    void handle_item_func_ASHS_SCRIBBLING();
    extern void (*return_item_func_ASHS_SCRIBBLING)();

    // Message functions
    bool handle_setMessageCode_inSequence(libtp::tp::control::TControl* control,
                                          const void* TProcessor,
                                          uint16_t unk3,
                                          uint16_t msgId);

    extern bool (*return_setMessageCode_inSequence)(libtp::tp::control::TControl* control,
                                                    const void* TProcessor,
                                                    uint16_t unk3,
                                                    uint16_t msgId);

    uint32_t handle_getFontCCColorTable(uint8_t colorId, uint8_t unk);
    extern uint32_t (*return_getFontCCColorTable)(uint8_t colorId, uint8_t unk);

    uint32_t handle_getFontGCColorTable(uint8_t colorId, uint8_t unk);
    extern uint32_t (*return_getFontGCColorTable)(uint8_t colorId, uint8_t unk);

    void handle_jmessage_tSequenceProcessor__do_begin(void* seqProcessor, const void* unk2, const char* text);
    extern void (*return_jmessage_tSequenceProcessor__do_begin)(void* seqProcessor, const void* unk2, const char* text);

    bool handle_jmessage_tSequenceProcessor__do_tag(void* seqProcessor, uint32_t unk2, const void* currentText, uint32_t unk4);
    extern bool (*return_jmessage_tSequenceProcessor__do_tag)(void* seqProcessor,
                                                              uint32_t unk2,
                                                              const void* currentText,
                                                              uint32_t unk4);

    // Query/Event functions. Various uses
    int32_t handle_query022(void* unk1, void* unk2, int32_t unk3);
    extern int32_t (*return_query022)(void* unk1, void* unk2, int32_t unk3);

    int32_t handle_query023(void* unk1, void* unk2, int32_t unk3);
    extern int32_t (*return_query023)(void* unk1, void* unk2, int32_t unk3);

    int32_t handle_query025(void* unk1, void* unk2, int32_t unk3);
    extern int32_t (*return_query025)(void* unk1, void* unk2, int32_t unk3);

    uint8_t handle_checkEmptyBottle(libtp::tp::d_save::dSv_player_item_c* playerItem);
    extern uint8_t (*return_checkEmptyBottle)(libtp::tp::d_save::dSv_player_item_c* playerItem);

    int32_t handle_query042(void* unk1, void* unk2, int32_t unk3);
    extern int32_t (*return_query042)(void* unk1, void* unk2, int32_t unk3);

    int32_t handle_query037(void* unk1, void* unk2, int32_t unk3);
    extern int32_t (*return_query037)(void* unk1, void* unk2, int32_t unk3);

    int32_t handle_query049(void* unk1, void* unk2, int32_t unk3);
    extern int32_t (*return_query049)(void* unk1, void* unk2, int32_t unk3);

    // int32_t handle_event000( void* messageFlow, void* nodeEvent, void* actrPtr );
    // extern int32_t ( *return_event000 )( void* messageFlow, void* nodeEvent, void* actrPtr );

    int32_t handle_event017(void* messageFlow, void* nodeEvent, void* actrPtr);
    extern int32_t (*return_event017)(void* messageFlow, void* nodeEvent, void* actrPtr);

    int32_t handle_doFlow(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                          libtp::tp::f_op_actor::fopAc_ac_c* actrPtr,
                          libtp::tp::f_op_actor::fopAc_ac_c** actrValue,
                          int32_t i_flow);

    extern int32_t (*return_doFlow)(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                    libtp::tp::f_op_actor::fopAc_ac_c* actrPtr,
                                    libtp::tp::f_op_actor::fopAc_ac_c** actrValue,
                                    int32_t i_flow);

    int32_t handle_setNormalMsg(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                void* flowNode,
                                libtp::tp::f_op_actor::fopAc_ac_c* actrPtr);

    extern int32_t (*return_setNormalMsg)(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                          void* flowNode,
                                          libtp::tp::f_op_actor::fopAc_ac_c* actrPtr);

    // Save flag functions
    bool handle_isDungeonItem(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit);
    extern bool (*return_isDungeonItem)(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit);

    void handle_onDungeonItem(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit);
    extern void (*return_onDungeonItem)(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit);

    bool handle_daNpcT_chkEvtBit(int16_t flag);
    extern bool (*return_daNpcT_chkEvtBit)(int16_t flag);

    bool handle_isEventBit(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag);
    extern bool (*return_isEventBit)(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag);

    void handle_onEventBit(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag);
    extern void (*return_onEventBit)(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag);

    bool handle_isSwitch_dSv_memBit(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag);
    extern bool (*return_isSwitch_dSv_memBit)(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag);

    void handle_onSwitch_dSv_memBit(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag);
    extern void (*return_onSwitch_dSv_memBit)(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag);

    bool handle_checkTreasureRupeeReturn(libtp::tp::d_a_alink::daAlink* linkActrPtr, int32_t item);
    extern bool (*return_checkTreasureRupeeReturn)(libtp::tp::d_a_alink::daAlink* linkActrPtr, int32_t item);

    bool handle_isDarkClearLV(void* playerStatusPtr, int32_t twilightNode);
    extern bool (*return_isDarkClearLV)(void* playerStatusPtr, int32_t twilightNode);

    // Pause menu functions
    void handle_collect_save_open_init(uint8_t param_1);
    extern void (*return_collect_save_open_init)(uint8_t param_1);

    // Link functions
    bool handle_checkBootsMoveAnime(libtp::tp::d_a_alink::daAlink* d_a_alink, int32_t param_1);
    extern bool (*return_checkBootsMoveAnime)(libtp::tp::d_a_alink::daAlink* d_a_alink, int32_t param_1);

    void handle_setGetItemFace(libtp::tp::d_a_alink::daAlink* daALink, uint16_t itemID);
    extern void (*return_setGetItemFace)(libtp::tp::d_a_alink::daAlink* daALink, uint16_t itemID);

    void handle_setWolfLockDomeModel(libtp::tp::d_a_alink::daAlink* daALink);
    extern void (*return_setWolfLockDomeModel)(libtp::tp::d_a_alink::daAlink* daALink);

    bool handle_procFrontRollCrashInit(libtp::tp::d_a_alink::daAlink* daALink);
    extern bool (*return_procFrontRollCrashInit)(libtp::tp::d_a_alink::daAlink* daALink);

    bool handle_procWolfDashReverseInit(libtp::tp::d_a_alink::daAlink* daALink, bool param_1);
    extern bool (*return_procWolfDashReverseInit)(libtp::tp::d_a_alink::daAlink* daALink, bool param_1);

    bool handle_procWolfAttackReverseInit(libtp::tp::d_a_alink::daAlink* daALink);
    extern bool (*return_procWolfAttackReverseInit)(libtp::tp::d_a_alink::daAlink* daALink);

    libtp::tp::f_op_actor::fopAc_ac_c* handle_searchBouDoor(libtp::tp::f_op_actor::fopAc_ac_c* actrPtr);
    extern libtp::tp::f_op_actor::fopAc_ac_c* (*return_searchBouDoor)(libtp::tp::f_op_actor::fopAc_ac_c* actrPtr);

    bool handle_checkCastleTownUseItem(uint16_t item_id);
    extern bool (*return_checkCastleTownUseItem)(uint16_t item_id);

    float handle_damageMagnification(libtp::tp::d_a_alink::daAlink* daALink, int32_t param_1, int32_t param_2);
    extern float (*return_damageMagnification)(libtp::tp::d_a_alink::daAlink* daALink, int32_t param_1, int32_t param_2);

    int32_t handle_procCoGetItemInit(libtp::tp::d_a_alink::daAlink* linkActrPtr);
    extern int32_t (*return_procCoGetItemInit)(libtp::tp::d_a_alink::daAlink* linkActrPtr);

    // Audio functions
    void handle_loadSeWave(void* Z2SceneMgr, uint32_t waveID);
    extern void (*return_loadSeWave)(void* Z2SceneMgr, uint32_t waveID);

    void handle_sceneChange(libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,
                            libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,
                            uint8_t SeWave1,
                            uint8_t SeWave2,
                            uint8_t BgmWave1,
                            uint8_t BgmWave2,
                            uint8_t DemoWave,
                            bool param_7);

    extern void (*return_sceneChange)(libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,
                                      libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,
                                      uint8_t SeWave1,
                                      uint8_t SeWave2,
                                      uint8_t BgmWave1,
                                      uint8_t BgmWave2,
                                      uint8_t DemoWave,
                                      bool param_7);

    void handle_startSound(void* soungMgr, libtp::z2audiolib::z2scenemgr::JAISoundID soundId, void* soundHandle, void* pos);
    extern void (*return_startSound)(void* soundMgr,
                                     libtp::z2audiolib::z2scenemgr::JAISoundID soundId,
                                     void* soundHandle,
                                     void* pos);

    bool handle_checkBgmIDPlaying(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, uint32_t sfx_id);
    extern bool (*return_checkBgmIDPlaying)(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, uint32_t sfx_id);

    // Title Screen functions
    void* handle_dScnLogo_c_dt(void* dScnLogo_c, int16_t bFreeThis);
    extern void* (*return_dScnLogo_c_dt)(void* dScnLogo_c, int16_t bFreeThis);

    // Archive/Resource functions
    libtp::tp::d_resource::dRes_info_c* handle_getResInfo(const char* arcName,
                                                          libtp::tp::d_resource::dRes_info_c* objectInfo,
                                                          int32_t size);
    extern libtp::tp::d_resource::dRes_info_c* (*return_getResInfo)(const char* arcName,
                                                                    libtp::tp::d_resource::dRes_info_c* objectInfo,
                                                                    int32_t size);

    bool handle_mountArchive__execute(libtp::tp::m_Do_dvd_thread::mDoDvdThd_mountArchive_c* mountArchive);
    extern bool (*return_mountArchive__execute)(libtp::tp::m_Do_dvd_thread::mDoDvdThd_mountArchive_c* mountArchive);

    // d_meter functions
    void handle_resetMiniGameItem(libtp::tp::d_meter2_info::G_Meter2_Info* gMeter2InfoPtr, bool minigameFlag);
    extern void (*return_resetMiniGameItem)(libtp::tp::d_meter2_info::G_Meter2_Info* gMeter2InfoPtr, bool minigameFlag);

    // Game Over functions
    void handle_dispWait_init(libtp::tp::d_gameover::dGameOver* ptr);
    extern void (*return_dispWait_init)(libtp::tp::d_gameover::dGameOver* ptr);

    // Shop Functions
    int32_t handle_seq_decide_yes(libtp::tp::d_shop_system::dShopSystem* shopPtr,
                                  libtp::tp::f_op_actor::fopAc_ac_c* actor,
                                  void* msgFlow);

    extern int32_t (*return_seq_decide_yes)(libtp::tp::d_shop_system::dShopSystem* shopPtr,
                                            libtp::tp::f_op_actor::fopAc_ac_c* actor,
                                            void* msgFlow);
} // namespace mod
#endif