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
    Audio::AudioComponent* music;
    GameObject* first;
    GameObject* second;
    //SphereCollision* ballCollider;
    //BoxCollision* vikingCampCollider;

public:
    void Init();
    void Update();
    void Clean();
};
