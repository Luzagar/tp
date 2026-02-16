#include "d/dolzel.h"  // IWYU pragma: keep

#include "gz/gz_menu_inventory.h"
#include "d/d_com_inf_game.h"
#include "d/d_meter2_info.h"
#include "d/d_select_cursor.h"
#include "d/actor/d_a_alink.h"
#include "d/actor/d_a_player.h"
#include "JSystem/JKernel/JKRAramArchive.h"
#include "JSystem/JKernel/JKRArchive.h"
#include <cstdio>

static bool loadArchiveTexture(JKRArchive* arc, const char* name,
                                J2DPicture** outPane, ResTIMG** outBuf,
                                JKRHeap* heap, bool setBasePos) {
    if (arc == NULL || *outPane != NULL) return false;

    JKRArchive::SDIFileEntry* entry =
        arc->findTypeResource('TIMG', name);
    bool wasCached = (entry != NULL && entry->data != NULL);

    ResTIMG* tex;
    {
        JKRHeapOverrideScope scope(heap);
        tex = (ResTIMG*)arc->getResource('TIMG', name);
    }

    if (tex == NULL) return false;

    JKRHeap* oldHeap = heap->becomeCurrentHeap();
    u32 imgSize = GXGetTexBufferSize(tex->width, tex->height, tex->format,
                                      tex->mipmapEnabled, tex->mipmapCount);
    u32 totalSize = tex->imageOffset + imgSize;
    if (tex->indexTexture && tex->numColors > 0) {
        u32 palEnd = tex->paletteOffset + tex->numColors * 2;
        if (palEnd > totalSize) {
            totalSize = palEnd;
        }
    }
    *outBuf = (ResTIMG*)heap->alloc(totalSize, 32);
    if (*outBuf != NULL) {
        memcpy(*outBuf, tex, totalSize);
        DCStoreRangeNoSync(*outBuf, totalSize);
        *outPane = new (heap, 4) J2DPicture(*outBuf);
        if (*outPane != NULL && setBasePos) {
            (*outPane)->setBasePosition(J2DBasePosition_4);
        }
    }
    oldHeap->becomeCurrentHeap();

    if (!wasCached) {
        arc->detachResource(tex);
        heap->free(tex);
    }

    return *outPane != NULL;
}

static const char* getScentTextureName(u8 itemId) {
    switch (itemId) {
    case fpcNm_ITEM_SMELL_CHILDREN:
        return "ni_nioi_child.bti";
    case fpcNm_ITEM_SMELL_YELIA_POUCH:
        return "ni_nioi_iria.bti";
    case fpcNm_ITEM_SMELL_FISH:
        return "ni_nioi_fish.bti";
    case fpcNm_ITEM_SMELL_MEDICINE:
        return "ni_nioi_medicin.bti";
    case fpcNm_ITEM_SMELL_POH:
        return "ni_nioi_pou.bti";
    default:
        return NULL;
    }
}

void gzInventoryMenu_c::freePauseItemTextures() {
    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);

    for (int row = 0; row < PAUSE_MAX_ROWS; row++) {
        for (int col = 0; col < PAUSE_MAX_COLS; col++) {
            for (int k = 0; k < 3; k++) {
                delete mpPauseItemTex[row][col][k];
                mpPauseItemTex[row][col][k] = NULL;
                if (mpPauseItemBuf[row][col][k] != NULL) {
                    heap->free(mpPauseItemBuf[row][col][k]);
                    mpPauseItemBuf[row][col][k] = NULL;
                }
            }
        }
    }
}

void gzInventoryMenu_c::freePauseTextures(bool freeArchiveCache) {
    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);

    freePauseItemTextures();

    delete mpPauseFramePane;
    mpPauseFramePane = NULL;

    if (mpPauseFrameBuf != NULL) {
        heap->free(mpPauseFrameBuf);
        mpPauseFrameBuf = NULL;
    }

    delete mpPoeIconPane;
    mpPoeIconPane = NULL;
    if (mpPoeIconBuf != NULL) {
        heap->free(mpPoeIconBuf);
        mpPoeIconBuf = NULL;
    }

    delete mpBugsIconPane;
    mpBugsIconPane = NULL;
    if (mpBugsIconBuf != NULL) {
        heap->free(mpBugsIconBuf);
        mpBugsIconBuf = NULL;
    }

    delete mpSkillsIconPane;
    mpSkillsIconPane = NULL;
    if (mpSkillsIconBuf != NULL) {
        heap->free(mpSkillsIconBuf);
        mpSkillsIconBuf = NULL;
    }

    delete mpFishIconPane;
    mpFishIconPane = NULL;
    if (mpFishIconBuf != NULL) {
        heap->free(mpFishIconBuf);
        mpFishIconBuf = NULL;
    }

    delete mpLettersIconPane;
    mpLettersIconPane = NULL;
    if (mpLettersIconBuf != NULL) {
        heap->free(mpLettersIconBuf);
        mpLettersIconBuf = NULL;
    }

    for (int i = 0; i < HEART_TEX_COUNT; i++) {
        delete mpHeartPiecePanes[i];
        mpHeartPiecePanes[i] = NULL;
        if (mpHeartPieceBufs[i] != NULL) {
            heap->free(mpHeartPieceBufs[i]);
            mpHeartPieceBufs[i] = NULL;
        }
    }

    for (int i = 0; i < HUD_HEART_TEX_COUNT; i++) {
        delete mpHudHeartPanes[i];
        mpHudHeartPanes[i] = NULL;
        if (mpHudHeartBufs[i] != NULL) {
            heap->free(mpHudHeartBufs[i]);
            mpHudHeartBufs[i] = NULL;
        }
    }

    for (int i = 0; i < QUARTER_HEART_COUNT; i++) {
        delete mpQuarterHeartPanes[i];
        mpQuarterHeartPanes[i] = NULL;
        if (mpQuarterHeartBufs[i] != NULL) {
            heap->free(mpQuarterHeartBufs[i]);
            mpQuarterHeartBufs[i] = NULL;
        }
    }

    freeBugIcons();

    delete mpLetterIconPane;
    mpLetterIconPane = NULL;
    if (mpLetterIconBuf != NULL) {
        heap->free(mpLetterIconBuf);
        mpLetterIconBuf = NULL;
    }

    delete mpCheckIconPane;
    mpCheckIconPane = NULL;
    if (mpCheckIconBuf != NULL) {
        heap->free(mpCheckIconBuf);
        mpCheckIconBuf = NULL;
    }
    delete mpXMarkIconPane;
    mpXMarkIconPane = NULL;
    if (mpXMarkIconBuf != NULL) {
        heap->free(mpXMarkIconBuf);
        mpXMarkIconBuf = NULL;
    }

    mPauseMenuInitialized = false;
}

