#pragma once

#include "core/x-platform/scene.h"
#include "core/components/mesh.h"
#include "core/components/spherecollider.h"
#include "systems/audio/audio.h"

class VikingScene : public Scene
{
private:
    Mesh* vikingCamp;
    Mesh* ball;
    //SphereCollision* ballCollider;
    //BoxCollision* vikingCampCollider;

public:
    void Init();
    void Update();
    Audio::AudioComponent* Music;
};
