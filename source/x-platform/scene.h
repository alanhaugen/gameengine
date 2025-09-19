#pragma once

class Scene
{
public:
    Scene();
    virtual void Init() = 0;
    virtual void Update() = 0;
};
