#pragma once

#ifdef _WIN32
#include <AL/al.h>
#include <AL/alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <glm/glm.hpp>
#include <string>

/// One sound source.
/**
    Contains one source and one buffer.
    Intended to play a single clip.
    Does not support streaming audio (yet).
**/
class SoundSource
{
public:
    /// Constructor.
    /**
        Takes two arguments, initialises some variables.
        \param The name of the sound source. Not used.
        \param A boolean to check if sound should loop.
    **/
    SoundSource(std::string name, bool loop = false, float gain = 1.0);
    ~SoundSource();

    /// Plays the sound source from the current position.
    void play();
    /// Pauses the sound source at the current position.
    void pause();
    /// Stops the sound source and rewinds to start.
    void stop();

    /// Loads one given WAVE file.
    /**
        Calls the wave loader from the FileHandler class, parses the wave data and buffers it.
        \param The file path relative to execution directory.
    **/
    bool loadWave(std::string filePath);

    void setPosition(glm::vec3 newPos);             ///< Sets source position from glm::vec3.
    glm::vec3 getPosition() {return mPosition;}     ///< Returns source position as glm::vec3.
    void setVelocity(glm::vec3 newVel);             ///< Sets source velocity from glm::vec3.
    glm::vec3 getVelocity() {return mVelocity;}     ///< Returns source velocity as glm::vec3.

private:
    std::string mName;          ///< The name of the sound source (Not used).
    ALuint mSource;             ///< The sound source.
    ALuint mBuffer;             ///< The data buffer.
    glm::vec3 mPosition;    ///< Vector containing source position.
    glm::vec3 mVelocity;    ///< Vector containing source velocity.
    bool checkError(std::string name);
};
