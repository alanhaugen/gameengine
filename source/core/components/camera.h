#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "component.h"

class Camera : public Component
{
private:
    void Init();

public:
    Camera();
    Camera(float x, float y, float z);
    ~Camera() {}

    void Update() override;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float roll;
};

#endif // CAMERA_H
