#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz.h"
#include "gz/gz_menu_main.h"
#include "gz/gz_setup_wizard.h"
#include "gz/gz_utility_draw.h"
#include "SSystem/SComponent/c_counter.h"
#include "gz/gz_utility_notification.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_select_cursor.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRAramArchive.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "m_Do/m_Do_MemCard.h"
#include "dolphin/card.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/gx/GXCull.h"
#include "dolphin/gx/GXGet.h"
#include "dolphin/gx/GXTransform.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GXTev.h"
#include "dolphin/gx/GXLighting.h"
#include "m_Do/m_Do_mtx.h"
#include <cmath>

class gzCapture_c : public dDlst_base_c {
public:
    virtual void draw() {
        if (mFlag == 0) {
            return;
        } else if (mFlag == 1) {
            mFlag = 3;
            GXSetTexCopySrc(0, 0, FB_WIDTH, FB_HEIGHT);
            GXSetTexCopyDst(FB_WIDTH / 2, FB_HEIGHT / 2, (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_ENABLE);
            GXCopyTex(mDoGph_gInf_c::getFrameBufferTex(), GX_FALSE);
            GXPixModeSync();
            dComIfGp_onPauseFlag();
        } else {
            GXTexObj tex;
            GXInitTexObj(&tex, mDoGph_gInf_c::getFrameBufferTex(), FB_WIDTH / 2, FB_HEIGHT / 2,
                        (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&tex, GX_TEXMAP0);
            GXSetNumChans(0);
            GXSetNumTexGens(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            const GXColor color = {0, 0, 0, mAlpha};
            GXSetTevColor(GX_TEVREG0, color);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetZCompLoc(GX_TRUE);
            GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
            GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
            GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
            GXSetFogRangeAdj(GX_FALSE, 0, NULL);
            GXSetCullMode(GX_CULL_NONE);
            GXSetDither(GX_TRUE);
            GXLoadPosMtxImm(g_mDoMtx_identity, GX_PNMTX0);
            GXSetCurrentMtx(0);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGB8, 0);

            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3s16(mDoGph_gInf_c::getMinX(), mDoGph_gInf_c::getMinY(), 0);
            GXTexCoord2s8(0, 0);
            GXPosition3s16(mDoGph_gInf_c::getMaxX(), mDoGph_gInf_c::getMinY(), 0);
            GXTexCoord2s8(1, 0);
            GXPosition3s16(mDoGph_gInf_c::getMaxX(), mDoGph_gInf_c::getMaxY(), 0);
            GXTexCoord2s8(1, 1);
            GXPosition3s16(mDoGph_gInf_c::getMinX(), mDoGph_gInf_c::getMaxY(), 0);
            GXTexCoord2s8(0, 1);
            GXEnd();
        }
    }

    virtual ~gzCapture_c() {}

    static const u8 CAPTURE_DIM_ALPHA = 128;

    gzCapture_c() {
        mFlag = 0;
        mAlpha = CAPTURE_DIM_ALPHA;
    }

    void setCaptureFlag() { mFlag = 1; }
    void disable() { mFlag = 0; }
    bool isCapturing() { return mFlag != 0; }

private:
    u8 mFlag;
    u8 mAlpha;
};

gzInfo_c g_gzInfo;

// Automation state for Python scripts - address dumped on boot
gzAutoState_s g_gzAutoState = {
    0x475A4155,  // magic = "GZAU"
    false,       // menuVisible
    false,       // optionMode
    0, 0,        // cursorX, cursorY
    3, 0, 0, 0,  // warpTypeIdx (OVERWORLD default), stage, room, spawn
    false,       // warpExecuted
    {0},         // currentStage
    0            // faderStatus
};

void gzDVDLoadFile(const char* filePath, void* buffer, int length, int offset) {
    DVDFileInfo ATTRIBUTE_ALIGN(32) fileInfo;
    if (DVDOpen(filePath, &fileInfo)) {
        int bytesRead = DVDReadPrio(&fileInfo, buffer, length, offset, 2);
        if (bytesRead > 0) {
            DVDClose(&fileInfo);
        } else {
            OSReport("no bytes read!\n");
        }
    } else {
        OSReport("failed to open file %s\n", filePath);
    }
}

void gzInfo_c::startIconPreload() {
    static const char* PATHS[] = {
        "/gz/check.bti", "/gz/x_mark.bti", "/gz/bg.bti", "/gz/icon_atlas.bti"
    };
    static const u32 SIZES[] = {544, 544, 54432, 13856};
    JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
    for (int i = 0; i < PRELOAD_COUNT; i++) {
        if (!DVDOpen(PATHS[i], &mPreloadFileInfos[i])) continue;
        mpPreloadBufs[i] = heap->alloc(SIZES[i], 32);
        if (mpPreloadBufs[i] == NULL) {
            DVDClose(&mPreloadFileInfos[i]);
            continue;
        }
        mPreloadAsyncPending[i] = true;
        DVDReadAsync(&mPreloadFileInfos[i], mpPreloadBufs[i], SIZES[i], 0, NULL);
    }
}

void gzInfo_c::pollIconPreload() {
    if (mPreloadsComplete) return;
    bool allDone = true;
    for (int i = 0; i < PRELOAD_COUNT; i++) {
        if (mPreloadAsyncPending[i]) {
            s32 status = DVDGetFileInfoStatus(&mPreloadFileInfos[i]);
            if (status == DVD_STATE_END || status == DVD_STATE_FATAL_ERROR) {
                DVDClose(&mPreloadFileInfos[i]);
                mPreloadAsyncPending[i] = false;
                if (status == DVD_STATE_FATAL_ERROR && mpPreloadBufs[i] != NULL) {
                    gzHeap(GZ_GROUP_GRAPHICS)->free(mpPreloadBufs[i]);
                    mpPreloadBufs[i] = NULL;
                }
            } else {
                allDone = false;
            }
        }
    }
    if (!allDone) return;
    mPreloadsComplete = true;
    JKRHeap* heap = gzHeap(GZ_GROUP_GRAPHICS);
    if (mpPreloadBufs[0] != NULL) {
        mpCheckIcon = new (heap, 4) J2DPicture((ResTIMG*)mpPreloadBufs[0]);
        mpCheckIcon->setBlackWhite(JUtility::TColor(0, 0, 0, 0),
                                   JUtility::TColor(76, 175, 80, 255));
    }
    if (mpPreloadBufs[1] != NULL) {
        mpXMarkIcon = new (heap, 4) J2DPicture((ResTIMG*)mpPreloadBufs[1]);
        mpXMarkIcon->setBlackWhite(JUtility::TColor(0, 0, 0, 0),
                                   JUtility::TColor(244, 67, 54, 255));
    }
    if (mpPreloadBufs[2] != NULL) {
        mpBackground = new (heap, 4) J2DPicture((ResTIMG*)mpPreloadBufs[2]);
        mpBackground->setWhite(JUtility::TColor(55, 52, 40, 255));
    }
}

void gzInfo_c::loadDefaultSettings() {
    mSettings.mTextColor = COLOR_GOLD_DROP;
    mSettings.mCommandCombos.mGorgeVoid = (PAD_TRIGGER_L | PAD_TRIGGER_Z);
    mSettings.mCommandCombos.mMoveLink = (PAD_TRIGGER_L | PAD_TRIGGER_R | PAD_BUTTON_Y);
    mSettings.mCommandCombos.mMoonJump = (PAD_TRIGGER_R | PAD_BUTTON_A);
    mSettings.mCommandCombos.mTeleportSave = (PAD_TRIGGER_R | PAD_BUTTON_UP);
    mSettings.mCommandCombos.mTeleportLoad = (PAD_TRIGGER_R | PAD_BUTTON_DOWN);
    mSettings.mCommandCombos.mFreeCamToggle = (PAD_TRIGGER_Z | PAD_BUTTON_B | PAD_BUTTON_A);
    mSettings.mDropShadows = true;
    mSettings.mMenuPausesGame = true;
    setCursorType(1);
    mpFont = mDoExt_getMesgFont();
    mCursor.x = 0;
    mCursor.y = 0;
    mSettings.mMenuSfx = true;

    mStickTriggers = 0;
    mRepeatDirection = 0;
    mRepeatCounter = 0;
    mButtonRepeatTriggers = 0;
    mButtonRepeatState = 0;
    mButtonRepeatCounter = 0;

    mDisplay = false;
    mWasPausedOnOpen = false;
    mpCapture = NULL;

    mBackgroundXPos = 5.0f;
    mBackgroundYPos = 5.0f;
    mBackgroundWidth = 595.0f;
    mBackgroundHeight = 415.0f;

    mBorderAnimTimer = 0.0f;
    mBorderHighlightAlpha = 200;

    mSeparatorVisibleX = mBackgroundXPos + 165.0f;
    mSeparatorHiddenX = mBackgroundXPos - 10.0f;
    mSeparatorXPos = mSeparatorVisibleX;

    mIconXPos = mBackgroundXPos + 8.0f;
    mIconYPos = mBackgroundYPos + 7.0f;
    mIconWidth = 30.0f;
    mIconHeight = 30.0f;

    mHeaderXPos = mBackgroundXPos + 40.0f;
    mHeaderYPos = mBackgroundYPos + 30.0f;
}


void gzInfo_c::startInit() {
    mInitPhase = INIT_PHASE_SETUP_RESOURCES;
}

void gzInfo_c::loadMenuResources() {
    while (!mMenuResourcesLoaded) {
        loadMenuResourcesBatch();
    }
}

void gzInfo_c::loadMenuResourcesBatch() {
    if (mMenuResourcesLoaded) return;

    JKRHeap* gfxHeap = gzHeap(GZ_GROUP_GRAPHICS);

    switch (mMenuLoadStep) {
    case 0: {
        ResTIMG* icon;
        {
            JKRHeapOverrideScope scope(gfxHeap);
            icon = (ResTIMG*)dComIfGp_getMain2DArchive()->getResource('TIMG', "midona64.bti");
        }
        if (icon != NULL) {
            mpIcon = new (gfxHeap, 4) J2DPicture(icon);
        }

        JKRArchive* msgArc = dComIfGp_getMsgArchive(4);
        if (msgArc != NULL) {
            JKRHeapOverrideScope scope(gfxHeap);

            ResTIMG* bgSrc = (ResTIMG*)msgArc->getResource('TIMG', "i4_gra.bti");
            if (bgSrc != NULL) {
                u32 bgImgSize = GXGetTexBufferSize(bgSrc->width, bgSrc->height, bgSrc->format,
                                                    bgSrc->mipmapEnabled, bgSrc->mipmapCount);
                u32 bgSize = bgSrc->imageOffset + bgImgSize;
                void* bgBuf = gfxHeap->alloc(bgSize, 32);
                memcpy(bgBuf, bgSrc, bgSize);
                mpBannerBg = new (gfxHeap, 4) J2DPicture((ResTIMG*)bgBuf);
            }

            ResTIMG* swirlSrc = (ResTIMG*)msgArc->getResource('TIMG', "tt_gold_uzu_long2.bti");
            if (swirlSrc != NULL) {
                u32 imgSize = GXGetTexBufferSize(swirlSrc->width, swirlSrc->height,
                                                  swirlSrc->format, swirlSrc->mipmapEnabled,
                                                  swirlSrc->mipmapCount);
                u32 totalSize = swirlSrc->imageOffset + imgSize;
                void* buf = gfxHeap->alloc(totalSize, 32);
                memcpy(buf, swirlSrc, totalSize);
                mpSwirl = new (gfxHeap, 4) J2DPicture((ResTIMG*)buf);
            }
        }
        break;
    }
    case 1: {
        JKRArchive* main2dArc = dComIfGp_getMain2DArchive();
        if (main2dArc != NULL) {
            const char* btnNames[] = {
                "tt_zelda_button_ab_maru.bti",
                "tt_zelda_button_a_text.bti",
                "tt_zelda_button_b_text.bti",
                "tt_zelda_button_x_base.bti",
                "tt_zelda_button_x_text.bti",
                "tt_zelda_button_y_base.bti",
                "tt_zelda_button_y_text.bti",
                "im_zelda_button_z_base.bti",
                "im_zelda_button_z_text.bti"
            };
            J2DPicture** btnPtrs[] = {
                &mpBtnABBase, &mpBtnAText, &mpBtnBText,
                &mpBtnXBase, &mpBtnXText, &mpBtnYBase, &mpBtnYText,
                &mpBtnZBase, &mpBtnZText
            };
            JKRHeapOverrideScope main2dScope(gfxHeap);
            for (int i = 0; i < 9; i++) {
                ResTIMG* src = (ResTIMG*)main2dArc->getResource('TIMG', btnNames[i]);
                if (src != NULL) {
                    u32 imgSize = GXGetTexBufferSize(src->width, src->height, src->format,
                                                      src->mipmapEnabled, src->mipmapCount);
                    u32 totalSize = src->imageOffset + imgSize;
                    void* buf = JKRHeap::alloc(totalSize, 32, gfxHeap);
                    memcpy(buf, src, totalSize);
                    *btnPtrs[i] = new (gfxHeap, 4) J2DPicture((ResTIMG*)buf);
                }
            }
        }
        break;
    }
    case 2: {
        JKRArchive* buttonArc = dComIfGp_getMeterButtonArchive();
        if (buttonArc != NULL) {
            JKRHeapOverrideScope btnScope(gfxHeap);

            ResTIMG* src = (ResTIMG*)buttonArc->getResource('TIMG', "tt_zelda_button_l_base.bti");
            if (src != NULL) {
                u32 imgSize = GXGetTexBufferSize(src->width, src->height, src->format,
                                                  src->mipmapEnabled, src->mipmapCount);
                u32 totalSize = src->imageOffset + imgSize;
                void* buf = gfxHeap->alloc(totalSize, 32);
                if (buf != NULL) {
                    memcpy(buf, src, totalSize);
                    mpBtnLRBase = new (gfxHeap, 4) J2DPicture((ResTIMG*)buf);
                }
            }
        }

        JKRArchive* ringArc = dComIfGp_getRingResArchive();
        if (ringArc != NULL) {
            ResTIMG* src;
            JKRHeapOverrideScope scope(gfxHeap);
            src = (ResTIMG*)ringArc->getResource('TIMG', "tt_zelda_button_l_text.bti");

            if (src != NULL) {
                u32 imgSize = GXGetTexBufferSize(src->width, src->height, src->format,
                                                  src->mipmapEnabled, src->mipmapCount);
                u32 totalSize = src->imageOffset + imgSize;
                void* buf = gfxHeap->alloc(totalSize, 32);
                if (buf != NULL) {
                    memcpy(buf, src, totalSize);
                    mpBtnLText = new (gfxHeap, 4) J2DPicture((ResTIMG*)buf);
                }
            }

            src = (ResTIMG*)ringArc->getResource('TIMG', "tt_zelda_button_r_text.bti");

            if (src != NULL) {
                u32 imgSize = GXGetTexBufferSize(src->width, src->height, src->format,
                                                  src->mipmapEnabled, src->mipmapCount);
                u32 totalSize = src->imageOffset + imgSize;
                void* buf = gfxHeap->alloc(totalSize, 32);
                if (buf != NULL) {
                    memcpy(buf, src, totalSize);
                    mpBtnRText = new (gfxHeap, 4) J2DPicture((ResTIMG*)buf);
                }
            }
        }
        break;
    }
    case 3: {
        mpHeader = gzTextBox_allocate();
        mpHeader->setString("tpgz v2.0.0");

        mpMainMenu = new (gzHeap(GZ_GROUP_MENU), 4) gzMainMenu_c();

        mpNotification = new (gzHeap(GZ_GROUP_UI), 4) gzNotification_c();

        mpTPCursor = new (gzHeap(GZ_GROUP_GRAPHICS), 4) dSelect_cursor_c(2, 1.0f, NULL);
        mpTPCursor->setParam(0.96f, 0.84f, 0.03f, 0.5f, 0.5f);
        mpTPCursor->setAlphaRate(1.0f);

        mpMenuDescription = gzTextBox_allocate();
        mMenuOption = false;
        mTopLine = 0;
        mVisibleLines = 15;

        mpButtonHintText = gzTextBox_allocate();

        mInputWaitTimer = 2;

        gzChangeMenu(mpMainMenu->getMenu(0));

        mMenuResourcesLoaded = true;
        break;
    }
    }
    mMenuLoadStep++;
}

int gzInfo_c::_delete() {
    OSReport("deleting gzInfo_c\n");

    delete mpSetupWizard;
    mpSetupWizard = NULL;

    for (int i = 0; i < PRELOAD_COUNT; i++) {
        if (mPreloadAsyncPending[i]) {
            DVDCancel(&mPreloadFileInfos[i].cb);
            DVDClose(&mPreloadFileInfos[i]);
            mPreloadAsyncPending[i] = false;
        }
        if (mpPreloadBufs[i] != NULL) {
            gzHeap(GZ_GROUP_GRAPHICS)->free(mpPreloadBufs[i]);
            mpPreloadBufs[i] = NULL;
        }
    }
    delete mpCheckIcon;
    mpCheckIcon = NULL;
    delete mpXMarkIcon;
    mpXMarkIcon = NULL;

    delete mpIcon;
    mpIcon = NULL;

    gzTextBox_free(mpHeader);
    mpHeader = NULL;

    delete mpBackground;
    mpBackground = NULL;

    delete mpBannerBg;
    mpBannerBg = NULL;

    delete mpSwirl;
    mpSwirl = NULL;

    delete mpBtnABBase;
    mpBtnABBase = NULL;
    delete mpBtnAText;
    mpBtnAText = NULL;
    delete mpBtnBText;
    mpBtnBText = NULL;
    delete mpBtnXBase;
    mpBtnXBase = NULL;
    delete mpBtnXText;
    mpBtnXText = NULL;
    delete mpBtnYBase;
    mpBtnYBase = NULL;
    delete mpBtnYText;
    mpBtnYText = NULL;
    delete mpBtnZBase;
    mpBtnZBase = NULL;
    delete mpBtnZText;
    mpBtnZText = NULL;
    delete mpBtnLRBase;
    mpBtnLRBase = NULL;
    delete mpBtnLText;
    mpBtnLText = NULL;
    delete mpBtnRText;
    mpBtnRText = NULL;

    mpCurrentMenu = NULL;

    delete mpMainMenu;
    mpMainMenu = NULL;

    delete mpNotification;
    mpNotification = NULL;

    delete mpTPCursor;
    mpTPCursor = NULL;

    gzTextBox_free(mpMenuDescription);
    mpMenuDescription = NULL;

    gzTextBox_free(mpButtonHintText);
    mpButtonHintText = NULL;

    return 1;
}

void gzInfo_c::updateStickTriggers() {
    static const f32 STICK_THRESHOLD = 0.5f;
    static const s16 REPEAT_DELAY = 12;  // Frames before repeat starts
    static const s16 REPEAT_RATE = 2;    // Frames between repeats

    // Get current direction from d-pad
    u32 currentDir = 0;
    u32 dpadHold = mDoCPd_c::m_gzPadInfo.mButtonFlags & (PAD_BUTTON_UP | PAD_BUTTON_DOWN | PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT);
    currentDir |= dpadHold;

    // Only use analog stick for menu navigation if menu pauses game is enabled
    // (otherwise stick passes through to game)
    if (gzInfo_isMenuPausesGame()) {
        f32 stickX = gzPad::getStickX();
        f32 stickY = gzPad::getStickY();

        if (stickY > STICK_THRESHOLD) currentDir |= PAD_BUTTON_UP;
        if (stickY < -STICK_THRESHOLD) currentDir |= PAD_BUTTON_DOWN;
        if (stickX < -STICK_THRESHOLD) currentDir |= PAD_BUTTON_LEFT;
        if (stickX > STICK_THRESHOLD) currentDir |= PAD_BUTTON_RIGHT;
    }

    mStickTriggers = 0;

    if (currentDir == 0) {
        // No direction held - reset
        mRepeatDirection = 0;
        mRepeatCounter = 0;
    } else if (currentDir != mRepeatDirection) {
        // New direction - trigger immediately and start counting
        mStickTriggers = currentDir;
        mRepeatDirection = currentDir;
        mRepeatCounter = 0;
    } else {
        // Same direction held - handle repeat
        mRepeatCounter++;
        if (mRepeatCounter == REPEAT_DELAY) {
            mStickTriggers = currentDir;
        } else if (mRepeatCounter > REPEAT_DELAY && (mRepeatCounter - REPEAT_DELAY) % REPEAT_RATE == 0) {
            mStickTriggers = currentDir;
        }
    }

    static const u32 BUTTON_REPEAT_MASK = PAD_BUTTON_X | PAD_BUTTON_Y;
    u32 currentButtons = mDoCPd_c::m_gzPadInfo.mButtonFlags & BUTTON_REPEAT_MASK;

    mButtonRepeatTriggers = 0;

    if (currentButtons == 0) {
        mButtonRepeatState = 0;
        mButtonRepeatCounter = 0;
    } else if (currentButtons != mButtonRepeatState) {
        mButtonRepeatTriggers = currentButtons;
        mButtonRepeatState = currentButtons;
        mButtonRepeatCounter = 0;
    } else {
        mButtonRepeatCounter++;
        if (mButtonRepeatCounter == REPEAT_DELAY) {
            mButtonRepeatTriggers = currentButtons;
        } else if (mButtonRepeatCounter > REPEAT_DELAY && (mButtonRepeatCounter - REPEAT_DELAY) % REPEAT_RATE == 0) {
            mButtonRepeatTriggers = currentButtons;
        }
    }
}

int gzInfo_c::execute() {
    if (!mGZInitialized) {
        switch (mInitPhase) {
        case INIT_PHASE_IDLE:
            return 0;
        case INIT_PHASE_SETUP_RESOURCES: {
            OSReport("creating gzInfo_c\n");
            gzCreateHeap();

            for (int i = 0; i < PRELOAD_COUNT; i++) {
                mpPreloadBufs[i] = NULL;
                mPreloadAsyncPending[i] = false;
            }
            mPreloadsComplete = false;
            mpCheckIcon = NULL;
            mpXMarkIcon = NULL;

            startIconPreload();
            loadDefaultSettings();

            mpIcon = NULL;
            mpBackground = NULL;
            mpBannerBg = NULL;
            mpSwirl = NULL;
            mpBtnABBase = NULL;
            mpBtnAText = NULL;
            mpBtnBText = NULL;
            mpBtnXBase = NULL;
            mpBtnXText = NULL;
            mpBtnYBase = NULL;
            mpBtnYText = NULL;
            mpBtnZBase = NULL;
            mpBtnZText = NULL;
            mpBtnLRBase = NULL;
            mpBtnLText = NULL;
            mpBtnRText = NULL;
            mpHeader = NULL;
            mpMainMenu = NULL;
            mpNotification = NULL;
            mpTPCursor = NULL;
            mpMenuDescription = NULL;
            mpButtonHintText = NULL;
            mpCurrentMenu = NULL;
            mpSetupWizard = NULL;

            mMenuResourcesLoaded = false;
            mMenuLoadStep = 0;

            OSReport("tpgz auto: 0x%08X\n", (u32)&g_gzAutoState);

#ifndef __REVOLUTION_SDK__
            mIsNintendont = detectNintendont();
            OSReport("tpgz: nintendont detected = %d\n", mIsNintendont);
#endif
            int settingsResult = loadSettings();

            dComIfGp_setOxygen(OXYGEN_MAX);
            dComIfGp_setNowOxygen(OXYGEN_MAX);
            dComIfGp_setMaxOxygen(OXYGEN_MAX);

            mGZInitialized = true;
            mInitPhase = INIT_PHASE_DONE;

            if (settingsResult != 0) {
                mpSetupWizard = new (gzHeap(GZ_GROUP_UI), 4) gzSetupWizard_c();
                dComIfGp_onPauseFlag();
            } else if (mSettings.mBootToMenu) {
                loadMenuResources();
                mDisplay = true;
            }
            return 0;
        }
        }
        return 0;
    }

    pollIconPreload();

    if (mpSetupWizard != NULL) {
        updateStickTriggers();
        mpSetupWizard->execute();
        if (mpSetupWizard->isComplete()) {
            bool bootToMenu = mpSetupWizard->mBootToMenu;
            delete mpSetupWizard;
            mpSetupWizard = NULL;
            dComIfGp_offPauseFlag();
            if (bootToMenu) {
                loadMenuResources();
                mDisplay = true;
            }
        }
        return 1;
    }

    bool wasDisplayed = mDisplay;

    updateStickTriggers();

    if (gzPad::getHoldL() && gzPad::getHoldR() && (gzPad::getTrig() & PAD_BUTTON_DOWN)) {
        if (!mMenuResourcesLoaded) {
            loadMenuResources();
        }
        mDisplay = !mDisplay;
        gzClearControllerInput();

        if (mDisplay)
            mInputWaitTimer = 2;
    }

    if (!wasDisplayed && mDisplay) {
        mWasPausedOnOpen = dComIfGp_isPauseFlag();
        if (isMenuPausesGame() && !mWasPausedOnOpen && mpCapture == NULL) {
            mpCapture = new (gzHeap(GZ_GROUP_UI), 4) gzCapture_c();
            mpCapture->setCaptureFlag();
        }
        if (mpCurrentMenu != NULL) {
            mpCurrentMenu->onHighlight();
        }
    }

    if (mDisplay) {
        mBorderAnimTimer += 0.07f;
        f32 sineVal = sinf(mBorderAnimTimer);
        mBorderHighlightAlpha = (u8)(168 + (s32)(87.0f * sineVal));

        if (mInputWaitTimer != 0) {
            mInputWaitTimer--;
            return 1;
        }

        if (mpMainMenu != NULL && mCursor.x == 0) mpMainMenu->execute();
        if (mpCurrentMenu != NULL && mCursor.x > 0) mpCurrentMenu->execute();

        if (!isMenuPausesGame() && mpCapture != NULL) {
            delete mpCapture;
            mpCapture = NULL;
            if (!mWasPausedOnOpen) {
                dComIfGp_offPauseFlag();
            }
        } else if (isMenuPausesGame() && mpCapture == NULL && !mWasPausedOnOpen && !dComIfGp_isPauseFlag()) {
            mpCapture = new (gzHeap(GZ_GROUP_UI), 4) gzCapture_c();
            mpCapture->setCaptureFlag();
        }
    } else {
        mCheatsMng.execute();
        mToolsMng.execute();
        mSceneMng.execute();
        mSaveLoaderMng.execute();
    }

    if (wasDisplayed && !mDisplay) {
        if (mpCurrentMenu != NULL) {
            mpCurrentMenu->onUnhighlight();
        }
        if (mpCapture != NULL) {
            delete mpCapture;
            mpCapture = NULL;
        }
        if (!mWasPausedOnOpen) {
            dComIfGp_offPauseFlag();
        }
    }

    // Update automation state for Python scripts
    g_gzAutoState.menuVisible = mDisplay;
    g_gzAutoState.optionMode = mMenuOption;
    g_gzAutoState.cursorX = mCursor.x;
    g_gzAutoState.cursorY = mCursor.y;
    strncpy(g_gzAutoState.currentStage, dComIfGp_getStartStageName(), 7);
    g_gzAutoState.currentStage[7] = '\0';
    g_gzAutoState.faderStatus = mDoGph_gInf_c::getFader()->getStatus();

    return 1;
}

// Scissor padding to prevent drawing right up to menu edge
static const u32 SCISSOR_PADDING = 8;

int gzInfo_c::draw() {
    if (!mGZInitialized) {
        if (mpFont != NULL) {
            gzSetup2DContext();
            J2DTextBox loadingText;
            loadingText.setFont(mpFont);
            loadingText.setFontSize(24.0f, 24.0f);
            loadingText.setString("tpgz loading...");
            JUtility::TColor white(255, 255, 255, 255);
            loadingText.setCharColor(white);
            loadingText.setGradColor(white);
            loadingText.draw(0.0f, 210.0f, 608.0f, HBIND_CENTER);
        }
        return 0;
    }

    if (mpSetupWizard != NULL) {
        gzSetup2DContext();
        mpSetupWizard->draw();
        return 1;
    }

    // Draw capture directly (dims the background game)
    if (mpCapture != NULL && mpCapture->isCapturing()) {
        mpCapture->draw();
    }

    if (mDisplay) {
        u8 baseAlpha = isMenuPausesGame() ? 255 : 128;
        u32 theme = mSettings.mTextColor;

        if (mpBackground != NULL) {
            mpBackground->setAlpha(baseAlpha);
            mpBackground->draw(mBackgroundXPos, mBackgroundYPos, mBackgroundWidth, mBackgroundHeight, false, false, false);
        }

        static const f32 OUTER_THICKNESS = 3.0f;
        GXColor outerShadow = {30, 28, 20, baseAlpha};
        gzDrawRectOutline(mBackgroundXPos, mBackgroundYPos,
                          mBackgroundWidth, mBackgroundHeight,
                          OUTER_THICKNESS, outerShadow);

        static const f32 GOLD_THICKNESS = 2.0f;
        static const f32 GOLD_INSET = OUTER_THICKNESS;
        GXColor goldBorder = gzGetThemedBorderColor(theme, baseAlpha);
        gzDrawRectOutline(mBackgroundXPos + GOLD_INSET, mBackgroundYPos + GOLD_INSET,
                          mBackgroundWidth - (GOLD_INSET * 2), mBackgroundHeight - (GOLD_INSET * 2),
                          GOLD_THICKNESS, goldBorder);

        static const f32 HIGHLIGHT_THICKNESS = 2.0f;
        static const f32 HIGHLIGHT_INSET = GOLD_INSET + GOLD_THICKNESS;
        u8 highlightAlpha = (u8)((mBorderHighlightAlpha * baseAlpha) / 255);
        GXColor highlightBorder = gzGetThemedHighlightColor(theme, highlightAlpha);
        gzDrawRectOutline(mBackgroundXPos + HIGHLIGHT_INSET, mBackgroundYPos + HIGHLIGHT_INSET,
                          mBackgroundWidth - (HIGHLIGHT_INSET * 2), mBackgroundHeight - (HIGHLIGHT_INSET * 2),
                          HIGHLIGHT_THICKNESS, highlightBorder);

        if (mpMainMenu != NULL) {
            if (mpMainMenu->isTransitioning()) {
                u32 currentFrame = cCt_getFrameCount();
                f32 sepStartX = mpMainMenu->isTransitionForward() ? mSeparatorVisibleX : mSeparatorHiddenX;
                f32 sepEndX = mpMainMenu->isTransitionForward() ? mSeparatorHiddenX : mSeparatorVisibleX;
                mSeparatorXPos = calcSlidePosition(currentFrame, mpMainMenu->getTransitionStart(),
                                                   sepStartX, sepEndX, mpMainMenu->getTransitionDuration());

                // Sync submenu position for tab connector drawing
                if (mpCurrentMenu != NULL) {
                    f32 subStartX = mpMainMenu->isTransitionForward() ? mpMainMenu->getSubHiddenX() : mpMainMenu->getSubVisibleX();
                    f32 subEndX = mpMainMenu->isTransitionForward() ? mpMainMenu->getSubVisibleX() : mpMainMenu->getSubHiddenX();
                    mpCurrentMenu->setXPos(calcSlidePosition(currentFrame, mpMainMenu->getTransitionStart(),
                                                             subStartX, subEndX, mpMainMenu->getTransitionDuration()));
                }
            } else {
                mSeparatorXPos = (mCursor.x == 0) ? mSeparatorVisibleX : mSeparatorHiddenX;
            }
        }

        f32 separatorY = mBackgroundYPos + 40.0f;
        f32 separatorLeft = mBackgroundXPos + HIGHLIGHT_INSET + 2.0f;
        f32 separatorRight = mBackgroundXPos + mBackgroundWidth - HIGHLIGHT_INSET - 2.0f;
        GXColor separatorColor = gzGetThemedSeparatorColor(theme, baseAlpha);
        gzDrawHorizontalLine(separatorLeft, separatorRight, separatorY, 1.0f, separatorColor);

        // Draw submenu content box - left edge follows separator, clamped to menu bounds
        {
            f32 boxPadding = HIGHLIGHT_INSET + 2.0f;
            f32 boxTop = separatorY;
            f32 boxBottom = mBackgroundYPos + mBackgroundHeight - boxPadding;
            f32 boxRight = mBackgroundXPos + mBackgroundWidth - boxPadding;
            // Clamp left edge: follows separator when visible, snaps to left edge when separator is hidden
            f32 boxLeft = (mSeparatorXPos > mBackgroundXPos + boxPadding) ? mSeparatorXPos : mBackgroundXPos + boxPadding;

        if (mSeparatorXPos > mBackgroundXPos + HIGHLIGHT_INSET) {
            f32 separatorBottom = boxBottom;
            gzDrawVerticalLine(mSeparatorXPos, separatorY, separatorBottom, 2.0f, separatorColor);
        }

            // Semi-transparent filled box (flat rectangle)
            GXColor boxColor = gzGetThemedBorderColor(theme, (u8)((baseAlpha * 90) / 255));
            gzDrawFilledRect(boxLeft, boxTop, boxRight - boxLeft, boxBottom - boxTop, boxColor);
        }

        if (mpIcon != NULL) mpIcon->draw(mIconXPos, mIconYPos, mIconWidth, mIconHeight, false, false, false);
        if (mpHeader != NULL) mpHeader->draw(mHeaderXPos, mHeaderYPos, mSettings.mTextColor);

        bool inMainMenu = (mCursor.x == 0);

        f32 circleRadius = 9.0f;
        f32 iconY = mBackgroundYPos + 21.0f;
        f32 textY = mBackgroundYPos + 30.0f;

        f32 bannerX = mSeparatorVisibleX;
        f32 bannerY = mBackgroundYPos + 8.0f;
        f32 bannerW = mBackgroundXPos + mBackgroundWidth - bannerX - 8.0f;
        f32 bannerH = 30.0f;

        if (mpBannerBg != NULL) {
            u8 bgAlpha = (u8)((baseAlpha * 180) / 255);
            mpBannerBg->setAlpha(bgAlpha);
            mpBannerBg->setWhite(JUtility::TColor(60, 55, 45, 255));
            mpBannerBg->draw(bannerX, bannerY, bannerW, bannerH, false, false, false);
        }

        if (mpSwirl != NULL) {
            GXColor sColor = gzGetThemedBorderColor(theme, baseAlpha);
            mpSwirl->setWhite(JUtility::TColor(sColor.r, sColor.g, sColor.b, 255));
            mpSwirl->setAlpha(baseAlpha);

            f32 centerY = bannerY + bannerH / 2.0f;
            f32 pairS = 14.0f;
            f32 bigS = 17.0f;

            mpSwirl->draw(bannerX, centerY - pairS, pairS, pairS,
                          false, false, false);
            mpSwirl->draw(bannerX, centerY, pairS, pairS,
                          true, false, false);
            mpSwirl->draw(bannerX - bigS + 3.0f, centerY - bigS / 2.0f,
                          bigS, bigS, true, false, false);
        }

        f32 hintStartX = mSeparatorVisibleX + 20.0f;
        f32 btnSize = 16.0f;
        f32 letterSizeAB = 10.0f;
        f32 letterSizeXY = 8.0f;
        f32 letterSizeZ = 6.0f;
        f32 letterOffsetAB = (btnSize - letterSizeAB) / 2.0f;
        f32 letterOffsetXY = (btnSize - letterSizeXY) / 2.0f;
        f32 letterOffsetZ = (btnSize - letterSizeZ) / 2.0f;

        // Gamecube Button Colors
        static const JUtility::TColor colorA(0, 200, 80, 255);
        static const JUtility::TColor colorB(200, 60, 60, 255);
        static const JUtility::TColor colorXY(180, 180, 180, 255);
        static const JUtility::TColor colorZ(100, 100, 200, 255);

        if (inMainMenu) {
            f32 iconX = hintStartX;
            f32 btnY = iconY - btnSize/2;
            if (mpBtnABBase != NULL) {
                mpBtnABBase->setAlpha(255);
                mpBtnABBase->setWhite(colorA);
                mpBtnABBase->draw(iconX, btnY, btnSize, btnSize, false, false, false);
            }
            if (mpBtnAText != NULL) {
                mpBtnAText->setAlpha(255);
                mpBtnAText->draw(iconX + letterOffsetAB, btnY + letterOffsetAB, letterSizeAB, letterSizeAB, false, false, false);
            }
            if (mpButtonHintText != NULL) {
                mpButtonHintText->setFontSize(18.0f, 18.0f);
                mpButtonHintText->setString("Enter Menu");
                mpButtonHintText->draw(iconX + btnSize + 4.0f, textY, COLOR_WHITE);
            }
        } else if (mpCurrentMenu != NULL) {
            gzButtonHints_s hints = mpCurrentMenu->getButtonHints();
            f32 currentX = hintStartX;

            for (int i = 0; i < hints.count && i < 7; i++) {
                J2DPicture* base = NULL;
                J2DPicture* text = NULL;
                JUtility::TColor baseColor(255, 255, 255, 255);
                f32 lSize = letterSizeAB;
                f32 lOffset = letterOffsetAB;
                const char* btnLabel = NULL;
                switch (hints.hints[i].button) {
                case GZ_BTN_A:
                    base = mpBtnABBase;
                    text = mpBtnAText;
                    baseColor = colorA;
                    break;
                case GZ_BTN_B:
                    base = mpBtnABBase;
                    text = mpBtnBText;
                    baseColor = colorB;
                    break;
                case GZ_BTN_X:
                    base = mpBtnXBase;
                    text = mpBtnXText;
                    baseColor = colorXY;
                    lSize = letterSizeXY;
                    lOffset = letterOffsetXY;
                    break;
                case GZ_BTN_Y:
                    base = mpBtnYBase;
                    text = mpBtnYText;
                    baseColor = colorXY;
                    lSize = letterSizeXY;
                    lOffset = letterOffsetXY;
                    break;
                case GZ_BTN_Z:
                    base = mpBtnZBase;
                    text = mpBtnZText;
                    baseColor = colorZ;
                    lSize = letterSizeZ;
                    lOffset = letterOffsetZ;
                    break;
                case GZ_BTN_L:
                    base = mpBtnLRBase;
                    text = mpBtnLText;
                    break;
                case GZ_BTN_R:
                    base = mpBtnLRBase;
                    text = mpBtnRText;
                    break;
                }
                f32 btnY = iconY - btnSize/2;
                f32 btnWidth = btnSize;
                if (hints.hints[i].button == GZ_BTN_L || hints.hints[i].button == GZ_BTN_R) {
                    bool isRBtn = (hints.hints[i].button == GZ_BTN_R);
                    f32 lrWidth = 27.0f;
                    f32 lrHeight = 16.0f;
                    f32 lrY = iconY - lrHeight/2 + 2.0f;
                    if (base != NULL) {
                        base->setAlpha(255);
                        base->setWhite(colorXY);
                        base->draw(currentX, lrY, lrWidth, lrHeight, isRBtn, false, false);
                    }
                    if (text != NULL) {
                        f32 textWidth = 4.0f;
                        f32 textHeight = 7.0f;
                        f32 textX = currentX + (lrWidth - textWidth) / 2.0f + 1.0f;
                        f32 textY = lrY + (lrHeight - textHeight) / 2.0f - 2.0f;
                        text->setAlpha(255);
                        text->draw(textX, textY, textWidth, textHeight, false, false, false);
                    }
                    btnWidth = lrWidth;
                } else if (btnLabel != NULL) {
                    if (mpButtonHintText != NULL) {
                        mpButtonHintText->setFontSize(18.0f, 18.0f);
                        mpButtonHintText->setString(btnLabel);
                        mpButtonHintText->updateBounds();
                        mpButtonHintText->draw(currentX, textY, 0xAAAAAAFF);
                        btnWidth = mpButtonHintText->getWidth();
                    }
                } else {
                    if (base != NULL) {
                        base->setAlpha(255);
                        base->setWhite(baseColor);
                        base->draw(currentX, btnY, btnSize, btnSize, false, false, false);
                    }
                    if (text != NULL) {
                        text->setAlpha(255);
                        text->draw(currentX + lOffset, btnY + lOffset, lSize, lSize, false, false, false);
                    }
                }

                if (mpButtonHintText != NULL) {
                    mpButtonHintText->setFontSize(18.0f, 18.0f);
                    mpButtonHintText->setString(hints.hints[i].text);
                    mpButtonHintText->updateBounds();
                    f32 textX = currentX + btnWidth + 3.0f;
                    mpButtonHintText->draw(textX, textY, COLOR_WHITE);
                    currentX += btnWidth + 3.0f + mpButtonHintText->getWidth() + 8.0f;
                } else {
                    currentX += 90.0f;
                }
            }
        }

        u32 savedLeft, savedTop, savedWidth, savedHeight;
        GXGetScissor(&savedLeft, &savedTop, &savedWidth, &savedHeight);
        GXSetScissor((u32)mBackgroundXPos + SCISSOR_PADDING,
                     (u32)mBackgroundYPos + SCISSOR_PADDING,
                     (u32)mBackgroundWidth - (SCISSOR_PADDING * 2),
                     (u32)mBackgroundHeight - (SCISSOR_PADDING * 2));

        // Draw menus directly to avoid issues with deferred rendering
        if (mpMainMenu != NULL) mpMainMenu->draw();
        if (mpCurrentMenu != NULL) mpCurrentMenu->draw();

        GXSetScissor(savedLeft, savedTop, savedWidth, savedHeight);

        if (mpMenuDescription != NULL && mpMenuDescription->getStringPtr() != NULL && mpMenuDescription->getStringPtr()[0] != '\0') {
            f32 description_y = mBackgroundYPos + mBackgroundHeight + 15.0f;
            mpMenuDescription->draw(0.0f, description_y, gzInfo_getCursorColor(), HBIND_CENTER);
        }
    }

    // Draw any notifications
    if (mpNotification != NULL) mpNotification->draw();

    if (!mDisplay) {
        mToolsMng.draw();
    }

    return 1;
}

void gzSetup2DContext() {
    // Set up 2D orthographic projection for drawing J2DScreen-based elements.
    // This is necessary because GZ draws after the game's normal 2D render pass,
    // when the original graphics context (a stack-local ortho) is no longer valid.
    // We must also set the current graf port because J2DScreen::draw uses it.
    static J2DOrthoGraph sGzOrtho(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    sGzOrtho.setPort();
    dComIfGp_setCurrentGrafPort(&sGzOrtho);

    // Restore menu scissor after J2D setup (J2D resets scissor)
    if (g_gzInfo.mDisplay) {
        u32 left = (u32)g_gzInfo.mBackgroundXPos + SCISSOR_PADDING;
        u32 top = (u32)g_gzInfo.mBackgroundYPos + SCISSOR_PADDING;
        u32 width = (u32)g_gzInfo.mBackgroundWidth - (SCISSOR_PADDING * 2);
        u32 height = (u32)g_gzInfo.mBackgroundHeight - (SCISSOR_PADDING * 2);
        GXSetScissor(left, top, width, height);
    }
}

int gzInfo_c::storeSettingsMemcard() {
    CARDFileInfo file;
    int ret;

    ret = CARDProbeEx(0, NULL, NULL);
    if (ret != CARD_RESULT_READY) {
        return -1;
    }

    ret = CARDCreate(0, "tpgzcfg", SECTOR_SIZE, &file);
    if (ret == CARD_RESULT_READY || ret == CARD_RESULT_EXIST) {
        ret = CARDOpen(0, "tpgzcfg", &file);
        if (ret == CARD_RESULT_READY) {
            gzConfigHeader_s cfg;
            cfg.version = GZ_SAVE_VERSION;
            cfg.settingsOffset = sizeof(gzConfigHeader_s);

            memcpy(mDoMemCd_Ctrl_c::sTmpBuf, &cfg, sizeof(gzConfigHeader_s));
            memcpy(mDoMemCd_Ctrl_c::sTmpBuf + cfg.settingsOffset, &mSettings, sizeof(gzSettings_s));

            ret = CARDWrite(&file, mDoMemCd_Ctrl_c::sTmpBuf, SECTOR_SIZE, 0);
            if (ret == CARD_RESULT_READY) {
                OSReport("stored tpgz settings to memcard!\n");
                gzInfo_sendNotification("settings saved to memcard!");
            }

            CARDClose(&file);
        }
    }

    return ret;
}

int gzInfo_c::loadSettingsMemcard() {
    CARDFileInfo file;
    int ret;

    ret = CARDProbeEx(0, NULL, NULL);
    if (ret != CARD_RESULT_READY) {
        return -1;
    }

    ret = CARDOpen(0, "tpgzcfg", &file);
    if (ret == CARD_RESULT_READY) {
        ret = CARDRead(&file, mDoMemCd_Ctrl_c::sTmpBuf, SECTOR_SIZE, 0);
        if (ret == CARD_RESULT_READY) {
            OSReport("loaded tpgz settings from memcard!\n");
            gzInfo_sendNotification("settings loaded from memcard!");

            gzConfigHeader_s cfg;
            memcpy(&cfg, mDoMemCd_Ctrl_c::sTmpBuf, sizeof(gzConfigHeader_s));
            if (cfg.version != GZ_SAVE_VERSION) {
                OSReport("outdated tpgz save version!\n");
                return -1;
            }

            gzSettings_s settings;
            memcpy(&mSettings, mDoMemCd_Ctrl_c::sTmpBuf + cfg.settingsOffset, sizeof(gzSettings_s));
        }

        CARDClose(&file);
    } else {
        gzInfo_sendNotification("no memcard settings found!");
    }

    return ret;
}

int gzInfo_c::deleteSettingsMemcard() {
    CARDFileInfo file;
    int ret;

    ret = CARDProbeEx(0, NULL, NULL);
    if (ret != CARD_RESULT_READY) {
        return -1;
    }

    ret = CARDDelete(0, "tpgzcfg");
    if (ret == CARD_RESULT_READY) {
        OSReport("deleted tpgz settings from memcard!\n");
        gzInfo_sendNotification("memcard settings deleted!");
    } else {
        OSReport_Error("failed to delete tpgz settings from memcard!\n");
    }

    return ret;
}

void gzInfo_c::sendNotification(const char* msg) { 
    if (mpNotification != NULL) mpNotification->send(msg);
}

void gzInfo_c::sendNotification(const char* msg, int i_notificationType) {
    if (mpNotification != NULL) mpNotification->send(msg, (gzNotification_c::NotificationType)i_notificationType);
}

static JKRExpHeap* s_gzHeap = NULL;
static const u32 GZ_HEAP_SIZE = 0x100000;  // 1MB

void gzCreateHeap() {
    if (s_gzHeap != NULL) return;

    JKRExpHeap* archiveHeap = (JKRExpHeap*)mDoExt_getArchiveHeap();
    s_gzHeap = JKRExpHeap::create(GZ_HEAP_SIZE, archiveHeap, true);

    JKRAllocFromAram(0xC0000, JKRAramHeap::HEAD);  // 768KB test fill
}

void gzSetGzHeap(JKRHeap* heap) {
    s_gzHeap = (JKRExpHeap*)heap;
}

JKRHeap* gzGetGzHeap() {
    return s_gzHeap;
}

JKRHeap* gzHeap(gzGroupId_e groupId) {
    s_gzHeap->mCurrentGroupId = (u8)groupId;
    return s_gzHeap;
}
