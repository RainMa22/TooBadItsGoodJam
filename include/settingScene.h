#include "sceneDefinitions.h"

typedef struct settingSceneData
{
    int titleSize;
    // TODO
} settingSceneData;

settingSceneData ssd;
int SettingSceneInit()
{
    int titleSize = 32;
    ssd = (settingSceneData){titleSize};
    // TODO
    return SettingScene;
}

int SettingSceneProcedure()
{
    // failsafe
    if (sceneID != SettingScene)
    {
        SettingSceneInit();
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int titleSize = ssd.titleSize;
    DrawTextCentered("SETTINGS", screenWidth / 2, screenHeight / 10, titleSize, DARKGRAY);
    DrawRectangleLines(screenWidth / 16, screenHeight / 10 * 2, screenWidth * 14 / 16, screenHeight / 10 * 7, GRAY);

    // TODO
    EndDrawing();
    return SettingScene;
}