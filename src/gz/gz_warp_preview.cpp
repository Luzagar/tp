#include "gz/gz_warp_preview.h"
#include "gz/gz.h"
#include "d/d_com_inf_game.h"
#include "JSystem/JKernel/JKRAramArchive.h"
#include <cstring>
#include <cstdio>

static const char* TYPE_NAMES[] = {"cave", "dungeon", "interior", "overworld", "special"};
static const u32 MAX_INDEX_SIZE = 8192;

gzWarpPreview_c::gzWarpPreview_c()
    : mpPicture(NULL), mpTextureData(NULL), mCurrentRoom(0xFF), mCurrentType(-1),
      mOwnsTextureData(false), mIndexesLoaded(false), mAsyncLoadIdx(-1), mAllocationFailed(false) {
    mCurrentStage[0] = '\0';
    for (int i = 0; i < PREVIEW_NUM_TYPES; i++) {
        mpIndexes[i] = NULL;
        mIndexSizes[i] = 0;
        mAsyncPending[i] = false;
    }
}

gzWarpPreview_c::~gzWarpPreview_c() {
    unloadPreview();
}

void gzWarpPreview_c::unloadIndexes() {
    for (int i = 0; i < PREVIEW_NUM_TYPES; i++) {
        if (mAsyncPending[i]) {
            DVDCancel(&mFileInfos[i].cb);
            DVDClose(&mFileInfos[i]);
            mAsyncPending[i] = false;
        }
        if (mpIndexes[i] != NULL) {
            JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
            heap->free(mpIndexes[i]);
            mpIndexes[i] = NULL;
        }
        mIndexSizes[i] = 0;
    }
    mIndexesLoaded = false;
    mAsyncLoadIdx = -1;
}

void gzWarpPreview_c::startAsyncPreload() {
    if (mIndexesLoaded || mAsyncLoadIdx >= 0) return;

    JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
    mAsyncLoadIdx = 0;

    for (int i = 0; i < PREVIEW_NUM_TYPES; i++) {
        char path[64];
        snprintf(path, sizeof(path), "/gz/previews/%s.bin", TYPE_NAMES[i]);

        if (!DVDOpen(path, &mFileInfos[i])) {
            continue;
        }

        u32 readSize = (mFileInfos[i].length < MAX_INDEX_SIZE) ? mFileInfos[i].length : MAX_INDEX_SIZE;
        readSize = (readSize + 31) & ~31;

        mpIndexes[i] = (u8*)heap->alloc(readSize, 32);
        if (mpIndexes[i] == NULL) {
            DVDClose(&mFileInfos[i]);
            continue;
        }

        mIndexSizes[i] = readSize;
        mAsyncPending[i] = true;
        DVDReadAsync(&mFileInfos[i], mpIndexes[i], readSize, 0, NULL);
    }
}

void gzWarpPreview_c::finishAsyncLoad(int idx) {
    if (!mAsyncPending[idx]) return;

    DVDClose(&mFileInfos[idx]);
    mAsyncPending[idx] = false;

    if (mpIndexes[idx] == NULL) return;

    gzPreviewHeader_s* header = (gzPreviewHeader_s*)mpIndexes[idx];
    if (header->magic != PREVIEW_MAGIC || header->version != PREVIEW_VERSION) {
        JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
        heap->free(mpIndexes[idx]);
        mpIndexes[idx] = NULL;
        mIndexSizes[idx] = 0;
    }
}

bool gzWarpPreview_c::isPreloadComplete() {
    if (mIndexesLoaded) return true;
    if (mAsyncLoadIdx < 0) return false;

    bool allDone = true;
    for (int i = 0; i < PREVIEW_NUM_TYPES; i++) {
        if (mAsyncPending[i]) {
            s32 status = DVDGetFileInfoStatus(&mFileInfos[i]);
            if (status == DVD_STATE_END) {
                finishAsyncLoad(i);
            } else if (status != DVD_STATE_FATAL_ERROR) {
                allDone = false;
            } else {
                finishAsyncLoad(i);
            }
        }
    }

    if (allDone) {
        mIndexesLoaded = true;
        mAsyncLoadIdx = -1;
    }
    return allDone;
}

