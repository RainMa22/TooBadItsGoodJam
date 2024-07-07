#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "sceneDefinitions.h"

typedef struct progressBar
{
    Rectangle bounds;
    float progress; // from 0 to 1;
    int textSize;
    Color body;
    Color progressColor;
    Color textColor;
    bool locked;
} progressBar;

progressBar newProgressBar(int x, int y, int width, int height, float progress, int textSize, Color body, Color progressColor, Color textColor, bool locked)
{
    return (progressBar){(Rectangle){x, y, width, height}, progress, textSize, body, progressColor, textColor, locked};
}

void drawProgressBar(progressBar *self)
{
    int x = self->bounds.x;
    int y = self->bounds.y;
    int width = self->bounds.width;
    int height = self->bounds.height;
    int textSize = self->textSize;
    float progress = self->progress;
    Color body = self->body;
    Color progressColor = self->progressColor;
    Color textColor = self->textColor;
    if (self->locked)
    {
        DrawRectangle(x, y, width, height, progressColor);
        const char *text = "LOCKED";
        Vector2 textBound = MeasureTextEx(GetFontDefault(), text, textSize, 1.0f);
        DrawText(text, x + width - textBound.x - 1, y + (height - textBound.y) / 2, textSize, textColor);
    }
    else
    {

        // Draw body rectangle
        DrawRectangle(x, y, width, height, body);
        // Draw progress rectangle over body
        DrawRectangle(x, y, width * progress, height, progressColor);
        // Draw progress text
        const char *progressText = TextFormat("%d%%", (int)(progress * 100));
        Vector2 textBound = MeasureTextEx(GetFontDefault(), progressText, textSize, 1.0f);
        DrawText(progressText, x + width - textBound.x - 1, y + (height - textBound.y) / 2, textSize, textColor);
    }
}

#endif // PROGRESSBAR_H
