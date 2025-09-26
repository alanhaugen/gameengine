#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

void Camera::Init()
{
    fovDegrees = 60.f;
    nearField = 0.1f;
    farField = 100.f;
    position = glm::vec3(0.0f, 0.0f, 0.0f);

    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::cross(forward, up);

    yaw = -90;
    pitch = 0;
    roll = 0;
}

Camera::Camera()
{
    Init();
}

Camera::Camera(float x, float y, float z)
{
    Init();
    position = glm::vec3(x, y, z);
}

void Camera::Update()
{
    view = glm::lookAtRH(position, position + forward, up);
}
