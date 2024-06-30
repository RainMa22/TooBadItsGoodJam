#include "raylib.h"
#include "raymath.h"

#ifndef DRAWUTILS_H
#define DRAWUTILS_H

void DrawTextCenteredEx(Font font, const char *text, int centerX, int centerY, int textSize,float gap, Color color)
{
    Vector2 size = MeasureTextEx(GetFontDefault(), text, textSize, gap);
    DrawTextEx(font, text, (Vector2){centerX - size.x / 2, centerY - size.y}, textSize, gap, color);
}

void DrawTextCentered(const char *text, int centerX, int centerY, int textSize, Color color)
{
    DrawTextCenteredEx(GetFontDefault(),text,centerX,centerY,textSize,1.0f,color);
}


#endif /*DRAWUTILS_H*/