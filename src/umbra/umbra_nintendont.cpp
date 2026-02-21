#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "umbra/umbra_nintendont.h"
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

#endif // !__REVOLUTION_SDK__
