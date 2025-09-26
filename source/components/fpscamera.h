#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "component.h"
#include "camera.h"

class FPSCamera : public Component
{
private:
    void UpdateCamera();
    float speed = 0.1;
    Camera* camera;

public:
    FPSCamera(Camera* camera = nullptr);
    void Update();
};

#endif // FPSCAMERA_H
