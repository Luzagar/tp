//
// Generated By: dol2asm
// Translation Unit: d_a_obj_ndoor
//

#include "rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor.h"
#include "d/cc/d_cc_d.h"
#include "dol2asm.h"

//
// Types:
//

struct request_of_phase_process_class {};

struct obj_ndoor_class {};

struct mDoMtx_stack_c {
    static u8 now[48];
};

struct fopAc_ac_c {
    /* 80018B64 */ fopAc_ac_c();
};

struct dKy_tevstr_c {};

struct J3DModelData {};

struct dScnKy_env_light_c {
    /* 801A37C4 */ void settingTevStruct(int, cXyz*, dKy_tevstr_c*);
    /* 801A4DA0 */ void setLightTevColorType_MAJI(J3DModelData*, dKy_tevstr_c*);
};

struct dRes_info_c {};

struct dRes_control_c {
    /* 8003C2EC */ void getRes(char const*, s32, dRes_info_c*, int);
};

struct dCcU_AtInfo {};

struct cCcS {
    /* 80264BA8 */ void Set(cCcD_Obj*);
};

struct JMath {
    static u8 sincosTable_[65536];
};

struct J3DModel {};

//
// Forward References:
//

extern "C" static void daObj_Ndoor_Draw__FP15obj_ndoor_class();
extern "C" static void daObj_Ndoor_Execute__FP15obj_ndoor_class();
extern "C" static bool daObj_Ndoor_IsDelete__FP15obj_ndoor_class();
extern "C" static void daObj_Ndoor_Delete__FP15obj_ndoor_class();
extern "C" static void useHeapInit__FP10fopAc_ac_c();
extern "C" static void daObj_Ndoor_Create__FP10fopAc_ac_c();
extern "C" void __dt__8cM3dGSphFv();
extern "C" void __dt__8cM3dGAabFv();
extern "C" extern char const* const d_a_obj_ndoor__stringBase0;

//
// External References:
//

extern "C" void mDoMtx_XrotM__FPA4_fs();
extern "C" void mDoMtx_YrotM__FPA4_fs();
extern "C" void mDoExt_modelUpdateDL__FP8J3DModel();
extern "C" void mDoExt_J3DModel__create__FP12J3DModelDataUlUl();
extern "C" void __ct__10fopAc_ac_cFv();
extern "C" void fopAcM_entrySolidHeap__FP10fopAc_ac_cPFP10fopAc_ac_c_iUl();
extern "C" void fopAcM_searchActorDistanceXZ__FPC10fopAc_ac_cPC10fopAc_ac_c();
extern "C" void dComIfG_resLoad__FP30request_of_phase_process_classPCc();
extern "C" void dComIfG_resDelete__FP30request_of_phase_process_classPCc();
extern "C" void getRes__14dRes_control_cFPCclP11dRes_info_ci();
extern "C" void __ct__10dCcD_GSttsFv();
extern "C" void Init__9dCcD_SttsFiiP10fopAc_ac_c();
extern "C" void __ct__12dCcD_GObjInfFv();
extern "C" void ChkTgHit__12dCcD_GObjInfFv();
extern "C" void GetTgHitObj__12dCcD_GObjInfFv();
extern "C" void Set__8dCcD_SphFRC11dCcD_SrcSph();
extern "C" void at_power_check__FP11dCcU_AtInfo();
extern "C" void settingTevStruct__18dScnKy_env_light_cFiP4cXyzP12dKy_tevstr_c();
extern "C" void setLightTevColorType_MAJI__18dScnKy_env_light_cFP12J3DModelDataP12dKy_tevstr_c();
extern "C" void Set__4cCcSFP8cCcD_Obj();
extern "C" void SetC__8cM3dGSphFRC4cXyz();
extern "C" void SetR__8cM3dGSphFf();
extern "C" void cLib_addCalc0__FPfff();
extern "C" void __dl__FPv();
extern "C" void PSMTXCopy();
extern "C" void PSMTXTrans();
extern "C" extern void* g_fopAc_Method[8];
extern "C" extern void* g_fpcLf_Method[5 + 1 /* padding */];
extern "C" extern void* __vt__8dCcD_Sph[36];
extern "C" extern void* __vt__9dCcD_Stts[11];
extern "C" extern void* __vt__12cCcD_SphAttr[25];
extern "C" extern void* __vt__14cCcD_ShapeAttr[22];
extern "C" extern void* __vt__9cCcD_Stts[8];
extern "C" u8 now__14mDoMtx_stack_c[48];
extern "C" extern u8 g_dComIfG_gameInfo[122384];
extern "C" extern u8 g_env_light[4880];
extern "C" u8 sincosTable___5JMath[65536];

