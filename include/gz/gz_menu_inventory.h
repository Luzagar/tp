#ifndef GZ_MENU_INVENTORY_H
#define GZ_MENU_INVENTORY_H

#include "gz/gz_menu.h"
#include "JSystem/J2DGraph/J2DPicture.h"

class CPaneMgr;
class J2DScreen;

class gzInventoryMenu_c : public gzMenu_c {
public:
    enum gzInventoryMenu_Tabs_e {
        TAB_RING_MENU,
        TAB_PAUSE_MENU,

        TAB_MAX_e
    };

    static const int RING_MAX_SLOTS = 24;

    static const int PAUSE_MAX_ROWS = 5;
    static const int PAUSE_MAX_COLS = 4;

    static const int BUG_COUNT = 24;
    static const int BUG_GRID_COLS = 6;
    static const int BUG_GRID_ROWS = 4;

    static const int LETTER_COUNT = 16;
    static const int LETTER_GRID_COLS = 4;
    static const int LETTER_GRID_ROWS = 4;

    static const int FISH_COUNT = 6;
    static const int FISH_GRID_COLS = 2;
    static const int FISH_GRID_ROWS = 3;

    enum PauseSlotType_e {
        PAUSE_SLOT_SWORD_WOODEN,
        PAUSE_SLOT_SWORD_MASTER,
        PAUSE_SLOT_SHIELD_WOODEN,
        PAUSE_SLOT_SHIELD_HYLIAN,
        PAUSE_SLOT_TUNIC_HERO,
        PAUSE_SLOT_TUNIC_ZORA,
        PAUSE_SLOT_TUNIC_MAGIC,
        PAUSE_SLOT_WALLET,
        PAUSE_SLOT_QUIVER,
        PAUSE_SLOT_BUGS,
        PAUSE_SLOT_SKILLS,
        PAUSE_SLOT_SCENT,
        PAUSE_SLOT_POES,
        PAUSE_SLOT_FISH,
        PAUSE_SLOT_LETTERS,
    };

    gzInventoryMenu_c();
    ~gzInventoryMenu_c();

    virtual void _delete();
    virtual void execute();
    virtual void draw();
    virtual gzTabInfo_s getTabInfo();
    virtual gzButtonHints_s getButtonHints();
    virtual void onEnterMenu();
    virtual void onExitMenu();
    virtual void onHighlight();
    virtual void onUnhighlight();
    virtual void onAButtonSound() {}
    void reloadRingScreen();
    void freeRingScreen();

private:
    void initRingItems();
    void freeAllTextures();
    void loadItemTexture(int slotIdx, u8 slotNo);
    void loadPickerItemTexture(int pickerIdx, u8 itemId);
    int findItemInList(u8 item);
    void setSlotItem(int slotIdx, u8 newItem);
    void addSlot();
    void deleteSlot();
    void calcEllipsePlotAverage(int numItems, f32 centerX, f32 centerY);
    f32 calcEllipseFunction(f32 x, f32 radiusH, f32 radiusV);
    f32 calcDistance(f32 x1, f32 y1, f32 x2, f32 y2);
    void drawRingMenu();
    void drawPauseMenu();
    void drawItemOnRing(int slotIdx, f32 x, f32 y, f32 scale, bool selected);
    void drawItemPicker(f32 centerX, f32 centerY);
    const char* getItemName(u8 itemId);
    inline bool isPoeSlotSelected() { return (mPauseCursorRow == 4 && mPauseCursorCol == 1); }
    inline bool inPoeEditMode() { return isPoeSlotSelected() && gzInfo_isMenuOption(); }
    inline bool isHudHeartsSelected() { return mPauseCursorRow == -1; }
    inline bool inCurrentLifeEditMode() { return isHudHeartsSelected() && gzInfo_isMenuOption(); }
    inline bool isHeartPieceSlotSelected() { return (mPauseCursorCol == 2 && mPauseCursorRow >= 0 && mPauseCursorRow <= 1); }
    inline bool inHeartPieceEditMode() { return isHeartPieceSlotSelected() && gzInfo_isMenuOption(); }
    inline bool isWalletSlotSelected() { return (mPauseCursorRow == 3 && mPauseCursorCol == 0); }
    inline bool inRupeeEditMode() { return isWalletSlotSelected() && gzInfo_isMenuOption(); }
    inline bool isSkillSlotSelected() { return (mPauseCursorRow == 3 && mPauseCursorCol == 3); }
    inline bool inSkillSubMenu() { return mSkillSubMenuActive; }
    inline bool isBugSlotSelected() { return (mPauseCursorRow == 3 && mPauseCursorCol == 2); }
    inline bool inBugSubMenu() { return mBugSubMenuActive; }
    inline bool isLetterSlotSelected() { return (mPauseCursorRow == 4 && mPauseCursorCol == 3); }
    inline bool inLetterSubMenu() { return mLetterSubMenuActive; }
    inline bool isFishSlotSelected() { return (mPauseCursorRow == 4 && mPauseCursorCol == 2); }
    inline bool inFishSubMenu() { return mFishSubMenuActive; }
    inline bool inFishEditMode() { return mFishSubMenuActive && gzInfo_isMenuOption(); }
    inline bool inFishAdjusting();

private:
    void initPauseMenu();
    void executePauseMenu();
    void drawPauseMenuContent();
    void executeRingMenu();
    void executeSkillSubMenu();
    void executeBugSubMenu();
    void executeLetterSubMenu();
    void executeFishAdjusting();
    void executeFishEditMode();
    void executeFishSubMenu();
    void executePoeEditMode();
    void executeHeartPieceEditMode();
    void executeCurrentLifeEditMode();
    void executeRupeeEditMode();
    void drawSkillSubMenu();
    void drawBugSubMenu();
    void drawLetterSubMenu();
    void drawFishSubMenu();
    void loadBugIcons();
    void freeBugIcons();
    void freePauseTextures(bool freeArchiveCache = true);
    void freePauseItemTextures();
    void loadPauseItemTexture(int row, int col, u8 itemId);
    void cyclePauseSlot(int row, int col);
    void equipPauseSlot(int row, int col);
    u8 getItemForSlot(int row, int col);
    u8 getDisplayItemForSlot(int row, int col);
    int getMaxColsForRow(int row);
    void readPauseSlotStates();
    bool isSlotEquipped(int row, int col);

private:
    int mCurrentTab;
    int mCurrentSlot;
    int mItemsTotal;

