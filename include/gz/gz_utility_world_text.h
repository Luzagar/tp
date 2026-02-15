#ifndef GZ_UTILITY_WORLD_TEXT_H
#define GZ_UTILITY_WORLD_TEXT_H

#include "SSystem/SComponent/c_xyz.h"

class gzTextBox;

struct gzScreenProjection {
    cXyz screenPos;
    f32 scale;
    bool visible;
};

void gzProjectToScreen(const cXyz& i_worldPos, f32 i_refHeight, gzScreenProjection& o_proj);
void gzDrawWorldText(gzTextBox* i_textBox, const cXyz& i_worldPos, f32 i_refHeight,
                     const char* i_text, u32 i_color, f32 i_xOffset = 0.0f,
                     f32 i_yOffset = 0.0f);

#endif // GZ_UTILITY_WORLD_TEXT_H
