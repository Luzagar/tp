#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_menu_warp.h"
#include "gz/gz_utility_draw.h"
#include "gz/gz_menu_main.h"
#include "d/d_com_inf_game.h"
#include "dolphin/dvd.h"
#include <cstring>
#include <cstdio>

static const char* STAGE_TYPE_NAMES[gzWarpMenu_c::STAGE_TYPE_MAX] = {
    "cave", "dungeon", "interior", "overworld", "special"
};

static const u8 DEFAULT_LAYER = 0xFF;
static const u32 HEADER_SIZE = 8;

gzWarpMenu_c::gzWarpMenu_c() {
    mXPos = g_gzInfo.mBackgroundXPos + 170.0f;
    mLineYStart = gzMenuLayout::TAB_HEADER_Y_OFFSET;
    mOptionsXOffset = gzMenuLayout::OPTIONS_X_OFFSET - 30.0f;

    mpLines[WARP_TYPE] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("type", "stage type category");
    mpLines[WARP_STAGE] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("stage", "current stage");
    mpLines[WARP_ROOM] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("room", "current room");
    mpLines[WARP_SPAWN] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("spawn", "spawn point");
    mpLines[WARP_LAYER] = new (gzHeap(GZ_GROUP_MENU), 4) gzListOptionLine("layer", "layer override");
    mpLines[WARP_EXECUTE] = new (gzHeap(GZ_GROUP_MENU), 4) gzLine("warp", "execute warp");

    mpTypeData = NULL;
    mTypeDataSize = 0;
    mTypeIdx = STAGE_OVERWORLD;
    mStageIdx = 0;
    mRoomIdx = 0;
    mSpawnIdx = 0;
    mLayer = DEFAULT_LAYER;
    mpCurrentStage = NULL;
    mpCurrentRoom = NULL;
}

gzWarpMenu_c::~gzWarpMenu_c() {
    _delete();
}

void gzWarpMenu_c::_delete() {
    for (int i = 0; i < LINE_NUM; i++) {
        delete mpLines[i];
        mpLines[i] = NULL;
    }

    unloadTypeFile();
    mPreview.unloadPreview();
}

void gzWarpMenu_c::loadTypeFile(int stageType) {
    unloadTypeFile();

    char path[64];
    snprintf(path, sizeof(path), "/gz/stage_info/%s.bin", STAGE_TYPE_NAMES[stageType]);

    DVDFileInfo fileInfo;
    if (!DVDOpen(path, &fileInfo)) {
        OSReport("tpgz: failed to open %s\n", path);
        return;
    }

    mTypeDataSize = fileInfo.length;
    JKRHeap* heap = gzHeap(GZ_GROUP_OTHER);
    mpTypeData = (u8*)heap->alloc(mTypeDataSize, 32);
    if (!mpTypeData) {
        OSReport("tpgz: failed to allocate %d bytes\n", mTypeDataSize);
        DVDClose(&fileInfo);
        return;
    }

    DVDReadPrio(&fileInfo, mpTypeData, mTypeDataSize, 0, 2);
    DVDClose(&fileInfo);

    gzStageHeader_s* header = (gzStageHeader_s*)mpTypeData;
    if (header->version != STAGE_INFO_VERSION) {
        OSReport("tpgz: invalid stage info version %d\n", header->version);
        unloadTypeFile();
        return;
    }
}

void gzWarpMenu_c::unloadTypeFile() {
    if (mpTypeData) {
        JKRHeap* heap = gzHeap(GZ_GROUP_OTHER);
        heap->free(mpTypeData);
        mpTypeData = NULL;
    }
    mTypeDataSize = 0;
    mpCurrentStage = NULL;
    mpCurrentRoom = NULL;
}

u32 gzWarpMenu_c::getStageOffset(int idx) {
    if (!mpTypeData) return 0;

    gzStageHeader_s* header = (gzStageHeader_s*)mpTypeData;
    if (idx < 0 || idx >= header->num_stages) return 0;

    u32* stageIndexTable = (u32*)(mpTypeData + HEADER_SIZE);
    return stageIndexTable[idx];
}

gzStageEntryHeader_s* gzWarpMenu_c::getStageEntry(int idx) {
    u32 offset = getStageOffset(idx);
    if (offset == 0 || offset >= mTypeDataSize) return NULL;

    return (gzStageEntryHeader_s*)(mpTypeData + offset);
}

u32 gzWarpMenu_c::getRoomOffset(gzStageEntryHeader_s* stage, int idx) {
    if (!mpTypeData || !stage) return 0;
    if (idx < 0 || idx >= stage->num_rooms) return 0;

    u32* roomOffsets = (u32*)((u8*)stage + sizeof(gzStageEntryHeader_s));
    return roomOffsets[idx];
}

