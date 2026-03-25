#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz.h"
#include "d/actor/d_a_alink.h"
#include "d/d_com_inf_game.h"
#include "d/d_select_cursor.h"
#include "gz/gz_menu_main.h"
#include "gz/gz_setup_wizard.h"
#include "gz/gz_utility_draw.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRAramArchive.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "SSystem/SComponent/c_counter.h"
#include "dolphin/gx/GXCull.h"
#include "dolphin/gx/GXGet.h"
#include <cmath>

#include "umbra/umbra_gdb.h"

gzInfo_c g_gzInfo;

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
    mSettings.mOnline.mStateStreaming = false;
    mSettings.mOnline.mServerIP = umbraNet::makeIP(192, 168, 86, 30);
    mSettings.mOnline.mServerPort = 52224; // 0x00CC00
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

int gzInfo_c::storeSettings() {
    u8 data[sizeof(gzConfigHeader_s) + sizeof(gzSettings_s)];

    gzConfigHeader_s cfg;
    cfg.version = GZ_SAVE_VERSION;
    cfg.settingsOffset = sizeof(gzConfigHeader_s);
    memset(cfg.reserved, 0, sizeof(cfg.reserved));
    memcpy(data, &cfg, sizeof(gzConfigHeader_s));
    memcpy(data + cfg.settingsOffset, &mSettings, sizeof(gzSettings_s));

    umbraStorage* storage;
#ifndef __REVOLUTION_SDK__
    if (umbraHasUmbraSupport()) {
        storage = &mSD;
    } else
#endif
    {
        storage = &mMemCard;
    }

    bool useSD = (storage == &mSD);
    int result = storage->write(data, sizeof(data));
    if (result != 0) {
        gzInfo_sendNotification(useSD ? "save FAILED (sd)" : "save FAILED (memcard)");
        return -1;
    }

    gzInfo_sendNotification(useSD ? "saved to sd!" : "saved to memcard!");
    gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
    return 0;
}

int gzInfo_c::loadSettings() {
    u8 data[sizeof(gzConfigHeader_s) + sizeof(gzSettings_s)];

    umbraStorage* storage;
#ifndef __REVOLUTION_SDK__
    if (umbraHasUmbraSupport()) {
        storage = &mSD;
    } else
#endif
    {
        storage = &mMemCard;
    }

    bool useSD = (storage == &mSD);
    int result = storage->read(data, sizeof(data));
    if (result != 0) {
        gzInfo_sendNotification(useSD ? "load FAILED (sd)" : "load FAILED (memcard)");
        return -1;
    }

    gzConfigHeader_s cfg;
    memcpy(&cfg, data, sizeof(gzConfigHeader_s));
    if (cfg.version == 0) {
        gzInfo_sendNotification(useSD ? "load FAILED (not found, sd)" : "load FAILED (not found, memcard)");
        return -1;
    }
    if (cfg.version != GZ_SAVE_VERSION) {
        OSReport("TPGZ: outdated save version %d (expected %d)\n",
                 cfg.version, GZ_SAVE_VERSION);
        gzInfo_sendNotification(useSD ? "load FAILED (version, sd)" : "load FAILED (version, memcard)");
        return -1;
    }
    memcpy(&mSettings, data + cfg.settingsOffset, sizeof(gzSettings_s));
    gzInfo_sendNotification(useSD ? "loaded from sd!" : "loaded from memcard!");
    gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
    return 0;
}

