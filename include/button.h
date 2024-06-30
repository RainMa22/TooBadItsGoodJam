#include "raylib.h"
#include "raymath.h"

//include guard to avoid future pain
#ifndef BUTTON_H
#define BUTTON_H

typedef struct
{
    int x;
    int y;
    int sizeX;
    int sizeY;
    int outlineSize;
    int textSize;
    Color body;
    Color outline;
    const char *text; // man, pointers :/
    Color textColor;
} Button;

Rectangle getButtonRect(Button btn){
    return (Rectangle){btn.x, btn.y, btn.sizeX, btn.sizeY};
}

Button newButton(int x, int y, int sizeX, int SizeY, int outlineSize, int textSize, Color body, Color outline, const char *text, Color textColor)
{
    return (Button){
        x,
        y,
        sizeX,
        SizeY,
        outlineSize,
        textSize,
        body,
        outline,
        text,
        textColor};
}
// EFFECTS: draws the given button, and Mouse Position and returns the Button
//          if mouse hovers over the button, flip the color so the text and outline color are the body color, and the body color is the outline color
Button drawButton(Button btn, Rectangle mouseRec)
{
    Rectangle buttonRec = getButtonRect(btn);
    Color outline = btn.outline;
    Color textColor = btn.textColor;
    Color body = btn.body;

    if (CheckCollisionRecs(buttonRec, mouseRec))
    {
        textColor = body;
        body = outline;
        outline = textColor;
    }

    // draw outline
    DrawRectangle(btn.x - btn.outlineSize, btn.y - btn.outlineSize,
                  btn.sizeX + btn.outlineSize * 2, btn.sizeY + btn.outlineSize * 2, outline);
    // draw body
    DrawRectangle(btn.x, btn.y, btn.sizeX, btn.sizeY, body);
    // draw text centered at btn center
    Vector2 textSize = MeasureTextEx(GetFontDefault(), btn.text, btn.textSize, 0.0f);
    DrawText(btn.text, btn.x + (btn.sizeX - roundf(textSize.x)) / 2, btn.y + (btn.sizeY - roundf(textSize.y)) / 2, btn.textSize, textColor);
    return btn;
}
//EFFECTS: get the bounding Rectangle of the button

#endif /*BUTTON_H*/