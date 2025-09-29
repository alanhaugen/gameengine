#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#pragma once

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QAudioOutput>

class ResourceManager : public QObject
{
    Q_OBJECT
public:
    ResourceManager(QObject* parent = nullptr);

    void clickSound();
    void toggleBackgroundMusick();

private:
    QMediaPlayer *click;
    QMediaPlayer *background;
    QAudioOutput *clickOutPut;
    QAudioOutput *backOutPut;
};

#endif // RESOURCEMANAGER_H
