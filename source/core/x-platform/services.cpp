#include "services.h"
#include "core/components/fpscamera.h"

Scene* Services::currentScene = nullptr;
std::vector<Scene*> Services::scenes;

Services::Services()
{
}

void Services::AddScene(Scene *scene)
{
    scene->renderer = renderer;
    scenes.push_back(scene);

    if (editor != nullptr)
    {
        GameObject* camera = new GameObject("Camera");
        camera->components.push_back(new FPSCamera(&scene->camera));
        scene->gameObjects.push_back(camera);
    }

    if (currentScene == nullptr)
    {
        SetScene(scene);
    }
}

void Services::SetScene(Scene *scene)
{
    currentScene = scene;
    scene->Init();
}

void Services::SetScene(int index)
{
}
