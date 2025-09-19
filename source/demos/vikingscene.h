#pragma once

#include "../x-platform/scene.h"
#include "../components/mesh.h"

class VikingScene : public Scene
{
private:
    Mesh* vikingCamp;

public:
    void Init();
    void Update(float time);
};
