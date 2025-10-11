#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <string>
#include "MainWindow.h"
#include "Systems.h"
#include "WavfileReader.h"

//For playing with Qts mediasystem
#include <QMediaPlayer>
#include <QAudioOutput>

namespace gea
{

class SoundSystem : public SystemBase
{
public:
    SoundSystem(class Engine* engineInstance);

    void setMainWindow(MainWindow* mainWindow);
    void update(float deltaTime) override {};

    //Waiting for system.cpp to be made in Main
    void play(int component_ID);;
    void playFromPosition(int component_ID);
    void pause(int component_ID);
    void stop(int component_ID);
    bool assignBuffer(wave_t* waveData, int component_ID);
    void removeBuffer(int component_ID);
    
    //AL Error checking
    bool checkError(std::string name);

    QMediaPlayer *mMediaPlayer{nullptr};
    QAudioOutput *mAudioOutput{nullptr};

    //This function uses the Qt Media Framework, not OpenAL
    void playSound(std::string soundFile);
};

} // namespace gea

#endif // SOUNDSYSTEM_H
