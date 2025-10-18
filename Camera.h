#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>


class Camera
{
public:

    Camera();
    Camera(float x, float y, float z);
    ~Camera() {}

    void update();

     glm::vec3 position;
     glm::vec3 forward;
     glm::vec3 up;
     glm::vec3 right;
     glm::vec3 left;

     float yaw;
     float pitch;
     float roll;


 private:

     void init();
};

#endif // CAMERA_H
