#ifndef SNOWGLOBECAMERA_H
#define SNOWGLOBECAMERA_H

#include "core/components/component.h"

class Camera;

class SnowGlobeCamera : public Component
{
public:
    Camera* mainCamera;
    float distance = 10.0f;
    bool init = false;

    SnowGlobeCamera(Camera *camera);
    void Update();
};

#endif // SNOWGLOBECAMERA_H
