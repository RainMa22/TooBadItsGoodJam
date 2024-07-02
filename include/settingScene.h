#include "settingsBox.h"

typedef struct settingSceneData
{
    int titleSize;
    SettingsBox settingsBox;
} settingSceneData;

settingSceneData ssd;
int SettingSceneInit()
{
    int titleSize = 32;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    SettingsBox box = (SettingsBox){1,GRAY,(Rectangle){screenWidth / 16, screenHeight / 10 * 2, screenWidth * 14 / 16, screenHeight / 10 * 7}};
    ssd = (settingSceneData){titleSize, box};
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
    drawSettingsBox(ssd.settingsBox);

    // TODO
    EndDrawing();
    return SettingScene;
}