// A bunch predefined constants that needs to be shared across file

#ifndef SCENEDEFINITION_H
#define SCENEDEFINITION_H

#include "raylib.h"
#include "button.h"
#include "drawUtils.h"

#define GAMENAME "BRAINROT TYCOON"

#define InactiveScene -1
#define TitleScene 0
#define GameScene 1
#define SettingScene 2
int sceneID = InactiveScene;

//the collision box of mouse needs to have a size
#define mouseCollisionSize 1

int TitleSceneInit(void);
int TitleSceneProcedure(void);
int GameSceneInit(void);
int GameSceneProcedure(void);
int SettingSceneInit(void);
int SettingSceneProcedure(void);

#endif //SCENEDEFINITION_H