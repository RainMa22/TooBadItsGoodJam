#include "sceneDefinitions.h"
#include "clickStats.h"

#ifndef GAMESCENE_H
#define GAMESCENE_H

typedef struct GameSceneData
{
    ClickStats clickStats;
} GameSceneData;

GameSceneData gsd;

// Input logic

int GameSceneInit()
{
    // printf("Initalising game scene...");
    ClickStats clickStats = newClickStats(); // A new click stats instance.
    gsd = (GameSceneData){clickStats};
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

int GameSceneProcedure()
{
    // failsafe: avoid stupidity
    if (sceneID != GameScene)
    {
        GameSceneInit();
    }
    ClickStats *clickStats = &gsd.clickStats;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int titleSize = 36;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    const char *text = "This is the [Game Scene]\n\n(name pending)";
    DrawTextCentered(text, screenWidth / 2, screenHeight / 4, titleSize, DARKGRAY);
    // TODO

    // Test for click stats
    DrawTextCentered(TextFormat("Current clicks: %08i", clickStats->currentClicks), screenWidth / 2, screenHeight / 4 + 50, titleSize, DARKGRAY); // Print the current clicker count

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        addClicks(clickStats, 1); // Add clicks when mouse button just pressed (LMB)
    }

    EndDrawing();
    return GameScene;
}

#endif // GAMESCENE_H