#ifndef FPVCAMERA_H
#define FPVCAMERA_H

#include "component.h"
#include "camera.h"

class FPVCamera : public Component
{
public:
    FPVCamera(Camera* camera = nullptr);
    void Update(float deltaTime);

    void UpdateCamera();
    float speed = 1.00;
    Camera* camera;
};

#endif // FPVCAMERA_H