u32 gzWarpPreview_c::findBtiOffset(int typeIdx, const char* stageId, u8 roomId) {
    if (typeIdx < 0 || typeIdx >= PREVIEW_NUM_TYPES) return 0;
    if (mpIndexes[typeIdx] == NULL) return 0;

    u8* index = mpIndexes[typeIdx];
    u32 indexSize = mIndexSizes[typeIdx];

    gzPreviewHeader_s* header = (gzPreviewHeader_s*)index;
    gzPreviewStageIndex_s* stages = (gzPreviewStageIndex_s*)(index + sizeof(gzPreviewHeader_s));

    for (int i = 0; i < header->num_stages; i++) {
        if (strncmp(stages[i].stage_id, stageId, 7) == 0) {
            u32 roomTableOffset = stages[i].room_table_offset;
            if (roomTableOffset >= indexSize) return 0;

            gzPreviewRoomTable_s* roomTable = (gzPreviewRoomTable_s*)(index + roomTableOffset);
            gzPreviewRoomEntry_s* rooms = (gzPreviewRoomEntry_s*)(index + roomTableOffset + sizeof(gzPreviewRoomTable_s));

            for (int j = 0; j < roomTable->num_rooms; j++) {
                if (rooms[j].room_id == roomId) {
                    return rooms[j].bti_offset;
                }
            }
            return 0;
        }
    }
    return 0;
}

void gzWarpPreview_c::loadFallback(JKRHeap* heap) {
    ResTIMG* fallbackTex;
    {
        JKRHeapOverrideScope scope(heap);
        fallbackTex =
            (ResTIMG*)dComIfGp_getMain2DArchive()->getResource('TIMG', "tt_block8x8.bti");
    }
    if (fallbackTex != NULL) {
        mpPicture = new (heap, 4) J2DPicture(fallbackTex);
        mpPicture->setBlackWhite(JUtility::TColor(0, 0, 0, 0),
                                 JUtility::TColor(48, 48, 48, 255));
        mOwnsTextureData = false;
    }
}

void gzWarpPreview_c::forceReload() {
    mCurrentType = -1;
    mCurrentStage[0] = '\0';
    mCurrentRoom = 0xFF;
    mAllocationFailed = false;
}

void gzWarpPreview_c::loadPreview(int typeIdx, const char* stageId, u8 roomId) {
    if (stageId == NULL || typeIdx < 0 || typeIdx >= PREVIEW_NUM_TYPES) return;

    if (mCurrentType == typeIdx && strcmp(mCurrentStage, stageId) == 0 && mCurrentRoom == roomId)
        return;

    mAllocationFailed = false;

    if (mpPicture != NULL) {
        delete mpPicture;
        mpPicture = NULL;
    }
    if (mpTextureData != NULL && mOwnsTextureData) {
        JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
        heap->free(mpTextureData);
    }
    mpTextureData = NULL;
    mOwnsTextureData = false;

    strncpy(mCurrentStage, stageId, 7);
    mCurrentStage[7] = '\0';
    mCurrentRoom = roomId;
    mCurrentType = typeIdx;

    JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);

    if (!isPreloadComplete()) {
        loadFallback(heap);
        return;
    }

    u32 btiOffset = findBtiOffset(typeIdx, stageId, roomId);
    if (btiOffset == 0) {
        loadFallback(heap);
        return;
    }

    mpTextureData = heap->alloc(PREVIEW_BTI_SIZE, 32);
    if (mpTextureData == NULL) {
        mAllocationFailed = true;
        loadFallback(heap);
        return;
    }

    char path[64];
    snprintf(path, sizeof(path), "/gz/previews/%s.bin", TYPE_NAMES[typeIdx]);

    DVDFileInfo fileInfo;
    if (!DVDOpen(path, &fileInfo)) {
        heap->free(mpTextureData);
        mpTextureData = NULL;
        loadFallback(heap);
        return;
    }

    DVDReadPrio(&fileInfo, mpTextureData, PREVIEW_BTI_SIZE, btiOffset, 2);
    DVDClose(&fileInfo);

    mpPicture = new (heap, 4) J2DPicture((ResTIMG*)mpTextureData);
    mOwnsTextureData = true;
}

void gzWarpPreview_c::unloadPreview() {
    if (mpPicture != NULL) {
        delete mpPicture;
        mpPicture = NULL;
    }
    if (mpTextureData != NULL && mOwnsTextureData) {
        JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
        heap->free(mpTextureData);
    }
    mpTextureData = NULL;
    mOwnsTextureData = false;
    mCurrentStage[0] = '\0';
    mCurrentRoom = 0xFF;
    mCurrentType = -1;
    mAllocationFailed = false;

    unloadIndexes();
}

void gzWarpPreview_c::draw(f32 x, f32 y, f32 w, f32 h) {
    if (mpPicture != NULL) {
        mpPicture->draw(x, y, w, h, false, false, false);
    }
}
