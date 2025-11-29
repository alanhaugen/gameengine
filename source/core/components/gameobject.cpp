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

    if (Locator::editor)
    {
        Locator::editor->AddEntity(name.c_str(), id);
    }
}

void GameObject::AddComponent(Component* newComponent)
{
    newComponent->gameObject = this;
    components.push_back(newComponent);

    if (Locator::editor)
    {
        Locator::editor->AddComponent(newComponent->name.c_str(), id);
    }

    VisualObject* visualObject = dynamic_cast<VisualObject*>(newComponent);

    if (visualObject)
    {
        //visualObject->drawable->ubo.model = matrix;
        renderer->SetModel(visualObject->drawable, matrix);
    }
}

void GameObject::Update()
{
    //wiredCube->drawable->ubo.model = matrix;
    renderer->SetModel(wiredCube->drawable, matrix);

    for (unsigned i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
}
