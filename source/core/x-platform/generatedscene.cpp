#include "generatedscene.h"
#include "core/components/sphere.h"
#include "core/components/cube.h"
#include "core/components/wiredcube.h"
#include "core/components/spherecollider.h"
#include "core/components/fpvcamera.h"
#include <fstream>

GeneratedScene::GeneratedScene(std::string fileName)
{
    std::ifstream file(fileName);

    file >> j;
}

void GeneratedScene::Init()
{
    for (size_t i = 0; i < j.size(); ++i)
    {
        std::string name = j[i]["name"];
        GameObject* newObj = new GameObject(name);

        newObj->matrix = mat4_from_json(j[i]["matrix"]);

        for (size_t k = 0; k < j[i]["components"].size(); ++k)
        {
            std::string type = j[i]["components"][k]["name"];
            if (type == "Mesh")
            {
                newObj->AddComponent(new Sphere);
            }
            else if (type == "Sphere")
            {
                newObj->AddComponent(new Sphere);
            }
            else if (type == "Sphere Collider")
            {
                newObj->AddComponent(new SphereCollider(newObj));
            }
            else if (type == "FPS Camera")
            {
                newObj->AddComponent(new FPVCamera(&camera));
            }
            else if (type == "Cube")
            {
                newObj->AddComponent(new Cube);
            }
            else if (type == "Wired Cube")
            {
                newObj->AddComponent(new WiredCube);
            }
        }
    }
}

void GeneratedScene::Update(float deltaTime)
{
}

void GeneratedScene::Clean()
{
}