    f32 mRingRadiusH;
    f32 mRingRadiusV;

    u8 mItemSlots[RING_MAX_SLOTS];
    f32 mItemSlotPosX[RING_MAX_SLOTS];
    f32 mItemSlotPosY[RING_MAX_SLOTS];
    f32 mItemSlotScale[RING_MAX_SLOTS];
    f32 mItemSlotParam1[RING_MAX_SLOTS];
    f32 mItemSlotParam2[RING_MAX_SLOTS];

    J2DPicture* mpItemTex[RING_MAX_SLOTS][3];
    ResTIMG* mpItemBuf[RING_MAX_SLOTS][3];

    J2DPicture* mpPickerTex[3][3];
    ResTIMG* mpPickerBuf[3][3];
    u8 mPickerItems[3];

    J2DScreen* mpRingScreen;
    CPaneMgr* mpCenterPaneMgr;
    CPaneMgr* mpCirclePaneMgr;
    CPaneMgr* mpLabelPaneMgr;
    void* mpRingResData;

    u8 mOriginalItem;

    int mPauseCursorRow;
    int mPauseCursorCol;
    J2DPicture* mpPauseItemTex[PAUSE_MAX_ROWS][PAUSE_MAX_COLS][3];
    ResTIMG* mpPauseItemBuf[PAUSE_MAX_ROWS][PAUSE_MAX_COLS][3];
    u8 mPauseSlotState[PAUSE_MAX_ROWS][PAUSE_MAX_COLS];
    bool mPauseMenuInitialized;

    J2DPicture* mpPauseFramePane;
    ResTIMG* mpPauseFrameBuf;

    J2DPicture* mpPoeIconPane;
    ResTIMG* mpPoeIconBuf;

    J2DPicture* mpBugsIconPane;
    ResTIMG* mpBugsIconBuf;
    J2DPicture* mpSkillsIconPane;
    ResTIMG* mpSkillsIconBuf;
    J2DPicture* mpFishIconPane;
    ResTIMG* mpFishIconBuf;
    J2DPicture* mpLettersIconPane;
    ResTIMG* mpLettersIconBuf;
    static const int HEART_TEX_COUNT = 5;
    J2DPicture* mpHeartPiecePanes[HEART_TEX_COUNT];
    ResTIMG* mpHeartPieceBufs[HEART_TEX_COUNT];

    static const int HUD_HEART_TEX_COUNT = 2;
    J2DPicture* mpHudHeartPanes[HUD_HEART_TEX_COUNT];
    ResTIMG* mpHudHeartBufs[HUD_HEART_TEX_COUNT];

    static const int QUARTER_HEART_COUNT = 3;
    J2DPicture* mpQuarterHeartPanes[QUARTER_HEART_COUNT];
    ResTIMG* mpQuarterHeartBufs[QUARTER_HEART_COUNT];

    bool mSkillSubMenuActive;
    int mSkillSubMenuIndex;

    bool mBugSubMenuActive;
    int mBugSubMenuRow;
    int mBugSubMenuCol;
    J2DPicture* mpBugIconPanes[BUG_COUNT];
    ResTIMG* mpBugIconBufs[BUG_COUNT];
    J2DPicture* mpButterflyIconPane;
    ResTIMG* mpButterflyIconBuf;

    bool mLetterSubMenuActive;
    int mLetterSubMenuRow;
    int mLetterSubMenuCol;
    J2DPicture* mpLetterIconPane;
    ResTIMG* mpLetterIconBuf;

    bool mFishSubMenuActive;
    int mFishSubMenuRow;
    int mFishSubMenuCol;
    int mFishEditField;
    bool mFishAdjusting;
    f32 mFishSizeTextW;
    f32 mFishCountTextW;

    static const int SKILL_ICON_BTI_SIZE = 544;
    J2DPicture* mpCheckIconPane;
    void* mpCheckIconBuf;
    J2DPicture* mpXMarkIconPane;
    void* mpXMarkIconBuf;
};

inline bool gzInventoryMenu_c::inFishAdjusting() { return inFishEditMode() && mFishAdjusting; }

#endif // GZ_MENU_INVENTORY_H