int gzInventoryMenu_c::getMaxColsForRow(int row) {
    switch (row) {
    case 0: return 3;
    case 1: return 3;
    case 2: return 3;
    case 3: return 4;
    case 4: return 4;
    default: return 0;
    }
}

void gzInventoryMenu_c::readPauseSlotStates() {
    if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SWORD)) {
        mPauseSlotState[0][0] = 2;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_WOOD_STICK)) {
        mPauseSlotState[0][0] = 1;
    } else {
        mPauseSlotState[0][0] = 0;
    }

    if (dComIfGs_isItemFirstBit(fpcNm_ITEM_LIGHT_SWORD)) {
        mPauseSlotState[0][1] = 2;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_MASTER_SWORD)) {
        mPauseSlotState[0][1] = 1;
    } else {
        mPauseSlotState[0][1] = 0;
    }

    if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SHIELD)) {
        mPauseSlotState[1][0] = 2;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_WOOD_SHIELD)) {
        mPauseSlotState[1][0] = 1;
    } else {
        mPauseSlotState[1][0] = 0;
    }

    mPauseSlotState[1][1] = dComIfGs_isItemFirstBit(fpcNm_ITEM_HYLIA_SHIELD) ? 1 : 0;

    mPauseSlotState[2][0] = dComIfGs_isItemFirstBit(fpcNm_ITEM_WEAR_KOKIRI) ? 1 : 0;
    mPauseSlotState[2][1] = dComIfGs_isItemFirstBit(fpcNm_ITEM_WEAR_ZORA) ? 1 : 0;
    mPauseSlotState[2][2] = dComIfGs_isItemFirstBit(fpcNm_ITEM_ARMOR) ? 1 : 0;

    mPauseSlotState[3][0] = dComIfGs_getWalletSize();
    if (dComIfGs_isItemFirstBit(fpcNm_ITEM_ARROW_LV3)) {
        mPauseSlotState[3][1] = 3;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_ARROW_LV2)) {
        mPauseSlotState[3][1] = 2;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_ARROW_LV1)) {
        mPauseSlotState[3][1] = 1;
    } else {
        mPauseSlotState[3][1] = 0;
    }
    {
        static const u8 sBugItems[] = {
            fpcNm_ITEM_M_ANT, fpcNm_ITEM_F_ANT, fpcNm_ITEM_M_MAYFLY, fpcNm_ITEM_F_MAYFLY,
            fpcNm_ITEM_M_BEETLE, fpcNm_ITEM_F_BEETLE, fpcNm_ITEM_M_MANTIS, fpcNm_ITEM_F_MANTIS,
            fpcNm_ITEM_M_STAG_BEETLE, fpcNm_ITEM_F_STAG_BEETLE, fpcNm_ITEM_M_DANGOMUSHI,
            fpcNm_ITEM_F_DANGOMUSHI, fpcNm_ITEM_M_BUTTERFLY, fpcNm_ITEM_F_BUTTERFLY,
            fpcNm_ITEM_M_LADYBUG, fpcNm_ITEM_F_LADYBUG, fpcNm_ITEM_M_SNAIL, fpcNm_ITEM_F_SNAIL,
            fpcNm_ITEM_M_NANAFUSHI, fpcNm_ITEM_F_NANAFUSHI, fpcNm_ITEM_M_GRASSHOPPER,
            fpcNm_ITEM_F_GRASSHOPPER, fpcNm_ITEM_M_DRAGONFLY, fpcNm_ITEM_F_DRAGONFLY,
        };
        bool hasBug = false;
        for (int i = 0; i < (int)(sizeof(sBugItems) / sizeof(sBugItems[0])); i++) {
            if (dComIfGs_isItemFirstBit(sBugItems[i])) {
                hasBug = true;
                break;
            }
        }
        mPauseSlotState[3][2] = hasBug ? 1 : 0;
    }
    mPauseSlotState[3][3] = dComIfGs_getEventReg(0x30ff) & 0x7;

    if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SMELL_POH)) {
        mPauseSlotState[4][0] = 5;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SMELL_MEDICINE)) {
        mPauseSlotState[4][0] = 4;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SMELL_FISH)) {
        mPauseSlotState[4][0] = 3;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SMELL_YELIA_POUCH)) {
        mPauseSlotState[4][0] = 2;
    } else if (dComIfGs_isItemFirstBit(fpcNm_ITEM_SMELL_CHILDREN)) {
        mPauseSlotState[4][0] = 1;
    } else {
        mPauseSlotState[4][0] = 0;
    }
    mPauseSlotState[4][2] = 0;
    mPauseSlotState[4][3] = 0;
}

u8 gzInventoryMenu_c::getItemForSlot(int row, int col) {
    u8 state = mPauseSlotState[row][col];

    switch (row) {
    case 0:
        if (col == 0) {
            if (state == 2) return fpcNm_ITEM_SWORD;
            if (state == 1) return fpcNm_ITEM_WOOD_STICK;
            return fpcNm_ITEM_NONE;
        } else {
            if (state == 2) return fpcNm_ITEM_LIGHT_SWORD;
            if (state == 1) return fpcNm_ITEM_MASTER_SWORD;
            return fpcNm_ITEM_NONE;
        }
    case 1:
        if (col == 0) {
            if (state == 2) return fpcNm_ITEM_SHIELD;
            if (state == 1) return fpcNm_ITEM_WOOD_SHIELD;
            return fpcNm_ITEM_NONE;
        } else {
            return state ? fpcNm_ITEM_HYLIA_SHIELD : fpcNm_ITEM_NONE;
        }
    case 2:
        if (col == 0) return state ? fpcNm_ITEM_WEAR_KOKIRI : fpcNm_ITEM_NONE;
        if (col == 1) return state ? fpcNm_ITEM_WEAR_ZORA : fpcNm_ITEM_NONE;
        if (col == 2) return state ? fpcNm_ITEM_ARMOR : fpcNm_ITEM_NONE;
        break;
    case 3:
        if (col == 0) {
            if (state >= 2) return fpcNm_ITEM_WALLET_LV3;
            if (state == 1) return fpcNm_ITEM_WALLET_LV2;
            return fpcNm_ITEM_WALLET_LV1;
        }
        if (col == 1) {
            if (state >= 3) return fpcNm_ITEM_ARROW_LV3;
            if (state == 2) return fpcNm_ITEM_ARROW_LV2;
            if (state == 1) return fpcNm_ITEM_ARROW_LV1;
            return fpcNm_ITEM_NONE;
        }
        if (col == 2) return fpcNm_ITEM_NONE;
        if (col == 3) return fpcNm_ITEM_NONE;
        break;
    case 4:
        if (col == 0) {
            if (state == 5) return fpcNm_ITEM_SMELL_POH;
            if (state == 4) return fpcNm_ITEM_SMELL_MEDICINE;
            if (state == 3) return fpcNm_ITEM_SMELL_FISH;
            if (state == 2) return fpcNm_ITEM_SMELL_YELIA_POUCH;
            if (state == 1) return fpcNm_ITEM_SMELL_CHILDREN;
            return fpcNm_ITEM_NONE;
        }
        if (col == 1) return fpcNm_ITEM_NONE;
        if (col == 2) return fpcNm_ITEM_NONE;
        if (col == 3) return fpcNm_ITEM_NONE;
        break;
    }
    return fpcNm_ITEM_NONE;
}

