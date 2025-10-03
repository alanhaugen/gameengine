#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    void clickSound();
    void toggleBackgroundMusic();

private:
    // OpenAL device + context
    ALCdevice* device;
    ALCcontext* context;

    // Buffers and sources
    ALuint clickBuffer;
    ALuint clickSource;

    ALuint backgroundBuffer;
    ALuint backgroundSource;

    // Utility to load a WAV file
    bool loadWavFile(const std::string& filename, ALuint* buffer);
};

#endif // RESOURCEMANAGER_H
