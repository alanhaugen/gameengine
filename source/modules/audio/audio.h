#pragma once

#include "../system.h"
#include <string>
#include <glm/glm.hpp>

class Audio : public System
{
public:
    virtual bool Init() = 0;
    virtual void Update() = 0;
    virtual void PlaySound(std::string filename, glm::vec3 pos) = 0;
};
