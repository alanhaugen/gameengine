#include "resourcemanager.h"
#include <iostream>
#include <fstream>
#include <vector>

//Helper to read little-endian ints
static int readInt(std::ifstream& file) {
    char data[4];
    file.read(data, 4);
    return (unsigned char)data[0] | ((unsigned char)data[1] << 8) |
           ((unsigned char)data[2] << 16) | ((unsigned char)data[3] << 24);
}

static short readShort(std::ifstream& file) {
    char data[2];
    file.read(data, 2);
    return (unsigned char)data[0] | ((unsigned char)data[1] << 8);
}

ResourceManager::ResourceManager()
    : device(nullptr), context(nullptr),
    clickBuffer(0), clickSource(0),
    backgroundBuffer(0), backgroundSource(0)
{
    //Open the default audio device
    device = alcOpenDevice(nullptr);
    if (!device) {
        std::cerr << "Failed to open audio device" << std::endl;
        return;
    }

    context = alcCreateContext(device, nullptr);
    if (!context || !alcMakeContextCurrent(context)) {
        std::cerr << "Failed to set OpenAL context" << std::endl;
        return;
    }

    //Click and BG sounds
    alGenBuffers(1, &clickBuffer);
    alGenSources(1, &clickSource);

    alGenBuffers(1, &backgroundBuffer);
    alGenSources(1, &backgroundSource);

    loadWavFile("../../Assets/Sounds/click.wav", &clickBuffer);
    alSourcei(clickSource, AL_BUFFER, clickBuffer);

    loadWavFile("../../Assets/Sounds/Background.wav", &backgroundBuffer);
    alSourcei(backgroundSource, AL_BUFFER, backgroundBuffer);
    alSourcei(backgroundSource, AL_LOOPING, AL_TRUE);
}

ResourceManager::~ResourceManager()
{
    //Cleanup
    alDeleteSources(1, &clickSource);
    alDeleteBuffers(1, &clickBuffer);

    alDeleteSources(1, &backgroundSource);
    alDeleteBuffers(1, &backgroundBuffer);

    if (context) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
    }
    if (device) {
        alcCloseDevice(device);
    }
}

void ResourceManager::clickSound()
{
    ALint state;
    alGetSourcei(clickSource, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING) {
        alSourceStop(clickSource);
        alSourceRewind(clickSource);
    }
    alSourcePlay(clickSource);
}

void ResourceManager::toggleBackgroundMusic()
{
    ALint state;
    alGetSourcei(backgroundSource, AL_SOURCE_STATE, &state);

    if (state == AL_PLAYING) {
        alSourceStop(backgroundSource);
        std::cout << "Shut that thing up!" << std::endl;
    } else {
        alSourcePlay(backgroundSource);
        std::cout << "Play that good shit!" << std::endl;
    }
}

bool ResourceManager::loadWavFile(const std::string& filename, ALuint* buffer)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open WAV file: " << filename << std::endl;
        return false;
    }

    // Basic WAV header parsing
    char riff[4];
    file.read(riff, 4); // "RIFF"
    file.seekg(22); // Skip to audio format section

    short channels = readShort(file);
    int sampleRate = readInt(file);
    file.seekg(34);
    short bitsPerSample = readShort(file);

    // Find data chunk
    char dataHeader[4];
    int dataSize = 0;
    while (file.read(dataHeader, 4)) {
        dataSize = readInt(file);
        if (std::string(dataHeader, 4) == "data") break;
        file.seekg(dataSize, std::ios::cur);
    }

    std::vector<char> data(dataSize);
    file.read(data.data(), dataSize);

    ALenum format = 0;
    if (channels == 1 && bitsPerSample == 8) format = AL_FORMAT_MONO8;
    else if (channels == 1 && bitsPerSample == 16) format = AL_FORMAT_MONO16;
    else if (channels == 2 && bitsPerSample == 8) format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bitsPerSample == 16) format = AL_FORMAT_STEREO16;

    alBufferData(*buffer, format, data.data(), dataSize, sampleRate);
    return true;
}
