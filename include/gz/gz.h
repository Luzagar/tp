#ifndef GZ_H
#define GZ_H

#include "c/c_damagereaction.h"
#include "d/d_com_inf_game.h"
#include "d/d_item.h"
#include "d/d_item_data.h"
#include "gz/gz_capture.h"
#include "gz/gz_utility_misc.h"
#include "gz/gz_manager_cheats.h"
#include "gz/gz_manager_practice.h"
#include "gz/gz_manager_scene.h"
#include "gz/gz_manager_tools.h"
#include "umbra/umbra_nintendont.h"
#include "umbra/umbra_platform.h"
#include "umbra/umbra_storage.h"
#include "umbra/umbra_net.h"
#include "gz/gz_utility_notification.h"
#include "JSystem/J2DGraph/J2DPicture.h"
#include "JSystem/J2DGraph/J2DTextBox.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_machine.h"
#include "SSystem/SComponent/c_API_controller_pad.h"
#include "dolphin/dvd.h"

class JKRArchive;
class JKRHeap;
class dSelect_cursor_c;
class gzMainMenu_c;
class gzMenu_c;
class gzSetupWizard_c;
class gzTextBox;
class gzToolsMng_c;

#define COLOR_WHITE 0xFFFFFFFFu
#define COLOR_RED 0xFF0000FFu
#define COLOR_BLUE 0x0000FFFFu
#define COLOR_GREEN 0x00FF00FFu
#define COLOR_CYAN 0x00FFFFFFu
#define COLOR_YELLOW 0xFFFF00FFu
#define COLOR_MAGENTA 0xFF00FFFFu
#define COLOR_ORANGE 0xFFA500FFu
#define COLOR_GRAY 0x808080FFu

#define COLOR_AMETHYST 0x9966FFFF
#define COLOR_AQUAMARINE 0x71D9E2FF
#define COLOR_BANANA_MANIA 0xFAE7B5FF
#define COLOR_BOLD_CRIMSON 0xDC143CFF
#define COLOR_BUBBLEGUM_PINK 0xFF69B4FF
#define COLOR_CERULEAN 0x007BA7FF
#define COLOR_COSMIC_COBALT 0x2E2D88FF
#define COLOR_ELECTRIC_BLUE 0x7DF9FFFF
#define COLOR_FIERY_ORANGE 0xFF4500FF
#define COLOR_FLAMINGO_FEATHER 0xFC8EACFF
#define COLOR_GOLD_DROP 0xEE8000FF
#define COLOR_LEMON_YELLOW 0xFFF44FFF
#define COLOR_LIME_GREEN 0x32CD32FF
#define COLOR_MAGENTA_MAGIC 0xFF00FFFF
#define COLOR_MIDNIGHT_BLUE 0x191970FF
#define COLOR_MYSTICAL_PURPLE 0x9370DBFF
#define COLOR_NEON_CARROT 0xFFA343FF
#define COLOR_PERIWINKLE 0xCCCCFFFF
#define COLOR_SAPPHIRE_SPARKLE 0x0F52BAFF
#define COLOR_SHAMROCK_GREEN 0x009E60FF
#define COLOR_SUNNY_YELLOW 0xFFFF00FF
#define COLOR_TANGERINE_TWIST 0xFFA500FF
#define COLOR_TROPICAL_TURQUOISE 0x40E0D0FF
#define COLOR_VIVID_VIOLET 0x9F00FFFF
#define COLOR_WILD_STRAWBERRY 0xFF43A4FF
#define COLOR_ZESTY_CHARTREUSE 0x7FFF00FF

static const u32 GZ_TEXT_COLORS[] = {
    COLOR_AMETHYST, COLOR_AQUAMARINE, COLOR_BANANA_MANIA, COLOR_BOLD_CRIMSON,
    COLOR_BUBBLEGUM_PINK, COLOR_CERULEAN, COLOR_COSMIC_COBALT, COLOR_ELECTRIC_BLUE,
    COLOR_FIERY_ORANGE, COLOR_FLAMINGO_FEATHER, COLOR_GOLD_DROP, COLOR_LEMON_YELLOW,
    COLOR_LIME_GREEN, COLOR_MAGENTA_MAGIC, COLOR_MIDNIGHT_BLUE, COLOR_MYSTICAL_PURPLE,
    COLOR_NEON_CARROT, COLOR_PERIWINKLE, COLOR_SAPPHIRE_SPARKLE, COLOR_SHAMROCK_GREEN,
    COLOR_SUNNY_YELLOW, COLOR_TANGERINE_TWIST, COLOR_TROPICAL_TURQUOISE, COLOR_VIVID_VIOLET,
    COLOR_WILD_STRAWBERRY, COLOR_ZESTY_CHARTREUSE
};
static const int GZ_NUM_TEXT_COLORS = ARRAY_SIZE(GZ_TEXT_COLORS);

inline const char* gzGetThemeColorName(u32 color) {
    switch (color) {
    case COLOR_AMETHYST: return "amethyst";
    case COLOR_AQUAMARINE: return "aquamarine";
    case COLOR_BANANA_MANIA: return "banana mania";
    case COLOR_BOLD_CRIMSON: return "bold crimson";
    case COLOR_BUBBLEGUM_PINK: return "bubblegum pink";
    case COLOR_CERULEAN: return "cerulean";
    case COLOR_COSMIC_COBALT: return "cosmic cobalt";
    case COLOR_ELECTRIC_BLUE: return "electric blue";
    case COLOR_FIERY_ORANGE: return "fiery orange";
    case COLOR_FLAMINGO_FEATHER: return "flamingo feather";
    case COLOR_GOLD_DROP: return "gold drop";
    case COLOR_LEMON_YELLOW: return "lemon yellow";
    case COLOR_LIME_GREEN: return "lime green";
    case COLOR_MAGENTA_MAGIC: return "magenta magic";
    case COLOR_MIDNIGHT_BLUE: return "midnight blue";
    case COLOR_MYSTICAL_PURPLE: return "mystical purple";
    case COLOR_NEON_CARROT: return "neon carrot";
    case COLOR_PERIWINKLE: return "periwinkle";
    case COLOR_SAPPHIRE_SPARKLE: return "sapphire sparkle";
    case COLOR_SHAMROCK_GREEN: return "shamrock green";
    case COLOR_SUNNY_YELLOW: return "sunny yellow";
    case COLOR_TANGERINE_TWIST: return "tangerine twist";
    case COLOR_TROPICAL_TURQUOISE: return "tropical turquoise";
    case COLOR_VIVID_VIOLET: return "vivid violet";
    case COLOR_WHITE: return "white";
    case COLOR_WILD_STRAWBERRY: return "wild strawberry";
    case COLOR_ZESTY_CHARTREUSE: return "zesty chartreuse";
    default: return "unknown";
    }
}

struct gzCommandCombos_s {
    u32 mGorgeVoid;
    u32 mMoveLink;
    u32 mMoonJump;
    u32 mTeleportSave;
    u32 mTeleportLoad;
    u32 mFreeCamToggle;
};

struct gzToolsSettings_s {
    bool mMoveLink;
    bool mCoroTD;
    bool mElevatorEscape;
    bool mGorgeVoid;
    bool mEndingBlowMoonBoots;
    bool mLadderFreezardCancel;
    bool mRollChecker;
    bool mUniversalMapDelay;
    bool mAbMashRate;
    bool mInGameTimer;
    bool mInputViewer;
    bool mLinkDebugInfo;
    bool mLoadTimer;
    bool mStageInfo;
    bool mTeleport;
    bool mTimer;
    bool mFreeCam;
};

struct gzCheatsSettings_s {
    bool mDisableItemTimer;
    bool mDisableWalls;
    bool mFastBonkRecovery;
    bool mFastMovement;
    bool mInfiniteAir;
    bool mInfiniteArrows;
    bool mInfiniteBombs;
    bool mInfiniteHearts;
    bool mInfiniteOil;
    bool mInfiniteRupees;
    bool mInfiniteSlingshot;
    bool mInvincibleLink;
    bool mInvincibleEnemies;
    bool mMoonJump;
    bool mNoSinkingInSand;
    bool mSuperClawshot;
    bool mTransformAnywhere;
    bool mUnrestrictedItems;
};

struct gzSceneSettings_s {
    bool mFreezeTime;
    bool mFreezeActors;
    bool mFreezeCamera;
    bool mMuteBGM;
    bool mMuteSFX;
};

struct gzOnlineSettings_s {
    bool mStateStreaming;
    u32 mServerIP;      // big-endian IP (use umbraNet::makeIP)
    u16 mServerPort;    // default 52224 (0x00CC00)
};

