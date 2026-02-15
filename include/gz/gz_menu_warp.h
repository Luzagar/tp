#ifndef GZ_MENU_WARP_H
#define GZ_MENU_WARP_H

#include "gz/gz_menu.h"
#include "gz/gz_textbox.h"
#include "gz/gz_warp_preview.h"

static const u8 STAGE_INFO_VERSION = 2;


struct gzStageHeader_s {
    u8 version;
    u8 num_stages;
    u16 reserved;
    u32 total_size;
};


struct gzStageEntryHeader_s {
    char stage_id[8];
    char stage_name[32];
    u8 num_rooms;
    u8 reserved[3];
};

struct gzRoomEntryHeader_s {
    char room_name[32];
    u8 room_id;
    u8 num_spawns;
};

class gzWarpMenu_c : public gzMenu_c {
public:
    enum gzWarpMenu_Lines_e {
        WARP_TYPE,
        WARP_STAGE,
        WARP_ROOM,
        WARP_SPAWN,
        WARP_LAYER,
        WARP_EXECUTE,

        WARP_LINE_MAX
    };

    enum gzWarpMenu_StageType_e {
        STAGE_CAVE,
        STAGE_DUNGEON,
        STAGE_INTERIOR,
        STAGE_OVERWORLD,
        STAGE_SPECIAL,

        STAGE_TYPE_MAX
    };

    gzWarpMenu_c();
    virtual ~gzWarpMenu_c();

    virtual void _delete();
    virtual void onEnterMenu();
    virtual void execute();
    virtual void draw();

    static const int LINE_NUM = WARP_LINE_MAX;

private:
    void loadTypeFile(int stageType);
    void unloadTypeFile();

    u32 getStageOffset(int idx);
    gzStageEntryHeader_s* getStageEntry(int idx);
    u32 getRoomOffset(gzStageEntryHeader_s* stage, int idx);
    gzRoomEntryHeader_s* getRoomEntry(gzStageEntryHeader_s* stage, int idx);
    u8 getSpawnId(gzRoomEntryHeader_s* room, int idx);

    void selectStage(int idx);
    void selectRoom(int idx);
    void selectSpawn(int idx);
    void executeWarp();
    void updateLineText();

    gzLine* mpLines[LINE_NUM];
    gzWarpPreview_c mPreview;

    u8* mpTypeData;
    u32 mTypeDataSize;

    int mTypeIdx;
    int mStageIdx;
    int mRoomIdx;
    int mSpawnIdx;
    u8 mLayer;

    // Cache for current entries
    gzStageEntryHeader_s* mpCurrentStage;
    gzRoomEntryHeader_s* mpCurrentRoom;
};

#endif // GZ_MENU_WARP_H
