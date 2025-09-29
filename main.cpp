#include "MainWindow.h"
#include "resourcemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ResourceManager resourceMgr;         //Create sound manager
    MainWindow w(&resourceMgr);          //Pass pointer to MainWindow
    w.move(200, 100);
    w.show();
    w.start();
    return a.exec();
}
