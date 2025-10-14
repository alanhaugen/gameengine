#include "GameObject.h"

GameObject::GameObject(const QString name, Entity id)
{
    Name = name;
    ID= id;
}

void GameObject::AddComponent(Component *newComponent)
{
    Components.push_back(newComponent);
}

void GameObject::SetName(const QString NewName)
{
    Name = NewName;
}

const QString GameObject::GetName()
{
    return Name;
}

const Entity GameObject::GetEntityId()
{
    return ID;
}

void GameObject::SetPosition(double X, double Y, double Z)
{
    mTransform.mPosition.x = X;
    mTransform.mPosition.z = Y;
    mTransform.mPosition.y = Z;

}