u8 gzInventoryMenu_c::getDisplayItemForSlot(int row, int col) {
    u8 item = getItemForSlot(row, col);
    if (item != fpcNm_ITEM_NONE) return item;

    switch (row) {
    case 0:
        return (col == 0) ? fpcNm_ITEM_WOOD_STICK : fpcNm_ITEM_MASTER_SWORD;
    case 1:
        return (col == 0) ? fpcNm_ITEM_WOOD_SHIELD : fpcNm_ITEM_HYLIA_SHIELD;
    case 2:
        if (col == 0) return fpcNm_ITEM_WEAR_KOKIRI;
        if (col == 1) return fpcNm_ITEM_WEAR_ZORA;
        if (col == 2) return fpcNm_ITEM_ARMOR;
        break;
    case 3:
        if (col == 0) return fpcNm_ITEM_WALLET_LV1;
        if (col == 1) return fpcNm_ITEM_ARROW_LV1;
        break;
    case 4:
        if (col == 0) return fpcNm_ITEM_SMELL_CHILDREN;
        break;
    }
    return fpcNm_ITEM_NONE;
}

void gzInventoryMenu_c::loadPauseItemTexture(int row, int col, u8 itemId) {
    for (int k = 0; k < 3; k++) {
        delete mpPauseItemTex[row][col][k];
        mpPauseItemTex[row][col][k] = NULL;
    }

    if (itemId == fpcNm_ITEM_NONE) {
        return;
    }

    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);
    JKRHeap* oldHeap = heap->becomeCurrentHeap();

    for (int k = 0; k < 3; k++) {
        if (mpPauseItemBuf[row][col][k] == NULL) {
            mpPauseItemBuf[row][col][k] = (ResTIMG*)new (heap, 0x20) u8[0xC00];
        }
    }

    const char* scentTex = getScentTextureName(itemId);
    s32 textureNum = 0;

    if (scentTex != NULL) {
        JKRArchive* collectArc = dComIfGp_getCollectResArchive();
        if (collectArc != NULL) {
            u32 readSize = collectArc->readResource(
                mpPauseItemBuf[row][col][0], 0xC00, 'TIMG', scentTex);
            if (readSize > 0) {
                DCStoreRangeNoSync(mpPauseItemBuf[row][col][0], 0xC00);
                textureNum = 1;
            }
        }
    } else {
        textureNum = dMeter2Info_readItemTexture(
            itemId, mpPauseItemBuf[row][col][0], NULL, mpPauseItemBuf[row][col][1], NULL,
            mpPauseItemBuf[row][col][2], NULL, NULL, NULL, -1);
    }

    for (int k = 0; k < textureNum; k++) {
        mpPauseItemTex[row][col][k] = new (heap, 4) J2DPicture(mpPauseItemBuf[row][col][k]);
        mpPauseItemTex[row][col][k]->setBasePosition(J2DBasePosition_4);
    }

    if (scentTex == NULL) {
        dMeter2Info_setItemColor(itemId, mpPauseItemTex[row][col][0], mpPauseItemTex[row][col][1], mpPauseItemTex[row][col][2], NULL);
    }

    oldHeap->becomeCurrentHeap();
}

void gzInventoryMenu_c::loadBugIcons() {
    static const u8 sBugItemIds[BUG_COUNT] = {
        fpcNm_ITEM_M_ANT, fpcNm_ITEM_F_ANT, fpcNm_ITEM_M_MAYFLY, fpcNm_ITEM_F_MAYFLY,
        fpcNm_ITEM_M_BEETLE, fpcNm_ITEM_F_BEETLE, fpcNm_ITEM_M_MANTIS, fpcNm_ITEM_F_MANTIS,
        fpcNm_ITEM_M_STAG_BEETLE, fpcNm_ITEM_F_STAG_BEETLE, fpcNm_ITEM_M_DANGOMUSHI,
        fpcNm_ITEM_F_DANGOMUSHI, fpcNm_ITEM_M_BUTTERFLY, fpcNm_ITEM_F_BUTTERFLY,
        fpcNm_ITEM_M_LADYBUG, fpcNm_ITEM_F_LADYBUG, fpcNm_ITEM_M_SNAIL, fpcNm_ITEM_F_SNAIL,
        fpcNm_ITEM_M_NANAFUSHI, fpcNm_ITEM_F_NANAFUSHI, fpcNm_ITEM_M_GRASSHOPPER,
        fpcNm_ITEM_F_GRASSHOPPER, fpcNm_ITEM_M_DRAGONFLY, fpcNm_ITEM_F_DRAGONFLY,
    };
    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);
    JKRHeap* oldHeap = heap->becomeCurrentHeap();
    for (int i = 0; i < BUG_COUNT; i++) {
        if (mpBugIconPanes[i] != NULL) continue;
        if (mpBugIconBufs[i] == NULL) {
            mpBugIconBufs[i] = (ResTIMG*)new (heap, 0x20) u8[0xC00];
        }
        if (mpBugIconBufs[i] != NULL) {
            int texNum = dMeter2Info_readItemTexture(
                sBugItemIds[i], mpBugIconBufs[i], NULL, NULL, NULL,
                NULL, NULL, NULL, NULL, -1);
            if (texNum > 0) {
                mpBugIconPanes[i] = new (heap, 4) J2DPicture(mpBugIconBufs[i]);
            }
        }
    }
    oldHeap->becomeCurrentHeap();
}

void gzInventoryMenu_c::freeBugIcons() {
    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);
    for (int i = 0; i < BUG_COUNT; i++) {
        delete mpBugIconPanes[i];
        mpBugIconPanes[i] = NULL;
        if (mpBugIconBufs[i] != NULL) {
            heap->free(mpBugIconBufs[i]);
            mpBugIconBufs[i] = NULL;
        }
    }
}

