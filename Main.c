#include "sceneDefinitions.h" //mouseCollisionSize also here

#include "clickStats.h"
#include "titleScene.h"
#include "settingScene.h"


int screenWidth = 800;
int screenHeight = 600;
// main gameloop
int main()
{
  InitWindow(screenWidth, screenHeight, GAMENAME);
  SetTargetFPS(60);

  sceneID = TitleSceneInit();
  initGlobals();
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
    case SettingScene:
      sceneID = SettingSceneProcedure();
      break;
    default:
      break;
    }
  }
  CloseWindow();
  return 0;
}

void initGlobals()
{
  globals = (Globals){.settings= newSettingManager("setting.txt"),NULL};
}

ClickStats clickStats;

// Input logic
bool leftClickPressed = false;

int GameSceneInit()
{
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
  return GameScene;
}

int GameSceneProcedure()
{
  // failsafe: avoid stupidity
  if (sceneID != GameScene)
  {
    GameSceneInit();
  }
  int titleSize = 36;
  BeginDrawing();
  ClearBackground(RAYWHITE);
  const char *text = "This is the [Game Scene]\n\n(name pending)";
  DrawTextCentered(text, screenWidth / 2, screenHeight / 4, titleSize, DARKGRAY);
  // TODO

  // Test for click stats
  DrawTextCentered(TextFormat("Current clicks: %08i", clickStats.currentClicks), screenWidth / 2, screenHeight / 4 + 50, titleSize, DARKGRAY); // Print the current clicker count

  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
  {
    if (!leftClickPressed)
    {
      addClicks(&clickStats, 1); // Add clicks when mouse button just pressed (LMB)
    }
    leftClickPressed = true;
  }
  else
  {
    leftClickPressed = false;
  }

  EndDrawing();
  return GameScene;
}