struct gzSettings_s {
    u32 mTextColor;  // todo: just make this an index?
    bool mDropShadows;
    bool mSwapEquips;
    bool mReloadType;
    u8 mCursorType;
    bool mDisplayMode;
    bool mMenuPausesGame;
    bool mBootToMenu;
    bool mMenuSfx;

    gzCheatsSettings_s mCheats;
    gzToolsSettings_s mTools;
    gzSceneSettings_s mScene;
    gzCommandCombos_s mCommandCombos;
    gzOnlineSettings_s mOnline;
};

// tpgz config file header
struct gzConfigHeader_s {
    u32 version;
    u32 settingsOffset;

    u8 reserved[0x20 - 0x8];
};

struct gzCursor {
    int x;
    int y;
};

class gzInfo_c {
public:
    static const int GZ_SAVE_VERSION = 1;

    gzInfo_c() : mMemCard("tpgzcfg") {
        mGZInitialized = false;
        mIsPlayInfoInit = false;
        mInitPhase = INIT_PHASE_IDLE;
        mMenuResourcesLoaded = false;
        mMenuLoadStep = 0;
    }

    enum InitPhase_e {
        INIT_PHASE_IDLE,
        INIT_PHASE_SETUP_RESOURCES,
        INIT_PHASE_DONE
    };

    enum gzInfoMenu_CursorType_e {
        CURSOR_CLASSIC = 1,
        CURSOR_TP,
        CURSOR_BOTH,
    };

    void startInit();
    int _delete();
    int execute();
    int draw();
    void loadMenuTextures();
    void updateStickTriggers();
    void loadMenuResourcesBatch();
    void loadMenuResources();

    void drawMenuFrame(u8 baseAlpha, u32 theme);
    void drawButtonHints();

    void startIconPreload();
    void pollIconPreload();
    J2DPicture* getCheckIcon() { return mpCheckIcon; }
    J2DPicture* getXMarkIcon() { return mpXMarkIcon; }
    ResTIMG* getIconAtlas() { return mPreloadsComplete ? (ResTIMG*)mpPreloadBufs[3] : NULL; }

    void loadDefaultSettings();
    int storeSettings();
    int loadSettings();
    int deleteSettings();
    void showHeapUsage();
    void setButtonFlags();
    void executeTools();
    void executeMoveLink();

    bool isDisplay() { return mDisplay; }

    gzCursor* getCursor() { return &mCursor; }
    dSelect_cursor_c* getTPCursor() { return mpTPCursor; }
    gzTextBox* getMenuDescription() { return mpMenuDescription; }
    
    void setMenuOption(bool i_opt) { mMenuOption = i_opt; }
    bool isMenuOption() { return mMenuOption; }

    s32 getTopLine() { return mTopLine; }
    void setTopLine(s32 i_topLine) { mTopLine = i_topLine; }

    s32 getVisibleLines() { return mVisibleLines; }
    void setVisibleLines(s32 i_visibleLines) { mVisibleLines = i_visibleLines; }

    u32 getCursorColor() { return getCursorType() & CURSOR_CLASSIC ? getTextColor() : COLOR_WHITE; }

    JUTFont* getFont() { return mpFont; }
    void setFont(JUTFont* i_font) { mpFont = i_font; }

    void sendNotification(const char* msg) { if (mpNotification != NULL) mpNotification->send(msg); }
    void sendNotification(const char* msg, int i_notificationType) { if (mpNotification != NULL) mpNotification->send(msg, (gzNotification_c::NotificationType)i_notificationType); }

    // General Settings
    bool isCursorTypeClassic() { return getCursorType() & CURSOR_CLASSIC; }
    bool isCursorTypeTP() { return getCursorType() & CURSOR_TP; }
    bool isDropShadows() { return mSettings.mDropShadows; }
    bool isMenuPausesGame() const { return mSettings.mMenuPausesGame; }
    bool isBootToMenu() const { return mSettings.mBootToMenu; }
    bool isMenuSfx() const { return mSettings.mMenuSfx; }
    bool isSwapEquips() const { return mSettings.mSwapEquips; }

    u8 getCursorType() const { return mSettings.mCursorType; }
    bool getDisplayMode() const { return mSettings.mDisplayMode; }
    bool getReloadType() const { return mSettings.mReloadType; }
    u32 getTextColor() const { return mSettings.mTextColor; }

    void setCursorType(u8 i_type) { mSettings.mCursorType = i_type; }
    void setDisplayMode(bool i_mode) { mSettings.mDisplayMode = i_mode; }
    void setDropShadows(bool i_dropShadows) { mSettings.mDropShadows = i_dropShadows; }
    void setMenuPausesGame(bool i_opt) { mSettings.mMenuPausesGame = i_opt; }
    void setBootToMenu(bool i_opt) { mSettings.mBootToMenu = i_opt; }
    void setMenuSfx(bool sfx) { mSettings.mMenuSfx = sfx; }
    void setReloadType(bool i_type) { mSettings.mReloadType = i_type; }
    void setSwapEquips(bool i_swapEquips) { mSettings.mSwapEquips = i_swapEquips; }
    void setTextColor(u32 i_textColor) { mSettings.mTextColor = i_textColor; }

    // Flags
    u8 getBossFlag() { return cDmr_SkipInfo; }
    bool isFlag_EponaStolen() { return dComIfGs_isEventBit(0x0580); }
    bool isFlag_EponaTamed() { return dComIfGs_isEventBit(0x0601); }
    bool isFlag_MaloMartCT() { return dComIfGs_isEventBit(0x2210); }
    bool isFlag_MapWarping() { return dComIfGs_isEventBit(0x0604); }
    bool isFlag_MidnaCharge() { return dComIfGs_isEventBit(0x0501); }
    bool isFlag_MidnaHealthy() { return dComIfGs_isEventBit(0x1E08); }
    bool isFlag_MidnaOnBack() { return dComIfGs_isTransformLV(3); }
    bool isFlag_MidnaOnZ() { return dComIfGs_isEventBit(0x0C10); }
    bool isFlag_RuslTD() { return dComIfGs_isTmpBit(0x0006); }
    bool isFlag_TransformWarp() { return dComIfGs_isEventBit(0x0D04); }
    bool isFlag_WolfSense() { return dComIfGs_isEventBit(0x4308); }

