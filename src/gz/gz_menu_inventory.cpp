#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_menu_inventory.h"
#include "gz/gz_menu_main.h"
#include "d/d_com_inf_game.h"
#include "d/d_pane_class.h"
#include "d/d_select_cursor.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRAramArchive.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/J2DGraph/J2DScreen.h"

static bool isAmmoItem(u8 item) {
    switch (item) {
    case fpcNm_ITEM_BOW:
    case fpcNm_ITEM_LIGHT_ARROW:
    case fpcNm_ITEM_BOMB_ARROW:
    case fpcNm_ITEM_HAWK_ARROW:
    case fpcNm_ITEM_NORMAL_BOMB:
    case fpcNm_ITEM_WATER_BOMB:
    case fpcNm_ITEM_POKE_BOMB:
        return true;
    default:
        return false;
    }
}

gzInventoryMenu_c::gzInventoryMenu_c() {
    mXPos = g_gzInfo.mBackgroundXPos + 170.0f;

    mCurrentTab = TAB_RING_MENU;
    mCurrentSlot = 0;
    mItemsTotal = 0;

    mRingRadiusH = 150.0f;
    mRingRadiusV = 140.0f;
    mOriginalItem = fpcNm_ITEM_NONE;

    for (int i = 0; i < gzInventoryMenu_c::RING_MAX_SLOTS; i++) {
        mItemSlots[i] = 0;
        mItemSlotPosX[i] = 0.0f;
        mItemSlotPosY[i] = 0.0f;
        mItemSlotScale[i] = 1.0f;
        mItemSlotParam1[i] = 1.0f;
        mItemSlotParam2[i] = 1.0f;
        for (int j = 0; j < 3; j++) {
            mpItemTex[i][j] = NULL;
            mpItemBuf[i][j] = NULL;
        }
    }

    for (int i = 0; i < 3; i++) {
        mPickerItems[i] = fpcNm_ITEM_NONE;
        for (int j = 0; j < 3; j++) {
            mpPickerTex[i][j] = NULL;
            mpPickerBuf[i][j] = NULL;
        }
    }

    mpRingScreen = NULL;
    mpRingResData = NULL;
    mpCenterPaneMgr = NULL;
    mpCirclePaneMgr = NULL;
    mpLabelPaneMgr = NULL;

    mPauseCursorRow = 0;
    mPauseCursorCol = 0;
    mPauseMenuInitialized = false;
    mpPauseFramePane = NULL;
    mpPauseFrameBuf = NULL;
    mpPoeIconPane = NULL;
    mpPoeIconBuf = NULL;
    mpBugsIconPane = NULL;
    mpBugsIconBuf = NULL;
    mpSkillsIconPane = NULL;
    mpSkillsIconBuf = NULL;
    mpFishIconPane = NULL;
    mpFishIconBuf = NULL;
    mpLettersIconPane = NULL;
    mpLettersIconBuf = NULL;
    for (int i = 0; i < HEART_TEX_COUNT; i++) {
        mpHeartPiecePanes[i] = NULL;
        mpHeartPieceBufs[i] = NULL;
    }
    for (int i = 0; i < HUD_HEART_TEX_COUNT; i++) {
        mpHudHeartPanes[i] = NULL;
        mpHudHeartBufs[i] = NULL;
    }
    for (int i = 0; i < QUARTER_HEART_COUNT; i++) {
        mpQuarterHeartPanes[i] = NULL;
        mpQuarterHeartBufs[i] = NULL;
    }
    mSkillSubMenuActive = false;
    mSkillSubMenuIndex = 0;
    mBugSubMenuActive = false;
    mBugSubMenuRow = 0;
    mBugSubMenuCol = 0;
    mLetterSubMenuActive = false;
    mLetterSubMenuRow = 0;
    mLetterSubMenuCol = 0;
    mpLetterIconPane = NULL;
    mpLetterIconBuf = NULL;
    mFishSubMenuActive = false;
    mFishSubMenuRow = 0;
    mFishSubMenuCol = 0;
    mFishEditField = 0;
    mFishAdjusting = false;
    mFishSizeTextW = 0.0f;
    mFishCountTextW = 0.0f;
    for (int i = 0; i < BUG_COUNT; i++) {
        mpBugIconPanes[i] = NULL;
        mpBugIconBufs[i] = NULL;
    }
    mpButterflyIconPane = NULL;
    mpButterflyIconBuf = NULL;
    {
        JKRHeap* heap = gzHeap(GZ_GROUP_MENU);
        JKRArchive* insectArc = JKRArchive::mount(
            "/res/Layout/insectRes.arc", JKRArchive::MOUNT_ARAM, heap,
            JKRArchive::MOUNT_DIRECTION_HEAD);
        if (insectArc != NULL) {
            ResTIMG* tex;
            {
                JKRHeapOverrideScope scope(heap);
                tex = (ResTIMG*)insectArc->getResource('TIMG', "ageha_01.bti");
            }
            if (tex != NULL) {
                JKRHeap* oldHeap = heap->becomeCurrentHeap();
                u32 imgSize = GXGetTexBufferSize(tex->width, tex->height, tex->format,
                                                  tex->mipmapEnabled, tex->mipmapCount);
                u32 totalSize = tex->imageOffset + imgSize;
                if (tex->indexTexture && tex->numColors > 0) {
                    u32 palEnd = tex->paletteOffset + tex->numColors * 2;
                    if (palEnd > totalSize) {
                        totalSize = palEnd;
                    }
                }
                mpButterflyIconBuf = (ResTIMG*)heap->alloc(totalSize, 32);
                if (mpButterflyIconBuf != NULL) {
                    memcpy(mpButterflyIconBuf, tex, totalSize);
                    DCStoreRangeNoSync(mpButterflyIconBuf, totalSize);
                    mpButterflyIconPane = new (heap, 4) J2DPicture(mpButterflyIconBuf);
                }
                oldHeap->becomeCurrentHeap();
            }
            insectArc->unmount();
        }
    }
    mpCheckIconPane = NULL;
    mpCheckIconBuf = NULL;
    mpXMarkIconPane = NULL;
    mpXMarkIconBuf = NULL;
    for (int row = 0; row < PAUSE_MAX_ROWS; row++) {
        for (int col = 0; col < PAUSE_MAX_COLS; col++) {
            mPauseSlotState[row][col] = 0;
            for (int k = 0; k < 3; k++) {
                mpPauseItemTex[row][col][k] = NULL;
                mpPauseItemBuf[row][col][k] = NULL;
            }
        }
    }
}

