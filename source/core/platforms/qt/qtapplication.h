#pragma once

#include <QApplication>
#include <QWindow>
#include "core/x-platform/Services.h"
#include "mainwindow.h"
#include "systems/renderer/renderer.h"
#include "core/x-platform/editor.h"

class QtApplication: public Services
{
private:
    QApplication a;
    MainWindow w;

protected:
    //Scene* currentScene = nullptr;
    Editor* editor;

public:
    QtApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight);
    static void NextScene();
    static void Quit();
    int Run();

    Renderer* renderer;
};

