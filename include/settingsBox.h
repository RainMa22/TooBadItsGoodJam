#include "drawUtils.h"
#include "dragbar.h"

#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H
// represents a settingbox
typedef struct SettingsBox
{
    Rectangle bounds;
    int thickness;
    Color lineColor;
    Dragbar volume;
    Dragbar narration;
    Dragbar yapVolume;
    // etc.
} SettingsBox;

SettingsBox newSettingsBox(Rectangle bounds, int thickness, Color lineColor)
{
    Vector2 selfPos = (Vector2){bounds.x, bounds.y};
    Vector2 volumePos = relativeToAbsolute(selfPos, (Vector2){bounds.width / 8, 0});
    Dragbar volume = newDragbar((Rectangle){volumePos.x, volumePos.y, bounds.width * 4 / 8, bounds.height / 5},
                                (Vector2){bounds.width / 16, bounds.height / 6}, 100, DARKGRAY, GRAY);

    Vector2 narrationPos = relativeToAbsolute(selfPos, (Vector2){bounds.width / 8, bounds.height / 5});
    Dragbar narration = newDragbar((Rectangle){narrationPos.x, narrationPos.y, bounds.width * 4 / 8, bounds.height / 5},
                                   (Vector2){bounds.width / 16, bounds.height / 6}, 100, DARKGRAY, GRAY);

    Vector2 yapVolPos = relativeToAbsolute(selfPos, (Vector2){bounds.width / 8, bounds.height * 2 / 5});
    Dragbar yapVol = newDragbar((Rectangle){yapVolPos.x, yapVolPos.y, bounds.width * 4 / 8, bounds.height / 5},
                                (Vector2){bounds.width / 16, bounds.height / 6}, 100, DARKGRAY, GRAY);

    return (SettingsBox){bounds, thickness, lineColor, volume, narration, yapVol};
}

void drawSettingsBox(SettingsBox *self)
{
    DrawRectangleLinesEx(self->bounds, self->thickness, self->lineColor);
    BeginScissorMode(self->bounds.x, self->bounds.y, self->bounds.width, self->bounds.height);
    drawDragbar(&(self->volume));
    drawDragbar(&(self->narration));
    drawDragbar(&(self->yapVolume));
    EndScissorMode();
};
#endif // SETTINGSBOX_H
