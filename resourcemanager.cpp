#include "resourcemanager.h"
#include <QUrl>

ResourceManager::ResourceManager(QObject* parent) : QObject(parent)
{
    //Click sound
    clickOutPut = new QAudioOutput(this);
    clickOutPut->setVolume(1.0f);

    click = new QMediaPlayer(this);
    click->setAudioOutput(clickOutPut);
    click->setSource(QUrl::fromLocalFile("../../Assets/Sounds/click.wav"));

    //Background musick
    backOutPut = new QAudioOutput(this);
    backOutPut->setVolume(1.0f);

    background = new QMediaPlayer(this);
    background->setAudioOutput(backOutPut);
    background->setSource(QUrl::fromLocalFile("../../Assets/Sounds/Background.mp3"));
    background->setLoops(QMediaPlayer::Infinite);
}

void ResourceManager::clickSound()
{
    if(click->playbackState() == QMediaPlayer::PlayingState)
        click->setPosition(0);
    click->play();

}

void ResourceManager::toggleBackgroundMusick()
{
    if (background->playbackState() == QMediaPlayer::PlayingState)
    {
        background->stop();
        qDebug("Shut that thing up!");
    }
    else
    {
        background->play();
        qDebug("Play that good shit!");
    }
}
