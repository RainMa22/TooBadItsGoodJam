#include "sceneDefinitions.h" //mouseCollisionSize also here
#include "titleScene.h"
#include "clickStats.h"

int screenWidth = 800;
int screenHeight = 600;
int sceneID = InactiveScene;
// main gameloop
int main()
{
  InitWindow(screenWidth, screenHeight, GAMENAME);
  SetTargetFPS(60);

  int sceneID = switchTo(TitleScene);

  while (!WindowShouldClose())
  {
    switch (sceneID)
    {
    case TitleScene:
      switchTo(TitleSceneProcedure());
      break;
    case GameScene:
      switchTo(GameSceneProcedure());
      break;
    default:
      break;
    }
  }
  CloseWindow();
  return 0;
}

// EFFECTS: Calls the init function of the switch-to scene and then returns the sceneID.
//          if the scene to be switched, do not call the init function
int switchTo(int scene)
{
  if (sceneID == scene)
    return scene;

  switch (scene)
  {
  case TitleScene:
    TitleSceneInit();
    break;
  case GameScene:
    GameSceneInit();
    break;
  default:
    break;
  }
  return scene;
}

// ----------
// GAME SCENE
// ----------

ClickStats clickStats;

// Input logic
bool leftClickPressed = false;

void GameSceneInit()
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
}

int GameSceneProcedure()
{
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