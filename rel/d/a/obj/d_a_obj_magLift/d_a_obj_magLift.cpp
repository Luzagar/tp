//
// Generated By: dol2asm
// Translation Unit: d_a_obj_magLift
//

#include "rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift.h"
#include "dol2asm.h"

//
// Types:
//

struct request_of_phase_process_class {};

struct mDoMtx_stack_c {
    static u8 now[48];
};

struct mDoHIO_entry_c {
    /* 80C8DA58 */ ~mDoHIO_entry_c();
};

struct fopAc_ac_c {};

struct daMagLift_c {
    /* 80C8DAA0 */ void setBaseMtx();
    /* 80C8DB28 */ void CreateHeap();
    /* 80C8DB94 */ void create();
    /* 80C8DD38 */ void Execute(f32 (**)[3][4]);
    /* 80C8DD88 */ void moveLift();
    /* 80C8DE98 */ void modeAcc();
    /* 80C8DF20 */ void init_modeMove();
    /* 80C8DF2C */ void modeMove();
    /* 80C8E1EC */ void init_modeBrk();
    /* 80C8E1F8 */ void modeBrk();
    /* 80C8E260 */ void init_modeWaitInit();
    /* 80C8E26C */ void modeWaitInit();
    /* 80C8E2A0 */ void init_modeWait();
    /* 80C8E2AC */ void modeWait();
    /* 80C8E2B8 */ void init_modeMoveWait();
    /* 80C8E2C4 */ void modeMoveWait();
    /* 80C8E318 */ void modeDead();
    /* 80C8E31C */ void setNextPoint();
    /* 80C8E450 */ void Draw();
    /* 80C8E4F4 */ void Delete();

    static u8 const mSpeed[64];
};

struct daMagLift_HIO_c {
    /* 80C8DA2C */ daMagLift_HIO_c();
    /* 80C8E5B0 */ ~daMagLift_HIO_c();
};

struct dSv_info_c {
    /* 80035360 */ void isSwitch(int, int) const;
};

struct dKy_tevstr_c {};

struct J3DModelData {};

struct Vec {};

struct cXyz {
    /* 80266B34 */ void operator-(Vec const&) const;
    /* 8026702C */ bool operator==(Vec const&) const;
};

struct dScnKy_env_light_c {
    /* 801A37C4 */ void settingTevStruct(int, cXyz*, dKy_tevstr_c*);
    /* 801A4DA0 */ void setLightTevColorType_MAJI(J3DModelData*, dKy_tevstr_c*);
};

struct dRes_info_c {};

struct dRes_control_c {
    /* 8003C2EC */ void getRes(char const*, s32, dRes_info_c*, int);
};

struct dBgW {};

struct cBgS_PolyInfo {};

struct csXyz {};

struct dBgS_MoveBgActor {
    /* 80078624 */ dBgS_MoveBgActor();
    /* 80078690 */ bool Create();
    /* 800786B0 */ bool IsDelete();
    /* 800786B8 */ bool ToFore();
    /* 800786C0 */ bool ToBack();
    /* 800787BC */ void MoveBGCreate(char const*, int,
                                     void (*)(dBgW*, void*, cBgS_PolyInfo const&, bool, cXyz*,
                                              csXyz*, csXyz*),
                                     u32, f32 (*)[3][4]);
    /* 800788DC */ void MoveBGDelete();
    /* 80078950 */ void MoveBGExecute();
};

struct J3DModel {};

//
// Forward References:
//