gzInventoryMenu_c::~gzInventoryMenu_c() {
    _delete();
}

void gzInventoryMenu_c::_delete() {
    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);

    for (int i = 0; i < gzInventoryMenu_c::RING_MAX_SLOTS; i++) {
        for (int j = 0; j < 3; j++) {
            delete mpItemTex[i][j];
            mpItemTex[i][j] = NULL;
            if (mpItemBuf[i][j] != NULL) {
                heap->free(mpItemBuf[i][j]);
                mpItemBuf[i][j] = NULL;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete mpPickerTex[i][j];
            mpPickerTex[i][j] = NULL;
            if (mpPickerBuf[i][j] != NULL) {
                heap->free(mpPickerBuf[i][j]);
                mpPickerBuf[i][j] = NULL;
            }
        }
    }

    freePauseTextures();

    delete mpButterflyIconPane;
    mpButterflyIconPane = NULL;
    if (mpButterflyIconBuf != NULL) {
        heap->free(mpButterflyIconBuf);
        mpButterflyIconBuf = NULL;
    }

    delete mpLabelPaneMgr;
    mpLabelPaneMgr = NULL;
    delete mpCirclePaneMgr;
    mpCirclePaneMgr = NULL;
    delete mpCenterPaneMgr;
    mpCenterPaneMgr = NULL;
    delete mpRingScreen;
    mpRingScreen = NULL;
    if (mpRingResData != NULL) {
        gzHeap(GZ_GROUP_MENU)->free(mpRingResData);
        mpRingResData = NULL;
    }
}