    void setFlag_BossFlag(u8 i_value) { cDmr_SkipInfo = i_value; }
    void setFlag_EponaStolen(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x0580) : dComIfGs_offEventBit(0x0580); }
    void setFlag_EponaTamed(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x0601) : dComIfGs_offEventBit(0x0601); }
    void setFlag_MidnaCharge(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x0501) : dComIfGs_offEventBit(0x0501); }
    void setFlag_MidnaHealthy(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x1E08) : dComIfGs_offEventBit(0x1E08); }
    void setFlag_MidnaOnBack(bool i_opt) { i_opt ? dComIfGs_onTransformLV(3): dComIfGs_offTransformLV(3); }
    void setFlag_MidnaOnZ(bool i_opt)  { i_opt ? dComIfGs_onEventBit(0x0C10) : dComIfGs_offEventBit(0x0C10); }
    void setFlag_MaloMartCT(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x2210) : dComIfGs_offEventBit(0x2210); }
    void setFlag_MapWarping(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x0604) : dComIfGs_offEventBit(0x0604); }
    void setFlag_RuslTD(bool i_opt) { i_opt ? dComIfGs_onTmpBit(0x0006) : dComIfGs_offTmpBit(0x0006); }
    void setFlag_TransformWarp(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x0D04) : dComIfGs_offEventBit(0x0D04); }
    void setFlag_WolfSense(bool i_opt) { i_opt ? dComIfGs_onEventBit(0x4308) : dComIfGs_offEventBit(0x4308); }

    // Cheats
    bool isCheat_DisableItemTimer() { return mSettings.mCheats.mDisableItemTimer; }
    bool isCheat_DisableWalls() { return mSettings.mCheats.mDisableWalls; }
    bool isCheat_InfiniteAir() { return mSettings.mCheats.mInfiniteAir; }
    bool isCheat_InfiniteArrows() { return mSettings.mCheats.mInfiniteArrows; }
    bool isCheat_InfiniteBombs() { return mSettings.mCheats.mInfiniteBombs; }
    bool isCheat_InfiniteHearts() { return mSettings.mCheats.mInfiniteHearts; }
    bool isCheat_InfiniteOil() { return mSettings.mCheats.mInfiniteOil; }
    bool isCheat_InfiniteRupees() { return mSettings.mCheats.mInfiniteRupees; }
    bool isCheat_InfiniteSlingshot() { return mSettings.mCheats.mInfiniteSlingshot; }
    bool isCheat_InvincibleEnemies() { return mSettings.mCheats.mInvincibleEnemies; }
    bool isCheat_InvincibleLink() { return mSettings.mCheats.mInvincibleLink; }
    bool isCheat_MoonJump() { return mSettings.mCheats.mMoonJump; }
    bool isCheat_SuperClawshot() { return mSettings.mCheats.mSuperClawshot; }
    bool isCheat_TransformAnywhere() { return mSettings.mCheats.mTransformAnywhere; }
    bool isCheat_UnrestrictedItems() { return mSettings.mCheats.mUnrestrictedItems; }

    void setCheat_DisableItemTimer(bool i_opt) { mSettings.mCheats.mDisableItemTimer = i_opt; }
    void setCheat_DisableWalls(bool i_opt) { mSettings.mCheats.mDisableWalls = i_opt; }
    void setCheat_InfiniteAir(bool i_opt) { mSettings.mCheats.mInfiniteAir = i_opt; }
    void setCheat_InfiniteArrows(bool i_opt) { mSettings.mCheats.mInfiniteArrows = i_opt; }
    void setCheat_InfiniteBombs(bool i_opt) { mSettings.mCheats.mInfiniteBombs = i_opt; }
    void setCheat_InfiniteHearts(bool i_opt) { mSettings.mCheats.mInfiniteHearts = i_opt; }
    void setCheat_InfiniteOil(bool i_opt) { mSettings.mCheats.mInfiniteOil = i_opt; }
    void setCheat_InfiniteRupees(bool i_opt) { mSettings.mCheats.mInfiniteRupees = i_opt; }
    void setCheat_InfiniteSlingshot(bool i_opt) { mSettings.mCheats.mInfiniteSlingshot = i_opt; }
    void setCheat_InvincibleEnemies(bool i_opt) { mSettings.mCheats.mInvincibleEnemies = i_opt; }
    void setCheat_InvincibleLink(bool i_opt) { mSettings.mCheats.mInvincibleLink = i_opt; }
    void setCheat_MoonJump(bool i_opt) { mSettings.mCheats.mMoonJump = i_opt; }
    void setCheat_SuperClawshot(bool i_opt) { mSettings.mCheats.mSuperClawshot = i_opt; }
    void setCheat_TransformAnywhere(bool i_opt) { mSettings.mCheats.mTransformAnywhere = i_opt; }
    void setCheat_UnrestrictedItems(bool i_opt) { mSettings.mCheats.mUnrestrictedItems = i_opt; }

    // Tools
    bool isTool_AbMashRate() { return mSettings.mTools.mAbMashRate; }
    bool isTool_CoroTD() { 
        mSettings.mTools.mCoroTD = dComIfGs_isTmpBit(0x0002);
        return mSettings.mTools.mCoroTD;
    }
    bool isTool_ElevatorEscape() { return mSettings.mTools.mElevatorEscape; }
    bool isTool_EndingBlowMoonBoots() { return mSettings.mTools.mEndingBlowMoonBoots; }
    bool isCheat_FastBonkRecovery() { return mSettings.mCheats.mFastBonkRecovery; }
    bool isCheat_FastMovement() { return mSettings.mCheats.mFastMovement; }
    bool isTool_GorgeVoid() { return mSettings.mTools.mGorgeVoid; }
    bool isTool_InGameTimer() { return mSettings.mTools.mInGameTimer; }
    bool isTool_InputViewer() { return mSettings.mTools.mInputViewer; }
    bool isTool_LadderFreezardCancel() { return mSettings.mTools.mLadderFreezardCancel; }
    bool isTool_LinkDebugInfo() { return mSettings.mTools.mLinkDebugInfo; }
    bool isTool_LoadTimer() { return mSettings.mTools.mLoadTimer; }
    bool isTool_MoveLink() { return mSettings.mTools.mMoveLink; }
    bool isCheat_NoSinkingInSand() { return mSettings.mCheats.mNoSinkingInSand; }
    bool isTool_RollChecker() { return mSettings.mTools.mRollChecker; }
    bool isTool_StageInfo() { return mSettings.mTools.mStageInfo; }
    bool isTool_Teleport() { return mSettings.mTools.mTeleport; }
    bool isTool_Timer() { return mSettings.mTools.mTimer; }
    bool isTool_FreeCam() { return mSettings.mTools.mFreeCam; }
    bool isTool_UniversalMapDelay() { return mSettings.mTools.mUniversalMapDelay; }
    bool isTool_MoveLinkActive() { return mToolsMng.isMoveLinkActive(); }

    void setTool_AbMashRate(bool i_opt) { mSettings.mTools.mAbMashRate = i_opt; }
    void setTool_CoroTD(bool i_opt) {
        i_opt ? dComIfGs_onTmpBit(0x0002) : dComIfGs_offTmpBit(0x0002);
        mSettings.mTools.mCoroTD = i_opt;
    }
    void setTool_ElevatorEscape(bool i_opt) { mSettings.mTools.mElevatorEscape = i_opt; }
    void setTool_EndingBlowMoonBoots(bool i_opt) { mSettings.mTools.mEndingBlowMoonBoots = i_opt; }
    void setCheat_FastBonkRecovery(bool i_opt) { mSettings.mCheats.mFastBonkRecovery = i_opt; }
    void setCheat_FastMovement(bool i_opt) { mSettings.mCheats.mFastMovement = i_opt; }
    void setTool_GorgeVoid(bool i_opt) { mSettings.mTools.mGorgeVoid = i_opt; }
    void setTool_InGameTimer(bool i_opt) { mSettings.mTools.mInGameTimer = i_opt; }
    void setTool_InputViewer(bool i_opt) { mSettings.mTools.mInputViewer = i_opt; }
    void setTool_LadderFreezardCancel(bool i_opt) { mSettings.mTools.mLadderFreezardCancel = i_opt; }
    void setTool_LinkDebugInfo(bool i_opt) { mSettings.mTools.mLinkDebugInfo = i_opt; }
    void setTool_LoadTimer(bool i_opt) { mSettings.mTools.mLoadTimer = i_opt; }
    void setTool_MoveLink(bool i_opt) { mSettings.mTools.mMoveLink = i_opt; }
    void setCheat_NoSinkingInSand(bool i_opt) { mSettings.mCheats.mNoSinkingInSand = i_opt; }
    void setTool_RollChecker(bool i_opt) { mSettings.mTools.mRollChecker = i_opt; }
    void setTool_StageInfo(bool i_opt) { mSettings.mTools.mStageInfo = i_opt; }
    void setTool_Teleport(bool i_opt) { mSettings.mTools.mTeleport = i_opt; }
    void setTool_Timer(bool i_opt) { mSettings.mTools.mTimer = i_opt; }
    void setTool_FreeCam(bool i_opt) { mSettings.mTools.mFreeCam = i_opt; }
    void setTool_UniversalMapDelay(bool i_opt) { mSettings.mTools.mUniversalMapDelay = i_opt; }    

    // Online
    bool isOnline_StateStreaming() { return mSettings.mOnline.mStateStreaming; }
    u32 getOnline_ServerIP() { return mSettings.mOnline.mServerIP; }
    u16 getOnline_ServerPort() { return mSettings.mOnline.mServerPort; }

    void setOnline_StateStreaming(bool i_opt) { mSettings.mOnline.mStateStreaming = i_opt; }
    void setOnline_ServerIP(u32 i_ip) { mSettings.mOnline.mServerIP = i_ip; }
    void setOnline_ServerPort(u16 i_port) { mSettings.mOnline.mServerPort = i_port; }

    // Scene
    bool isScene_FreezeTime() { return mSettings.mScene.mFreezeTime; }
    bool isScene_FreezeActors() { return mSettings.mScene.mFreezeActors; }
    bool isScene_FreezeCamera() { return mSettings.mScene.mFreezeCamera; }
    bool isScene_MuteBGM() { return mSettings.mScene.mMuteBGM; }
    bool isScene_MuteSFX() { return mSettings.mScene.mMuteSFX; }

    void setScene_FreezeTime(bool i_opt) { mSettings.mScene.mFreezeTime = i_opt; }
    void setScene_FreezeActors(bool i_opt) { mSettings.mScene.mFreezeActors = i_opt; }
    void setScene_FreezeCamera(bool i_opt) { mSettings.mScene.mFreezeCamera = i_opt; }
    void setScene_MuteBGM(bool i_opt) { mSettings.mScene.mMuteBGM = i_opt; }
    void setScene_MuteSFX(bool i_opt) { mSettings.mScene.mMuteSFX = i_opt; }


    void seStart(u32 i_sfxID) {
        if (mSettings.mMenuSfx) mDoAud_seStart(i_sfxID, NULL, 0, 0);
    }

    u8 nextCursorType() {
        switch (getCursorType()) {
        case CURSOR_CLASSIC:
            return CURSOR_TP;
        case CURSOR_TP:
            return CURSOR_BOTH;
        case CURSOR_BOTH:
            return CURSOR_CLASSIC;
        default:
            return CURSOR_CLASSIC;
        }
    }

    u8 prevCursorType() {
        switch (getCursorType()) {
        case CURSOR_CLASSIC:
            return CURSOR_BOTH;
        case CURSOR_BOTH:
            return CURSOR_TP;
        case CURSOR_TP:
            return CURSOR_CLASSIC;
        default:
            return CURSOR_CLASSIC;
        }
    }

    u32 nextTextColor() {
        u32 current = getTextColor();
        for (int i = 0; i < GZ_NUM_TEXT_COLORS; i++) {
            if (GZ_TEXT_COLORS[i] == current) {
                return GZ_TEXT_COLORS[(i + 1) % GZ_NUM_TEXT_COLORS];
            }
        }
        return GZ_TEXT_COLORS[0];
    }

    u32 prevTextColor() {
        u32 current = getTextColor();
        for (int i = 0; i < GZ_NUM_TEXT_COLORS; i++) {
            if (GZ_TEXT_COLORS[i] == current) {
                return GZ_TEXT_COLORS[(i - 1 + GZ_NUM_TEXT_COLORS) % GZ_NUM_TEXT_COLORS];
            }
        }
        return GZ_TEXT_COLORS[0];
    }

    J2DPicture* mpIcon;
    J2DPicture* mpBackground;
    J2DPicture* mpBannerBg;
    J2DPicture* mpSwirl;

    J2DPicture* mpBtnABBase;
    J2DPicture* mpBtnAText;
    J2DPicture* mpBtnBText;
    J2DPicture* mpBtnXBase;
    J2DPicture* mpBtnXText;
    J2DPicture* mpBtnYBase;
    J2DPicture* mpBtnYText;
    J2DPicture* mpBtnZBase;
    J2DPicture* mpBtnZText;
    J2DPicture* mpBtnLRBase;
    J2DPicture* mpBtnLText;
    J2DPicture* mpBtnRText;
    gzTextBox* mpHeader;

    gzTextBox* mpButtonHintText;

    gzMenu_c* mpCurrentMenu;
    gzMainMenu_c* mpMainMenu;
    gzNotification_c* mpNotification;
    dSelect_cursor_c* mpTPCursor;
    gzCapture_c* mpCapture;
    gzSetupWizard_c* mpSetupWizard;
    gzTextBox* mpMenuDescription;
    bool mMenuOption;
    s32 mTopLine;
    s32 mVisibleLines;

    JUTFont* mpFont;
    s16 mInputWaitTimer;
    bool mDisplay;
    bool mGZInitialized;
    bool mIsPlayInfoInit;
    int mInitPhase;
    bool mMenuResourcesLoaded;
    int mMenuLoadStep;
    bool mMenuTexturesLoaded;
    bool mWasPausedOnOpen;

    u32 mStickTriggers;
    u32 mRepeatDirection;
    s16 mRepeatCounter;
    u32 mButtonRepeatTriggers;
    u32 mButtonRepeatState;
    s16 mButtonRepeatCounter;
    gzSettings_s mSettings;
    gzCursor mCursor;
    gzSaveLoaderMng_c mSaveLoaderMng;
    gzCheatsMng_c mCheatsMng;
    gzToolsMng_c mToolsMng;
    gzSceneMng_c mSceneMng;
    umbraStorageNintendont mSD;
    umbraNet mNet;
    umbraStorageMemcard mMemCard;

    f32 mIconXPos;
    f32 mIconYPos;
    f32 mIconWidth;
    f32 mIconHeight;

    f32 mHeaderXPos;
    f32 mHeaderYPos;

    f32 mBackgroundXPos;
    f32 mBackgroundYPos;
    f32 mBackgroundWidth;
    f32 mBackgroundHeight;

    f32 mBorderAnimTimer;
    u8 mBorderHighlightAlpha;

    f32 mSeparatorXPos;
    f32 mSeparatorVisibleX;
    f32 mSeparatorHiddenX;

    u8 mGzGroupID;

    static const int PRELOAD_COUNT = 4;
    DVDFileInfo mPreloadFileInfos[PRELOAD_COUNT];
    void* mpPreloadBufs[PRELOAD_COUNT];
    bool mPreloadAsyncPending[PRELOAD_COUNT];
    bool mPreloadsComplete;
    J2DPicture* mpCheckIcon;
    J2DPicture* mpXMarkIcon;
};

