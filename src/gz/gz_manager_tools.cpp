#include "d/actor/d_a_alink.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_event.h"
#include "d/d_event_manager.h"
#include "m_Do/m_Do_controller_pad.h"
#include "SSystem/SComponent/c_counter.h"

#include "gz/gz.h"
#include "gz/gz_textbox.h"
#include "gz/gz_utility_notification.h"
#include "gz/gz_utility_world_text.h"
#include "gz/gz_utility_draw.h"

#include <cmath>
#include <cstdio>

#define FREECAM_ROTATION_SPEED 0.002
#define FREECAM_FAST_SPEED 4.0
#define FREECAM_SPEED 0.5
#define FREECAM_TRIGGER_DEADZONE 20

static const u8 METAMORPHOSE_ANM_LENGTH = 56;

void gzToolsMng_c::executeElevatorEscape() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link == NULL) return;
    if (!daAlink_c::checkStageName("R_SP110")) return;
    if (link->current.pos.x > -1400.0f || link->current.pos.x < -1600.0f) return;
    if (link->current.pos.z < 4000.0f || link->current.pos.z > 4400.0f) return;

    char buf[20];

    switch (link->mProcID) {
    case daAlink_c::PROC_TALK:
        mElevatorEscape.prevAction = daAlink_c::PROC_TALK;
        break;
    case daAlink_c::PROC_METAMORPHOSE:
        if (mElevatorEscape.prevAction == daAlink_c::PROC_TALK) {
            mElevatorEscape.metamorphoseStartFrame = cCt_getFrameCount();
        }
        if ((gzPad::getTrig() & PAD_BUTTON_A)) {
            s32 elapsed = cCt_getFrameCount() - mElevatorEscape.metamorphoseStartFrame;
            snprintf(buf, sizeof(buf), "early by %df", METAMORPHOSE_ANM_LENGTH - elapsed);
            gzInfo_sendNotification(buf, gzNotification_c::NOTIFY_WARNING);
        }
        mElevatorEscape.prevAction = daAlink_c::PROC_METAMORPHOSE;
        break;
    case daAlink_c::PROC_WAIT:
        mElevatorEscape.lateRollFrame = 0;
        mElevatorEscape.targetFrame = cCt_getFrameCount();
        break;
    case daAlink_c::PROC_MOVE:
    case daAlink_c::PROC_WAIT_TURN:
    case daAlink_c::PROC_MOVE_TURN:
        if ((gzPad::getTrig() & PAD_BUTTON_A)) {
            mElevatorEscape.lateRollFrame = cCt_getFrameCount();
        }
        break;
    case daAlink_c::PROC_FRONT_ROLL:
        if (mElevatorEscape.prevAction != daAlink_c::PROC_FRONT_ROLL) {
            if (mElevatorEscape.lateRollFrame == 0) {
                gzInfo_sendNotification("got it", gzNotification_c::NOTIFY_INFO);
            } else {
                snprintf(buf, sizeof(buf), "late by %df",
                         mElevatorEscape.lateRollFrame - mElevatorEscape.targetFrame);
                gzInfo_sendNotification(buf, gzNotification_c::NOTIFY_ERROR);
            }
        }
        mElevatorEscape.prevAction = daAlink_c::PROC_FRONT_ROLL;
        break;
    default:
        mElevatorEscape.lateRollFrame = 0;
        break;
    }
}

