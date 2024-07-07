#ifndef SPEAKER_H
#define SPEAKER_H

#include "sceneDefinitions.h"

typedef struct Speaker
{
    bool occupied;
    Sound sound;
    bool initiated;
    bool repeat;
} Speaker;

Speaker createPlaceHolderSpeaker()
{
    return (Speaker){false};
}

bool isSpeakerPlaceHolder(Speaker *speaker)
{
    return !speaker->occupied;
}
void removeSpeaker(Speaker *self)
{
    if (isSpeakerPlaceHolder(self))
    {
        return;
    }
    StopSound(self->sound);
    UnloadSoundAlias(self->sound);
    self->occupied = false;
}

Speaker createSound(Sound src, float originalVolume)
{
    float volume = ((float)getSettingsValue("Volume")) / 100.0f;
    Speaker speaker;
    speaker.occupied = true;
    speaker.sound = LoadSoundAlias(src);
    SetSoundVolume(speaker.sound, volume * originalVolume);
    speaker.initiated = false;
    speaker.repeat = false;
    return speaker;
}

Speaker createNarration(Sound src, float originalVolume)
{
    float volume = ((float)getSettingsValue("Narration")) / 100.0f;
    return createSound(src, originalVolume);
}

Speaker createSfx(Sound src, float originalVolume)
{
    float volume = ((float)getSettingsValue("Narration")) / 100.0f;
    return createSound(src, originalVolume);
}

Speaker createYap(Sound src, float originalVolume)
{
    float volume = ((float)getSettingsValue("YapVolume")) / 100.0f;
    return createSfx(src, originalVolume);
}

void updateSpeaker(Speaker *speaker)
{
    if (!speaker->occupied)
    {
        return;
    }

    if (!speaker->initiated && IsSoundReady(speaker->sound))
    {
        speaker->initiated = true;

        PlaySound(speaker->sound);
    }
    else if (speaker->initiated && !IsSoundPlaying(speaker->sound))
    {
        if (speaker->repeat)
        {
            PlaySound(speaker->sound);
        }
        else
        {
            removeSpeaker(speaker);
        }
    }
}

#endif // SPEAKER_H