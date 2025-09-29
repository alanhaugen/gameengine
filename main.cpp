#include "MainWindow.h"
#include "wavfilereader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    ///Loading Sounds
    /*
    const std::string ASSET_PATH = NULL;
    wave_t *exampleSound = new wave_t;
    WavFileReader SoundFileReader;
    SoundFileReader.loadWave(ASSET_PATH, exampleSound);
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.move(200, 100);
    w.show();
    w.start();
    return a.exec();
}
