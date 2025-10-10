#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"
#include <cstdint>
#include <qstring.h>
#include <glm/glm.hpp>
#include <vector>

struct Transform
{
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;
};

static unsigned int ID_TOP = 0;

class GameObject
{
protected:
    unsigned int ID;
    QString Name;

public:
    GameObject(const QString name = "empty");

    Transform mTransform;
   // std::vector<GameObject*> children;
    std::vector<Component*> components;


    void AddComponent(Component* newComponent);

    void SetName(const QString NewName);


    const QString GetName();

    const uint32_t GetEntityId();

    void Update();
};

#endif // GAMEOBJECT_H
