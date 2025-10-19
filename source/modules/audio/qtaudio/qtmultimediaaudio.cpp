#include "qtmultimediaaudio.h"
#include <QFileInfo>

void QtMultimediaAudio::Init()
{
    player = new QMediaPlayer();
    audioOutput = new QAudioOutput;
    audioOutput->setVolume(1.0);
    player->setAudioOutput(audioOutput);
}

void QtMultimediaAudio::Update()
{

}

void QtMultimediaAudio::PlaySound(std::string filename, glm::vec3 pos)
{
    effect.setSource(QUrl::fromLocalFile(QFileInfo(filename.c_str()).absoluteFilePath()));
    effect.setVolume(1.0f);
    effect.play();
}

void QtMultimediaAudio::PlayMusic(std::string filename)
{
    player->setSource(QUrl::fromLocalFile(QFileInfo(filename.c_str()).absoluteFilePath()));
    player->play();
}