void gzToolsMng_c::executeFreeCam() {
    dCamera_c* camera = dCam_getBody();
    dEvt_control_c* event = dComIfGp_getEvent();

    if (camera == NULL || event == NULL) {
        return;
    }

    cXyz* cam_pos = &camera->mEye;
    cXyz* cam_target = &camera->mCenter;

    // Freeze the game to prevent control stick inputs from moving Link
    event->mEventStatus = 1;

    // Lock the camera to allow for its movement
    dComIfGp_getEventManager().setCameraPlay(1);

    if (!mFreeCam.initialized) {
        mFreeCam.savedState.center = *cam_target;
        mFreeCam.savedState.eye = *cam_pos;
        mFreeCam.savedState.fovy = camera->mFovy;
        mFreeCam.savedState.bank = camera->mBank;

        f32 dx = cam_target->x - cam_pos->x;
        f32 dy = cam_target->y - cam_pos->y;
        f32 dz = cam_target->z - cam_pos->z;

        mFreeCam.yaw = atan2f(dz, dx);
        f32 horizontal = sqrtf(dx * dx + dz * dz);
        mFreeCam.pitch = atan2f(dy, horizontal);

        mFreeCam.initialized = true;
    }

    interface_of_controller_pad& pad = mDoCPd_c::getCpadInfo(0);
    f32 stickY = pad.mMainStickPosY * 72.0f;
    f32 stickX = pad.mMainStickPosX * 72.0f;
    f32 cStickY = pad.mCStickPosY * 59.0f;
    f32 cStickX = pad.mCStickPosX * 59.0f;

    f32 trigL = pad.mTriggerLeft * 150.0f;
    f32 trigR = pad.mTriggerRight * 150.0f;

    f32 verticalDisp = 0.0f;
    if (trigL >= FREECAM_TRIGGER_DEADZONE) {
        verticalDisp += trigL;
    }

    if (trigR >= FREECAM_TRIGGER_DEADZONE) {
        verticalDisp -= trigR;
    }

    f32 moveDy = stickY * sinf(mFreeCam.pitch) + verticalDisp;
    f32 moveDx = stickY * cosf(mFreeCam.yaw) * cosf(mFreeCam.pitch) - stickX * sinf(mFreeCam.yaw);
    f32 moveDz = stickY * sinf(mFreeCam.yaw) * cosf(mFreeCam.pitch) + stickX * cosf(mFreeCam.yaw);

    f32 speed = gzPad::getHoldZ() ? FREECAM_FAST_SPEED : FREECAM_SPEED;

    cam_pos->x += speed * moveDx;
    cam_pos->y += speed * moveDy;
    cam_pos->z += speed * moveDz;

    cam_target->x = cam_pos->x + cosf(mFreeCam.yaw) * cosf(mFreeCam.pitch);
    cam_target->z = cam_pos->z + sinf(mFreeCam.yaw) * cosf(mFreeCam.pitch);
    cam_target->y = cam_pos->y + sinf(mFreeCam.pitch);

    // Call Reset to update viewCache and internal camera state
    camera->Reset(*cam_target, *cam_pos);

    mFreeCam.yaw -= cStickX * FREECAM_ROTATION_SPEED;
    mFreeCam.yaw = fmodf(mFreeCam.yaw + 2.0f * M_PI, 2.0f * M_PI);

    f32 newPitch = mFreeCam.pitch + cStickY * FREECAM_ROTATION_SPEED;
    f32 maxPitch = M_PI / 2.0f - 0.1f;
    f32 minPitch = -M_PI / 2.0f + 0.1f;

    if (newPitch > maxPitch) {
        mFreeCam.pitch = maxPitch;
    } else if (newPitch < minPitch) {
        mFreeCam.pitch = minPitch;
    } else {
        mFreeCam.pitch = newPitch;
    }
}

void gzToolsMng_c::executeMoveLink() {
    if (gzCheckComboToggle(g_gzInfo.mSettings.mCommandCombos.mMoveLink, mMoveLink.comboHeld)) {
        mMoveLink.active = !mMoveLink.active;
    }
}

