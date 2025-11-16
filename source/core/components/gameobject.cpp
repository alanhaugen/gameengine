#include "gameobject.h"
#include "component.h"
#include "core/x-platform/services.h"

unsigned idCurrent = 0;

GameObject::GameObject(const std::string innName)
{
    name = innName;
    id = idCurrent;
    idCurrent++;

    wiredCube = new WiredCube();
    wiredCube->Hide();

    Services::currentScene->gameObjects.push_back(this);
}

void GameObject::AddComponent(Component* newComponent)
{
    newComponent->gameObject = this;
    components.push_back(newComponent);
}

void GameObject::Update()
{
    wiredCube->drawable->ubo.model = matrix;

    for (unsigned i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
}
