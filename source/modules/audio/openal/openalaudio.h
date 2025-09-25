#ifndef OPENALAUDIO_H
#define OPENALAUDIO_H

#include "../audio.h"

class OpenALAudio : public Audio
{
public:
    OpenALAudio();
    void Init();
    void Update();
    void PlaySound(std::string filename, glm::vec3 pos);
};

#endif // OPENALAUDIO_H
