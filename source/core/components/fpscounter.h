#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "core/components/component.h"
#include "core/components/timer.h"
#include "core/components/text.h"

class FPSCounter : public Component
{
public:
    FPSCounter();
    void Update();
    Timer counter;
    Text* text;
};

#endif // FPSCOUNTER_H