extern "C" void __ct__15daMagLift_HIO_cFv();
extern "C" void __dt__14mDoHIO_entry_cFv();
extern "C" void setBaseMtx__11daMagLift_cFv();
extern "C" void CreateHeap__11daMagLift_cFv();
extern "C" void create__11daMagLift_cFv();
extern "C" void Execute__11daMagLift_cFPPA3_A4_f();
extern "C" void moveLift__11daMagLift_cFv();
extern "C" void modeAcc__11daMagLift_cFv();
extern "C" void init_modeMove__11daMagLift_cFv();
extern "C" void modeMove__11daMagLift_cFv();
extern "C" void init_modeBrk__11daMagLift_cFv();
extern "C" void modeBrk__11daMagLift_cFv();
extern "C" void init_modeWaitInit__11daMagLift_cFv();
extern "C" void modeWaitInit__11daMagLift_cFv();
extern "C" void init_modeWait__11daMagLift_cFv();
extern "C" void modeWait__11daMagLift_cFv();
extern "C" void init_modeMoveWait__11daMagLift_cFv();
extern "C" void modeMoveWait__11daMagLift_cFv();
extern "C" void modeDead__11daMagLift_cFv();
extern "C" void setNextPoint__11daMagLift_cFv();
extern "C" void Draw__11daMagLift_cFv();
extern "C" void Delete__11daMagLift_cFv();
extern "C" static void daMagLift_Draw__FP11daMagLift_c();
extern "C" static void daMagLift_Execute__FP11daMagLift_c();
extern "C" static void daMagLift_Delete__FP11daMagLift_c();
extern "C" static void daMagLift_Create__FP10fopAc_ac_c();
extern "C" void __dt__15daMagLift_HIO_cFv();
extern "C" void __sinit_d_a_obj_magLift_cpp();
extern "C" u8 const mSpeed__11daMagLift_c[64];
extern "C" extern char const* const d_a_obj_magLift__stringBase0;

//
// External References:
//

extern "C" void mDoMtx_ZXYrotM__FPA4_fsss();
extern "C" void mDoExt_modelUpdateDL__FP8J3DModel();
extern "C" void mDoExt_J3DModel__create__FP12J3DModelDataUlUl();
extern "C" void fopAcM_setCullSizeBox2__FP10fopAc_ac_cP12J3DModelData();
extern "C" void dComIfG_resLoad__FP30request_of_phase_process_classPCc();
extern "C" void dComIfG_resDelete__FP30request_of_phase_process_classPCc();
extern "C" void isSwitch__10dSv_info_cCFii();
extern "C" void getRes__14dRes_control_cFPCclP11dRes_info_ci();
extern "C" void dPath_GetRoomPath__Fii();
extern "C" void dBgS_MoveBGProc_TypicalRotY__FP4dBgWPvRC13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz();
extern "C" void __ct__16dBgS_MoveBgActorFv();
extern "C" bool Create__16dBgS_MoveBgActorFv();
extern "C" bool IsDelete__16dBgS_MoveBgActorFv();
extern "C" bool ToFore__16dBgS_MoveBgActorFv();
extern "C" bool ToBack__16dBgS_MoveBgActorFv();
extern "C" void
MoveBGCreate__16dBgS_MoveBgActorFPCciPFP4dBgWPvRC13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz_vUlPA3_A4_f();
extern "C" void MoveBGDelete__16dBgS_MoveBgActorFv();
extern "C" void MoveBGExecute__16dBgS_MoveBgActorFv();
extern "C" void settingTevStruct__18dScnKy_env_light_cFiP4cXyzP12dKy_tevstr_c();
extern "C" void setLightTevColorType_MAJI__18dScnKy_env_light_cFP12J3DModelDataP12dKy_tevstr_c();
extern "C" void __mi__4cXyzCFRC3Vec();
extern "C" bool __eq__4cXyzCFRC3Vec();
extern "C" void cLib_addCalcPos__FP4cXyzRC4cXyzfff();
extern "C" void cLib_chaseF__FPfff();
extern "C" void __dl__FPv();
extern "C" void PSMTXCopy();
extern "C" void PSMTXTrans();
extern "C" void PSVECSquareMag();
extern "C" void __ptmf_scall();
extern "C" extern void* g_fopAc_Method[8];
extern "C" extern void* g_fpcLf_Method[5 + 1 /* padding */];
extern "C" u8 now__14mDoMtx_stack_c[48];
extern "C" extern u8 g_dComIfG_gameInfo[122384];
extern "C" extern u8 g_env_light[4880];
extern "C" extern u8 j3dSys[284];
extern "C" extern u32 __float_nan;
extern "C" void __register_global_object();

