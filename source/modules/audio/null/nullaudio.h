#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    bool Init() override;
    void Update() override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
    void PlayMusic(std::string filename) override;
    Audio::AudioComponent* PlaySound(std::string name, std::string filepath, glm::vec3 pos, bool loop, float gain) override;
};

#endif // NULLAUDIO_H
