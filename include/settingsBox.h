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
    Vector2 volumePos = relativeToAbsolute(selfPos, (Vector2){bounds.width / 8, bounds.height * 2 / 8});
    Dragbar volume = newDragbar((Rectangle){volumePos.x, volumePos.y, bounds.width * 4 / 8, bounds.height / 8},
                                (Vector2){bounds.width / 16, bounds.height / 16}, getRecordValue(&globals.settings, "Volume"), DARKGRAY, GRAY);
    setDragBarListener(&volume, &globals.settings, "Volume");

    Vector2 narrationPos = relativeToAbsolute(selfPos, (Vector2){bounds.width / 8, bounds.height * 4 / 8});
    Dragbar narration = newDragbar((Rectangle){narrationPos.x, narrationPos.y, bounds.width * 4 / 8, bounds.height / 8},
                                   (Vector2){bounds.width / 16, bounds.height / 16}, getRecordValue(&globals.settings, "Narration"), DARKGRAY, GRAY);
    setDragBarListener(&narration, &globals.settings, "Narration");

    Vector2 yapVolPos = relativeToAbsolute(selfPos, (Vector2){bounds.width / 8, bounds.height * 6 / 8});
    Dragbar yapVol = newDragbar((Rectangle){yapVolPos.x, yapVolPos.y, bounds.width * 4 / 8, bounds.height / 8},
                                (Vector2){bounds.width / 16, bounds.height / 16}, getRecordValue(&globals.settings, "YapVolume"), DARKGRAY, GRAY);
    setDragBarListener(&yapVol, &globals.settings, "YapVolume");

    return (SettingsBox){bounds, thickness, lineColor, volume, narration, yapVol};
}

void drawSettingsBox(SettingsBox *self)
{
    const int textSize = 24;
    DrawRectangleLinesEx(self->bounds, self->thickness, self->lineColor);
    BeginScissorMode(self->bounds.x, self->bounds.y, self->bounds.width, self->bounds.height);
    Vector2 selfPos = (Vector2){self->bounds.x, self->bounds.y};
    Vector2 textPos = relativeToAbsolute(selfPos, (Vector2){self->bounds.width / 8, self->bounds.height / 8});

    Vector2 indicatorPos = (Vector2){self->volume.bounds.x + self->volume.bounds.width + textSize, self->volume.bounds.y};
    DrawText("Master Volume", textPos.x, textPos.y, textSize, DARKGRAY);
    drawDragbar(&(self->volume));
    DrawText(TextFormat("%d", getPercentage(&(self->volume))), indicatorPos.x, indicatorPos.y, textSize, DARKGRAY);

    textPos.y += self->bounds.height * 2 / 8;
    indicatorPos.y += self->bounds.height * 2 / 8;
    DrawText("Narration Volume", textPos.x, textPos.y, textSize, DARKGRAY);
    drawDragbar(&(self->narration));
    char narrationPercentage = getPercentage(&(self->narration));
    if (narrationPercentage == 0)
    {
        DrawText(TextFormat(":("), indicatorPos.x, indicatorPos.y, textSize, DARKGRAY);
    }
    else
    {
        DrawText(TextFormat("%d", narrationPercentage), indicatorPos.x, indicatorPos.y, textSize, DARKGRAY);
    }

    textPos.y += self->bounds.height * 2 / 8;
    indicatorPos.y += self->bounds.height * 2 / 8;
    DrawText("Yap Volume(Excessive Sound Design)", textPos.x, textPos.y, textSize, DARKGRAY);
    drawDragbar(&(self->yapVolume));
    DrawText(TextFormat("%d", getPercentage(&(self->yapVolume))), indicatorPos.x, indicatorPos.y, textSize, DARKGRAY);
    EndScissorMode();
};
#endif // SETTINGSBOX_H
