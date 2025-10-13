#pragma once

#include "../x-platform/scene.h"

#define PLATFORM_HEADER "qt/qtapplication.h"
#define PLATFORM QtApplication

#include PLATFORM_HEADER

class Application : public PLATFORM
{
private:
    std::vector<Scene*> scenes;

public:
    Application(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight);
    void SetScene(Scene* scene);
    void AddScene(Scene* scene);
    int Run();
};
