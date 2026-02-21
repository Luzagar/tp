#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_menu_scene.h"
#include "gz/gz_menu_main.h"
#include "gz/gz_utility_draw.h"
#include "d/d_select_cursor.h"
#include "JSystem/J2DGraph/J2DPicture.h"

// Environment tab
static gzBoolOption_s envOptions[] = {
    {"freeze time", "stop time of day from passing", gzInfo_isScene_FreezeTime, gzInfo_onScene_FreezeTime, gzInfo_offScene_FreezeTime},
    {"freeze actors", "freeze actors in place", gzInfo_isScene_FreezeActors, gzInfo_onScene_FreezeActors, gzInfo_offScene_FreezeActors},
    {"freeze camera", "freeze camera in place", gzInfo_isScene_FreezeCamera, gzInfo_onScene_FreezeCamera, gzInfo_offScene_FreezeCamera},
};

// Audio tab
static gzBoolOption_s audioOptions[] = {
    {"mute bgm", "mute all background music", gzInfo_isScene_MuteBGM, gzInfo_onScene_MuteBGM, gzInfo_offScene_MuteBGM},
    {"mute sfx", "mute all sound effects", gzInfo_isScene_MuteSFX, gzInfo_onScene_MuteSFX, gzInfo_offScene_MuteSFX},
};

gzSceneMenu_c::gzSceneMenu_c() {
    OSReport("creating gzSceneMenu_c\n");
    mXPos = g_gzInfo.mBackgroundXPos + 170.0f;

    for (int i = 0; i < TAB_MAX_e; i++) {
        mpTabHeaders[i] = gzTextBox_allocate();
        mpTabHeaders[i]->setFontSize(15.0f, 15.0f);
    }

    mpTabHeaders[TAB_ENV_e]->setString("environment");
    mpTabHeaders[TAB_VIEWERS_e]->setString("viewers");
    mpTabHeaders[TAB_AUDIO_e]->setString("audio");

    // environment tab
    for (int i = 0; i < ENV_MAX; i++) {
        mpEnvLines[i] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine(envOptions[i].name, envOptions[i].desc,
                                                   envOptions[i].is, envOptions[i].on, envOptions[i].off);
    }

    // audio tab
    for (int i = 0; i < AUDIO_MAX; i++) {
        mpAudioLines[i] = new (gzHeap(GZ_GROUP_MENU), 4) gzBoolOptionLine(audioOptions[i].name, audioOptions[i].desc,
                                                   audioOptions[i].is, audioOptions[i].on, audioOptions[i].off);
    }

    mCurrentTab = TAB_ENV_e;
    gzInfo_resetTopLine();
    gzInfo_offMenuOption();
}

gzSceneMenu_c::~gzSceneMenu_c() {
    _delete();
}

void gzSceneMenu_c::_delete() {
    OSReport("deleting gzSceneMenu_c\n");

    for (int i = 0; i < TAB_MAX_e; i++) {
        gzTextBox_free(mpTabHeaders[i]);
        mpTabHeaders[i] = NULL;
    }

    for (int i = 0; i < ENV_MAX; i++) {
        delete mpEnvLines[i];
        mpEnvLines[i] = NULL;
    }
}

int gzSceneMenu_c::getCurrentLineNum() {
    switch (mCurrentTab) {
    case TAB_ENV_e:
        return ENV_MAX;
    case TAB_AUDIO_e:
        return AUDIO_MAX;
    }
    return 0;
}

void gzSceneMenu_c::onHighlight() {
}

void gzSceneMenu_c::onUnhighlight() {
}

