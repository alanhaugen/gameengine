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

class GameObject
{
protected:
    uint32_t ID;
    QString Name;

public:
    GameObject(const QString name, uint32_t id);

    Transform mTransform;
   // std::vector<GameObject*> children;
    std::vector<Component*> Components;


    void AddComponent(Component* newComponent);

    void SetName(const QString NewName);


    const QString GetName();

    const uint32_t GetEntityId();

};

#endif // GAMEOBJECT_H
