#pragma once

#include <QApplication>
#include <QWindow>
#include "mainwindow.h"
#include "../../modules/renderer/renderer.h"

class QtApplication
{
private:
    QApplication a;
    MainWindow w;

protected:
    Scene* currentScene = nullptr;

public:
    QtApplication(int argc, char* argv[], const char* windowTitle, int windowWidth, int windowHeight);
    int Run();

    Renderer* renderer;
};

