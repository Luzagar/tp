#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_menu_main.h"
#include "d/d_select_cursor.h"
#include "gz/gz_menu_cheats.h"
#include "gz/gz_menu_flags.h"
#include "gz/gz_menu_framework.h"
#include "gz/gz_menu_heaps.h"
#include "gz/gz_menu_inventory.h"
#include "gz/gz_menu_memory.h"
#include "gz/gz_menu_practice.h"
#include "gz/gz_menu_scene.h"
#include "gz/gz_menu_settings.h"
#include "gz/gz_menu_tools.h"
#include "gz/gz_menu_warp.h"
#include "gz/gz_utility_draw.h"
#include "SSystem/SComponent/c_counter.h"

static const f32 MAIN_LINE_SPACING = 30.0f;
static const f32 MAIN_X_OFFSET = 8.0f;
static const f32 MAIN_Y_OFFSET = 10.0f;

void gzMainMenu_c::startForwardTransition() {
    mTransitioning = true;
    mTransitionForward = true;
    mTransitionStart = cCt_getFrameCount();
    mpTransitioningMenu = g_gzInfo.mpCurrentMenu;
    mSubHiddenX = mpTransitioningMenu->getXPos();
    mMainStartX = mMainVisibleX;
    mMainEndX = mMainHiddenX;
    mSubStartX = mSubHiddenX;
    mSubEndX = mSubVisibleX;
    g_gzInfo.mSeparatorXPos = g_gzInfo.mSeparatorVisibleX;
}

void gzMainMenu_c::startReverseTransition() {
    mTransitioning = true;
    mTransitionForward = false;
    mTransitionStart = cCt_getFrameCount();
    mpTransitioningMenu = g_gzInfo.mpCurrentMenu;
    mMainStartX = mMainHiddenX;
    mMainEndX = mMainVisibleX;
    mSubStartX = mSubVisibleX;
    mSubEndX = mSubHiddenX;
    g_gzInfo.mSeparatorXPos = g_gzInfo.mSeparatorHiddenX;
    if (mpTransitioningMenu != NULL) {
        mpTransitioningMenu->onExitMenu();
    }
    g_gzInfo.mInputWaitTimer = 2;
}

gzMainMenu_c::gzMainMenu_c() {
    OSReport("creating gzMainMenu_c\n");

    mpMenus[MENU_ACTORS] = NULL;
    mpMenus[MENU_CHEATS] = new (gzHeap(GZ_GROUP_MENU), 4) gzCheatsMenu_c();
    mpMenus[MENU_FLAGS] = new (gzHeap(GZ_GROUP_MENU), 4) gzFlagsMenu_c();
    mpMenus[MENU_FRAMEWORK] = new (gzHeap(GZ_GROUP_MENU), 4) gzFrameworkMenu_c();
    mpMenus[MENU_HEAPS] = new (gzHeap(GZ_GROUP_MENU), 4) gzHeapsMenu_c();
    mpMenus[MENU_INVENTORY] = new (gzHeap(GZ_GROUP_MENU), 4) gzInventoryMenu_c();
    // mpMenus[MENU_INVENTORY] = NULL;
    mpMenus[MENU_MEMORY] = new (gzHeap(GZ_GROUP_MENU), 4) gzMemoryMenu_c();
    mpMenus[MENU_PRACTICE] = new (gzHeap(GZ_GROUP_MENU), 4) gzPracticeMenu_c();
    mpMenus[MENU_SCENE] = new (gzHeap(GZ_GROUP_MENU), 4) gzSceneMenu_c();
    mpMenus[MENU_SETTINGS] = new (gzHeap(GZ_GROUP_MENU), 4) gzSettingsMenu_c();
    mpMenus[MENU_TOOLS] = new (gzHeap(GZ_GROUP_MENU), 4) gzToolsMenu_c();
    mpMenus[MENU_WARPING] = new (gzHeap(GZ_GROUP_MENU), 4) gzWarpMenu_c();

    mpLines[MENU_ACTORS] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("actors", "create, read, update or delete actors in the current scene");
    mpLines[MENU_CHEATS] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("cheats", "toggle cheats");
    mpLines[MENU_FLAGS] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("flags", "toggle in-game flags");
    mpLines[MENU_FRAMEWORK] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("framework", "view and edit running processes");
    mpLines[MENU_HEAPS] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("heaps", "see how cooked we are");
    mpLines[MENU_INVENTORY] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("inventory", "set items and equipment");
    mpLines[MENU_MEMORY] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("memory", "view and edit memory");
    mpLines[MENU_PRACTICE] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("practice", "load practice files");
    mpLines[MENU_SCENE] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("scene", "adjust current scene settings");
    mpLines[MENU_SETTINGS] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("settings", "configure tpgz settings");
    mpLines[MENU_TOOLS] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("tools", "use various tools for practice and testing");
    mpLines[MENU_WARPING] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("warping", "warp to any area");

    mpMeterHaihai = new (gzHeap(GZ_GROUP_GRAPHICS), 4) dMeterHaihai_c(3);

    mpTransitioningMenu = NULL;
    mTransitioning = false;
    mTransitionForward = true;
    mTransitionStart = 0;
    mTransitionDuration = 5.0f;

    mXPos = mMainVisibleX = g_gzInfo.mBackgroundXPos + 15.0f;
    mSubVisibleX = g_gzInfo.mBackgroundXPos + 20.0f;
    mMainHiddenX = mXPos - 160.0f;
    mSubHiddenX = mXPos + 180.0f;
}

