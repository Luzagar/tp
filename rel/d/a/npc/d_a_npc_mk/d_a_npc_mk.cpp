//
// Generated By: dol2asm
// Translation Unit: d_a_npc_mk
//

#include "rel/d/a/npc/d_a_npc_mk/d_a_npc_mk.h"
#include "dol2asm.h"

//
// Forward References:
//

extern "C" static bool daNpc_Mk_Create__FPv();
extern "C" static bool daNpc_Mk_Delete__FPv();
extern "C" static bool daNpc_Mk_Execute__FPv();
extern "C" static bool daNpc_Mk_Draw__FPv();
extern "C" static bool daNpc_Mk_IsDelete__FPv();
extern "C" extern void* g_profile_NPC_MK[12];

//
// External References:
//

extern "C" extern void* g_fopAc_Method[8];
extern "C" extern void* g_fpcLf_Method[5 + 1 /* padding */];

//
// Declarations:
//

/* 80A73DD8-80A73DE0 000078 0008+00 1/0 0/0 0/0 .text            daNpc_Mk_Create__FPv */
static bool daNpc_Mk_Create(void* param_0) {
    return true;
}

/* 80A73DE0-80A73DE8 000080 0008+00 1/0 0/0 0/0 .text            daNpc_Mk_Delete__FPv */
static bool daNpc_Mk_Delete(void* param_0) {
    return true;
}

/* 80A73DE8-80A73DF0 000088 0008+00 1/0 0/0 0/0 .text            daNpc_Mk_Execute__FPv */
static bool daNpc_Mk_Execute(void* param_0) {
    return true;
}

/* 80A73DF0-80A73DF8 000090 0008+00 1/0 0/0 0/0 .text            daNpc_Mk_Draw__FPv */
static bool daNpc_Mk_Draw(void* param_0) {
    return true;
}

/* 80A73DF8-80A73E00 000098 0008+00 1/0 0/0 0/0 .text            daNpc_Mk_IsDelete__FPv */
static bool daNpc_Mk_IsDelete(void* param_0) {
    return true;
}

/* ############################################################################################## */
/* 80A73E08-80A73E28 -00001 0020+00 1/0 0/0 0/0 .data            daNpc_Mk_MethodTable */
SECTION_DATA static void* daNpc_Mk_MethodTable[8] = {
    (void*)daNpc_Mk_Create__FPv,
    (void*)daNpc_Mk_Delete__FPv,
    (void*)daNpc_Mk_Execute__FPv,
    (void*)daNpc_Mk_IsDelete__FPv,
    (void*)daNpc_Mk_Draw__FPv,
    (void*)NULL,
    (void*)NULL,
    (void*)NULL,
};

/* 80A73E28-80A73E58 -00001 0030+00 0/0 0/0 1/0 .data            g_profile_NPC_MK */
SECTION_DATA extern void* g_profile_NPC_MK[12] = {
    (void*)0xFFFFFFFD, (void*)0x0007FFFD,
    (void*)0x02A80000, (void*)&g_fpcLf_Method,
    (void*)0x00000001, (void*)NULL,
    (void*)NULL,       (void*)&g_fopAc_Method,
    (void*)0x01AB0000, (void*)&daNpc_Mk_MethodTable,
    (void*)0x020C4407, (void*)NULL,
};
