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

    void Update();

    glm::mat4 view;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    float yaw;
    float pitch;
    float roll;
    float nearField;
    float farField;
    float fovDegrees;
};

#endif // CAMERA_H
