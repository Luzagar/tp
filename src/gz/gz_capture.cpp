#include "d/dolzel.h" // IWYU pragma: keep

#include "gz/gz_capture.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_mtx.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/gx/GXCull.h"
#include "dolphin/gx/GXTransform.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GXTev.h"
#include "dolphin/gx/GXLighting.h"

void gzCapture_c::draw() {
    if (mFlag == 0) {
        return;
    } else if (mFlag == 1) {
        mFlag = 3;
        GXSetTexCopySrc(0, 0, FB_WIDTH, FB_HEIGHT);
        GXSetTexCopyDst(FB_WIDTH / 2, FB_HEIGHT / 2, (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_ENABLE);
        GXCopyTex(mDoGph_gInf_c::getFrameBufferTex(), GX_FALSE);
        GXPixModeSync();
        dComIfGp_onPauseFlag();
    } else {
        GXTexObj tex;
        GXInitTexObj(&tex, mDoGph_gInf_c::getFrameBufferTex(), FB_WIDTH / 2, FB_HEIGHT / 2,
                    (GXTexFmt)mDoGph_gInf_c::getFrameBufferTimg()->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&tex, GX_TEXMAP0);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        const GXColor color = {0, 0, 0, mAlpha};
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetZCompLoc(GX_TRUE);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
        GXSetFogRangeAdj(GX_FALSE, 0, NULL);
        GXSetCullMode(GX_CULL_NONE);
        GXSetDither(GX_TRUE);
        GXLoadPosMtxImm(g_mDoMtx_identity, GX_PNMTX0);
        GXSetCurrentMtx(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_RGBA4, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGB8, 0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3s16(mDoGph_gInf_c::getMinX(), mDoGph_gInf_c::getMinY(), 0);
        GXTexCoord2s8(0, 0);
        GXPosition3s16(mDoGph_gInf_c::getMaxX(), mDoGph_gInf_c::getMinY(), 0);
        GXTexCoord2s8(1, 0);
        GXPosition3s16(mDoGph_gInf_c::getMaxX(), mDoGph_gInf_c::getMaxY(), 0);
        GXTexCoord2s8(1, 1);
        GXPosition3s16(mDoGph_gInf_c::getMinX(), mDoGph_gInf_c::getMaxY(), 0);
        GXTexCoord2s8(0, 1);
        GXEnd();
    }
}
