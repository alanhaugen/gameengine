#pragma once

#include "../x-platform/scene.h"
#include "../components/mesh.h"
#include "../modules/audio/audio.h"

class VikingScene : public Scene
{
private:
    Mesh* vikingCamp;
    Mesh* ball;

public:
    void Init();
    void Update();
    Audio::AudioComponent* Music;
};