int gzInfo_c::deleteSettings() {
    umbraStorage* storage;
#ifndef __REVOLUTION_SDK__
    if (umbraHasUmbraSupport()) {
        storage = &mSD;
    } else
#endif
    {
        storage = &mMemCard;
    }

    bool useSD = (storage == &mSD);
    int result = storage->remove();
    if (result != 0) {
        gzInfo_sendNotification(useSD ? "delete FAILED (sd)" : "delete FAILED (memcard)");
        return -1;
    }

    gzInfo_sendNotification(useSD ? "deleted from sd!" : "deleted from memcard!");
    gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
    return 0;
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
            mpBannerBg = gzCopyArchiveTexture(msgArc, "i4_gra.bti", gfxHeap);
            mpSwirl = gzCopyArchiveTexture(msgArc, "tt_gold_uzu_long2.bti", gfxHeap);
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
                *btnPtrs[i] = gzCopyArchiveTexture(main2dArc, btnNames[i], gfxHeap);
            }
        }
        break;
    }
    case 2: {
        JKRArchive* buttonArc = dComIfGp_getMeterButtonArchive();
        if (buttonArc != NULL) {
            JKRHeapOverrideScope btnScope(gfxHeap);
            mpBtnLRBase = gzCopyArchiveTexture(buttonArc, "tt_zelda_button_l_base.bti", gfxHeap);
        }

        JKRArchive* ringArc = dComIfGp_getRingResArchive();
        if (ringArc != NULL) {
            JKRHeapOverrideScope scope(gfxHeap);
            mpBtnLText = gzCopyArchiveTexture(ringArc, "tt_zelda_button_l_text.bti", gfxHeap);
            mpBtnRText = gzCopyArchiveTexture(ringArc, "tt_zelda_button_r_text.bti", gfxHeap);
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

#ifndef __REVOLUTION_SDK__
            umbraDetectPlatform();
#endif
            int settingsResult = loadSettings();

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

    umbra_gdb_poll();
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

    {
        static bool wasStreaming = false;

        if (mSettings.mOnline.mStateStreaming && !wasStreaming) {
            mNet.connect(mSettings.mOnline.mServerIP, mSettings.mOnline.mServerPort);
            wasStreaming = true;
        } else if (!mSettings.mOnline.mStateStreaming && wasStreaming) {
            mNet.disconnect();
            wasStreaming = false;
        }

        if (wasStreaming) {
            daAlink_c* link = daAlink_getAlinkActorClass();
            if (link != NULL) {
                // Packet payload: [1B player_id][1B msg_type=STATE][2B len][state data]
                // State data: [3x f32 pos][3x s16 angle][f32 speed][u16 action]
                u8 pkt[4 + 24];
                pkt[0] = 0;    // player_id (server assigns)
                pkt[1] = 0x01; // MSG_STATE
                pkt[2] = 0;    // payload len high
                pkt[3] = 24;   // payload len low

                u8* d = pkt + 4;
                f32 px = link->current.pos.x;
                f32 py = link->current.pos.y;
                f32 pz = link->current.pos.z;
                memcpy(d + 0,  &px, 4);
                memcpy(d + 4,  &py, 4);
                memcpy(d + 8,  &pz, 4);
                d[12] = (link->shape_angle.x >> 8) & 0xFF;
                d[13] = link->shape_angle.x & 0xFF;
                d[14] = (link->shape_angle.y >> 8) & 0xFF;
                d[15] = link->shape_angle.y & 0xFF;
                d[16] = (link->shape_angle.z >> 8) & 0xFF;
                d[17] = link->shape_angle.z & 0xFF;
                f32 spd = link->speedF;
                memcpy(d + 18, &spd, 4);
                d[22] = (link->mProcID >> 8) & 0xFF;
                d[23] = link->mProcID & 0xFF;

                mNet.stateWrite(pkt, sizeof(pkt));
            }

            u8 recvBuf[4 + 24];
            int recvLen = mNet.stateRead(recvBuf, sizeof(recvBuf));
            if (recvLen >= 28) {
                u8 playerID = recvBuf[0];
                u8* rd = recvBuf + 4;
                f32 rx, ry, rz, rspd;
                memcpy(&rx, rd + 0, 4);
                memcpy(&ry, rd + 4, 4);
                memcpy(&rz, rd + 8, 4);
                s16 rAngle = (rd[14] << 8) | rd[15];
                memcpy(&rspd, rd + 18, 4);
                OSReport("TPGZ RECV: p%d (%.0f,%.0f,%.0f) a=%d s=%.1f\n",
                         playerID, rx, ry, rz, rAngle, rspd);
            }
        }
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

    return 1;
}

int gzInfo_c::draw() {
    static const u32 SCISSOR_PADDING = 8;

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

        drawMenuFrame(baseAlpha, theme);

        if (mpIcon != NULL) mpIcon->draw(mIconXPos, mIconYPos, mIconWidth, mIconHeight, false, false, false);
        if (mpHeader != NULL) mpHeader->draw(mHeaderXPos, mHeaderYPos, mSettings.mTextColor);

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

        drawButtonHints();

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

void gzInfo_c::drawMenuFrame(u8 baseAlpha, u32 theme) {
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

    {
        f32 boxPadding = HIGHLIGHT_INSET + 2.0f;
        f32 boxTop = separatorY;
        f32 boxBottom = mBackgroundYPos + mBackgroundHeight - boxPadding;
        f32 boxRight = mBackgroundXPos + mBackgroundWidth - boxPadding;
        f32 boxLeft = (mSeparatorXPos > mBackgroundXPos + boxPadding) ? mSeparatorXPos : mBackgroundXPos + boxPadding;

        if (mSeparatorXPos > mBackgroundXPos + HIGHLIGHT_INSET) {
            f32 separatorBottom = boxBottom;
            gzDrawVerticalLine(mSeparatorXPos, separatorY, separatorBottom, 2.0f, separatorColor);
        }

        GXColor boxColor = gzGetThemedBorderColor(theme, (u8)((baseAlpha * 90) / 255));
        gzDrawFilledRect(boxLeft, boxTop, boxRight - boxLeft, boxBottom - boxTop, boxColor);
    }
}

void gzInfo_c::drawButtonHints() {
    f32 iconY = mBackgroundYPos + 21.0f;
    f32 textY = mBackgroundYPos + 30.0f;
    bool inMainMenu = (mCursor.x == 0);

    f32 hintStartX = mSeparatorVisibleX + 20.0f;
    f32 btnSize = 16.0f;
    f32 letterSizeAB = 10.0f;
    f32 letterSizeXY = 8.0f;
    f32 letterSizeZ = 6.0f;
    f32 letterOffsetAB = (btnSize - letterSizeAB) / 2.0f;
    f32 letterOffsetXY = (btnSize - letterSizeXY) / 2.0f;
    f32 letterOffsetZ = (btnSize - letterSizeZ) / 2.0f;

    static const JUtility::TColor colorA(0, 200, 80, 255);
    static const JUtility::TColor colorB(200, 60, 60, 255);
    static const JUtility::TColor colorXY(180, 180, 180, 255);
    static const JUtility::TColor colorZ(100, 100, 200, 255);

    if (inMainMenu) {
        f32 iconX = hintStartX;
        f32 btnY = iconY - btnSize / 2;
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
            f32 btnY = iconY - btnSize / 2;
            f32 btnWidth = btnSize;
            if (hints.hints[i].button == GZ_BTN_L || hints.hints[i].button == GZ_BTN_R) {
                bool isRBtn = (hints.hints[i].button == GZ_BTN_R);
                f32 lrWidth = 27.0f;
                f32 lrHeight = 16.0f;
                f32 lrY = iconY - lrHeight / 2 + 2.0f;
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
}