gzRoomEntryHeader_s* gzWarpMenu_c::getRoomEntry(gzStageEntryHeader_s* stage, int idx) {
    u32 offset = getRoomOffset(stage, idx);
    if (offset == 0 || offset >= mTypeDataSize) return NULL;

    return (gzRoomEntryHeader_s*)(mpTypeData + offset);
}

u8 gzWarpMenu_c::getSpawnId(gzRoomEntryHeader_s* room, int idx) {
    if (!room || idx < 0 || idx >= room->num_spawns) return 0;

    u8* spawnIds = (u8*)room + sizeof(gzRoomEntryHeader_s);
    return spawnIds[idx];
}

void gzWarpMenu_c::selectStage(int idx) {
    if (!mpTypeData) return;

    gzStageHeader_s* header = (gzStageHeader_s*)mpTypeData;
    int numStages = header->num_stages;
    if (numStages == 0) return;

    mStageIdx = ((idx % numStages) + numStages) % numStages;
    mpCurrentStage = getStageEntry(mStageIdx);

    selectRoom(0);
}

void gzWarpMenu_c::selectRoom(int idx) {
    if (!mpCurrentStage) return;

    int numRooms = mpCurrentStage->num_rooms;
    if (numRooms == 0) return;

    mRoomIdx = ((idx % numRooms) + numRooms) % numRooms;
    mpCurrentRoom = getRoomEntry(mpCurrentStage, mRoomIdx);

    selectSpawn(0);
}

void gzWarpMenu_c::selectSpawn(int idx) {
    if (!mpCurrentRoom) return;

    int numSpawns = mpCurrentRoom->num_spawns;
    if (numSpawns == 0) {
        mSpawnIdx = 0;
        return;
    }

    mSpawnIdx = ((idx % numSpawns) + numSpawns) % numSpawns;
}

void gzWarpMenu_c::executeWarp() {
    if (!mpCurrentStage || !mpCurrentRoom) return;

    u8 spawnId = (mpCurrentRoom->num_spawns > 0) ? getSpawnId(mpCurrentRoom, mSpawnIdx) : 0;

    OSReport("tpgz warp: %s room %d spawn %d\n",
             mpCurrentStage->stage_id, mpCurrentRoom->room_id, spawnId);

    mPreview.unloadPreview();
    unloadTypeFile();

    g_dComIfG_gameInfo.play.setNextStage(
        mpCurrentStage->stage_id,
        mpCurrentRoom->room_id,
        spawnId,
        mLayer,
        13,
        0
    );
    g_dComIfG_gameInfo.info.getRestart().setLastSceneInfo(0.0f, 0, 0);
    g_gzInfo.mDisplay = false;

    // Signal to automation scripts that warp was executed
    g_gzAutoState.warpExecuted = true;
}

void gzWarpMenu_c::updateLineText() {
    mpLines[WARP_TYPE]->getOptionBox()->setStringf("%s", STAGE_TYPE_NAMES[mTypeIdx]);

    if (mpCurrentStage) {
        mpLines[WARP_STAGE]->getOptionBox()->setStringf("%s", mpCurrentStage->stage_name);
    } else {
        mpLines[WARP_STAGE]->getOptionBox()->setString("none");
    }

    if (mpCurrentRoom) {
        mpLines[WARP_ROOM]->getOptionBox()->setStringf("%s", mpCurrentRoom->room_name);
        u8 spawnId = (mpCurrentRoom->num_spawns > 0) ? getSpawnId(mpCurrentRoom, mSpawnIdx) : 0;
        mpLines[WARP_SPAWN]->getOptionBox()->setStringf("%d", spawnId);
    } else {
        mpLines[WARP_ROOM]->getOptionBox()->setString("none");
        mpLines[WARP_SPAWN]->getOptionBox()->setString("0");
    }

    if (mLayer == DEFAULT_LAYER) {
        mpLines[WARP_LAYER]->getOptionBox()->setString("default");
    } else {
        mpLines[WARP_LAYER]->getOptionBox()->setStringf("%d", mLayer);
    }
}

