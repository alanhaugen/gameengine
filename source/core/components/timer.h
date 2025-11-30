#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include "core/components/component.h"

class Timer : public Component
{
public:
    Timer();
    Timer(float msTime, void (*function)());
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    bool isPaused;
    bool isStarted;

    void Update(float deltaTime) override;
    void Start();
    void Reset();
    void Pause();

    //get time spent in milliseconds
    float TimeSinceStarted();

private:
    float addedTime;
    float timerLength;
    void (*functionCall)();
    bool isActive = true;
};

#endif
