#ifndef D_A_E_PZ_H
#define D_A_E_PZ_H

#include "dolphin/types.h"

struct daE_PZ_c {
    void onBombArrowHit() { field_0x845 = 1; }

    /* 807585BC */ void draw();
    /* 80758800 */ void setBck(int, u8, f32, f32);
    /* 807588AC */ void setActionMode(int, int);
    /* 807588B8 */ void mEntrySUB(bool);
    /* 80758A94 */ void mPzScaleSet(bool);
    /* 80758BA0 */ void mEnemyScaleSet();
    /* 80758D44 */ void getCutType();
    /* 80758DA4 */ void mSetFirePos();
    /* 80758E04 */ void damage_check();
    /* 807592F4 */ void executeSearchPoint();
    /* 807593CC */ void executeOpeningDemo();
    /* 8075B7E0 */ void mPointerSet();
    /* 8075B970 */ void executeWait();
    /* 8075C6AC */ void executeAttack();
    /* 8075CB80 */ void executeDamage();
    /* 8075CE68 */ void executeDead();
    /* 8075D94C */ void executeSummonsBullet();
    /* 8075F0BC */ void executeBullet();
    /* 8075F3A8 */ void action();
    /* 8075F510 */ void action_fire();
    /* 8075F578 */ void fire_mtx_set();
    /* 8075F734 */ void mtx_set();
    /* 8075F7E8 */ void cc_set();
    /* 8075F964 */ void execute();
    /* 8075FA88 */ void _delete();
    /* 8075FB4C */ void CreateHeap();
    /* 8076010C */ void create();
    /* 807607EC */ daE_PZ_c();

    /* 0x000 */ u8 base[0x845];
    /* 0x845 */ u8 field_0x845;
};

#endif /* D_A_E_PZ_H */