//
// Declarations:
//

/* ############################################################################################## */
/* 80C8E6DC-80C8E6E8 000000 000C+00 1/1 0/0 0/0 .data            cNullVec__6Z2Calc */
SECTION_DATA static u8 cNullVec__6Z2Calc[12] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/* 80C8E6E8-80C8E6FC 00000C 0004+10 0/0 0/0 0/0 .data            @1787 */
#pragma push
#pragma force_active on
SECTION_DATA static u32 lit_1787[1 + 4 /* padding */] = {
    0x02000201,
    /* padding */
    0x40080000,
    0x00000000,
    0x3FE00000,
    0x00000000,
};
#pragma pop

/* 80C8E6FC-80C8E708 -00001 000C+00 0/1 0/0 0/0 .data            @3736 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3736[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeAcc__11daMagLift_cFv,
};
#pragma pop

/* 80C8E708-80C8E714 -00001 000C+00 0/1 0/0 0/0 .data            @3737 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3737[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeMove__11daMagLift_cFv,
};
#pragma pop

/* 80C8E714-80C8E720 -00001 000C+00 0/1 0/0 0/0 .data            @3738 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3738[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeBrk__11daMagLift_cFv,
};
#pragma pop

/* 80C8E720-80C8E72C -00001 000C+00 0/1 0/0 0/0 .data            @3739 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3739[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeWait__11daMagLift_cFv,
};
#pragma pop

/* 80C8E72C-80C8E738 -00001 000C+00 0/1 0/0 0/0 .data            @3740 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3740[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeWaitInit__11daMagLift_cFv,
};
#pragma pop

/* 80C8E738-80C8E744 -00001 000C+00 0/1 0/0 0/0 .data            @3741 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3741[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeDead__11daMagLift_cFv,
};
#pragma pop

/* 80C8E744-80C8E750 -00001 000C+00 0/1 0/0 0/0 .data            @3742 */
#pragma push
#pragma force_active on
SECTION_DATA static void* lit_3742[3] = {
    (void*)NULL,
    (void*)0xFFFFFFFF,
    (void*)modeMoveWait__11daMagLift_cFv,
};
#pragma pop

/* 80C8E750-80C8E7B0 000074 0060+00 0/1 0/0 0/0 .data            mode_proc$3735 */
#pragma push
#pragma force_active on
SECTION_DATA static u8 mode_proc[96] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#pragma pop

/* 80C8E7B0-80C8E7D0 -00001 0020+00 1/0 0/0 0/0 .data            l_daMagLift_Method */
SECTION_DATA static void* l_daMagLift_Method[8] = {
    (void*)daMagLift_Create__FP10fopAc_ac_c,
    (void*)daMagLift_Delete__FP11daMagLift_c,
    (void*)daMagLift_Execute__FP11daMagLift_c,
    (void*)NULL,
    (void*)daMagLift_Draw__FP11daMagLift_c,
    (void*)NULL,
    (void*)NULL,
    (void*)NULL,
};

/* 80C8E7D0-80C8E800 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_Obj_MagLift */
SECTION_DATA extern void* g_profile_Obj_MagLift[12] = {
    (void*)0xFFFFFFFD, (void*)0x0003FFFD,
    (void*)0x00370000, (void*)&g_fpcLf_Method,
    (void*)0x000005D4, (void*)NULL,
    (void*)NULL,       (void*)&g_fopAc_Method,
    (void*)0x01EC0000, (void*)&l_daMagLift_Method,
    (void*)0x00040100, (void*)0x000E0000,
};

