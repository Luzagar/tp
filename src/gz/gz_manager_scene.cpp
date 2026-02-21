#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz.h"
#include "d/d_stage.h"
#include "m_Do/m_Do_audio.h"

void gzSceneMng_c::execute() {
    if (gzInfo_isScene_FreezeTime()) {
        dComIfGp_roomControl_setTimePass(FALSE);
        mInit_FreezeTime = true;
    } else if (mInit_FreezeTime) {
        roomRead_class* room = dComIfGp_getStageRoom();
        int roomNo = dComIfGp_roomControl_getStayNo();
        if (room != NULL && room->num > roomNo) {
            dComIfGp_roomControl_setTimePass(dStage_roomRead_dt_c_GetTimePass(*room->m_entries[roomNo]));
        }

        mInit_FreezeTime = false;
    }

    if (gzInfo_isScene_MuteBGM()) {
        Z2GetSeqMgr()->bgmAllMute(0, 0.0f);
        mInit_MuteBGM = true;
    } else if (mInit_MuteBGM) {
        Z2GetSeqMgr()->bgmAllUnMute(0);
        mInit_MuteBGM = false;
    }

    if (gzInfo_isScene_MuteSFX()) {
        Z2GetSeMgr()->seMoveVolumeAll(0.0f, 0);
        mInit_MuteSFX = true;
    } else if (mInit_MuteSFX) {
        Z2GetSeMgr()->seMoveVolumeAll(1.0f, 0);
        mInit_MuteSFX = false;
    }
}
