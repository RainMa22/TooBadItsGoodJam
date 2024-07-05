#include "settingsBox.h"

typedef struct settingSceneData
{
    int titleSize;
    SettingsBox settingsBox;
    Button quitBtn;
} settingSceneData;

settingSceneData ssd;
int SettingSceneInit()
{
    int titleSize = 32;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    SettingsBox box = newSettingsBox((Rectangle){screenWidth / 16, screenHeight / 10 * 2, screenWidth * 14 / 16, screenHeight / 10 * 7},
                                     1, GRAY);
    Button quitBtn = newButton(screenWidth / 16, screenWidth / 16, screenWidth / 16, screenWidth / 16, 1, 20, RAYWHITE, DARKGRAY, "<-", DARKGRAY);
    ssd = (settingSceneData){titleSize, box, quitBtn};
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
    drawSettingsBox(&(ssd.settingsBox));
    drawButton(ssd.quitBtn);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionRecs(getButtonRect(ssd.quitBtn), getMouseRect()))
        {
            return globals.prevSceneInit();
        }
    }

    // TODO
    EndDrawing();
    return SettingScene;
}