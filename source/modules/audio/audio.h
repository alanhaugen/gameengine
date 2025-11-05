    #pragma once

#include "../system.h"
#include <string>
#include <glm/glm.hpp>

class Audio : public System
{
public:
    class AudioComponent
    {
    public:
        bool isPlaying = false;
        virtual void Play() = 0;
        virtual void Stop() = 0;
        virtual void Pause() = 0;
        virtual void adjustGain(float gain = 0.0f) = 0;
    };
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual AudioComponent* PlaySound(std::string name, std::string filepath, bool loop = false, float gain = 0.5, glm::vec3 pos = glm::vec3()) = 0;
    virtual void updateListener(glm::vec3 pos, glm::vec3 vel = glm::vec3(.0f,.0f,.0f), glm::vec3 dir = glm::vec3(.0f,.0f,-1.0f), glm::vec3 up = glm::vec3(.0f,1.0f,.0f)) = 0;
    virtual void PlaySound(std::string filename, glm::vec3 pos = glm::vec3()) = 0;
    virtual void PlayMusic(std::string filename) = 0;
};
