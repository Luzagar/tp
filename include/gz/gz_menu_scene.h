#ifndef GZ_MENU_SCENE_H
#define GZ_MENU_SCENE_H

#include "gz/gz_menu.h"
#include "gz/gz_textbox.h"

class gzSceneMenu_c : public gzMenu_c {
public:
    enum gzSceneMenuTabs_e {
        TAB_ENV_e,
        TAB_VIEWERS_e,
        TAB_AUDIO_e,

        TAB_MAX_e
    };

    static const int ENV_MAX = 3;
    static const int AUDIO_MAX = 2;

    gzSceneMenu_c();
    ~gzSceneMenu_c();

    virtual void _delete();
    virtual void execute();
    virtual void draw();
    virtual gzTabInfo_s getTabInfo();
    virtual void onHighlight();
    virtual void onUnhighlight();

private:
    int getCurrentLineNum();

private:
    gzTextBox* mpTabHeaders[TAB_MAX_e];
    gzBoolOptionLine* mpEnvLines[ENV_MAX];
    gzBoolOptionLine* mpAudioLines[AUDIO_MAX];

    int mCurrentTab;
};

#endif // GZ_MENU_SCENE_H
