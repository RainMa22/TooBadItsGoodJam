#include "sceneDefinitions.h" //mouseCollisionSize also here

#include "clickStats.h"
#include "titleScene.h"
#include "gameScene.h"
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
    sceneID = procedures[sceneID]();
  }
  CloseWindow();
  return 0;
}

void initGlobals()
{
  globals = (Globals){.settings = newSettingManager("setting.txt"), NULL, newSaveManager(SAVEFILE_NAME)};
}
