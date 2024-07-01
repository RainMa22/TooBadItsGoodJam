#include "raylib.h"
#include "button.h"
#include "drawUtils.h"

#include "clickStats.h"

#define GAMENAME "BRAINROT TYCOON"
#define TitleScene 0
#define GameScene 1

int screenWidth = 800;
int screenHeight = 600;
//the collision box of mouse needs to have a size
int mouseCollisionSize = 1;

int switchTo(int);

void TitleSceneInit(void);
int TitleSceneProcedure(void);
void GameSceneInit(void);
int GameSceneProcedure(void);

// main gameloop
int main()
{
  int sceneID = switchTo(TitleScene);

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

int switchTo(int sceneID) { // Calls the init function of the switch-to scene and then returns the sceneID.
  switch (sceneID) {
    case TitleScene:
      TitleSceneInit();
      break;
    case GameScene:
      GameSceneInit();
      break;
    default:
      break;
  }
  return sceneID;
}

// -----------
// TITLE SCENE
// -----------

void TitleSceneInit() {
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
      return switchTo(GameScene);
    }
  }
  EndDrawing();
  return TitleScene;
}



// ----------
// GAME SCENE
// ----------

ClickStats clickStats;

// Input logic
bool leftClickPressed = false;

void GameSceneInit() {
  // printf("Initalising game scene...");
  clickStats = newClickStats(); // A new click stats instance.
  // TESTing click stats
  // addClicks(&clickStats, 30);
  // printf(clickStats.currentClicks);
  // printf("remove 15");
  // consumeClicks(&clickStats, 15);
  // printf(clickStats.currentClicks);
  // printf("lifetime");
  // printf(clickStats.lifetimeClicks);
}

int GameSceneProcedure(){
  int titleSize = 36;
  BeginDrawing();
  ClearBackground(RAYWHITE);
  const char *text = "This is the [Game Scene]\n\n(name pending)"; 
  DrawTextCentered(text,screenWidth/2,screenHeight/4,titleSize,DARKGRAY);
  //TODO

  // Test for click stats
  DrawTextCentered(TextFormat("Current clicks: %08i", clickStats.currentClicks),screenWidth/2,screenHeight/4 + 50,titleSize,DARKGRAY); // Print the current clicker count

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
  {
    if (!leftClickPressed) {
      addClicks(&clickStats, 1); // Add clicks when mouse button just pressed (LMB)
    }
    leftClickPressed = true;
  } else {
    leftClickPressed = false;
  }

  EndDrawing();
  return GameScene;
}