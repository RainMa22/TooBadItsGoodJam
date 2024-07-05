// A bunch predefined constants that needs to be shared across file

#ifndef SCENEDEFINITION_H
#define SCENEDEFINITION_H

#include "raylib.h"
#include "raymath.h"
#include "recordKeeper.h"

#define GAMENAME "BRAINROT TYCOON"

#define InactiveScene -1
#define TitleScene 0
#define GameScene 1
#define SettingScene 2
int sceneID = InactiveScene;

// the collision box of mouse needs to have a size
const char mouseCollisionSize = 1;

typedef struct Globals
{
  RecordKeeper settings;
  int (*prevSceneInit)(void);
  // etc.
} Globals;

Globals globals;

void initGlobals(void);
int TitleSceneInit(void);
int TitleSceneProcedure(void);
int GameSceneInit(void);
int GameSceneProcedure(void);
int SettingSceneInit(void);
int SettingSceneProcedure(void);

#include "drawUtils.h"
#include "button.h"

#endif // SCENEDEFINITION_H