void gzInventoryMenu_c::initPauseMenu() {
    JKRHeap* heap = gzHeap(GZ_GROUP_MENU);

    readPauseSlotStates();

    for (int row = 0; row < PAUSE_MAX_ROWS; row++) {
        int maxCols = getMaxColsForRow(row);
        for (int col = 0; col < maxCols; col++) {
            u8 item = getDisplayItemForSlot(row, col);
            loadPauseItemTexture(row, col, item);
        }
    }

    JKRArchive* collectArc = dComIfGp_getCollectResArchive();

    loadArchiveTexture(collectArc, "tt_spot_square3.bti",
                       &mpPauseFramePane, &mpPauseFrameBuf, heap, true);

    loadArchiveTexture(collectArc, "ni_item_icon_pou.bti",
                       &mpPoeIconPane, &mpPoeIconBuf, heap, true);

    struct CollectIconLoad {
        const char* texName;
        J2DPicture** pPane;
        ResTIMG** pBuf;
    };
    CollectIconLoad iconLoads[] = {
        {"ni_kab_o.bti", &mpBugsIconPane, &mpBugsIconBuf},
        {"ni_item_icon_makimono.bti", &mpSkillsIconPane, &mpSkillsIconBuf},
        {"ni_item_icon_fish.bti", &mpFishIconPane, &mpFishIconBuf},
        {"ni_item_icon_letter.bti", &mpLettersIconPane, &mpLettersIconBuf},
    };
    for (int i = 0; i < 4; i++) {
        loadArchiveTexture(collectArc, iconLoads[i].texName,
                           iconLoads[i].pPane, iconLoads[i].pBuf, heap, true);
    }

    if (collectArc != NULL && mpHeartPiecePanes[0] == NULL) {
        static const char* heartTexNames[HEART_TEX_COUNT] = {
            "zelda_heart_parts_iwasawa_ver2_base_00.bti",
            "zelda_heart_parts_iwasawa_ver2_parts1.bti",
            "zelda_heart_parts_iwasawa_ver2_parts2.bti",
            "zelda_heart_parts_iwasawa_ver2_parts3.bti",
            "zelda_heart_parts_iwasawa_ver2_parts4.bti",
        };
        for (int i = 0; i < HEART_TEX_COUNT; i++) {
            loadArchiveTexture(collectArc, heartTexNames[i],
                               &mpHeartPiecePanes[i], &mpHeartPieceBufs[i], heap, false);
        }
    }

    JKRArchive* main2DArc = dComIfGp_getMain2DArchive();
    if (main2DArc != NULL && mpHudHeartPanes[0] == NULL) {
        static const char* hudHeartTexNames[HUD_HEART_TEX_COUNT] = {
            "tt_heart_00.bti",
            "tt_heart_base_wave_24.bti",
        };
        for (int i = 0; i < HUD_HEART_TEX_COUNT; i++) {
            loadArchiveTexture(main2DArc, hudHeartTexNames[i],
                               &mpHudHeartPanes[i], &mpHudHeartBufs[i], heap, false);
        }
    }

    if (main2DArc != NULL && mpQuarterHeartPanes[0] == NULL) {
        static const char* quarterHeartTexNames[QUARTER_HEART_COUNT] = {
            "tt_heart_01.bti",
            "tt_heart_02.bti",
            "tt_heart_03.bti",
        };
        for (int i = 0; i < QUARTER_HEART_COUNT; i++) {
            loadArchiveTexture(main2DArc, quarterHeartTexNames[i],
                               &mpQuarterHeartPanes[i], &mpQuarterHeartBufs[i], heap, false);
        }
    }

    loadBugIcons();

    if (mpLetterIconPane == NULL) {
        if (mpLetterIconBuf == NULL) {
            mpLetterIconBuf = (ResTIMG*)new (heap, 0x20) u8[0xC00];
        }
        if (mpLetterIconBuf != NULL) {
            JKRHeap* oldHeap = heap->becomeCurrentHeap();
            int texNum = dMeter2Info_readItemTexture(
                fpcNm_ITEM_LETTER, mpLetterIconBuf, NULL, NULL, NULL,
                NULL, NULL, NULL, NULL, -1);
            if (texNum > 0) {
                mpLetterIconPane = new (heap, 4) J2DPicture(mpLetterIconBuf);
            }
            oldHeap->becomeCurrentHeap();
        }
    }

    if (mpCheckIconPane == NULL) {
        mpCheckIconBuf = JKRHeap::alloc(SKILL_ICON_BTI_SIZE, 32, heap);
        if (mpCheckIconBuf != NULL) {
            gzDVDLoadFile("/gz/check.bti", mpCheckIconBuf, SKILL_ICON_BTI_SIZE, 0);
            mpCheckIconPane = new (heap, 4) J2DPicture((ResTIMG*)mpCheckIconBuf);
            if (mpCheckIconPane != NULL) {
                mpCheckIconPane->setBlackWhite(
                    JUtility::TColor(0, 0, 0, 0), JUtility::TColor(76, 175, 80, 255));
            }
        }
    }
    if (mpXMarkIconPane == NULL) {
        mpXMarkIconBuf = JKRHeap::alloc(SKILL_ICON_BTI_SIZE, 32, heap);
        if (mpXMarkIconBuf != NULL) {
            gzDVDLoadFile("/gz/x_mark.bti", mpXMarkIconBuf, SKILL_ICON_BTI_SIZE, 0);
            mpXMarkIconPane = new (heap, 4) J2DPicture((ResTIMG*)mpXMarkIconBuf);
            if (mpXMarkIconPane != NULL) {
                mpXMarkIconPane->setBlackWhite(
                    JUtility::TColor(0, 0, 0, 0), JUtility::TColor(244, 67, 54, 255));
            }
        }
    }

    mPauseMenuInitialized = true;
}

