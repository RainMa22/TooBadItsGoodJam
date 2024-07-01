#include "sceneDefinitions.h"

typedef struct settingSceneData
{
} settingSceneData;

settingSceneData ssd;
int SettingSceneInit(){
    //TODO
    return SettingScene;
}

int SettingSceneProcedure(){
    //failsafe
    if (sceneID != SettingScene)
    {
        SettingSceneInit();
    }

    //TODO

    return SettingScene;
    
}