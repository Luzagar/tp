#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz.h"
#include "d/actor/d_a_alink.h"

void gzCheatsMng_c::executeDisableItemTimer() {
    daItemBase_c::m_data.mWaitTime = ITEM_TIMER_DISABLED;
    mDisableItemTimer = true;
}

void gzCheatsMng_c::executeDisableWalls() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        link->mLinkAcch.SetWallNone();
        link->mLinkAcch.OnLineCheckNone();
        mDisableWalls = true;
    }
}

void gzCheatsMng_c::executeEnableItemTimer() {
    daItemBase_c::m_data.mWaitTime = ITEM_TIMER_DEFAULT;
    mDisableItemTimer = false;
}


void gzCheatsMng_c::executeFastBonkRecovery() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        daAlinkHIO_frontRoll_c0::m.mCrashAnm.mStartFrame = 50.0f;
        daAlinkHIO_frontRoll_c0::m.mCrashAnm.mSpeed = 0.0f;
        mFastBonkRecovery = true;
    }
}

void gzCheatsMng_c::executeFastMovement() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        daAlinkHIO_frontRoll_c0::m.mSpeedRate = 3.0f;
        daAlinkHIO_swim_c0::m.mUnderwaterMaxSpeed = 50;
        daAlinkHIO_swim_c0::m.mBackwardMaxSpeed = 50;
        daAlinkHIO_swim_c0::m.mStrafeMaxSpeed = 50;
        daAlinkHIO_swim_c0::m.mDashMaxSpeed = 50;
        daAlinkHIO_swim_c0::m.mForwardMaxSpeed = 50;
        daAlinkHIO_swim_c0::m.mUnderwaterFallMaxSpeed = 50;
        daAlinkHIO_swim_c0::m.mBootsMaxFallSpeed = -50;
        daAlinkHIO_swim_c0::m.mBootsGravity = -50;
        daAlinkHIO_wlMove_c0::m.mADashInitSpeed = 100;
        daAlinkHIO_wlMove_c0::m.mADashMaxSpeed = 100;
        daAlinkHIO_wlMove_c0::m.mADashInitSpeedSlow = 70;
        daAlinkHIO_wlMove_c0::m.mADashMaxSpeedSlow = 70;
        daAlinkHIO_wlMove_c0::m.mMaxSpeed = 50;
        mFastMovement = true;
    }
}

void gzCheatsMng_c::executeEnableWalls() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        link->mLinkAcch.ClrWallNone();
        link->mLinkAcch.OffLineCheckNone();
        mDisableWalls = false;
    }
}

void gzCheatsMng_c::executeInfiniteAir() {
    dComIfGp_setOxygen(OXYGEN_MAX);
    dComIfGp_setNowOxygen(OXYGEN_MAX);
    dComIfGp_setMaxOxygen(OXYGEN_MAX);
}

void gzCheatsMng_c::executeInfiniteArrows() {
    dComIfGs_setArrowNum(100);
}

void gzCheatsMng_c::executeInfiniteBombs() {
    // setting to 60 works on all bags regardless type / upgrade
    dComIfGs_setBombNum(0, 60);
    dComIfGs_setBombNum(1, 60);
    dComIfGs_setBombNum(2, 60);
}

void gzCheatsMng_c::executeInfiniteHearts() {
    // needs to be maxLifeGauge for great spin to still work without modification
    dComIfGs_setLife(dComIfGs_getMaxLifeGauge());
}

void gzCheatsMng_c::executeInfiniteOil() {
    dComIfGs_setOil(OIL_MAX);
}

void gzCheatsMng_c::executeInfiniteRupees() {
    dComIfGs_setRupee(1000);
}

void gzCheatsMng_c::executeInfiniteSlingshot() {
    dComIfGs_setPachinkoNum(dComIfGs_getPachinkoMax());
}

void gzCheatsMng_c::executeInvincibleLink() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        for (int i = 0; i < 3; i++) {
            link->mTgCyls[i].GetGObjInf()->OffTgSetBit();
            link->mTgCyls[i].GetGObjInf()->ClrTgHit();
        }

        if (link->checkWolf()) {
            link->mAtSph.GetGObjInf()->OffTgSetBit();
            link->mAtSph.GetGObjInf()->ClrTgHit();
        }
    }
}

void gzCheatsMng_c::executeMoonJump() {
    u32 combo = g_gzInfo.mSettings.mCommandCombos.mMoonJump;
    if (combo && ((gzPad::getHold() & combo) == combo)) {
        daAlink_c* link = daAlink_getAlinkActorClass();
        if (link) {
            fopAcM_GetSpeed_p(link)->y = MOON_JUMP_SPEED;
        }
    }
}

