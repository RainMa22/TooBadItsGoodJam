#include "sceneDefinitions.h"


#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H
//represents a settingbox
typedef struct SettingsBox
{
    int thickness;
    Color lineColor;
    Rectangle bounds;
    //Dragbar volume;
    //Dragbar narration;
    //Dragbar yapVolume;
    //etc.
}SettingsBox;

void drawSettingsBox(SettingsBox box){
    DrawRectangleLinesEx(box.bounds,box.thickness,box.lineColor);
    BeginScissorMode(box.bounds.x,box.bounds.y,box.bounds.width,box.bounds.height);
    //DrawDragbar(volume);
    //DrawDragbar(narration);
    //DrawDragbar(yapVolume)
    EndScissorMode();
};
#endif //SETTINGSBOX_H

