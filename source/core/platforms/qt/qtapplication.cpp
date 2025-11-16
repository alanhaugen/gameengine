#include "qtapplication.h"
#include "qteditor.h"
#include "core/x-platform/locator.h"

QtApplication::QtApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight)
    : a(argc, argv),
      w(nullptr, windowTitle, windowWidth, windowHeight)
{
    w.move(200, 100);
    w.show();
    w.start();

    renderer = w.renderer;
    editor = new QtEditor(w.ui, w.statusBar());
}

void QtApplication::NextScene()
{
    currentScene->Clean();
    SetScene(currentScene->id + 1);
}

void QtApplication::Quit()
{
    QApplication::quit();
}

int QtApplication::Run()
{
    return a.exec();
}
