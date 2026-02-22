#ifndef UMBRA_NINTENDONT_H
#define UMBRA_NINTENDONT_H

#include "dolphin/types.h"

#define NIN_MAILBOX_BASE 0xD3026800
#define NIN_MAILBOX_CMD  (*(volatile u32*)0xD3026800)
#define NIN_MAILBOX_DATA (*(volatile u32*)0xD3026804)

#define UMBRA_MAGIC 0x475A
#define UMBRA_CMD_WRITE 0x01
#define UMBRA_CMD_READ 0x02
#define UMBRA_CMD_DELETE 0x03
#define UMBRA_CMD_NET_SEND 0x04
#define UMBRA_CMD_NET_RECV 0x05
#define UMBRA_CMD_NET_CONNECT 0x06
#define UMBRA_CMD_NET_STATE_WRITE 0x07
#define UMBRA_CMD_NET_STATE_READ 0x08
#define UMBRA_CMD_NET_DISCONNECT 0x09

#define UMBRA_CMD_WORD(cmd) (((u32)UMBRA_MAGIC << 16) | ((u32)(cmd) << 8))

#define DMA_ALIGN(x) (((x) + 31) & ~31)

#define UMBRA_CARD_CHAN 0

#define UMBRA_EXI_CHAN 1
#define UMBRA_EXI_DEV 0

bool ninMailboxTransfer(void* buf, u32 len, u32 mode);
void ninReturnToLoader();
bool exiUmbraTransfer(void* buf, u32 len, u32 mode);
bool umbraTransfer(void* buf, u32 len, u32 mode);
bool umbraProbeEXI();

#endif // UMBRA_NINTENDONT_H
