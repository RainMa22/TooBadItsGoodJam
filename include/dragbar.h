#include "sceneDefinitions.h"
#ifndef DRAGBAR_H
#define DRAGBAR_H

typedef struct Dragbar
{
    Rectangle bounds;
    Button dragButton;
    char percent; // from 0 to 100
    Color color;
    Color selected;
    bool isSelected;
} Dragbar;

// creates a new dragbar with the given bounds, buttonSize, percent, color, and selected color
Dragbar newDragbar(Rectangle bounds, Vector2 buttonSize, char percent, Color color, Color selected)
{
    int btnX = bounds.x + (bounds.width * percent / 100 - buttonSize.x / 2);
    int btnY = bounds.y + (bounds.height - buttonSize.y) / 2;
    Button btn = newButton(btnX, btnY, buttonSize.x, buttonSize.y, 0, 0, color, selected, "", RAYWHITE);
    return (Dragbar){bounds, btn, percent, color, selected, false};
}

// update dragbar's percentage and button location with the given percentage
void updateDragbarPercent(Dragbar *self, char percent)
{
    Button *btn = &(self->dragButton);
    Rectangle bounds = self->bounds;

    int btnX = bounds.x + (bounds.width * percent / 100 - btn->sizeX / 2);
    int btnY = bounds.y + (bounds.height - btn->sizeY) / 2;
    btn->x = btnX;
    btn->y = btnY;
    self->percent = percent;
}

void updateDragbar(Dragbar *self)
{
    Rectangle mouseRect = getMouseRect();
    Rectangle buttonRect = getButtonRect(self->dragButton);
    if (self->isSelected)
    {
        int deltaX = mouseRect.x - self->bounds.x;
        char newPercent = Clamp((float)deltaX / (float)self->bounds.width * 100.0f, 0, 100);
        updateDragbarPercent(self, newPercent);
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(mouseRect, buttonRect))
    {
        self->isSelected = true;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        self->isSelected = false;
    }
}

void drawDragbar(Dragbar *bar)
{
    updateDragbar(bar);
    DrawLine(bar->bounds.x, bar->bounds.y + bar->bounds.height / 2, bar->bounds.x + bar->bounds.width, bar->bounds.y + bar->bounds.height / 2, bar->color);
    drawButton(bar->dragButton);
}

char getPercentage(Dragbar *bar)
{
    int x = bar->percent;
    return x;
}

#endif // DRAGBAR_H