extern gzInfo_c g_gzInfo;

inline ResTIMG* gzInfo_getIconAtlas() { return g_gzInfo.getIconAtlas(); }
inline J2DPicture* gzInfo_getCheckIcon() { return g_gzInfo.getCheckIcon(); }
inline J2DPicture* gzInfo_getXMarkIcon() { return g_gzInfo.getXMarkIcon(); }
inline gzCursor* gzInfo_getCursor() { return g_gzInfo.getCursor(); }
inline dSelect_cursor_c* gzInfo_getTPCursor() { return g_gzInfo.getTPCursor(); }
inline gzTextBox* gzInfo_getMenuDescription() { return g_gzInfo.getMenuDescription(); }
inline bool gzInfo_isMenuOption() { return g_gzInfo.isMenuOption(); }
inline void gzInfo_setMenuOption(bool i_opt) { g_gzInfo.setMenuOption(i_opt); }
inline void gzInfo_onMenuOption() { g_gzInfo.setMenuOption(true); }
inline void gzInfo_offMenuOption() { g_gzInfo.setMenuOption(false); }
inline s32 gzInfo_getTopLine() { return g_gzInfo.getTopLine(); }
inline void gzInfo_setTopLine(s32 i_topLine) { g_gzInfo.setTopLine(i_topLine); }
inline void gzInfo_resetTopLine() { g_gzInfo.setTopLine(0); }
inline s32 gzInfo_getVisibleLines() { return g_gzInfo.getVisibleLines(); }
inline void gzInfo_setVisibleLines(s32 i_visibleLines) { g_gzInfo.setVisibleLines(i_visibleLines); }
inline u32 gzInfo_getCursorColor() { return g_gzInfo.getCursorColor(); }
inline u32 gzInfo_getTextColor() { return g_gzInfo.getTextColor(); }
inline u8 gzInfo_getCursorType() { return g_gzInfo.getCursorType(); }
inline bool gzInfo_getDisplayMode() { return g_gzInfo.getDisplayMode(); }
inline bool gzInfo_getReloadType() { return g_gzInfo.getReloadType(); }
inline u8 gzInfo_getBossFlag() { return g_gzInfo.getBossFlag(); }

inline int gzInfo_storeSettings() { return g_gzInfo.storeSettings(); }
inline int gzInfo_loadSettings() { return g_gzInfo.loadSettings(); }
inline int gzInfo_deleteSettings() { return g_gzInfo.deleteSettings(); }
inline u32 gzInfo_nextCursorType() { return g_gzInfo.nextCursorType(); }
inline u32 gzInfo_prevCursorType() { return g_gzInfo.prevCursorType(); }
inline u32 gzInfo_nextTextColor() { return g_gzInfo.nextTextColor(); }
inline u32 gzInfo_prevTextColor() { return g_gzInfo.prevTextColor(); }

inline void gzInfo_seStart(u32 i_sfxID) { g_gzInfo.seStart(i_sfxID); }
inline void gzInfo_sendNotification(const char* msg) { g_gzInfo.sendNotification(msg); }
inline void gzInfo_sendNotification(const char* msg, int i_notificationType) { g_gzInfo.sendNotification(msg, i_notificationType); }

inline void gzInfo_returnToLoader() {
    if (umbraDetectPlatform() != PLATFORM_NINTENDONT_UMBRA) {
        gzInfo_sendNotification("exit requires umbra nintendont");
        return;
    }
    ninReturnToLoader();
}

