/* Do NOT include d/dolzel.h — conflicts with targimpl.h struct definitions */

#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSException.h>
#include <dolphin/os/OSIC.h>

#include "umbra/umbra_gdb.h"
#include "umbra/umbra_nintendont.h"
#include "umbra/umbra_platform.h"

extern "C" {
    void OSReport(const char* msg, ...);
    void AIStopDMA(void);
    void AIStartDMA(void);
    BOOL OSDisableInterrupts(void);
    __OSExceptionHandler __OSSetExceptionHandler(__OSException exception,
                                                  __OSExceptionHandler handler);
    void OSLoadContext(OSContext* ctx);
}

/* Must match kernel/gdb.h */

#define GDB_SHM_BASE      ((volatile u32*)0xD3003600)
#define GDB_SHM_SIZE      512

#define GDB_SHM_MAGIC     0x47444253  /* "GDBS" */

#define GDB_STATE_IDLE    0
#define GDB_STATE_STOPPED 1
#define GDB_STATE_RESUME  2
#define GDB_STATE_STEP    3
#define GDB_STATE_DETACH  4

#define SHM_MAGIC       0
#define SHM_STATE       1
#define SHM_STOP_REASON 2
#define SHM_SIGNAL      3
#define SHM_GPR_BASE    4
#define SHM_PC          36
#define SHM_LR          37
#define SHM_CR          38
#define SHM_CTR         39
#define SHM_XER         40
#define SHM_MSR         41
#define SHM_FPR_BYTE_OFF   0x0A8
#define SHM_FPSCR_BYTE_OFF 0x1A8
#define SHM_HALT_REQ       108
#define SHM_PPC_HEARTBEAT  109
#define SHM_PPC_HALT_SEEN  110
#define SHM_EXIT_REQ       111
#define SHM_IC_INVAL_CNT   112
#define SHM_IC_INVAL_ADDR  113
#define SHM_TBU_SAVE       121
#define SHM_TBL_SAVE       122
#define SHM_DEC_SAVE       123

#define MSR_SE (1 << 10)
#define MSR_EE (1 << 15)

static u16 s_gdb_port = 2159;

/* Freeze PPC time during halt so game timers don't see a multi-second gap. */
static asm u32 get_tbu(void) { nofralloc; mftbu r3; blr; }
static asm u32 get_tbl(void) { nofralloc; mftb r3; blr; }
static asm u32 get_dec(void) { nofralloc; mfspr r3, 22; blr; }
static asm void set_tb(register u32 tbu, register u32 tbl) {
    nofralloc
    li r5, 0
    mtspr 284, r5
    mtspr 285, r3
    mtspr 284, r4
    blr
}
static asm void set_dec(register u32 val) { nofralloc; mtspr 22, r3; blr; }

static void save_timebase(void) {
    u32 tbu1, tbu2, tbl;
    do {
        tbu1 = get_tbu();
        tbl  = get_tbl();
        tbu2 = get_tbu();
    } while (tbu1 != tbu2);
    GDB_SHM_BASE[SHM_TBU_SAVE] = tbu1;
    GDB_SHM_BASE[SHM_TBL_SAVE] = tbl;
    GDB_SHM_BASE[SHM_DEC_SAVE] = get_dec();
}

static void restore_timebase(void) {
    set_tb(GDB_SHM_BASE[SHM_TBU_SAVE], GDB_SHM_BASE[SHM_TBL_SAVE]);
    set_dec(GDB_SHM_BASE[SHM_DEC_SAVE]);
}

static u32 s_saved_msr_ee = 0;

static void do_game_exit(void);

static u32 exception_to_signal(u32 exception_id) {
    switch (exception_id & 0xFFFF) {
    case 0x0200: return 11;
    case 0x0300: return 11;
    case 0x0400: return 11;
    case 0x0500: return 2;
    case 0x0600: return 11;
    case 0x0700: return 5;
    case 0x0800: return 8;
    case 0x0900: return 14;
    case 0x0D00: return 5;
    default:     return 5;
    }
}

/* ARM writes instructions to physical memory, bypassing PPC caches.
 * DCInvalidateRange prevents stale D-cache castouts from refilling L2.
 * ICInvalidateRange forces I-fetch from DRAM. */