void gzInventoryMenu_c::onEnterMenu() {
    gzMenu_c::onEnterMenu();
    mCurrentSlot = 0;
}

void gzInventoryMenu_c::onExitMenu() {
    gzMenu_c::onExitMenu();
    if (gzInfo_getTPCursor() != NULL) {
        gzInfo_getTPCursor()->setParam(0.96f, 0.84f, 0.03f, 0.5f, 0.5f);
    }
}

void gzInventoryMenu_c::onHighlight() {
    if (mCurrentTab == TAB_RING_MENU) {
        reloadRingScreen();
        initRingItems();
    } else if (mCurrentTab == TAB_PAUSE_MENU) {
        initPauseMenu();
    }
}

void gzInventoryMenu_c::onUnhighlight() {
    freeAllTextures();
    freePauseTextures();
    freeRingScreen();
}

void gzInventoryMenu_c::reloadRingScreen() {
    freeRingScreen();

    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);
    JKRHeap* oldHeap = heap->becomeCurrentHeap();

    mpRingScreen = new (heap, 4) J2DScreen();
    JKRHeapOverrideScope heapScope(heap);
    dPaneClass_setPriority(&mpRingResData, heap, mpRingScreen,
                            "SCRN/zelda_item_select_icon3_center_parts.blo", 0x20000,
                            dComIfGp_getRingResArchive());
    dPaneClass_showNullPane(mpRingScreen);

    mpCenterPaneMgr = new (heap, 4) CPaneMgr(mpRingScreen, 'center_n', 2, (JKRExpHeap*)heap);
    mpCirclePaneMgr = new (heap, 4) CPaneMgr(mpRingScreen, 'circle_n', 2, (JKRExpHeap*)heap);
    mpLabelPaneMgr = new (heap, 4) CPaneMgr(mpRingScreen, 'label_n', 1, (JKRExpHeap*)heap);

    oldHeap->becomeCurrentHeap();
}

void gzInventoryMenu_c::freeRingScreen() {
    delete mpLabelPaneMgr;
    mpLabelPaneMgr = NULL;

    delete mpCirclePaneMgr;
    mpCirclePaneMgr = NULL;

    delete mpCenterPaneMgr;
    mpCenterPaneMgr = NULL;

    delete mpRingScreen;
    mpRingScreen = NULL;

    if (mpRingResData != NULL) {
        gzHeap(GZ_GROUP_MENU)->free(mpRingResData);
        mpRingResData = NULL;
    }

    JKRArchive* ringArc = dComIfGp_getRingResArchive();
    if (ringArc != NULL) {
        JKRHeap* heap = gzHeap(GZ_GROUP_MENU);
        u8* heapStart = (u8*)heap->getStartAddr();
        u8* heapEnd = (u8*)heap->getEndAddr();
        u32 numFiles = ringArc->countFile();
        JKRArchive::SDIFileEntry* files = ringArc->mFiles;
        for (u32 i = 0; i < numFiles; i++) {
            u8* data = (u8*)files[i].data;
            if (data != NULL && data >= heapStart && data < heapEnd) {
                heap->free(data);
                files[i].data = NULL;
            }
        }
    }
}

