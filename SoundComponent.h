/*#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include <cstdint>
#include <string>
#include <cstdio>

struct wave_t
{
    uint32_t size;              ///< Size of the WAVE file.
    uint32_t chunkSize;         ///< Size of the fmt chunk.
    uint32_t sampleRate;        ///< Sample rate of the audio.
    uint32_t avgBytesPerSec;    ///< Average byte rate.
    uint32_t dataSize;          ///< Size of the data chunk.
    short formatType;           ///< Audio format.
    short channels;             ///< Number of audio channels.
    short bytesPerSample;       ///< Number of bytes per sample.
    short bitsPerSample;        ///< Number of bits per sample.
    short arrayPosition;        ///< Position in array containing all Wave data

    unsigned char* buffer;      ///< Buffer to hold audio data.
    wave_t() : buffer(NULL) {}  ///< Structure Constructor. Initialises data buffer to NULL.
};

class WavFileReader
{
public:
    /// Loads a given wave file, fills wave_t structure with wave data.
    /**
        \param File path relative to execution directory.
        \param Pointer to a wave_t structure to contain the wave data.
    **/
    /*static bool loadWave(std::string filePath, wave_t* wavePtr);
private:
    /// Error handling function.
    /**
        Always returns false, outputs argumen string to the command line.
        \param Error message to output.
    **/"
   /* static bool endOnError(std::string errmsg);
};


#endif // SOUNDCOMPONENT_H
