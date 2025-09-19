#pragma once

#include <QApplication>
#include <QWindow>
#include "mainwindow.h"

class QtApplication
{
private:
    QApplication a;
    MainWindow w;
public:
    QtApplication(int argc, char* argv[]);
    int Run();
};

