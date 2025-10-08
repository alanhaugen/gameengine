#ifndef SYSTEM_H
#define SYSTEM_H

#include "Components.h"
#include "wavfilereader.h"
#include <sstream>
#include <iostream>
#include <string>
#include <QDebug>
#ifdef _WIN32
#include <AL/al.h>
#include <AL/alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

//Maybe make a parent class that different systems should inherit from?

//One could have a common update() function for all Systems and then have a vector allSystems with all systems.
//Then run
//for (auto sys : allSystems) {
//    sys->update();
//}


//We will not have that many systems, and maybe want to control what order the systems will run, so I don't see that this is wise...
//Seems easier at the start to just make the separate systems on their own in their own independent classes...


//Need namespace, since we start to get naming collisions with other code
namespace gea
{
    class System
    {
    public:
        virtual void update() = 0;        // pure virtual → interface
        virtual ~System() = default;     // virtual dtor: safe deletion

    };

    class SoundSystem
    {
        //Waiting for system.cpp to be made in Main
        void play(int component_ID)
        {
            for (auto component : ComponentSoundVector) {
                if (component.mEntityID == component_ID)
                {
                    alSourcePlay(ComponentSoundVector[component_ID].mSoundSource);
                    checkError("Playing source");
                    return;
                }
            }
        };
        void playFromPosition(int component_ID);
        void pause(int component_ID);
        void stop(int component_ID);
        bool assignBuffer(wave_t* waveData, int component_ID)
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


            for (auto component : ComponentSoundVector){
                if (component.mEntityID == component_ID)
                {
                    alGetError();
                    alBufferData(ComponentSoundVector[component_ID].mSoundBuffer, format, waveData->buffer, waveData->dataSize, frequency);
                    checkError("alBufferData");
                    alSourcei(ComponentSoundVector[component_ID].mSoundSource, AL_BUFFER, ComponentSoundVector[component_ID].mSoundBuffer);
                    checkError("alSourcei (loadWave)");

                    qDebug() << "Loading complete!\n";
                    //if (waveData->buffer) delete waveData->buffer;
                    //if (waveData) delete waveData;
                    return true;
                }
            }
            return false;
        };
        void removeBuffer(int component_ID);

        //AL Error checking
        bool checkError(std::string name){

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
                return true;


        };
    };
}

#endif // SYSTEM_H
