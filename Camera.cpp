#include "Camera.h"

Camera::Camera()
{
    init();
}

void Camera::init()
{
    mProjectionMatrix.setToIdentity();
    mViewMatrix.setToIdentity();
}

void Camera::translate(float x, float y, float z)
{
    mViewMatrix.translate(x, y, z);
}

void Camera::rotate(float t, float x, float y, float z)
{
    mViewMatrix.rotate(t, x, y, z);
}

void Camera::pitch(float deg)
{
    mPitch += deg;
}

void Camera::yaw(float deg)
{
    mYaw += deg;
}

void Camera::moveRight(float delta)
{
    mPosition.setX( mPosition.x() + delta);
}

void Camera::moveUp(float delta)
{
    mPosition.setY(mPosition.y() + delta);
}

void Camera::update()
{
    mViewMatrix.setToIdentity();
    mPosition.setZ(mPosition.z() + mSpeed);
    mViewMatrix.rotate(mPitch, 1.0, 0.0, 0.0);
    mViewMatrix.rotate(mYaw, 0.0, 1.0, 0.0);
    mViewMatrix.translate(mPosition);
}

void Camera::setSpeed(float speed)
{
    mSpeed = speed;
}

void Camera::setPosition(const QVector3D &newPos)
{
    mPosition = newPos;
    update();
}

void Camera::setPerspective(float fovy, float screenWidth, float near, float far)
{
    mProjectionMatrix.setToIdentity();
    mProjectionMatrix.perspective(fovy, screenWidth, near, far);
}

void Camera::lookAt(QVector3D position, QVector3D forward, QVector3D up)
{
    mPosition = position;
    mForward = forward;
    mUp = up;
    mViewMatrix.setToIdentity();
    mViewMatrix.lookAt(mPosition, mForward, mUp);
}
