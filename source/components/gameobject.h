#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "component.h"
#include <cstdint>
#include <qstring.h>
#include <glm/glm.hpp>
#include <vector>



static unsigned int ID_TOP = 0;

class GameObject
{
protected:
    unsigned int ID;
    QString Name;


public:
    GameObject(const QString name);

    Renderer::Drawable* drawable;
    Transform mTransform;
    // std::vector<GameObject*> children;
    std::vector<Component*> components;


    void AddComponent(Component* newComponent);

    void SetName(const QString NewName);


    const QString GetName();

    const uint32_t GetEntityId();

    void Update();
    void UpdateTransform(glm::vec3 Position,glm::vec3 Rotation,glm::vec3 Scale);

};

#endif // GAMEOBJECT_H
