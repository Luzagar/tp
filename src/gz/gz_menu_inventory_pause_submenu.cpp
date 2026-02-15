#include "d/dolzel.h"  // IWYU pragma: keep

#include "gz/gz_menu_inventory.h"
#include "gz/gz_utility_draw.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter2_info.h"
#include "d/d_save.h"
#include "d/d_select_cursor.h"
#include <cstdio>

static const u8 sBugItemIds[gzInventoryMenu_c::BUG_COUNT] = {
    fpcNm_ITEM_M_ANT, fpcNm_ITEM_F_ANT, fpcNm_ITEM_M_MAYFLY, fpcNm_ITEM_F_MAYFLY,
    fpcNm_ITEM_M_BEETLE, fpcNm_ITEM_F_BEETLE, fpcNm_ITEM_M_MANTIS, fpcNm_ITEM_F_MANTIS,
    fpcNm_ITEM_M_STAG_BEETLE, fpcNm_ITEM_F_STAG_BEETLE, fpcNm_ITEM_M_DANGOMUSHI,
    fpcNm_ITEM_F_DANGOMUSHI, fpcNm_ITEM_M_BUTTERFLY, fpcNm_ITEM_F_BUTTERFLY,
    fpcNm_ITEM_M_LADYBUG, fpcNm_ITEM_F_LADYBUG, fpcNm_ITEM_M_SNAIL, fpcNm_ITEM_F_SNAIL,
    fpcNm_ITEM_M_NANAFUSHI, fpcNm_ITEM_F_NANAFUSHI, fpcNm_ITEM_M_GRASSHOPPER,
    fpcNm_ITEM_F_GRASSHOPPER, fpcNm_ITEM_M_DRAGONFLY, fpcNm_ITEM_F_DRAGONFLY,
};

static const u16 sSkillFlags[] = {
    dSv_event_flag_c::F_0339, dSv_event_flag_c::F_0338,
    dSv_event_flag_c::F_0340, dSv_event_flag_c::F_0341,
    dSv_event_flag_c::F_0342, dSv_event_flag_c::F_0343,
    dSv_event_flag_c::F_0344,
};

static const char* sSkillNames[] = {
    "Ending Blow", "Shield Attack", "Back Slice", "Helm Splitter",
    "Mortal Draw", "Jump Strike", "Great Spin",
};

static const char* sSkillNumbers[] = {
    "Skill One", "Skill Two", "Skill Three", "Skill Four",
    "Skill Five", "Skill Six", "Skill Seven",
};

static const u16 sBugTurnInFlags[gzInventoryMenu_c::BUG_COUNT] = {
    dSv_event_flag_c::F_0421, dSv_event_flag_c::F_0422,
    dSv_event_flag_c::F_0423, dSv_event_flag_c::F_0424,
    dSv_event_flag_c::F_0401, dSv_event_flag_c::F_0402,
    dSv_event_flag_c::F_0413, dSv_event_flag_c::F_0414,
    dSv_event_flag_c::F_0405, dSv_event_flag_c::F_0406,
    dSv_event_flag_c::F_0411, dSv_event_flag_c::F_0412,
    dSv_event_flag_c::F_0403, dSv_event_flag_c::F_0404,
    dSv_event_flag_c::F_0415, dSv_event_flag_c::F_0416,
    dSv_event_flag_c::F_0417, dSv_event_flag_c::F_0418,
    dSv_event_flag_c::F_0409, dSv_event_flag_c::F_0410,
    dSv_event_flag_c::F_0407, dSv_event_flag_c::F_0408,
    dSv_event_flag_c::F_0419, dSv_event_flag_c::F_0420,
};

static const char* sBugNames[] = {
    "Male Ant", "Female Ant", "Male Dayfly", "Female Dayfly",
    "Male Beetle", "Female Beetle", "Male Mantis", "Female Mantis",
    "Male Stag Beetle", "Female Stag Beetle", "Male Pill Bug", "Female Pill Bug",
    "Male Butterfly", "Female Butterfly", "Male Ladybug", "Female Ladybug",
    "Male Snail", "Female Snail", "Male Phasmid", "Female Phasmid",
    "Male Grasshopper", "Female Grasshopper", "Male Dragonfly", "Female Dragonfly",
};

static const char* sBugSpeciesNames[] = {
    "Ant", "Dayfly", "Beetle", "Mantis", "Stag Beetle", "Pill Bug",
    "Butterfly", "Ladybug", "Snail", "Phasmid", "Grasshopper", "Dragonfly",
};

