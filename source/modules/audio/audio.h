#pragma once

#include <string>
#include <glm/glm.hpp>

class Audio
{
public:
    virtual void Update();
    virtual void PlaySound(std::string filename, glm::vec3 pos);
};