void gzInventoryMenu_c::execute() {
    if (checkInputWait()) return;

    if (gzInfo_isMenuOption() && gzPad::getTrigB() && !inFishEditMode()) {
        setSlotItem(mCurrentSlot, mOriginalItem);
        gzInfo_offMenuOption();
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }

    if (!inSkillSubMenu() && !inBugSubMenu() && !inLetterSubMenu() && !inFishSubMenu() && handleBackButton(gzMainMenu_c::MENU_INVENTORY)) return;

    gzCursor* l_cursor = gzInfo_getCursor();

    u32 lrTrig = gzPad::getTrig() & (PAD_TRIGGER_L | PAD_TRIGGER_R);
    if ((lrTrig & PAD_TRIGGER_R) && mCurrentTab == TAB_RING_MENU && !inPoeEditMode()) {
        mCurrentTab = TAB_PAUSE_MENU;
        l_cursor->y = 0;
        mCurrentSlot = 0;
        gzInfo_resetTopLine();
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        freeAllTextures();
        freeRingScreen();
        mPauseMenuInitialized = false;
    }

    if ((lrTrig & PAD_TRIGGER_L) && mCurrentTab == TAB_PAUSE_MENU && !inPoeEditMode() && !inHeartPieceEditMode() && !inCurrentLifeEditMode() && !inRupeeEditMode() && !inSkillSubMenu() && !inBugSubMenu() && !inLetterSubMenu() && !inFishSubMenu()) {
        mCurrentTab = TAB_RING_MENU;
        l_cursor->y = 0;
        mCurrentSlot = 0;
        gzInfo_resetTopLine();
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        freePauseTextures(false);
        reloadRingScreen();
        initRingItems();
    }

    if (mCurrentTab == TAB_PAUSE_MENU) {
        executePauseMenu();
        return;
    }

    if (mCurrentTab == TAB_RING_MENU) {
        executeRingMenu();
    }
}

void gzInventoryMenu_c::draw() {
    switch (mCurrentTab) {
    case TAB_RING_MENU:
        drawRingMenu();
        break;
    case TAB_PAUSE_MENU:
        drawPauseMenu();
        break;
    }
}

gzTabInfo_s gzInventoryMenu_c::getTabInfo() {
    gzTabInfo_s info;
    info.hasTabs = false;
    info.currentTab = mCurrentTab;
    info.numTabs = TAB_MAX_e;
    return info;
}

gzButtonHints_s gzInventoryMenu_c::getButtonHints() {
    gzButtonHints_s hints;
    hints.count = 0;

    if (mCurrentTab == TAB_PAUSE_MENU) {
        bool isHudHearts = isHudHeartsSelected();
        bool isPoeSlot = isPoeSlotSelected();
        bool isHeartSlot = isHeartPieceSlotSelected();
        bool isWallet = isWalletSlotSelected();
        bool hasItem = mPauseCursorRow >= 0 &&
                       mPauseSlotState[mPauseCursorRow][mPauseCursorCol] > 0;
        bool alreadyEquipped = mPauseCursorRow >= 0 &&
                               isSlotEquipped(mPauseCursorRow, mPauseCursorCol);

        if (isHudHearts || isPoeSlot || isHeartSlot || isWallet) {
            hints.hints[hints.count].button = GZ_BTN_A;
            hints.hints[hints.count].text = gzInfo_isMenuOption() ? "Done" : "Edit";
            hints.count++;
        } else {
            if (mPauseCursorRow <= 2 && hasItem && !alreadyEquipped) {
                hints.hints[hints.count].button = GZ_BTN_A;
                hints.hints[hints.count].text = "Equip";
                hints.count++;
            }
        }

        if (!isHudHearts && !isPoeSlot && !isHeartSlot) {
            hints.hints[hints.count].button = GZ_BTN_Z;
            hints.hints[hints.count].text = "Cycle";
            hints.count++;
        }

        if (inPoeEditMode() || inRupeeEditMode()) {
            hints.hints[hints.count].button = GZ_BTN_X;
            hints.hints[hints.count].text = "+10";
            hints.count++;
            hints.hints[hints.count].button = GZ_BTN_Y;
            hints.hints[hints.count].text = "-10";
            hints.count++;
        }

        hints.hints[hints.count].button = GZ_BTN_B;
        hints.hints[hints.count].text = "Back";
        hints.count++;

        if (!inPoeEditMode() && !inHeartPieceEditMode() && !inCurrentLifeEditMode() && !inRupeeEditMode()) {
            hints.hints[hints.count].button = GZ_BTN_L;
            hints.hints[hints.count].text = "Ring";
            hints.count++;
        }

        return hints;
    }

    if (mItemsTotal > 0) {
        hints.hints[hints.count].button = GZ_BTN_A;
        hints.hints[hints.count].text = gzInfo_isMenuOption() ? "Select" : "Edit";
        hints.count++;
    }

    hints.hints[hints.count].button = GZ_BTN_B;
    hints.hints[hints.count].text = "Back";
    hints.count++;

    if (gzInfo_isMenuOption() && mItemsTotal > 0) {
        u8 slotNo = mItemSlots[mCurrentSlot];
        u8 curItem = dComIfGs_getItem(slotNo, false);
        if (isAmmoItem(curItem)) {
            hints.hints[hints.count].button = GZ_BTN_X;
            hints.hints[hints.count].text = "Ammo +";
            hints.count++;
            hints.hints[hints.count].button = GZ_BTN_Y;
            hints.hints[hints.count].text = "Ammo -";
            hints.count++;
        }
    } else {
        if (mItemsTotal < MAX_ITEM_SLOTS) {
            hints.hints[hints.count].button = GZ_BTN_Y;
            hints.hints[hints.count].text = "Add";
            hints.count++;
        }

        if (mItemsTotal > 0) {
            hints.hints[hints.count].button = GZ_BTN_X;
            hints.hints[hints.count].text = "Delete";
            hints.count++;
        }

        hints.hints[hints.count].button = GZ_BTN_R;
        hints.hints[hints.count].text = "Pause";
        hints.count++;
    }

    return hints;
}

