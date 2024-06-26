//
// Generated By: dol2asm
// Translation Unit: d_a_coach_fire
//

#include "rel/d/a/d_a_coach_fire/d_a_coach_fire.h"
#include "dol2asm.h"

//
// Types:
//

struct mDoMtx_stack_c {
    static u8 now[48];
};

struct fopAc_ac_c {
    /* 80018B64 */ fopAc_ac_c();
    /* 80018C8C */ ~fopAc_ac_c();
};

struct daNpcCoach_c {
    /* 8099DBA4 */ void deleteFireArrow(unsigned int);
    /* 8099DCE8 */ void deleteFireArrowFromList(unsigned int);
};

struct daCoachFire_c {
    /* 80657B78 */ void create_init();
    /* 80657C48 */ void initBaseMtx();
    /* 80657CA8 */ void setBaseMtx();
    /* 80657D2C */ void initCcSphere();

    static u8 const M_attr[16];
};

struct dPa_levelEcallBack {};

struct dKy_tevstr_c {};

struct csXyz {};

struct _GXColor {};

struct Vec {};

struct cXyz {
    /* 80266B34 */ void operator-(Vec const&) const;
};

struct dPa_control_c {
    struct level_c {
        /* 8004B918 */ void getEmitter(u32);
    };

    /* 8004D4CC */ void set(u32, u8, u16, cXyz const*, dKy_tevstr_c const*, csXyz const*,
                            cXyz const*, u8, dPa_levelEcallBack*, s8, _GXColor const*,
                            _GXColor const*, cXyz const*, f32);

    static u8 mParticleTracePCB[4 + 4 /* padding */];
};

struct dCcD_Stts {
    /* 80083860 */ void Init(int, int, fopAc_ac_c*);
};

struct dCcD_SrcSph {};

struct dCcD_Sph {
    /* 80084A34 */ void Set(dCcD_SrcSph const&);
};

struct dCcD_GStts {
    /* 80083760 */ dCcD_GStts();
    /* 8065833C */ ~dCcD_GStts();
};

struct dCcD_GObjInf {
    /* 80083A28 */ dCcD_GObjInf();
    /* 800840E4 */ ~dCcD_GObjInf();
    /* 80084460 */ void ChkTgHit();
};

struct dAttention_c {
    /* 8007353C */ void LockonTarget(s32);
    /* 800737E4 */ void LockonTruth();
};

struct cM3dGSph {
    /* 8026F648 */ void SetC(cXyz const&);
    /* 8026F708 */ void SetR(f32);
    /* 806582AC */ ~cM3dGSph();
};

struct cM3dGAab {
    /* 806582F4 */ ~cM3dGAab();
};

struct cCcD_Obj {};

struct cCcS {
    /* 80264BA8 */ void Set(cCcD_Obj*);
};

struct cCcD_GStts {
    /* 80658398 */ ~cCcD_GStts();
};

struct LIGHT_INFLUENCE {};

//
// Forward References:
//

extern "C" void create_init__13daCoachFire_cFv();
extern "C" void initBaseMtx__13daCoachFire_cFv();
extern "C" void setBaseMtx__13daCoachFire_cFv();
extern "C" void initCcSphere__13daCoachFire_cFv();
extern "C" static void daCoachFire_Draw__FP13daCoachFire_c();
extern "C" static void daCoachFire_Execute__FP13daCoachFire_c();
extern "C" static bool daCoachFire_IsDelete__FP13daCoachFire_c();
extern "C" static void daCoachFire_Delete__FP13daCoachFire_c();
extern "C" static void daCoachFire_Create__FP10fopAc_ac_c();
extern "C" void __dt__8cM3dGSphFv();
extern "C" void __dt__8cM3dGAabFv();
extern "C" void __dt__10dCcD_GSttsFv();
extern "C" void __dt__10cCcD_GSttsFv();
extern "C" u8 const M_attr__13daCoachFire_c[16];
extern "C" extern char const* const d_a_coach_fire__stringBase0;

//
// External References:
//

