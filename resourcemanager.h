#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#pragma once

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QAudioOutput>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void clickSound();
    void toggleBackgroundMusick();

private:
    std::unique_ptr <QMediaPlayer> click;
    std::unique_ptr <QMediaPlayer> background;
    std::unique_ptr <QAudioOutput> clickOutPut;
    std::unique_ptr <QAudioOutput> backOutPut;
};

#endif // RESOURCEMANAGER_H
