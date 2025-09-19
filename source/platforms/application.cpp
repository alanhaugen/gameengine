#include "application.h"

Application::Application(int argc, char* argv[])
    : PLATFORM(argc, argv)
{
}

int Application::Run()
{
    return PLATFORM::Run();
}