//
// Declarations:
//

/* 80CA3538-80CA359C 000078 0064+00 1/0 0/0 0/0 .text daObj_Ndoor_Draw__FP15obj_ndoor_class */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daObj_Ndoor_Draw(obj_ndoor_class* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/daObj_Ndoor_Draw__FP15obj_ndoor_class.s"
}
#pragma pop

/* ############################################################################################## */
/* 80CA3A44-80CA3A48 000000 0004+00 1/1 0/0 0/0 .rodata          @3831 */
SECTION_RODATA static f32 const lit_3831 = 350.0f;
COMPILER_STRIP_GATE(0x80CA3A44, &lit_3831);

/* 80CA3A48-80CA3A4C 000004 0004+00 0/1 0/0 0/0 .rodata          @3832 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3832 = 2500.0f;
COMPILER_STRIP_GATE(0x80CA3A48, &lit_3832);
#pragma pop

/* 80CA3A4C-80CA3A50 000008 0004+00 0/1 0/0 0/0 .rodata          @3833 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3833 = 25.0f;
COMPILER_STRIP_GATE(0x80CA3A4C, &lit_3833);
#pragma pop

/* 80CA3A50-80CA3A54 00000C 0004+00 0/1 0/0 0/0 .rodata          @3834 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3834 = 27000.0f;
COMPILER_STRIP_GATE(0x80CA3A50, &lit_3834);
#pragma pop

/* 80CA3A54-80CA3A58 000010 0004+00 0/1 0/0 0/0 .rodata          @3835 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3835 = 30.0f;
COMPILER_STRIP_GATE(0x80CA3A54, &lit_3835);
#pragma pop

/* 80CA3A58-80CA3A5C 000014 0004+00 0/1 0/0 0/0 .rodata          @3836 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3836 = 1.0f / 20.0f;
COMPILER_STRIP_GATE(0x80CA3A58, &lit_3836);
#pragma pop

/* 80CA3A5C-80CA3A64 000018 0004+04 0/1 0/0 0/0 .rodata          @3837 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3837[1 + 1 /* padding */] = {
    500.0f,
    /* padding */
    0.0f,
};
COMPILER_STRIP_GATE(0x80CA3A5C, &lit_3837);
#pragma pop

/* 80CA3A64-80CA3A6C 000020 0008+00 0/1 0/0 0/0 .rodata          @3839 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_3839[8] = {
    0x43, 0x30, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80CA3A64, &lit_3839);
#pragma pop

/* 80CA359C-80CA37A4 0000DC 0208+00 2/1 0/0 0/0 .text daObj_Ndoor_Execute__FP15obj_ndoor_class */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daObj_Ndoor_Execute(obj_ndoor_class* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/daObj_Ndoor_Execute__FP15obj_ndoor_class.s"
}
#pragma pop

/* 80CA37A4-80CA37AC 0002E4 0008+00 1/0 0/0 0/0 .text daObj_Ndoor_IsDelete__FP15obj_ndoor_class */
static bool daObj_Ndoor_IsDelete(obj_ndoor_class* param_0) {
    return true;
}

/* ############################################################################################## */
/* 80CA3A6C-80CA3A6C 000028 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80CA3A6C = "Obj_ndoor";
#pragma pop

/* 80CA37AC-80CA37DC 0002EC 0030+00 1/0 0/0 0/0 .text daObj_Ndoor_Delete__FP15obj_ndoor_class */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daObj_Ndoor_Delete(obj_ndoor_class* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/daObj_Ndoor_Delete__FP15obj_ndoor_class.s"
}
#pragma pop

