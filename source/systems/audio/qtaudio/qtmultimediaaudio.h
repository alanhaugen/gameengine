#ifndef QTMULTIMEDIAAUDIO_H
#define QTMULTIMEDIAAUDIO_H

#include "../null/nullaudio.h"
//#include <QMediaPlayer>
// #include <QAudioOutput>
// #include <QSoundEffect>

class QtMultimediaAudio : public NullAudio
{
private:
    // QMediaPlayer* player;
    // QAudioOutput* audioOutput;
    // QSoundEffect effect;

public:
    bool Init() override;
    void Update() override;
    void PlaySound(std::string filename, glm::vec3 pos) override;
    void PlayMusic(std::string filename) override;
};

#endif // QTMULTIMEDIAAUDIO_H
