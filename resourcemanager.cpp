#include "resourcemanager.h"
#include <QUrl>

ResourceManager::ResourceManager(QObject* parent) : QObject(parent)
{
    outPut = new QAudioOutput(this);
    outPut->setVolume(1.0f);

    //Click sound
    click = new QMediaPlayer(this);
    click->setAudioOutput(outPut);
    click->setSource(QUrl::fromLocalFile("../../Assets/Sounds/click.wav"));

    //Background musick
    background = new QMediaPlayer(this);
    background->setAudioOutput(outPut);
    background->setSource(QUrl::fromLocalFile("../../Assets/Sounds/Background.mp3"));
}

void ResourceManager::clickSound()
{

    click->play();
}

void ResourceManager::backgroundMusick()
{
    background->play();
}
