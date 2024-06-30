#include "raylib.h"
#include "button.h"
#include "drawUtils.h"

#define GAMENAME "BRAINROT TYCOON"
#define TitleScene 0
#define GameScene 1

int screenWidth = 800;
int screenHeight = 600;
//the collision box of mouse needs to have a size
int mouseCollisionSize = 1;

int TitleSceneProcedure(void);
int GameSceneProcedure(void);

// main gameloop
int main()
{
  int sceneID = 0;

  InitWindow(screenWidth, screenHeight, GAMENAME);
  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    switch (sceneID)
    {
    case TitleScene:
      sceneID = TitleSceneProcedure();
      break;
    case GameScene:
      sceneID = GameSceneProcedure();
      break;
    default:
      break;
    }
  }
  CloseWindow();
  return 0;
}

// EFFECTS: draws the title scene with the Title text, a start button and a setting button
int TitleSceneProcedure()
{
  int titleSize = 42;
  int buttonWidth = 400;
  int buttonHeight = 80;
  int textSize = 22;
  Button startbtn = newButton((screenWidth - buttonWidth) / 2, (screenHeight / 8 * 6 - buttonHeight / 2), buttonWidth, buttonHeight, 5, textSize, RAYWHITE, DARKGRAY, "Start!", DARKGRAY);
  Rectangle MouseRec = {GetMouseX(),GetMouseY(),mouseCollisionSize,mouseCollisionSize};
  
  BeginDrawing();
  ClearBackground(RAYWHITE);
  
  // draw title
  DrawTextCenteredEx(GetFontDefault(),GAMENAME,screenWidth/2,screenHeight/4,titleSize,5,DARKGRAY);
  
  // draw buttons
  drawButton(startbtn,MouseRec);

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
  {
    if (CheckCollisionRecs(getButtonRect(startbtn),MouseRec))
    {
      return GameScene;
    }
    
  }
  EndDrawing();
  return TitleScene;
}

int GameSceneProcedure(){
  int titleSize = 36;
  BeginDrawing();
  ClearBackground(RAYWHITE);
  const char *text = "This is the [Game Scene]\n\n(name pending)"; 
  DrawTextCentered(text,screenWidth/2,screenHeight/4,titleSize,DARKGRAY);
  //TODO
  EndDrawing();
  return GameScene;
}