static void process_ic_inval(void) {
    u32 cnt = GDB_SHM_BASE[SHM_IC_INVAL_CNT];
    if (cnt == 0)
        return;
    if (cnt > 8)
        cnt = 8;
    for (u32 i = 0; i < cnt; i++) {
        u32 addr = GDB_SHM_BASE[SHM_IC_INVAL_ADDR + i];
        DCInvalidateRange((void*)addr, 32);
        ICInvalidateRange((void*)addr, 4);
    }
    GDB_SHM_BASE[SHM_IC_INVAL_CNT] = 0;
}

static int start_gdb_server(u16 port) {
    if (!umbraHasUmbraSupport()) {
        return -1;
    }

    u8 buf[32] ATTRIBUTE_ALIGN(32);
    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);

    for (int i = 0; i < 32; i++) {
        buf[i] = 0;
        statusBuf[i] = 0;
    }

    *(u32*)(buf + 0) = UMBRA_CMD_WORD(UMBRA_CMD_GDB_START);
    buf[4] = (port >> 8) & 0xFF;
    buf[5] = port & 0xFF;

    if (!umbraTransfer(buf, sizeof(buf), 1) ||
        !umbraTransfer(statusBuf, sizeof(statusBuf), 0)) {
        return -1;
    }

    u32 status = *(u32*)(statusBuf + 0);
    return (status == 0) ? 0 : -1;
}

static void save_ctx_to_shm(OSContext* ctx, u32 exc_vector) {
    for (int i = 0; i < 32; i++)
        GDB_SHM_BASE[SHM_GPR_BASE + i] = ctx->gpr[i];

    GDB_SHM_BASE[SHM_PC]  = ctx->srr0;
    GDB_SHM_BASE[SHM_LR]  = ctx->lr;
    GDB_SHM_BASE[SHM_CR]  = ctx->cr;
    GDB_SHM_BASE[SHM_CTR] = ctx->ctr;
    GDB_SHM_BASE[SHM_XER] = ctx->xer;
    GDB_SHM_BASE[SHM_MSR] = ctx->srr1;

    volatile u64* fpr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPR_BYTE_OFF);
    for (int i = 0; i < 32; i++)
        fpr_shm[i] = *(volatile u64*)&ctx->fpr[i];

    volatile u64* fpscr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPSCR_BYTE_OFF);
    *fpscr_shm = (u64)ctx->fpscr;

    GDB_SHM_BASE[SHM_STOP_REASON] = exc_vector;
    GDB_SHM_BASE[SHM_SIGNAL] = exception_to_signal(exc_vector);
}

static void restore_shm_to_ctx(OSContext* ctx, u32 state) {
    for (int i = 0; i < 32; i++)
        ctx->gpr[i] = GDB_SHM_BASE[SHM_GPR_BASE + i];

    ctx->srr0 = GDB_SHM_BASE[SHM_PC];
    ctx->lr   = GDB_SHM_BASE[SHM_LR];
    ctx->cr   = GDB_SHM_BASE[SHM_CR];
    ctx->ctr  = GDB_SHM_BASE[SHM_CTR];
    ctx->xer  = GDB_SHM_BASE[SHM_XER];

    u32 msr = GDB_SHM_BASE[SHM_MSR];
    if (state == GDB_STATE_STEP)
        msr = (msr | MSR_SE) & ~MSR_EE;
    else
        msr = (msr & ~MSR_SE) | s_saved_msr_ee;
    ctx->srr1 = msr;

    volatile u64* fpr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPR_BYTE_OFF);
    for (int i = 0; i < 32; i++)
        *(volatile u64*)&ctx->fpr[i] = fpr_shm[i];
    volatile u64* fpscr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPSCR_BYTE_OFF);
    ctx->fpscr = (u32)*fpscr_shm;
}

static __OSExceptionHandler s_old_program_handler;
static __OSExceptionHandler s_old_trace_handler;

/* Forward declaration — C handler entered from asm stub. */
static void gdb_exc_handler(__OSException exception, OSContext* ctx);

/* OS exception trampoline saves r3-r5, CR, LR, CTR, XER, SRR0, SRR1.
 * This asm stub saves the remaining GPRs before entering C code,
 * so OSLoadContext can restore the full register set on resume. */
