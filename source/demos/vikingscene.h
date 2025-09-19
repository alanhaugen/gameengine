#pragma once

#include "../x-platform/scene.h"
#include "../components/mesh.h"

class VikingScene : public Scene
{
private:
    Mesh* vikingCamp1;
    Mesh* vikingCamp2;

public:
    void Init();
    void Update(float time);
};
