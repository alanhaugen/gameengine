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
        SetScene(scenes.at(0));
    }
}

void Services::SetScene(Scene *scene)
{
    if(currentScene)
    {
        currentScene->Clean();
        currentScene=nullptr;
    }

    currentScene = scene;
    currentScene->Init();
}

void Services::SetScene(int index)
{
    if(currentScene)
    {
        currentScene->Clean();
        currentScene=nullptr;
    }
    currentScene = scenes.at(index);
    scenes.at(index)->Init();
}

Scene *Services::GetScenes()
{
    for(int index = 0; index < scenes.size(); index++)
    {
        return scenes.at(index);
    }
    return nullptr;
}
