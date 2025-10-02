#include "nullaudio.h"

bool NullAudio::Init()
{
    return true;
}

void NullAudio::Update()
{

}

Audio::AudioComponent* NullAudio::PlaySound(std::string name, std::string filepath, glm::vec3 pos, bool loop, float gain)
{
    return nullptr;
}
