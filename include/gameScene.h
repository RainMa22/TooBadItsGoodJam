#include "sceneDefinitions.h"
#include "clickStats.h"

#ifndef GAMESCENE_H
#define GAMESCENE_H

typedef struct GameProgression
{
    ClickStats clickStats;    // game Currency basically
    uint8_t upgrade1;         // 1-255
    uint8_t upgrade2;         // 0-255
    bool secondStageUnlocked; // unlock for next upgrade
    bool thirdStageUnlocked;  // unlock for next upgrade

} GameProgression;

// return a new game progressions
GameProgression newGameProgression()
{
    return (GameProgression){newClickStats(), // A new click stats instance.
                             1,
                             0,
                             false,
                             false};
}

typedef struct GameSceneData
{
    GameProgression progression;
    Button pauseBtn;
} GameSceneData;

GameSceneData gsd;

int GameSceneInit()
{
    // printf("Initalising game scene...");
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Button pauseBtn = newButton(screenWidth / 16, screenWidth / 16, screenWidth / 16, screenWidth / 16, 1, 20, RAYWHITE, DARKGRAY, "||", DARKGRAY);
    gsd = (GameSceneData){newGameProgression(), pauseBtn};
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
    int paddings[4] = {screenWidth * 2 / 16, screenWidth / 16, screenWidth / 16, screenWidth / 16};
    const int LEFT = 0;
    const int RIGHT = 1;
    const int TOP = 2;
    const int BOTTOM = 3;
    // use Button fornow, need to have TextBox Struct later
    Button clickStatTextBox = newButton(paddings[LEFT], paddings[TOP], screenWidth * 4 / 16, screenHeight / 12, 1, 20, RAYWHITE, DARKGRAY,
                                        TextFormat("Units Sold: %d", unitSold), DARKGRAY);
    drawButton(clickStatTextBox);
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
    DrawTextCentered(text, screenWidth / 2, screenHeight / 4, titleSize, DARKGRAY);
    // TODO

    // Test for click stats
    DrawTextCentered(TextFormat("Current clicks: %08i", clickStats->currentClicks), screenWidth / 2, screenHeight / 4 + 50, titleSize, DARKGRAY); // Print the current clicker count

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        // Input logic
        if (CheckCollisionRecs(getButtonRect(pauseBtn), getMouseRect()))
        {
            // goto settign scene when paused... fornow
            EndDrawing();
            globals.prevSceneInit = procedures[GameScene];
            return inits[SettingScene]();
        }
        else
        {
            addClicks(clickStats, 1); // Add clicks when mouse button just pressed (LMB)
        }
    }

    EndDrawing();
    return GameScene;
}

#endif // GAMESCENE_H