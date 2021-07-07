#include "Button.h"

Button* InitButton(Button* b, char* str, u32 color, Vector2f pos, Vector2f size, float textSize, C2D_Font font, C2D_TextBuf textbuf) {
    b->pos = pos;
    b->size = size;
    b->textSize = textSize;
    b->str = str;
    b->color = color;

    C2D_TextFontParse(&b->text, font, textbuf, b->str);
    C2D_TextOptimize (&b->text);

    return b;
}

int ButtonPressed(Button* b, touchPosition pos) {
    return (pos.px >= b->pos.x && pos.px <= b->pos.x + b->size.x && pos.py >= b->pos.y && pos.py <= b->pos.y + b->size.y && ButtonDown(KEY_TOUCH));
}

void DrawButton(Button* b, Vector2f origin) {
    C2D_DrawRectSolid(b->pos.x,  b->pos.y, 0, b->size.x, b->size.y, b->color);
    C2D_DrawText (&b->text, C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, b->pos.x + origin.x, b->pos.y + origin.y, 0, b->textSize, b->textSize, 
                        C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
}