void gzToolsMng_c::executeTeleport() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    dCamera_c* camera = dCam_getBody();

    if (gzCheckComboToggle(g_gzInfo.mSettings.mCommandCombos.mTeleportSave, mTeleport.saveComboHeld)) {
        if (link != NULL && camera != NULL) {
            mTeleport.camera.center = camera->mCenter;
            mTeleport.camera.eye = camera->mEye;
            mTeleport.camera.fovy = camera->mFovy;
            mTeleport.camera.bank = camera->mBank;
            mTeleport.linkPos = link->current.pos;
            mTeleport.linkAngle = link->shape_angle;
        }
        gzClearButtonInput();
    }

    if (gzCheckComboToggle(g_gzInfo.mSettings.mCommandCombos.mTeleportLoad, mTeleport.loadComboHeld)) {
        if (link != NULL && camera != NULL) {
            camera->Reset(mTeleport.camera.center, mTeleport.camera.eye,
                          mTeleport.camera.fovy, mTeleport.camera.bank.Val());
            link->current.pos = mTeleport.linkPos;
            link->shape_angle = mTeleport.linkAngle;
        }
        gzClearButtonInput();
    }
}

static const s32 EBMB_PERFECT_FRAME = 4;
static const s32 EBMB_LATE_LIMIT = 10;
static const u8 RESULT_DISPLAY_FRAMES = 60;
static const u8 COROTD_GOAL_FRAME = 10;
static const u8 COROTD_WINDOW_FRAMES = 20;

void gzToolsMng_c::executeCoroTD() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link == NULL) {
        mCoroTD.frameCount = 0;
        mCoroTD.goalHit = false;
        mCoroTD.timerStarted = false;
        return;
    }

    if (dComIfGp_isPauseFlag()) {
        return;
    }

    if (!mCoroTD.timerStarted && (gzPad::getTrig() & PAD_BUTTON_A) &&
        daAlink_c::checkStageName("F_SP108")) {
        mCoroTD.timerStarted = true;
        mCoroTD.frameCount = 0;
        mCoroTD.goalHit = false;
    }

    if (mCoroTD.timerStarted) {
        mCoroTD.frameCount++;

        bool itemPressed = (gzPad::getTrig() & (PAD_BUTTON_Y | PAD_BUTTON_X)) != 0;

        if (mCoroTD.frameCount < COROTD_WINDOW_FRAMES) {
            if (!mCoroTD.goalHit && itemPressed) {
                char buf[20];
                if (mCoroTD.frameCount < COROTD_GOAL_FRAME) {
                    snprintf(buf, sizeof(buf), "-%df",
                             COROTD_GOAL_FRAME - mCoroTD.frameCount);
                    gzInfo_sendNotification(buf, gzNotification_c::NOTIFY_WARNING);
                } else if (mCoroTD.frameCount == COROTD_GOAL_FRAME) {
                    gzInfo_sendNotification("got it", gzNotification_c::NOTIFY_INFO);
                } else {
                    snprintf(buf, sizeof(buf), "+%df",
                             mCoroTD.frameCount - COROTD_GOAL_FRAME);
                    gzInfo_sendNotification(buf, gzNotification_c::NOTIFY_ERROR);
                }
                mCoroTD.goalHit = true;
            }
        } else {
            mCoroTD.frameCount = 0;
            mCoroTD.goalHit = false;
            mCoroTD.timerStarted = false;
        }
    }
}

void gzToolsMng_c::executeEBMB() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link == NULL) {
        return;
    }

    if (link->mProcID == daAlink_c::PROC_CUT_DOWN) {
        if (mEBMB.prevAction == daAlink_c::PROC_ATN_ACTOR_WAIT) {
            mEBMB.frameDelta = 0;
        }

        bool ibOn = link->checkEquipHeavyBoots() != 0;

        if (!dComIfGp_isPauseFlag()) {
            mEBMB.frameDelta++;

            if (!ibOn && mEBMB.ibOnLastFrame) {
                if (mEBMB.frameDelta == EBMB_PERFECT_FRAME) {
                    gzInfo_sendNotification("got it", gzNotification_c::NOTIFY_INFO);
                } else if (mEBMB.frameDelta > EBMB_PERFECT_FRAME &&
                           mEBMB.frameDelta <= EBMB_LATE_LIMIT) {
                    char buf[20];
                    snprintf(buf, sizeof(buf), "+%df", mEBMB.frameDelta - EBMB_PERFECT_FRAME);
                    gzInfo_sendNotification(buf, gzNotification_c::NOTIFY_ERROR);
                }
            } else if (!ibOn && mEBMB.frameDelta == 3) {
                gzInfo_sendNotification("equip iron boots", gzNotification_c::NOTIFY_WARNING);
            }

            mEBMB.ibOnLastFrame = ibOn;
        }
    }

    mEBMB.prevAction = link->mProcID;
}