static asm void gdb_exc_asm_stub(void) {
    nofralloc
    stw     r0, OS_CONTEXT_R0(r4)
    stw     r1, OS_CONTEXT_R1(r4)
    stw     r2, OS_CONTEXT_R2(r4)
    stw     r6, OS_CONTEXT_R6(r4)
    stw     r7, OS_CONTEXT_R7(r4)
    stw     r8, OS_CONTEXT_R8(r4)
    stw     r9, OS_CONTEXT_R9(r4)
    stw     r10, OS_CONTEXT_R10(r4)
    stw     r11, OS_CONTEXT_R11(r4)
    stw     r12, OS_CONTEXT_R12(r4)
    stw     r13, OS_CONTEXT_R13(r4)
    stw     r14, OS_CONTEXT_R14(r4)
    stw     r15, OS_CONTEXT_R15(r4)
    stw     r16, OS_CONTEXT_R16(r4)
    stw     r17, OS_CONTEXT_R17(r4)
    stw     r18, OS_CONTEXT_R18(r4)
    stw     r19, OS_CONTEXT_R19(r4)
    stw     r20, OS_CONTEXT_R20(r4)
    stw     r21, OS_CONTEXT_R21(r4)
    stw     r22, OS_CONTEXT_R22(r4)
    stw     r23, OS_CONTEXT_R23(r4)
    stw     r24, OS_CONTEXT_R24(r4)
    stw     r25, OS_CONTEXT_R25(r4)
    stw     r26, OS_CONTEXT_R26(r4)
    stw     r27, OS_CONTEXT_R27(r4)
    stw     r28, OS_CONTEXT_R28(r4)
    stw     r29, OS_CONTEXT_R29(r4)
    stw     r30, OS_CONTEXT_R30(r4)
    stw     r31, OS_CONTEXT_R31(r4)
    stwu    r1, -8(r1)
    b       gdb_exc_handler
}

static void gdb_exc_handler(__OSException exception, OSContext* ctx) {
    OSReport("tpgz: gdb_exc_handler entered, exc=%d srr0=0x%08X\n",
             exception, ctx->srr0);

    if (GDB_SHM_BASE[SHM_MAGIC] != GDB_SHM_MAGIC) {
        OSReport("tpgz: SHM magic not set, chaining\n");
        __OSExceptionHandler old = (exception == __OS_EXCEPTION_PROGRAM) ?
            s_old_program_handler : s_old_trace_handler;
        if (old)
            old(exception, ctx);
        return;
    }

    u32 exc_vector = (exception == __OS_EXCEPTION_TRACE) ? 0xD00 : 0x700;

    /* Only save MSR_EE / timebase / stop DMA on initial break (Program exception).
     * Trace exceptions from single-step have MSR_EE deliberately cleared;
     * re-saving would lose the original EE state and resume with interrupts
     * permanently disabled — causing DVD errors, timer failures, etc. */
    if (exception != __OS_EXCEPTION_TRACE) {
        s_saved_msr_ee = ctx->srr1 & MSR_EE;
    }

    save_ctx_to_shm(ctx, exc_vector);

    /* Flush D-cache so ARM can read stack for backtrace.
     * Must happen before STATE=STOPPED so data is visible when ARM reads. */
    DCFlushRange((void*)(ctx->gpr[1] & ~0x1F), 32 * 1024);

    GDB_SHM_BASE[SHM_STATE] = GDB_STATE_STOPPED;

    if (exception != __OS_EXCEPTION_TRACE) {
        save_timebase();
        AIStopDMA();
    }

    OSReport("tpgz: waiting for debugger (vec=0x%X)\n", exc_vector);

    while (1) {
        u32 state = GDB_SHM_BASE[SHM_STATE];

        if (state == GDB_STATE_RESUME || state == GDB_STATE_STEP) {
            restore_shm_to_ctx(ctx, state);
            process_ic_inval();
            ICFlashInvalidate();
            if (state == GDB_STATE_RESUME) {
                restore_timebase();
                AIStartDMA();
            }
            OSLoadContext(ctx);
        } else if (state == GDB_STATE_DETACH) {
            u32 exit_req = GDB_SHM_BASE[SHM_EXIT_REQ];
            GDB_SHM_BASE[SHM_MAGIC] = 0;
            process_ic_inval();
            ICFlashInvalidate();
            restore_timebase();
            AIStartDMA();
            if (exit_req == 1) {
                GDB_SHM_BASE[SHM_EXIT_REQ] = 0;
                do_game_exit();
            }
            ctx->srr1 = (ctx->srr1 & ~MSR_SE) | s_saved_msr_ee;
            OSLoadContext(ctx);
        }
    }
}