inline bool gzInfo_isInDungeon(int i_stageNo) {
    // Check if we're in the dungeon, and return true
    switch (i_stageNo) {
    case 16:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN05") == 0) {
            return true;
        }
        break;
    case 17:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN04") == 0) {
            return true;
        }
        break;
    case 18:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN01") == 0) {
            return true;
        }
        break;
    case 19:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN10") == 0) {
            return true;
        }
        break;
    case 20:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN11") == 0) {
            return true;
        }
        break;
    case 21:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN06") == 0) {
            return true;
        }
        break;
    case 22:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN07") == 0) {
            return true;
        }
        break;
    case 23:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN08") == 0) {
            return true;
        }
        break;
    case 24:
        if (strcmp(dComIfGp_getStartStageName(), "D_MN09") == 0) {
            return true;
        }
        break;
    }

    return false;
}

inline bool gzInfo_isBossDefeated(int i_stageNo) { 
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isStageBossEnemy() : dComIfGs_isSaveStageBossEnemy(i_stageNo);
}

inline bool gzInfo_isMiniBossDefeated(int i_stageNo) { 
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isStageMiddleBoss() : dComIfGs_isSaveStageMiddleBoss(i_stageNo);
}

inline bool gzInfo_isCursorTypeClassic() { return g_gzInfo.isCursorTypeClassic(); }
inline bool gzInfo_isCursorTypeTP() { return g_gzInfo.isCursorTypeTP(); }
inline bool gzInfo_isDisplayModeInterlaced() { return g_gzInfo.getDisplayMode() == false; }
inline bool gzInfo_isDisplayModeProgressive() { return g_gzInfo.getDisplayMode() == true; }
inline bool gzInfo_isDropShadows() { return g_gzInfo.isDropShadows(); }

inline bool gzInfo_isDungeonBossKey(int i_stageNo) { 
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isDungeonItemBossKey() : dComIfGs_isSaveDungeonItemBossKey(i_stageNo);
}

inline bool gzInfo_isDungeonCompass(int i_stageNo) { 
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isDungeonItemCompass() : dComIfGs_isSaveDungeonItemCompass(i_stageNo);
}

inline bool gzInfo_isDungeonHeartContainer(int i_stageNo) { 
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isStageLife() : dComIfGs_isSaveStageLife(i_stageNo);
}

inline bool gzInfo_isDungeonMap(int i_stageNo) {
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isDungeonItemMap() : dComIfGs_isSaveDungeonItemMap(i_stageNo);
}

inline bool gzInfo_isDungeonOoccoo(int i_stageNo) { 
    return gzInfo_isInDungeon(i_stageNo) ? dComIfGs_isDungeonItemWarp() : dComIfGs_isSaveDungeonItemWarp(i_stageNo); 
}

// Flags
inline bool gzInfo_isFlag_BossFlag() { return gzInfo_getBossFlag() > 0; }
inline bool gzInfo_isFlag_EponaStolen() { return g_gzInfo.isFlag_EponaStolen(); }
inline bool gzInfo_isFlag_EponaTamed() { return g_gzInfo.isFlag_EponaTamed(); }
inline bool gzInfo_isFlag_MaloMartCT() { return g_gzInfo.isFlag_MaloMartCT(); }
inline bool gzInfo_isFlag_MapWarping() { return g_gzInfo.isFlag_MapWarping(); }
inline bool gzInfo_isFlag_MidnaCharge() { return g_gzInfo.isFlag_MidnaCharge(); }
inline bool gzInfo_isFlag_MidnaHealthy() { return g_gzInfo.isFlag_MidnaHealthy(); }
inline bool gzInfo_isFlag_MidnaOnBack() { return g_gzInfo.isFlag_MidnaOnBack(); }
inline bool gzInfo_isFlag_MidnaOnZ() { return g_gzInfo.isFlag_MidnaOnZ(); }
inline bool gzInfo_isFlag_RuslTD() { return g_gzInfo.isFlag_RuslTD(); }
inline bool gzInfo_isFlag_TransformWarp() { return g_gzInfo.isFlag_TransformWarp(); }
inline bool gzInfo_isFlag_WolfSense() { return g_gzInfo.isFlag_WolfSense(); }

inline void gzInfo_setFlag_BossFlag(u8 value) { g_gzInfo.setFlag_BossFlag(value); }

inline void gzInfo_onFlag_BossFlag() { g_gzInfo.setFlag_BossFlag(50); }
inline void gzInfo_onFlag_EponaStolen() { g_gzInfo.setFlag_EponaStolen(true); }
inline void gzInfo_onFlag_EponaTamed() { g_gzInfo.setFlag_EponaTamed(true); }
inline void gzInfo_onFlag_MaloMartCT() { g_gzInfo.setFlag_MaloMartCT(true); }
inline void gzInfo_onFlag_MapWarping() { g_gzInfo.setFlag_MapWarping(true); }
inline void gzInfo_onFlag_MidnaCharge() { g_gzInfo.setFlag_MidnaCharge(true); }
inline void gzInfo_onFlag_MidnaHealthy() { g_gzInfo.setFlag_MidnaHealthy(true); }
inline void gzInfo_onFlag_MidnaOnBack() { g_gzInfo.setFlag_MidnaOnBack(true); }
inline void gzInfo_onFlag_MidnaOnZ() { g_gzInfo.setFlag_MidnaOnZ(true); }
inline void gzInfo_onFlag_RuslTD() { g_gzInfo.setFlag_RuslTD(true); }
inline void gzInfo_onFlag_TransformWarp() { g_gzInfo.setFlag_TransformWarp(true); }
inline void gzInfo_onFlag_WolfSense() { g_gzInfo.setFlag_WolfSense(true); }

inline void gzInfo_offFlag_BossFlag() { g_gzInfo.setFlag_BossFlag(0); }
inline void gzInfo_offFlag_EponaStolen() { g_gzInfo.setFlag_EponaStolen(false); }
inline void gzInfo_offFlag_EponaTamed() { g_gzInfo.setFlag_EponaTamed(false); }
inline void gzInfo_offFlag_MaloMartCT() { g_gzInfo.setFlag_MaloMartCT(false); }
inline void gzInfo_offFlag_MapWarping() { g_gzInfo.setFlag_MapWarping(false); }
inline void gzInfo_offFlag_MidnaCharge() { g_gzInfo.setFlag_MidnaCharge(false); }
inline void gzInfo_offFlag_MidnaHealthy() { g_gzInfo.setFlag_MidnaHealthy(false); }
inline void gzInfo_offFlag_MidnaOnBack() { g_gzInfo.setFlag_MidnaOnBack(false); }
inline void gzInfo_offFlag_MidnaOnZ() { g_gzInfo.setFlag_MidnaOnZ(false); }
inline void gzInfo_offFlag_RuslTD() { g_gzInfo.setFlag_RuslTD(false); }
inline void gzInfo_offFlag_TransformWarp() { g_gzInfo.setFlag_TransformWarp(false); }
inline void gzInfo_offFlag_WolfSense() { g_gzInfo.setFlag_WolfSense(false); }

// Cheats
inline bool gzInfo_isCheat_InfiniteAir() { return g_gzInfo.isCheat_InfiniteAir(); }
inline bool gzInfo_isCheat_InfiniteArrows() { return g_gzInfo.isCheat_InfiniteArrows(); }
inline bool gzInfo_isCheat_InfiniteBombs() { return g_gzInfo.isCheat_InfiniteBombs(); }
inline bool gzInfo_isCheat_InfiniteHearts() { return g_gzInfo.isCheat_InfiniteHearts(); }
inline bool gzInfo_isCheat_InfiniteOil() { return g_gzInfo.isCheat_InfiniteOil(); }
inline bool gzInfo_isCheat_InfiniteRupees() { return g_gzInfo.isCheat_InfiniteRupees(); }
inline bool gzInfo_isCheat_InfiniteSlingshot() { return g_gzInfo.isCheat_InfiniteSlingshot(); }
inline bool gzInfo_isCheat_InvincibleEnemies() { return g_gzInfo.isCheat_InvincibleEnemies(); }
inline bool gzInfo_isCheat_InvincibleLink() { return g_gzInfo.isCheat_InvincibleLink(); }
inline bool gzInfo_isCheat_MoonJump() { return g_gzInfo.isCheat_MoonJump(); }
inline bool gzInfo_isCheat_NoSinkingInSand() { return g_gzInfo.isCheat_NoSinkingInSand(); }
inline bool gzInfo_isCheat_SuperClawshot() { return g_gzInfo.isCheat_SuperClawshot(); }
inline bool gzInfo_isCheat_TransformAnywhere() { return g_gzInfo.isCheat_TransformAnywhere(); }
inline bool gzInfo_isCheat_UnrestrictedItems() { return g_gzInfo.isCheat_UnrestrictedItems(); }
inline bool gzInfo_isCheat_DisableItemTimer() { return g_gzInfo.isCheat_DisableItemTimer(); }
inline bool gzInfo_isCheat_DisableWalls() { return g_gzInfo.isCheat_DisableWalls(); }
inline bool gzInfo_isCheat_FastBonkRecovery() { return g_gzInfo.isCheat_FastBonkRecovery(); }
inline bool gzInfo_isCheat_FastMovement() { return g_gzInfo.isCheat_FastMovement(); }