void gzToolsMng_c::executeRollChecker() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link == NULL || dComIfGs_getTransformStatus() != TF_STATUS_HUMAN) {
        mRollChecker.frameDelta = 0;
        mRollChecker.resultTimer = 0;
        return;
    }

    if (dComIfGp_isPauseFlag()) {
        return;
    }

    if (mRollChecker.resultTimer > 0) {
        mRollChecker.resultTimer--;
    }

    bool rolling = (link->mProcID == daAlink_c::PROC_FRONT_ROLL);
    bool aPressed = (gzPad::getTrig() & PAD_BUTTON_A) != 0;

    if (rolling) {
        if (mRollChecker.prevAction == daAlink_c::PROC_DIVE_JUMP) {
            mRollChecker.endFrame = 15;
            mRollChecker.earlyFrame = 9;
            mRollChecker.lateFrame = 20;
        } else {
            mRollChecker.endFrame = 20;
            mRollChecker.earlyFrame = 14;
            mRollChecker.lateFrame = 25;
        }

        if (mRollChecker.frameDelta == 0) {
            mRollChecker.frameDelta = 1;
        }

        if (aPressed) {
            if (mRollChecker.frameDelta == mRollChecker.endFrame) {
                snprintf(mRollChecker.resultText, sizeof(mRollChecker.resultText), "<3");
                mRollChecker.resultColor = COLOR_GREEN;
                mRollChecker.resultTimer = RESULT_DISPLAY_FRAMES;
                mRollChecker.frameDelta = 0;
            } else if (mRollChecker.frameDelta > mRollChecker.earlyFrame &&
                       mRollChecker.frameDelta < mRollChecker.endFrame) {
                snprintf(mRollChecker.resultText, sizeof(mRollChecker.resultText), "-%df",
                         mRollChecker.endFrame - mRollChecker.frameDelta);
                mRollChecker.resultColor = COLOR_BLUE;
                mRollChecker.resultTimer = RESULT_DISPLAY_FRAMES;
            } else if (mRollChecker.frameDelta > mRollChecker.endFrame &&
                       mRollChecker.frameDelta <= mRollChecker.lateFrame) {
                snprintf(mRollChecker.resultText, sizeof(mRollChecker.resultText), "+%df",
                         mRollChecker.frameDelta - mRollChecker.endFrame);
                mRollChecker.resultColor = COLOR_RED;
                mRollChecker.resultTimer = RESULT_DISPLAY_FRAMES;
                mRollChecker.frameDelta = 0;
            }
        }

        if (mRollChecker.frameDelta != 0) {
            mRollChecker.frameDelta++;
        }
    } else {
        if (aPressed && mRollChecker.frameDelta > mRollChecker.endFrame &&
            mRollChecker.frameDelta <= mRollChecker.lateFrame) {
            snprintf(mRollChecker.resultText, sizeof(mRollChecker.resultText), "+%df",
                     mRollChecker.frameDelta - mRollChecker.endFrame);
            mRollChecker.resultColor = COLOR_RED;
            mRollChecker.resultTimer = RESULT_DISPLAY_FRAMES;
            mRollChecker.frameDelta = 0;
        }

        if (mRollChecker.frameDelta > mRollChecker.endFrame &&
            mRollChecker.frameDelta <= mRollChecker.lateFrame) {
            mRollChecker.frameDelta++;
        } else {
            mRollChecker.frameDelta = 0;
        }

        mRollChecker.prevAction = link->mProcID;
    }

    if (mRollChecker.resultTimer > 0) {
        mRollChecker.worldPos = link->current.pos;
    }
}

