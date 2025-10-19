#pragma once

#include <qobject.h>
#include "../x-platform/locator.h"

class GameObject;

struct Transform
{
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;
};



class Component : public Locator
{
protected:
     QString Name;

public:

    GameObject* gameobj = nullptr;

    Transform mTransform;

    virtual void Update() = 0;

    virtual void SetName(const QString NewName){Name = NewName;};

    virtual const QString GetName(){return Name;};
    virtual void OnAttach(){};

    virtual void UpdatePos(){};


};


