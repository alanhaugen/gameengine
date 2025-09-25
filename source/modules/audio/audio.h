#pragma once

#include <string>
#include <glm/glm.hpp>

class Audio
{
public:
    virtual void Update() = 0;
    virtual void PlaySound(std::string filename, glm::vec3 pos) = 0;
};
