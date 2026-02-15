#ifndef GZ_MANAGER_SCENE_H
#define GZ_MANAGER_SCENE_H

#include <dolphin/types.h>

class gzSceneMng_c {
public:
    void execute();

private:
    bool mInit_FreezeTime;
    bool mInit_MuteBGM;
    bool mInit_MuteSFX;
};

#endif
