#include "application.h"
#include <vector>
#include "../components/fpscamera.h"

Application::Application(int argc, char* argv[], const char *windowTitle, int windowWidth, int windowHeight)
    : PLATFORM(argc, argv, windowTitle, windowWidth, windowHeight)
{
}

void Application::SetScene(Scene *scene)
{
    currentScene = scene;
    scene->Init();
}

void Application::AddScene(Scene *scene)
{
    scene->renderer = renderer;
    scene->editor   = editor;
    scenes.push_back(scene);

    if (editor != nullptr)
    {
        GameObject* camera = new GameObject;
        camera->components.push_back(new FPSCamera(&scene->camera));
        scene->gameObjects.push_back(camera);
    }

    if (currentScene == nullptr)
    {
        SetScene(scene);
    }
}

int Application::Run()
{
    return PLATFORM::Run();
}
