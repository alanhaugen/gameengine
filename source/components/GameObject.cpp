#include "GameObject.h"

GameObject::GameObject(const QString name, uint32_t id)
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

const uint32_t GameObject::GetEntityId()
{
    return ID;
}
