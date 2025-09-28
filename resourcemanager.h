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
    void backgroundMusick();

private:
    QMediaPlayer *click;
    QMediaPlayer *background;
    QAudioOutput *outPut;
};

#endif // RESOURCEMANAGER_H
