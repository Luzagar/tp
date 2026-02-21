#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "umbra/umbra_net.h"
#include "umbra/umbra_nintendont.h"
#include "umbra/umbra_platform.h"
#include <dolphin/os.h>

int umbraNet::sendUDP(u32 ip, u16 port, const void* data, u32 len) {
    if (!umbraIsNintendont()) {
        return -1;
    }

    if (len > 1400) {
        len = 1400;
    }

    u32 totalSize = DMA_ALIGN(12 + len);
    u8 buf[DMA_ALIGN(12 + 1400)] ATTRIBUTE_ALIGN(32);
    memset(buf, 0, totalSize);

    *(u32*)(buf + 0) = UMBRA_CMD_WORD(UMBRA_CMD_NET_SEND);
    buf[4] = (ip >> 24) & 0xFF;
    buf[5] = (ip >> 16) & 0xFF;
    buf[6] = (ip >> 8) & 0xFF;
    buf[7] = ip & 0xFF;
    buf[8] = (port >> 8) & 0xFF;
    buf[9] = port & 0xFF;
    buf[10] = (len >> 8) & 0xFF;
    buf[11] = len & 0xFF;
    memcpy(buf + 12, data, len);

    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));

    if (!ninMailboxTransfer(buf, totalSize, 1) ||
        !ninMailboxTransfer(statusBuf, sizeof(statusBuf), 0)) {
        return -1;
    }

    u32 status = *(u32*)(statusBuf + 0);
    if (status != 0) {
        return -1;
    }

    return 0;
}

int umbraNet::connect(u32 ip, u16 port) {
    if (!umbraIsNintendont()) {
        return -1;
    }

    u8 buf[32] ATTRIBUTE_ALIGN(32);
    memset(buf, 0, sizeof(buf));

    *(u32*)(buf + 0) = UMBRA_CMD_WORD(UMBRA_CMD_NET_CONNECT);
    buf[4] = (ip >> 24) & 0xFF;
    buf[5] = (ip >> 16) & 0xFF;
    buf[6] = (ip >> 8) & 0xFF;
    buf[7] = ip & 0xFF;
    buf[8] = (port >> 8) & 0xFF;
    buf[9] = port & 0xFF;

    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));

    if (!ninMailboxTransfer(buf, sizeof(buf), 1) ||
        !ninMailboxTransfer(statusBuf, sizeof(statusBuf), 0)) {
        return -1;
    }

    u32 status = *(u32*)(statusBuf + 0);
    return (status == 0) ? 0 : -1;
}

int umbraNet::disconnect() {
    if (!umbraIsNintendont()) {
        return -1;
    }

    u8 buf[32] ATTRIBUTE_ALIGN(32);
    memset(buf, 0, sizeof(buf));
    *(u32*)buf = UMBRA_CMD_WORD(UMBRA_CMD_NET_DISCONNECT);

    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));

    if (!ninMailboxTransfer(buf, sizeof(buf), 1) ||
        !ninMailboxTransfer(statusBuf, sizeof(statusBuf), 0)) {
        return -1;
    }

    u32 status = *(u32*)(statusBuf + 0);
    return (status == 0) ? 0 : -1;
}

int umbraNet::stateWrite(const void* data, u32 len) {
    if (!umbraIsNintendont()) {
        return -1;
    }

    if (len > 1400) {
        len = 1400;
    }

    u32 totalSize = DMA_ALIGN(4 + len);
    u8 buf[DMA_ALIGN(4 + 1400)] ATTRIBUTE_ALIGN(32);
    memset(buf, 0, totalSize);

    *(u32*)(buf + 0) = UMBRA_CMD_WORD(UMBRA_CMD_NET_STATE_WRITE);
    memcpy(buf + 4, data, len);

    u8 statusBuf[32] ATTRIBUTE_ALIGN(32);
    memset(statusBuf, 0, sizeof(statusBuf));

    if (!ninMailboxTransfer(buf, totalSize, 1) ||
        !ninMailboxTransfer(statusBuf, sizeof(statusBuf), 0)) {
        return -1;
    }

    u32 status = *(u32*)(statusBuf + 0);
    return (status == 0) ? 0 : -1;
}

int umbraNet::stateRead(void* buf, u32 maxLen) {
    if (!umbraIsNintendont()) {
        return -1;
    }

    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = UMBRA_CMD_WORD(UMBRA_CMD_NET_STATE_READ);

    u32 readSize = DMA_ALIGN(8 + maxLen);
    u8 readBuf[DMA_ALIGN(8 + 1400)] ATTRIBUTE_ALIGN(32);
    memset(readBuf, 0, readSize);

    if (!ninMailboxTransfer(cmdBuf, sizeof(cmdBuf), 1) ||
        !ninMailboxTransfer(readBuf, readSize, 0)) {
        return -1;
    }

    u32 status = *(u32*)(readBuf + 0);
    u32 dataLen = *(u32*)(readBuf + 4);

    if (status != 0) {
        return -1;
    }
    if (dataLen == 0) {
        return 0;
    }
    if (dataLen > maxLen) {
        dataLen = maxLen;
    }

    memcpy(buf, readBuf + 8, dataLen);
    return (int)dataLen;
}

int umbraNet::recvUDP(void* buf, u32 maxLen) {
    if (!umbraIsNintendont()) {
        return -1;
    }

    u8 cmdBuf[32] ATTRIBUTE_ALIGN(32);
    memset(cmdBuf, 0, sizeof(cmdBuf));
    *(u32*)cmdBuf = UMBRA_CMD_WORD(UMBRA_CMD_NET_RECV);

    u32 readSize = DMA_ALIGN(8 + maxLen);
    u8 readBuf[DMA_ALIGN(8 + 1400)] ATTRIBUTE_ALIGN(32);
    memset(readBuf, 0, readSize);

    if (!ninMailboxTransfer(cmdBuf, sizeof(cmdBuf), 1) ||
        !ninMailboxTransfer(readBuf, readSize, 0)) {
        return -1;
    }

    u32 status = *(u32*)(readBuf + 0);
    u32 dataLen = *(u32*)(readBuf + 4);

    if (status != 0) {
        return -1;
    }
    if (dataLen == 0) {
        return 0;
    }
    if (dataLen > maxLen) {
        dataLen = maxLen;
    }

    memcpy(buf, readBuf + 8, dataLen);
    return (int)dataLen;
}

#endif // !__REVOLUTION_SDK__
