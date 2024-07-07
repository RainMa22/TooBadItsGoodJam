#ifndef GAMEUPGRADES_H
#define GAMEUPGRADES_H

#include "sceneDefinitions.h"
#include "presets.h"
#include "progressBar.h"
/*
TODO: put this in an extra file

GameUpgrade Preset Specification
Must have 255 lines
first line denotes the UpgradeCost(int), unitPerCycle(int) and framesPerCycle(float), delimited by space, at level 0;
the n-th line represents the change in the aforemention stat at n-th level
 */

typedef struct GameUpgrade
{
    int ID;
    int x, y, width, height;
    int level;
    int upgradeCost;
    int unitPerCycle;
    int framesPerCycle;
    float progress;
    Button doManuallyBtn;
    Button upgradeBtn;
    PresetLoader *loader;
} GameUpgrade;

const char *upgradeNames[2] = {(const char *)"Pyramid Scheme", (const char *)"Short Video with ADHD content"};
// TODO: upgradeEvolutionNames, if evolution will be implemneted

void removeUpgrades(GameUpgrade *self);

GameUpgrade newGameUpgrade(int ID, int x, int y, int width, int height, int level, int upgradeCost, int unitPerCycle, float framesPerCycle, PresetLoader *loader)
{
    const int circleRadius = height / 2;
    const int textSize = height / 4;
    Button doManuallyBtn = newButton(x + circleRadius, y + height - textSize - 1, (width - circleRadius) / 2, textSize, 1, textSize, RAYWHITE, GRAY, "DO IT MANUALLY", DARKGRAY);
    // TODO: SHOW UPGRADE COST
    Button upgradeBtn = newButton(x + circleRadius + (width - circleRadius) / 2, y + height - textSize - 1, (width - circleRadius) / 2, textSize, 1, textSize, RAYWHITE, GRAY, "UPGRADE", DARKGRAY);
    return (GameUpgrade){
        ID, x, y, width, height, level, upgradeCost, unitPerCycle, framesPerCycle, 0, doManuallyBtn, upgradeBtn, loader};
}

GameUpgrade loadFromPreset(int ID, int x, int y, int width, int height, int level)
{
    PresetLoader *loaderptr = malloc(sizeof(PresetLoader));
    PresetLoader loader = newPresetLoader(TextFormat("presets\\%d.txt", ID));
    *loaderptr = loader;
    int values[3] = {0, 0, 0};
    for (char i = 0; i <= level; i++)
    {
        nextPresetLine(&loader);
        for (char j = 0; j < 3; j++)
        {
            char *sval = nextPresetToken(&loader);
            if (sval == NULL)
            {
                stopPresetLoader(&loader);
                return newGameUpgrade(ID, x, y, width, height, -1, -1, -1, 0, NULL);
            }

            values[j] += atoi(sval);
            free(sval);
        }
    }
    // stopPresetLoader(&loader);
    return newGameUpgrade(ID, x, y, width, height, level, values[0], values[1], values[2], loaderptr);
}

void drawGameUpgrade(GameUpgrade *self)
{
    const char *upgradeString = TextFormat("UPGRADE (COST: %d)", self->upgradeCost);
    int x = self->x;
    int y = self->y;
    int width = self->width;
    int height = self->height;
    String text = upgradeNames[self->ID];
    Button doManuallyBtn = self->doManuallyBtn;
    Button upgradeBtn = self->upgradeBtn;
    Color circleColor = RAYWHITE;

    upgradeBtn.text = upgradeString;
    const int circleRadius = height / 2;
    const int textSize = height / 4;

    if (self->level == 0)
    {
        // not leveled behavior
        upgradeBtn.x = doManuallyBtn.x;
        upgradeBtn.sizeX = width - circleRadius;
        doManuallyBtn = (Button){};
        circleColor = GRAY;
        Button lockedTextBox = newButton(x + circleRadius, y, width - circleRadius, height, 1, textSize * 2, GRAY, GRAY, "LOCKED", DARKGRAY);
        drawButton(lockedTextBox);
        // DrawRectangle(x + circleRadius, y, width - circleRadius, height, GRAY);
    }
    else
    {
        // GAMEUPGRADE LOGIC
        if (self->framesPerCycle != 0)
        {
            self->progress += 1.0f / (float)(self->framesPerCycle);
        }

        // Draw progress bar
        Color transparent = (Color){0, 0, 0, 0};
        progressBar bar = newProgressBar(x + circleRadius, y + textSize,
                                         width - circleRadius, height - textSize * 2, self->progress, (height - textSize * 2) / 2,
                                         transparent, GRAY, DARKGRAY, self->framesPerCycle <= 0);
        drawProgressBar(&bar);
    }

    // Draw outline
    DrawLine(x + circleRadius, y, x + width, y, GRAY);
    DrawLine(x + circleRadius, y + height, x + width, y + height, GRAY);
    DrawLine(x + width, y, x + width, y + height, GRAY);

    // draw textbox
    DrawLine(x + circleRadius, y + textSize, x + width, y + textSize, GRAY);
    DrawText(text, x + circleRadius * 2, y, textSize, DARKGRAY);

    // draw level indicator
    const char *levelText;
    if (self->level == 255)
    {
        levelText = "Lvl MAX";
    }
    else
    {
        levelText = TextFormat(TextFormat("Lvl %d", self->level));
    }

    DrawText(levelText, x + width - MeasureText(levelText, textSize) - textSize, y, textSize, DARKGRAY);

    // Draw Button to progress
    drawButton(doManuallyBtn);
    drawButton(upgradeBtn);

    // draw circle outline
    DrawCircle(x + circleRadius, y + circleRadius, circleRadius, circleColor);
    DrawCircleLines(x + circleRadius, y + circleRadius, circleRadius, GRAY);
    // TODO: DrawTexture inside circle, correlates with upgrade

    // TODO: Draw ProgressBar
}

void upgradeUpgrade(GameUpgrade *self)
{
    if (self->level == 255)
    {
        return;
    }
    float progress = self->progress;
    removeUpgrades(self);
    *self = loadFromPreset(self->ID, self->x, self->y, self->width, self->height, self->level + 1);
    self->progress = progress;
    // self->level++;
    // int *values[3] = {&self->upgradeCost, &self->unitPerCycle, &self->framesPerCycle};
    // nextPresetLine(self->loader);
    // for (char j = 0; j < 3; j++)
    // {
    //     char *sval = nextPresetToken(self->loader);
    //     if (sval == NULL)
    //     {
    //         break;
    //     }

    //     *values[j] += atoi(sval);
    //     // puts(sval);
    //     // printf("%d,", *values[j]);
    //     free(sval);
    // }
    // printf("%d,%d,%d\n", self->upgradeCost, self->unitPerCycle, self->framesPerCycle);
}

bool isUpgradeManualClicked(GameUpgrade *upgrade)
{
    return upgrade->level != 0 && isButtonClicked(&upgrade->doManuallyBtn);
}

bool isUpgradeUpgradeClicked(GameUpgrade *upgrade)
{
    return isButtonClicked(&upgrade->upgradeBtn);
}

void removeUpgrades(GameUpgrade *self)
{
    stopPresetLoader(self->loader);
}

#endif // GAMEUPHRADES_H