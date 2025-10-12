#include "SoundSystem.h"
#include "Editor/MainWindow.h"

#ifdef _WIN32
#include <AL/al.h>
#include <AL/alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include "Components.h"
#include "Core/Utilities.h"
#include "Editor/MainWindow.h"
#include <sstream>
#include <string>
#include <QDebug>
#include <QFileInfo>

//For playing with Qts mediasystem
#include <QMediaPlayer>
#include <QAudioOutput>

namespace gea {

SoundSystem::SoundSystem(Engine* engineInstance) : SystemBase(engineInstance)
{

}

void SoundSystem::setMainWindow(MainWindow *mainWindow)
{
    //Sound - using Qts Multimedia system
    mAudioOutput = new QAudioOutput(mainWindow);
    mAudioOutput->setVolume(0.5);

    mMediaPlayer = new QMediaPlayer(mainWindow);
    mMediaPlayer->setAudioOutput(mAudioOutput);
}

void SoundSystem::playSound(std::string soundFile)
{
    QString filePath = QString((PATH + "Assets/Sounds/" + soundFile).c_str());

    if(!QFileInfo::exists(filePath))
    {
        qDebug() << "File does not exist:" << filePath;
        return;
    }

    if(mMediaPlayer)
    {
        mMediaPlayer->setSource(QUrl::fromLocalFile(filePath));
        mMediaPlayer->play();
    }
}

void SoundSystem::play(int component_ID)
{
    // for (gea::Sound component : ComponentSoundVector) {
        // if (component.mEntityID == component_ID)
        {
            // alSourcePlay(ComponentSoundVector[component_ID].mSoundSource);
            checkError("Playing source");
            return;
        }
    // }
}

bool SoundSystem::assignBuffer(wave_t *waveData, int component_ID)
{
    ALuint frequency{};
    ALenum format{};


    frequency = waveData->sampleRate;

    switch (waveData->bitsPerSample)
    {
    case 8:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO8;
            qDebug() << "Format: 8bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO8;
            qDebug() << "Format: 8bit Stereo\n";
            break;
        default: break;
        }
        break;
    case 16:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO16;
            qDebug() << "Format: 16bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO16;
            qDebug() << "Format: 16bit Stereo\n";
            break;
        default: break;
        }
        break;
    default: break;
    }

    if (waveData->buffer == NULL)
    {
        qDebug() << "NO WAVE DATA!\n";
    }

    std::ostringstream i2s;
    i2s << waveData->dataSize;
    qDebug() << "DataSize: " << i2s.str() << " bytes\n";

#ifdef _WIN32
    // for (gea::Sound component : ComponentSoundVector){
        // if (component.mEntityID == component_ID)
        {
            alGetError();
            // alBufferData(ComponentSoundVector[component_ID].mSoundBuffer, format, waveData->buffer, waveData->dataSize, frequency);
            checkError("alBufferData");
            // alSourcei(ComponentSoundVector[component_ID].mSoundSource, AL_BUFFER, ComponentSoundVector[component_ID].mSoundBuffer);
            checkError("alSourcei (loadWave)");

            qDebug() << "Loading complete!\n";
            //if (waveData->buffer) delete waveData->buffer;
            //if (waveData) delete waveData;
            return true;
        }
#endif
    // }
    return false;
}

bool SoundSystem::checkError(std::string name)
{
    //OpenAL seems to be deprecated on MacOS - OEF has to find a solution to this
#ifdef _WIN32
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        qDebug() << "OpenAL Error: "+name+": Invalid name!\n";
        return false;
    case AL_INVALID_ENUM:
        qDebug() << "OpenAL Error: "+name+": Invalid enum!\n";
        return false;
    case AL_INVALID_VALUE:
        qDebug() << "OpenAL Error: "+name+": Invalid value!\n";
        return false;
    case AL_INVALID_OPERATION:
        qDebug() << "OpenAL Error: "+name+": Invalid operation!\n";
        return false;
    case AL_OUT_OF_MEMORY:
        qDebug() << "OpenAL Error: "+name+": Out of memory!\n";
        return false;
    default: break;
    }
#endif
    return true;
}

} // namespace gea