const char* gzInventoryMenu_c::getItemName(u8 itemId) {
    switch (itemId) {
    case fpcNm_ITEM_NOENTRY_19: return "Black Rupee";
    case fpcNm_ITEM_BOOMERANG: return "Gale Boomerang";
    case fpcNm_ITEM_KANTERA: return "Lantern";
    case fpcNm_ITEM_PACHINKO: return "Slingshot";
    case fpcNm_ITEM_FISHING_ROD_1: return "Fishing Rod";
    case fpcNm_ITEM_LURE_ROD: return "Fishing Rod (Lure)";
    case fpcNm_ITEM_BEE_ROD: return "Fishing Rod (Bee)";
    case fpcNm_ITEM_WORM_ROD: return "Fishing Rod (Worm)";
    case fpcNm_ITEM_JEWEL_ROD: return "Fishing Rod (Coral)";
    case fpcNm_ITEM_JEWEL_BEE_ROD: return "Fishing Rod (Coral+Bee)";
    case fpcNm_ITEM_JEWEL_WORM_ROD: return "Fishing Rod (Coral+Worm)";
    case fpcNm_ITEM_HVY_BOOTS: return "Iron Boots";
    case fpcNm_ITEM_HOOKSHOT: return "Clawshot";
    case fpcNm_ITEM_W_HOOKSHOT: return "Double Clawshots";
    case fpcNm_ITEM_BOW: return "Hero's Bow";
    case fpcNm_ITEM_LIGHT_ARROW: return "Bow (Light Arrows)";
    case fpcNm_ITEM_BOMB_ARROW: return "Bow (Bomb Arrows)";
    case fpcNm_ITEM_HAWK_ARROW: return "Bow (Hawkeye)";
    case fpcNm_ITEM_HAWK_EYE: return "Hawkeye";
    case fpcNm_ITEM_NORMAL_BOMB: return "Bomb";
    case fpcNm_ITEM_WATER_BOMB: return "Water Bomb";
    case fpcNm_ITEM_POKE_BOMB: return "Bomblings";
    case fpcNm_ITEM_SPINNER: return "Spinner";
    case fpcNm_ITEM_IRONBALL: return "Ball and Chain";
    case fpcNm_ITEM_COPY_ROD: return "Dominion Rod";
    case fpcNm_ITEM_COPY_ROD_2: return "Dominion Rod (Powered)";
    case fpcNm_ITEM_HORSE_FLUTE: return "Horse Call";
    case fpcNm_ITEM_WOOD_STICK: return "Wooden Sword";
    case fpcNm_ITEM_EMPTY_BOTTLE: return "Empty Bottle";
    case fpcNm_ITEM_RED_BOTTLE: return "Red Potion";
    case fpcNm_ITEM_GREEN_BOTTLE: return "Green Potion";
    case fpcNm_ITEM_BLUE_BOTTLE: return "Blue Potion";
    case fpcNm_ITEM_MILK_BOTTLE: return "Milk";
    case fpcNm_ITEM_HALF_MILK_BOTTLE: return "Half Milk";
    case fpcNm_ITEM_WATER_BOTTLE: return "Water";
    case fpcNm_ITEM_HOT_SPRING: return "Hot Spring Water";
    case fpcNm_ITEM_OIL_BOTTLE: return "Lantern Oil";
    case fpcNm_ITEM_UGLY_SOUP: return "Nasty Soup";
    case fpcNm_ITEM_LV1_SOUP: return "Simple Soup";
    case fpcNm_ITEM_LV2_SOUP: return "Good Soup";
    case fpcNm_ITEM_LV3_SOUP: return "Superb Soup";
    case fpcNm_ITEM_CHUCHU_RARE: return "Rare Chu Jelly";
    case fpcNm_ITEM_CHUCHU_RED: return "Red Chu Jelly";
    case fpcNm_ITEM_CHUCHU_BLUE: return "Blue Chu Jelly";
    case fpcNm_ITEM_CHUCHU_GREEN: return "Green Chu Jelly";
    case fpcNm_ITEM_CHUCHU_YELLOW: return "Yellow Chu Jelly";
    case fpcNm_ITEM_CHUCHU_PURPLE: return "Purple Chu Jelly";
    case fpcNm_ITEM_BEE_CHILD: return "Bee Larva";
    case fpcNm_ITEM_FAIRY: return "Fairy";
    case fpcNm_ITEM_FAIRY_DROP: return "Fairy's Tears";
    case fpcNm_ITEM_WORM: return "Worm";
    case fpcNm_ITEM_ZORAS_JEWEL: return "Reekfish Scent";
    case fpcNm_ITEM_LETTER: return "Letter";
    case fpcNm_ITEM_BILL: return "Invoice";
    case fpcNm_ITEM_SWORD: return "Ordon Sword";
    case fpcNm_ITEM_MASTER_SWORD: return "Master Sword";
    case fpcNm_ITEM_LIGHT_SWORD: return "Master Sword (Light)";
    case fpcNm_ITEM_WOOD_SHIELD: return "Ordon Shield";
    case fpcNm_ITEM_SHIELD: return "Wooden Shield";
    case fpcNm_ITEM_HYLIA_SHIELD: return "Hylian Shield";
    case fpcNm_ITEM_WEAR_KOKIRI: return "Hero's Clothes";
    case fpcNm_ITEM_WEAR_ZORA: return "Zora Armor";
    case fpcNm_ITEM_ARMOR: return "Magic Armor";
    case fpcNm_ITEM_WALLET_LV1: return "Wallet (300)";
    case fpcNm_ITEM_WALLET_LV2: return "Wallet (600)";
    case fpcNm_ITEM_WALLET_LV3: return "Wallet (1000)";
    case fpcNm_ITEM_ARROW_LV1: return "Quiver (30)";
    case fpcNm_ITEM_ARROW_LV2: return "Quiver (60)";
    case fpcNm_ITEM_ARROW_LV3: return "Quiver (100)";
    case fpcNm_ITEM_SMELL_CHILDREN: return "Youth's Scent";
    case fpcNm_ITEM_SMELL_YELIA_POUCH: return "Scent of Ilia";
    case fpcNm_ITEM_SMELL_FISH: return "Reekfish Scent";
    case fpcNm_ITEM_SMELL_MEDICINE: return "Medicine Scent";
    case fpcNm_ITEM_SMELL_POH: return "Poe Scent";
    case fpcNm_ITEM_NONE: return "";
    default: return "Unknown";
    }
}
