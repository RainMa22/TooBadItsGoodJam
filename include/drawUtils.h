#include "sceneDefinitions.h"

#ifndef DRAWUTILS_H
#define DRAWUTILS_H

void DrawTextCenteredEx(Font font, const char *text, int centerX, int centerY, int textSize, float gap, Color color)
{
    Vector2 size = MeasureTextEx(GetFontDefault(), text, textSize, gap);
    DrawTextEx(font, text, (Vector2){centerX - size.x / 2, centerY - size.y/2}, textSize, gap, color);
}

void DrawTextCentered(const char *text, int centerX, int centerY, int textSize, Color color)
{
    DrawTextCenteredEx(GetFontDefault(), text, centerX, centerY, textSize, 1.0f, color);
}

// EFFECT: converts relative xy coordinates to absolute xy coordinate
Vector2 relativeToAbsolute(Vector2 parent, Vector2 child)
{
    return (Vector2){parent.x + child.x, parent.y + child.y};
}



Rectangle getMouseRect()
{
    return (Rectangle){GetMouseX(), GetMouseY(), mouseCollisionSize, mouseCollisionSize};
}
#endif /*DRAWUTILS_H*/