void gzInventoryMenu_c::cyclePauseSlot(int row, int col) {
    u8 state = mPauseSlotState[row][col];

    switch (row) {
    case 0:
        if (col == 0) {
            state = (state + 1) % 3;
            dComIfGs_offItemFirstBit(fpcNm_ITEM_WOOD_STICK);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SWORD);
            if (state == 1) dComIfGs_onItemFirstBit(fpcNm_ITEM_WOOD_STICK);
            if (state == 2) dComIfGs_onItemFirstBit(fpcNm_ITEM_SWORD);
        } else {
            state = (state + 1) % 3;
            dComIfGs_offItemFirstBit(fpcNm_ITEM_MASTER_SWORD);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_LIGHT_SWORD);
            if (state == 1) dComIfGs_onItemFirstBit(fpcNm_ITEM_MASTER_SWORD);
            if (state == 2) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_MASTER_SWORD);
                dComIfGs_onItemFirstBit(fpcNm_ITEM_LIGHT_SWORD);
            }
        }
        break;
    case 1:
        if (col == 0) {
            state = (state + 1) % 3;
            dComIfGs_offItemFirstBit(fpcNm_ITEM_WOOD_SHIELD);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SHIELD);
            if (state == 1) dComIfGs_onItemFirstBit(fpcNm_ITEM_WOOD_SHIELD);
            if (state == 2) dComIfGs_onItemFirstBit(fpcNm_ITEM_SHIELD);
        } else {
            state = state ? 0 : 1;
            if (state) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_HYLIA_SHIELD);
            } else {
                dComIfGs_offItemFirstBit(fpcNm_ITEM_HYLIA_SHIELD);
            }
        }
        break;
    case 2:
        state = state ? 0 : 1;
        if (col == 0) {
            if (state) dComIfGs_onItemFirstBit(fpcNm_ITEM_WEAR_KOKIRI);
            else dComIfGs_offItemFirstBit(fpcNm_ITEM_WEAR_KOKIRI);
        } else if (col == 1) {
            if (state) dComIfGs_onItemFirstBit(fpcNm_ITEM_WEAR_ZORA);
            else dComIfGs_offItemFirstBit(fpcNm_ITEM_WEAR_ZORA);
        } else if (col == 2) {
            if (state) dComIfGs_onItemFirstBit(fpcNm_ITEM_ARMOR);
            else dComIfGs_offItemFirstBit(fpcNm_ITEM_ARMOR);
        }
        break;
    case 3:
        if (col == 0) {
            state = (state + 1) % 3;
            dComIfGs_setWalletSize(state);
        } else if (col == 1) {
            state = (state + 1) % 4;
            dComIfGs_offItemFirstBit(fpcNm_ITEM_ARROW_LV1);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_ARROW_LV2);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_ARROW_LV3);
            if (state >= 1) dComIfGs_onItemFirstBit(fpcNm_ITEM_ARROW_LV1);
            if (state >= 2) dComIfGs_onItemFirstBit(fpcNm_ITEM_ARROW_LV2);
            if (state >= 3) dComIfGs_onItemFirstBit(fpcNm_ITEM_ARROW_LV3);
            static const u8 sArrowMax[] = { 0, 30, 60, 100 };
            dComIfGs_setArrowMax(sArrowMax[state]);
            dComIfGs_setArrowNum(sArrowMax[state]);
        } else if (col == 2) {
            state = state ? 0 : 1;
        } else if (col == 3) {
            state = (state + 1) % 8;
            dComIfGs_setEventReg(0x30ff, state);
        }
        break;
    case 4:
        if (col == 0) {
            state = (state + 1) % 6;
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SMELL_CHILDREN);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SMELL_YELIA_POUCH);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SMELL_FISH);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SMELL_MEDICINE);
            dComIfGs_offItemFirstBit(fpcNm_ITEM_SMELL_POH);
            if (state == 1) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_SMELL_CHILDREN);
                dComIfGs_setCollectSmell(fpcNm_ITEM_SMELL_CHILDREN);
            } else if (state == 2) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_SMELL_YELIA_POUCH);
                dComIfGs_setCollectSmell(fpcNm_ITEM_SMELL_YELIA_POUCH);
            } else if (state == 3) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_SMELL_FISH);
                dComIfGs_setCollectSmell(fpcNm_ITEM_SMELL_FISH);
            } else if (state == 4) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_SMELL_MEDICINE);
                dComIfGs_setCollectSmell(fpcNm_ITEM_SMELL_MEDICINE);
            } else if (state == 5) {
                dComIfGs_onItemFirstBit(fpcNm_ITEM_SMELL_POH);
                dComIfGs_setCollectSmell(fpcNm_ITEM_SMELL_POH);
            } else {
                dComIfGs_setCollectSmell(fpcNm_ITEM_NONE);
            }
        } else if (col == 1) {
        } else if (col == 2) {
            state = state ? 0 : 1;
        } else if (col == 3) {
            state = state ? 0 : 1;
        }
        break;
    }

    bool wasEquipped = isSlotEquipped(row, col);
    mPauseSlotState[row][col] = state;
    u8 item = getDisplayItemForSlot(row, col);
    loadPauseItemTexture(row, col, item);
    if (wasEquipped && getItemForSlot(row, col) != fpcNm_ITEM_NONE) {
        equipPauseSlot(row, col);
    }
}

void gzInventoryMenu_c::equipPauseSlot(int row, int col) {
    if (row > 2) return;

    u8 state = mPauseSlotState[row][col];
    if (state == 0) return;

    u8 item = getItemForSlot(row, col);
    if (item == fpcNm_ITEM_NONE) return;

    switch (row) {
    case 0:
        dMeter2Info_setSword(item, false);
        break;
    case 1:
        dMeter2Info_setShield(item, false);
        if (daAlink_getAlinkActorClass() != NULL) {
            daAlink_getAlinkActorClass()->setShieldChange();
        }
        break;
    case 2:
        dMeter2Info_setCloth(item, false);
        if (daPy_getPlayerActorClass() != NULL) {
            daPy_getPlayerActorClass()->setClothesChange(0);
        }
        break;
    }
}

