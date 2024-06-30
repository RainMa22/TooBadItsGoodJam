#include "raylib.h"
#include "raymath.h"

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
Button drawButton(Button btn)
{
    // draw outline
    DrawRectangle(btn.x - btn.outlineSize, btn.y - btn.outlineSize,
                  btn.sizeX + btn.outlineSize * 2, btn.sizeY + btn.outlineSize * 2, btn.outline);
    // draw body
    DrawRectangle(btn.x, btn.y, btn.sizeX, btn.sizeY, btn.body);
    // draw text centered at btn center
    Vector2 textSize = MeasureTextEx(GetFontDefault(), btn.text, btn.textSize, 0.0f);
    DrawText(btn.text, btn.x + (btn.sizeX - roundf(textSize.x)) / 2, btn.y + (btn.sizeY - roundf(textSize.y)) / 2, btn.textSize, btn.textColor);
    return btn;
}