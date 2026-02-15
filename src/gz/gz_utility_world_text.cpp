#include "gz/gz_utility_world_text.h"
#include "gz/gz_textbox.h"
#include "m_Do/m_Do_lib.h"
#include <cmath>

static const f32 MIN_FONT_SIZE = 8.0f;
static const f32 MAX_FONT_SIZE = 72.0f;

void gzProjectToScreen(const cXyz& i_worldPos, f32 i_refHeight, gzScreenProjection& o_proj) {
    cXyz screenPos;
    mDoLib_project(const_cast<cXyz*>(&i_worldPos), &screenPos);

    cXyz abovePos(i_worldPos.x, i_worldPos.y + i_refHeight, i_worldPos.z);
    cXyz aboveScreen;
    mDoLib_project(&abovePos, &aboveScreen);

    f32 pixelHeight = fabsf(screenPos.y - aboveScreen.y);

    o_proj.screenPos = screenPos;
    o_proj.scale = pixelHeight * 2.0f;
    o_proj.visible = (screenPos.z < 1.0f);
}

void gzDrawWorldText(gzTextBox* i_textBox, const cXyz& i_worldPos, f32 i_refHeight,
                     const char* i_text, u32 i_color, f32 i_xOffset, f32 i_yOffset) {
    if (i_textBox == NULL) {
        return;
    }

    gzScreenProjection proj;
    gzProjectToScreen(i_worldPos, i_refHeight, proj);

    if (!proj.visible) {
        return;
    }

    f32 fontSize = proj.scale;
    if (fontSize < MIN_FONT_SIZE) fontSize = MIN_FONT_SIZE;
    if (fontSize > MAX_FONT_SIZE) fontSize = MAX_FONT_SIZE;

    i_textBox->setFontSize(fontSize, fontSize);
    i_textBox->setString(i_text);
    i_textBox->draw(proj.screenPos.x + i_xOffset * fontSize,
                    proj.screenPos.y + i_yOffset * fontSize, i_color);
}
