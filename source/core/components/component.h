#pragma once

#include <qobject.h>
#include "core/x-platform/locator.h"

class GameObject;

struct Transform
{
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale {1.0,1.0,1.0};
};



class Component : public Locator
{
protected:
    QString Name;
    uint32_t entityOwner = 0;

public:

    Transform mTransform;

    virtual void Update() = 0;

    virtual void SetName(const QString NewName){Name = NewName;};

    virtual const QString GetName(){return Name;};

    uint32_t GetEntityOwner(){return entityOwner;}

    virtual void SetEntityOwner(uint32_t EntityOwner){entityOwner = EntityOwner;}

    virtual void OnAttach(){};

    virtual void UpdateTransform(Transform transform){};

};


