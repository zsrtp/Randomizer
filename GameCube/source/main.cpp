#include "main.h"

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cinttypes>

#ifdef DVD
#include "gc_wii/dvd.h"
#else
#include "gc_wii/card.h"
#endif

#include "Z2AudioLib/Z2AudioMgr.h"
#include "data/items.h"
#include "data/stages.h"
#include "game_patch/game_patch.h"
#include "memory.h"
#include "rando/data.h"
#include "rando/randomizer.h"
#include "rando/seedlist.h"
#include "tools.h"
#include "tp/J2DPicture.h"
#include "tp/JKRArchive.h"
#include "tp/control.h"
#include "tp/d_a_alink.h"
#include "tp/d_a_player.h"
#include "tp/d_com_inf_game.h"
#include "tp/d_save.h"
#include "tp/dzx.h"
#include "tp/f_op_actor_mng.h"
#include "tp/f_op_actor.h"
#include "tp/f_op_scene_req.h"
#include "tp/f_op_msg_mng.h"
#include "tp/f_pc_node_req.h"
#include "tp/m_do_controller_pad.h"
#include "tp/m_do_audio.h"
#include "item_wheel_menu.h"
#include "user_patch/03_customCosmetics.h"
#include "data/flags.h"
#include "tp/JKRExpHeap.h"
#include "tp/m_do_ext.h"
#include "patch.h"
#include "asm.h"
#include "tp/d_a_itembase.h"
#include "tp/JKRMemArchive.h"
#include "tp/m_Do_dvd_thread.h"
#include "util/texture_utils.h"
#include "rando/data.h"
#include "gc_wii/OSInterrupt.h"
#include "tp/d_kankyo.h"
#include "rando/customItems.h"
#include "cxx.h"
#include "tp/f_pc_executor.h"
#include "tp/d_msg_flow.h"

#ifdef TP_EU
#include "tp/d_s_logo.h"
#endif

namespace mod
{
    // Bind extern global variables
    KEEP_VAR libtp::display::Console* console = nullptr;
    KEEP_VAR rando::Randomizer* randomizer = nullptr;
    KEEP_VAR rando::SeedList* seedList = nullptr;

    // Variables
    void* z2ScenePtr = nullptr;
    uint32_t randState = 0;

    // Analog L is currently not being used, so commented out
    // float prevFrameAnalogL = 0.f;
    float prevFrameAnalogR = 0.f;

    KEEP_VAR uint8_t* m_MsgTableInfo = nullptr;
    KEEP_VAR uint8_t* m_HintMsgTableInfo = nullptr;
    libtp::tp::J2DPicture::J2DPicture* bgWindow = nullptr;
    uint16_t lastButtonInput = 0;
    KEEP_VAR uint16_t m_TotalMsgEntries = 0;
    KEEP_VAR uint16_t m_TotalHintMsgEntries = 0;
    bool roomReloadingState = false;
    bool consoleState = true;
    uint8_t gameState = GAME_BOOT;
    KEEP_VAR bool walletsPatched = false;
    KEEP_VAR uint8_t seedRelAction = SEED_ACTION_NONE;
    bool modifyShopModels = false;
    bool instantTextEnabled = false;
    bool increaseSpinnerSpeed = false;
    bool transformAnywhereEnabled = false;
    uint8_t damageMultiplier = 1;
    bool bonksDoDamage = false;
    EventItemStatus giveItemToPlayer = QUEUE_EMPTY;

#ifdef TP_EU
    KEEP_VAR libtp::tp::d_s_logo::Languages currentLanguage = libtp::tp::d_s_logo::Languages::uk;
#endif

    // Function hook return trampolines
    KEEP_VAR void (*return_fapGm_Execute)(void) = nullptr;

    // DMC (REL) Hook
    KEEP_VAR bool (*return_do_unlink)(libtp::tp::dynamic_link::DynamicModuleControl* dmc) = nullptr;

    // DZX trampolines
    KEEP_VAR bool (*return_actorInit)(void* mStatus_roomControl,
                                      libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                      int32_t unk3,
                                      void* unk4) = nullptr;

    KEEP_VAR bool (*return_actorInit_always)(void* mStatus_roomControl,
                                             libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                             int32_t unk3,
                                             void* unk4) = nullptr;

    KEEP_VAR bool (*return_actorCommonLayerInit)(void* mStatus_roomControl,
                                                 libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                                 int32_t unk3,
                                                 void* unk4) = nullptr;

    KEEP_VAR int32_t (*return_tgscInfoInit)(void* stageDt, void* i_data, int32_t entryNum, void* param_3) = nullptr;

    KEEP_VAR void (*return_roomLoader)(void* data, void* stageDt, int32_t roomNo) = nullptr;

    // KEEP_VAR void ( *return_stageLoader )( void* data, void* stageDt ) = nullptr;

    KEEP_VAR int32_t (*return_dStage_playerInit)(void* stageDt,
                                                 libtp::tp::d_stage::stage_dzr_header_entry* i_data,
                                                 int32_t num,
                                                 void* raw_data) = nullptr;

    KEEP_VAR void (*return_dComIfGp_setNextStage)(const char* stage,
                                                  int16_t point,
                                                  int8_t roomNo,
                                                  int8_t layer,
                                                  float lastSpeed,
                                                  uint32_t lastMode,
                                                  int32_t setPoint,
                                                  int8_t wipe,
                                                  int16_t lastAngle,
                                                  int32_t param_9,
                                                  int32_t wipSpeedT) = nullptr;

    // GetLayerNo trampoline
    KEEP_VAR int32_t (*return_getLayerNo_common_common)(const char* stageName, int32_t roomId, int32_t layerOverride) = nullptr;

    // Item creation functions.
    KEEP_VAR int32_t (*return_createItemForBoss)(const float pos[3],
                                                 int32_t item,
                                                 int32_t roomNo,
                                                 const int16_t rot[3],
                                                 const float scale[3],
                                                 float unk6,
                                                 float unk7,
                                                 int32_t parameters) = nullptr;

    KEEP_VAR int32_t (*return_createItemForPresentDemo)(const float pos[3],
                                                        int32_t item,
                                                        uint8_t unk3,
                                                        int32_t unk4,
                                                        int32_t unk5,
                                                        const float unk6[3],
                                                        const float unk7[3]) = nullptr;

    KEEP_VAR int32_t (*return_createItemForTrBoxDemo)(const float pos[3],
                                                      int32_t item,
                                                      int32_t itemPickupFlag,
                                                      int32_t roomNo,
                                                      const int16_t rot[3],
                                                      const float scale[3]) = nullptr;

    KEEP_VAR int32_t (*return_createItemForMidBoss)(const float pos[3],
                                                    int32_t item,
                                                    int32_t roomNo,
                                                    const int16_t rot[3],
                                                    const float scale[3],
                                                    int32_t unk6,
                                                    int32_t itemPickupFlag) = nullptr;

    KEEP_VAR void (*return_CheckFieldItemCreateHeap)(libtp::tp::f_op_actor::fopAc_ac_c* actor) = nullptr;

    // Item Wheel trampoline
    KEEP_VAR void (*return_setLineUpItem)(libtp::tp::d_save::dSv_player_item_c*) = nullptr;

    // ItemGet functions.
    KEEP_VAR void (*return_execItemGet)(uint8_t item) = nullptr;
    KEEP_VAR int32_t (*return_checkItemGet)(uint8_t item, int32_t defaultValue) = nullptr;
    KEEP_VAR void (*return_item_func_ASHS_SCRIBBLING)() = nullptr;

    // Message functions
    KEEP_VAR bool (*return_setMessageCode_inSequence)(libtp::tp::control::TControl* control,
                                                      const void* TProcessor,
                                                      uint16_t unk3,
                                                      uint16_t msgId) = nullptr;

    KEEP_VAR uint32_t (*return_getFontCCColorTable)(uint8_t colorId, uint8_t unk) = nullptr;
    KEEP_VAR uint32_t (*return_getFontGCColorTable)(uint8_t colorId, uint8_t unk) = nullptr;

    KEEP_VAR void (*return_jmessage_tSequenceProcessor__do_begin)(void* seqProcessor,
                                                                  const void* unk2,
                                                                  const char* text) = nullptr;

    KEEP_VAR bool (*return_jmessage_tSequenceProcessor__do_tag)(void* seqProcessor,
                                                                uint32_t unk2,
                                                                const void* currentText,
                                                                uint32_t unk4) = nullptr;

    // Query/Event functions.
    KEEP_VAR int32_t (*return_query022)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    KEEP_VAR int32_t (*return_query023)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    KEEP_VAR int32_t (*return_query025)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    KEEP_VAR uint8_t (*return_checkEmptyBottle)(libtp::tp::d_save::dSv_player_item_c* playerItem) = nullptr;
    KEEP_VAR int32_t (*return_query042)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    KEEP_VAR int32_t (*return_query004)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    KEEP_VAR int32_t (*return_query037)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    KEEP_VAR int32_t (*return_query049)(void* unk1, void* unk2, int32_t unk3) = nullptr;
    // KEEP_VAR int32_t ( *return_event000 )( void* messageFlow, void* nodeEvent, void* actrPtr ) = nullptr;
    KEEP_VAR int32_t (*return_event017)(void* messageFlow, void* nodeEvent, void* actrPtr) = nullptr;
    KEEP_VAR int32_t (*return_event003)(void* messageFlow, void* nodeEvent, void* actrPtr) = nullptr;

    KEEP_VAR int32_t (*return_doFlow)(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                      libtp::tp::f_op_actor::fopAc_ac_c* actrPtr,
                                      libtp::tp::f_op_actor::fopAc_ac_c** actrValue,
                                      int32_t i_flow) = nullptr;

    KEEP_VAR int32_t (*return_setNormalMsg)(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                            void* flowNode,
                                            libtp::tp::f_op_actor::fopAc_ac_c* actrPtr) = nullptr;

    // Save flag functions
    KEEP_VAR bool (*return_isDungeonItem)(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit) = nullptr;
    KEEP_VAR void (*return_onDungeonItem)(libtp::tp::d_save::dSv_memBit_c* memBitPtr, const int32_t memBit) = nullptr;
    KEEP_VAR bool (*return_daNpcT_chkEvtBit)(int16_t flag) = nullptr;
    KEEP_VAR bool (*return_isEventBit)(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag) = nullptr;
    KEEP_VAR void (*return_onEventBit)(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag) = nullptr;
    KEEP_VAR bool (*return_isSwitch_dSv_memBit)(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag) = nullptr;
    KEEP_VAR void (*return_onSwitch_dSv_memBit)(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag) = nullptr;
    KEEP_VAR bool (*return_checkTreasureRupeeReturn)(libtp::tp::d_a_alink::daAlink* linkActrPtr, int32_t item) = nullptr;
    KEEP_VAR bool (*return_isDarkClearLV)(void* playerStatusPtr, int32_t twilightNode) = nullptr;

