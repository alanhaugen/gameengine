#include "nullaudio.h"

bool NullAudio::Init()
{
    return true;
}

void NullAudio::Update()
{

}

void NullAudio::PlaySound(std::string filename, glm::vec3 pos)
{

}

Audio::AudioComponent* NullAudio::PlaySound(std::string name, std::string filepath, glm::vec3 pos, bool loop, float gain)
{
    return nullptr;
}

void NullAudio::PlayMusic(std::string filename)
{

}
