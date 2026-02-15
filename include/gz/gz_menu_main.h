#ifndef GZ_MENU_MAIN_H
#define GZ_MENU_MAIN_H

#include "gz/gz_menu.h"
#include "gz/gz_textbox.h"
#include "JSystem/J2DGraph/J2DAnimation.h"

class gzMainMenu_c : public gzMenu_c {
public:
    enum gzMainMenu_Menus_e {
        MENU_ACTORS,
        MENU_CHEATS,
        MENU_FLAGS,
        MENU_FRAMEWORK,
        MENU_HEAPS,
        MENU_INVENTORY,
        MENU_MEMORY,
        MENU_PRACTICE,
        MENU_SCENE,
        MENU_SETTINGS,
        MENU_TOOLS,
        MENU_WARPING,

        MENU_MAX
    };

    gzMainMenu_c();
    ~gzMainMenu_c();
    gzMenu_c* getMenu(int idx) { return mpMenus[idx]; }
    bool isTransitioning() const { return mTransitioning; }
    bool isTransitionForward() const { return mTransitionForward; }
    u32 getTransitionStart() const { return mTransitionStart; }
    f32 getTransitionDuration() const { return mTransitionDuration; }
    void startForwardTransition();
    void startReverseTransition();
    void setDefaultMenuXPos();
    virtual void _delete();
    virtual void execute();
    virtual void draw();
    void setMainVisibleX(f32 x) { mMainVisibleX = x; }
    void setMainHiddenX(f32 x) { mMainHiddenX = x; }
    void setSubVisibleX(f32 x) { mSubVisibleX = x; }
    void setSubHiddenX(f32 x) { mSubHiddenX = x; }
    f32 getSubVisibleX() const { return mSubVisibleX; }
    f32 getSubHiddenX() const { return mSubHiddenX; }

    static const int LINE_NUM = MENU_MAX;
    static const int ICON_SIZE = 18;
    static const int ICON_PADDING = 2;

private:
    gzLine* mpLines[LINE_NUM];
    gzMenu_c* mpMenus[LINE_NUM];
    dMeterHaihai_c* mpMeterHaihai;
    gzMenu_c* mpTransitioningMenu;
    bool mTransitioning;
    bool mTransitionForward;
    u32 mTransitionStart;
    f32 mTransitionDuration;
    f32 mMainStartX;
    f32 mMainEndX;
    f32 mSubStartX;
    f32 mSubEndX;
    f32 mMainVisibleX;
    f32 mMainHiddenX;
    f32 mSubVisibleX;
    f32 mSubHiddenX;
};

inline void gzChangeMenu(gzMenu_c* i_menu) {
    if (g_gzInfo.mpCurrentMenu != NULL) {
        g_gzInfo.mpCurrentMenu->onUnhighlight();
    }
    g_gzInfo.mpCurrentMenu = i_menu;
    if (i_menu != NULL) {
        i_menu->onHighlight();
    }
}

inline f32 calcSlidePosition(u32 currentFrame, u32 startFrame, f32 startPos, f32 endPos, f32 duration) {
    f32 age = (f32)(currentFrame - startFrame);

    if (age >= duration) {
        return endPos;
    }

    f32 time0 = 0.0f;
    f32 value0 = startPos;
    f32 tan_out0 = 0.0f;
    f32 time1 = duration;
    f32 value1 = endPos;
    f32 tan_in1 = 0.0f;

    return J2DHermiteInterpolation(age, &time0, &value0, &tan_out0, &time1, &value1, &tan_in1);
}

#endif // GZ_MENU_MAIN_H
