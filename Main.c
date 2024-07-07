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
  InitAudioDevice();
  SetTargetFPS(60);

  sceneID = TitleSceneInit();
  initGlobals();
  while (!WindowShouldClose())
  {
    sceneID = procedures[sceneID]();
    for (size_t i = 0; i < MAX_SOUND_PER_SCENE; i++)
    {
      updateSpeaker(&globals.speakers[i]);
    }
    
  }
  CloseWindow();
  CloseAudioDevice();
  return 0;
}

void initGlobals()
{
  globals = (Globals){.settings = newSettingManager("setting.txt"), NULL, newSaveManager(SAVEFILE_NAME)};
  for (size_t i = 0; i < MAX_SOUND_PER_SCENE; i++)
  {
    globals.speakers[i] = createPlaceHolderSpeaker();
  }
}
