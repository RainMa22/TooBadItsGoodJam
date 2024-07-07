#ifndef PRESETS_H
#define PRESETS_H
// reads GameUpgrade presets stored in files
#include "sceneDefinitions.h"
/*
TODO: put this in an extra file

GameUpgrade Preset Specification
Must have 255 lines
first line denotes the UpgradeCost(int), unitPerCycle(int) and framesPerPercent(int), delimited by space, at level 0;
the n-th line represents the change in the aforemention stat at n-th level
 */

// a state-machine that loads presets
typedef struct PresetLoader
{
    int lineNum;
    char lineBuffer[512]; // pointer for line
    int tokenNum;
    char *lineSavePtr;  // pointer for line
    char *tokenSavePtr; // pointer for token
    char *data;         // data of file
} PresetLoader;

// creates a presetLoader with the filename, it will read "{filename}""
PresetLoader newPresetLoader(const char *fileName)
{
    PresetLoader loader = {};
    loader.lineNum = -1;
    loader.tokenNum = -1;
    FILE *file = fopen(fileName, "r");
    fseek(file, 0, SEEK_END);

    size_t size = ftell(file);
    loader.data = (char *)malloc(size);

    fseek(file, 0, SEEK_SET);

    fread(loader.data, 1, size, file);
    loader.lineSavePtr = &loader.data[0];
    // puts(loader.data);
    fclose(file);
    return loader;
}

bool nextPresetLine(PresetLoader *self)
{
    size_t size = 8;
    self->lineNum++;
    self->tokenNum = -1;
    // puts(self->data);
    for (size_t i = 0; i < 512; i++)
    {
        self->lineBuffer[i] = *(self->lineSavePtr);
        if (self->lineBuffer[i] == '\n')
        {
            self->lineBuffer[i] == '\0';
            self->lineSavePtr++;
            break;
        }
        else if (self->lineBuffer[i] == '\0')
        {
            break;
        }
        self->lineSavePtr++;
    }

    self->tokenSavePtr = &self->lineBuffer[0];
    puts(self->lineBuffer);
    return (self->lineBuffer != NULL);
}

// returns a token delimited by " ", return null if no more token avaliable
char *nextPresetToken(PresetLoader *self)
{
    self->tokenNum++;
    char *token = (char *)malloc(8);
    size_t size = 8;
    size_t index = 0;
    while (*self->tokenSavePtr != ' ' && *self->tokenSavePtr != '\0')
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
    // index++;
    // if (index == size)
    // {
    //     size += 1;
    //     token = (char *)realloc(token, size);
    // }
    token[index] = '\0';
    if (strcmp(self->tokenSavePtr, "\0") != 0)
    {
        self->tokenSavePtr++;
    }
    if (token[0] == '\0')
    {
        free(token);
        return (char *)NULL;
    }
    puts(token);
    return token;
}

void stopPresetLoader(PresetLoader *self)
{
    free(self->data);
    self = NULL;
}

#endif // PRESETS_H