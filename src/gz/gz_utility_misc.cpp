#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_utility_misc.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/J2DGraph/J2DPicture.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "dolphin/dvd.h"
#include "dolphin/gx/GXTexture.h"

static JKRExpHeap* s_gzHeap = NULL;
static const u32 GZ_HEAP_SIZE = 0xC0000;  // 768KB

J2DPicture* gzCopyArchiveTexture(JKRArchive* arc, const char* name, JKRHeap* heap) {
    ResTIMG* src = (ResTIMG*)arc->getResource('TIMG', name);
    if (src == NULL) return NULL;

    u32 imgSize = GXGetTexBufferSize(src->width, src->height, src->format,
                                      src->mipmapEnabled, src->mipmapCount);
    u32 totalSize = src->imageOffset + imgSize;
    void* buf = heap->alloc(totalSize, 32);
    if (buf == NULL) return NULL;

    memcpy(buf, src, totalSize);
    return new (heap, 4) J2DPicture((ResTIMG*)buf);
}

void gzDVDLoadFile(const char* filePath, void* buffer, int length, int offset) {
    DVDFileInfo ATTRIBUTE_ALIGN(32) fileInfo;
    if (DVDOpen(filePath, &fileInfo)) {
        int bytesRead = DVDReadPrio(&fileInfo, buffer, length, offset, 2);
        if (bytesRead > 0) {
            DVDClose(&fileInfo);
        } else {
            OSReport("no bytes read!\n");
        }
    } else {
        OSReport("failed to open file %s\n", filePath);
    }
}

void gzCreateHeap() {
    if (s_gzHeap != NULL) return;

    JKRExpHeap* archiveHeap = (JKRExpHeap*)mDoExt_getArchiveHeap();
    s_gzHeap = JKRExpHeap::create(GZ_HEAP_SIZE, archiveHeap, true);
}

void gzSetGzHeap(JKRHeap* heap) {
    s_gzHeap = (JKRExpHeap*)heap;
}

JKRHeap* gzGetGzHeap() {
    return s_gzHeap;
}

JKRHeap* gzHeap(gzGroupId_e groupId) {
    s_gzHeap->mCurrentGroupId = (u8)groupId;
    return s_gzHeap;
}
