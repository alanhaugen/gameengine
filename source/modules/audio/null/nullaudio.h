#ifndef NULLAUDIO_H
#define NULLAUDIO_H

#include "../audio.h"

class NullAudio : public Audio
{
public:
    void Update();
    void PlaySound(std::string filename, glm::vec3 pos);
};

#endif // NULLAUDIO_H
