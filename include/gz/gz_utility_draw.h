#ifndef GZ_UTILITY_DRAW_H
#define GZ_UTILITY_DRAW_H

#include <dolphin/gx.h>

struct ResTIMG;

void gzDrawRectOutline(f32 x, f32 y, f32 w, f32 h, f32 thickness, GXColor color);
void gzDrawFilledRect(f32 x, f32 y, f32 w, f32 h, GXColor color);
void gzDrawFilledRoundedTopRect(f32 x, f32 y, f32 w, f32 h, f32 radius, GXColor color);
void gzDrawVerticalLine(f32 x, f32 y1, f32 y2, f32 thickness, GXColor color);
void gzDrawHorizontalLine(f32 x1, f32 x2, f32 y, f32 thickness, GXColor color);
void gzDrawFilledCircle(f32 cx, f32 cy, f32 radius, GXColor fillColor, GXColor outlineColor,
                        f32 outlineWidth);
GXColor gzGetThemedBorderColor(u32 theme, u8 alpha);
GXColor gzGetThemedHighlightColor(u32 theme, u8 alpha);
GXColor gzGetThemedSeparatorColor(u32 theme, u8 alpha);
void gzDrawAtlasIcon(ResTIMG* atlas, int iconIndex, int iconSize, int iconCount,
                     f32 x, f32 y, f32 w, f32 h, GXColor color);
int gzPrint(int x, int y, u32 color, char const* string, ...);

#endif // GZ_UTILITY_DRAW_H
