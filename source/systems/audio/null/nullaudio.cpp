#include "nullaudio.h"

bool NullAudio::Init()
{
    return true;
}

void NullAudio::Update()
{

}


Audio::AudioComponent* NullAudio::PlaySound(std::string name, std::string filepath, bool loop, float gain, glm::vec3 pos = glm::vec3())
{
    return nullptr;
}

void NullAudio::PlaySound(std::string filename, glm::vec3 pos)
{

}

void NullAudio::updateListener(glm::vec3 pos, glm::vec3 vel, glm::vec3 dir, glm::vec3 up)
{
    return;
}
void NullAudio::PlayMusic(std::string filename)
{


}

void NullAudio::Stop()
{

}
