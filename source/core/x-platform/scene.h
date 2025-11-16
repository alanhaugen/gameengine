#pragma once

#include <vector>
#include "core/components/gameobject.h"
#include "core/components/camera.h"
#include "locator.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class Scene : public Locator
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Clean() = 0;
    void Save()
    {
        std::ofstream file("save.json");
        json j;

        for (int i = 0; i < gameObjects.size(); i++)
        {
            j += gameObjects[i]->to_json();
        }

        file << j.dump(4);
    }

    Camera camera;
    unsigned id;

    std::vector<GameObject*> gameObjects;
};
