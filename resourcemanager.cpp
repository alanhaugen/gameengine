#include "resourcemanager.h"
#include <QUrl>

ResourceManager::ResourceManager()
{
    //Click sound
    clickOutPut = std::make_unique<QAudioOutput>();
    clickOutPut->setVolume(1.0f);

    click = std::make_unique<QMediaPlayer>();
    click->setAudioOutput(clickOutPut.get());
    click->setSource(QUrl::fromLocalFile("../../Assets/Sounds/click.wav"));

    //Background musick
    backOutPut = std::make_unique<QAudioOutput>();
    backOutPut->setVolume(1.0f);

    background = std::make_unique<QMediaPlayer>();
    background->setAudioOutput(backOutPut.get());
    background->setSource(QUrl::fromLocalFile("../../Assets/Sounds/Background.mp3"));
    background->setLoops(QMediaPlayer::Infinite);
}
ResourceManager::~ResourceManager()
{

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
