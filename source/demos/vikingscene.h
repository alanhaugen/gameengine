#pragma once

#include "../x-platform/scene.h"
#include "../components/mesh.h"

class VikingScene : public Scene
{
private:
    Mesh* vikingCamp;
    Mesh* ball;

public:
    void Init();
    void Update();
};
