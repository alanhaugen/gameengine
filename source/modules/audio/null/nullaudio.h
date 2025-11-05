#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    bool Init() override;
    void Update() override;
    Audio::AudioComponent* PlaySound(std::string name, std::string filepath, bool loop, float gain, glm::vec3 pos) override;
    void updateListener(glm::vec3 pos, glm::vec3 vel = glm::vec3(.0f,.0f,.0f), glm::vec3 dir = glm::vec3(.0f,.0f,-1.0f), glm::vec3 up = glm::vec3(.0f,1.0f,.0f)) override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
    void PlayMusic(std::string filename) override;
};

#endif // NULLAUDIO_H
