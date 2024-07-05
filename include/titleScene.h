#include "sceneDefinitions.h"

typedef struct titleSceneData
{
    int titleSize;
    int buttonWidth;
    int buttonHeight;
    int textSize;
    Button startbtn;
    Button settingsbtn;
} titleSceneData;

titleSceneData tsd;
int TitleSceneInit()
{
    int titleSize = 42;
    int buttonWidth = 400;
    int buttonHeight = 59;
    int textSize = 22;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Button startbtn = newButton((screenWidth - buttonWidth) / 2, (screenHeight / 8 * 5 - buttonHeight / 2), buttonWidth, buttonHeight, 5, textSize, RAYWHITE, DARKGRAY, "Start!", DARKGRAY);
    Button settingbtn = newButton((screenWidth - buttonWidth) / 2, (screenHeight / 8 * 6 - buttonHeight / 2), buttonWidth, buttonHeight, 5, textSize, RAYWHITE, DARKGRAY, "Settings", DARKGRAY);
    tsd = (titleSceneData){titleSize, buttonWidth, buttonHeight, textSize, startbtn, settingbtn};
    return TitleScene;
}

// EFFECTS: draws the title scene with the Title text, a start button and a setting button
int TitleSceneProcedure()
{
    // failsafe: avoid stupidity
    if (sceneID != TitleScene)
    {
        TitleSceneInit();
    }
    int titleSize = tsd.titleSize;
    int buttonWidth = tsd.buttonWidth;
    int buttonHeight = tsd.buttonHeight;
    int textSize = tsd.textSize;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Button startbtn = tsd.startbtn;
    Button settingbtn = tsd.settingsbtn;
    Rectangle MouseRec = getMouseRect();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw title
    DrawTextCenteredEx(GetFontDefault(), GAMENAME, screenWidth / 2, screenHeight / 4, titleSize, 5, DARKGRAY);

    // draw buttons
    drawButton(startbtn);
    drawButton(settingbtn);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionRecs(getButtonRect(startbtn), MouseRec))
        {
            globals.prevSceneInit = TitleSceneInit;
            return inits[GameScene]();
        }
        if (CheckCollisionRecs(getButtonRect(settingbtn), MouseRec))
        {
            globals.prevSceneInit = TitleSceneInit;
            return inits[SettingScene]();
        }
    }
    EndDrawing();
    return TitleScene;
}