static void install_exc_handlers(void) {
    s_old_program_handler = __OSSetExceptionHandler(
        __OS_EXCEPTION_PROGRAM, (__OSExceptionHandler)gdb_exc_asm_stub);
    s_old_trace_handler = __OSSetExceptionHandler(
        __OS_EXCEPTION_TRACE, (__OSExceptionHandler)gdb_exc_asm_stub);
}

extern "C" void umbra_gdb_auto_start(u16 port) {
    s_gdb_port = port;
    if (umbraIsNintendont()) {
        install_exc_handlers();
    }
    start_gdb_server(port);
}

static void save_regs_to_shm(void) {
    for (int i = 0; i < 32; i++)
        GDB_SHM_BASE[SHM_GPR_BASE + i] = gTRKCPUState.Default.GPR[i];

    GDB_SHM_BASE[SHM_PC]  = gTRKCPUState.Default.PC;
    GDB_SHM_BASE[SHM_LR]  = gTRKCPUState.Default.LR;
    GDB_SHM_BASE[SHM_CR]  = gTRKCPUState.Default.CR;
    GDB_SHM_BASE[SHM_CTR] = gTRKCPUState.Default.CTR;
    GDB_SHM_BASE[SHM_XER] = gTRKCPUState.Default.XER;
    GDB_SHM_BASE[SHM_MSR] = gTRKCPUState.Extended1.MSR;

    volatile u64* fpr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPR_BYTE_OFF);
    for (int i = 0; i < 32; i++)
        fpr_shm[i] = gTRKCPUState.Float.FPR[i];

    volatile u64* fpscr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPSCR_BYTE_OFF);
    *fpscr_shm = gTRKCPUState.Float.FPSCR;

    u32 exc_id = gTRKCPUState.Extended1.exceptionID;
    GDB_SHM_BASE[SHM_STOP_REASON] = exc_id;
    GDB_SHM_BASE[SHM_SIGNAL] = exception_to_signal(exc_id);
}

static void restore_regs_from_shm(u32 state) {
    for (int i = 0; i < 32; i++)
        gTRKCPUState.Default.GPR[i] = GDB_SHM_BASE[SHM_GPR_BASE + i];

    gTRKCPUState.Default.PC  = GDB_SHM_BASE[SHM_PC];
    gTRKCPUState.Default.LR  = GDB_SHM_BASE[SHM_LR];
    gTRKCPUState.Default.CR  = GDB_SHM_BASE[SHM_CR];
    gTRKCPUState.Default.CTR = GDB_SHM_BASE[SHM_CTR];
    gTRKCPUState.Default.XER = GDB_SHM_BASE[SHM_XER];

    u32 msr = GDB_SHM_BASE[SHM_MSR];
    if (state == GDB_STATE_STEP) {
        msr |= MSR_SE;
    } else {
        msr &= ~MSR_SE;
    }
    gTRKCPUState.Extended1.MSR = msr;

    volatile u64* fpr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPR_BYTE_OFF);
    for (int i = 0; i < 32; i++)
        gTRKCPUState.Float.FPR[i] = fpr_shm[i];
    volatile u64* fpscr_shm = (volatile u64*)((u8*)GDB_SHM_BASE + SHM_FPSCR_BYTE_OFF);
    gTRKCPUState.Float.FPSCR = *fpscr_shm;
}

static void gdb_spin_wait(void) {
    while (1) {
        u32 state = GDB_SHM_BASE[SHM_STATE];

        if (state == GDB_STATE_RESUME || state == GDB_STATE_STEP) {
            restore_regs_from_shm(state);
            process_ic_inval();
            ICFlashInvalidate();
            TRKSwapAndGo();
        }
        else if (state == GDB_STATE_DETACH) {
            u32 exit_req = GDB_SHM_BASE[SHM_EXIT_REQ];
            GDB_SHM_BASE[SHM_MAGIC] = 0;
            process_ic_inval();
            ICFlashInvalidate();
            if (exit_req == 1) {
                GDB_SHM_BASE[SHM_EXIT_REQ] = 0;
                do_game_exit();
            }
            TRKSwapAndGo();
        }
    }
}

#define PPC_RESET_STATUS  ((volatile u32*)0xD3003420)