extern "C" void __ct__10fopAc_ac_cFv();
extern "C" void __dt__10fopAc_ac_cFv();
extern "C" void fopAcM_setStageLayer__FPv();
extern "C" void fopAcM_delete__FP10fopAc_ac_c();
extern "C" void fopAcM_setCullSizeBox__FP10fopAc_ac_cffffff();
extern "C" void fpcEx_SearchByID__FUi();
extern "C" void getEmitter__Q213dPa_control_c7level_cFUl();
extern "C" void
set__13dPa_control_cFUlUcUsPC4cXyzPC12dKy_tevstr_cPC5csXyzPC4cXyzUcP18dPa_levelEcallBackScPC8_GXColorPC8_GXColorPC4cXyzf();
extern "C" void LockonTarget__12dAttention_cFl();
extern "C" void LockonTruth__12dAttention_cFv();
extern "C" void __ct__10dCcD_GSttsFv();
extern "C" void Init__9dCcD_SttsFiiP10fopAc_ac_c();
extern "C" void __ct__12dCcD_GObjInfFv();
extern "C" void __dt__12dCcD_GObjInfFv();
extern "C" void ChkTgHit__12dCcD_GObjInfFv();
extern "C" void Set__8dCcD_SphFRC11dCcD_SrcSph();
extern "C" void dKy_plight_set__FP15LIGHT_INFLUENCE();
extern "C" void dKy_plight_cut__FP15LIGHT_INFLUENCE();
extern "C" void Set__4cCcSFP8cCcD_Obj();
extern "C" void __mi__4cXyzCFRC3Vec();
extern "C" void SetC__8cM3dGSphFRC4cXyz();
extern "C" void SetR__8cM3dGSphFf();
extern "C" void __dl__FPv();
extern "C" void PSMTXCopy();
extern "C" void PSMTXMultVec();
extern "C" void PSVECScale();
extern "C" void _savegpr_29();
extern "C" void _restgpr_29();
extern "C" extern void* g_fopAc_Method[8];
extern "C" extern void* g_fpcLf_Method[5 + 1 /* padding */];
extern "C" extern void* __vt__8dCcD_Sph[36];
extern "C" extern void* __vt__9dCcD_Stts[11];
extern "C" extern void* __vt__12cCcD_SphAttr[25];
extern "C" extern void* __vt__14cCcD_ShapeAttr[22];
extern "C" extern void* __vt__9cCcD_Stts[8];
extern "C" u8 now__14mDoMtx_stack_c[48];
extern "C" extern u8 g_dComIfG_gameInfo[122384];
extern "C" u8 mParticleTracePCB__13dPa_control_c[4 + 4 /* padding */];
extern "C" void deleteFireArrow__12daNpcCoach_cFUi();
extern "C" void deleteFireArrowFromList__12daNpcCoach_cFUi();

//
// Declarations:
//

/* ############################################################################################## */
/* 806583E8-806583F8 000000 0010+00 3/3 0/0 0/0 .rodata          M_attr__13daCoachFire_c */
SECTION_RODATA u8 const daCoachFire_c::M_attr[16] = {
    0x42, 0x48, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x24, 0xFF, 0x64, 0x00, 0x44, 0x2F, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x806583E8, &daCoachFire_c::M_attr);

/* 806583F8-806583FC 000010 0004+00 0/1 0/0 0/0 .rodata          @3812 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3812 = -100.0f;
COMPILER_STRIP_GATE(0x806583F8, &lit_3812);
#pragma pop

/* 806583FC-80658400 000014 0004+00 0/1 0/0 0/0 .rodata          @3813 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3813 = -10.0f;
COMPILER_STRIP_GATE(0x806583FC, &lit_3813);
#pragma pop

/* 80658400-80658404 000018 0004+00 0/1 0/0 0/0 .rodata          @3814 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3814 = 100.0f;
COMPILER_STRIP_GATE(0x80658400, &lit_3814);
#pragma pop

/* 80658404-80658408 00001C 0004+00 0/1 0/0 0/0 .rodata          @3815 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3815 = 200.0f;
COMPILER_STRIP_GATE(0x80658404, &lit_3815);
#pragma pop

/* 80657B78-80657C48 000078 00D0+00 1/1 0/0 0/0 .text            create_init__13daCoachFire_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daCoachFire_c::create_init() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/create_init__13daCoachFire_cFv.s"
}
#pragma pop

/* 80657C48-80657CA8 000148 0060+00 1/1 0/0 0/0 .text            initBaseMtx__13daCoachFire_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daCoachFire_c::initBaseMtx() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/initBaseMtx__13daCoachFire_cFv.s"
}
#pragma pop

/* 80657CA8-80657D2C 0001A8 0084+00 1/1 0/0 0/0 .text            setBaseMtx__13daCoachFire_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daCoachFire_c::setBaseMtx() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/setBaseMtx__13daCoachFire_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80658408-80658448 000020 0040+00 1/1 0/0 0/0 .rodata
 * ccSphSrc$localstatic3$initCcSphere__13daCoachFire_cFv        */
SECTION_RODATA static u8 const data_80658408[64] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x48, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80658408, &data_80658408);

