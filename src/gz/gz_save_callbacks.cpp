#include "gz/gz_manager_practice.h"
#include "gz/gz_menu_practice.h"

#include "c/c_damagereaction.h"
#include "d/actor/d_a_alink.h"
#include "d/actor/d_a_obj_swspinner.h"
#include "d/actor/d_a_obj_lv4RailWall.h"
#include "d/actor/d_a_e_zs.h"
#include "d/actor/d_a_b_zant.h"
#include "d/actor/d_a_b_ds.h"

static void SaveCb_SetEarlyBossFlag() {
    cDmr_SkipInfo = 1;
}

static void SaveCb_SetCoroTD() {
    dComIfGs_onTmpBit(0x0002);
}

static void SaveCb_SpawnOnHorse() {
    g_dComIfG_gameInfo.info.mRestart.mLastMode = 1;
}

static void SaveCb_OrdonGateClip() {
    fopAc_ac_c* rock = fopAcM_searchFromName("stoneB", 0xFFFFFFFF, 0x00FF6511);
    if (rock != NULL) {
        rock->current.pos = cXyz(400.0f, 307.8f, -11365.f);
        rock->shape_angle.y = 0x16F8;
    }
}

static void SaveCb_SetupHugo() {
    fopAc_ac_c* hugo = fopAcM_SearchByName(fpcNm_E_RD_e);
    if (hugo != NULL) {
        hugo->current.pos = cXyz(-289.9785, 401.5400, -18533.078);
        hugo->shape_angle.y = 0x16F8;
    }
}

static void SaveCb_ForestBiT() {
    daAlink_c* player = daAlink_getAlinkActorClass();
    if (player != NULL) {
        player->onNoResetFlg2(daPy_py_c::FLG2_UNK_1); // lantern out
        player->mEquipItem = 0x102;
    }
}

static void SaveCb_KargorokOoB() {
    dComIfGs_setRestartLastMode(10);
    dComIfGs_setTransformStatus(TF_STATUS_HUMAN);
}

static void SaveCb_WaterfallSidehop() {
    dComIfGs_getSaveInfo()->getRestart().mLastSpeedF = 10.0f;
}

static void SaveCb_PlummOoB() {
    dComIfGs_setRestartLastMode(10);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(4);
    cDmr_SkipInfo = 1;
}

static void SaveCb_EmptyLakeHylia() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(4);
    cDmr_SkipInfo = 1;
}

static void SaveCb_Morpheel() {
    daAlink_c* player = daAlink_getAlinkActorClass();
    if (player != NULL) {
        player->mEquipItem = dItemNo_HOOKSHOT_e;
        player->onNoResetFlg0(daPy_py_c::FLG0_EQUIP_HVY_BOOTS);
    }
}

static void SaveCb_StallordInit() {
    fopAc_ac_c* stallord = fopAcM_SearchByName(fpcNm_B_DS_e);
    if (stallord != NULL) {
        dComIfGs_onZoneSwitch(5, fopAcM_GetRoomNo(stallord)); // intro cs off
    }

    cDmr_SkipInfo = 1;
}

static void* sub_findJosephActor(void* i_actor, void*) {
    if (fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_E_ZS_e) {
        return i_actor;
    }

    return NULL;
}

static void SaveCb_StallordSkipCAD() {
    daE_ZS_c* joseph = (daE_ZS_c*)fopAcM_Search(sub_findJosephActor, NULL);
    if (joseph != NULL) {
        joseph->mAction = 1;
        joseph->mMode = 0;
        joseph->field_0x65c = 0;
        joseph->field_0x673 = 1;
        joseph->mCyl.OnTgSetBit();
        joseph->mCyl.OnCoSetBit();
        fopAcM_OnStatus(joseph, fopAcStts_UNK_0x200000_e);
    }
}