    // Pause menu functions
    KEEP_VAR void (*return_collect_save_open_init)(uint8_t param_1) = nullptr;

    // Link functions
    KEEP_VAR bool (*return_checkBootsMoveAnime)(libtp::tp::d_a_alink::daAlink* d_a_alink, int32_t param_1) = nullptr;
    KEEP_VAR bool (*return_checkDamageAction)(libtp::tp::d_a_alink::daAlink* linkMapPtr) = nullptr;
    KEEP_VAR void (*return_setGetItemFace)(libtp::tp::d_a_alink::daAlink* daALink, uint16_t itemID) = nullptr;
    KEEP_VAR void (*return_setWolfLockDomeModel)(libtp::tp::d_a_alink::daAlink* daALink) = nullptr;
    KEEP_VAR bool (*return_procFrontRollCrashInit)(libtp::tp::d_a_alink::daAlink* daALink) = nullptr;
    KEEP_VAR bool (*return_procWolfAttackReverseInit)(libtp::tp::d_a_alink::daAlink* daALink) = nullptr;
    KEEP_VAR bool (*return_procWolfDashReverseInit)(libtp::tp::d_a_alink::daAlink* daALink, bool param_1) = nullptr;
    KEEP_VAR libtp::tp::f_op_actor::fopAc_ac_c* (*return_searchBouDoor)(libtp::tp::f_op_actor::fopAc_ac_c* actrPtr) = nullptr;

    KEEP_VAR float (*return_damageMagnification)(libtp::tp::d_a_alink::daAlink* daALink,
                                                 int32_t param_1,
                                                 int32_t param_2) = nullptr;

    KEEP_VAR bool (*return_checkCastleTownUseItem)(uint16_t item_id) = nullptr;
    KEEP_VAR int32_t (*return_procCoGetItemInit)(libtp::tp::d_a_alink::daAlink* linkActrPtr) = nullptr;

    // Audio functions
    KEEP_VAR void (*return_loadSeWave)(void* Z2SceneMgr, uint32_t waveID) = nullptr;

    KEEP_VAR void (*return_sceneChange)(libtp::z2audiolib::z2scenemgr::Z2SceneMgr* sceneMgr,
                                        libtp::z2audiolib::z2scenemgr::JAISoundID BGMid,
                                        uint8_t SeWave1,
                                        uint8_t SeWave2,
                                        uint8_t BgmWave1,
                                        uint8_t BgmWave2,
                                        uint8_t DemoWave,
                                        bool param_7) = nullptr;

    KEEP_VAR void (*return_startSound)(void* soungMgr,
                                       libtp::z2audiolib::z2scenemgr::JAISoundID soundId,
                                       void* soundHandle,
                                       void* pos) = nullptr;

    KEEP_VAR bool (*return_checkBgmIDPlaying)(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, uint32_t sfx_id) = nullptr;

    // Title Screen functions
    KEEP_VAR void* (*return_dScnLogo_c_dt)(void* dScnLogo_c, int16_t bFreeThis) = nullptr;

    // Archive/resource functions
    KEEP_VAR libtp::tp::d_resource::dRes_info_c* (*return_getResInfo)(const char* arcName,
                                                                      libtp::tp::d_resource::dRes_info_c* objectInfo,
                                                                      int32_t size) = nullptr;

    KEEP_VAR bool (*return_mountArchive__execute)(libtp::tp::m_Do_dvd_thread::mDoDvdThd_mountArchive_c* mountArchive) = nullptr;

    // d_meter functions
    KEEP_VAR void (*return_resetMiniGameItem)(libtp::tp::d_meter2_info::G_Meter2_Info* gMeter2InfoPtr,
                                              bool minigameFlag) = nullptr;

    // Game Over functions
    KEEP_VAR void (*return_dispWait_init)(libtp::tp::d_gameover::dGameOver* ptr) = nullptr;

    // Shop Functions
    KEEP_VAR int32_t (*return_seq_decide_yes)(libtp::tp::d_shop_system::dShopSystem* shopPtr,
                                              libtp::tp::f_op_actor::fopAc_ac_c* actor,
                                              void* msgFlow) = nullptr;

    void main()
    {
        // do_link needs to be hooked immediately, as otherwise we may not be able to modify f_pc_profile_lst.rel, which gets
        // linked via a callback function that gets called at boot, and this may occur before the boot REL's prolog function
        // gets called
        uint32_t do_link_address = reinterpret_cast<uint32_t>(libtp::tp::dynamic_link::do_link);

        libtp::patch::writeStandardBranches(do_link_address + 0x250, assembly::asmDoLinkHookStart, assembly::asmDoLinkHookEnd);

        // Call the boot REL
        // Interrupts are required to be enabled for CARD/DVD functions to work properly
        const bool enable = libtp::gc_wii::os_interrupt::OSEnableInterrupts();
#ifdef DVD
        // The seedlist will be generated in the boot REL
        libtp::tools::callRelProlog("/mod/boot.rel");
#else
        // The seedlist will be generated in the boot REL, so avoid mounting/unmounting the memory card multiple times
        libtp::tools::callRelProlog(CARD_SLOT_A, SUBREL_BOOT_ID);
#endif
        // Restore interrupts
        libtp::gc_wii::os_interrupt::OSRestoreInterrupts(enable);
    }

    void exit() {}

    void drawHeapDebugInfo()
    {
        static uint32_t archiveHeapLowestFreeSize = 0xFFFFFFFF;
        static uint32_t zeldaHeapLowestFreeSize = 0xFFFFFFFF;

        // Get the current maximum free size from any given block in the heaps
        // Archive heap
        void* heapPtr = libtp::tp::m_Do_ext::archiveHeap;
        if (heapPtr)
        {
            uint32_t currentFreeSize = libtp::tp::jkr_exp_heap::do_getFreeSize_JKRExpHeap(heapPtr);
            if (currentFreeSize < archiveHeapLowestFreeSize)
            {
                archiveHeapLowestFreeSize = currentFreeSize;
            }
        }

        // Zelda heap
        heapPtr = libtp::tp::m_Do_ext::zeldaHeap;
        if (heapPtr)
        {
            uint32_t currentFreeSize = libtp::tp::jkr_exp_heap::do_getFreeSize_JKRExpHeap(heapPtr);
            if (currentFreeSize < zeldaHeapLowestFreeSize)
            {
                zeldaHeapLowestFreeSize = currentFreeSize;
            }
        }

        // Get the values to draw
        char buf[96];
        snprintf(buf,
                 sizeof(buf),
                 "Archive: %.2fkb, Zelda: %.2fkb",
                 intToFloat(archiveHeapLowestFreeSize) / 1024.f,
                 intToFloat(zeldaHeapLowestFreeSize) / 1024.f);

        // Draw the values
        events::drawText(buf, 161, 430, 0xFFFFFFFF, true, 14.f);
    }

    KEEP_FUNC rando::Seed* getCurrentSeed(rando::Randomizer* rando)
    {
        if (!randoIsEnabled(rando))
        {
            return nullptr;
        }

        return rando->m_Seed;
    }

    void setScreen(bool state)
    {
        consoleState = state;
        libtp::display::setConsole(state, 0);
    }

    bool checkButtonsPressedThisFrame(uint32_t buttons)
    {
        using namespace libtp::tp::m_do_controller_pad;
        CPadInfo* padInfo = &cpadInfo[PAD_1];

        return padInfo->mPressedButtonFlags & buttons;
    }

    bool checkButtonCombo(uint32_t combo, bool checkAnalog)
    {
        using namespace libtp::tp::m_do_controller_pad;
        CPadInfo* padInfo = &cpadInfo[PAD_1];

        // Get the buttons that are currently held and were pressed this frame
        uint32_t buttonsHeld = padInfo->mButtonFlags;
        uint32_t buttonsPressedThisFrame = padInfo->mPressedButtonFlags;

        // Check if analog L and R should be checked
        if (checkAnalog)
        {
            // Get the threshold for the analog buttons
            constexpr float analogThreshold = 0.7f; // 70%

            // Check if L is included in the button combo
            // Analog L is currently not being used, so commented out
            /*
            if ( combo & PadInputs::Button_L )
            {
                // Check if analog L is at 70% or more
                if ( padInfo->mTriggerLeft >= analogThreshold )
                {
                    // Manually set the bit for L being pressed
                    buttonsHeld |= PadInputs::Button_L;

                    // If prevFrameAnalogL is less than 70%, then 70% was reached this frame
                    if ( prevFrameAnalogL < analogThreshold )
                    {
                        buttonsPressedThisFrame |= PadInputs::Button_L;
                    }
                }
            }
            */

            // Check if R is included in the button combo
            if (combo & PadInputs::Button_R)
            {
                // Check if analog R is at 70% or more
                if (padInfo->mTriggerRight >= analogThreshold)
                {
                    // Manually set the bit for R being pressed
                    buttonsHeld |= PadInputs::Button_R;

                    // If prevFrameAnalogR is less than 70%, then 70% was reached this frame
                    if (prevFrameAnalogR < analogThreshold)
                    {
                        buttonsPressedThisFrame |= PadInputs::Button_R;
                    }
                }
            }
        }

        // Check if the button combo is held
        if ((buttonsHeld & combo) != combo)
        {
            return false;
        }

        // Check if at least one button in the combo was pressed this frame
        return buttonsPressedThisFrame & combo;
    }

    void doInput(uint32_t input)
    {
        using namespace libtp::tp::m_do_controller_pad;
        auto checkBtn = [&input](uint32_t combo) { return static_cast<bool>((input & combo) == combo); };

        if (input && gameState == GAME_TITLE)
        {
            // Handle seed selection if necessary
            const uint32_t numSeeds = seedList->m_numSeeds;
            if (numSeeds > 1)
            {
                uint32_t selectedSeed = seedList->m_selectedSeed;

                if (checkBtn(Button_X))
                {
                    selectedSeed++;
                    seedList->m_selectedSeed = static_cast<uint8_t>(selectedSeed);

                    if (selectedSeed >= numSeeds)
                    {
                        selectedSeed = 0;
                        seedList->m_selectedSeed = static_cast<uint8_t>(selectedSeed);
                    }
                }
                else if (checkBtn(Button_Y))
                {
                    if (selectedSeed == 0)
                    {
                        selectedSeed = numSeeds;
                        seedList->m_selectedSeed = static_cast<uint8_t>(selectedSeed);
                    }

                    selectedSeed--;
                    seedList->m_selectedSeed = static_cast<uint8_t>(selectedSeed);
                }

                getConsole().setLine(CONSOLE_PROTECTED_LINES - 1);
                getConsole() << "\r"
                             << "Press X/Y to select a seed\n"
                             << "Press R + Z to close the console\n"
                             << "[" << static_cast<int32_t>(selectedSeed) + 1 << "/" << static_cast<int32_t>(numSeeds)
                             << "] Seed: " << seedList->m_minSeedInfo[selectedSeed].fileName << "\n";
            }
        }
        // End of handling title screen inputs
    }

