#ifndef GZ_MANAGER_CHEATS_H
#define GZ_MANAGER_CHEATS_H

#include "dolphin/types.h"

static const int ITEM_TIMER_DISABLED = 0x7FFF;
static const int ITEM_TIMER_DEFAULT = 240;
static const int OXYGEN_MAX = 600;
static const int OIL_MAX = 21600;
static const f32 MOON_JUMP_SPEED = 56.0f;

static const f32 CLAWSHOT_SUPER_SHOOT_SPEED = 2870.0f;
static const f32 CLAWSHOT_SUPER_MAX_LENGTH = 69420.0f;
static const f32 CLAWSHOT_SUPER_RETURN_SPEED = 2870.0f;
static const f32 CLAWSHOT_SUPER_STICK_RETURN_SPEED = 500.0f;

static const f32 CLAWSHOT_DEFAULT_SHOOT_SPEED = 100.0f;
static const f32 CLAWSHOT_DEFAULT_MAX_LENGTH = 2000.0f;
static const f32 CLAWSHOT_DEFAULT_RETURN_SPEED = 150.0f;
static const f32 CLAWSHOT_DEFAULT_STICK_RETURN_SPEED = 60.0f;

class gzCheatsMng_c {
public:
    void execute();
    void executeDisableItemTimer();
    void executeDisableWalls();
    void executeEnableItemTimer();
    void executeEnableWalls();
    void executeFastBonkRecovery();
    void executeFastMovement();
    void executeInfiniteAir();
    void executeInfiniteArrows();
    void executeInfiniteBombs();
    void executeInfiniteHearts();
    void executeInfiniteOil();
    void executeInfiniteRupees();
    void executeInfiniteSlingshot();
    void executeInvincibleLink();
    void executeInvincibleEnemies();
    void executeMoonJump();
    void executeNoSinkSand();
    void executeSuperClawshot();
    void executeUnrestrictedItems();

private:
    // for "run once" reenable checks
    bool mDisableWalls;
    bool mDisableItemTimer;
    bool mFastBonkRecovery;
    bool mFastMovement;
    bool mSuperClawshot;
};

#endif