/* 80CA37DC-80CA3848 00031C 006C+00 1/1 0/0 0/0 .text            useHeapInit__FP10fopAc_ac_c */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void useHeapInit(fopAc_ac_c* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/useHeapInit__FP10fopAc_ac_c.s"
}
#pragma pop

/* ############################################################################################## */
/* 80CA3A78-80CA3AB8 000000 0040+00 1/1 0/0 0/0 .data            cc_sph_src$3869 */
static dCcD_SrcSph cc_sph_src = {
    {
        {0x0, {{0x0, 0x0, 0x0}, {0xd8fbfdff, 0x3}, 0x0}}, // mObj
        {dCcD_SE_NONE, 0x0, 0x0, 0x0, 0x0}, // mGObjAt
        {dCcD_SE_NONE, 0x0, 0x0, 0x0, 0x2}, // mGObjTg
        {0x0}, // mGObjCo
    }, // mObjInf
    {
        {{0.0f, 0.0f, 0.0f}, 40.0f} // mSph
    } // mSphAttr
};

/* 80CA3AB8-80CA3AD8 -00001 0020+00 1/0 0/0 0/0 .data            l_daObj_Ndoor_Method */
SECTION_DATA static void* l_daObj_Ndoor_Method[8] = {
    (void*)daObj_Ndoor_Create__FP10fopAc_ac_c,
    (void*)daObj_Ndoor_Delete__FP15obj_ndoor_class,
    (void*)daObj_Ndoor_Execute__FP15obj_ndoor_class,
    (void*)daObj_Ndoor_IsDelete__FP15obj_ndoor_class,
    (void*)daObj_Ndoor_Draw__FP15obj_ndoor_class,
    (void*)NULL,
    (void*)NULL,
    (void*)NULL,
};

/* 80CA3AD8-80CA3B08 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_OBJ_NDOOR */
SECTION_DATA extern void* g_profile_OBJ_NDOOR[12] = {
    (void*)0xFFFFFFFD, (void*)0x0007FFFD,
    (void*)0x01280000, (void*)&g_fpcLf_Method,
    (void*)0x00000718, (void*)NULL,
    (void*)NULL,       (void*)&g_fopAc_Method,
    (void*)0x004C0000, (void*)&l_daObj_Ndoor_Method,
    (void*)0x00040100, (void*)NULL,
};

/* 80CA3B08-80CA3B14 000090 000C+00 2/2 0/0 0/0 .data            __vt__8cM3dGSph */
SECTION_DATA extern void* __vt__8cM3dGSph[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGSphFv,
};

/* 80CA3B14-80CA3B20 00009C 000C+00 2/2 0/0 0/0 .data            __vt__8cM3dGAab */
SECTION_DATA extern void* __vt__8cM3dGAab[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__8cM3dGAabFv,
};

/* 80CA3848-80CA39AC 000388 0164+00 1/0 0/0 0/0 .text            daObj_Ndoor_Create__FP10fopAc_ac_c
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daObj_Ndoor_Create(fopAc_ac_c* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/daObj_Ndoor_Create__FP10fopAc_ac_c.s"
}
#pragma pop

/* 80CA39AC-80CA39F4 0004EC 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGSphFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
// asm cM3dGSph::~cM3dGSph() {
extern "C" asm void __dt__8cM3dGSphFv() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/__dt__8cM3dGSphFv.s"
}
#pragma pop

/* 80CA39F4-80CA3A3C 000534 0048+00 1/0 0/0 0/0 .text            __dt__8cM3dGAabFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
// asm cM3dGAab::~cM3dGAab() {
extern "C" asm void __dt__8cM3dGAabFv() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_ndoor/d_a_obj_ndoor/__dt__8cM3dGAabFv.s"
}
#pragma pop

/* 80CA3A6C-80CA3A6C 000028 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
