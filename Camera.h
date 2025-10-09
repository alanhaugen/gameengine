#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class Camera
{
public:
    Camera();
    ~Camera() {}

    void init();

    void translate(float x, float y, float z);
    void rotate(float t, float x, float y, float z);
    void pitch(float deg);
    void yaw(float deg);
    void moveRight(float delta);
    void moveUp(float delta);

    void setPerspective(float fovy, float screenWidth, float near, float far);
    //void setPerspective(glm::radians(float fovy), float screenWidth, float near, float far);
    void lookAt(QVector3D position, QVector3D forward, QVector3D up);

    inline QMatrix4x4 getViewMatrix() const {return mViewMatrix; }
    inline QMatrix4x4 getProjectionMatrix() const {return mProjectionMatrix; }

    inline void setViewMatrix(const QMatrix4x4 &newViewMatrix) { mViewMatrix = newViewMatrix; }
    inline void setProjectionMatrix(const QMatrix4x4 &newProjectionMatrix) {mProjectionMatrix = newProjectionMatrix; }
    void setPosition(const QVector3D &newPos);
    void setSpeed(float speed);

    void update();


    //glm::mat4 perspective = (glm::radians(45.0f),( double aspect, double near, double far));

private:

    QMatrix4x4 mProjectionMatrix{};
    QMatrix4x4 mViewMatrix{};

    QVector3D mPosition = {0, 0, 0};
    QVector3D mForward = {0, 0, -1.0};
    QVector3D mUp = {0, 1, 0};
    QVector3D mTarget = {};

    float mPitch = 0.f;
    float mYaw = 0.f;

    float mSpeed = 100.f;
    float *ptr = &mSpeed;
};

#endif // CAMERA_H
