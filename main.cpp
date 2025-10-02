#include "MainWindow.h"
#include "Utilities.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *mSplash = new QSplashScreen;
    mSplash->setPixmap(QPixmap(QString::fromStdString(PATH) + "Assets/Engine/INNgine_splash.png")); // splash picture
    mSplash->show();

    MainWindow w;
    w.move(200, 100);
    w.show();
    w.start();

    mSplash->hide();

    return a.exec();
}