inline void gzInfo_onCheat_DisableItemTimer() { g_gzInfo.setCheat_DisableItemTimer(true); }
inline void gzInfo_onCheat_DisableWalls() { g_gzInfo.setCheat_DisableWalls(true); }
inline void gzInfo_onCheat_FastBonkRecovery() { g_gzInfo.setCheat_FastBonkRecovery(true); }
inline void gzInfo_onCheat_FastMovement() { g_gzInfo.setCheat_FastMovement(true); }
inline void gzInfo_onCheat_InfiniteAir() { g_gzInfo.setCheat_InfiniteAir(true); }
inline void gzInfo_onCheat_InfiniteArrows() { g_gzInfo.setCheat_InfiniteArrows(true); }
inline void gzInfo_onCheat_InfiniteBombs() { g_gzInfo.setCheat_InfiniteBombs(true); }
inline void gzInfo_onCheat_InfiniteHearts() { g_gzInfo.setCheat_InfiniteHearts(true); }
inline void gzInfo_onCheat_InfiniteOil() { g_gzInfo.setCheat_InfiniteOil(true); }
inline void gzInfo_onCheat_InfiniteRupees() { g_gzInfo.setCheat_InfiniteRupees(true); }
inline void gzInfo_onCheat_InfiniteSlingshot() { g_gzInfo.setCheat_InfiniteSlingshot(true); }
inline void gzInfo_onCheat_InvincibleEnemies() { g_gzInfo.setCheat_InvincibleEnemies(true); }
inline void gzInfo_onCheat_InvincibleLink() { g_gzInfo.setCheat_InvincibleLink(true); }
inline void gzInfo_onCheat_MoonJump() { g_gzInfo.setCheat_MoonJump(true); }
inline void gzInfo_onCheat_NoSinkingInSand() { g_gzInfo.setCheat_NoSinkingInSand(true); }
inline void gzInfo_onCheat_SuperClawshot() { g_gzInfo.setCheat_SuperClawshot(true); }
inline void gzInfo_onCheat_TransformAnywhere() { g_gzInfo.setCheat_TransformAnywhere(true); }
inline void gzInfo_onCheat_UnrestrictedItems() { g_gzInfo.setCheat_UnrestrictedItems(true); }

inline void gzInfo_offCheat_DisableItemTimer() { g_gzInfo.setCheat_DisableItemTimer(false); }
inline void gzInfo_offCheat_DisableWalls() { g_gzInfo.setCheat_DisableWalls(false); }
inline void gzInfo_offCheat_FastBonkRecovery() { g_gzInfo.setCheat_FastBonkRecovery(false); }
inline void gzInfo_offCheat_FastMovement() { g_gzInfo.setCheat_FastMovement(false); }
inline void gzInfo_offCheat_InfiniteAir() { g_gzInfo.setCheat_InfiniteAir(false); }
inline void gzInfo_offCheat_InfiniteArrows() { g_gzInfo.setCheat_InfiniteArrows(false); }
inline void gzInfo_offCheat_InfiniteBombs() { g_gzInfo.setCheat_InfiniteBombs(false); }
inline void gzInfo_offCheat_InfiniteHearts() { g_gzInfo.setCheat_InfiniteHearts(false); }
inline void gzInfo_offCheat_InfiniteOil() { g_gzInfo.setCheat_InfiniteOil(false); }
inline void gzInfo_offCheat_InfiniteRupees() { g_gzInfo.setCheat_InfiniteRupees(false); }
inline void gzInfo_offCheat_InfiniteSlingshot() { g_gzInfo.setCheat_InfiniteSlingshot(false); }
inline void gzInfo_offCheat_InvincibleEnemies() { g_gzInfo.setCheat_InvincibleEnemies(false); }
inline void gzInfo_offCheat_InvincibleLink() { g_gzInfo.setCheat_InvincibleLink(false); }
inline void gzInfo_offCheat_MoonJump() { g_gzInfo.setCheat_MoonJump(false); }
inline void gzInfo_offCheat_NoSinkingInSand() { g_gzInfo.setCheat_NoSinkingInSand(false); }
inline void gzInfo_offCheat_SuperClawshot() { g_gzInfo.setCheat_SuperClawshot(false); }
inline void gzInfo_offCheat_TransformAnywhere() { g_gzInfo.setCheat_TransformAnywhere(false); }
inline void gzInfo_offCheat_UnrestrictedItems() { g_gzInfo.setCheat_UnrestrictedItems(false); }

// Tools
inline bool gzInfo_isTool_CoroTD() { return g_gzInfo.isTool_CoroTD(); }
inline bool gzInfo_isTool_ElevatorEscape() { return g_gzInfo.isTool_ElevatorEscape(); }
inline bool gzInfo_isTool_EndingBlowMoonBoots() { return g_gzInfo.isTool_EndingBlowMoonBoots(); }
inline bool gzInfo_isTool_GorgeVoid() { return g_gzInfo.isTool_GorgeVoid(); }
inline bool gzInfo_isTool_LadderFreezardCancel() { return g_gzInfo.isTool_LadderFreezardCancel(); }
inline bool gzInfo_isTool_MoveLink() { return g_gzInfo.isTool_MoveLink(); }
inline bool gzInfo_isTool_MoveLinkActive() { return g_gzInfo.isTool_MoveLinkActive(); }
inline bool gzInfo_isTool_RollChecker() { return g_gzInfo.isTool_RollChecker(); }
inline bool gzInfo_isTool_UniversalMapDelay() { return g_gzInfo.isTool_UniversalMapDelay(); }
inline bool gzInfo_isTool_AbMashRate() { return g_gzInfo.isTool_AbMashRate(); }
inline bool gzInfo_isTool_LinkDebugInfo() { return g_gzInfo.isTool_LinkDebugInfo(); }
inline bool gzInfo_isTool_InGameTimer() { return g_gzInfo.isTool_InGameTimer(); }
inline bool gzInfo_isTool_InputViewer() { return g_gzInfo.isTool_InputViewer(); }
inline bool gzInfo_isTool_LoadTimer() { return g_gzInfo.isTool_LoadTimer(); }
inline bool gzInfo_isTool_StageInfo() { return g_gzInfo.isTool_StageInfo(); }
inline bool gzInfo_isTool_Timer() { return g_gzInfo.isTool_Timer(); }
inline bool gzInfo_isTool_Teleport() { return g_gzInfo.isTool_Teleport(); }
inline bool gzInfo_isTool_FreeCam() { return g_gzInfo.isTool_FreeCam(); }

inline void gzInfo_setTool_MoveLink(bool i_opt) { g_gzInfo.setTool_MoveLink(i_opt); }

inline void gzInfo_onTool_AbMashRate() { g_gzInfo.setTool_AbMashRate(true); }
inline void gzInfo_onTool_CoroTD() { g_gzInfo.setTool_CoroTD(true); }
inline void gzInfo_onTool_ElevatorEscape() { g_gzInfo.setTool_ElevatorEscape(true); }
inline void gzInfo_onTool_EndingBlowMoonBoots() { g_gzInfo.setTool_EndingBlowMoonBoots(true); }
inline void gzInfo_onTool_GorgeVoid() { g_gzInfo.setTool_GorgeVoid(true); }
inline void gzInfo_onTool_InGameTimer() { g_gzInfo.setTool_InGameTimer(true); }
inline void gzInfo_onTool_InputViewer() { g_gzInfo.setTool_InputViewer(true); }
inline void gzInfo_onTool_LadderFreezardCancel() { g_gzInfo.setTool_LadderFreezardCancel(true); }
inline void gzInfo_onTool_LinkDebugInfo() { g_gzInfo.setTool_LinkDebugInfo(true); }
inline void gzInfo_onTool_LoadTimer() { g_gzInfo.setTool_LoadTimer(true); }
inline void gzInfo_onTool_MoveLink() { g_gzInfo.setTool_MoveLink(true); }
inline void gzInfo_onTool_RollChecker() { g_gzInfo.setTool_RollChecker(true); }
inline void gzInfo_onTool_Teleport() { g_gzInfo.setTool_Teleport(true); }
inline void gzInfo_onTool_Timer() { g_gzInfo.setTool_Timer(true); }
inline void gzInfo_onTool_FreeCam() { g_gzInfo.setTool_FreeCam(true); }
inline void gzInfo_onTool_StageInfo() { g_gzInfo.setTool_StageInfo(true); }
inline void gzInfo_onTool_UniversalMapDelay() { g_gzInfo.setTool_UniversalMapDelay(true); }