/* Must match loader/source/ppc/PADReadGC/source/PADReadGC.c DoGameExit() */
static void do_game_exit(void) {
    OSDisableInterrupts();
    AIStopDMA();
    *PPC_RESET_STATUS = 0x1DEA;
    while (*PPC_RESET_STATUS == 0x1DEA)
        ;
    *(volatile u32*)0xCC00403C = 0xF;
    *(volatile u32*)0xCC004040 = 0;
    *(volatile u32*)0xCC004020 = 0xFF;
    volatile u32* dest = (volatile u32*)0x80004000;
    volatile u32* src  = (volatile u32*)0x93011810;
    u32 size = 0x1800;
    do { *dest++ = *src++; } while ((size -= 4) > 0);
    DCFlushRange((void*)0x80004000, 0x1800);
    ICInvalidateRange((void*)0x80004000, 0x1800);
    *(volatile u32*)0xCD800004 = 0x36;
    ((void(*)(void))0x80004000)();
}

extern "C" void umbra_gdb_poll(void) {
    static u32 heartbeat = 0;
    static bool exc_handlers_installed = false;

    /* SHM lives in uncached MEM2 — only exists on real Wii, not Dolphin. */
    if (!umbraIsNintendont())
        return;

    u32 magic = GDB_SHM_BASE[SHM_MAGIC];
    if (magic != GDB_SHM_MAGIC)
        return;

    if (!exc_handlers_installed) {
        exc_handlers_installed = true;
        install_exc_handlers();
    }

    /* Process any pending icache invalidation requests from ARM.
     * Critical after dirty disconnect: ARM restores original instructions
     * but PPC icache may still have stale trap instructions. */
    process_ic_inval();

    if (GDB_SHM_BASE[SHM_EXIT_REQ] == 1) {
        GDB_SHM_BASE[SHM_EXIT_REQ] = 0;
        do_game_exit();
    }

    u32 halt = GDB_SHM_BASE[SHM_HALT_REQ];
    GDB_SHM_BASE[SHM_PPC_HEARTBEAT] = ++heartbeat;
    GDB_SHM_BASE[SHM_PPC_HALT_SEEN] = halt;

    if (halt != 1)
        return;

    OSContext ctx;
    OSSaveContext(&ctx);

    /* OSSaveContext saves its own return address as LR, not our caller's. */
    u32 sp = ctx.gpr[1];
    u32 back_chain = *(volatile u32*)sp;
    if (back_chain >= 0x80000000 && back_chain < 0x81800000) {
        ctx.lr = *(volatile u32*)(back_chain + 4);
    }

    save_ctx_to_shm(&ctx, 0x0500);
    GDB_SHM_BASE[SHM_SIGNAL] = 2;
    GDB_SHM_BASE[SHM_STATE] = GDB_STATE_STOPPED;
    GDB_SHM_BASE[SHM_HALT_REQ] = 0;

    save_timebase();

    DCFlushRange((void*)(sp & ~0x1F), 32 * 1024);

    AIStopDMA();

    while (1) {
        u32 state = GDB_SHM_BASE[SHM_STATE];

        if (state == GDB_STATE_STEP) {
            process_ic_inval();
            ICFlashInvalidate();
            s_saved_msr_ee = ctx.srr1 & MSR_EE;
            ctx.srr1 = (ctx.srr1 | MSR_SE) & ~MSR_EE;
            OSLoadContext(&ctx);
        } else if (state == GDB_STATE_RESUME) {
            process_ic_inval();
            ICFlashInvalidate();
            restore_timebase();
            AIStartDMA();
            return;
        } else if (state == GDB_STATE_DETACH) {
            u32 exit_req = GDB_SHM_BASE[SHM_EXIT_REQ];
            GDB_SHM_BASE[SHM_MAGIC] = 0;
            process_ic_inval();
            ICFlashInvalidate();
            restore_timebase();
            AIStartDMA();
            if (exit_req == 1) {
                GDB_SHM_BASE[SHM_EXIT_REQ] = 0;
                do_game_exit();
            }
            return;
        }
    }
}

extern "C" void umbra_gdb_trk_hook(void) {
    if (!umbraIsNintendont())
        return;
    if (GDB_SHM_BASE[SHM_MAGIC] == GDB_SHM_MAGIC) {
        save_regs_to_shm();
        DCFlushRange((void*)(gTRKCPUState.Default.GPR[1] & ~0x1F), 32 * 1024);
        GDB_SHM_BASE[SHM_STATE] = GDB_STATE_STOPPED;
        gdb_spin_wait();
    }
}
