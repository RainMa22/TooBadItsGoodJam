#ifndef GAMEEFFECTS_H
#define GAMEEFFECTS_H

#include "sceneDefinitions.h"

const int EFFECTS_TOTAL_LIFETIME_FRAMES = 60;
// textEffects with 1 seconds(60 frames) lifetime, linked node
typedef struct Effects
{
    int bounds[3]; // x, y, textSize
    const char *text;
    Color textColor;
    int remainingLifeTime; // 0 to 60
    bool immortal;         // if true, never reduce lifetime
} Effects;

Effects newUninitializedEffects()
{
    return (Effects){{0, 0, 0}};
}

bool isEffectsInitialized(Effects e)
{
    return e.bounds[0] != 0 || e.bounds[1] != 0 || e.bounds[2] != 0;
}

Effects newTextEffects(int x, int y, int textSize, const char *text, Color textColor)
{
    return (Effects){{x, y, textSize}, text, textColor, EFFECTS_TOTAL_LIFETIME_FRAMES, false};
}

void removeEffects(Effects *self)
{
    if (!isEffectsInitialized(*self))
    {
        return;
    }

    free((void *)self->text);
    *self = newUninitializedEffects();
    return;
}

void drawEffects(Effects *self)
{
    if (self == NULL)
    {
        return;
    }

    DrawTextCentered(self->text, self->bounds[0], self->bounds[1], self->bounds[2], self->textColor);
    self->remainingLifeTime--;
    (&self->textColor)->a = 255 * ((float)self->remainingLifeTime / (float)EFFECTS_TOTAL_LIFETIME_FRAMES);
    self->bounds[1]--;

    if (!self->immortal && self->remainingLifeTime <= 0)
    {
        removeEffects(self);
    }
}

#endif // GAMEEFFECTS_H