gzMainMenu_c::~gzMainMenu_c() {
    _delete();
}

void gzMainMenu_c::_delete() {
    OSReport("deleting gzMainMenu_c\n");

    for (int i = 0; i < LINE_NUM; i++) {
        delete mpLines[i];
        mpLines[i] = NULL;

        delete mpMenus[i];
        mpMenus[i] = NULL;
    }
}

void gzMainMenu_c::execute() {
    gzCursor* l_cursor = gzInfo_getCursor();

    if (mTransitioning) {
        return;
    }

    if (gzPad::getTrigDown()) {
        l_cursor->y = (l_cursor->y + 1) % LINE_NUM;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
        gzChangeMenu(mpMenus[l_cursor->y]);
    }

    if (gzPad::getTrigUp()) {
        l_cursor->y = (l_cursor->y - 1 + LINE_NUM) % LINE_NUM;
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
        gzChangeMenu(mpMenus[l_cursor->y]);
    }

    if (gzPad::getTrigB()) {
        g_gzInfo.mDisplay = false;
        return;
    }

    if (gzPad::getTrigA()) {
        if (g_gzInfo.mpCurrentMenu != NULL) {
            startForwardTransition();
            l_cursor->x++;
            l_cursor->y = 0;
            g_gzInfo.mInputWaitTimer = 2;
            gzInfo_seStart(Z2SE_SY_EXP_WIN_OPEN);
        }
    }
}