/* 80C8E800-80C8E828 000124 0028+00 1/1 0/0 0/0 .data            __vt__11daMagLift_c */
SECTION_DATA extern void* __vt__11daMagLift_c[10] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)CreateHeap__11daMagLift_cFv,
    (void*)Create__16dBgS_MoveBgActorFv,
    (void*)Execute__11daMagLift_cFPPA3_A4_f,
    (void*)Draw__11daMagLift_cFv,
    (void*)Delete__11daMagLift_cFv,
    (void*)IsDelete__16dBgS_MoveBgActorFv,
    (void*)ToFore__16dBgS_MoveBgActorFv,
    (void*)ToBack__16dBgS_MoveBgActorFv,
};

/* 80C8E828-80C8E834 00014C 000C+00 2/2 0/0 0/0 .data            __vt__15daMagLift_HIO_c */
SECTION_DATA extern void* __vt__15daMagLift_HIO_c[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__15daMagLift_HIO_cFv,
};

/* 80C8E834-80C8E840 000158 000C+00 3/3 0/0 0/0 .data            __vt__14mDoHIO_entry_c */
SECTION_DATA extern void* __vt__14mDoHIO_entry_c[3] = {
    (void*)NULL /* RTTI */,
    (void*)NULL,
    (void*)__dt__14mDoHIO_entry_cFv,
};

/* 80C8DA2C-80C8DA58 0000EC 002C+00 1/1 0/0 0/0 .text            __ct__15daMagLift_HIO_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm daMagLift_HIO_c::daMagLift_HIO_c() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/__ct__15daMagLift_HIO_cFv.s"
}
#pragma pop

/* 80C8DA58-80C8DAA0 000118 0048+00 1/0 0/0 0/0 .text            __dt__14mDoHIO_entry_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm mDoHIO_entry_c::~mDoHIO_entry_c() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/__dt__14mDoHIO_entry_cFv.s"
}
#pragma pop

/* 80C8DAA0-80C8DB28 000160 0088+00 2/2 0/0 0/0 .text            setBaseMtx__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::setBaseMtx() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/setBaseMtx__11daMagLift_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80C8E6D0-80C8E6D0 000074 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
#pragma push
#pragma force_active on
SECTION_DEAD static char const* const stringBase_80C8E6D0 = "L_maglift";
#pragma pop

/* 80C8DB28-80C8DB94 0001E8 006C+00 1/0 0/0 0/0 .text            CreateHeap__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::CreateHeap() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/CreateHeap__11daMagLift_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80C8E65C-80C8E69C 000000 0040+00 4/4 0/0 0/0 .rodata          mSpeed__11daMagLift_c */
SECTION_RODATA u8 const daMagLift_c::mSpeed[64] = {
    0x40, 0xA0, 0x00, 0x00, 0x40, 0xD5, 0x55, 0x55, 0x41, 0x05, 0x55, 0x55, 0x41, 0x20, 0x00, 0x00,
    0x41, 0x3A, 0xAA, 0xAB, 0x41, 0x55, 0x55, 0x55, 0x41, 0x70, 0x00, 0x00, 0x41, 0x85, 0x55, 0x55,
    0x41, 0x92, 0xAA, 0xAB, 0x41, 0xA0, 0x00, 0x00, 0x41, 0xAD, 0x55, 0x55, 0x41, 0xBA, 0xAA, 0xAB,
    0x41, 0xC8, 0x00, 0x00, 0x41, 0xD5, 0x55, 0x55, 0x41, 0xE2, 0xAA, 0xAB, 0x40, 0x55, 0x55, 0x55,
};
COMPILER_STRIP_GATE(0x80C8E65C, &daMagLift_c::mSpeed);

/* 80C8E69C-80C8E6A0 000040 0004+00 1/3 0/0 0/0 .rodata          @3718 */
SECTION_RODATA static u8 const lit_3718[4] = {
    0x00,
    0x00,
    0x00,
    0x00,
};
COMPILER_STRIP_GATE(0x80C8E69C, &lit_3718);

/* 80C8DB94-80C8DD38 000254 01A4+00 1/1 0/0 0/0 .text            create__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::create() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/create__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8DD38-80C8DD88 0003F8 0050+00 1/0 0/0 0/0 .text            Execute__11daMagLift_cFPPA3_A4_f */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::Execute(f32 (**param_0)[3][4]) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/Execute__11daMagLift_cFPPA3_A4_f.s"
}
#pragma pop