void gzSceneMenu_c::execute() {
    if (checkInputWait()) return;
    if (handleBackButton(gzMainMenu_c::MENU_SCENE)) return;

    gzCursor* l_cursor = gzInfo_getCursor();
    gzBoolOption_s* flags = NULL;
    int maxIdx = 0;

    switch (mCurrentTab) {
    case TAB_ENV_e:
        flags = envOptions;
        maxIdx = ENV_MAX;
        break;
    case TAB_VIEWERS_e:
        break;
    case TAB_AUDIO_e:
        flags = audioOptions;
        maxIdx = AUDIO_MAX;
        break;
    }

    if (gzPad::getTrigR() && !gzInfo_isMenuOption()) {
        mCurrentTab = (mCurrentTab + 1) % TAB_MAX_e;
        l_cursor->y = 0;
        gzInfo_resetTopLine();
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }
    if (gzPad::getTrigL() && !gzInfo_isMenuOption()) {
        mCurrentTab = (mCurrentTab - 1 + TAB_MAX_e) % TAB_MAX_e;
        l_cursor->y = 0;
        gzInfo_resetTopLine();
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getTrigA()) {
        if (l_cursor->y < maxIdx) {
            if (flags[l_cursor->y].is())
                flags[l_cursor->y].off();
            else
                flags[l_cursor->y].on();
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    }

    handleNavigation(maxIdx);
    finishExecute(maxIdx);
}

void gzSceneMenu_c::draw() {
    static const f32 ICON_SIZE = 14.0f;
    static const u32 COLOR_DIM = 0x808080FFu;

    // Set up tab header x positions
    static const f32 TAB_PADDING = 5.0f;
    f32 tabXPositions[TAB_MAX_e];
    f32 tabBaseX = mXPos;
    tabXPositions[0] = tabBaseX;
    for (int i = 1; i < TAB_MAX_e; i++) {
        mpTabHeaders[i - 1]->updateBounds();
        tabXPositions[i] = tabXPositions[i - 1] + mpTabHeaders[i - 1]->mBounds.f.x + TAB_PADDING;
    }

    // Get current tab's lines and flags
    gzBoolOptionLine** currentLines;
    gzBoolOption_s* flags;
    int currentLineNum;
    switch (mCurrentTab) {
    case TAB_ENV_e:
        currentLines = mpEnvLines;
        flags = envOptions;
        currentLineNum = ENV_MAX;
        break;
    case TAB_VIEWERS_e:
        break;
    case TAB_AUDIO_e:
        currentLines = mpAudioLines;
        flags = audioOptions;
        currentLineNum = AUDIO_MAX;
        break;
    }

    // Draw tab headers
    f32 yHeader = g_gzInfo.mBackgroundYPos + gzMenuLayout::TAB_HEADER_Y_OFFSET;
    drawTabHeaders(mpTabHeaders, tabXPositions, TAB_MAX_e, mCurrentTab, yHeader, gzInfo_getCursorColor());

    // TODO
    if (mCurrentTab == TAB_VIEWERS_e) {
        return;
    }

    // Draw lines with icons
    gzCursor* l_cursor = gzInfo_getCursor();
    u32 cursorColor = gzInfo_getCursorColor();
    f32 lineX = mXPos;
    f32 optionX = mXPos + getCurrentOptionsXOffset();
    f32 lineY_start = g_gzInfo.mBackgroundYPos + mLineYStart;
    s32 topLine = gzInfo_getTopLine();
    s32 endLine = topLine + gzMenuLayout::VISIBLE_LINES;
    if (endLine > currentLineNum) endLine = currentLineNum;

    for (s32 i = topLine; i < endLine; i++) {
        gzBoolOptionLine* line = currentLines[i];
        s32 screenIdx = i - topLine;
        f32 lineY = lineY_start + (screenIdx * gzMenuLayout::LINE_SPACING);
        bool isSelected = (l_cursor->y == i && gzInfo_isSubMenuVisible());
        bool isOn = flags[i].is();
        bool classicHL = isSelected && gzInfo_isCursorTypeClassic();
        u32 color = classicHL ? cursorColor : (isOn ? COLOR_WHITE : COLOR_DIM);

        line->mText->draw(lineX, lineY, color);

        J2DPicture* icon = isOn ? gzInfo_getCheckIcon() : gzInfo_getXMarkIcon();
        if (icon != NULL) {
            f32 iconY = lineY - 17.0f + (gzMenuLayout::LINE_SPACING - ICON_SIZE) / 2.0f;
            gzSetup2DContext();
            icon->setAlpha(255);
            icon->draw(optionX, iconY, ICON_SIZE, ICON_SIZE, false, false, false);
        }

        if (isSelected && gzInfo_isCursorTypeTP() && gzInfo_getTPCursor() != NULL) {
            line->mText->updateBounds();
            f32 cursorX = lineX + (line->mText->getWidth() / 2.0f) + gzMenuLayout::TP_CURSOR_X_OFFSET;
            f32 cursorY = lineY + (line->mText->getHeight() / 2.0f) + gzMenuLayout::TP_CURSOR_Y_OFFSET;
            gzInfo_getTPCursor()->setPos(cursorX, cursorY, (J2DPane*)line->mText, false);
            gzSetup2DContext();
            gzInfo_getTPCursor()->draw();
        }
    }

    drawDescription((l_cursor->y < currentLineNum) ? currentLines[l_cursor->y]->m_description : NULL);
}

gzTabInfo_s gzSceneMenu_c::getTabInfo() {
    gzTabInfo_s info;
    info.hasTabs = true;
    info.currentTab = mCurrentTab;
    info.numTabs = TAB_MAX_e;

    // Calculate positions and widths based on text content
    static const f32 TAB_PADDING = 5.0f;
    f32 tabBaseX = mXPos;
    info.tabX[0] = tabBaseX;
    for (int i = 0; i < TAB_MAX_e; i++) {
        mpTabHeaders[i]->updateBounds();
        info.tabWidth[i] = mpTabHeaders[i]->mBounds.f.x;
        if (i < TAB_MAX_e - 1) {
            info.tabX[i + 1] = info.tabX[i] + info.tabWidth[i] + TAB_PADDING;
        }
    }

    return info;
}
