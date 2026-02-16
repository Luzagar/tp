#include "d/dolzel.h" // IWYU pragma: keep

#include "d/d_drawlist.h"
#include "gz/gz.h"
#include "m_Do/m_Do_MemCard.h"
#include "SSystem/SComponent/c_lib.h"
#include "Z2AudioLib/Z2SeqMgr.h"

static const char* getCategoryFolder(gzSaveLoaderMng_c::SaveCategory_e i_category) {
    switch (i_category) {
    case gzSaveLoaderMng_c::CATEGORY_NOSQ_e:
        return "nosq_saves";
    case gzSaveLoaderMng_c::CATEGORY_HUNDO_e:
        return "hundo_saves";
    case gzSaveLoaderMng_c::CATEGORY_ALLDUNGEONS_e:
        return "ad_saves";
    case gzSaveLoaderMng_c::CATEGORY_GLITCHLESS_e:
        return "glitchless_saves";
    case gzSaveLoaderMng_c::CATEGORY_ANYP_e:
    default:
        return "any_saves";
    }
}

static const char* getCategoryMetadataPath(gzSaveLoaderMng_c::SaveCategory_e i_category) {
    switch (i_category) {
    case gzSaveLoaderMng_c::CATEGORY_NOSQ_e:
        return "nosq_saves/nosq";
    case gzSaveLoaderMng_c::CATEGORY_HUNDO_e:
        return "hundo_saves/hundo";
    case gzSaveLoaderMng_c::CATEGORY_ALLDUNGEONS_e:
        return "ad_saves/ad";
    case gzSaveLoaderMng_c::CATEGORY_GLITCHLESS_e:
        return "glitchless_saves/glitchless";
    case gzSaveLoaderMng_c::CATEGORY_ANYP_e:
    default:
        return "any_saves/any";
    }
}

void gzSaveLoaderMng_c::doSaveInject() {
    dComIfGp_offPauseFlag();
    memcpy(&g_dComIfG_gameInfo.info.mSavedata, mDoMemCd_Ctrl_c::sTmpBuf, sizeof(dSv_save_c));
    dComIfGs_getSave(dComIfGs_getSaveInfo()->getDan().mStageNo);

    if (mSaveCallbacks.stageInitCb != NULL) {
        OSReport("running stageInit callback\n");
        mSaveCallbacks.stageInitCb();
    }
}

void gzSaveLoaderMng_c::doSceneReadyCallbacks() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    // make sure this only runs once, since the scene done function runs multiple times
    if (player != NULL && mLoadPhase == PHASE_PLAYER_INIT_e) {
        if (mMode == MODE_MEMFILE_e) {
            player->current.pos = mMemfileExData.player_pos;
        } else {
            if (mSaveMetadata.flags & SETFLAG_POS_e) {
                OS_REPORT("attempting to set position (%f, %f, %f) %d\n", mSaveMetadata.player_pos.x, mSaveMetadata.player_pos.y, mSaveMetadata.player_pos.z, mSaveMetadata.angle);
                player->current.pos = mSaveMetadata.player_pos;
                player->current.angle.y = mSaveMetadata.angle;
            }

            if (mSaveMetadata.flags & SETFLAG_CAM_e) {
                // TODO
            }

            if (mSaveCallbacks.playerInitCb != NULL) {
                OSReport("running playerInit callback\n");
                mSaveCallbacks.playerInitCb();
            }
        }

        end();
    }
}

void gzSaveLoaderMng_c::execute() {
    switch (mLoadPhase) {
    case PHASE_WAIT_e:
        return;
    case PHASE_INIT_e:
        mSaveInjectReady = true;
        wait();
        break;
    case PHASE_STAGE_INIT_e: // TODO: is this phase needed anymore?
        mLoadPhase = PHASE_PLAYER_INIT_e;
        break;
    case PHASE_PLAYER_INIT_e:
        break;
    }
}

void gzSaveLoaderMng_c::loadSave(SaveCategory_e i_category, int i_entryNo, const saveCallbacks_s i_callbackList[], int i_callbackListSize) {
    const int SAVE_READ_SIZE = OSRoundUp32B(sizeof(dSv_save_c));
    mMode = MODE_SAVE_e;

    getSaveMetadata(i_category, i_entryNo, &mSaveMetadata);

    char pathbuf[64];
    snprintf(pathbuf, sizeof(pathbuf), "/gz/%s/%s.bin", getCategoryFolder(i_category), mSaveMetadata.filename);
    gzDVDLoadFile(pathbuf, mDoMemCd_Ctrl_c::sTmpBuf, SAVE_READ_SIZE, 0);

    dSv_save_c* savep = (dSv_save_c*)mDoMemCd_Ctrl_c::sTmpBuf;
    dComIfGp_setNextStage(savep->getPlayer().getPlayerReturnPlace().getName(),
                          savep->getPlayer().getPlayerReturnPlace().getPlayerStatus(),
                          savep->getPlayer().getPlayerReturnPlace().getRoomNo(),
                          -1);

    start();

    if (i_callbackList != NULL) {
        // find and set save "specials"
        for (int i = 0; i < i_callbackListSize; i++) {
            if (i_entryNo == i_callbackList[i].saveIndex) {
                OSReport("found save callbacks, now setting...\n");
                setSaveCallbacks(i_callbackList[i].stageInitCb, i_callbackList[i].playerInitCb);
                break;
            }
        }
    }

    // NOTE: hold-over from original gz save loading code. Inject the "during" callback early
    // so that any location changes and such are set before stage loading begins.
    // May want a cleaner solution later, but just want something that works for now
    if (mSaveCallbacks.stageInitCb != NULL) {
        mSaveCallbacks.stageInitCb();
    }

    // helps prevent bugs that happen when a save 
    // is loaded right around the time a void happens
    // we need a better solution here probably
    dComIfGp_onPauseFlag();

    Z2GetSeqMgr()->bgmStop(0, 0);
    Z2GetSeqMgr()->subBgmStop();
    Z2GetSeqMgr()->bgmStreamStop(0);

    g_gzInfo.mDisplay = false;
    dDlst_list_c::wipeIn(1.0f);
}

void gzSaveLoaderMng_c::getSaveMetadata(SaveCategory_e i_category, int i_entryNo, saveMetadata_s* o_data) {
    const int METADATA_OFFSET = 32;

    char pathbuf[64];
    snprintf(pathbuf, sizeof(pathbuf), "/gz/%s.bin", getCategoryMetadataPath(i_category));
    gzDVDLoadFile(pathbuf, o_data, sizeof(saveMetadata_s), METADATA_OFFSET + (i_entryNo * sizeof(saveMetadata_s)));
}

int gzSaveLoaderMng_c::getSaveEntryNum(SaveCategory_e i_category) {
    const int MIN_READ_SIZE = 32;

    u8 ATTRIBUTE_ALIGN(32) read_buffer[MIN_READ_SIZE];

    char pathbuf[64];
    snprintf(pathbuf, sizeof(pathbuf), "/gz/%s.bin", getCategoryMetadataPath(i_category));
    gzDVDLoadFile(pathbuf, read_buffer, MIN_READ_SIZE, 0);

    int entry_num = *(int*)read_buffer;
    return entry_num;
}