void gzInventoryMenu_c::executePauseMenu() {
    if (!mIsEntered) {
        return;
    }
    if (!mPauseMenuInitialized) {
        initPauseMenu();
    }

    if (inSkillSubMenu()) { executeSkillSubMenu(); return; }
    if (inBugSubMenu()) { executeBugSubMenu(); return; }
    if (inLetterSubMenu()) { executeLetterSubMenu(); return; }
    if (inFishAdjusting()) { executeFishAdjusting(); return; }
    if (inFishEditMode()) { executeFishEditMode(); return; }
    if (inFishSubMenu()) { executeFishSubMenu(); return; }
    if (inPoeEditMode()) { executePoeEditMode(); return; }
    if (inCurrentLifeEditMode()) { executeCurrentLifeEditMode(); return; }
    if (inHeartPieceEditMode()) { executeHeartPieceEditMode(); return; }
    if (inRupeeEditMode()) { executeRupeeEditMode(); return; }

    if (gzPad::getTrigDown()) {
        if (mPauseCursorRow == -1) {
            mPauseCursorRow = 0;
        } else if (isHeartPieceSlotSelected()) {
            mPauseCursorRow = 2;
        } else {
            mPauseCursorRow = (mPauseCursorRow + 1) % PAUSE_MAX_ROWS;
        }
        if (mPauseCursorRow >= 0) {
            int newMaxCols = getMaxColsForRow(mPauseCursorRow);
            if (mPauseCursorCol >= newMaxCols) {
                mPauseCursorCol = newMaxCols - 1;
            }
        }
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }
    if (gzPad::getTrigUp()) {
        if (mPauseCursorRow == -1) {
            mPauseCursorRow = PAUSE_MAX_ROWS - 1;
        } else if (mPauseCursorRow == 0 || isHeartPieceSlotSelected()) {
            mPauseCursorRow = -1;
        } else {
            mPauseCursorRow--;
        }
        if (mPauseCursorRow >= 0) {
            int newMaxCols = getMaxColsForRow(mPauseCursorRow);
            if (mPauseCursorCol >= newMaxCols) {
                mPauseCursorCol = newMaxCols - 1;
            }
        }
        gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
    }

    if (mPauseCursorRow >= 0) {
        int maxCols = getMaxColsForRow(mPauseCursorRow);
        if (gzPad::getTrigRight()) {
            mPauseCursorCol = (mPauseCursorCol + 1) % maxCols;
            gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
        }
        if (gzPad::getTrigLeft()) {
            mPauseCursorCol = (mPauseCursorCol - 1 + maxCols) % maxCols;
            gzInfo_seStart(Z2SE_SY_NAME_CURSOR);
        }
    }

    if (gzPad::getTrigZ() && mPauseCursorRow >= 0 && !isPoeSlotSelected() &&
        !isHeartPieceSlotSelected() && !isSkillSlotSelected() &&
        !isBugSlotSelected() && !isLetterSlotSelected() &&
        !isFishSlotSelected()) {
        cyclePauseSlot(mPauseCursorRow, mPauseCursorCol);
        gzInfo_seStart(Z2SE_SY_TALK_CURSOR);
    }

    if (gzPad::getTrigA()) {
        if (isHudHeartsSelected()) {
            gzInfo_onMenuOption();
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
        } else if (isBugSlotSelected() && !inBugSubMenu()) {
            mBugSubMenuActive = true;
            mBugSubMenuRow = 0;
            mBugSubMenuCol = 0;
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
        } else if (isSkillSlotSelected() && !inSkillSubMenu()) {
            mSkillSubMenuActive = true;
            mSkillSubMenuIndex = 0;
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
        } else if (isLetterSlotSelected() && !inLetterSubMenu()) {
            mLetterSubMenuActive = true;
            mLetterSubMenuRow = 0;
            mLetterSubMenuCol = 0;
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
        } else if (isFishSlotSelected() && !inFishSubMenu()) {
            mFishSubMenuActive = true;
            mFishSubMenuRow = 0;
            mFishSubMenuCol = 0;
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
        } else if (isPoeSlotSelected() || isHeartPieceSlotSelected() ||
                   isWalletSlotSelected()) {
            if (gzInfo_isMenuOption()) {
                gzInfo_offMenuOption();
            } else {
                gzInfo_onMenuOption();
            }
            gzInfo_seStart(Z2SE_SY_TALK_CURSOR_OK);
        } else if (mPauseCursorRow <= 2) {
            bool hasItem = mPauseSlotState[mPauseCursorRow][mPauseCursorCol] > 0;
            bool alreadyEquipped = isSlotEquipped(mPauseCursorRow, mPauseCursorCol);
            if (hasItem && !alreadyEquipped) {
                equipPauseSlot(mPauseCursorRow, mPauseCursorCol);
                gzInfo_seStart(Z2SE_SY_ITEM_SET_X);
            }
        }
    }

    const char* itemName;
    if (mPauseCursorRow == -1) {
        itemName = "Current Life";
    } else {
        u8 currentItem = getDisplayItemForSlot(mPauseCursorRow, mPauseCursorCol);
        itemName = getItemName(currentItem);
        if (mPauseCursorCol == 2 && mPauseCursorRow <= 1) {
            itemName = "Heart Pieces";
        } else if (mPauseCursorRow == 3 && mPauseCursorCol == 0) {
            itemName = "Wallet";
        } else if (mPauseCursorRow == 3 && mPauseCursorCol == 2) {
            itemName = "Golden Bugs";
        } else if (mPauseCursorRow == 3 && mPauseCursorCol == 3) {
            itemName = "Hidden Skills";
        } else if (mPauseCursorRow == 4 && mPauseCursorCol == 1) {
            itemName = "Poe Souls";
        } else if (mPauseCursorRow == 4 && mPauseCursorCol == 2) {
            itemName = "Fish Journal";
        } else if (mPauseCursorRow == 4 && mPauseCursorCol == 3) {
            itemName = "Letters";
        }
    }
    gzInfo_getMenuDescription()->setString(itemName);
}

bool gzInventoryMenu_c::isSlotEquipped(int row, int col) {
    u8 item = getItemForSlot(row, col);
    if (item == fpcNm_ITEM_NONE) return false;

    switch (row) {
    case 0:
        return item == dComIfGs_getSelectEquipSword();
    case 1:
        return item == dComIfGs_getSelectEquipShield();
    case 2:
        return item == dComIfGs_getSelectEquipClothes();
    default:
        return false;
    }
}

