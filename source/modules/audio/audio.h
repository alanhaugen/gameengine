#pragma once

#include "../system.h"
#include <string>
#include <glm/glm.hpp>

class Audio : public System
{
public:
    virtual void Update() override;
    virtual void PlaySound(std::string filename, glm::vec3 pos);
};
