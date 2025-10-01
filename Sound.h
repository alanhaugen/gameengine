#ifndef SOUND_H
#define SOUND_H

#include <cstdint>
#include <string>
#include <cstdio>

#ifdef _WIN32
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

struct wave_t
{
    uint32_t size;
    uint32_t chunkSize;
    uint32_t sampleRate;
    uint32_t avgBytesPerSec;
    uint32_t dataSize;
    short formatType;
    short channels;
    short bytesPerSample;
    short bitsPerSample;

    unsigned char* buffer;
    wave_t() : buffer(NULL) {}
};

class WavFileReader
{
public:

    static bool loadWave(std::string filePath, wave_t* wavePtr);

private:

    static bool endOnError(std::string errmsg);
};


class SoundSource
{
public:

    SoundSource(std::string name, bool loop = false, float gain = 1.0);
    ~SoundSource();

    void play();
    void pause();
    void stop();

    bool loadWave(std::string filePath);

private:
    std::string mName;
    ALuint mSource;
    ALuint mBuffer;
    bool checkError(std::string name);
};



#endif // SOUND_H
