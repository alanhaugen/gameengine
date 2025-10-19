#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    void Init() override;
    void Update() override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
    void PlayMusic(std::string filename) override;
};

#endif // NULLAUDIO_H
