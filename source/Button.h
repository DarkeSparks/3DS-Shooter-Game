#ifndef BUTTON_H
#define BUTTON_H

#include <citro2d.h>
#include <stdlib.h>

#include "Game.h"
#include "Math.h"

typedef struct Button {
    Vector2f pos, size;
    float textSize;

    u32 color;

    C2D_Text text;
    char* str;
} Button;

Button* InitButton(Button* b, char* str, u32 color, Vector2f pos, Vector2f size, float textSize, C2D_Font font, C2D_TextBuf textbuf);
int ButtonPressed(Button* b, touchPosition pos);
void DrawButton(Button* b, Vector2f origin);

#endif