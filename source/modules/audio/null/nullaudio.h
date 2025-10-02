#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    bool Init() override;
    void Update() override;
    Audio::AudioComponent* PlaySound(std::string name, std::string filepath, glm::vec3 pos, bool loop, float gain) override;
};

#endif // NULLAUDIO_H