inline void gzInfo_offTool_AbMashRate() { g_gzInfo.setTool_AbMashRate(false); }
inline void gzInfo_offTool_ElevatorEscape() { g_gzInfo.setTool_ElevatorEscape(false); }
inline void gzInfo_offTool_EndingBlowMoonBoots() { g_gzInfo.setTool_EndingBlowMoonBoots(false); }
inline void gzInfo_offTool_CoroTD() { g_gzInfo.setTool_CoroTD(false); }
inline void gzInfo_offTool_GorgeVoid() { g_gzInfo.setTool_GorgeVoid(false); }
inline void gzInfo_offTool_InGameTimer() { g_gzInfo.setTool_InGameTimer(false); }
inline void gzInfo_offTool_InputViewer() { g_gzInfo.setTool_InputViewer(false); }
inline void gzInfo_offTool_LadderFreezardCancel() { g_gzInfo.setTool_LadderFreezardCancel(false); }
inline void gzInfo_offTool_LinkDebugInfo() { g_gzInfo.setTool_LinkDebugInfo(false); }
inline void gzInfo_offTool_LoadTimer() { g_gzInfo.setTool_LoadTimer(false); }
inline void gzInfo_offTool_MoveLink() { g_gzInfo.setTool_MoveLink(false); }
inline void gzInfo_offTool_RollChecker() { g_gzInfo.setTool_RollChecker(false); }
inline void gzInfo_offTool_StageInfo() { g_gzInfo.setTool_StageInfo(false); }
inline void gzInfo_offTool_Teleport() { g_gzInfo.setTool_Teleport(false); }
inline void gzInfo_offTool_Timer() { g_gzInfo.setTool_Timer(false); }
inline void gzInfo_offTool_FreeCam() { g_gzInfo.setTool_FreeCam(false); }
inline void gzInfo_offTool_UniversalMapDelay() { g_gzInfo.setTool_UniversalMapDelay(false); }

// Scene
inline bool gzInfo_isScene_FreezeTime() { return g_gzInfo.isScene_FreezeTime(); }
inline void gzInfo_onScene_FreezeTime() { g_gzInfo.setScene_FreezeTime(true); }
inline void gzInfo_offScene_FreezeTime() { g_gzInfo.setScene_FreezeTime(false); }

inline bool gzInfo_isScene_FreezeActors() { return g_gzInfo.isScene_FreezeActors(); }
inline void gzInfo_onScene_FreezeActors() { g_gzInfo.setScene_FreezeActors(true); }
inline void gzInfo_offScene_FreezeActors() { g_gzInfo.setScene_FreezeActors(false); }

inline bool gzInfo_isScene_FreezeCamera() { return g_gzInfo.isScene_FreezeCamera(); }
inline void gzInfo_onScene_FreezeCamera() { g_gzInfo.setScene_FreezeCamera(true); }
inline void gzInfo_offScene_FreezeCamera() { g_gzInfo.setScene_FreezeCamera(false); }

inline bool gzInfo_isScene_MuteBGM() { return g_gzInfo.isScene_MuteBGM(); }
inline void gzInfo_onScene_MuteBGM() { g_gzInfo.setScene_MuteBGM(true); }
inline void gzInfo_offScene_MuteBGM() { g_gzInfo.setScene_MuteBGM(false); }

inline bool gzInfo_isScene_MuteSFX() { return g_gzInfo.isScene_MuteSFX(); }
inline void gzInfo_onScene_MuteSFX() { g_gzInfo.setScene_MuteSFX(true); }
inline void gzInfo_offScene_MuteSFX() { g_gzInfo.setScene_MuteSFX(false); }


// Online
inline bool gzInfo_isOnline_StateStreaming() { return g_gzInfo.isOnline_StateStreaming(); }
inline void gzInfo_onOnline_StateStreaming() {
    if (!umbraHasUmbraSupport()) {
        gzInfo_sendNotification("umbra support required");
        return;
    }
    g_gzInfo.setOnline_StateStreaming(true);
}
inline void gzInfo_offOnline_StateStreaming() { g_gzInfo.setOnline_StateStreaming(false); }

inline bool gzInfo_isMainMenuVisible() { return g_gzInfo.mCursor.x == 0;}
inline bool gzInfo_isMenuPausesGame() { return g_gzInfo.isMenuPausesGame(); }
inline bool gzInfo_isBootToMenu() { return g_gzInfo.isBootToMenu(); }
inline bool gzInfo_isMenuSfx() { return g_gzInfo.isMenuSfx(); }
inline bool gzInfo_isReloadArea() { return g_gzInfo.getReloadType() == true; }
inline bool gzInfo_isReloadFile() { return g_gzInfo.getReloadType() == false; }
inline bool gzInfo_isSubMenuVisible() { return g_gzInfo.mCursor.x > 0;}
inline bool gzInfo_isSwapEquips() { return g_gzInfo.isSwapEquips(); }

inline void gzInfo_setCursorType(u8 type) { g_gzInfo.setCursorType(type); }
inline void gzInfo_setDisplayMode(bool mode) { g_gzInfo.setDisplayMode(mode); }
inline void gzInfo_setDisplayModeInterlaced() { mDoMch_render_c::setInterlacedMode(); gzInfo_setDisplayMode(false); }
inline void gzInfo_setDisplayModeProgressive() { mDoMch_render_c::setProgressiveMode(); gzInfo_setDisplayMode(true); }
inline void gzInfo_setDropShadows(bool dropShadows) { g_gzInfo.setDropShadows(dropShadows); }
inline void gzInfo_setMenuPausesGame(bool opt) { g_gzInfo.setMenuPausesGame(opt); }
inline void gzInfo_setBootToMenu(bool opt) { g_gzInfo.setBootToMenu(opt); }
inline void gzInfo_setMenuSfx(bool sfx) { g_gzInfo.setMenuSfx(sfx); }
inline void gzInfo_setReloadType(bool i_type) { g_gzInfo.setReloadType(i_type); }
inline void gzInfo_setReloadArea() { gzInfo_setReloadType(true); }
inline void gzInfo_setReloadFile() { gzInfo_setReloadType(false); }
inline void gzInfo_setSwapEquips(bool swapEquips) { g_gzInfo.setSwapEquips(swapEquips); }
inline void gzInfo_setTextColor(u32 textColor) { g_gzInfo.setTextColor(textColor); }

inline void gzInfo_offBossDefeated(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offStageBossEnemy() : dComIfGs_offSaveStageBossEnemy(i_stageNo); 
}

inline void gzInfo_offMiniBossDefeated(int i_stageNo) {
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offStageMiddleBoss() : dComIfGs_offSaveStageMiddleBoss(i_stageNo);
}

inline void gzInfo_offDropShadows() { g_gzInfo.setDropShadows(false); }

inline void gzInfo_offDungeonBossKey(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offDungeonItemBossKey() : dComIfGs_offSaveDungeonItemBossKey(i_stageNo); 
}

inline void gzInfo_offDungeonCompass(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offDungeonItemCompass() : dComIfGs_offSaveDungeonItemCompass(i_stageNo); 
}

inline void gzInfo_offDungeonHeartContainer(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offStageLife() : dComIfGs_offSaveStageLife(i_stageNo); 
}

inline void gzInfo_offDungeonMap(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offDungeonItemMap() : dComIfGs_offSaveDungeonItemMap(i_stageNo); 
}

inline void gzInfo_offDungeonOoccoo(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_offDungeonItemWarp() : dComIfGs_offSaveDungeonItemWarp(i_stageNo);
}

inline void gzInfo_offMenuPausesGame() { g_gzInfo.setMenuPausesGame(false); }
inline void gzInfo_offBootToMenu() { g_gzInfo.setBootToMenu(false); }
inline void gzInfo_offMenuSfx() { g_gzInfo.setMenuSfx(false); }
inline void gzInfo_offSwapEquips() { g_gzInfo.setSwapEquips(false); }

