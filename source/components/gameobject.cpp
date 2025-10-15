#include "gameobject.h"

GameObject::GameObject(const QString name)
{
    Name = name;
    ID = ID_TOP;
    ID_TOP++;

    if (name == "empty")
    {
        Name = "GameObject" + QString::number(ID);
    }
}

void GameObject::AddComponent(Component *newComponent)
{
    components.push_back(newComponent);
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

void GameObject::Update()
{
    for (unsigned i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
}
