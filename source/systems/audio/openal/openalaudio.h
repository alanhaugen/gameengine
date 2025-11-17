#pragma once

#include "../null/nullaudio.h"

#ifdef _WIN32
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <string>
#include "soundsource.h"
#include <glm/glm.hpp>

//TODO: Array of soundsources

class OpenALAudio : public NullAudio
{
public:
    OpenALAudio();
    bool Init() override;
    void Update() override;
    SoundSource* PlaySound(std::string name, std::string filepath, bool loop, float gain, glm::vec3 pos) override;
    void PlayMusic(std::string filename) override;
    void PlaySound(std::string filename, glm::vec3 pos)  override;
public:
    struct SoundListener
    {
        glm::vec3 pos;
        glm::vec3 vel;
        glm::vec3 dir;
        glm::vec3 up;
        SoundListener()
        {
            pos = glm::vec3(0.0f, 0.0f, 0.0f);
            vel = glm::vec3(0.0f, 0.0f, 0.0f);
            dir = glm::vec3(0.0f, 0.0f, 1.0f);
            up = glm::vec3(0.0f, 1.0f, 0.0f);
            //Could be something like this, if glm::vec3-class had support support:
            //pos = glm::vec3::ZERO;
            //vel = glm::vec3::ZERO;
            //dir = glm::vec3::UNIT_Z;
            //up = glm::vec3::UNIT_Y;
        }
    };

    static OpenALAudio* getInstance()          ///< Get pointer to singleton instance.
    {
        if (!mInstance)
            mInstance = new OpenALAudio();
        return mInstance;
    }

    /// Initialises OpenAL.
    bool init();
    /// Cleans up and shuts down OpenAl.
    void cleanUp();

    /// Creates a new SoundSource with the given parameters.
    /**
        \param The name of the sound. (Not in use.)
        \param The source position as glm::vec3.
        \param File path relative to execution directory.
        \param Boolean to see if sound should loop or not.
    **/
    SoundSource* createSource(std::string name, glm::vec3 pos, std::string filePath = "", bool loop = false, float gain = 1.0);

    void updateListener(glm::vec3 pos, glm::vec3 vel = glm::vec3(.0f,.0f,.0f), glm::vec3 dir = glm::vec3(.0f,.0f,-1.0f), glm::vec3 up = glm::vec3(.0f,1.0f,.0f)) override;

private:                         ///< Private constructor.
    OpenALAudio(OpenALAudio const&);      ///< Private copy constructor.
    void operator=(OpenALAudio const&);    ///< Private class assignment operator.
    static OpenALAudio* mInstance;         ///< Singleton instance pointer.
    /// Debug function.
    /**
        Checks for and outputs OpenAL errors.
    **/
    bool checkError();

    ALCdevice* mDevice{nullptr};                 ///< Pointer to the ALC Device.
    ALCcontext* mContext{nullptr};               ///< Pointer to the ALC Context.

    SoundListener mListener;               ///< The listener data structure. (Temporary)

};
