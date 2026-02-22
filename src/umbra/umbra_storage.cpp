#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "umbra/umbra_storage.h"
#include "umbra/umbra_nintendont.h"
#include <dolphin/card.h>
#include <dolphin/os.h>

static const u32 CMD_SIZE = 4;

#define SECTOR_SIZE 0x2000

int umbraStorageNintendont::write(const void* data, u32 size) {
    u32 payloadSize = CMD_SIZE + size;
    u32 bufSize = DMA_ALIGN(payloadSize);
    u8 buf[DMA_ALIGN(512)] ATTRIBUTE_ALIGN(32);
    if (bufSize > sizeof(buf)) {
        return -1;
    }

    memset(buf, 0, bufSize);
    *(u32*)buf = UMBRA_CMD_WORD(UMBRA_CMD_WRITE);
    memcpy(buf + CMD_SIZE, data, size);

    if (!umbraTransfer(buf, bufSize, 1)) {
        return -1;
    }

    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));
    umbraTransfer(statusBuf, sizeof(statusBuf), 0);
    u32 status = *(u32*)statusBuf;
    return (status == 0) ? 0 : -1;
}

int umbraStorageNintendont::read(void* data, u32 size) {
    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = UMBRA_CMD_WORD(UMBRA_CMD_READ);
    if (!umbraTransfer(cmdBuf, sizeof(cmdBuf), 1)) {
        return -1;
    }

    u32 bufSize = DMA_ALIGN(size);
    u8 buf[DMA_ALIGN(512)] ATTRIBUTE_ALIGN(32);
    if (bufSize > sizeof(buf)) {
        return -1;
    }

    memset(buf, 0, bufSize);
    if (!umbraTransfer(buf, bufSize, 0)) {
        return -1;
    }

    memcpy(data, buf, size);
    return 0;
}

int umbraStorageNintendont::remove() {
    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = UMBRA_CMD_WORD(UMBRA_CMD_DELETE);
    if (!umbraTransfer(cmdBuf, sizeof(cmdBuf), 1)) {
        return -1;
    }

    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));
    umbraTransfer(statusBuf, sizeof(statusBuf), 0);
    u32 status = *(u32*)statusBuf;
    return (status == 0) ? 0 : -1;
}

int umbraStorageMemcard::write(const void* data, u32 size) {
    s32 result;
    CARDFileInfo fileInfo;

    result = CARDProbeEx(UMBRA_CARD_CHAN, NULL, NULL);
    if (result != CARD_RESULT_READY) {
        return -1;
    }

    result = CARDCreate(UMBRA_CARD_CHAN, mFilename, SECTOR_SIZE, &fileInfo);
    if (result == CARD_RESULT_READY || result == CARD_RESULT_EXIST) {
        result = CARDOpen(UMBRA_CARD_CHAN, mFilename, &fileInfo);
        if (result != CARD_RESULT_READY) {
            return -1;
        }
    } else {
        return -1;
    }

    u8 writeBuf[SECTOR_SIZE] ATTRIBUTE_ALIGN(32);
    memset(writeBuf, 0, sizeof(writeBuf));
    if (size <= sizeof(writeBuf)) {
        memcpy(writeBuf, data, size);
    }

    result = CARDWrite(&fileInfo, writeBuf, SECTOR_SIZE, 0);
    CARDClose(&fileInfo);
    return (result == CARD_RESULT_READY) ? 0 : -1;
}

int umbraStorageMemcard::read(void* data, u32 size) {
    s32 result;
    CARDFileInfo fileInfo;

    result = CARDProbeEx(UMBRA_CARD_CHAN, NULL, NULL);
    if (result != CARD_RESULT_READY) {
        return -1;
    }

    result = CARDOpen(UMBRA_CARD_CHAN, mFilename, &fileInfo);
    if (result != CARD_RESULT_READY) {
        return -1;
    }

    u8 readBuf[SECTOR_SIZE] ATTRIBUTE_ALIGN(32);
    memset(readBuf, 0, sizeof(readBuf));

    result = CARDRead(&fileInfo, readBuf, SECTOR_SIZE, 0);
    CARDClose(&fileInfo);

    if (result != CARD_RESULT_READY) {
        return -1;
    }
    if (size <= sizeof(readBuf)) {
        memcpy(data, readBuf, size);
    }
    return 0;
}

int umbraStorageMemcard::remove() {
    s32 result;

    result = CARDProbeEx(UMBRA_CARD_CHAN, NULL, NULL);
    if (result != CARD_RESULT_READY) {
        return -1;
    }

    result = CARDDelete(UMBRA_CARD_CHAN, mFilename);
    return (result == CARD_RESULT_READY) ? 0 : -1;
}

#endif // !__REVOLUTION_SDK__
