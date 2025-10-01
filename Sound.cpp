#include "Sound.h"
#include <QMediaPlayer>
#include <QAudioOutput>

/*#include <iostream>
#include <sstream>

int sound()
{
    const std::string ASSET_PATH = "../../Assets/Sounds/";

}

bool WavFileReader::loadWave(std::string filePath, wave_t* wavePtr)
{
    std::cout << "Loading "+ filePath + " from disk\n";
    FILE* fp = NULL;
    fp = std::fopen(filePath.c_str(), "rb");
    if (fp == NULL)    {
        return endOnError("FileHandler error: File not found.\n");
    }

    char type[4];

    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
    {
        return endOnError("FileHandler error: RIFF header missing or invalid.\n");
    }

    std::fread(&wavePtr->size, sizeof(uint32_t), 1, fp);
    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
    {
        return endOnError("FileHandler error: WAVE header missing or invalid.\n");
    }

    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
    {
        return endOnError("FileHandler error: fmt header missing or invalid.\n");
    }

    std::fread(&wavePtr->chunkSize,       sizeof(uint32_t), 1, fp);
    std::fread(&wavePtr->formatType,      sizeof(short), 1, fp);
    std::fread(&wavePtr->channels,        sizeof(short), 1, fp);
    std::fread(&wavePtr->sampleRate,      sizeof(uint32_t), 1, fp);
    std::fread(&wavePtr->avgBytesPerSec,  sizeof(uint32_t), 1, fp);
    std::fread(&wavePtr->bytesPerSample,  sizeof(short), 1, fp);
    std::fread(&wavePtr->bitsPerSample,   sizeof(short), 1, fp);

    std::fread(type, sizeof(char), 4, fp);
    if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
    {
        return endOnError("FileHandler error: data header missing or invalid.\n");
    }

    std::fread(&wavePtr->dataSize, sizeof(uint32_t), 1, fp);

    wavePtr->buffer = new unsigned char[wavePtr->dataSize];
    //static_cast just to get rid of compiler warning
    uint32_t result = static_cast<uint32_t>(std::fread(wavePtr->buffer, sizeof(char), wavePtr->dataSize, fp));
    if (result != wavePtr->dataSize)
    {
        return endOnError("Wav-file read error: fread result mismatch.\n");
    }

    if (ferror(fp))
    {
        return endOnError("Wav-file read error: fstream error.");
    }

    if (wavePtr->buffer == NULL)
    {
        return endOnError("Wav-file read error: Wave Data pointer is NULL.\n");
    }

    std::fclose(fp);
    std::cout << "Loading complete!\n";
    return true;
}

bool WavFileReader::endOnError(std::string errmsg)
{
    std::cout << errmsg;
    return false;
}

SoundSource::SoundSource(std::string name, bool loop, float gain) :
    mName(name),
    mSource(0),
    mBuffer(0),
{
    alGetError();
    alGenBuffers(1, &mBuffer);
    checkError("alGenBuffers");
    alGenSources(1, &mSource);
    checkError("alGenSources");
    alSourcef(mSource, AL_PITCH, 1.0f);
    alSourcef(mSource, AL_GAIN, gain);

    alSourcei(mSource, AL_LOOPING, loop);
}
SoundSource::~SoundSource()
{
    std::cout << "Destroying SoundSource " + mName;
    stop();
    alGetError();
    alSourcei(mSource, AL_BUFFER, 0);
    checkError("alSourcei");
    alDeleteSources(1, &mSource);
    checkError("alDeleteSources");
    alDeleteBuffers(1, &mBuffer);
    checkError("alDeleteBuffers");
}

bool SoundSource::loadWave(std::string filePath)
{
    std::cout << "Loading wave file!\n";
    ALuint frequency{};
    ALenum format{};
    wave_t* waveData = new wave_t();
    if (!WavFileReader::loadWave(filePath, waveData))
    {
        std::cout << "Error loading wave file!\n";
        return false;
    }

    frequency = waveData->sampleRate;

    switch (waveData->bitsPerSample)
    {
    case 8:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO8;
            std::cout << "Format: 8bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO8;
            std::cout << "Format: 8bit Stereo\n";
            break;
        default: break;
        }
        break;
    case 16:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO16;
            std::cout << "Format: 16bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO16;
            std::cout << "Format: 16bit Stereo\n";
            break;
        default: break;
        }
        break;
    default: break;
    }

    if (waveData->buffer == NULL)
    {
        std::cout << "NO WAVE DATA!\n";
    }

    std::ostringstream i2s;
    i2s << waveData->dataSize;
    std::cout << "DataSize: " << i2s.str() << " bytes\n";

    alGetError();
    alBufferData(mBuffer, format, waveData->buffer, waveData->dataSize, frequency);
    checkError("alBufferData");
    alSourcei(mSource, AL_BUFFER, mBuffer);
    checkError("alSourcei (loadWave)");

    std::cout << "Loading complete!\n";
    if (waveData->buffer) delete waveData->buffer;
    if (waveData) delete waveData;
    return true;
}

void SoundSource::play()
{
    alSourcePlay(mSource);
    checkError("Play source");
}
void SoundSource::pause()
{
    alSourcePause(mSource);
}
void SoundSource::stop()
{
    alSourceStop(mSource);
    checkError("Stop source");
}

bool SoundSource::checkError(std::string name)
{
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        std::cout << "OpenAL Error: "+name+": Invalid name!\n";
        return false;
    case AL_INVALID_ENUM:
        std::cout << "OpenAL Error: "+name+": Invalid enum!\n";
        return false;
    case AL_INVALID_VALUE:
        std::cout << "OpenAL Error: "+name+": Invalid value!\n";
        return false;
    case AL_INVALID_OPERATION:
        std::cout << "OpenAL Error: "+name+": Invalid operation!\n";
        return false;
    case AL_OUT_OF_MEMORY:
        std::cout << "OpenAL Error: "+name+": Out of memory!\n";
        return false;
    default: break;
    }
    return true;
}
*/
