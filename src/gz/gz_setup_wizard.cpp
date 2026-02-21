#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_setup_wizard.h"
#include "gz/gz_menu.h"
#include "gz/gz_textbox.h"
#include "gz/gz_utility_draw.h"

gzSetupWizard_c::gzSetupWizard_c() {
    mStep = STEP_WELCOME;
    mSelection = 0;
    mBootToMenu = false;
    mMenuPauses = true;
    mDisplayMode = false;
    mMenuSfx = true;
    mThemeIndex = 10;

    mpTitle = gzTextBox_allocate();
    mpQuestion = gzTextBox_allocate();
    mpOption0 = gzTextBox_allocate();
    mpOption1 = gzTextBox_allocate();
    mpOption2 = gzTextBox_allocate();
    mpHint = gzTextBox_allocate();
}

gzSetupWizard_c::~gzSetupWizard_c() {
    gzTextBox* boxes[] = {mpTitle, mpQuestion, mpOption0, mpOption1, mpOption2, mpHint};
    for (int i = 0; i < 6; i++) {
        if (boxes[i] != NULL) {
            boxes[i]->setFontSize(18.0f, 18.0f);
        }
    }

    gzTextBox_free(mpTitle);
    gzTextBox_free(mpQuestion);
    gzTextBox_free(mpOption0);
    gzTextBox_free(mpOption1);
    gzTextBox_free(mpOption2);
    gzTextBox_free(mpHint);
}

void gzSetupWizard_c::applySettings() {
    g_gzInfo.setBootToMenu(mBootToMenu);
    g_gzInfo.setMenuPausesGame(mMenuPauses);
    g_gzInfo.setDisplayMode(mDisplayMode);
    g_gzInfo.setMenuSfx(mMenuSfx);
    g_gzInfo.setTextColor(GZ_TEXT_COLORS[mThemeIndex]);

    if (mDisplayMode) {
        gzInfo_setDisplayModeProgressive();
    } else {
        gzInfo_setDisplayModeInterlaced();
    }

    gzInfo_storeSettings();
}

void gzSetupWizard_c::execute() {
    if (mStep == STEP_DONE) return;

    if (gzPad::getTrigLeft() || gzPad::getTrigRight()) {
        bool isLeft = gzPad::getTrigLeft();
        switch (mStep) {
        case STEP_WELCOME:
        case STEP_BOOT_TARGET:
        case STEP_MENU_PAUSES:
        case STEP_DISPLAY_MODE:
        case STEP_MENU_SFX:
            mSelection ^= 1;
            break;
        case STEP_THEME:
            mThemeIndex = isLeft ? (mThemeIndex - 1 + GZ_NUM_TEXT_COLORS) % GZ_NUM_TEXT_COLORS
                                 : (mThemeIndex + 1) % GZ_NUM_TEXT_COLORS;
            g_gzInfo.setTextColor(GZ_TEXT_COLORS[mThemeIndex]);
            break;
        default:
            break;
        }
        if (mStep == STEP_MENU_SFX) g_gzInfo.setMenuSfx(mSelection == 0);
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }

    if (gzPad::getTrigB() && mStep != STEP_WELCOME && mStep != STEP_COMPLETE) {
        switch (mStep) {
        case STEP_THEME:
            mStep = STEP_WELCOME;
            mSelection = 1;
            break;
        case STEP_BOOT_TARGET:
            mStep = STEP_THEME;
            mSelection = 0;
            break;
        case STEP_MENU_PAUSES:
            mStep = STEP_BOOT_TARGET;
            mSelection = mBootToMenu ? 1 : 0;
            break;
        case STEP_DISPLAY_MODE:
            mStep = STEP_MENU_PAUSES;
            mSelection = mMenuPauses ? 0 : 1;
            break;
        case STEP_MENU_SFX:
            mStep = STEP_DISPLAY_MODE;
            mSelection = mDisplayMode ? 1 : 0;
            break;
        default:
            break;
        }
        gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
    }

    if (gzPad::getTrigA()) {
        bool wasComplete = (mStep == STEP_COMPLETE);
        switch (mStep) {
        case STEP_WELCOME:
            if (mSelection == 0) {
                applySettings();
                mStep = STEP_DONE;
            } else {
                mStep = STEP_THEME;
                mSelection = 0;
            }
            break;
        case STEP_THEME:
            mStep = STEP_BOOT_TARGET;
            mSelection = 0;
            break;
        case STEP_BOOT_TARGET:
            mBootToMenu = (mSelection == 1);
            mStep = STEP_MENU_PAUSES;
            mSelection = 0;
            break;
        case STEP_MENU_PAUSES:
            mMenuPauses = (mSelection == 0);
            mStep = STEP_DISPLAY_MODE;
            mSelection = 0;
            break;
        case STEP_DISPLAY_MODE:
            mDisplayMode = (mSelection == 1);
            mStep = STEP_MENU_SFX;
            mSelection = 0;
            break;
        case STEP_MENU_SFX:
            mMenuSfx = (mSelection == 0);
            applySettings();
            mStep = STEP_COMPLETE;
            mSelection = 0;
            break;
        case STEP_COMPLETE:
            mStep = STEP_DONE;
            break;
        default:
            break;
        }
        if (!wasComplete) {
            gzInfo_seStart(Z2SE_SY_CURSOR_OK);
        }
    }

    if (mStep == STEP_DISPLAY_MODE) {
        if (mSelection == 1) {
            gzInfo_setDisplayModeProgressive();
        } else {
            gzInfo_setDisplayModeInterlaced();
        }
    }
    if (mStep == STEP_MENU_SFX) {
        g_gzInfo.setMenuSfx(mSelection == 0);
    }
}

