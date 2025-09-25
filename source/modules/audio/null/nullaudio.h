#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    void Update() override;
    void PlaySound() override;
};

#endif // NULLAUDIO_H
