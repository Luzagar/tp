#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "umbra/umbra_nintendont.h"
#include "umbra/umbra_platform.h"
#include <dolphin/exi.h>
#include <dolphin/os.h>

bool ninMailboxTransfer(void* buf, u32 len, u32 mode) {
    volatile u32* mailbox = (volatile u32*)NIN_MAILBOX_BASE;

    if (mode == 1) {
        DCFlushRange(buf, len);
    } else {
        // Stamp magic so kernel can identify this as an umbra read.
        // The kernel overwrites the buffer with response data.
        if (len >= 4) {
            *(u32*)buf = UMBRA_CMD_WORD(0);
        }
        DCFlushRange(buf, len);
    }

    u32 physAddr = (u32)buf & 0x1FFFFFFF;

    // Command format must match EXIDMA.S:
    // EXI_CMD_1 = data pointer (physical)
    // EXI_CMD_0 = 0x12000000 | (chn << 20) | (mode << 16) | (len & 0xFFFF)
    mailbox[1] = physAddr;
    mailbox[0] = 0x12000000 | (0 << 20) | ((mode & 0xF) << 16) | (len & 0xFFFF);

    // Poll until kernel clears the command. SD card writes can take
    // hundreds of ms.
    for (int i = 0; i < 500000000; i++) {
        if (mailbox[0] == 0) {
            if (mode == 0) {
                DCInvalidateRange(buf, len);
            }
            return true;
        }
    }

    return false;
}

void ninReturnToLoader() {
    ((void (*)(void))0x93000008)();
}

bool exiUmbraTransfer(void* buf, u32 len, u32 mode) {
    s32 chan = UMBRA_EXI_CHAN;
    u32 dev = UMBRA_EXI_DEV;

    if (mode == EXI_WRITE) {
        DCFlushRange(buf, len);
    }

    if (!EXILock(chan, dev, NULL)) {
        return false;
    }
    if (!EXISelect(chan, dev, EXI_FREQ_8M)) {
        EXIUnlock(chan);
        return false;
    }

    BOOL ok = EXIDma(chan, buf, (s32)len, mode, NULL);
    if (ok) {
        ok = EXISync(chan);
    }

    EXIDeselect(chan);
    EXIUnlock(chan);

    if (!ok) {
        return false;
    }

    if (mode == EXI_READ) {
        DCInvalidateRange(buf, len);
    }

    return true;
}

bool umbraTransfer(void* buf, u32 len, u32 mode) {
    UmbraPlatform p = umbraDetectPlatform();
    if (p == PLATFORM_NINTENDONT_UMBRA) {
        return ninMailboxTransfer(buf, len, mode);
    } else if (p == PLATFORM_DOLPHIN_UMBRA) {
        return exiUmbraTransfer(buf, len, mode);
    }
    return false;
}

bool umbraProbeEXI() {
    // Send CMD_NET_STATE_READ (safe, read-only) and check for a known
    // status response.  When not connected, CEXIUmbra returns
    // STATUS_NET_NOT_CONN (0x09) in the first 4 bytes.
    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = UMBRA_CMD_WORD(UMBRA_CMD_NET_STATE_READ);
    DCFlushRange(cmdBuf, sizeof(cmdBuf));

    s32 chan = UMBRA_EXI_CHAN;
    u32 dev = UMBRA_EXI_DEV;

    if (!EXILock(chan, dev, NULL)) {
        return false;
    }
    if (!EXISelect(chan, dev, EXI_FREQ_8M)) {
        EXIUnlock(chan);
        return false;
    }

    BOOL ok = EXIDma(chan, cmdBuf, sizeof(cmdBuf), EXI_WRITE, NULL);
    if (ok) ok = EXISync(chan);
    EXIDeselect(chan);

    if (!ok) {
        EXIUnlock(chan);
        return false;
    }

    u8 respBuf[32] ATTRIBUTE_ALIGN(32);
    memset(respBuf, 0xFF, sizeof(respBuf));
    DCFlushRange(respBuf, sizeof(respBuf));

    if (!EXISelect(chan, dev, EXI_FREQ_8M)) {
        EXIUnlock(chan);
        return false;
    }

    ok = EXIDma(chan, respBuf, sizeof(respBuf), EXI_READ, NULL);
    if (ok) ok = EXISync(chan);
    EXIDeselect(chan);
    EXIUnlock(chan);

    if (!ok) {
        return false;
    }

    DCInvalidateRange(respBuf, sizeof(respBuf));

    // CEXIUmbra returns STATUS_NET_NOT_CONN (0x09) when no socket is open.
    // A real memory card or empty slot should not produce this value.
    u32 status = *(u32*)respBuf;
    return (status == 0x09);
}

#endif // !__REVOLUTION_SDK__
