#include "../x-platform/../components/../x-platform/../components/timer.h"

Timer::Timer() {
    addedTime = 0;
    isPaused = false;
    isStarted = false;
}

Timer::Timer(float msTime, void (*function)())
{
    timerLength = msTime;
    functionCall = function;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::Update(float deltaTime)
{
    if(isActive == false)
        return;

    auto currentTime = std::chrono::high_resolution_clock::now();
    if(std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - startTime).count() >= timerLength)
    {
        isActive = false;
        (*functionCall)();
    }
    //Log(std::to_string(std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - startTime).count()));
}

void Timer::Start()
{
    if(isStarted && isPaused == false)
        return;

    startTime = std::chrono::high_resolution_clock::now();
    isPaused = false;
    isStarted = true;
}

void Timer::Reset()
{
    addedTime = 0;
    startTime = std::chrono::high_resolution_clock::now();
    isStarted = true;
    isPaused = false;
}

void Timer::Pause()
{
    if(isStarted == false)
        return;

    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - startTime).count();
    addedTime += deltaTime;
    isPaused = true;
}

float Timer::TimeSinceStarted()
{
    //if timer not started
    if(isStarted == false)
        return -1;

    if(isPaused)
        return addedTime;

    auto currentTime = std::chrono::high_resolution_clock::now();

    return addedTime + std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - startTime).count();
}
