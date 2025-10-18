#include "qtaudio.h"
#include <QFileInfo>

void QtAudio::Init()
{
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
}

void QtAudio::Update()
{

}

void QtAudio::PlaySound(std::string filename, glm::vec3 pos)
{
    player->setSource(QUrl::fromLocalFile(QFileInfo(filename.c_str()).absoluteFilePath()));
    audioOutput->setVolume(1.0);
    player->play();
}
