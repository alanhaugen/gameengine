#ifndef QTAUDIO_H
#define QTAUDIO_H

#include "../null/nullaudio.h"
#include <QMediaPlayer>
#include <QAudioOutput>

class QtAudio : public NullAudio
{
private:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;

public:
    void Init() override;
    void Update() override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
};

#endif // QTAUDIO_H