void gzInventoryMenu_c::drawPauseMenuContent() {
    static const f32 GRID_START_X = -15.0f;
    static const f32 GRID_START_Y = 70.0f;
    static const f32 CELL_SIZE = 52.0f;
    static const f32 ROW_SPACING = 56.0f;

    f32 baseX = mXPos + GRID_START_X;
    f32 baseY = g_gzInfo.mBackgroundYPos + GRID_START_Y;

    if (mpHudHeartPanes[0] != NULL && mpHudHeartPanes[1] != NULL) {
        mpHudHeartPanes[0]->setBlackWhite(
            JUtility::TColor(231, 25, 0, 0), JUtility::TColor(255, 255, 255, 255));
        mpHudHeartPanes[1]->setBlackWhite(
            JUtility::TColor(0, 0, 0, 0), JUtility::TColor(255, 242, 170, 140));
        for (int q = 0; q < QUARTER_HEART_COUNT; q++) {
            if (mpQuarterHeartPanes[q] != NULL) {
                mpQuarterHeartPanes[q]->setBlackWhite(
                    JUtility::TColor(231, 25, 0, 0),
                    JUtility::TColor(255, 255, 255, 255));
            }
        }

        u16 maxLife = dComIfGs_getMaxLife();
        u16 life = dComIfGs_getLife();
        int numContainers = maxLife / 5;
        int fullCurrent = life / 4;
        int quarters = life % 4;
        static const f32 HH_W = 20.0f;
        static const f32 HH_H = 18.0f;
        static const f32 HH_GAP = 1.0f;
        static const int HH_PER_ROW = 10;
        f32 heartsX = baseX + 24.0f;
        f32 heartsY = g_gzInfo.mBackgroundYPos + 48.0f;

        bool editing = inCurrentLifeEditMode();
        bool selected = isHudHeartsSelected() && mIsEntered;
        int activeIdx = 0;
        if (quarters > 0) {
            activeIdx = fullCurrent;
        } else if (fullCurrent > 0) {
            activeIdx = fullCurrent - 1;
        }

        f32 activeHX = heartsX;
        f32 activeHY = heartsY;

        for (int i = 0; i < numContainers; i++) {
            int hRow = i / HH_PER_ROW;
            int hCol = i % HH_PER_ROW;
            f32 hx = heartsX + hCol * (HH_W + HH_GAP);
            f32 hy = heartsY + hRow * (HH_H + HH_GAP);

            f32 scale = 1.0f;
            if (editing && i == activeIdx) {
                scale = 1.4f;
            } else if (selected && !editing) {
                scale = 1.1f;
            }
            f32 dw = HH_W * scale;
            f32 dh = HH_H * scale;
            f32 dx = hx - (dw - HH_W) / 2.0f;
            f32 dy = hy - (dh - HH_H) / 2.0f;

            if (i < fullCurrent) {
                gzSetup2DContext();
                mpHudHeartPanes[1]->setAlpha(255);
                mpHudHeartPanes[1]->draw(dx, dy, dw, dh, true, true, false);

                gzSetup2DContext();
                mpHudHeartPanes[0]->setAlpha(255);
                mpHudHeartPanes[0]->draw(dx, dy, dw, dh, false, false, false);
            } else if (i == fullCurrent && quarters > 0) {
                J2DPicture* qPane = mpQuarterHeartPanes[quarters - 1];
                if (qPane != NULL) {
                    gzSetup2DContext();
                    qPane->setAlpha(255);
                    qPane->draw(dx, dy, dw, dh, false, false, false);
                }
            } else {
                gzSetup2DContext();
                mpHudHeartPanes[0]->setAlpha(50);
                mpHudHeartPanes[0]->draw(dx, dy, dw, dh, false, false, false);
            }

            if (i == activeIdx) {
                activeHX = hx;
                activeHY = hy;
            }
        }

        if (selected && gzInfo_isCursorTypeTP() && gzInfo_getTPCursor() != NULL) {
            if (editing) {
                gzInfo_getTPCursor()->setPos(
                    activeHX + HH_W / 2.0f, activeHY + HH_H / 2.0f);
                gzInfo_getTPCursor()->setParam(0.7f, 0.6f, 0.03f, 0.6f, 0.5f);
            } else {
                int topCols = numContainers > HH_PER_ROW ? HH_PER_ROW : numContainers;
                int numRows = (numContainers + HH_PER_ROW - 1) / HH_PER_ROW;
                f32 totalW = topCols * (HH_W + HH_GAP);
                f32 totalH = numRows * (HH_H + HH_GAP);
                f32 cx = heartsX + totalW / 2.0f;
                f32 cy = heartsY + totalH / 2.0f - HH_GAP / 2.0f;
                gzInfo_getTPCursor()->setPos(cx, cy);
                f32 xScale = topCols * 0.5f;
                if (xScale < 1.0f) xScale = 1.0f;
                f32 yScale = numRows * 0.5f;
                if (yScale < 0.5f) yScale = 0.5f;
                gzInfo_getTPCursor()->setParam(xScale, yScale, 0.03f, 0.6f, 0.5f);
            }
            gzInfo_getTPCursor()->draw();
        }

        if (editing && mpHaihai != NULL) {
            mpHaihai->_execute(0);
            mpHaihai->setScale(0.5f);
            u16 maxHealth = (maxLife / 5) * 4;
            u8 arrowFlags = ARROW_LEFT | ARROW_RIGHT;
            if (life == 0) arrowFlags &= ~ARROW_LEFT;
            if (life >= maxHealth) arrowFlags &= ~ARROW_RIGHT;
            f32 haihaiX = activeHX + HH_W / 2.0f;
            f32 haihaiY = activeHY + HH_H / 2.0f;
            mpHaihai->drawHaihai(arrowFlags, haihaiX, haihaiY, 30.0f, 0.0f);
        }
    }

    for (int row = 0; row < PAUSE_MAX_ROWS; row++) {
        f32 rowY = baseY + row * ROW_SPACING;
        int maxCols = getMaxColsForRow(row);

        for (int col = 0; col < maxCols; col++) {
            f32 cellX = baseX + col * CELL_SIZE;
            f32 cellY = rowY;

            bool isHeartSlot = (col == 2 && row <= 1);
            if (isHeartSlot) {
                cellX += 20.0f;
                cellY = baseY + ROW_SPACING / 2.0f;
            }

            bool isSelected = (row == mPauseCursorRow && col == mPauseCursorCol);

            if (isHeartSlot) {
                if (row == 0 && mpHeartPiecePanes[0] != NULL) {
                    bool heartSelected = mIsEntered && isHeartPieceSlotSelected();
                    f32 heartW = 80.0f;
                    f32 heartH = 66.0f;
                    if (heartSelected) {
                        heartW *= 1.1f;
                        heartH *= 1.1f;
                    }
                    f32 heartX = cellX + 48.0f - heartW / 2.0f;
                    f32 heartY = cellY + 48.0f - heartH / 2.0f;

                    gzSetup2DContext();
                    mpHeartPiecePanes[0]->setAlpha(255);
                    mpHeartPiecePanes[0]->draw(heartX, heartY, heartW, heartH,
                                               false, false, false);

                    u16 maxLife = dComIfGs_getMaxLife();
                    s32 pieces = maxLife % 5;
                    for (int p = 1; p <= pieces; p++) {
                        if (mpHeartPiecePanes[p] != NULL) {
                            gzSetup2DContext();
                            mpHeartPiecePanes[p]->setAlpha(255);
                            mpHeartPiecePanes[p]->draw(heartX, heartY, heartW, heartH,
                                                       false, false, false);
                        }
                    }

                    if (inHeartPieceEditMode() && mpHaihai != NULL) {
                        mpHaihai->_execute(0);
                        mpHaihai->setScale(0.5f);
                        u8 arrowFlags = ARROW_LEFT | ARROW_RIGHT;
                        if (maxLife <= 5) arrowFlags &= ~ARROW_LEFT;
                        if (maxLife >= 100) arrowFlags &= ~ARROW_RIGHT;
                        mpHaihai->drawHaihai(arrowFlags,
                                             cellX + 48.0f, cellY + 48.0f,
                                             heartW + 10.0f, 0.0f);
                    }
                }

                if (isSelected && mIsEntered && gzInfo_isCursorTypeTP() &&
                    gzInfo_getTPCursor() != NULL) {
                    gzInfo_getTPCursor()->setPos(cellX + 49.0f, cellY + 49.0f);
                    gzInfo_getTPCursor()->setParam(1.5f, 1.5f, 0.1f, 0.6f, 0.5f);
                    gzInfo_getTPCursor()->draw();
                }
                continue;
            }

            bool hasItem = mPauseSlotState[row][col] > 0 || (row == 3 && col == 0);
            bool isEquipped = isSlotEquipped(row, col);

            if (mpPauseFramePane != NULL) {
                gzSetup2DContext();
                JUtility::TColor frameColor(107, 107, 107, 255);
                if (mIsEntered && isSelected && gzInfo_isCursorTypeClassic()) {
                    u32 themeColor = gzInfo_getTextColor();
                    frameColor.r = (themeColor >> 24) & 0xFF;
                    frameColor.g = (themeColor >> 16) & 0xFF;
                    frameColor.b = (themeColor >> 8) & 0xFF;
                } else if (hasItem && isEquipped) {
                    frameColor = JUtility::TColor(255, 255, 0, 255);
                }
                mpPauseFramePane->setBlackWhite(JUtility::TColor(0, 0, 0, 0), frameColor);
                mpPauseFramePane->draw(cellX + 24.0f, cellY + 24.0f, 48.0f, 48.0f, false, false, false);
            }

            J2DPicture* staticIcon = NULL;
            if (row == 3 && col == 2) staticIcon = mpBugsIconPane;
            if (row == 3 && col == 3) staticIcon = mpSkillsIconPane;
            if (row == 4 && col == 1) staticIcon = mpPoeIconPane;
            if (row == 4 && col == 2) staticIcon = mpFishIconPane;
            if (row == 4 && col == 3) staticIcon = mpLettersIconPane;

            u8 iconAlpha = hasItem ? 255 : 80;

            if (staticIcon != NULL) {
                gzSetup2DContext();
                f32 itemSize = (mIsEntered && isSelected) ? 56.0f : 48.0f;
                if (row == 4 && col == 1) {
                    iconAlpha = dComIfGs_getPohSpiritNum() > 0 ? 255 : 80;
                }
                if (row == 4 && col == 2) {
                    bool anyFish = false;
                    for (int f = 0; f < FISH_COUNT; f++) {
                        if (dComIfGs_getFishNum(f) > 0) { anyFish = true; break; }
                    }
                    iconAlpha = anyFish ? 255 : 80;
                }
                if (row == 4 && col == 3) {
                    iconAlpha = dMeter2Info_getRecieveLetterNum() > 0 ? 255 : 80;
                }
                staticIcon->setAlpha(iconAlpha);
                f32 sizeOff = (itemSize - 48.0f) / 2.0f;
                if (row == 3 && col == 3) {
                    f32 scrollW = itemSize * 32.0f / 80.0f;
                    f32 scrollH = itemSize;
                    f32 scrollX = cellX + 48.0f - scrollW / 2.0f;
                    f32 scrollY = cellY + 24.0f - sizeOff;
                    staticIcon->rotate(scrollW / 2.0f, scrollH / 2.0f, ROTATE_Z, 45.0f);
                    staticIcon->draw(scrollX, scrollY, scrollW, scrollH, false, false, false);
                } else {
                    staticIcon->draw(cellX + 24.0f - sizeOff, cellY + 24.0f - sizeOff,
                                     itemSize, itemSize, false, false, false);
                }

                if (row == 4 && col == 1) {
                    u8 poeCount = dComIfGs_getPohSpiritNum();
                    char numStr[8];
                    sprintf(numStr, "%d", poeCount);
                    gzTextBox* poeText = gzTextBox_allocate();
                    f32 fontSize = (mIsEntered && isSelected) ? 16.0f : 14.0f;
                    poeText->setFontSize(fontSize, fontSize);
                    poeText->setString(numStr);
                    f32 textCenter = cellX + 48.0f;
                    f32 textX = textCenter - 305.0f;
                    f32 textY = cellY + 76.0f;
                    poeText->draw(textX, textY, COLOR_WHITE, HBIND_CENTER);
                    gzTextBox_free(poeText);

                    if (inPoeEditMode() && mpHaihai != NULL) {
                        mpHaihai->_execute(0);
                        mpHaihai->setScale(0.5f);
                        u8 arrowFlags = ARROW_LEFT | ARROW_RIGHT;
                        if (poeCount == 0) arrowFlags &= ~ARROW_LEFT;
                        if (poeCount >= 60) arrowFlags &= ~ARROW_RIGHT;
                        mpHaihai->drawHaihai(arrowFlags, textCenter, textY - 5.0f,
                                             40.0f, 0.0f);
                    }
                }
            } else {
                gzSetup2DContext();
                f32 itemSize = (mIsEntered && isSelected) ? 56.0f : 48.0f;
                f32 sizeOff = (itemSize - 48.0f) / 2.0f;
                for (int k = 0; k < 3; k++) {
                    if (mpPauseItemTex[row][col][k] != NULL) {
                        mpPauseItemTex[row][col][k]->setAlpha(iconAlpha);
                        mpPauseItemTex[row][col][k]->draw(cellX + 24.0f - sizeOff,
                                                          cellY + 24.0f - sizeOff,
                                                          itemSize, itemSize, false, false, false);
                    }
                }

                if (row == 3 && col == 0) {
                    u16 rupees = dComIfGs_getRupee();
                    char numStr[8];
                    sprintf(numStr, "%d", rupees);

                    f32 fontSize = (mIsEntered && isSelected) ? 16.0f : 14.0f;
                    f32 textCenter = cellX + 48.0f;
                    f32 textX = textCenter - 305.0f;
                    f32 textY = cellY + 76.0f;

                    gzSetup2DContext();
                    gzTextBox* rupeeText = gzTextBox_allocate();
                    rupeeText->setFontSize(fontSize, fontSize);
                    rupeeText->setString(numStr);
                    rupeeText->draw(textX, textY, COLOR_WHITE, HBIND_CENTER);
                    gzTextBox_free(rupeeText);

                    if (inRupeeEditMode() && mpHaihai != NULL) {
                        mpHaihai->_execute(0);
                        mpHaihai->setScale(0.5f);
                        u8 arrowFlags = ARROW_LEFT | ARROW_RIGHT;
                        u16 maxRupee = dComIfGs_getRupeeMax();
                        if (rupees == 0) arrowFlags &= ~ARROW_LEFT;
                        if (rupees >= maxRupee) arrowFlags &= ~ARROW_RIGHT;
                        mpHaihai->drawHaihai(arrowFlags, textCenter, textY - 5.0f,
                                             40.0f, 0.0f);
                    }
                }
            }

            if (isSelected && mIsEntered && !inSkillSubMenu() && !inBugSubMenu() &&
                !inLetterSubMenu() && !inFishSubMenu() && gzInfo_isCursorTypeTP() && gzInfo_getTPCursor() != NULL) {
                if (mpPauseFramePane != NULL) {
                    mpPauseFramePane->mBounds.f.x = 48.0f;
                    mpPauseFramePane->mBounds.f.y = 48.0f;
                    gzInfo_getTPCursor()->setPos(cellX + 49.0f, cellY + 49.0f, (J2DPane*)mpPauseFramePane, false);
                } else {
                    gzInfo_getTPCursor()->setPos(cellX + 49.0f, cellY + 49.0f);
                }
                gzInfo_getTPCursor()->setParam(1.0f, 1.0f, 0.1f, 0.6f, 0.5f);
                gzInfo_getTPCursor()->draw();
            }
        }
    }

    if (isSkillSlotSelected() || inSkillSubMenu()) {
        drawSkillSubMenu();
    }
    if (isBugSlotSelected() || inBugSubMenu()) {
        drawBugSubMenu();
    }
    if (isLetterSlotSelected() || inLetterSubMenu()) {
        drawLetterSubMenu();
    }
    if (isFishSlotSelected() || inFishSubMenu()) {
        drawFishSubMenu();
    }
}

void gzInventoryMenu_c::drawPauseMenu() {
    if (!mPauseMenuInitialized && mIsEntered) {
        initPauseMenu();
    }
    if (!mPauseMenuInitialized) {
        return;
    }
    drawPauseMenuContent();
}