inline void gzInfo_onBossDefeated(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_onStageBossEnemy() : dComIfGs_onSaveStageBossEnemy(i_stageNo);
}

inline void gzInfo_onMiniBossDefeated(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_onStageMiddleBoss() : dComIfGs_onSaveStageMiddleBoss(i_stageNo);
}

inline void gzInfo_onDropShadows() { g_gzInfo.setDropShadows(true); }

inline void gzInfo_onDungeonBossKey(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? execItemGet(dItemNo_BOSS_KEY_e) : dComIfGs_onSaveDungeonItemBossKey(i_stageNo); 
}

inline void gzInfo_onDungeonCompass(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? execItemGet(dItemNo_COMPUS_e) : dComIfGs_onSaveDungeonItemCompass(i_stageNo); 
}

inline void gzInfo_onDungeonHeartContainer(int i_stageNo) { 
    // Not using execItemGet func for this as it does more than we want in this context
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_onStageLife() : dComIfGs_onSaveStageLife(i_stageNo);
}

inline void gzInfo_onDungeonMap(int i_stageNo) { 
    gzInfo_isInDungeon(i_stageNo) ? execItemGet(dItemNo_MAP_e) : dComIfGs_onSaveDungeonItemMap(i_stageNo);
}

inline void gzInfo_onDungeonOoccoo(int i_stageNo) { 
    // NOTE(Pheenoh): This won't actually give you the ooccoo, just set the flag. 
    // Maybe we should call execItemGet(dItemNo_DUNGEON_EXIT_e) which will do both?
    // Or should we leave them separate and let the user set ooccoo in the inventory menu?
    gzInfo_isInDungeon(i_stageNo) ? dComIfGs_onDungeonItemWarp() : dComIfGs_onSaveDungeonItemWarp(i_stageNo);
}

inline void gzInfo_onMenuPausesGame() { g_gzInfo.setMenuPausesGame(true); }
inline void gzInfo_onBootToMenu() { g_gzInfo.setBootToMenu(true); }
inline void gzInfo_onMenuSfx() { g_gzInfo.setMenuSfx(true); }
inline void gzInfo_onSwapEquips() { g_gzInfo.setSwapEquips(true); }

namespace gzPad {
    inline u32 getTrig() { return mDoCPd_c::m_gzPadInfo.mPressedButtonFlags; }
    inline u32 getInputTrig() { return g_gzInfo.mStickTriggers; }  // Combined stick + d-pad with repeat
    inline u32 getTrigLockL() { return mDoCPd_c::m_gzPadInfo.mTrigLockL; }
    inline u32 getTrigLockR() { return mDoCPd_c::m_gzPadInfo.mTrigLockR; }
    inline u32 getTrigUp() { return getInputTrig() & PAD_BUTTON_UP; }
    inline u32 getTrigDown() { return getInputTrig() & PAD_BUTTON_DOWN; }
    inline u32 getTrigLeft() { return getInputTrig() & PAD_BUTTON_LEFT; }
    inline u32 getTrigRight() { return getInputTrig() & PAD_BUTTON_RIGHT; }
    inline u32 getTrigL() { return getTrig() & PAD_TRIGGER_L; }
    inline u32 getTrigR() { return getTrig() & PAD_TRIGGER_R; }
    inline u32 getTrigA() { return getTrig() & PAD_BUTTON_A; }
    inline u32 getTrigB() { return getTrig() & PAD_BUTTON_B; }
    inline u32 getTrigZ() { return getTrig() & PAD_TRIGGER_Z; }
    inline u32 getTrigY() { return getTrig() & PAD_BUTTON_Y; }
    inline u32 getTrigX() { return getTrig() & PAD_BUTTON_X; }
    inline u32 getRepeatX() { return g_gzInfo.mButtonRepeatTriggers & PAD_BUTTON_X; }
    inline u32 getRepeatY() { return g_gzInfo.mButtonRepeatTriggers & PAD_BUTTON_Y; }
    inline u32 getTrigStart() { return getTrig() & PAD_BUTTON_START; }
    inline u32 getHold() { return mDoCPd_c::m_gzPadInfo.mButtonFlags; }
    inline u32 getHoldLockL() { return mDoCPd_c::m_gzPadInfo.mHoldLockL; }
    inline u32 getHoldLockR() { return mDoCPd_c::m_gzPadInfo.mHoldLockR; }
    inline u32 getHoldUp() { return getHold() & PAD_BUTTON_UP; }
    inline u32 getHoldDown() { return getHold() & PAD_BUTTON_DOWN; }
    inline u32 getHoldLeft() { return getHold() & PAD_BUTTON_LEFT; }
    inline u32 getHoldRight() { return getHold() & PAD_BUTTON_RIGHT; }
    inline u32 getHoldL() { return getHold() & PAD_TRIGGER_L; }
    inline u32 getHoldR() { return getHold() & PAD_TRIGGER_R; }
    inline u32 getHoldA() { return getHold() & PAD_BUTTON_A; }
    inline u32 getHoldB() { return getHold() & PAD_BUTTON_B; }
    inline u32 getHoldZ() { return getHold() & PAD_TRIGGER_Z; }
    inline u32 getHoldY() { return getHold() & PAD_BUTTON_Y; }
    inline u32 getHoldX() { return getHold() & PAD_BUTTON_X; }
    inline f32 getStickX() { return mDoCPd_c::m_gzPadInfo.mMainStickPosX; }
    inline f32 getStickY() { return mDoCPd_c::m_gzPadInfo.mMainStickPosY; }
    inline f32 getStickX3D() { return mDoCPd_c::m_gzPadInfo.mMainStickPosX; }
    inline f32 getStickValue() { return mDoCPd_c::m_gzPadInfo.mMainStickValue; }
    inline s16 getStickAngle() { return mDoCPd_c::m_gzPadInfo.mMainStickAngle; }
    inline s16 getStickAngle3D() { return mDoCPd_c::m_gzPadInfo.mMainStickAngle; }
    inline f32 getSubStickX3D() { return mDoCPd_c::m_gzPadInfo.mCStickPosX; }
    inline f32 getSubStickX() { return mDoCPd_c::m_gzPadInfo.mCStickPosX; }
    inline f32 getSubStickY() { return mDoCPd_c::m_gzPadInfo.mCStickPosY; }
    inline f32 getSubStickValue() { return mDoCPd_c::m_gzPadInfo.mCStickValue; }
    inline s16 getSubStickAngle() { return mDoCPd_c::m_gzPadInfo.mCStickAngle; }
    inline f32 getAnalogR() { return mDoCPd_c::m_gzPadInfo.mTriggerRight; }
    inline f32 getAnalogL() { return mDoCPd_c::m_gzPadInfo.mTriggerLeft; }
};

inline bool gzCheckComboToggle(u32 combo, bool& wasHeld) {
    u32 rawHold = mDoCPd_c::getHold(0);
    bool comboHeld = combo && (rawHold & combo) == combo;
    bool shouldToggle = comboHeld && !wasHeld;
    wasHeld = comboHeld;
    return shouldToggle;
}

// Clears all controller input (buttons, sticks, triggers)
inline void gzClearControllerInput() {
    interface_of_controller_pad& cpad = mDoCPd_c::getCpadInfo(PAD_1);
    cpad.mPressedButtonFlags = 0;
    cpad.mButtonFlags = 0;
    cpad.mMainStickPosX = 0.0f;
    cpad.mMainStickPosY = 0.0f;
    cpad.mMainStickValue = 0.0f;
    cpad.mMainStickAngle = 0;
    cpad.mCStickPosX = 0.0f;
    cpad.mCStickPosY = 0.0f;
    cpad.mCStickValue = 0.0f;
    cpad.mCStickAngle = 0;
    cpad.mAnalogA = 0.0f;
    cpad.mAnalogB = 0.0f;
    cpad.mTriggerLeft = 0.0f;
    cpad.mTriggerRight = 0.0f;
}

// Clears just button input (pressed and held)
inline void gzClearButtonInput() {
    mDoCPd_c::getCpadInfo(PAD_1).mPressedButtonFlags = 0;
    mDoCPd_c::getCpadInfo(PAD_1).mButtonFlags = 0;
}

// Toggles menu option state and plays appropriate sound effect
inline void gzInfo_toggleMenuOption() {
    gzInfo_setMenuOption(!gzInfo_isMenuOption());
    gzInfo_seStart(gzInfo_isMenuOption() ? Z2SE_SY_TALK_CURSOR_OK : Z2SE_SY_CURSOR_CANCEL);
}

#endif // GZ_H
