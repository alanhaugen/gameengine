#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"
#include <cstdint>
#include <qstring.h>
#include <glm/glm.hpp>
#include <vector>

using Entity = uint32_t;


struct Transform
{
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;

};


class GameObject
{

protected:
    Entity ID;
    QString Name;
public:
    GameObject(const QString name, Entity id);

    Transform mTransform;
   // std::vector<GameObject*> children;
    std::vector<Component*> Components;


    void AddComponent(Component* newComponent);

    void SetName(const QString NewName);


    const QString GetName();

    const Entity GetEntityId();

    void SetPosition(double X,double Y, double Z);



};

#endif // GAMEOBJECT_H
