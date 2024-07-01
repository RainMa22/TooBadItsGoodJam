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
void TitleSceneInit()
{
    int titleSize = 42;
    int buttonWidth = 400;
    int buttonHeight = 80;
    int textSize = 22;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Button startbtn = newButton((screenWidth - buttonWidth) / 2, (screenHeight / 8 * 5 - buttonHeight / 2), buttonWidth, buttonHeight, 5, textSize, RAYWHITE, DARKGRAY, "Start!", DARKGRAY);
    Button settingbtn = newButton((screenWidth - buttonWidth) / 2, (screenHeight / 8 * 6 - buttonHeight / 2), buttonWidth, buttonHeight, 5, textSize, RAYWHITE, DARKGRAY, "Settings", DARKGRAY);
    tsd = (titleSceneData){titleSize, buttonWidth, buttonHeight, textSize, startbtn, settingbtn};
}

// EFFECTS: draws the title scene with the Title text, a start button and a setting button
int TitleSceneProcedure()
{
    int titleSize = tsd.titleSize;
    int buttonWidth = tsd.buttonWidth;
    int buttonHeight = tsd.buttonHeight;
    int textSize = tsd.textSize;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Button startbtn = tsd.startbtn;
    Button settingbtn = tsd.settingsbtn;
    Rectangle MouseRec = {GetMouseX(), GetMouseY(), mouseCollisionSize, mouseCollisionSize};

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw title
    DrawTextCenteredEx(GetFontDefault(), GAMENAME, screenWidth / 2, screenHeight / 4, titleSize, 5, DARKGRAY);

    // draw buttons
    drawButton(startbtn, MouseRec);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (CheckCollisionRecs(getButtonRect(startbtn), MouseRec))
        {
            return GameScene;
        }
        if (CheckCollisionRecs(getButtonRect(settingbtn), MouseRec))
        {
            return SettingScene;
        }
    }
    EndDrawing();
    return TitleScene;
}