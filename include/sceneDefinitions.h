// A bunch predefined constants that needs to be shared across file

#ifndef SCENEDEFINITION_H
#define SCENEDEFINITION_H

#if __GNUC_STDC_INLINE__
#define INLINE inline
#else
#define INLINE
#endif

#include "raylib.h"
#include "raymath.h"
#include "recordKeeper.h"


#define GAMENAME "BRAINROT TYCOON"
#define SAVEFILE_NAME "save.sav"
#define GAMEUPGRADES_ID_MAX 2
#define GAMESCENE_EFFECTS_MAX 512

#include "saveManager.h"

#define InactiveScene -1
#define TitleScene 0
#define GameScene 1
#define SettingScene 2

int sceneID = InactiveScene;

typedef const char *(String);

// the collision box of mouse needs to have a size
const char mouseCollisionSize = 1;



typedef struct Globals
{
  RecordKeeper settings;
  int (*prevSceneInit)(void);
  SaveManager save;
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

INLINE int powi(int base, int exp)
{
  int out = 1;
  for (size_t i = 0; i < exp; i++)
  {
    out *= base;
  }
  return out;
}

typedef int (*Procedure)(void);

Procedure inits[3] = {TitleSceneInit, GameSceneInit, SettingSceneInit};
Procedure procedures[3] = {TitleSceneProcedure, GameSceneProcedure, SettingSceneProcedure};

#include "drawUtils.h"
#include "button.h"

#endif // SCENEDEFINITION_H