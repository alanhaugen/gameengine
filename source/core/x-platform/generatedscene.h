#ifndef GENERATEDSCENE_H
#define GENERATEDSCENE_H

#include "core/x-platform/scene.h"
#include "json.hpp"

using json = nlohmann::json;

class GeneratedScene : public Scene
{
public:
    json j;
    GeneratedScene(std::string fileName);
    void Init();
    void Update(float deltaTime = 0.0f);
    void Clean();
    glm::mat4 mat4_from_json(const json& j)
    {
        glm::mat4 m(1.0f);
        for (int i = 0; i < 16; i++)
            ((float*)&m)[i] = j[i];
        return m;
    }
};

#endif // GENERATEDSCENE_H
