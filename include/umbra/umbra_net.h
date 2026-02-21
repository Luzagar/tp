#ifndef UMBRA_NET_H
#define UMBRA_NET_H

#include "dolphin/types.h"

class umbraNet {
public:
    int sendUDP(u32 ip, u16 port, const void* data, u32 len);
    int recvUDP(void* buf, u32 maxLen);

    int connect(u32 ip, u16 port);
    int disconnect();
    int stateWrite(const void* data, u32 len);
    int stateRead(void* buf, u32 maxLen);

    static u32 makeIP(u8 a, u8 b, u8 c, u8 d) {
        return ((u32)a << 24) | ((u32)b << 16) | ((u32)c << 8) | (u32)d;
    }
};

#endif // UMBRA_NET_H
