#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>


void Camera::Init()
{
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
    renderer->SetViewMatrix(glm::lookAtRH(position, position + forward, up));
    renderer->SetCameraPosition(position);
    //renderer->SetLightPos(position);
}

Physics::Ray Camera::ScreenPointToRay(float x, float y) const
{
    // Thanks to https://antongerdelan.net/opengl/raycasting.html
    float Px = (2.0f * x) / float(renderer->windowWidth) - 1.0f;
    float Py = 1.0f - (2.0f * y) / float(renderer->windowHeight);
    float Pz = 1.0f;

    glm::vec3 rayNDC(Px, Py, Pz);

    glm::vec4 rayClip(rayNDC.x, rayNDC.y, -1.0, 1.0);

    glm::vec4 rayEye = glm::inverse(renderer->GetProjectionMatrix()) * rayClip;

    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

    glm::vec4 rayWorld = (glm::inverse(renderer->cameraView) * rayEye);
    rayWorld = glm::normalize(rayWorld);

    Physics::Ray ray(position, glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z));
    return ray;
}
