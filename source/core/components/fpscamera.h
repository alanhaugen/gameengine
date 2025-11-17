#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "component.h"
#include "camera.h"

class FPSCamera : public Component
{
public:
    FPSCamera(Camera* camera = nullptr);
    void Update();

    void UpdateCamera();
    float speed = 1.00;
    Camera* camera;
};

#endif // FPSCAMERA_H