void gzMainMenu_c::draw() {
    gzCursor* l_cursor = gzInfo_getCursor();

    static const f32 DESCRIPTION_X = 0.0f;

    f32 y_alignment = g_gzInfo.mBackgroundYPos + gzMenuLayout::Y_ALIGNMENT + MAIN_Y_OFFSET;
    u32 cursor_color = gzInfo_getCursorColor();

    if (mTransitioning) {
        u32 currentFrame = cCt_getFrameCount();
        f32 age = (f32)(currentFrame - mTransitionStart);

        if (age >= mTransitionDuration) {
            mTransitioning = false;
            mXPos = mMainEndX;
            if (mpTransitioningMenu != NULL) {
                mpTransitioningMenu->setXPos(mSubEndX);
                if (mTransitionForward) {
                    mpTransitioningMenu->onEnterMenu();
                }
            }
            mpTransitioningMenu = NULL;
        } else {
            mXPos = calcSlidePosition(currentFrame, mTransitionStart, mMainStartX, mMainEndX, mTransitionDuration);

            if (mpTransitioningMenu != NULL)
                mpTransitioningMenu->setXPos(calcSlidePosition(currentFrame, mTransitionStart, mSubStartX, mSubEndX, mTransitionDuration));
        }

        f32 x_offset = mXPos + MAIN_X_OFFSET;
        ResTIMG* atlas = gzInfo_getIconAtlas();
        for (int i = 0; i < LINE_NUM; i++) {
            if (mpLines[i] != NULL && mXPos >= g_gzInfo.mBackgroundXPos) {
                f32 y_pos = y_alignment + ((i - 1) * MAIN_LINE_SPACING);
                bool isSelected = (l_cursor->y == i && gzInfo_isMainMenuVisible());
                u32 color = (isSelected && gzInfo_isCursorTypeClassic()) ? gzInfo_getTextColor() : COLOR_WHITE;
                if (atlas != NULL) {
                    GXColor iconColor = {(u8)((color >> 24) & 0xFF), (u8)((color >> 16) & 0xFF),
                                         (u8)((color >> 8) & 0xFF), 0xFF};
                    gzDrawAtlasIcon(atlas, i, 24, LINE_NUM, x_offset, y_pos - 17.0f,
                                    (f32)ICON_SIZE, (f32)ICON_SIZE, iconColor);
                }
                mpLines[i]->draw(x_offset + ICON_SIZE + ICON_PADDING, y_pos, color);
            }
        }
    } else {
        f32 x_offset = mXPos + MAIN_X_OFFSET;
        ResTIMG* atlas = gzInfo_getIconAtlas();
        for (int i = 0; i < LINE_NUM; i++) {
            if (mpLines[i] != NULL) {
                f32 y_pos = y_alignment + ((i - 1) * MAIN_LINE_SPACING);
                bool isSelected = (l_cursor->y == i && gzInfo_isMainMenuVisible());
                u32 color = (isSelected && gzInfo_isCursorTypeClassic()) ? gzInfo_getTextColor() : COLOR_WHITE;
                if (atlas != NULL) {
                    GXColor iconColor = {(u8)((color >> 24) & 0xFF), (u8)((color >> 16) & 0xFF),
                                         (u8)((color >> 8) & 0xFF), 0xFF};
                    gzDrawAtlasIcon(atlas, i, 24, LINE_NUM, x_offset, y_pos - 17.0f,
                                    (f32)ICON_SIZE, (f32)ICON_SIZE, iconColor);
                }
                mpLines[i]->draw(x_offset + ICON_SIZE + ICON_PADDING, y_pos, color);
            }
        }
    }

    if (gzInfo_isMainMenuVisible()) {
        if (mpLines[l_cursor->y] && mpLines[l_cursor->y]->m_description[0] != 0) {
            gzInfo_getMenuDescription()->setString(mpLines[l_cursor->y]->m_description);
        } else {
            gzInfo_getMenuDescription()->setString("");
        }
    }

    if (gzInfo_isCursorTypeTP() && gzInfo_getTPCursor() != NULL && !mTransitioning && gzInfo_isMainMenuVisible()) {
        // Update bounds for selected line and set cursor position
        if (mpLines[l_cursor->y] != NULL) {
            mpLines[l_cursor->y]->mText->updateBounds();
            f32 y_pos = y_alignment + ((l_cursor->y - 1) * MAIN_LINE_SPACING);

            // Calculate total width including icon + padding + text
            f32 textWidth = mpLines[l_cursor->y]->mText->getWidth();
            f32 totalWidth = ICON_SIZE + ICON_PADDING + textWidth;
            // Scale cursor to fit icon + text (base cursor sizes to text pane)
            f32 scaleFactor = totalWidth / textWidth;
            gzInfo_getTPCursor()->setScale(scaleFactor);
            // setPos expects center position - center over icon + text combined
            f32 cursorX = mXPos + MAIN_X_OFFSET + (totalWidth / 2.0f) + gzMenuLayout::TP_CURSOR_X_OFFSET;
            f32 cursorY = y_pos + (mpLines[l_cursor->y]->mText->getHeight() / 2.0f) + gzMenuLayout::TP_CURSOR_Y_OFFSET;
            gzInfo_getTPCursor()->setPos(cursorX, cursorY, (J2DPane*)mpLines[l_cursor->y]->mText, false);
        }
        gzSetup2DContext();
        gzInfo_getTPCursor()->draw();
        // Reset scale for other menus
        gzInfo_getTPCursor()->setScale(1.0f);
    }
}