void gzSetupWizard_c::draw() {
    if (mStep == STEP_DONE) return;

    u32 theme = g_gzInfo.getTextColor();
    u32 cursorColor = gzInfo_getCursorColor();

    static const f32 BOX_W = 380.0f;
    static const f32 BOX_H = 180.0f;
    static const f32 BOX_X = (608.0f - BOX_W) / 2.0f;
    static const f32 BOX_Y = (448.0f - BOX_H) / 2.0f;

    // GX primitives
    GXColor bgColor = {35, 33, 25, 220};
    gzDrawFilledRect(BOX_X, BOX_Y, BOX_W, BOX_H, bgColor);

    GXColor borderColor = gzGetThemedBorderColor(theme, 255);
    gzDrawRectOutline(BOX_X, BOX_Y, BOX_W, BOX_H, 2.0f, borderColor);

    GXColor innerColor = gzGetThemedHighlightColor(theme, 120);
    gzDrawRectOutline(BOX_X + 2.0f, BOX_Y + 2.0f, BOX_W - 4.0f, BOX_H - 4.0f, 1.0f, innerColor);

    GXColor sepColor = gzGetThemedSeparatorColor(theme, 180);
    gzDrawHorizontalLine(BOX_X + 10.0f, BOX_X + BOX_W - 10.0f, BOX_Y + 46.0f, 1.0f, sepColor);

    // Reset J2D context after GX primitives
    gzSetup2DContext();

    if (mpTitle != NULL) {
        mpTitle->setFontSize(22.0f, 22.0f);
        mpTitle->setString("tpgz v2 setup");
        mpTitle->draw(0.0f, BOX_Y + 33.0f, theme, HBIND_CENTER);
    }

    const char* question = "";
    switch (mStep) {
    case STEP_WELCOME: question = "run first time setup?"; break;
    case STEP_BOOT_TARGET: question = "when tpgz boots, what should load?"; break;
    case STEP_MENU_PAUSES: question = "should the menu pause the game?"; break;
    case STEP_THEME: question = "select your theme"; break;
    case STEP_DISPLAY_MODE: question = "select display mode"; break;
    case STEP_MENU_SFX: question = "enable menu sound effects?"; break;
    case STEP_COMPLETE: question = "setup complete!"; break;
    default: break;
    }

    if (mpQuestion != NULL) {
        mpQuestion->setFontSize(18.0f, 18.0f);
        mpQuestion->setString(question);
        mpQuestion->draw(0.0f, BOX_Y + 68.0f, COLOR_WHITE, HBIND_CENTER);
    }

    f32 optionY = BOX_Y + 110.0f;

    switch (mStep) {
    case STEP_WELCOME:
        drawBinaryOptions("no", "yes", 40.0f, optionY, cursorColor);
        break;
    case STEP_BOOT_TARGET:
        drawBinaryOptions("title screen", "tpgz menu", 60.0f, optionY, cursorColor);
        break;
    case STEP_MENU_PAUSES:
        drawBinaryOptions("yes", "no", 40.0f, optionY, cursorColor);
        break;
    case STEP_THEME: {
        if (mpOption0 != NULL) {
            mpOption0->setFontSize(18.0f, 18.0f);
            mpOption0->setStringf("< %s >", gzGetThemeColorName(GZ_TEXT_COLORS[mThemeIndex]));
            mpOption0->draw(0.0f, optionY, cursorColor, HBIND_CENTER);
        }
        break;
    }
    case STEP_DISPLAY_MODE:
        drawBinaryOptions("interlaced", "progressive", 60.0f, optionY, cursorColor);
        break;
    case STEP_MENU_SFX:
        drawBinaryOptions("yes", "no", 40.0f, optionY, cursorColor);
        break;
    case STEP_COMPLETE: {
        if (mpOption0 != NULL) {
            mpOption0->setFontSize(18.0f, 18.0f);
            mpOption0->setString("ok");
            mpOption0->draw(0.0f, optionY, cursorColor, HBIND_CENTER);
        }
        break;
    }
    default:
        break;
    }

    if (mpHint != NULL) {
        const char* hint = "";
        switch (mStep) {
        case STEP_THEME: hint = "d-pad left/right to cycle, A to confirm"; break;
        case STEP_COMPLETE: hint = "A to confirm"; break;
        default: hint = "d-pad left/right to select, A to confirm"; break;
        }
        mpHint->setFontSize(14.0f, 14.0f);
        mpHint->setString(hint);
        mpHint->draw(0.0f, BOX_Y + BOX_H - 22.0f, COLOR_GRAY, HBIND_CENTER);
    }
}

void gzSetupWizard_c::drawBinaryOptions(const char* text0, const char* text1, f32 spread,
                                         f32 y, u32 selColor) {
    u32 col0 = (mSelection == 0) ? selColor : COLOR_WHITE;
    u32 col1 = (mSelection == 1) ? selColor : COLOR_WHITE;
    if (mpOption0 != NULL) {
        mpOption0->setFontSize(18.0f, 18.0f);
        mpOption0->setString(text0);
        mpOption0->draw(-spread, y, col0, HBIND_CENTER);
    }
    if (mpOption1 != NULL) {
        mpOption1->setFontSize(18.0f, 18.0f);
        mpOption1->setString(text1);
        mpOption1->draw(spread, y, col1, HBIND_CENTER);
    }
}