    KEEP_FUNC void handle_fapGm_Execute()
    {
        using namespace libtp;
        using namespace tp::m_do_controller_pad;
        using namespace tp::f_pc_node_req;
        using namespace tp::d_com_inf_game;

// Uncomment out the next line to display debug heap info
// #define DRAW_DEBUG_HEAP_INFO
#ifdef DRAW_DEBUG_HEAP_INFO
        drawHeapDebugInfo();
#undef DRAW_DEBUG_HEAP_INFO
#endif

        // New frame, so the ring will be redrawn
        item_wheel_menu::ringDrawnThisFrame = false;

        dComIfG_inf_c* gameInfo = &dComIfG_gameInfo;
        CPadInfo* padInfo = &cpadInfo[PAD_1];

        // Handle game state updates
        if (l_fpcNdRq_Queue)
        {
            // Previous state
            const uint32_t prevState = gameState;
            const uint32_t state = *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(l_fpcNdRq_Queue) + 0x59);

            // Normal/Loading into game
            if (prevState != GAME_ACTIVE && state == 11)
            {
                // check whether we're in title screen CS
                if (0 != strcmp("S_MV000", gameInfo->play.mNextStage.mStage))
                {
                    gameState = GAME_ACTIVE;
                }
            }
            else if (prevState != GAME_TITLE && (state == 12 || state == 13))
            {
                gameState = GAME_TITLE;

                // Handle console differently when the user first loads it
                if (prevState == GAME_BOOT)
                {
                    switch (seedList->m_numSeeds)
                    {
                        case 0:
                            // Err, no seeds
                            getConsole() << "No seeds available! Please check your memory\ncard and region!\n";
                            setScreen(true);
                            break;

                        case 1:
                            // Only one seed present, auto-select it and disable console for convenience
                            getConsole() << "Seed: " << seedList->m_minSeedInfo[0].fileName << " found.\n";
                            setScreen(false);
                            break;

                        default:
                            // User has to select one of the seeds

                            // trigger a dummy input to print the current selection
                            doInput(Button_Start);

                            setScreen(true);
                            break;
                    }
                }
            }
        }
        // End of handling gameStates

        // Handle button inputs only if buttons are being held that weren't held last time
        auto checkBtn = [](uint32_t input, uint32_t combo) { return static_cast<bool>((input & combo) == combo); };
        uint32_t currentButtons = padInfo->mButtonFlags;

        // Generic button checks need to occur outside the following conditional, so use a bool to determine if they should be
        // checked or not
        bool handledSpecialInputs = false;

        if (currentButtons != lastButtonInput)
        {
            // Store before processing since we (potentially) un-set the padInfo values later
            lastButtonInput = static_cast<uint16_t>(currentButtons);

            // Special combo to (de)activate the console should be handled first
            if (checkBtn(currentButtons, PadInputs::Button_R | PadInputs::Button_Z))
            {
                // Disable the input that was just pressed, as sometimes it could cause talking to Midna when in-game
                padInfo->mPressedButtonFlags = 0;

                // Disallow during boot as we print info etc.
                // Will automatically disappear if there is no seeds to select from
                setScreen(!consoleState);
                handledSpecialInputs = true;
            }
            // Handle Inputs if console is already active
            else if (consoleState)
            {
                doInput(currentButtons);

                if (gameState != GAME_BOOT)
                {
                    // Disable input so game doesn't notice
                    currentButtons = 0;
                    padInfo->mButtonFlags = 0;
                    padInfo->mPressedButtonFlags = 0;
                }

                handledSpecialInputs = true;
            }
        }

        tp::d_a_alink::daAlink* linkMapPtr = gameInfo->play.mPlayer;
        if (!handledSpecialInputs)
        {
            // Handle generic button checks
            if (checkButtonCombo(PadInputs::Button_R | PadInputs::Button_Y, true))
            {
                // Disable the input that was just pressed, as sometimes it could cause items to be used or Wolf Link to dig.
                padInfo->mPressedButtonFlags = 0;

                // Handle transforming
                events::handleQuickTransform();
            }

            else if (checkBtn(currentButtons, PadInputs::Button_R) && increaseSpinnerSpeed && linkMapPtr)
            {
                libtp::tp::f_op_actor::fopAc_ac_c* spinnerActor = libtp::tp::d_a_alink::getSpinnerActor(linkMapPtr);

                if (spinnerActor)
                {
                    float spinnerSpeed = spinnerActor->mSpeedF;
                    if (spinnerSpeed < 60.f)
                    {
                        spinnerSpeed += 2.f;
                        spinnerActor->mSpeedF = spinnerSpeed;
                    }
                }
            }
        }

        // Handle rando state
        rando::Randomizer* rando = randomizer;
        if (gameState == GAME_ACTIVE)
        {
            if (!getCurrentSeed(rando) && (seedList->m_numSeeds > 0) && (seedRelAction == SEED_ACTION_NONE))
            {
                // Interrupts are required to be enabled for CARD/DVD functions to work properly
                const bool enable = libtp::gc_wii::os_interrupt::OSEnableInterrupts();
#ifndef DVD
                constexpr int32_t chan = CARD_SLOT_A;
#endif
                if (!rando || !rando->m_Seed)
                {
                    seedRelAction = SEED_ACTION_LOAD_SEED;

                    // m_Enabled will be set to true in the seed REL
                    // The seed REL will set seedRelAction to SEED_ACTION_NONE if it ran successfully
#ifdef DVD
                    if (!tools::callRelProlog("/mod/seed.rel"))
#else
                    // Only mount/unmount the memory card once
                    if (!tools::callRelProlog(chan, SUBREL_SEED_ID))
#endif
                    {
                        seedRelAction = SEED_ACTION_FATAL;
                    }

                    // The randomizer pointer may have updated by the seed rel, so update the local pointer
                    rando = randomizer;
                }
                else
                {
                    // Enable the randomizer
                    rando->m_Enabled = true;

                    // Check if loading a different seed
                    if (rando->m_CurrentSeed != seedList->m_selectedSeed)
                    {
                        getConsole() << "Changing seed:\n";
                        seedRelAction = SEED_ACTION_CHANGE_SEED;

                        // The seed REL will set seedRelAction to SEED_ACTION_NONE if it ran successfully
#ifdef DVD
                        if (!tools::callRelProlog("/mod/seed.rel"))
#else
                        // Only mount/unmount the memory card once
                        if (!tools::callRelProlog(chan, SUBREL_SEED_ID))
#endif
                        {
                            seedRelAction = SEED_ACTION_FATAL;
                        }

                        // The randomizer pointer may have updated by the seed rel, so update the local pointer
                        rando = randomizer;
                    }
                    else
                    {
                        // Not loading a different seed, so load checks for first load
                        rando->onStageLoad();
                    }
                }

                // Restore interrupts
                libtp::gc_wii::os_interrupt::OSRestoreInterrupts(enable);

                // Make sure no errors occurred
                rando::Seed* seed = getCurrentSeed(rando);
                if (seed && (seedRelAction == SEED_ACTION_NONE))
                {
                    // Volatile patches need to be applied whenever a file is loaded
                    // getConsole() << "Applying volatile patches:\n";
                    seed->applyVolatilePatches(true);
                }
            }
        }
        else
        {
            seedRelAction = SEED_ACTION_NONE;
            if (randoIsEnabled(rando))
            {
                // Temporarily disable the randomizer
                rando->m_Enabled = false;
                rando->m_SeedInit = false;
            }
        }

        // Custom events
        bool currentReloadingState;

        if (linkMapPtr)
        {
            // checkRestartRoom is needed for voiding
            currentReloadingState = tp::d_a_alink::checkRestartRoom(linkMapPtr);
        }
        else
        {
            // If linkMapPtr is not set, then assume a room is being loaded
            // In most cases this will be used for triggering onLoad
            currentReloadingState = true;
        }

        const bool prevReloadingState = roomReloadingState;

        // Custom events
        if (currentReloadingState)
        {
            if (!prevReloadingState)
            {
                // OnLoad
                events::onLoad(rando);
            }
        }
        else
        {
            if (prevReloadingState)
            {
                // OffLoad
                events::offLoad(rando);

                // SetHUDCosmetics
                user_patch::setHUDCosmetics(rando);
            }
        }

        roomReloadingState = currentReloadingState;

        handleFoolishItem();
        tools::xorshift32(&randState);

        if (events::timeChange != 0)
        {
            events::handleTimeSpeed();
        }

        // Giving items at any point
        if (linkMapPtr)
        {
            initGiveItemToPlayer(linkMapPtr);
        }

        // End of custom events

        // Call the original function
        return_fapGm_Execute();

