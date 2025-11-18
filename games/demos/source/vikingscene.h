#pragma once

#include "core/x-platform/scene.h"

class VikingScene : public Scene
{
private:
    GameObject* first;
    GameObject* second;

public:
    void Init();
    void Update(float deltaTime);
};
