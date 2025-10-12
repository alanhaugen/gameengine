//Based off Ole Flatens code from: https://github.com/oleflaten/3D-Sound-OpenAL

#include "WavfileReader.h"
#include <QDebug>

bool WavFileReader::loadWave(std::string filePath, wave_t* wavePtr)
{
    qDebug() << "Loading " + filePath + " from disk\n";
    FILE* fp{nullptr};

#ifdef _WIN32
    errno_t testOpenFile = fopen_s(&fp, filePath.c_str(), "rb");
    if (testOpenFile != 0 || fp == nullptr)
#else
    fp = fopen(filePath.c_str(), "rb");
    if (fp == nullptr)
#endif
    {
        // Handle error - fopen_s sets fp to nullptr on failure
        qDebug() << "Failed to open file:" << filePath.c_str();

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
    qDebug("Loading complete!\n");
    return true;
}

bool WavFileReader::endOnError(std::string errmsg)
{
    qDebug() << errmsg;
    return false;
}