static void SaveCb_StallordSkipJoseph() {
    dComIfGs_setSelectItemIndex(SELECT_ITEM_X, SLOT_0); // rang on x

    daE_ZS_c* joseph = (daE_ZS_c*)fopAcM_Search(sub_findJosephActor, NULL);
    if (joseph != NULL) {
        joseph->mAction = 1;
        joseph->mMode = 0;
        joseph->field_0x65c = 0;
        joseph->field_0x673 = 1;
        joseph->mCyl.OnTgSetBit();
        joseph->mCyl.OnCoSetBit();
        fopAcM_OnStatus(joseph, fopAcStts_UNK_0x200000_e);

        joseph->current.pos.set(301.9f, 1800.0f, -4966.0f);
    }
}

static void SaveCb_StallordPhase2() {
    // TODO: temp solution. realistically, the best option would be to modify the actor code
    // to handle custom situations rather than trying to hook onto the actor.
    // Probably want something similar to the debug "Register" system that can be used to
    // trigger special actions when the variable is set by a callback in the stageInit phase
    daB_DS_c* stallord = (daB_DS_c*)fopAcM_SearchByName(fpcNm_B_DS_e);
    if (stallord != NULL) {
        stallord->mAction =  daB_DS_c::ACT_DAMAGE;
        stallord->mMode = 100;
    }

    /* if (stallord != NULL) {
        // create the phase 2 version of stallord
        fopAcM_create(fpcNm_B_DS_e, fopAcM_GetParam(stallord) | 2, &stallord->current.pos,
                      fopAcM_GetRoomNo(stallord), NULL, NULL, -1);
        fopAcM_delete(stallord);  // delete phase 1 stallord
    }
    
    daObjSwSpinner_c* spinnersw = (daObjSwSpinner_c*)fopAcM_SearchByName(fpcNm_Obj_SwSpinner_e);
    if (spinnersw != NULL) {
        spinnersw->mRotSpeedY = 3000;  // set arena spinner switch to max speed
    }

    daObjLv4Wall_c* rwall = (daObjLv4Wall_c*)fopAcM_SearchByName(fpcNm_Obj_Lv4RailWall_e);
    if (rwall != NULL) {
        rwall->mRotCounter = 101;  // set spinner switch speed counter to threshold
        rwall->mHeight = 3370.0f;  // set arena height to max
    } */
}

static void SaveCb_CityFanTower() {
    dComIfGs_offSaveDunSwitch(18); // bottom sw
    dComIfGs_offSaveDunSwitch(19); // top sw
}

static void SaveCb_Argorok() {
    fopAc_ac_c* argorok = fopAcM_SearchByName(fpcNm_B_DR_e);
    if (argorok != NULL) {
        dComIfGs_onZoneSwitch(20, fopAcM_GetRoomNo(argorok));
    }

    cDmr_SkipInfo = 1;
}

static void SaveCb_Palace1() {
    dComIfGs_resetDan();
}

static void SaveCb_ZantFinal() {
    daB_ZANT_c* zant = (daB_ZANT_c*)fopAcM_SearchByName(fpcNm_B_ZANT_e);
    if (zant != NULL) {
        zant->mAction = daB_ZANT_c::ACT_ROOM_CHANGE;
        zant->mFightPhase = daB_ZANT_c::PHASE_YO;
        zant->mMode = 0;
    }
}

static void SaveCb_BeastGanon() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(1);
}

static void SaveCb_Goats1() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(5);
}

static void SaveCb_KB2Skip() {
    g_dComIfG_gameInfo.play.mNextStage.setLayer(3);
}

static void SaveCb_Escort() {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(13);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(98);
    g_dComIfG_gameInfo.play.mNextStage.setLayer(2);
}

static void SaveCb_GiveEscortKeys() {
    dComIfGs_setKeyNum(2);  // give 2 keys for field gates
}

static void SaveCb_EldinCollection() {
    SaveCb_SpawnOnHorse();
    g_dComIfG_gameInfo.info.mRestart.mLastSpeedF = 42.0f;
}

static void SaveCb_Dangoro() {
    fopAc_ac_c* dangoro = fopAcM_SearchByName(fpcNm_E_GOB_e);
    if (dangoro != NULL) {
        dComIfGs_onZoneSwitch(21, fopAcM_GetRoomNo(dangoro)); // intro cs off
    }
}

