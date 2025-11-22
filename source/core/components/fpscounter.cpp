#include "fpscounter.h"

FPSCounter::FPSCounter()
{
    counter.Start();
    text = new Text("FPS: 9999999");
}

void FPSCounter::Update()
{
    float hz = 1.0f / counter.TimeSinceStarted() * 1000.0f; // 1 frame / elapsed sec
    text->ChangeText(std::string("FPS:" + std::to_string(hz)).c_str());

    counter.Reset();
}
