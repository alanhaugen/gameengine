#include "mainwindow.h"
#include <QApplication>
#include <QWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(200, 100);
    w.show();
    w.start();
    return a.exec();
}
