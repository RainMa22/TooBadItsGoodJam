#include "sceneDefinitions.h"
#include "clickStats.h"

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "gameUpgrades.h"
#include "gameEffects.h"

#define GAMESCENE_EFFECTS_MAX 512

typedef struct GameProgression
{
    ClickStats clickStats;    // game Currency basically    bool secondStageUnlocked; // unlock for next upgrade
    bool secondStageUnlocked; // unlock for next upgrade

} GameProgression;

// return a new game progressions
GameProgression newGameProgression()
{
    return (GameProgression){newClickStats(), // A new click stats instance.
                             false};
}

typedef struct GameSceneData
{
    GameProgression progression;
    Button pauseBtn;
    GameUpgrade upgrades[2]; // list of GameUpgrades to draw
    Effects effects[GAMESCENE_EFFECTS_MAX];
} GameSceneData;

GameSceneData gsd;

int GameSceneInit()
{
    // printf("Initalising game scene...");
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Button pauseBtn = newButton(screenWidth / 16, screenWidth / 16, screenWidth / 16, screenWidth / 16, 1, 20, RAYWHITE, DARKGRAY, "||", DARKGRAY);
    gsd = (GameSceneData){newGameProgression(), pauseBtn};
    for (size_t i = 0; i < 2; i++)
    {
        int ybase = screenHeight * 3 / 8;
        int yoffset = screenHeight * 2 / 8;
        int upgradeWidth = screenWidth * 5 / 8;
        int upgradeHeight = screenHeight / 8;
        int upgradeX = (screenWidth - upgradeWidth) / 2;
        // gsd.upgrades[i] = newGameUpgrade(i, upgradeX, ybase + yoffset * i, upgradeWidth, upgradeHeight,
        //                                  (int)(i == 0), 1 << i, 1 << i, 0);
        gsd.upgrades[i] = loadFromPreset(i, upgradeX, ybase + yoffset * i, upgradeWidth, upgradeHeight, (int)(i == 0));
    }
    for (size_t i = 0; i < GAMESCENE_EFFECTS_MAX; i++)
    {
        gsd.effects[i] = newUninitializedEffects();
    }
    
    // TESTing click stats
    // addClicks(&clickStats, 30);
    // printf(clickStats.currentClicks);
    // printf("remove 15");
    // consumeClicks(&clickStats, 15);
    // printf(clickStats.currentClicks);
    // printf("lifetime");
    // printf(clickStats.lifetimeClicks);
    return GameScene;
}

void drawGameStatBar()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int unitSold = gsd.progression.clickStats.currentClicks;
    int lifetimeSale = gsd.progression.clickStats.lifetimeClicks;
    int paddings[4] = {screenWidth * 2 / 16, screenWidth / 16, screenWidth / 16, screenWidth / 16};
    const int LEFT = 0;
    const int RIGHT = 1;
    const int TOP = 2;
    const int BOTTOM = 3;
    // use Button for now, need to have TextBox Struct later
    Button clickStatTextBox = newButton(paddings[LEFT], paddings[TOP], screenWidth * 4 / 16, screenHeight / 12, 1, 20, RAYWHITE, DARKGRAY,
                                        TextFormat("Units Sold: %d", unitSold), DARKGRAY);
    Button LifetimeSaleTextBox = newButton(paddings[LEFT] + screenWidth * 4 / 16, paddings[TOP], screenWidth * 4 / 16, screenHeight / 12, 1, 20, RAYWHITE, DARKGRAY,
                                           TextFormat("Lifetime Sale: %d", lifetimeSale), DARKGRAY);
    drawButton(clickStatTextBox);
    drawButton(LifetimeSaleTextBox);
}

void cleanUpGame(GameSceneData *self)
{
    for (size_t i = 0; i < GAMESCENE_EFFECTS_MAX; i++)
    {
        removeEffects(&self->effects[i]);
    }

    for (size_t i = 0; i < sizeof(self->upgrades) / sizeof(GameUpgrade); i++)
    {
        removeUpgrades(&self->upgrades[i]);
    }
}

void addEffects(Effects effects)
{
    for (size_t i = 0; i < GAMESCENE_EFFECTS_MAX; i++)
    {
        if (!isEffectsInitialized(gsd.effects[i]))
        {
            gsd.effects[i] = effects;
            break;
        }
    }
}

int GameSceneProcedure()
{
    // failsafe: avoid stupidity
    if (sceneID != GameScene)
    {
        GameSceneInit();
    }
    ClickStats *clickStats = &gsd.progression.clickStats;
    Button pauseBtn = gsd.pauseBtn;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int titleSize = 36;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    const char *text = "This is the [Game Scene]\n\n(name pending)";
    drawGameStatBar();
    drawButton(pauseBtn);
    // TODO
    for (size_t i = 0; i < sizeof(gsd.upgrades) / sizeof(GameUpgrade); i++)
    {
        drawGameUpgrade(&gsd.upgrades[i]);
        if (gsd.upgrades[i].progress >= 1.0f)
        {
            addClicks(clickStats, gsd.upgrades[i].unitPerCycle);
            (&gsd.upgrades[i])->progress -= 1.0f;
        }
    }
    // drawEffects
    for (size_t i = 0; i < GAMESCENE_EFFECTS_MAX; i++)
    {
        drawEffects(&gsd.effects[i]);
    }

    // Test for click stats
    // DrawTextCentered(text, screenWidth / 2, screenHeight / 4, titleSize, DARKGRAY);
    // DrawTextCentered(TextFormat("Current clicks: %08i", clickStats->currentClicks), screenWidth / 2, screenHeight / 4 + 50, titleSize, DARKGRAY); // Print the current clicker count

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        // Input logic
        if (CheckCollisionRecs(getButtonRect(&pauseBtn), getMouseRect()))
        {
            // goto settign scene when paused... fornow
            EndDrawing();
            // for (size_t i = 0; i < sizeof(gsd.upgrades) / sizeof(GameUpgrade); i++)
            // {
            //     removeUpgrades(&gsd.upgrades[i]);
            // }
            cleanUpGame(&gsd);
            globals.prevSceneInit = procedures[GameScene];
            return inits[SettingScene]();
        }
        for (size_t i = 0; i < sizeof(gsd.upgrades) / sizeof(GameUpgrade); i++)
        {
            GameUpgrade *gameUpgrade = &gsd.upgrades[i];
            Rectangle mouse = getMouseRect();
            if (isUpgradeManualClicked(gameUpgrade))
            {
                addClicks(clickStats, gameUpgrade->unitPerCycle);
            }
            else if (isUpgradeUpgradeClicked(gameUpgrade))
            {
                if (clickStats->currentClicks >= gameUpgrade->upgradeCost)
                {
                    consumeClicks(clickStats, gameUpgrade->upgradeCost);
                    upgradeUpgrade(gameUpgrade);
                    addEffects(newTextEffects(mouse.x, mouse.y, titleSize / 3, strdup("Upgraded!"), DARKGRAY));
                }
                else
                {
                    
                    const char *text = TextFormat("not Enough unit sold! %d Needed", gameUpgrade->upgradeCost);
                    addEffects(newTextEffects(mouse.x, mouse.y, titleSize / 3, strdup(text), RED));
                }
            }
        }
    }

    EndDrawing();
    return GameScene;
}

#endif // GAMESCENE_H