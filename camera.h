#ifndef CAMERA_H
#define CAMERA_H
#include <QMatrix4x4>

class camera
{
public:
    camera();
    ~camera() {}

private:

    QMatrix4x4 mProjectionMatrix{};
    QMatrix4x4 mViewMatrix{};

    QVector3D mPosition = {0, 0, 0};
    QVector3D mForward = {0, 0, -1.0};
    QVector3D mUp = {0, 1, 0};

    float mPitch = 0.f;
    float mYaw = 0.f;
};

#endif // CAMERA_H