static const char* sFishNames[] = {
    "Ordon Catfish", "Greengill", "Reekfish",
    "Hyrule Bass", "Hylian Pike", "Hylian Loach",
};

static const u8 sFishGridIdx[gzInventoryMenu_c::FISH_COUNT] = { 3, 5, 4, 0, 2, 1 };

static const char* sLetterSendersLong[] = {
    "Renado", "Ooccoo 1", "Ooccoo 2", "The Postman",
    "Kakariko Goods", "Barnes 1", "Barnes 2", "Barnes Bombs",
    "Malo Mart", "Telma", "Purlo", "From Jr.",
    "Princess Agitha", "Lanayru Tourism", "Shad", "Yeta",
};

static const char* sLetterSendersShort[] = {
    "Renado", "Ooccoo 1", "Ooccoo 2", "Postman",
    "Kakariko", "Barnes 1", "Barnes 2", "Barnes B.",
    "Malo Mart", "Telma", "Purlo", "From Jr.",
    "Agitha", "Lanayru", "Shad", "Yeta",
};

void gzInventoryMenu_c::executeSkillSubMenu() {
    if (gzPad::getTrigDown()) {
        mSkillSubMenuIndex = (mSkillSubMenuIndex + 1) % 7;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigUp()) {
        mSkillSubMenuIndex = (mSkillSubMenuIndex - 1 + 7) % 7;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigA()) {
        u16 flag = sSkillFlags[mSkillSubMenuIndex];
        if (dComIfGs_isEventBit(flag)) {
            dComIfGs_offEventBit(flag);
        } else {
            dComIfGs_onEventBit(flag);
        }
        bool hasSkill = false;
        for (int i = 0; i < 7; i++) {
            if (dComIfGs_isEventBit(sSkillFlags[i])) {
                hasSkill = true;
                break;
            }
        }
        mPauseSlotState[3][3] = hasSkill ? 1 : 0;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }
    if (gzPad::getTrigB()) {
        mSkillSubMenuActive = false;
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString(sSkillNames[mSkillSubMenuIndex]);
}

void gzInventoryMenu_c::executeBugSubMenu() {
    if (gzPad::getTrigDown()) {
        mBugSubMenuRow = (mBugSubMenuRow + 1) % BUG_GRID_ROWS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigUp()) {
        mBugSubMenuRow = (mBugSubMenuRow - 1 + BUG_GRID_ROWS) % BUG_GRID_ROWS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigRight()) {
        mBugSubMenuCol = (mBugSubMenuCol + 1) % BUG_GRID_COLS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigLeft()) {
        mBugSubMenuCol = (mBugSubMenuCol - 1 + BUG_GRID_COLS) % BUG_GRID_COLS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    int idx = mBugSubMenuRow * BUG_GRID_COLS + mBugSubMenuCol;
    if (gzPad::getTrigA()) {
        u8 itemId = sBugItemIds[idx];
        if (dComIfGs_isItemFirstBit(itemId)) {
            dComIfGs_offItemFirstBit(itemId);
        } else {
            dComIfGs_onItemFirstBit(itemId);
        }
        bool hasBug = false;
        for (int i = 0; i < BUG_COUNT; i++) {
            if (dComIfGs_isItemFirstBit(sBugItemIds[i])) {
                hasBug = true;
                break;
            }
        }
        mPauseSlotState[3][2] = hasBug ? 1 : 0;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }
    if (gzPad::getTrigZ()) {
        u16 flag = sBugTurnInFlags[idx];
        if (dComIfGs_isEventBit(flag)) {
            dComIfGs_offEventBit(flag);
        } else {
            dComIfGs_onEventBit(flag);
        }
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }
    if (gzPad::getTrigB()) {
        mBugSubMenuActive = false;
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString(sBugNames[idx]);
}

void gzInventoryMenu_c::executeLetterSubMenu() {
    if (gzPad::getTrigDown()) {
        mLetterSubMenuRow = (mLetterSubMenuRow + 1) % LETTER_GRID_ROWS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigUp()) {
        mLetterSubMenuRow = (mLetterSubMenuRow - 1 + LETTER_GRID_ROWS) % LETTER_GRID_ROWS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigRight()) {
        mLetterSubMenuCol = (mLetterSubMenuCol + 1) % LETTER_GRID_COLS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigLeft()) {
        mLetterSubMenuCol = (mLetterSubMenuCol - 1 + LETTER_GRID_COLS) % LETTER_GRID_COLS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigA()) {
        int idx = mLetterSubMenuRow * LETTER_GRID_COLS + mLetterSubMenuCol;
        if (dComIfGs_isLetterGetFlag(idx)) {
            dComIfGs_offLetterGetFlag(idx);
            for (int j = 0; j < 64; j++) {
                if (dComIfGs_getGetNumber(j) == idx + 1) {
                    for (int k = j; k < 63; k++) {
                        dComIfGs_setGetNumber(k, dComIfGs_getGetNumber(k + 1));
                    }
                    dComIfGs_setGetNumber(63, 0);
                    break;
                }
            }
        } else {
            dComIfGs_onLetterGetFlag(idx);
            u8 letterNum = dMeter2Info_getRecieveLetterNum() - 1;
            dComIfGs_setGetNumber(letterNum, idx + 1);
        }
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }
    if (gzPad::getTrigB()) {
        mLetterSubMenuActive = false;
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString(
        sLetterSendersLong[mLetterSubMenuRow * LETTER_GRID_COLS + mLetterSubMenuCol]);
}

void gzInventoryMenu_c::executeFishAdjusting() {
    int gridIdx = mFishSubMenuRow * FISH_GRID_COLS + mFishSubMenuCol;
    u8 fishIdx = sFishGridIdx[gridIdx];

    if (mFishEditField == 0) {
        u16 count = dComIfGs_getFishNum(fishIdx);
        if (gzPad::getTrigRight()) {
            dComIfGs_setFishNum(fishIdx, count >= 999 ? 0 : count + 1);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
        if (gzPad::getTrigLeft()) {
            dComIfGs_setFishNum(fishIdx, count == 0 ? 999 : count - 1);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    } else {
        u8 size = dComIfGs_getFishSize(fishIdx);
        if (gzPad::getTrigRight()) {
            dComIfGs_setFishSize(fishIdx, size >= 255 ? 0 : size + 1);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
        if (gzPad::getTrigLeft()) {
            dComIfGs_setFishSize(fishIdx, size == 0 ? 255 : size - 1);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    }

    mpHaihai->_execute(0);

    if (gzPad::getTrigA() || gzPad::getTrigB()) {
        mFishAdjusting = false;
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString(sFishNames[gridIdx]);
}

void gzInventoryMenu_c::executeFishEditMode() {
    if (gzPad::getTrigUp() || gzPad::getTrigDown()) {
        mFishEditField ^= 1;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }

    if (gzPad::getTrigA()) {
        mFishAdjusting = true;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
    }

    if (gzPad::getTrigB()) {
        gzInfo_offMenuOption();
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    int idx = mFishSubMenuRow * FISH_GRID_COLS + mFishSubMenuCol;
    gzInfo_getMenuDescription()->setString(sFishNames[idx]);
}

void gzInventoryMenu_c::executeFishSubMenu() {
    if (gzPad::getTrigDown()) {
        mFishSubMenuRow = (mFishSubMenuRow + 1) % FISH_GRID_ROWS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigUp()) {
        mFishSubMenuRow = (mFishSubMenuRow - 1 + FISH_GRID_ROWS) % FISH_GRID_ROWS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigRight()) {
        mFishSubMenuCol = (mFishSubMenuCol + 1) % FISH_GRID_COLS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigLeft()) {
        mFishSubMenuCol = (mFishSubMenuCol - 1 + FISH_GRID_COLS) % FISH_GRID_COLS;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigA()) {
        mFishEditField = 0;
        mFishAdjusting = false;
        gzInfo_onMenuOption();
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
    }
    if (gzPad::getTrigB()) {
        mFishSubMenuActive = false;
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    int idx = mFishSubMenuRow * FISH_GRID_COLS + mFishSubMenuCol;
    gzInfo_getMenuDescription()->setString(sFishNames[idx]);
}

void gzInventoryMenu_c::executePoeEditMode() {
    u8 poeCount = dComIfGs_getPohSpiritNum();

    if (gzPad::getTrigRight()) {
        poeCount = (poeCount >= 60) ? 0 : poeCount + 1;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getTrigLeft()) {
        poeCount = (poeCount == 0) ? 60 : poeCount - 1;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getRepeatX()) {
        s32 val = (s32)poeCount + 10;
        poeCount = (val > 60) ? 60 : (u8)val;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getRepeatY()) {
        s32 val = (s32)poeCount - 10;
        poeCount = (val < 0) ? 0 : (u8)val;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    dComIfGs_setPohSpiritNum(poeCount);

    if (gzPad::getTrigA() || gzPad::getTrigB()) {
        gzInfo_offMenuOption();
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString("Poe Souls");
}

void gzInventoryMenu_c::executeRupeeEditMode() {
    u16 rupees = dComIfGs_getRupee();
    u16 maxRupee = dComIfGs_getRupeeMax();

    if (gzPad::getTrigRight()) {
        rupees = (rupees >= maxRupee) ? 0 : rupees + 1;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getTrigLeft()) {
        rupees = (rupees == 0) ? maxRupee : rupees - 1;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getRepeatX()) {
        s32 val = (s32)rupees + 10;
        rupees = (val > maxRupee) ? maxRupee : (u16)val;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getRepeatY()) {
        s32 val = (s32)rupees - 10;
        rupees = (val < 0) ? 0 : (u16)val;
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    dComIfGs_setRupee(rupees);

    if (gzPad::getTrigZ()) {
        cyclePauseSlot(3, 0);
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getTrigA() || gzPad::getTrigB()) {
        gzInfo_offMenuOption();
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString("Wallet");
}

void gzInventoryMenu_c::executeHeartPieceEditMode() {
    u16 maxLife = dComIfGs_getMaxLife();

    if (gzPad::getTrigRight()) {
        if (maxLife < 100) {
            dComIfGs_setMaxLife(maxLife + 1);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    }

    if (gzPad::getTrigLeft()) {
        if (maxLife > 5) {
            dComIfGs_setMaxLife(maxLife - 1);
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    }

    if (gzPad::getTrigB()) {
        gzInfo_offMenuOption();
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        return;
    }
    gzInfo_getMenuDescription()->setString("Heart Pieces");
}

void gzInventoryMenu_c::drawSkillSubMenu() {
    static const f32 GRID_START_X = -15.0f;
    static const f32 GRID_START_Y = 70.0f;
    static const f32 CELL_SIZE = 52.0f;
    static const f32 LINE_H = 20.0f;
    static const f32 SCROLL_ICON_H = 16.0f;
    static const f32 SCROLL_ICON_W = SCROLL_ICON_H * 32.0f / 80.0f;
    static const f32 STATUS_ICON_SIZE = 14.0f;
    static const f32 ICON_PAD_X = 8.0f;

    static const f32 ROW_SPACING = 56.0f;

    f32 baseX = mXPos + GRID_START_X;
    f32 baseY = g_gzInfo.mBackgroundYPos + GRID_START_Y;
    f32 panelX = baseX + PAUSE_MAX_COLS * CELL_SIZE + 26.0f;
    f32 bgRight = g_gzInfo.mBackgroundXPos + g_gzInfo.mBackgroundWidth;
    f32 bgBottom = g_gzInfo.mBackgroundYPos + g_gzInfo.mBackgroundHeight;
    f32 panelW = bgRight - panelX - 10.0f;
    f32 panelY = g_gzInfo.mBackgroundYPos + 42.0f;
    f32 panelH = bgBottom - panelY - 10.0f;

    u32 themeColor = gzInfo_getTextColor();
    GXColor borderColor = gzGetThemedBorderColor(themeColor, 255);
    gzDrawVerticalLine(panelX, panelY, panelY + panelH, 1.0f, borderColor);

    for (int i = 0; i < 7; i++) {
        f32 lineY = panelY + 8.0f + i * LINE_H;
        bool enabled = dComIfGs_isEventBit(sSkillFlags[i]);

        u32 textColor;
        if (inSkillSubMenu() && mSkillSubMenuIndex == i) {
            textColor = themeColor;
        } else if (enabled) {
            textColor = COLOR_WHITE;
        } else {
            textColor = 0x808080FFu;
        }

        if (mpSkillsIconPane != NULL) {
            gzSetup2DContext();
            u8 iconAlpha = enabled ? 255 : 80;
            mpSkillsIconPane->setAlpha(iconAlpha);
            mpSkillsIconPane->rotate(0.0f, 0.0f, ROTATE_Z, 0.0f);
            f32 iconX = panelX + ICON_PAD_X;
            f32 iconY = lineY + (LINE_H - SCROLL_ICON_H) / 2.0f;
            mpSkillsIconPane->draw(iconX, iconY, SCROLL_ICON_W, SCROLL_ICON_H,
                                   false, false, false);
        }

        gzSetup2DContext();
        gzTextBox* numText = gzTextBox_allocate();
        numText->setFontSize(14.0f, 14.0f);
        numText->setString(sSkillNumbers[i]);
        f32 textX = panelX + ICON_PAD_X + SCROLL_ICON_W + 4.0f;
        numText->draw(textX, lineY + 16.0f, textColor);
        gzTextBox_free(numText);

        f32 statusRightEdge = panelX + panelW - ICON_PAD_X;
        f32 statusX = statusRightEdge - STATUS_ICON_SIZE;

        gzSetup2DContext();
        gzTextBox* nameText = gzTextBox_allocate();
        nameText->setFontSize(12.0f, 12.0f);
        nameText->setString(sSkillNames[i]);
        f32 nameRightEdge = statusX - 4.0f;
        f32 nameDrawX = nameRightEdge - 608.0f;
        nameText->draw(nameDrawX, lineY + 16.0f, textColor, HBIND_RIGHT);
        gzTextBox_free(nameText);

        J2DPicture* statusIcon = enabled ? mpCheckIconPane : mpXMarkIconPane;
        if (statusIcon != NULL) {
            gzSetup2DContext();
            statusIcon->setAlpha(255);
            f32 statusY = lineY + (LINE_H - STATUS_ICON_SIZE) / 2.0f;
            statusIcon->draw(statusX, statusY, STATUS_ICON_SIZE, STATUS_ICON_SIZE,
                             false, false, false);
        }
    }

    if (inSkillSubMenu() && mIsEntered && gzInfo_isCursorTypeTP() &&
        gzInfo_getTPCursor() != NULL) {
        f32 cursorY = panelY + 8.0f + mSkillSubMenuIndex * LINE_H + LINE_H / 2.0f;
        f32 cursorX = panelX + panelW / 2.0f;
        gzInfo_getTPCursor()->setPos(cursorX, cursorY);
        gzInfo_getTPCursor()->setParam(7.0f, 0.4f, 0.03f, 0.6f, 0.5f);
        gzInfo_getTPCursor()->draw();
    }
}

void gzInventoryMenu_c::drawBugSubMenu() {
    static const f32 GRID_START_X = -15.0f;
    static const f32 CELL_SIZE = 52.0f;
    static const f32 BUG_ICON_SIZE = 28.0f;

    f32 baseX = mXPos + GRID_START_X;
    f32 panelX = baseX + PAUSE_MAX_COLS * CELL_SIZE + 26.0f;
    f32 bgRight = g_gzInfo.mBackgroundXPos + g_gzInfo.mBackgroundWidth;
    f32 bgBottom = g_gzInfo.mBackgroundYPos + g_gzInfo.mBackgroundHeight;
    f32 panelW = bgRight - panelX - 10.0f;
    f32 panelY = g_gzInfo.mBackgroundYPos + 42.0f;
    f32 panelH = bgBottom - panelY - 10.0f;

    u32 themeColor = gzInfo_getTextColor();
    GXColor borderColor = gzGetThemedBorderColor(themeColor, 255);
    gzDrawVerticalLine(panelX, panelY, panelY + panelH, 1.0f, borderColor);

    f32 cellW = panelW / (f32)BUG_GRID_COLS;
    f32 cellH = panelH / (f32)BUG_GRID_ROWS;

    for (int row = 0; row < BUG_GRID_ROWS; row++) {
        for (int col = 0; col < BUG_GRID_COLS; col++) {
            int idx = row * BUG_GRID_COLS + col;
            f32 cellX = panelX + col * cellW;
            f32 cellY = panelY + row * cellH;
            bool collected = dComIfGs_isItemFirstBit(sBugItemIds[idx]) != 0;
            bool isSelected = inBugSubMenu() && mBugSubMenuRow == row && mBugSubMenuCol == col;

            f32 iconX = cellX + (cellW - BUG_ICON_SIZE) / 2.0f;
            f32 iconY = cellY + 4.0f;

            if (mpBugIconPanes[idx] != NULL) {
                gzSetup2DContext();
                mpBugIconPanes[idx]->setAlpha(collected ? 255 : 80);
                f32 drawSize = isSelected ? BUG_ICON_SIZE + 8.0f : BUG_ICON_SIZE;
                f32 drawX = iconX - (drawSize - BUG_ICON_SIZE) / 2.0f;
                f32 drawY = iconY - (drawSize - BUG_ICON_SIZE) / 2.0f;
                mpBugIconPanes[idx]->draw(drawX, drawY, drawSize, drawSize,
                                          false, false, false);
            }

            bool givenToAgitha = dComIfGs_isEventBit(sBugTurnInFlags[idx]) != 0;
            if (givenToAgitha && mpButterflyIconPane != NULL) {
                static const f32 BUTTERFLY_SIZE = 12.0f;
                gzSetup2DContext();
                mpButterflyIconPane->setAlpha(220);
                mpButterflyIconPane->draw(iconX - 2.0f, iconY - 2.0f,
                                          BUTTERFLY_SIZE, BUTTERFLY_SIZE,
                                          false, false, false);
            }

        }

        gzSetup2DContext();
        int speciesIdx = row * (BUG_GRID_COLS / 2);
        for (int pair = 0; pair < BUG_GRID_COLS / 2; pair++) {
            bool pairSelected = inBugSubMenu() && mBugSubMenuRow == row &&
                                mBugSubMenuCol / 2 == pair && gzInfo_isCursorTypeClassic();
            u32 nameColor = pairSelected ? themeColor : 0xA0A0A0FFu;
            gzTextBox* nameText = gzTextBox_allocate();
            nameText->setFontSize(9.0f, 9.0f);
            nameText->setString(sBugSpeciesNames[speciesIdx + pair]);
            f32 pairCenterX = panelX + (pair * 2) * cellW + cellW;
            f32 nameY = panelY + row * cellH + 4.0f + BUG_ICON_SIZE + 16.0f;
            nameText->draw(pairCenterX - 305.0f, nameY, nameColor, HBIND_CENTER);
            gzTextBox_free(nameText);
        }
    }

    if (inBugSubMenu() && mIsEntered && gzInfo_isCursorTypeTP() &&
        gzInfo_getTPCursor() != NULL) {
        f32 cellX = panelX + mBugSubMenuCol * cellW;
        f32 cellY = panelY + mBugSubMenuRow * cellH;
        f32 cursorX = cellX + cellW / 2.0f;
        f32 cursorY = cellY + 4.0f + (BUG_ICON_SIZE + 4.0f) / 2.0f;
        gzInfo_getTPCursor()->setPos(cursorX, cursorY);
        gzInfo_getTPCursor()->setParam(0.7f, 0.55f, 0.03f, 0.6f, 0.5f);
        gzInfo_getTPCursor()->draw();
    }
}

void gzInventoryMenu_c::drawLetterSubMenu() {
    static const f32 GRID_START_X = -15.0f;
    static const f32 CELL_SIZE = 52.0f;
    static const f32 LETTER_ICON_SIZE = 28.0f;

    f32 baseX = mXPos + GRID_START_X;
    f32 panelX = baseX + PAUSE_MAX_COLS * CELL_SIZE + 26.0f;
    f32 bgRight = g_gzInfo.mBackgroundXPos + g_gzInfo.mBackgroundWidth;
    f32 bgBottom = g_gzInfo.mBackgroundYPos + g_gzInfo.mBackgroundHeight;
    f32 panelW = bgRight - panelX - 10.0f;
    f32 panelY = g_gzInfo.mBackgroundYPos + 42.0f;
    f32 panelH = bgBottom - panelY - 10.0f;

    u32 themeColor = gzInfo_getTextColor();
    GXColor borderColor = gzGetThemedBorderColor(themeColor, 255);
    gzDrawVerticalLine(panelX, panelY, panelY + panelH, 1.0f, borderColor);

    f32 cellW = panelW / (f32)LETTER_GRID_COLS;
    f32 cellH = panelH / (f32)LETTER_GRID_ROWS;

    for (int row = 0; row < LETTER_GRID_ROWS; row++) {
        for (int col = 0; col < LETTER_GRID_COLS; col++) {
            int idx = row * LETTER_GRID_COLS + col;
            f32 cellX = panelX + col * cellW;
            f32 cellY = panelY + row * cellH;
            bool received = dComIfGs_isLetterGetFlag(idx) != 0;
            bool isSelected = inLetterSubMenu() && mLetterSubMenuRow == row &&
                              mLetterSubMenuCol == col;

            f32 iconX = cellX + (cellW - LETTER_ICON_SIZE) / 2.0f;
            f32 iconY = cellY + 14.0f;

            if (mpLetterIconPane != NULL) {
                gzSetup2DContext();
                mpLetterIconPane->setAlpha(received ? 255 : 80);
                mpLetterIconPane->draw(iconX, iconY, LETTER_ICON_SIZE, LETTER_ICON_SIZE,
                                       false, false, false);
            }

            gzSetup2DContext();
            gzTextBox* nameText = gzTextBox_allocate();
            nameText->setFontSize(9.0f, 9.0f);
            nameText->setString(sLetterSendersShort[idx]);
            u32 textColor = isSelected ? themeColor : (received ? COLOR_WHITE : 0x808080FFu);
            f32 textX = cellX + cellW / 2.0f - 305.0f;
            f32 textY = iconY + LETTER_ICON_SIZE + 10.0f;
            nameText->draw(textX, textY, textColor, HBIND_CENTER);
            gzTextBox_free(nameText);
        }
    }

    if (inLetterSubMenu() && mIsEntered && gzInfo_isCursorTypeTP() &&
        gzInfo_getTPCursor() != NULL) {
        f32 cellX = panelX + mLetterSubMenuCol * cellW;
        f32 cellY = panelY + mLetterSubMenuRow * cellH;
        f32 cursorX = cellX + cellW / 2.0f;
        f32 cursorY = cellY + 19.0f + (LETTER_ICON_SIZE + 4.0f) / 2.0f;
        gzInfo_getTPCursor()->setPos(cursorX, cursorY);
        gzInfo_getTPCursor()->setParam(1.0f, 1.0f, 0.03f, 0.6f, 0.5f);
        gzInfo_getTPCursor()->draw();
    }
}

void gzInventoryMenu_c::drawFishSubMenu() {
    static const f32 GRID_START_X = -15.0f;
    static const f32 CELL_SIZE = 52.0f;
    static const f32 FISH_ICON_SIZE = 28.0f;
    static const f32 STATUS_ICON_SIZE = 10.0f;

    f32 baseX = mXPos + GRID_START_X;
    f32 panelX = baseX + PAUSE_MAX_COLS * CELL_SIZE + 26.0f;
    f32 bgRight = g_gzInfo.mBackgroundXPos + g_gzInfo.mBackgroundWidth;
    f32 bgBottom = g_gzInfo.mBackgroundYPos + g_gzInfo.mBackgroundHeight;
    f32 panelW = bgRight - panelX - 10.0f;
    f32 lineTop = g_gzInfo.mBackgroundYPos + 40.0f;
    f32 lineBot = bgBottom - 7.0f;
    f32 panelY = lineTop + 2.0f;
    f32 panelH = lineBot - panelY - 2.0f;

    u32 themeColor = gzInfo_getTextColor();
    GXColor borderColor = gzGetThemedBorderColor(themeColor, 255);
    gzDrawVerticalLine(panelX, lineTop, lineBot, 1.0f, borderColor);

    f32 cellW = panelW / (f32)FISH_GRID_COLS;
    f32 cellH = panelH / (f32)FISH_GRID_ROWS;

    for (int row = 0; row < FISH_GRID_ROWS; row++) {
        for (int col = 0; col < FISH_GRID_COLS; col++) {
            int gridIdx = row * FISH_GRID_COLS + col;
            u8 fishIdx = sFishGridIdx[gridIdx];
            f32 cellX = panelX + col * cellW;
            f32 cellY = panelY + row * cellH;
            bool caught = dComIfGs_getFishNum(fishIdx) > 0;
            bool isSelected = inFishSubMenu() && mFishSubMenuRow == row &&
                              mFishSubMenuCol == col;

            f32 iconX = cellX + 35.0f + (col == 1 ? 20.0f : 0.0f);
            f32 iconY = cellY + 39.0f;

            if (mpFishIconPane != NULL) {
                gzSetup2DContext();
                mpFishIconPane->setAlpha(caught ? 255 : 80);
                mpFishIconPane->draw(iconX, iconY, FISH_ICON_SIZE, FISH_ICON_SIZE,
                                      false, false, false);
            }

            u8 fishSize = dComIfGs_getFishSize(fishIdx);
            u16 fishCount = dComIfGs_getFishNum(fishIdx);
            bool isEditing = inFishEditMode() && isSelected;

            static char sSizeBuf[16];
            static char sCountBuf[16];
            snprintf(sSizeBuf, sizeof(sSizeBuf), "%d in.", fishSize);
            snprintf(sCountBuf, sizeof(sCountBuf), "%d fish", fishCount);

            f32 valX = iconX + FISH_ICON_SIZE + 35.0f;
            f32 valTopY = iconY + 5.0f;
            f32 nameY = iconY + FISH_ICON_SIZE + 10.0f;
            f32 valBotY = nameY;

            bool useClassicColors = gzInfo_isCursorTypeClassic();
            u32 sizeColor, countColor;
            if (isEditing && useClassicColors) {
                sizeColor = (mFishEditField == 1) ? themeColor : 0xAAAAAAFFu;
                countColor = (mFishEditField == 0) ? themeColor : 0xAAAAAAFFu;
            } else if (isSelected && useClassicColors) {
                sizeColor = themeColor;
                countColor = themeColor;
            } else {
                sizeColor = caught ? COLOR_WHITE : 0x808080FFu;
                countColor = sizeColor;
            }

            gzSetup2DContext();
            gzTextBox* sizeText = gzTextBox_allocate();
            sizeText->setFontSize(10.0f, 10.0f);
            sizeText->setString(sSizeBuf);
            sizeText->draw(valX, valTopY, sizeColor, HBIND_LEFT);
            sizeText->updateBounds();
            if (isSelected) mFishSizeTextW = sizeText->mBounds.f.x;

            if (inFishAdjusting() && isSelected && mFishEditField == 1 && mpHaihai != NULL) {
                gzSetup2DContext();
                mpHaihai->setScale(10.0f * gzMenuLayout::HAIHAI_SCALE_FACTOR);
                f32 haihaiX = valX + (sizeText->mBounds.f.x / 2.0f) + gzMenuLayout::HAIHAI_X_OFFSET;
                f32 haihaiY = valTopY + gzMenuLayout::HAIHAI_Y_OFFSET + 2.0f;
                f32 haihaiW = sizeText->mBounds.f.x + 14.0f;
                u8 arrows = 0;
                if (fishSize > 0) arrows |= ARROW_LEFT;
                if (fishSize < 255) arrows |= ARROW_RIGHT;
                if (arrows) mpHaihai->drawHaihai(arrows, haihaiX, haihaiY, haihaiW, 0.0f);
            }
            gzTextBox_free(sizeText);

            gzSetup2DContext();
            gzTextBox* countText = gzTextBox_allocate();
            countText->setFontSize(10.0f, 10.0f);
            countText->setString(sCountBuf);
            countText->draw(valX, valBotY, countColor, HBIND_LEFT);
            countText->updateBounds();
            if (isSelected) mFishCountTextW = countText->mBounds.f.x;

            if (inFishAdjusting() && isSelected && mFishEditField == 0 && mpHaihai != NULL) {
                gzSetup2DContext();
                mpHaihai->setScale(10.0f * gzMenuLayout::HAIHAI_SCALE_FACTOR);
                f32 haihaiX = valX + (countText->mBounds.f.x / 2.0f) + gzMenuLayout::HAIHAI_X_OFFSET;
                f32 haihaiY = valBotY + gzMenuLayout::HAIHAI_Y_OFFSET + 2.0f;
                f32 haihaiW = countText->mBounds.f.x + 14.0f;
                u8 arrows = 0;
                if (fishCount > 0) arrows |= ARROW_LEFT;
                if (fishCount < 999) arrows |= ARROW_RIGHT;
                if (arrows) mpHaihai->drawHaihai(arrows, haihaiX, haihaiY, haihaiW, 0.0f);
            }
            gzTextBox_free(countText);

            gzSetup2DContext();
            gzTextBox* nameText = gzTextBox_allocate();
            nameText->setFontSize(9.0f, 9.0f);
            nameText->setString(sFishNames[gridIdx]);
            u32 textColor = (isSelected && useClassicColors) ? themeColor : (caught ? COLOR_WHITE : 0x808080FFu);
            f32 textX = iconX + FISH_ICON_SIZE / 2.0f - 304.0f;
            f32 textY = iconY + FISH_ICON_SIZE + 10.0f;
            nameText->draw(textX, textY, textColor, HBIND_CENTER);
            gzTextBox_free(nameText);
        }
    }

    if (inFishSubMenu() && mIsEntered && gzInfo_isCursorTypeTP() &&
        gzInfo_getTPCursor() != NULL) {
        f32 cellX = panelX + mFishSubMenuCol * cellW;
        f32 cellY = panelY + mFishSubMenuRow * cellH;
        f32 iconX = cellX + 35.0f + (mFishSubMenuCol == 1 ? 20.0f : 0.0f);
        f32 iconY = cellY + 39.0f;

        if (inFishEditMode()) {
            f32 valX = iconX + FISH_ICON_SIZE + 35.0f;
            f32 valTopY = iconY + 5.0f;
            f32 valBotY = iconY + FISH_ICON_SIZE + 10.0f;

            f32 textW = (mFishEditField == 1) ? mFishSizeTextW : mFishCountTextW;
            f32 targetY = (mFishEditField == 1) ? valTopY : valBotY;
            f32 cursorX = valX + textW / 2.0f;
            f32 xScale = (textW + 30.0f) * 0.02f;
            gzInfo_getTPCursor()->setPos(cursorX, targetY - 4.0f);
            gzInfo_getTPCursor()->setParam(xScale, 0.2f, 0.03f, 0.6f, 0.5f);
        } else {
            f32 cursorX = iconX + FISH_ICON_SIZE / 2.0f + 25.0f;
            f32 cursorY = cellY + cellH / 2.0f;
            gzInfo_getTPCursor()->setPos(cursorX, cursorY);
            gzInfo_getTPCursor()->setParam(2.5f, 2.2f, 0.03f, 0.8f, 0.5f);
        }
        gzInfo_getTPCursor()->draw();
    }
}
