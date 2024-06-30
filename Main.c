#include "raylib.h"
#include <string.h>

#define GAMENAME "BRAINROT TYCOON"
#define TitleScene 0


int main()
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  const int titleSize= 42;
  int sceneID = 0;
  
  InitWindow(screenWidth, screenHeight, "Raylib basic window");
  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    if (sceneID == TitleScene)
    {
      BeginDrawing();
      ClearBackground(RAYWHITE);
      //draw title
      DrawText(GAMENAME, (screenWidth-MeasureText(GAMENAME, titleSize))/2, screenHeight/8,titleSize, GRAY);

      EndDrawing();
    }
  }
  CloseWindow();
  return 0;
}