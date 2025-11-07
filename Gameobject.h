#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <qstring.h>
#include "components.h"
#include <glm/glm.hpp>
#include <vector>

struct transform{
    glm::vec3 mPosition;
    glm::vec3 mRoation;
    glm::vec3 mScale;
};



class GameObject
{

protected:
    QString Name;

public:
    GameObject(const QString name = "Nothing but Marvin");

    transform mTransform;

    std::vector<Component*> components;

    void addComponent(Component* newComponent);

    void setName(const QString Name);

    const QString getName();

    void update();


};

#endif // GAMEOBJECT_H
