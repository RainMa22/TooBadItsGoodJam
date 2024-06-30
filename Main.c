#include "raylib.h"
#include "button.h"

#define GAMENAME "BRAINROT TYCOON"
#define TitleScene 0

int screenWidth = 800;
int screenHeight = 600;

void TitleSceneProcedure(void);

// main gameloop
int main()
{
  int sceneID = 0;

  InitWindow(screenWidth, screenHeight, GAMENAME);
  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    if (sceneID == TitleScene)
    {
      TitleSceneProcedure();
    }
  }
  CloseWindow();
  return 0;
}

// EFFECTS: draws the title scene with the Title text, a start button and a setting button
void TitleSceneProcedure()
{
  int titleSize = 42;
  int buttonWidth = 400;
  int buttonHeight = 80;
  int textSize = 22;
  Button startbtn = newButton((screenWidth - buttonWidth) / 2, (screenHeight / 8 * 6 - buttonHeight / 2), buttonWidth, buttonHeight, 5, textSize, RAYWHITE, DARKGRAY, "Start!", DARKGRAY);

  BeginDrawing();
  ClearBackground(RAYWHITE);
  // draw title
  DrawText(GAMENAME, (screenWidth - MeasureText(GAMENAME, titleSize)) / 2, screenHeight / 8, titleSize, GRAY);
  // draw buttons
  drawButton(startbtn);

  EndDrawing();
}
