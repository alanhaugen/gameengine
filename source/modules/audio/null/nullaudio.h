#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    bool Init() override;
    void Update() override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
};

#endif // NULLAUDIO_H
