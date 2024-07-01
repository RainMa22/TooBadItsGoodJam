// A bunch predefined constants that needs to be shared across file

#ifndef SCENEDEFINITION_H
#define SCENEDEFINITION

#include "raylib.h"
#include "button.h"
#include "drawUtils.h"

#define GAMENAME "BRAINROT TYCOON"
#define TitleScene 0
#define GameScene 1
#define SettingScene 2

//the collision box of mouse needs to have a size
#define mouseCollisionSize 1

int switchTo(int);

void TitleSceneInit(void);
int TitleSceneProcedure(void);
void GameSceneInit(void);
int GameSceneProcedure(void);
void SettingSceneInit(void);
int SettingSceneProcedure(void);

#endif //SCENEDEFINITION_H