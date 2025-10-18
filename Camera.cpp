#include "Camera.h"

Camera::Camera()
{
    init();
}


void  Camera::init()
{
    position = glm::vec3(0.0f, 0.0f, -1.0f);

    forward = glm::vec3(0.f, 1.f, 0.f);
    left = glm::vec3(0.f, 1.f, 0.f);
    up = glm::vec3(0.f, 1.f, 0.f);
    right = glm::cross(forward, up);

    yaw = -90;
    pitch = 0;
    roll = 0;

}

Camera::Camera(float x, float y, float z)
{
    init();
    position = glm::vec3(x,y,z);
}

void Camera::update()
{

}