/* ############################################################################################## */
/* 80C8E848-80C8E854 000008 000C+00 1/1 0/0 0/0 .bss             @3619 */
static u8 lit_3619[12];

/* 80C8E854-80C8E85C 000014 0008+00 1/1 0/0 0/0 .bss             l_HIO */
static u8 l_HIO[8];

/* 80C8E85C-80C8E860 00001C 0004+00 1/1 0/0 0/0 .bss             None */
static u8 data_80C8E85C[4];

/* 80C8DD88-80C8DE98 000448 0110+00 1/1 0/0 0/0 .text            moveLift__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::moveLift() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/moveLift__11daMagLift_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80C8E6A0-80C8E6A4 000044 0004+00 0/2 0/0 0/0 .rodata          @3759 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3759 = 30.0f;
COMPILER_STRIP_GATE(0x80C8E6A0, &lit_3759);
#pragma pop

/* 80C8E6A4-80C8E6A8 000048 0004+00 0/2 0/0 0/0 .rodata          @3760 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3760 = 1.0f;
COMPILER_STRIP_GATE(0x80C8E6A4, &lit_3760);
#pragma pop

/* 80C8E6A8-80C8E6AC 00004C 0004+00 0/3 0/0 0/0 .rodata          @3761 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3761 = 1.0f / 10.0f;
COMPILER_STRIP_GATE(0x80C8E6A8, &lit_3761);
#pragma pop

/* 80C8DE98-80C8DF20 000558 0088+00 1/0 0/0 0/0 .text            modeAcc__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::modeAcc() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/modeAcc__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8DF20-80C8DF2C 0005E0 000C+00 1/1 0/0 0/0 .text            init_modeMove__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::init_modeMove() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/init_modeMove__11daMagLift_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80C8E6AC-80C8E6B4 000050 0008+00 0/1 0/0 0/0 .rodata          @3834 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_3834[8] = {
    0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80C8E6AC, &lit_3834);
#pragma pop

/* 80C8E6B4-80C8E6BC 000058 0008+00 0/1 0/0 0/0 .rodata          @3835 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_3835[8] = {
    0x40, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80C8E6B4, &lit_3835);
#pragma pop

/* 80C8E6BC-80C8E6C4 000060 0008+00 0/1 0/0 0/0 .rodata          @3836 */
#pragma push
#pragma force_active on
SECTION_RODATA static u8 const lit_3836[8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
COMPILER_STRIP_GATE(0x80C8E6BC, &lit_3836);
#pragma pop

/* 80C8E6C4-80C8E6C8 000068 0004+00 0/1 0/0 0/0 .rodata          @3837 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3837 = 3.0f / 10.0f;
COMPILER_STRIP_GATE(0x80C8E6C4, &lit_3837);
#pragma pop

/* 80C8E6C8-80C8E6CC 00006C 0004+00 0/1 0/0 0/0 .rodata          @3838 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3838 = 300.0f;
COMPILER_STRIP_GATE(0x80C8E6C8, &lit_3838);
#pragma pop

/* 80C8DF2C-80C8E1EC 0005EC 02C0+00 1/0 0/0 0/0 .text            modeMove__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::modeMove() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/modeMove__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E1EC-80C8E1F8 0008AC 000C+00 1/1 0/0 0/0 .text            init_modeBrk__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::init_modeBrk() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/init_modeBrk__11daMagLift_cFv.s"
}
#pragma pop

/* ############################################################################################## */
/* 80C8E6CC-80C8E6D0 000070 0004+00 0/1 0/0 0/0 .rodata          @3852 */
#pragma push
#pragma force_active on
SECTION_RODATA static f32 const lit_3852 = 0.5f;
COMPILER_STRIP_GATE(0x80C8E6CC, &lit_3852);
#pragma pop

/* 80C8E1F8-80C8E260 0008B8 0068+00 1/0 0/0 0/0 .text            modeBrk__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::modeBrk() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/modeBrk__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E260-80C8E26C 000920 000C+00 3/3 0/0 0/0 .text            init_modeWaitInit__11daMagLift_cFv
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::init_modeWaitInit() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/init_modeWaitInit__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E26C-80C8E2A0 00092C 0034+00 1/0 0/0 0/0 .text            modeWaitInit__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::modeWaitInit() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/modeWaitInit__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E2A0-80C8E2AC 000960 000C+00 1/1 0/0 0/0 .text            init_modeWait__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::init_modeWait() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/init_modeWait__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E2AC-80C8E2B8 00096C 000C+00 1/0 0/0 0/0 .text            modeWait__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::modeWait() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/modeWait__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E2B8-80C8E2C4 000978 000C+00 1/1 0/0 0/0 .text            init_modeMoveWait__11daMagLift_cFv
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::init_modeMoveWait() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/init_modeMoveWait__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E2C4-80C8E318 000984 0054+00 1/0 0/0 0/0 .text            modeMoveWait__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::modeMoveWait() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/modeMoveWait__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E318-80C8E31C 0009D8 0004+00 1/0 0/0 0/0 .text            modeDead__11daMagLift_cFv */
void daMagLift_c::modeDead() {
    /* empty function */
}

/* 80C8E31C-80C8E450 0009DC 0134+00 1/1 0/0 0/0 .text            setNextPoint__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::setNextPoint() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/setNextPoint__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E450-80C8E4F4 000B10 00A4+00 1/0 0/0 0/0 .text            Draw__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::Draw() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/Draw__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E4F4-80C8E524 000BB4 0030+00 1/0 0/0 0/0 .text            Delete__11daMagLift_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void daMagLift_c::Delete() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/Delete__11daMagLift_cFv.s"
}
#pragma pop

/* 80C8E524-80C8E550 000BE4 002C+00 1/0 0/0 0/0 .text            daMagLift_Draw__FP11daMagLift_c */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daMagLift_Draw(daMagLift_c* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/daMagLift_Draw__FP11daMagLift_c.s"
}
#pragma pop

/* 80C8E550-80C8E570 000C10 0020+00 1/0 0/0 0/0 .text            daMagLift_Execute__FP11daMagLift_c
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daMagLift_Execute(daMagLift_c* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/daMagLift_Execute__FP11daMagLift_c.s"
}
#pragma pop

/* 80C8E570-80C8E590 000C30 0020+00 1/0 0/0 0/0 .text            daMagLift_Delete__FP11daMagLift_c
 */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daMagLift_Delete(daMagLift_c* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/daMagLift_Delete__FP11daMagLift_c.s"
}
#pragma pop

/* 80C8E590-80C8E5B0 000C50 0020+00 1/0 0/0 0/0 .text            daMagLift_Create__FP10fopAc_ac_c */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
static asm void daMagLift_Create(fopAc_ac_c* param_0) {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/daMagLift_Create__FP10fopAc_ac_c.s"
}
#pragma pop

/* 80C8E5B0-80C8E60C 000C70 005C+00 2/1 0/0 0/0 .text            __dt__15daMagLift_HIO_cFv */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm daMagLift_HIO_c::~daMagLift_HIO_c() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/__dt__15daMagLift_HIO_cFv.s"
}
#pragma pop

/* 80C8E60C-80C8E648 000CCC 003C+00 0/0 1/0 0/0 .text            __sinit_d_a_obj_magLift_cpp */
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off
asm void __sinit_d_a_obj_magLift_cpp() {
    nofralloc
#include "asm/rel/d/a/obj/d_a_obj_magLift/d_a_obj_magLift/__sinit_d_a_obj_magLift_cpp.s"
}
#pragma pop

#pragma push
#pragma force_active on
REGISTER_CTORS(0x80C8E60C, __sinit_d_a_obj_magLift_cpp);
#pragma pop

/* 80C8E6D0-80C8E6D0 000074 0000+00 0/0 0/0 0/0 .rodata          @stringBase0 */
