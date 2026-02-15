#ifndef GZ_MENU_H
#define GZ_MENU_H

#include "d/d_drawlist.h"
#include "d/d_meter_haihai.h"
#include "gz/gz_textbox.h"

// Common layout constants for menu drawing
namespace gzMenuLayout {
    const f32 Y_ALIGNMENT = 88.0f;
    const f32 LINE_SPACING = 22.0f;
    const f32 OPTIONS_X_OFFSET = 270.0f;
    const f32 HAIHAI_X_OFFSET = 0.5f;
    const f32 HAIHAI_Y_OFFSET = -7.0f;
    const f32 HAIHAI_EXTRA_SPACING = 30.0f;
    const f32 HAIHAI_SCALE_FACTOR = 0.04f;
    const f32 TAB_HEADER_Y_OFFSET = 58.0f;
    const f32 TP_CURSOR_X_OFFSET = -3.0f;
    const f32 TP_CURSOR_Y_OFFSET = -17.0f;
    const s32 VISIBLE_LINES = 15;
}

struct gzBoolOption_s {
    const char* name;
    const char* desc;
    bool (*is)();
    void (*on)();
    void (*off)();
};

struct gzIntOption_s {
    const char* name;
    const char* desc;
    bool (*is)(int);
    void (*on)(int);
    void (*off)(int);
};

struct ScissorState {
    u32 left, top, width, height;
};

enum gzButtonType_e {
    GZ_BTN_A,
    GZ_BTN_B,
    GZ_BTN_X,
    GZ_BTN_Y,
    GZ_BTN_Z,
    GZ_BTN_L,
    GZ_BTN_R
};

struct gzButtonHint_s {
    gzButtonType_e button;
    const char* text;
};

struct gzButtonHints_s {
    gzButtonHint_s hints[7];
    int count;
};

static const int GZ_MAX_TABS = 8;

struct gzTabInfo_s {
    bool hasTabs;
    int currentTab;
    int numTabs;
    f32 tabX[GZ_MAX_TABS];
    f32 tabWidth[GZ_MAX_TABS];
};

class gzMenu_c : public dDlst_base_c {
public:
    enum gzMenu_Haihai_e {
        ARROW_LEFT = 1,
        ARROW_DOWN = 2,
        ARROW_RIGHT = 4,
        ARROW_UP = 8
    };

    gzMenu_c();
    virtual ~gzMenu_c();

    virtual void create() {}
    virtual void _delete() {}
    virtual void execute();
    virtual void draw() {}
    virtual f32 getXPos() { return mXPos; }
    virtual void setXPos(f32 x) { mXPos = x; }
    virtual u8 getHaihaiFlags(int idx) { return ARROW_LEFT | ARROW_RIGHT; }
    virtual gzButtonHints_s getButtonHints();
    virtual gzTabInfo_s getTabInfo() { gzTabInfo_s info; info.hasTabs = false; return info; }

    virtual void onEnterMenu();
    virtual void onExitMenu();
    virtual void onHighlight() {}
    virtual void onUnhighlight() {}
    virtual void onAButtonSound();
    f32 getCurrentOptionsXOffset();
    bool isEntered() { return mIsEntered; }
    void setMenuScissor();
    void restoreScissor(const ScissorState& saved);
    ScissorState saveScissor();

protected:
    bool checkInputWait();
    bool handleBackButton(int mainMenuIndex);
    void handleNavigation(int maxLines);
    void handleTabSwitch(int& currentTab, int maxTabs);
    void finishExecute(int maxLines);

    // Draw helpers
    void updateScrolling(s32 maxLines);
    void drawDescription(const char* desc);
    void drawTPCursor();
    void drawTPCursorForBox(gzTextBox* box, f32 x, f32 y);
    void updateLineBounds(gzLine** lines, int numLines);

    void drawTabHeaders(gzTextBox** headers, const f32* xPositions, int numTabs,
                        int currentTab, f32 yPosition, u32 activeColor);
    void drawLines(gzTextBox** lines, gzTextBox** lineOptions, u8 haihaiFlags, s32 numLines);
    void drawLines(gzLine** lines, s32 numLines, u8 haihai_flags, s32 topLine, s32 visibleLines);
    void drawLineWithOption(gzTextBox* line, gzTextBox* option, f32 lineX, f32 optionX, f32 lineY,
                            bool isSelected, u32 selectedColor, bool showHaihai, u8 haihaiFlags,
                            f32 haihaiX, f32 haihaiY, f32 haihaiWidth);
    void drawLinesWithHaihai(gzLine** lines, s32 numLines, s32 topLine, s32 visibleLines);

    f32 mXPos;
    f32 mOptionsXOffset;
    f32 mLineYStart;
    bool mIsEntered;
    dMeterHaihai_c* mpHaihai;
};

#endif // GZ_MENU_H
