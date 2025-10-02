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
    };
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual AudioComponent* PlaySound(std::string name, std::string filepath, glm::vec3 pos, bool loop, float gain) = 0;
};