void gzWarpMenu_c::execute() {
    if (checkInputWait()) return;

    // Check for back button
    if (gzPad::getTrigB()) {
        if (gzInfo_isMenuOption()) {
            gzInfo_offMenuOption();
            gzInfo_seStart(Z2SE_SY_CURSOR_CANCEL);
        } else if (!g_gzInfo.mpMainMenu->isTransitioning() || !g_gzInfo.mpMainMenu->isTransitionForward()) {
            mPreview.unloadPreview();
            unloadTypeFile();

            gzCursor* l_cursor = gzInfo_getCursor();
            l_cursor->x--;
            l_cursor->y = gzMainMenu_c::MENU_WARPING;
            gzInfo_seStart(Z2SE_SY_EXP_WIN_CLOSE);
            g_gzInfo.mpMainMenu->startReverseTransition();
            return;
        }
    }

    gzCursor* l_cursor = gzInfo_getCursor();

    if (gzPad::getTrigA()) {
        if (l_cursor->y == WARP_EXECUTE) {
            executeWarp();
            return;
        } else {
            gzInfo_toggleMenuOption();
        }
    }

    if (gzInfo_isMenuOption()) {
        if (gzPad::getTrigRight()) {
            switch (l_cursor->y) {
            case WARP_TYPE:
                mTypeIdx = (mTypeIdx + 1) % STAGE_TYPE_MAX;
                loadTypeFile(mTypeIdx);
                selectStage(0);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_STAGE:
                selectStage(mStageIdx + 1);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_ROOM:
                selectRoom(mRoomIdx + 1);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_SPAWN:
                selectSpawn(mSpawnIdx + 1);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_LAYER:
                mLayer++;
                if (mLayer == 0x10) mLayer = DEFAULT_LAYER;
                break;
            }
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }

        if (gzPad::getTrigLeft()) {
            switch (l_cursor->y) {
            case WARP_TYPE:
                mTypeIdx = (mTypeIdx - 1 + STAGE_TYPE_MAX) % STAGE_TYPE_MAX;
                loadTypeFile(mTypeIdx);
                selectStage(0);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_STAGE:
                selectStage(mStageIdx - 1);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_ROOM:
                selectRoom(mRoomIdx - 1);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_SPAWN:
                selectSpawn(mSpawnIdx - 1);
                mLayer = DEFAULT_LAYER;
                break;
            case WARP_LAYER:
                mLayer--;
                if (mLayer == 0xFE) mLayer = 0x0F;
                break;
            }
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
        }
    }

    if (gzPad::getTrigZ()) {
        selectStage(mStageIdx + 1);
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    handleNavigation(LINE_NUM);
    finishExecute(LINE_NUM);
}

void gzWarpMenu_c::onEnterMenu() {
    gzMenu_c::onEnterMenu();
    mPreview.startAsyncPreload();
}

void gzWarpMenu_c::draw() {
    if (!mpTypeData) {
        loadTypeFile(mTypeIdx);
        selectStage(0);
    }

    if (!mpTypeData) return;

    // Update automation state for Python scripts
    g_gzAutoState.warpTypeIdx = mTypeIdx;
    g_gzAutoState.warpStageIdx = mStageIdx;
    g_gzAutoState.warpRoomIdx = mRoomIdx;
    g_gzAutoState.warpSpawnIdx = mSpawnIdx;

    updateLineText();
    updateLineBounds((gzLine**)mpLines, LINE_NUM);

    gzCursor* l_cursor = gzInfo_getCursor();

    // Only show haihai arrows when option mode is active and not on warp line
    u8 haihai_flags = 0;
    if (gzInfo_isMenuOption() && l_cursor->y < WARP_EXECUTE) {
        haihai_flags = ARROW_LEFT | ARROW_RIGHT;
    }

    drawLines((gzLine**)mpLines, LINE_NUM, haihai_flags, 0, LINE_NUM);

    if (isEntered() && mpCurrentStage && mpCurrentRoom) {
        mPreview.startAsyncPreload();
        if (!mPreview.hasRealPreview() && mPreview.isPreloadComplete() && !mPreview.allocationFailed()) {
            mPreview.forceReload();
        }
        mPreview.loadPreview(mTypeIdx, mpCurrentStage->stage_id, mpCurrentRoom->room_id);

        f32 previewX = 170.0f;
        f32 previewY = 200.0f;
        f32 previewW = 256.0f;
        f32 previewH = 192.0f;

        u32 theme = gzInfo_getTextColor();

        GXColor shadowColor = {30, 28, 20, 255};
        gzDrawRectOutline(previewX - 7.0f, previewY - 7.0f, previewW + 14.0f, previewH + 14.0f, 3.0f, shadowColor);

        GXColor borderColor = gzGetThemedBorderColor(theme, 255);
        gzDrawRectOutline(previewX - 4.0f, previewY - 4.0f, previewW + 8.0f, previewH + 8.0f, 2.0f, borderColor);

        GXColor highlightColor = gzGetThemedHighlightColor(theme, 200);
        gzDrawRectOutline(previewX - 2.0f, previewY - 2.0f, previewW + 4.0f, previewH + 4.0f, 2.0f, highlightColor);

        mPreview.draw(previewX, previewY, previewW, previewH);
    }
}
