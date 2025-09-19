#include "application.h"
#include <vector>

Application::Application(int argc, char* argv[], const char *windowTitle, int windowWidth, int windowHeight)
    : PLATFORM(argc, argv, windowTitle, windowWidth, windowHeight)
{
}

void Application::AddScene(Scene *scene)
{
    scenes.push_back(scene);
}

int Application::Run()
{
    return PLATFORM::Run();
}
