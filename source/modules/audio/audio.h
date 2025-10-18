#pragma once

#include "../system.h"
#include <string>
#include <glm/glm.hpp>

class Audio : public System
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void PlaySound(std::string filename, glm::vec3 pos = glm::vec3()) = 0;
};
