#ifndef GZ_MENU_SETTINGS_H
#define GZ_MENU_SETTINGS_H

#include "gz/gz_menu_credits.h"
#include "gz/gz_utility_confirm.h"

class gzSettingsMenu_c : public gzMenu_c {
public:
    enum gzSettingsMenu_Settings_e {
        // Options (alphabetical)
        SETTING_BOOT_TO_MENU,
        SETTING_CURSOR_TYPE,
        SETTING_DISPLAY_MODE,
        SETTING_DROP_SHADOW,
        SETTING_MENU_PAUSES_GAME,
        SETTING_MENU_SFX,
        SETTING_RELOAD_TYPE,
        SETTING_STATE_STREAMING,
        SETTING_SWAP_EQUIPS,
        SETTING_THEME,
        // Actions
        SETTING_COMMAND_COMBOS,
        SETTING_MENU_POSITIONS,
        SETTING_GDB_SERVER,
        SETTING_SAVE,
        SETTING_LOAD,
        SETTING_DELETE,
        SETTING_RETURN_TO_LOADER,

        SETTING_MAX
    };

    gzSettingsMenu_c();
    ~gzSettingsMenu_c();
    void updateDynamicLines();

    virtual void _delete();
    virtual void execute();
    virtual void draw();

    char* getCursorTypeText() {
        switch (gzInfo_getCursorType()) {
        case g_gzInfo.CURSOR_CLASSIC:
            return "classic";
        case g_gzInfo.CURSOR_TP:
            return "tp";
        case g_gzInfo.CURSOR_BOTH:
            return "both";
        default:
            return "unknown";
        }
    }

    const char* getThemeText() { return gzGetThemeColorName(gzInfo_getTextColor()); }

    const char* getReloadTypeText() { return gzInfo_getReloadType() ? "load area" : "load file"; }
    const char* getDropShadowsText() { return gzInfo_isDropShadows() ? "enabled" : "disabled"; }
    const char* getStateStreamingText() { return gzInfo_isOnline_StateStreaming() ? "enabled" : "disabled"; }
    const char* getSwapEquipsText() { return gzInfo_isSwapEquips() ? "yes" : "no"; }
    const char* getDisplayModeText() { return gzInfo_getDisplayMode() ? "progressive" : "interlaced"; }
    const char* getMenuPausesGameText() { return gzInfo_isMenuPausesGame() ? "yes" : "no"; }
    const char* getBootToMenuText() { return gzInfo_isBootToMenu() ? "yes" : "no"; }
    const char* getMenuSfxText() { return gzInfo_isMenuSfx() ? "enabled" : "disabled"; }

    static const int LINE_NUM = SETTING_MAX;

    u8 getHaihaiFlags(int i);

    static int deleteConfirmCb(gzConfirm_c* i_confirm, void* i_data);
    static int deleteReturnCb(gzConfirm_c* i_confirm, void* i_data);
    static int returnToLoaderConfirmCb(gzConfirm_c* i_confirm, void* i_data);
    static int returnToLoaderReturnCb(gzConfirm_c* i_confirm, void* i_data);

    gzConfirm_c* mpConfirm;

private:
    // Options (alphabetical)
    gzBoolOptionLine* mpBootToMenu;
    gzListOptionLine* mpCursorType;
    gzBoolOptionLine* mpDisplayMode;
    gzBoolOptionLine* mpDropShadows;
    gzBoolOptionLine* mpMenuPausesGame;
    gzBoolOptionLine* mpMenuSfx;
    gzBoolOptionLine* mpReloadType;
    gzBoolOptionLine* mpStateStreaming;
    gzBoolOptionLine* mpSwapEquips;
    gzListOptionLine* mpTheme;
    // Actions
    gzLine* mpCommandCombos;
    gzLine* mpMenuPositions;
    gzLine* mpGdbServer;
    gzLine* mpSave;
    gzLine* mpLoad;
    gzLine* mpDelete;
    gzLine* mpReturnToLoader;
    int mLineCount;
    gzLine* mpLines[LINE_NUM];
};

#endif
