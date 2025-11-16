#include "gameobject.h"
#include "component.h"

unsigned idCurrent = 0;

GameObject::GameObject(const std::string innName)
{
    name = innName;
    id = idCurrent;
    idCurrent++;
}

void GameObject::AddComponent(Component *newComponent)
{
    newComponent->gameObject = this;
    components.push_back(newComponent);
}

void GameObject::Update()
{
    for (unsigned i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
}
