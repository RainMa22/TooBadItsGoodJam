
#include "sceneDefinitions.h"
#include "drawUtils.h"

// include guard to avoid future pain
#ifndef BUTTON_H
#define BUTTON_H

typedef struct Button
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

// EFFECTS: get the bounding Rectangle of the button
Rectangle getButtonRect(Button btn)
{
    return (Rectangle){btn.x, btn.y, btn.sizeX, btn.sizeY};
}

// EFFECTS: returns true if button is clicked;
bool isButtonClicked(Button btn)
{
    return CheckCollisionRecs(getButtonRect(btn), getMouseRect());
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
// EFFECTS: draws the given button and returns the Button
//          if mouse hovers over the button, flip the color so the text and outline color are the body color, and the body color is the outline color
Button drawButton(Button btn)
{
    Rectangle buttonRec = getButtonRect(btn);
    Color outline = btn.outline;
    Color textColor = btn.textColor;
    Color body = btn.body;
    Rectangle mouseRec = getMouseRect();

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
    // DrawText(btn.text, btn.x + (btn.sizeX - roundf(textSize.x)) / 2, btn.y + (btn.sizeY - roundf(textSize.y)) / 2, btn.textSize, textColor);
    DrawTextCentered(btn.text, btn.x + btn.sizeX / 2, btn.y + btn.sizeY / 2, btn.textSize, textColor);
    return btn;
}

#endif /*BUTTON_H*/