        // Main code has ran, so update previous frame variables
        // Analog L is currently not being used, so commented out
        // prevFrameAnalogL = padInfo->mTriggerLeft;
        prevFrameAnalogR = padInfo->mTriggerRight;
    }

    void initGiveItemToPlayer(libtp::tp::d_a_alink::daAlink* linkMapPtr)
    {
        using namespace libtp::tp;

        switch (linkMapPtr->mProcID)
        {
            case d_a_alink::PROC_WAIT:
            case d_a_alink::PROC_TIRED_WAIT:
            case d_a_alink::PROC_MOVE:
            case d_a_alink::PROC_WOLF_WAIT:
            case d_a_alink::PROC_WOLF_TIRED_WAIT:
            case d_a_alink::PROC_WOLF_MOVE:
            {
                // Check if link is currently in a cutscene
                if (d_a_alink::checkEventRun(linkMapPtr))
                {
                    break;
                }

                // Ensure that link is not currently in a message-based event.
                if (linkMapPtr->mMsgFlow.mEventId != 0)
                {
                    break;
                }

                d_com_inf_game::dComIfG_inf_c* gameInfo = &d_com_inf_game::dComIfG_gameInfo;
                uint8_t* reserveBytesPtr = &gameInfo->save.save_file.reserve.unk[0];
                uint32_t itemToGive = 0xFF;

                for (uint32_t i = 0; i < 4; i++)
                {
                    const uint32_t storedItem = reserveBytesPtr[i];

                    if (storedItem)
                    {
                        // If we have the call to clear the queue, then we want to clear the item and break out.
                        if (giveItemToPlayer == CLEAR_QUEUE)
                        {
                            reserveBytesPtr[i] = 0;
                            giveItemToPlayer = QUEUE_EMPTY;
                            break;
                        }
                        // If the queue is empty and we have an item to give, update the queue state.
                        else if (giveItemToPlayer == QUEUE_EMPTY)
                        {
                            giveItemToPlayer = ITEM_IN_QUEUE;
                        }
                        itemToGive = storedItem;
                        break;
                    }
                }

                // if there is no item to give, break out of the case.
                if (itemToGive == 0xFF)
                {
                    break;
                }

                libtp::tp::d_com_inf_game::dComIfG_play* playPtr = &gameInfo->play;
                playPtr->mEvent.mGtItm = static_cast<uint8_t>(itemToGive);

                // Set the process value for getting an item to start the "get item" cutscene when next available.
                linkMapPtr->mProcID = libtp::tp::d_a_alink::PROC_GET_ITEM;

                //  Get the event index for the "Get Item" event.
                const int16_t eventIdx = d_event_manager::getEventIdx3(&playPtr->mEvtManager,
                                                                       reinterpret_cast<f_op_actor::fopAc_ac_c*>(linkMapPtr),
                                                                       "DEFAULT_GETITEM",
                                                                       0xFF);

                // Finally we want to modify the event stack to prioritize our custom event so that it happens next.
                libtp::tp::f_op_actor_mng::fopAcM_orderChangeEventId(linkMapPtr, eventIdx, 1, 0xFFFF);
            }
            default:
            {
                break;
            }
        }
    }

    int32_t initCreatePlayerItem(uint32_t itemID,
                                 uint32_t flag,
                                 const float pos[3],
                                 int32_t roomNo,
                                 const int16_t rot[3],
                                 const float scale[3])
    {
        uint32_t params = 0xFF0000 | ((flag & 0xFF) << 0x8) | (itemID & 0xFF);
        return libtp::tp::f_op_actor_mng::fopAcM_create(539, params, pos, roomNo, rot, scale, -1);
    }

    KEEP_FUNC bool handle_do_unlink(libtp::tp::dynamic_link::DynamicModuleControl* dmc)
    {
        events::onRELUnlink(randomizer, dmc);
        return return_do_unlink(dmc);
    }

    KEEP_FUNC bool handle_actorInit(void* mStatus_roomControl,
                                    libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                    int32_t unk3,
                                    void* unk4)
    {
        // Load DZX based randomizer checks that are stored in the local DZX
        events::onDZX(randomizer, chunkTypeInfo);
        events::loadCustomActors(mStatus_roomControl);
        return return_actorInit(mStatus_roomControl, chunkTypeInfo, unk3, unk4);
    }

    KEEP_FUNC bool handle_actorInit_always(void* mStatus_roomControl,
                                           libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                           int32_t unk3,
                                           void* unk4)
    {
        // Load DZX based randomizer checks that are stored in the global DZX
        events::onDZX(randomizer, chunkTypeInfo);
        return return_actorInit_always(mStatus_roomControl, chunkTypeInfo, unk3, unk4);
    }

    KEEP_FUNC bool handle_actorCommonLayerInit(void* mStatus_roomControl,
                                               libtp::tp::dzx::ChunkTypeInfo* chunkTypeInfo,
                                               int32_t unk3,
                                               void* unk4)
    {
        // Load DZX based checks that are stored in the current layer DZX
        rando::Randomizer* randoPtr = randomizer;
        events::onDZX(randoPtr, chunkTypeInfo);
        events::loadCustomRoomActors(randoPtr);

        return return_actorCommonLayerInit(mStatus_roomControl, chunkTypeInfo, unk3, unk4);
    }

    KEEP_FUNC int32_t handle_tgscInfoInit(void* stageDt, void* i_data, int32_t entryNum, void* param_3)
    {
        events::loadCustomRoomSCOBs();
        return return_tgscInfoInit(stageDt, i_data, entryNum, param_3);
    }

    KEEP_FUNC void handle_dComIfGp_setNextStage(const char* stage,
                                                int16_t point,
                                                int8_t roomNo,
                                                int8_t layer,
                                                float lastSpeed,
                                                uint32_t lastMode,
                                                int32_t setPoint,
                                                int8_t wipe,
                                                int16_t lastAngle,
                                                int32_t param_9,
                                                int32_t wipSpeedT)
    {
        rando::Seed* seedPtr;
        if (seedPtr = getCurrentSeed(randomizer), seedPtr)
        {
            const int32_t stageIDX = libtp::tools::getStageIndex(stage);
            const uint32_t numShuffledEntrances = seedPtr->m_numShuffledEntrances;
            const rando::ShuffledEntrance* shuffledEntrances = &seedPtr->m_ShuffledEntrances[0];

            // getConsole() << stageIDX << "," << roomNo << "," << point << "," << layer << "\n";

            if (stageIDX !=
                libtp::data::stage::StageIDs::Title_Screen) // We won't want to shuffle if we are loading a save since some
                                                            // stages use their default spawn for their entrances.
            {
                for (uint32_t i = 0; i < numShuffledEntrances; i++)
                {
                    const rando::ShuffledEntrance* currentEntrance = &shuffledEntrances[i];

                    if ((stageIDX == currentEntrance->origStageIDX) && (roomNo == currentEntrance->origRoomIDX) &&
                        (point == currentEntrance->origSpawn) && (layer == currentEntrance->origState))
                    {
                        // getConsole() << "Shuffling Entrance\n";

                        return return_dComIfGp_setNextStage(libtp::data::stage::allStages[currentEntrance->newStageIDX],
                                                            currentEntrance->newSpawn,
                                                            currentEntrance->newRoomIDX,
                                                            currentEntrance->newState,
                                                            lastSpeed,
                                                            lastMode,
                                                            setPoint,
                                                            wipe,
                                                            lastAngle,
                                                            param_9,
                                                            wipSpeedT);
                    }
                }
            }
        }

        // getConsole() << "No match found.\n";

        return return_dComIfGp_setNextStage(stage,
                                            point,
                                            roomNo,
                                            layer,
                                            lastSpeed,
                                            lastMode,
                                            setPoint,
                                            wipe,
                                            lastAngle,
                                            param_9,
                                            wipSpeedT);
    }

    KEEP_FUNC void handle_roomLoader(void* data, void* stageDt, int32_t roomNo)
    {
        rando::Randomizer* rando = randomizer;
        if (randoIsEnabled(rando))
        {
            events::onARC(rando, data, roomNo, rando::FileDirectory::Room); // Replace room based checks.

            void* filePtr =
                libtp::tp::d_com_inf_game::dComIfG_getStageRes("stage.dzs"); // Could hook stageLoader instead since it takes
                                                                             // the first param as a pointer to the stage.dzs

            events::onARC(rando, filePtr, roomNo, rando::FileDirectory::Stage); // Replace stage based checks.
        }
        return return_roomLoader(data, stageDt, roomNo);
    }

    /*
    KEEP_FUNC void handle_stageLoader( void* data, void* stageDt )
    {
        // This function is a placeholder for now. May work with Taka on getting some ARC checks converted over to use this
        // function instead of roomLoader
        return return_stageLoader( data, stageDt );
    }
    */

    KEEP_FUNC int32_t handle_dStage_playerInit(void* stageDt,
                                               libtp::tp::d_stage::stage_dzr_header_entry* i_data,
                                               int32_t num,
                                               void* raw_data)
    {
        libtp::tp::d_save::dSv_player_status_a_c* playerStatusPtr =
            &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a;

        // If Link is in wolf form, then we want to change the entrance type to prevent a softlock caused by Link repeatedly
        // voiding out.

        libtp::tp::d_stage::stage_actor_data_class* allPLYR = i_data->mDzrDataPointer;

        for (int32_t i = 0; i < num; i++)
        {
            uint8_t* mParameter = reinterpret_cast<uint8_t*>(&allPLYR[i].mParameter);
            uint8_t* entranceType = &mParameter[2];

            switch (*entranceType)
            {
                // Only replace the entrance type if it is a door.
                case 0x80:
                case 0xA0:
                case 0xB0:
                {
                    if (playerStatusPtr->currentForm == 1)
                    {
                        // Change the entrance type to play the animation of walking out of the loading zone instead of entering
                        // through the door.
                        *entranceType = 0x50;
                    }
                    break;
                }

                case 0xD0:
                {
                    if (libtp::tp::d_a_alink::checkStageName(
                            libtp::data::stage::allStages[libtp::data::stage::StageIDs::Lake_Hylia]) &&
                        !libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::CLEARED_LANAYRU_TWILIGHT))
                    {
                        *entranceType = 0x50;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        return return_dStage_playerInit(stageDt, i_data, num, raw_data);
    }

    KEEP_FUNC int32_t handle_createItemForBoss(const float pos[3],
                                               int32_t item,
                                               int32_t roomNo,
                                               const int16_t rot[3],
                                               const float scale[3],
                                               float unk6,
                                               float unk7,
                                               int32_t parameters)
    {
        (void)unk6;
        (void)unk7;

        // Spawn the appropriate item with model
        rando::Randomizer* rando = randomizer;

        uint32_t itemID = rando->getBossItem(item);
        itemID = game_patch::_04_verifyProgressiveItem(rando, itemID);

        if (item == libtp::data::items::Heart_Container) // used for Dungeon Heart Containers
        {
            parameters = 0x9F;
        }

        // If we are in hyrule field then the function is running to give us the Hot Springwater heart piece and we want it to
        // spawn on the ground.
        if (libtp::tp::d_a_alink::checkStageName(libtp::data::stage::allStages[libtp::data::stage::StageIDs::Hyrule_Field]))
        {
            *const_cast<float*>(&pos[1]) = -190.f;
        }

        return initCreatePlayerItem(itemID, parameters & 0xFF, pos, roomNo, rot, scale);
    }

    KEEP_FUNC int32_t handle_createItemForMidBoss(const float pos[3],
                                                  int32_t item,
                                                  int32_t roomNo,
                                                  const int16_t rot[3],
                                                  const float scale[3],
                                                  int32_t unk6,
                                                  int32_t itemPickupFlag)
    {
        if (item == libtp::data::items::Boomerang)
        {
            // Spawn the appropriate item
            rando::Randomizer* rando = randomizer;

            uint32_t itemID = rando->getBossItem(item);
            itemID = game_patch::_04_verifyProgressiveItem(rando, itemID);

            return initCreatePlayerItem(itemID, 0xFF, pos, roomNo, rot, scale);
        }

        return return_createItemForMidBoss(pos, item, roomNo, rot, scale, unk6, itemPickupFlag);
    }

    KEEP_FUNC int32_t handle_createItemForPresentDemo(const float pos[3],
                                                      int32_t item,
                                                      uint8_t unk3,
                                                      int32_t unk4,
                                                      int32_t unk5,
                                                      const float rot[3],
                                                      const float scale[3])
    {
        item = game_patch::_04_verifyProgressiveItem(randomizer, item);
        return return_createItemForPresentDemo(pos, item, unk3, unk4, unk5, rot, scale);
    }

    KEEP_FUNC int32_t handle_createItemForTrBoxDemo(const float pos[3],
                                                    int32_t item,
                                                    int32_t itemPickupFlag,
                                                    int32_t roomNo,
                                                    const int16_t rot[3],
                                                    const float scale[3])
    {
        item = game_patch::_04_verifyProgressiveItem(randomizer, item);
        return return_createItemForTrBoxDemo(pos, item, itemPickupFlag, roomNo, rot, scale);
    }

    KEEP_FUNC void handle_CheckFieldItemCreateHeap(libtp::tp::f_op_actor::fopAc_ac_c* actor)
    {
        libtp::tp::d_a_itembase::ItemBase* item = static_cast<libtp::tp::d_a_itembase::ItemBase*>(actor);

        // We determine whether to use the item_resource or the field_item_resource structs to spawn an item based on the item
        // being created.
        switch (item->m_itemNo)
        {
            case libtp::data::items::Empty_Bottle:
            case libtp::data::items::Sera_Bottle:
            case libtp::data::items::Jovani_Bottle:
            case libtp::data::items::Coro_Bottle:
            case libtp::data::items::Purple_Rupee_Links_House:
            case libtp::data::items::Poe_Soul:
            {
                return libtp::tp::d_a_itembase::CheckItemCreateHeap(actor);
            }
            default:
            {
                return return_CheckFieldItemCreateHeap(actor);
            }
        }
    }

    KEEP_FUNC void handle_setLineUpItem(libtp::tp::d_save::dSv_player_item_c* unk1)
    {
        (void)unk1;

        using namespace libtp::tp::d_com_inf_game;

        static const uint8_t i_item_lst[24] = {0x0A, 0x08, 0x06, 0x02, 0x09, 0x04, 0x03, 0x00, 0x01, 0x17, 0x14, 0x05,
                                               0x0F, 0x10, 0x11, 0x0B, 0x0C, 0x0D, 0x0E, 0x13, 0x12, 0x16, 0x15, 0x7};
        int32_t i1 = 0;
        int32_t i2 = 0;
        libtp::tp::d_save::dSv_player_item_c* playerItemStructPtr = &dComIfG_gameInfo.save.save_file.player.player_item;
        uint8_t* playerItemSlots = &playerItemStructPtr->item_slots[0];

        for (; i1 < 24; i1++) // Clear all of the item slots.
        {
            playerItemSlots[i1] = 0xFF;
        }

        uint8_t* playerItem = &playerItemStructPtr->item[0];
        for (i1 = 0; i1 < 24; i1++) // Fill all of the item wheel slots with their respective items if gotten.
        {
            const uint32_t currentEntry = i_item_lst[i1];
            if (playerItem[currentEntry] != 0xFF)
            {
                playerItemSlots[i2] = static_cast<uint8_t>(currentEntry);
                i2++;
            }
        }
    }

    KEEP_FUNC void handle_execItemGet(uint8_t item)
    {
        item = game_patch::_04_verifyProgressiveItem(randomizer, item);
        return return_execItemGet(item);
    }

    KEEP_FUNC int32_t handle_checkItemGet(uint8_t item, int32_t defaultValue)
    {
        using namespace libtp;
        using namespace libtp::tp;
        using namespace libtp::data;
        using namespace libtp::data::stage;

        const auto stagesPtr = &allStages[0];
        switch (item)
        {
            case items::Hylian_Shield:
            {
                // Check if we are at Kakariko Malo mart and verify that we have not bought the shield.
                if (libtp::tools::playerIsInRoomStage(3, stagesPtr[StageIDs::Kakariko_Village_Interiors]) &&
                    !tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::BOUGHT_HYLIAN_SHIELD_AT_MALO_MART))
                {
                    // Return false so we can buy the shield.
                    return 0;
                }
                break;
            }
            case items::Hawkeye:
            {
                // Check if we are at Kakariko Village and that the hawkeye is currently not for sale.
                if ((tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Kakariko_Village]) &&
                     !libtp::tp::d_save::isSwitch_dSv_memBit(&d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x3E)))
                {
                    // Return false so we can buy the hawkeye.
                    return 0;
                }
                break;
            }
            case items::Wooden_Shield:
            {
                // Check if we are at Kakariko Malo Mart and that the Wooden Shield has not been bought.
                if (libtp::tools::playerIsInRoomStage(3, stagesPtr[StageIDs::Kakariko_Village_Interiors]) &&
                    !libtp::tp::d_save::isSwitch_dSv_memBit(&d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags, 0x3A))
                {
                    // Return false so we can buy the hawkeye.
                    return 0;
                }
                break;
            }
            case items::Ordon_Pumpkin:
            case items::Ordon_Goat_Cheese:
            {
                // Check to see if currently in Snowpeak Ruins
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Snowpeak_Ruins]))
                {
                    // Return false so that yeta will give the map item no matter what.
                    return 0;
                }
                break;
            }
            case items::Ball_and_Chain:
            {
                // Check to see if currently in Snowpeak Ruins
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[StageIDs::Darkhammer]))
                {
                    if (libtp::tp::d_save::isSwitch_dSv_memBit(&d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags,
                                                               0x5F)) // Picked up the Ball and Chain check.
                    {
                        // Return true so that they check cannot be infinitely picked up.
                        return 1;
                    }
                }
                break;
            }
            default:
            {
                break;
            }
        }

        return return_checkItemGet(item, defaultValue);
    }
    KEEP_FUNC void handle_item_func_ASHS_SCRIBBLING()
    {
        using namespace libtp::data::flags;
        if (!libtp::tp::d_com_inf_game::dComIfGs_isEventBit(GOT_CORAL_EARRING_FROM_RALIS))
        {
            return_item_func_ASHS_SCRIBBLING();
        }
    }

    KEEP_FUNC bool handle_setMessageCode_inSequence(libtp::tp::control::TControl* control,
                                                    const void* TProcessor,
                                                    uint16_t unk3,
                                                    uint16_t msgId)
    {
        // Call the original function immediately, as a lot of stuff needs to be set before our code runs
        const bool ret = return_setMessageCode_inSequence(control, TProcessor, unk3, msgId);

        // Make sure the function ran successfully
        if (ret)
        {
            game_patch::_05_setCustomItemMessage(control, TProcessor, unk3, msgId);
        }
        return ret;
    }

    KEEP_FUNC uint32_t handle_getFontCCColorTable(uint8_t colorId, uint8_t unk)
    {
        if (colorId >= 0x9)
        {
            return game_patch::_05_getCustomMsgColor(colorId);
        }
        else
        {
            return return_getFontCCColorTable(colorId, unk);
        }
    }

    KEEP_FUNC uint32_t handle_getFontGCColorTable(uint8_t colorId, uint8_t unk)
    {
        if (colorId >= 0x9)
        {
            return game_patch::_05_getCustomMsgColor(colorId);
        }
        else
        {
            return return_getFontCCColorTable(colorId, unk);
        }
    }

    KEEP_FUNC int32_t handle_query022(void* unk1, void* unk2, int32_t unk3)
    {
        return events::proc_query022(unk1, unk2, unk3);
    }

    KEEP_FUNC int32_t handle_query023(void* unk1, void* unk2, int32_t unk3)
    {
        return events::proc_query023(unk1, unk2, unk3);
    }

    KEEP_FUNC int32_t handle_query025(void* unk1, void* unk2, int32_t unk3)
    {
        return events::proc_query025(unk1, unk2, unk3);
    }

    KEEP_FUNC uint8_t handle_checkEmptyBottle(libtp::tp::d_save::dSv_player_item_c* playerItem)
    {
        if (libtp::tp::d_a_alink::checkStageName(libtp::data::stage::allStages[libtp::data::stage::StageIDs::Cave_of_Ordeals]))
        {
            // Return 1 to allow the player to collect the item from the floor 50 reward, as this will make the game think that
            // the player has an empty bottle.
            return 1;
        }
        return return_checkEmptyBottle(playerItem);
    }

    KEEP_FUNC int32_t handle_query037(void* unk1, void* unk2, int32_t unk3)
    {
        // Call the original function immediately as we need its output
        const int32_t menuType = return_query037(unk1, unk2, unk3);

        if ((menuType == 0x2) && (reinterpret_cast<int32_t>(libtp::tp::d_a_player::m_midnaActor) ==
                                  libtp::tp::f_op_actor_mng::fopAcM_getTalkEventPartner(nullptr)))
        {
            events::handleTimeOfDayChange();
        }

        return menuType;
    }

    KEEP_FUNC int32_t handle_query049(void* unk1, void* unk2, int32_t unk3)
    {
        const int32_t poeFlag = return_query049(unk1, unk2, unk3);

        if ((poeFlag == 4) && !libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::GOT_BOTTLE_FROM_JOVANI))
        {
            return 3;
        }

        return poeFlag;
    }

    KEEP_FUNC int32_t handle_query042(void* unk1, void* unk2, int32_t unk3)
    {
        return events::proc_query042(unk1, unk2, unk3);
    }

    /*
    KEEP_FUNC int32_t handle_event000( void* messageFlow, void* nodeEvent, void* actrPtr )
    {
        // Prevent the hidden skill CS from setting the proper flags
        if ( libtp::tp::d_a_alink::checkStageName( libtp::data::stage::allStages[libtp::data::stage::StageIDs::Hidden_Skill] ) )
        {
            *reinterpret_cast<uint16_t*>( reinterpret_cast<uint32_t>( nodeEvent ) + 4 ) = 0x0000;
        }
        return return_event000( messageFlow, nodeEvent, actrPtr );
    }
    */

    KEEP_FUNC int32_t handle_event017(void* messageFlow, void* nodeEvent, void* actrPtr)
    {
        const uint32_t messageParam = *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(nodeEvent) + 4);

        // Prevent Gor Liggs from setting the third key shard flag
        if (messageParam == 0x00FB)
        {
            *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(nodeEvent) + 4) = 0x0000;
        }

        return return_event017(messageFlow, nodeEvent, actrPtr);
    }

    KEEP_FUNC int32_t handle_doFlow(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                    libtp::tp::f_op_actor::fopAc_ac_c* actrPtr,
                                    libtp::tp::f_op_actor::fopAc_ac_c** actrValue,
                                    int32_t i_flow)
    {
        using namespace libtp::data::stage;
        if (msgFlow->mFlow == 0xFFFE) // Check if it equals our custom flow value
        {
            if (msgFlow->mMsg == 0xFFFFFFFF)
            {
                // Clear the invalid msg value since it will be set by the game once our text is loaded.
                msgFlow->mMsg = 0;

                // When this byte is set, the current event is aborted. With unused nodes, it is set to 1 by default so we need
                // to unset it.
                msgFlow->field_0x26 = 0;

                if (libtp::tp::d_a_alink::checkStageName(allStages[StageIDs::Hyrule_Field]) ||
                    libtp::tp::d_a_alink::checkStageName(allStages[StageIDs::Outside_Castle_Town]) ||
                    libtp::tp::d_a_alink::checkStageName(allStages[StageIDs::Lake_Hylia]))
                {
                    // Hyrule Field and outside Lake Hylia do not have a valid flow node for node 0 so we want it to use its
                    // native node (8)
                    msgFlow->field_0x10 = 0x8;
                }
                else if (libtp::tp::d_a_alink::checkStageName(allStages[StageIDs::Death_Mountain]))
                {
                    // Death Mountain does not have a valid flow node for node 0 so we want it to use its
                    // native node (4)
                    msgFlow->field_0x10 = 0x4;
                }
                else
                {
                    // Sets the flow to use the same flow grouping as the standard flow that getItem text uses.
                    msgFlow->field_0x10 = 0;
                }
            }
        }

        return return_doFlow(msgFlow, actrPtr, actrValue, i_flow);
    }

    KEEP_FUNC int32_t handle_setNormalMsg(libtp::tp::d_msg_flow::dMsgFlow* msgFlow,
                                          void* flowNode,
                                          libtp::tp::f_op_actor::fopAc_ac_c* actrPtr)
    {
        if (msgFlow->mFlow == 0xFFFE) // Check if it equals our custom flow value
        {
            // Set the msg id in the node to that of our specified message.
            const uint32_t msg = libtp::tp::f_op_msg_mng::fopMsgM_messageSet(0x1360, 1000);

            msgFlow->mMsg = msg;
            return 1;
        }

        return return_setNormalMsg(msgFlow, flowNode, actrPtr);
    }

    KEEP_FUNC void handle_jmessage_tSequenceProcessor__do_begin(void* seqProcessor, const void* unk2, const char* text)
    {
        // Call the original function immediately as it sets necessary values needed later on.
        return_jmessage_tSequenceProcessor__do_begin(seqProcessor, unk2, text);

        if (instantTextEnabled)
        {
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(seqProcessor) + 0xB2) = 0x1;
        }
    }

    KEEP_FUNC bool handle_jmessage_tSequenceProcessor__do_tag(void* seqProcessor,
                                                              uint32_t unk2,
                                                              const void* currentText,
                                                              uint32_t unk4)
    {
        // Call the original function immediately as it sets necessary values needed later on.
        const bool result = return_jmessage_tSequenceProcessor__do_tag(seqProcessor, unk2, currentText, unk4);

        if (instantTextEnabled)
        {
            *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(seqProcessor) + 0xB2) = 0x1;
#ifdef TP_JP
            constexpr uint32_t offset = 0x5A6;
#else
            constexpr uint32_t offset = 0x5D6;
#endif
            uint32_t tReferencePtr = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(seqProcessor) + 0x4);
            *reinterpret_cast<int16_t*>(tReferencePtr + offset) = 0;
        }
        return result;
    }

    KEEP_FUNC bool handle_isDungeonItem(libtp::tp::d_save::dSv_memBit_c* membitPtr, const int32_t memBit)
    {
        return events::proc_isDungeonItem(membitPtr, memBit);
    }

    KEEP_FUNC void handle_onDungeonItem(libtp::tp::d_save::dSv_memBit_c* membitPtr, const int32_t memBit)
    {
        return events::proc_onDungeonItem(membitPtr, memBit);
    }

    KEEP_FUNC bool handle_daNpcT_chkEvtBit(int16_t flag)
    {
        const auto stagesPtr = &libtp::data::stage::allStages[0];
        switch (flag)
        {
            case 0x153: // Checking if the player has Ending Blow
            {
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Hidden_Skill]))
                {
                    return true;
                }
                break;
            }

            case 0x40: // Checking if the player has completed Goron Mines
            {
                if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Kakariko_Village_Interiors]))
                {
                    return true; // Return true so Barnes will sell bombs no matter what
                }
                break;
            }
            default:
            {
                break;
            }
        }
        return return_daNpcT_chkEvtBit(flag);
    }

    KEEP_FUNC bool handle_isEventBit(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag)
    {
        using namespace libtp::tp::d_a_alink;
        using namespace libtp::tp::d_com_inf_game;
        using namespace libtp::data::stage;
        using namespace libtp::data::flags;

        const auto stagesPtr = &allStages[0];

        switch (flag)
        {
            case ENDING_BLOW_UNLOCKED: // Checking for ending blow.
            {
                if (checkStageName(stagesPtr[StageIDs::Hidden_Skill]))
                {
                    return true; // If we don't have the flag, the game sends us to Faron by default. Which we don't
                                 // want.
                }
                break;
            }

            case GREAT_SPIN_UNLOCKED:
            {
                if (checkStageName(stagesPtr[StageIDs::Hidden_Skill]))
                {
                    return false; // Tell the game we don't have great spin to
                                  // not softlock in hidden skill training.
                }
                break;
            }

            case BO_TALKED_TO_YOU_AFTER_OPENING_IRON_BOOTS_CHEST: // Has Bo been defeated in wrestling
            {
                if (checkStageName(stagesPtr[StageIDs::Ordon_Village_Interiors]))
                {
                    if (dComIfGs_isEventBit(
                            libtp::data::flags::HEARD_BO_TEXT_AFTER_SUMO_FIGHT)) // Talked to Bo after chest is spawned
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                break;
            }

            case GAVE_ILIA_HER_CHARM:    // Gave Ilia the charm
            case CITY_OOCCOO_CS_WATCHED: // CiTS Intro CS watched
            {
                if (checkStageName(stagesPtr[StageIDs::Hidden_Village]))
                {
                    if (!dComIfGs_isEventBit(libtp::data::flags::GOT_ILIAS_CHARM))
                    {
                        return false; // If we haven't gotten the item from Impaz then we need to return false or it
                                      // will break her dialogue.
                    }
                }
                break;
            }

            case GORON_MINES_CLEARED: // Goron Mines Story Flag
            {
                if (checkStageName(stagesPtr[StageIDs::Goron_Mines]))
                {
                    return false; // The elders will not spawn if the flag is set.
                }
                break;
            }

            case ZORA_ESCORT_CLEARED: // Escort Completed
            {
                if (checkStageName(stagesPtr[StageIDs::Castle_Town]))
                {
                    return true; // If flag isn't set, the player will be thrown into escort when they open the
                                 // door.
                }
                else if (libtp::tools::playerIsInRoomStage(
                             0,
                             stagesPtr[StageIDs::Kakariko_Village_Interiors])) // Return true to prevent Renado/Illia
                                                                               // crash after ToT
                {
                    return true;
                }
                break;
            }

            case ARBITERS_GROUNDS_CLEARED: // AG story flag.
            {
                if (checkStageName(stagesPtr[StageIDs::Stallord]))
                {
                    return false; // If the flag is set, the post boss music plays during the boss fight.
                }
                break;
            }

            case SNOWPEAK_RUINS_CLEARED: // Snowpeak Ruins Story flag
            {
                if (checkStageName(stagesPtr[StageIDs::Kakariko_Graveyard]))
                {
                    return false; // If the flag is set, Ralis will no longer spawn in the graveyard.
                }
                break;
            }

            case FOREST_TEMPLE_CLEARED: // Forest Temple Story Flag
            {
                if (checkStageName(stagesPtr[StageIDs::Diababa]))
                {
                    return false; // If the flag is set, the post boss music plays during the boss fight.
                }
                break;
            }

            case CITY_IN_THE_SKY_CLEARED: // City in the Sky Story flag
            {
                if (checkStageName(stagesPtr[StageIDs::Mirror_Chamber]))
                {
                    if (!libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::FIXED_THE_MIRROR_OF_TWILIGHT))
                    {
                        rando::Seed* seed;
                        if (seed = getCurrentSeed(randomizer), seed)
                        {
                            if (seed->m_Header->palaceRequirements != 3)
                            {
                                return false;
                            }
                        }
                    }
                }
                break;
            }
            case HOWLED_AT_SNOWPEAK_STONE:
            {
                if (checkStageName(stagesPtr[StageIDs::Snowpeak]))
                {
                    return false; // Return false so the player can howl at the stone multiple times to remove map glitch
                }
                break;
            }

            case WATCHED_CUTSCENE_AFTER_GOATS_2:
            {
                if (libtp::tools::playerIsInRoomStage(1, stagesPtr[StageIDs::Ordon_Village_Interiors]))
                {
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(SERAS_CAT_RETURNED_TO_SHOP))
                    {
                        return false; // Return false so Sera will give the milk item to the player once they help the cat.
                    }
                    else
                    {
                        return true; // Return true so the player can always access the shop, even if the cat has not
                                     // returned.
                    }
                }
                break;
            }

            default:
            {
                break;
            }
        }
        return return_isEventBit(eventPtr, flag);
    }

    KEEP_FUNC void handle_onEventBit(libtp::tp::d_save::dSv_event_c* eventPtr, uint16_t flag)
    {
        using namespace libtp::tp::d_a_alink;
        using namespace libtp::data::stage;
        using namespace libtp::data::flags;

        libtp::tp::d_save::dSv_save_c* saveFilePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file;
        if (eventPtr == &saveFilePtr->mEvent)
        {
            libtp::tp::d_save::dSv_player_c* playerPtr = &saveFilePtr->player;
            libtp::tp::d_save::dSv_player_status_a_c* playerStatusAPtr = &playerPtr->player_status_a;
            libtp::tp::d_save::dSv_player_status_b_c* playerStatusBPtr = &playerPtr->player_status_b;

            const uint32_t darkClearLevelFlag = playerStatusBPtr->dark_clear_level_flag;

            switch (flag)
            {
                // Case block for Wolf -> Human crash patches/bug fixes. Some cutscenes/events either crash or act weird if Link
                // is Human but needs to be Wolf and the game no longer attempts to auto-transform Link once the Shadow Crystal
                // has been obtained.
                case ENTERED_ORDON_SPRING_DAY_3:
                {
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(TRANSFORMING_UNLOCKED))
                    {
                        // Set player to Human as the game will not do so if Shadow Crystal has been obtained.
                        playerStatusAPtr->currentForm = 0;
                    }
                    break;
                }

                // Case block for Human -> Wolf crash patches/bug fixes. Some cutscenes/events either crash or act weird if Link
                // is Wolf but needs to be human and the game no longer attempts to auto-transform Link once the Shadow Crystal
                // has been obtained.
                case WATCHED_CUTSCENE_AFTER_BEING_CAPTURED_IN_FARON_TWILIGHT:
                {
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(TRANSFORMING_UNLOCKED))
                    {
                        // Set player to Wolf as the game will not do so if Shadow Crystal has been obtained.
                        playerStatusAPtr->currentForm = 1;
                    }
                    break;
                }

                case MIDNAS_DESPERATE_HOUR_COMPLETED: // MDH Completed
                {
                    playerStatusBPtr->dark_clear_level_flag |= 0x8;
                    break;
                }

                case CLEARED_FARON_TWILIGHT: // Cleared Faron Twilight
                {
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_COMPLETED))
                    {
                        if (darkClearLevelFlag == 0x6)
                        {
                            playerStatusBPtr->transform_level_flag = 0x8; // Set the flag for the last transformed twilight.
                                                                          // Also puts Midna on the player's back

                            playerStatusBPtr->dark_clear_level_flag |= 0x8;
                        }
                    }
                    break;
                }

                case CLEARED_ELDIN_TWILIGHT: // Cleared Eldin Twilight
                {
                    events::setSaveFileEventFlag(MAP_WARPING_UNLOCKED); // in glitched Logic, you can skip the gorge bridge.
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_COMPLETED))
                    {
                        if (darkClearLevelFlag == 0x5)
                        {
                            playerStatusBPtr->transform_level_flag |= 0x8; // Set the flag for the last transformed twilight.
                                                                           // Also puts Midna on the player's back

                            playerStatusBPtr->dark_clear_level_flag |= 0x8;
                        }
                    }

                    break;
                }

                case CLEARED_LANAYRU_TWILIGHT: // Cleared Lanayru Twilight
                {
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(MIDNAS_DESPERATE_HOUR_COMPLETED))
                    {
                        if (darkClearLevelFlag == 0x7) // All twilights completed
                        {
                            playerStatusBPtr->transform_level_flag |= 0x8; // Set the flag for the last transformed twilight.
                                                                           // Also puts Midna on the player's back

                            playerStatusBPtr->dark_clear_level_flag |= 0x8;
                        }
                    }

                    break;
                }

                case PALACE_OF_TWILIGHT_CLEARED:
                {
                    rando::Seed* seed;
                    if (seed = getCurrentSeed(randomizer), seed)
                    {
                        if (seed->m_Header->castleRequirements == rando::CastleEntryRequirements::HC_Vanilla) // Vanilla
                        {
                            events::setSaveFileEventFlag(libtp::data::flags::BARRIER_GONE);
                            return return_onEventBit(eventPtr, flag); // set PoT story flag
                        }
                    }
                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        return return_onEventBit(eventPtr, flag);
    }

    KEEP_FUNC bool handle_isSwitch_dSv_memBit(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag)
    {
        const auto stagesPtr = &libtp::data::stage::allStages[0];

        if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Kakariko_Graveyard]))
        {
            if (flag == 0x66) // Check for escort completed flag
            {
                if (!libtp::tp::d_com_inf_game::dComIfGs_isEventBit(
                        libtp::data::flags::GOT_ZORA_ARMOR_FROM_RUTELA)) // return false if we haven't gotten the item
                                                                         // from Rutella.
                {
                    return false;
                }
            }
        }
        else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Hidden_Village_Interiors]))
        {
            if (flag == 0x61) // Is Impaz in her house
            {
                return true;
            }
        }

        else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Ordon_Village]))
        {
            if ((flag == 0x21) &&
                !libtp::tp::d_kankyo::dKy_daynight_check()) // Midna jumps to shield house are active and it is daytime
            {
                return false;
            }
        }
        return return_isSwitch_dSv_memBit(memoryBit, flag);
    }

    KEEP_FUNC void handle_onSwitch_dSv_memBit(libtp::tp::d_save::dSv_memBit_c* memoryBit, int32_t flag)
    {
        libtp::tp::d_save::dSv_info_c* savePtr = &libtp::tp::d_com_inf_game::dComIfG_gameInfo.save;

        if (memoryBit == &savePtr->memory.temp_flags)
        {
            const auto stagesPtr = &libtp::data::stage::allStages[0];

            if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Forest_Temple]))
            {
                if (flag == 0x52)
                {
                    // Don't set the flag for all monkeys freed in the lobby of Forest Temple
                    return;
                }
            }
            else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Arbiters_Grounds]))
            {
                if (flag == 0x26) // Poe flame CS trigger
                {
                    // Open the Poe gate
                    libtp::tp::d_save::offSwitch_dSv_memBit(memoryBit, 0x45);

                    return;
                }
            }
            else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Lake_Hylia]))
            {
                if (flag == 0xD) // Lanayru Twilight End CS trigger.
                {
                    if (libtp::tp::d_com_inf_game::dComIfGs_isEventBit(libtp::data::flags::TRANSFORMING_UNLOCKED))
                    {
                        // Set player to Human as the game will not do so if Shadow Crystal has been obtained.
                        savePtr->save_file.player.player_status_a.currentForm = 0;
                    }
                }
            }
            else if (libtp::tp::d_a_alink::checkStageName(stagesPtr[libtp::data::stage::StageIDs::Kakariko_Village]))
            {
                if (flag == 0x3E) // Hawkeye is for sell.
                {
                    // Remove the coming soon sign so the hawkeye can be bought.
                    libtp::tp::d_save::offSwitch_dSv_memBit(memoryBit, 0xB);
                }
            }
        }

        return return_onSwitch_dSv_memBit(memoryBit, flag);
    }

    KEEP_FUNC bool handle_checkTreasureRupeeReturn(libtp::tp::d_a_alink::daAlink* linkActrPtr, int32_t item)
    {
        (void)linkActrPtr;
        (void)item;

        return false;
    }

    KEEP_FUNC bool handle_isDarkClearLV(void* playerStatusPtr, int32_t twilightNode)
    {
        if ((twilightNode == 0) && libtp::tools::playerIsInRoomStage(
                                       1,
                                       libtp::data::stage::allStages[libtp::data::stage::StageIDs::Ordon_Village_Interiors]))

        {
            return false; // Return false so Sera will give us the bottle if we have rescued the cat.
        }

        return return_isDarkClearLV(playerStatusPtr, twilightNode);
    }

    KEEP_FUNC void handle_collect_save_open_init(uint8_t param_1)
    {
        game_patch::_07_checkPlayerStageReturn();
        return return_collect_save_open_init(param_1);
    }

    KEEP_FUNC void handle_resetMiniGameItem(libtp::tp::d_meter2_info::G_Meter2_Info* gMeter2InfoPtr, bool minigameFlag)
    {
        using namespace libtp::tp;

        // If we are in Iza's hut and we have the bow, we want to update the save file bow item stored in g_meter2_info just in
        // case the player started the minigame without it and somehow broke out of the minigame.
        if (d_a_alink::checkStageName(libtp::data::stage::allStages[libtp::data::stage::StageIDs::Zoras_River]))
        {
            if (events::haveItem(libtp::data::items::Heros_Bow))
            {
                gMeter2InfoPtr->mSaveBowItem = libtp::data::items::Heros_Bow;

                // We want to keep track of the number of arrows we have as well because the game
                // will set our arrow count to this variable upon save warp if the minigame is not completed.
                gMeter2InfoPtr->mSaveArrowNum =
                    d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_item_record.bow_ammo;
            }
        }

        // Run the original function as we want to clear the other minigame flags
        return_resetMiniGameItem(gMeter2InfoPtr, minigameFlag);
    }

    KEEP_FUNC bool handle_checkBootsMoveAnime(libtp::tp::d_a_alink::daAlink* d_a_alink, int32_t param_1)
    {
        if (libtp::tp::d_a_alink::ironBootsVars.heavyStateSpeed == 1.f)
        {
            return false;
        }
        return return_checkBootsMoveAnime(d_a_alink, param_1);
    }

    KEEP_FUNC void handle_setGetItemFace(libtp::tp::d_a_alink::daAlink* linkMapPtr, uint16_t itemID)
    {
        using namespace libtp::data::items;
        using namespace rando::customItems;

        switch (itemID)
        {
            // Only the first foolish item should need to be checked, but check all to be safe
            case Foolish_Item_1:
            case Foolish_Item_2:
            case Foolish_Item_3:
            case Foolish_Item_4:
            case Foolish_Item_5:
            case Foolish_Item_6:
            {
                itemID = Ordon_Pumpkin;
                break;
            }

            case Wooden_Sword:
            case Ordon_Sword:
            case Ordon_Shield:
            case Master_Sword:
            case Master_Sword_Light:
            case Shadow_Crystal:
            {
                itemID = Clawshot;
                break;
            }

            default:
            {
                break;
            }
        }
        return return_setGetItemFace(linkMapPtr, itemID);
    }

    KEEP_FUNC void handle_setWolfLockDomeModel(libtp::tp::d_a_alink::daAlink* linkActrPtr)
    {
        // Call the original function immediately, as certain values need to be set in the Link Actor struct.
        return_setWolfLockDomeModel(linkActrPtr);

        rando::Randomizer* rando = randomizer;
        if (getCurrentSeed(rando))
        {
            rando->replaceWolfLockDomeColor(linkActrPtr);
        }
        return;
    }

    KEEP_FUNC bool handle_procFrontRollCrashInit(libtp::tp::d_a_alink::daAlink* linkActrPtr)
    {
        handleBonkDamage();
        return return_procFrontRollCrashInit(linkActrPtr);
    }

    KEEP_FUNC bool handle_procWolfDashReverseInit(libtp::tp::d_a_alink::daAlink* linkActrPtr, bool param_1)
    {
        handleBonkDamage();
        return return_procWolfDashReverseInit(linkActrPtr, param_1);
    }

    KEEP_FUNC bool handle_procWolfAttackReverseInit(libtp::tp::d_a_alink::daAlink* linkActrPtr)
    {
        handleBonkDamage();
        return return_procWolfAttackReverseInit(linkActrPtr);
    }

    KEEP_FUNC libtp::tp::f_op_actor::fopAc_ac_c* handle_searchBouDoor(libtp::tp::f_op_actor::fopAc_ac_c* actrPtr)
    {
        rando::Seed* seed;
        if (seed = getCurrentSeed(randomizer), seed)
        {
            if (seed->m_StageIDX == libtp::data::stage::StageIDs::Ordon_Village)
            {
                return nullptr;
            }
        }
        return return_searchBouDoor(actrPtr);
    }

    KEEP_FUNC float handle_damageMagnification(libtp::tp::d_a_alink::daAlink* linkActrPtr, int32_t param_1, int32_t param_2)
    {
        // Call the original function immediately, as we only need the current damage magnification value.
        float ret = return_damageMagnification(linkActrPtr, param_1, param_2);

        rando::Seed* seed;
        if (seed = getCurrentSeed(randomizer), seed)
        {
            ret *= intToFloat(static_cast<int32_t>(damageMultiplier));
        }
        return ret;
    }

    KEEP_FUNC bool handle_checkCastleTownUseItem(uint16_t item_id)
    {
        using namespace libtp::data::items;
        using namespace libtp::tp::d_a_alink;
        using namespace libtp::tp::d_com_inf_game;

        const int32_t roomID = libtp::tools::getCurrentRoomNo();

        if (checkStageName(libtp::data::stage::allStages[libtp::data::stage::StageIDs::Sacred_Grove]) &&
            roomID == 0x2) // check if the player is in past area
        {
            if (item_id == Ooccoo_Jr)
            {
                return false; // remove the ability to use ooccoo in past area
            }
        }
        else if (checkStageName(libtp::data::stage::allStages[libtp::data::stage::StageIDs::Temple_of_Time]) && roomID == 0x0)
        {
            switch (item_id)
            {
                case Ooccoo_Jr:
                case Ooccoo_FT:
                case Ooccoo_Dungeon:
                {
                    if (!libtp::tp::d_save::isDungeonItem(&libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.memory.temp_flags,
                                                          0x6)) // check if the player hasn't taken ooccoo at tot entrance
                    {
                        return false;
                    }
                    break;
                }
            }
        }

        return return_checkCastleTownUseItem(item_id);
    }

    KEEP_FUNC void handle_loadSeWave(void* z2SceneMgr, uint32_t waveID)
    {
        z2ScenePtr = z2SceneMgr;
        return return_loadSeWave(z2SceneMgr, waveID);
    }

    KEEP_FUNC bool handle_checkBgmIDPlaying(libtp::z2audiolib::z2seqmgr::Z2SeqMgr* seqMgr, uint32_t sfx_id)
    {
        // Call original function immediately as it sets necessary values.
        const bool ret = return_checkBgmIDPlaying(seqMgr, sfx_id);

        if (sfx_id == 0x01000013) // Game Over sfx
        {
            return false;
        }

        return ret;
    }

    KEEP_FUNC void handle_dispWait_init(libtp::tp::d_gameover::dGameOver* ptr)
    {
        // Set the timer
        ptr->mTimer = 0;
        return return_dispWait_init(ptr);
    }

    KEEP_FUNC int32_t handle_seq_decide_yes(libtp::tp::d_shop_system::dShopSystem* shopPtr,
                                            libtp::tp::f_op_actor::fopAc_ac_c* actor,
                                            void* msgFlow)
    {
        using namespace libtp::data::stage;

        const auto stagesPtr = &allStages[0];
        if (libtp::tools::playerIsInRoomStage(3, stagesPtr[StageIDs::Kakariko_Village_Interiors]))
        {
            // We want the shop item to have its flag updated no matter what in kak malo mart
            libtp::tp::d_shop_system::setSoldOutFlag(shopPtr);
        }

        return return_seq_decide_yes(shopPtr, actor, msgFlow);
    }

    KEEP_FUNC int32_t handle_procCoGetItemInit(libtp::tp::d_a_alink::daAlink* linkActrPtr)
    {
        // If we are giving a custom item, we want to set mParam0 to 0x100 so that instead of trying to search for an item actor
        // that doesnt exist we want the game to create one using the item id in mGtItm.
        if (giveItemToPlayer == ITEM_IN_QUEUE)
        {
            giveItemToPlayer = CLEAR_QUEUE;
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mPlayer->mDemo.mParam0 = 0x100;
        }

        return return_procCoGetItemInit(linkActrPtr);
    }

    KEEP_FUNC void* handle_dScnLogo_c_dt(void* dScnLogo_c, int16_t bFreeThis)
    {
        // Call the original function immediately, as certain values need to be set first
        void* ret = return_dScnLogo_c_dt(dScnLogo_c, bFreeThis);

        // Initialize bgWindow since mMain2DArchive should now be set
        if (!bgWindow)
        {
            void* main2DArchive = libtp::tp::d_com_inf_game::dComIfG_gameInfo.play.mMain2DArchive;
            if (main2DArchive)
            {
                // Get the image to use for the background window
                void* bg = libtp::tp::JKRArchive::JKRArchive_getResource2(main2DArchive,
                                                                          0x54494D47, // TIMG
                                                                          "tt_block_grade.bti");

                if (bg)
                {
                    bgWindow = new libtp::tp::J2DPicture::J2DPicture(bg);
                }
            }
        }

        return ret;
    }

    KEEP_FUNC void handleFoolishItem()
    {
        using namespace libtp::z2audiolib;
        using namespace libtp::z2audiolib::z2scenemgr;
        using namespace libtp::tp;

        const uint8_t currentDamageMultiplier = damageMultiplier;

        if (!randoIsEnabled(randomizer))
        {
            return;
        }

        // Get the trigger count
        uint8_t* triggerCount = &rando::foolishItems.triggerCount;
        uint32_t count = *triggerCount;
        if (count == 0)
        {
            return;
        }

        if (!events::checkFoolItemFreeze())
        {
            return;
        }

        // Failsafe: Make sure the count does not somehow exceed 100
        if (count > 100)
        {
            count = 100;
        }
        // reset trigger counter to 0
        *triggerCount = 0;

        /* Store the currently loaded sound wave to local variables as we will need to load them back later.
         * We use this method because if we just loaded the sound waves every time the item was gotten, we'd
         * eventually run out of memory so it is safer to unload everything and load it back in. */
        z2scenemgr::Z2SceneMgr* sceneMgrPtr = &z2audiomgr::g_mDoAud_zelAudio.mSceneMgr;
        const uint32_t seWave1 = sceneMgrPtr->SeWaveToErase_1;
        const uint32_t seWave2 = sceneMgrPtr->SeWaveToErase_2;

        void* scenePtr = z2ScenePtr;
        eraseSeWave(scenePtr, seWave1);
        eraseSeWave(scenePtr, seWave2);
        loadSeWave(scenePtr, 0x46);
        m_Do_Audio::mDoAud_seStartLevel(0x10040, nullptr, 0, 0);
        loadSeWave(scenePtr, seWave1);
        loadSeWave(scenePtr, seWave2);

        d_com_inf_game::dComIfG_inf_c* gameInfoPtr = &d_com_inf_game::dComIfG_gameInfo;
        libtp::tp::d_save::dSv_player_status_a_c* playerStatusPtr = &gameInfoPtr->save.save_file.player.player_status_a;
        d_a_alink::daAlink* linkMapPtr = gameInfoPtr->play.mPlayer;
        int32_t newHealthValue;

        if (playerStatusPtr->currentForm == 1)
        {
            newHealthValue = playerStatusPtr->currentHealth - ((2 * count) * currentDamageMultiplier);
            d_a_alink::procWolfDamageInit(linkMapPtr, nullptr);
        }
        else
        {
            newHealthValue = playerStatusPtr->currentHealth - (count * currentDamageMultiplier);
            d_a_alink::procDamageInit(linkMapPtr, nullptr, 0);
        }

        // Make sure an underflow doesn't occur
        if (newHealthValue < 0)
        {
            newHealthValue = 0;
        }

        playerStatusPtr->currentHealth = static_cast<uint16_t>(newHealthValue);
    }

    KEEP_FUNC void handleBonkDamage()
    {
        if (bonksDoDamage)
        {
            using namespace libtp::tp;
            d_com_inf_game::dComIfG_inf_c* gameInfoPtr = &d_com_inf_game::dComIfG_gameInfo;
            libtp::tp::d_save::dSv_player_status_a_c* playerStatusPtr = &gameInfoPtr->save.save_file.player.player_status_a;
            int32_t newHealthValue;
            const uint8_t currentDamageMultiplier = damageMultiplier;

            if (playerStatusPtr->currentForm == 1)
            {
                newHealthValue = playerStatusPtr->currentHealth - (2 * currentDamageMultiplier);
            }
            else
            {
                newHealthValue = playerStatusPtr->currentHealth - currentDamageMultiplier; // Damage multiplier is 1 by default
            }

            // Make sure an underflow doesn't occur
            if (newHealthValue < 0)
            {
                newHealthValue = 0;
            }

            playerStatusPtr->currentHealth = static_cast<uint16_t>(newHealthValue);
        }
    }

    KEEP_FUNC libtp::tp::d_resource::dRes_info_c* handle_getResInfo(const char* arcName,
                                                                    libtp::tp::d_resource::dRes_info_c* objectInfo,
                                                                    int32_t size)
    {
        libtp::tp::d_resource::dRes_info_c* resourcePtr = return_getResInfo(arcName, objectInfo, size);

        rando::Randomizer* rando = randomizer;
        if (getCurrentSeed(rando) && resourcePtr)
        {
            rando->overrideObjectARC(resourcePtr, arcName);
        }

        return resourcePtr;
    }

    // This is called in the NON-MAIN thread which is loading the archive where
    // `mountArchive->mIsDone = true;` would be called normally (this is the
    // last thing that gets called before the archive is considered loaded). The
    // archive is no longer automatically marked as loaded, so we need to do
    // this ourselves when we are done. (This indicates that the archive is
    // loaded, and whatever was waiting on it will see this byte change the next
    // time it polls the completion status (polling happens once per frame?))
    KEEP_FUNC bool handle_mountArchive__execute(libtp::tp::m_Do_dvd_thread::mDoDvdThd_mountArchive_c* mountArchive)
    {
        const bool ret = return_mountArchive__execute(mountArchive);

        if (ret)
        {
            // Make sure the randomizer is loaded/enabled and a seed is loaded
            rando::Seed* seed;
            rando::Randomizer* rando = randomizer;

            if (seed = getCurrentSeed(rando), seed)
            {
                rando->recolorArchiveTextures(mountArchive);
            }
        }

        // Need to mark the archive as loaded once we are done modifying its
        // contents.
        mountArchive->mIsDone = true;

        return ret;
    };

    float __attribute__((noinline)) intToFloat(int32_t value)
    {
        return static_cast<float>(value);
    }
} // namespace mod