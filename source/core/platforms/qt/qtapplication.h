#pragma once

#include <QApplication>
#include <QWindow>
#include "mainwindow.h"
#include "systems/renderer/renderer.h"
#include "core/x-platform/editor.h"

static bool isAlive = true;

class QtApplication
{
private:
    QApplication a;
    MainWindow w;

protected:
    Scene* currentScene = nullptr;
    Editor* editor;

public:
    QtApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight);
    int Run();

    Renderer* renderer;
};

