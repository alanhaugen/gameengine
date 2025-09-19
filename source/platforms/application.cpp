#include "application.h"
#include <vector>

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
    scenes.push_back(scene);

    if (currentScene == nullptr)
    {
        SetScene(scene);
    }
}

int Application::Run()
{
    return PLATFORM::Run();
}