/* 80657D2C-80657D9C 00022C 0070+00 1/1 0/0 0/0 .text            initCcSphere__13daCoachFire_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daCoachFire_c::initCcSphere() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/initCcSphere__13daCoachFire_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80658448-8065844C 000060 0004+00 0/1 0/0 0/0 .rodata          @3911 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3911 = 1.0f;
COMPILER_STRIP_GATE(0x80658448, &lit_3911);
#pragma pop

/* 8065844C-80658450 000064 0004+00 0/1 0/0 0/0 .rodata          @3912 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_3912[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x8065844C, &lit_3912);
#pragma pop

/* 80658450-80658454 000068 0004+00 0/1 0/0 0/0 .rodata          @3913 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3913 = 9.0f / 10.0f;
COMPILER_STRIP_GATE(0x80658450, &lit_3913);
#pragma pop

/* 80657D9C-80657EA0 00029C 0104+00 1/0 0/0 0/0 .text            daCoachFire_Draw__FP13daCoachFire_c
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daCoachFire_Draw(daCoachFire_c* param_0) {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/daCoachFire_Draw__FP13daCoachFire_c.s"
}
#pragma pop

/* 80657EA0-80658094 0003A0 01F4+00 1/0 0/0 0/0 .text daCoachFire_Execute__FP13daCoachFire_c */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daCoachFire_Execute(daCoachFire_c* param_0) {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/daCoachFire_Execute__FP13daCoachFire_c.s"
}
#pragma pop

/* 80658094-8065809C 000594 0008+00 1/0 0/0 0/0 .text daCoachFire_IsDelete__FP13daCoachFire_c */
static bool daCoachFire_IsDelete(daCoachFire_c* param_0) {
    return true;
}

/* ############################################################################################## */
/* 8065845C-8065847C -00001 0020+00 1/0 0/0 0/0 .data            l_daCoachFire_Method */
SECTION_DATA static void* l_daCoachFire_Method[8] = {
    (void*)daCoachFire_Create__FP10fopAc_ac_c,
    (void*)daCoachFire_Delete__FP13daCoachFire_c,
    (void*)daCoachFire_Execute__FP13daCoachFire_c,
    (void*)daCoachFire_IsDelete__FP13daCoachFire_c,
    (void*)daCoachFire_Draw__FP13daCoachFire_c,
    (void*)NULL,
    (void*)NULL,
    (void*)NULL,
};

/* 8065847C-806584AC -00001 0030+00 0/0 0/0 1/0 .data            g_profile_COACH_FIRE */
SECTION_DATA extern void* g_profile_COACH_FIRE[12] = {
    (void*)0xFFFFFFFD, (void*)0x0003FFFD,
    (void*)0x00580000, (void*)&g_fpcLf_Method,
    (void*)0x00000714, (void*)NULL,
    (void*)NULL,       (void*)&g_fopAc_Method,
    (void*)0x014C0000, (void*)&l_daCoachFire_Method,
    (void*)0x00044000, (void*)0x000E0000,
};

/* 806584AC-806584B8 000050 000C+00 3/3 0/0 0/0 .data            __vt__10cCcD_GStts */
SECTION_DATA extern void* __vt__10cCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10cCcD_GSttsFv,
};

/* 806584B8-806584C4 00005C 000C+00 2/2 0/0 0/0 .data            __vt__10dCcD_GStts */
SECTION_DATA extern void* __vt__10dCcD_GStts[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__10dCcD_GSttsFv,
};

/* 806584C4-806584D0 000068 000C+00 3/3 0/0 0/0 .data            __vt__8cM3dGAab */
SECTION_DATA extern void* __vt__8cM3dGAab[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGAabFv,
};

/* 806584D0-806584DC 000074 000C+00 3/3 0/0 0/0 .data            __vt__8cM3dGSph */
SECTION_DATA extern void* __vt__8cM3dGSph[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGSphFv,
};

/* 8065809C-806581C0 00059C 0124+00 1/0 0/0 0/0 .text daCoachFire_Delete__FP13daCoachFire_c */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daCoachFire_Delete(daCoachFire_c* param_0) {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/daCoachFire_Delete__FP13daCoachFire_c.s"
}
#pragma pop

/* 806581C0-806582AC 0006C0 00EC+00 1/0 0/0 0/0 .text            daCoachFire_Create__FP10fopAc_ac_c
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daCoachFire_Create(fopAc_ac_c* param_0) {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/daCoachFire_Create__FP10fopAc_ac_c.s"
}
#pragma pop

/* 806582AC-806582F4 0007AC 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGSphFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm cM3dGSph::~cM3dGSph() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/__dt__8cM3dGSphFv.s"
}
#pragma pop

/* 806582F4-8065833C 0007F4 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGAabFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm cM3dGAab::~cM3dGAab() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/__dt__8cM3dGAabFv.s"
}
#pragma pop

/* 8065833C-80658398 00083C 005C+00 1/0 0/0 0/0 .text            __dt__10dCcD_GSttsFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm dCcD_GStts::~dCcD_GStts() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/__dt__10dCcD_GSttsFv.s"
}
#pragma pop

/* 80658398-806583E0 000898 0048+00 1/0 0/0 0/0 .text            __dt__10cCcD_GSttsFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm cCcD_GStts::~cCcD_GStts() {
    nofralloc
#include "asm/rel/d/a/d_a_coach_fire/d_a_coach_fire/__dt__10cCcD_GSttsFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80658454-8065845A 00006C 0006+00 0/0 0/0 0/0 .rodata          None */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80658454 = "Coach";
#pragma pop

/* 80658454-80658454 00006C 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
