#ifndef GAMEUPGRADES_H
#define GAMEUPGRADES_H

#include "sceneDefinitions.h"

typedef struct GameUpgrade
{
    int x, y, width, height;
    const char *name;
    int level;
    bool automated;
    float framesPerPercent;
    float progress;
    Button doManuallyBtn;
    Button upgradeBtn;
} GameUpgrade;

GameUpgrade newGameUpgrade(int x, int y, int width, int height, const char *name, int level, bool automated, float framesPerPercent)
{
    const int circleRadius = height / 2;
    const int textSize = height / 4;
    Button doManuallyBtn = newButton(x + circleRadius, y + height - textSize - 1, (width - circleRadius) / 2, textSize, 1, textSize, RAYWHITE, GRAY, "DO IT MANUALLY", DARKGRAY);
    // TODO: SHOW UPGRADE COST
    Button upgradeBtn = newButton(x + circleRadius + (width - circleRadius) / 2, y + height - textSize - 1, (width - circleRadius) / 2, textSize, 1, textSize, RAYWHITE, GRAY, "UPGRADE", DARKGRAY);
    return (GameUpgrade){
        x, y, width, height, name, level, automated, framesPerPercent, 0.0f, doManuallyBtn, upgradeBtn};
}

void drawGameUpgrade(GameUpgrade *self)
{
    int x = self->x;
    int y = self->y;
    int width = self->width;
    int height = self->height;
    String text = self->name;
    Button doManuallyBtn = self->doManuallyBtn;
    Button upgradeBtn = self->upgradeBtn;

    const int circleRadius = height / 2;
    const int textSize = height / 4;

    // Draw outline
    DrawLine(x + circleRadius, y, x + width, y, GRAY);
    DrawLine(x + circleRadius, y + height, x + width, y + height, GRAY);
    DrawLine(x + width, y, x + width, y + height, GRAY);

    // draw textbox
    DrawLine(x + circleRadius, y + textSize, x + width, y + textSize, GRAY);
    DrawText(text, x + circleRadius * 2, y, textSize, DARKGRAY);

    // Draw Button to progress
    drawButton(doManuallyBtn);
    drawButton(upgradeBtn);

    // draw circle outline
    DrawCircle(x + circleRadius, y + circleRadius, circleRadius, RAYWHITE);
    DrawCircleLines(x + circleRadius, y + circleRadius, circleRadius, GRAY);
    // TODO: DrawTexture inside circle, correlates with upgrade

    // TODO: Draw ProgressBar
}

bool isUpgradeManualClicked(GameUpgrade upgrade)
{
    return isButtonClicked(upgrade.doManuallyBtn);
}

bool isUpgradeUpgradeClicked(GameUpgrade upgrade)
{
    return isButtonClicked(upgrade.upgradeBtn);
}

#endif // GAMEUPHRADES_H