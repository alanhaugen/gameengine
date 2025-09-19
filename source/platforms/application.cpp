#include "application.h"

Application::Application(int argc, char* argv[], const char *windowTitle, int windowWidth, int windowHeight)
    : PLATFORM(argc, argv, windowTitle, windowWidth, windowHeight)
{
}

int Application::Run()
{
    return PLATFORM::Run();
}