static void SaveCb_SPRBossKey() {
    g_dComIfG_gameInfo.play.mNextStage.setRoomNo(11);
    g_dComIfG_gameInfo.play.mNextStage.setPoint(0);
}

static void SaveCb_ToTEarlyHP() {
    dComIfGs_onSwitch(224, 4);  // gate moved to correct pos
}

static void SaveCb_CaveOfOrdeals() {
    dComIfGs_resetDan();
}

static void SaveCb_GorgeVoidInit() {
    g_dComIfG_gameInfo.info.getMemory().getBit().onSwitch(0);
    dComIfGs_putSave(g_dComIfG_gameInfo.info.getDan().mStageNo);
    dComIfGs_setTransformStatus(TF_STATUS_WOLF);

    g_dComIfG_gameInfo.play.setNextStage("F_SP121", 3, 2, 0xE, 13, 0);
    g_dComIfG_gameInfo.info.getRestart().setLastSceneInfo(0.0f, 0x28000000, 0);
    g_dComIfG_gameInfo.info.getRestart().setStartPoint(2);

    cXyz pos(-11856.857f, -5700.0f, 56661.5f);
    g_dComIfG_gameInfo.info.getRestart().setRoom(pos, 24169, 3);

    dComIfGs_setLife(12);

    cDmr_SkipInfo = 1;
}

static void SaveCb_GorgeVoid() {
    dComIfGs_onSwitch(21, 3); // shadow beasts dead
}

const gzSaveLoaderMng_c::saveCallbacks_s gzPracticeMenu_c::mAnypSaveCallbacks[] = {
    {0, NULL, SaveCb_OrdonGateClip},
    {4, NULL, SaveCb_SetupHugo},
    {7, NULL, SaveCb_ForestBiT},
    {8, SaveCb_SetEarlyBossFlag, NULL},
    {9, SaveCb_GorgeVoidInit, SaveCb_GorgeVoid},
    {10, SaveCb_SetEarlyBossFlag, NULL},
    {11, SaveCb_SetEarlyBossFlag, NULL},
    {13, SaveCb_KargorokOoB, NULL},
    {17, SaveCb_WaterfallSidehop, NULL},
    {19, SaveCb_SetEarlyBossFlag, NULL},
    {20, SaveCb_PlummOoB, NULL},
    {21, SaveCb_EmptyLakeHylia, NULL},
    {22, SaveCb_SetEarlyBossFlag, NULL},
    {23, SaveCb_SetEarlyBossFlag, NULL},
    {26, NULL, SaveCb_Morpheel},
    {33, SaveCb_SetEarlyBossFlag, NULL},
    {40, SaveCb_StallordInit, NULL},
    {41, SaveCb_StallordInit, SaveCb_StallordSkipCAD},
    {42, SaveCb_StallordInit, SaveCb_StallordSkipJoseph},
    {43, SaveCb_StallordInit, SaveCb_StallordSkipJoseph},
    {44, SaveCb_StallordInit, SaveCb_StallordPhase2},
    {50, SaveCb_CityFanTower, NULL},
    {51, SaveCb_Argorok, NULL},
    {52, SaveCb_Palace1, NULL},
    {60, NULL, SaveCb_ZantFinal},
    {64, SaveCb_BeastGanon, NULL},
};

const gzSaveLoaderMng_c::saveCallbacks_s gzPracticeMenu_c::mADSaveCallbacks[] = {
    {3, NULL, SaveCb_SetupHugo},
    {11, SaveCb_SetEarlyBossFlag, NULL},
    {12, SaveCb_SetEarlyBossFlag, NULL},
    {13, SaveCb_SetEarlyBossFlag, NULL},
    {24, NULL, SaveCb_Morpheel},
    {30, SaveCb_StallordInit, NULL},
    {39, SaveCb_Argorok, NULL},
    {40, SaveCb_Palace1, NULL},
};

