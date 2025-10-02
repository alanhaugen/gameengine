#include "MainWindow.h"
#include "wavfilereader.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    ///Loading Sounds
    /*
    std::vector<wave_t> waveDataVector;
    const std::string ASSET_PATH = NULL;
    wave_t *exampleSound = new wave_t;
    WavFileReader SoundFileReader;
    SoundFileReader.loadWave(ASSET_PATH, exampleSound);
    waveDataVector.push_back(*exampleSound);
    */

    QApplication a(argc, argv);

    QSplashScreen *mSplash = new QSplashScreen;
    mSplash->setPixmap(QPixmap("../../Assets/Engine/INNgine_splash.png")); // splash picture
    mSplash->show();

    MainWindow w;
    w.move(200, 100);
    w.show();
    w.start();

    mSplash->hide();

    return a.exec();
}