void gzCheatsMng_c::executeNoSinkSand() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        link->mSinkShapeOffset = 0.0f;
    }
}

void gzCheatsMng_c::executeSuperClawshot() {
    daAlink_c* link = daAlink_getAlinkActorClass();
    if (link != NULL) {
        daAlinkHIO_hookshot_c0::m.mShootSpeed = CLAWSHOT_SUPER_SHOOT_SPEED;
        daAlinkHIO_hookshot_c0::m.mMaxLength = CLAWSHOT_SUPER_MAX_LENGTH;
        daAlinkHIO_hookshot_c0::m.mReturnSpeed = CLAWSHOT_SUPER_RETURN_SPEED;
        daAlinkHIO_hookshot_c0::m.mStickReturnSpeed = CLAWSHOT_SUPER_STICK_RETURN_SPEED;
        mSuperClawshot = true;
    }
}

void gzCheatsMng_c::execute() {
    if (gzInfo_isCheat_FastBonkRecovery()) {
        executeFastBonkRecovery();
    } else if (mFastBonkRecovery) {
        daAlinkHIO_frontRoll_c0::m.mCrashAnm.mStartFrame = 3.0f;
        daAlinkHIO_frontRoll_c0::m.mCrashAnm.mSpeed = 0.8f;
        mFastBonkRecovery = false;
    }

    if (gzInfo_isCheat_FastMovement()) {
        executeFastMovement();
    } else if (mFastMovement) {
        daAlinkHIO_frontRoll_c0::m.mSpeedRate = 1.3f;
        daAlinkHIO_swim_c0::m.mUnderwaterMaxSpeed = 12;
        daAlinkHIO_swim_c0::m.mForwardMaxSpeed = 8;
        daAlinkHIO_swim_c0::m.mBackwardMaxSpeed = 6;
        daAlinkHIO_swim_c0::m.mStrafeMaxSpeed = 8;
        daAlinkHIO_swim_c0::m.mDashMaxSpeed = 13;
        daAlinkHIO_swim_c0::m.mUnderwaterFallMaxSpeed = 8;
        daAlinkHIO_swim_c0::m.mBootsMaxFallSpeed = -20;
        daAlinkHIO_swim_c0::m.mBootsGravity = -0.699999988f;
        daAlinkHIO_wlMove_c0::m.mADashInitSpeed = 65;
        daAlinkHIO_wlMove_c0::m.mADashMaxSpeed = 45;
        daAlinkHIO_wlMove_c0::m.mADashInitSpeedSlow = 35;
        daAlinkHIO_wlMove_c0::m.mADashMaxSpeedSlow = 33;
        daAlinkHIO_wlMove_c0::m.mMaxSpeed = 20;
        mFastMovement = false;
    }

    if (gzInfo_isCheat_DisableItemTimer()) {
        executeDisableItemTimer();
    } else if (mDisableItemTimer) {
        executeEnableItemTimer();
    }

    if (gzInfo_isCheat_DisableWalls()) {
        executeDisableWalls();
    } else if (mDisableWalls) {
        executeEnableWalls();
    }

    if (gzInfo_isCheat_InfiniteAir()) executeInfiniteAir();
    if (gzInfo_isCheat_InfiniteArrows()) executeInfiniteArrows();
    if (gzInfo_isCheat_InfiniteBombs()) executeInfiniteBombs();
    if (gzInfo_isCheat_InfiniteHearts()) executeInfiniteHearts();
    if (gzInfo_isCheat_InvincibleLink()) executeInvincibleLink();
    if (gzInfo_isCheat_MoonJump()) executeMoonJump();
    if (gzInfo_isCheat_InfiniteOil()) executeInfiniteOil();
    if (gzInfo_isCheat_InfiniteRupees()) executeInfiniteRupees();
    if (gzInfo_isCheat_NoSinkingInSand()) executeNoSinkSand();
    if (gzInfo_isCheat_InfiniteSlingshot()) executeInfiniteSlingshot();

    if (gzInfo_isCheat_SuperClawshot()) {
        executeSuperClawshot();
    } else if (mSuperClawshot) {
        daAlinkHIO_hookshot_c0::m.mShootSpeed = CLAWSHOT_DEFAULT_SHOOT_SPEED;
        daAlinkHIO_hookshot_c0::m.mMaxLength = CLAWSHOT_DEFAULT_MAX_LENGTH;
        daAlinkHIO_hookshot_c0::m.mReturnSpeed = CLAWSHOT_DEFAULT_RETURN_SPEED;
        daAlinkHIO_hookshot_c0::m.mStickReturnSpeed = CLAWSHOT_DEFAULT_STICK_RETURN_SPEED;
        mSuperClawshot = false;
    }
}
