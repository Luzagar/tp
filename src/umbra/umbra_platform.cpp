#include "d/dolzel.h" // IWYU pragma: keep

#ifndef __REVOLUTION_SDK__

#include "umbra/umbra_platform.h"
#include "umbra/umbra_nintendont.h"
#include <dolphin/os.h>

#define UMBRA_SIGNATURE_ADDR  ((volatile u32*)0x93003430)
#define UMBRA_SIGNATURE_MAGIC 0x554D4252 /* "UMBR" */
#define PADREADGC_BASE        ((volatile u32*)0x93000000)

static UmbraPlatform s_platform = PLATFORM_UNKNOWN;
static bool s_detected = false;

UmbraPlatform umbraDetectPlatform() {
    if (s_detected) {
        return s_platform;
    }
    s_detected = true;

    u32 consoleType = *(volatile u32*)0x8000002C;

    // Dolphin always sets devkit console type (LatestDevkit = 0x10000006).
    if (consoleType & 0x10000000) {
        s_platform = PLATFORM_DOLPHIN;
        return s_platform;
    }

    // On Wii hardware (Nintendont), MEM2 is physically mapped.
    // Check for our fork's UMBR signature at 0x93003430.
    if (UMBRA_SIGNATURE_ADDR != NULL) {
        DCInvalidateRange((void*)UMBRA_SIGNATURE_ADDR, 4);
        u32 sig = *UMBRA_SIGNATURE_ADDR;
        if (sig == UMBRA_SIGNATURE_MAGIC) {
            s_platform = PLATFORM_NINTENDONT_UMBRA;
            return s_platform;
        }
    }

    // Upstream Nintendont: PADReadGC loaded at 0x93000000.
    // Jump table starts with PPC branch instructions.
    if (PADREADGC_BASE != NULL) {
        DCInvalidateRange((void*)PADREADGC_BASE, 16);
        u32 jt0 = PADREADGC_BASE[0];
        if ((jt0 >> 26) == 18) {
            s_platform = PLATFORM_NINTENDONT;
            return s_platform;
        }
    }

    // TODO: Swiss detection
    return s_platform;
}

bool umbraIsNintendont() {
    UmbraPlatform p = umbraDetectPlatform();
    return p == PLATFORM_NINTENDONT || p == PLATFORM_NINTENDONT_UMBRA;
}

#endif // !__REVOLUTION_SDK__
