#ifndef GZ_SETUP_WIZARD_H
#define GZ_SETUP_WIZARD_H

#include "gz/gz.h"

class gzTextBox;

class gzSetupWizard_c {
public:
    enum WizardStep_e {
        STEP_WELCOME,
        STEP_THEME,
        STEP_BOOT_TARGET,
        STEP_MENU_PAUSES,
        STEP_DISPLAY_MODE,
        STEP_MENU_SFX,
        STEP_COMPLETE,
        STEP_DONE,
    };

    gzSetupWizard_c();
    ~gzSetupWizard_c();

    void execute();
    void draw();
    bool isComplete() const { return mStep == STEP_DONE; }

    bool mBootToMenu;
    bool mMenuPauses;
    bool mDisplayMode;
    bool mMenuSfx;
    int mThemeIndex;

private:
    void applySettings();
    void drawBinaryOptions(const char* text0, const char* text1, f32 spread,
                           f32 y, u32 selColor);

    WizardStep_e mStep;
    int mSelection;

    gzTextBox* mpTitle;
    gzTextBox* mpQuestion;
    gzTextBox* mpOption0;
    gzTextBox* mpOption1;
    gzTextBox* mpOption2;
    gzTextBox* mpHint;
};

#endif // GZ_SETUP_WIZARD_H
