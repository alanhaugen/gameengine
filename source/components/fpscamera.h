#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "component.h"

class FPSCamera : public Component
{
private:
    void UpdateCamera();
    float speed = 1.0;

public:
    FPSCamera();
    void Update();
};

#endif // FPSCAMERA_H