const gzSaveLoaderMng_c::saveCallbacks_s gzPracticeMenu_c::mHundoSaveCallbacks[] = {
    {0, SaveCb_Goats1, NULL},
    {13, SaveCb_SetEarlyBossFlag, NULL},
    {14, SaveCb_SetEarlyBossFlag, NULL},
    {15, SaveCb_KargorokOoB, NULL},
    {18, SaveCb_SetCoroTD, NULL},
    {20, NULL, SaveCb_Dangoro},
    {22, SaveCb_WaterfallSidehop, NULL},
    {24, SaveCb_KB2Skip, NULL},
    {25, SaveCb_Escort, SaveCb_GiveEscortKeys},
    {26, SaveCb_EldinCollection, NULL},
    {28, NULL, SaveCb_Morpheel},
    {34, SaveCb_PlummOoB, NULL},
    {40, SaveCb_StallordInit, NULL},
    {43, SaveCb_SetEarlyBossFlag, NULL},
    {46, SaveCb_SPRBossKey, NULL},
    {54, NULL, SaveCb_ToTEarlyHP},
    {69, SaveCb_CityFanTower, NULL},
    {70, SaveCb_Argorok, NULL},
    {72, SaveCb_Palace1, NULL},
    {76, SaveCb_CaveOfOrdeals, NULL},
    {77, SaveCb_CaveOfOrdeals, NULL},
    {78, SaveCb_CaveOfOrdeals, NULL},
    {79, SaveCb_CaveOfOrdeals, NULL},
    {80, SaveCb_CaveOfOrdeals, NULL},
};

const gzSaveLoaderMng_c::saveCallbacks_s gzPracticeMenu_c::mNoSQSaveCallbacks[] = {
    {1, NULL, SaveCb_SetupHugo},
    {5, SaveCb_SetEarlyBossFlag, NULL},
    {6, SaveCb_SetEarlyBossFlag, NULL},
    {7, SaveCb_SetEarlyBossFlag, NULL},
    {9, SaveCb_SetEarlyBossFlag, NULL},
    {11, SaveCb_KB2Skip, NULL},
    {12, SaveCb_Escort, SaveCb_GiveEscortKeys},
    {14, SaveCb_SetEarlyBossFlag, NULL},
    {15, SaveCb_SetEarlyBossFlag, NULL},
    {17, NULL, SaveCb_Morpheel},
    {23, SaveCb_StallordInit, NULL},
    {28, SaveCb_Argorok, NULL},
    {29, SaveCb_Palace1, NULL},
};

const gzSaveLoaderMng_c::saveCallbacks_s* gzGetSaveCallbackList(int i_category) {
    switch (i_category) {
    case gzSaveLoaderMng_c::CATEGORY_ANYP_e:
        return gzPracticeMenu_c::mAnypSaveCallbacks;
        break;
    case gzSaveLoaderMng_c::CATEGORY_ALLDUNGEONS_e:
        return gzPracticeMenu_c::mADSaveCallbacks;
        break;
    case gzSaveLoaderMng_c::CATEGORY_HUNDO_e:
        return gzPracticeMenu_c::mHundoSaveCallbacks;
        break;
    case gzSaveLoaderMng_c::CATEGORY_NOSQ_e:
        return gzPracticeMenu_c::mNoSQSaveCallbacks;
        break;
    }

    return NULL;
}

const int gzGetSaveCallbackListSize(int i_category) {
    switch (i_category) {
    case gzSaveLoaderMng_c::CATEGORY_ANYP_e:
        return ARRAY_SIZE(gzPracticeMenu_c::mAnypSaveCallbacks);
        break;
    case gzSaveLoaderMng_c::CATEGORY_ALLDUNGEONS_e:
        return ARRAY_SIZE(gzPracticeMenu_c::mADSaveCallbacks);
        break;
    case gzSaveLoaderMng_c::CATEGORY_HUNDO_e:
        return ARRAY_SIZE(gzPracticeMenu_c::mHundoSaveCallbacks);
        break;
    case gzSaveLoaderMng_c::CATEGORY_NOSQ_e:
        return ARRAY_SIZE(gzPracticeMenu_c::mNoSQSaveCallbacks);
        break;
    }

    return 0;
}
