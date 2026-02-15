#ifndef GZ_WARP_PREVIEW_H
#define GZ_WARP_PREVIEW_H

#include "JSystem/J2DGraph/J2DPicture.h"
#include "dolphin/dvd.h"

class JKRHeap;

static const u32 PREVIEW_MAGIC = 'GZPV';
static const u8 PREVIEW_VERSION = 2;
static const u32 PREVIEW_BTI_SIZE = 98336;
static const int PREVIEW_NUM_TYPES = 5;

struct gzPreviewHeader_s {
    u32 magic;
    u8 version;
    u8 num_stages;
    u16 reserved;
};

struct gzPreviewStageIndex_s {
    char stage_id[8];
    u32 room_table_offset;
};

struct gzPreviewRoomTable_s {
    u8 num_rooms;
    u8 reserved[3];
};

struct gzPreviewRoomEntry_s {
    u8 room_id;
    u8 reserved[3];
    u32 bti_offset;
};

class gzWarpPreview_c {
public:
    gzWarpPreview_c();
    ~gzWarpPreview_c();

    void startAsyncPreload();
    bool isPreloadComplete();
    void loadPreview(int typeIdx, const char* stageId, u8 roomId);
    void forceReload();
    void unloadPreview();
    void draw(f32 x, f32 y, f32 w, f32 h);
    bool isLoaded() const { return mpPicture != NULL; }
    bool hasRealPreview() const { return mpPicture != NULL && mOwnsTextureData; }
    bool allocationFailed() const { return mAllocationFailed; }

private:
    void unloadIndexes();
    void finishAsyncLoad(int idx);
    u32 findBtiOffset(int typeIdx, const char* stageId, u8 roomId);
    void loadFallback(JKRHeap* heap);

    J2DPicture* mpPicture;
    void* mpTextureData;
    char mCurrentStage[8];
    u8 mCurrentRoom;
    int mCurrentType;
    bool mOwnsTextureData;

    u8* mpIndexes[PREVIEW_NUM_TYPES];
    u32 mIndexSizes[PREVIEW_NUM_TYPES];

    DVDFileInfo mFileInfos[PREVIEW_NUM_TYPES];
    bool mAsyncPending[PREVIEW_NUM_TYPES];
    bool mIndexesLoaded;
    int mAsyncLoadIdx;
    bool mAllocationFailed;
};

#endif
