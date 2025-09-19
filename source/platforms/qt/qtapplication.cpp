#include "qtapplication.h"

QtApplication::QtApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight)
    : a(argc, argv),
      w(nullptr, windowTitle, windowWidth, windowHeight)
{
    w.move(200, 100);
    w.show();
    w.start();
}

int QtApplication::Run()
{
    return a.exec();
}