void gzToolsMng_c::execute() {
    if (gzInfo_isTool_FreeCam()) {
        if (gzCheckComboToggle(g_gzInfo.mSettings.mCommandCombos.mFreeCamToggle, mFreeCam.comboHeld)) {
            mFreeCam.active = !mFreeCam.active;
            if (!mFreeCam.active) {
                dCamera_c* camera = dCam_getBody();

                if (camera != NULL) {
                    camera->Reset(mFreeCam.savedState.center, mFreeCam.savedState.eye,
                                  mFreeCam.savedState.fovy, mFreeCam.savedState.bank.Val());
                }

                dEvt_control_c* event = dComIfGp_getEvent();

                if (event != NULL) {
                    event->mEventStatus = 0;
                }

                dComIfGp_getEventManager().setCameraPlay(0);
                mFreeCam.initialized = false;
            }
        }

        if (mFreeCam.active) {
            executeFreeCam();
        }
    } else if (mFreeCam.active) {
        dCamera_c* camera = dCam_getBody();

        if (camera != NULL) {
            camera->Reset(mFreeCam.savedState.center, mFreeCam.savedState.eye,
                          mFreeCam.savedState.fovy, mFreeCam.savedState.bank.Val());
        }

        dEvt_control_c* event = dComIfGp_getEvent();

        if (event != NULL) {
            event->mEventStatus = 0;
        }

        dComIfGp_getEventManager().setCameraPlay(0);
        mFreeCam.active = false;
        mFreeCam.initialized = false;
    }

    if (gzInfo_isTool_MoveLink()) {
        executeMoveLink();
    } else if (mMoveLink.active) {
        mMoveLink.active = false;
    }

    if (gzInfo_isTool_CoroTD()) executeCoroTD();
    if (gzInfo_isTool_ElevatorEscape()) executeElevatorEscape();
    if (gzInfo_isTool_EndingBlowMoonBoots()) executeEBMB();
    if (gzInfo_isTool_RollChecker()) executeRollChecker();
    if (gzInfo_isTool_Teleport()) executeTeleport();
}

void gzToolsMng_c::drawRollChecker() {
    if (mRollChecker.pText == NULL) {
        mRollChecker.pText = gzTextBox_allocate();
    }
    if (mRollChecker.pText == NULL || mRollChecker.resultTimer == 0 || dComIfGp_isPauseFlag()) {
        return;
    }

    gzDrawWorldText(mRollChecker.pText, mRollChecker.worldPos, 15.0f,
                    mRollChecker.resultText, mRollChecker.resultColor, 1.5f, -0.5f);
}

void gzToolsMng_c::drawLinkInfo() {
    daAlink_c* player = daAlink_getAlinkActorClass();
    if (player == NULL)
        return;

    const int BASE_X = 400;
    const int BASE_Y = 200;
    const int LINE_HEIGHT = 20;

    // TODO: do we like prints or textboxes here more?
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 0), COLOR_WHITE, "time: %02d:%02d", dKy_getdaytime_hour(), dKy_getdaytime_minute());
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 1), COLOR_WHITE, "action: %d", player->mProcID);
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 2), COLOR_WHITE, "pos x: %.4f", player->current.pos.x);
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 3), COLOR_WHITE, "pos y: %.4f", player->current.pos.y);
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 4), COLOR_WHITE, "pos z: %.4f", player->current.pos.z);
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 5), COLOR_WHITE, "angle: %d", (u16)player->shape_angle.y);
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 6), COLOR_WHITE, "v-angle: %d", player->mBodyAngle.x);
    gzPrint(BASE_X, BASE_Y + (LINE_HEIGHT * 7), COLOR_WHITE, "speed: %.4f", player->speedF);
}

void gzToolsMng_c::draw() {
    if (gzInfo_isTool_RollChecker()) drawRollChecker();

    if (gzInfo_isTool_LinkDebugInfo()) {
        drawLinkInfo();
    }
}
