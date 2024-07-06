#ifndef PRESETS_H
#define PRESETS_H
// reads GameUpgrade presets stored in files
#include "sceneDefinitions.h"
/*
TODO: put this in an extra file

GameUpgrade Preset Specification
Must have 255 lines
first line denotes the UpgradeCost(int), unitPerCycle(int) and framesPerPercent(float), delimited by space, at level 0;
the n-th line represents the change in the aforemention stat at n-th level
 */

// a state-machine that loads presets
typedef struct PresetLoader
{
    int lineNum;
    char lineBuffer[512]; // pointer for line
    int tokenNum;
    char *tokenSavePtr; // pointer for token
    FILE *data; // data of file
} PresetLoader;

// creates a presetLoader with the filename, it will read "presets/{filename}""
PresetLoader newPresetLoader(const char *fileName)
{
    PresetLoader loader = {};
    loader.lineNum = -1;
    loader.tokenNum = -1;
    loader.data = fopen(TextFormat("presets\\%s", fileName), "r");
}

bool nextPresetLine(PresetLoader *self)
{
    self->lineNum++;
    self->tokenNum = -1;
    char *status = fgets(self->lineBuffer, 512, self->data);
    self->tokenSavePtr = self->lineBuffer;
    return (status != 0);
}

// returns a token delimited by delim, return null if no more token avaliable
char *nextPresetToken(PresetLoader *self, const char *delim)
{
    self->tokenNum++;
    char *token = (char *)malloc(8);
    size_t size = 8;
    size_t index = 0;
    while (strcmp(self->tokenSavePtr, delim) != 0 && strcmp(self->tokenSavePtr, "\0") != 0)
    {
        token[index] = *self->tokenSavePtr;
        index++;
        self->tokenSavePtr++;
        if (index == size)
        {
            size *= 2;
            token = (char *)realloc(token, size);
        }
    }
    if (index == size)
    {
        size += 1;
        token = (char *)realloc(token, size);
    }
    token[index] = '\0';
    if (strcmp(self->tokenSavePtr, "\0") != 0)
    {
        self->tokenSavePtr++;
    }
    return token;
}

#endif // PRESETS_H