#ifndef OPENALAUDIO_H
#define OPENALAUDIO_H

#include "../audio.h"

class OpenALAudio : public Audio
{
public:
    OpenALAudio();
    void Init() override;
    void Update() override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
};

#endif // OPENALAUDIO_H
