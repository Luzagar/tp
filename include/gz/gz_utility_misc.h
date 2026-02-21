#ifndef GZ_UTILITY_MISC_H
#define GZ_UTILITY_MISC_H

#include "dolphin/types.h"

class J2DPicture;
class JKRArchive;
class JKRHeap;

enum gzGroupId_e {
    GZ_GROUP_MIN      = 0x60,

    GZ_GROUP_TEXTBOX  = 0x60,
    GZ_GROUP_MENU     = 0x61,
    GZ_GROUP_UI       = 0x62,
    GZ_GROUP_GRAPHICS = 0x63,
    GZ_GROUP_TRACKER  = 0x64,
    GZ_GROUP_OTHER    = 0x65,

    GZ_GROUP_MAX      = 0x66,
};

inline bool gzIsGzGroupId(u8 groupId) {
    return groupId >= GZ_GROUP_MIN && groupId < GZ_GROUP_MAX;
}

J2DPicture* gzCopyArchiveTexture(JKRArchive* arc, const char* name, JKRHeap* heap);
void gzDVDLoadFile(const char* filePath, void* buffer, int length, int offset);
void gzCreateHeap();
void gzSetGzHeap(JKRHeap* heap);
JKRHeap* gzGetGzHeap();
JKRHeap* gzHeap(gzGroupId_e groupId);

#endif // GZ_UTILITY_MISC_H
