#include "qtapplication.h"

QtApplication::QtApplication(int argc, char* argv[])
    : a(argc, argv)
{
    w.move(200, 100);
    w.show();
    w.start();
}

int QtApplication::Run()
{
    return a.exec();
}
