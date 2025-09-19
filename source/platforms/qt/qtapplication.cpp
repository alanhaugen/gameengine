#include "qtapplication.h"

QtApplication::QtApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight)
    : a(argc, argv),
      w(nullptr, windowTitle, windowWidth, windowHeight)
{
    w.move(200, 100);
    w.show();
    w.start();

    renderer = w.mVulkanWindow;
}

int QtApplication::Run()
{
    w.mVulkanWindow->scene = currentScene;
    return a.exec();
}
