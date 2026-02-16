#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "gz/gz.h"
#include <dolphin/exi.h>
#include <dolphin/os.h>

// Use memory card slot A (channel 0) — the patched EXIDMA stub works here.
// We call ONLY EXIDma (the patched stub doesn't need Lock/Select/Sync/etc).
// Calling those real SDK functions corrupts the memory card subsystem state.
#define SD_EXI_CHAN  0

// "GZ" magic in top 16 bits distinguishes TPGZ traffic from memory card DMA.
// Command word layout: [magic(16) | cmd(8) | reserved(8)]
#define TPGZ_MAGIC      0x475A
#define TPGZ_CMD_WRITE  0x01
#define TPGZ_CMD_READ   0x02
#define TPGZ_CMD_DELETE 0x03

#define TPGZ_CMD_WORD(cmd) (((u32)TPGZ_MAGIC << 16) | ((u32)(cmd) << 8))

// EXI DMA requires length to be a multiple of 32 bytes.
#define DMA_ALIGN(x) (((x) + 31) & ~31)

// Minimal EXI transfer: only DCFlush/DCInvalidate + EXIDma.
// The patched EXIDMA stub doesn't check EXI state (Lock/Select/etc),
// so we skip those to avoid corrupting the memory card subsystem.
static bool exiTransfer(void* buf, u32 len, u32 mode) {
    if (mode == EXI_WRITE) {
        DCFlushRange(buf, len);
    }

    bool ok = EXIDma(SD_EXI_CHAN, buf, len, mode, NULL);

    if (mode == EXI_READ) {
        DCInvalidateRange(buf, len);
    }

    return ok;
}

bool gzInfo_c::detectNintendont() {
    // Probe for Nintendont's patched EXIDMA stub.
    // The stub always returns 1 and doesn't require EXISelect.
    // The real SDK EXIDma checks STATE_SELECTED and returns 0 without it.
    u8 probeBuf[32] ATTRIBUTE_ALIGN(32);
    memset(probeBuf, 0, sizeof(probeBuf));
    DCFlushRange(probeBuf, sizeof(probeBuf));
    bool result = EXIDma(SD_EXI_CHAN, probeBuf, sizeof(probeBuf), EXI_WRITE, NULL);
    return result;
}

int gzInfo_c::storeSettingsSD() {
    // DMA write: [cmd_word(4B) | header | settings] padded to 32-byte boundary
    static const u32 PAYLOAD_SIZE = 4 + sizeof(gzConfigHeader_s) + sizeof(gzSettings_s);
    static const u32 BUF_SIZE = DMA_ALIGN(PAYLOAD_SIZE);
    u8 buf[BUF_SIZE] ATTRIBUTE_ALIGN(32);
    memset(buf, 0, sizeof(buf));
    *(u32*)buf = TPGZ_CMD_WORD(TPGZ_CMD_WRITE);

    gzConfigHeader_s cfg;
    cfg.version = GZ_SAVE_VERSION;
    cfg.settingsOffset = sizeof(gzConfigHeader_s);
    memset(cfg.reserved, 0, sizeof(cfg.reserved));
    memcpy(buf + 4, &cfg, sizeof(gzConfigHeader_s));
    memcpy(buf + 4 + cfg.settingsOffset, &mSettings, sizeof(gzSettings_s));

    if (!exiTransfer(buf, BUF_SIZE, EXI_WRITE)) {
        gzInfo_sendNotification("SD save FAILED (DMA err)");
        return -1;
    }

    // Read back kernel status
    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));
    exiTransfer(statusBuf, sizeof(statusBuf), EXI_READ);
    u32 status = *(u32*)statusBuf;
    if (status != 0) {
        gzInfo_sendNotification("SD save FAILED (write err)");
        return -1;
    }

    gzInfo_sendNotification("settings saved to SD!");
    gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
    return 0;
}

int gzInfo_c::loadSettingsSD() {
    // DMA write: send READ command
    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = TPGZ_CMD_WORD(TPGZ_CMD_READ);
    if (!exiTransfer(cmdBuf, sizeof(cmdBuf), EXI_WRITE)) {
        gzInfo_sendNotification("SD load FAILED (cmd err)");
        return -1;
    }

    // DMA read: receive settings
    static const u32 DATA_SIZE = sizeof(gzConfigHeader_s) + sizeof(gzSettings_s);
    static const u32 BUF_SIZE = DMA_ALIGN(DATA_SIZE);
    u8 buf[BUF_SIZE] ATTRIBUTE_ALIGN(32);
    memset(buf, 0, BUF_SIZE);
    if (!exiTransfer(buf, BUF_SIZE, EXI_READ)) {
        gzInfo_sendNotification("SD load FAILED (read err)");
        return -1;
    }

    gzConfigHeader_s cfg;
    memcpy(&cfg, buf, sizeof(gzConfigHeader_s));
    if (cfg.version == 0) {
        gzInfo_sendNotification("SD load FAILED (not found)");
        return -1;
    }
    if (cfg.version != GZ_SAVE_VERSION) {
        OSReport("TPGZ: outdated SD save version %d (expected %d)\n", cfg.version, GZ_SAVE_VERSION);
        gzInfo_sendNotification("SD load FAILED (version)");
        return -1;
    }
    memcpy(&mSettings, buf + cfg.settingsOffset, sizeof(gzSettings_s));
    gzInfo_sendNotification("settings loaded from SD!");
    gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
    return 0;
}

int gzInfo_c::deleteSettingsSD() {
    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = TPGZ_CMD_WORD(TPGZ_CMD_DELETE);
    if (!exiTransfer(cmdBuf, sizeof(cmdBuf), EXI_WRITE)) {
        gzInfo_sendNotification("SD delete FAILED (DMA err)");
        return -1;
    }

    // Read back kernel status
    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));
    exiTransfer(statusBuf, sizeof(statusBuf), EXI_READ);
    u32 status = *(u32*)statusBuf;
    if (status != 0) {
        gzInfo_sendNotification("SD delete FAILED");
        return -1;
    }

    gzInfo_sendNotification("SD settings deleted!");
    gzInfo_seStart(Z2SE_SY_CONTINUE_OK);
    return 0;
}

void gzInfo_c::returnToLoader() {
    if (!mIsNintendont) {
        gzInfo_sendNotification("exit requires nintendont");
        return;
    }
    // Call DoGameExit in PADReadGC binary
    ((void(*)(void))0x93000008)();
}

#endif // !__REVOLUTION_SDK__

int gzInfo_c::storeSettings() {
#ifndef __REVOLUTION_SDK__
    if (mIsNintendont) {
        return storeSettingsSD();
    }
#endif
    return storeSettingsMemcard();
}

int gzInfo_c::loadSettings() {
#ifndef __REVOLUTION_SDK__
    if (mIsNintendont) {
        return loadSettingsSD();
    }
#endif
    return loadSettingsMemcard();
}

int gzInfo_c::deleteSettings() {
#ifndef __REVOLUTION_SDK__
    if (mIsNintendont) {
        return deleteSettingsSD();
    }
#endif
    return deleteSettingsMemcard();
}
