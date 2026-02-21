#ifndef UMBRA_PLATFORM_H
#define UMBRA_PLATFORM_H

enum UmbraPlatform {
    PLATFORM_UNKNOWN,
    PLATFORM_NINTENDONT,
    PLATFORM_NINTENDONT_UMBRA,
    PLATFORM_DOLPHIN,
    PLATFORM_DOLPHIN_UMBRA, // doesn't exist... yet :^)
    PLATFORM_SWISS,
};

UmbraPlatform umbraDetectPlatform();
bool umbraIsNintendont();

#endif // UMBRA_PLATFORM_H
