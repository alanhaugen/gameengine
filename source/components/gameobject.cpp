#include "gameobject.h"
#include "glm/gtc/matrix_transform.hpp"
#include <qdebug.h>

GameObject::GameObject(const QString name)
{
    Name = name;

    ID = ID_TOP;
    ID_TOP++;

    if (Name.isEmpty())
    {
        Name = "GameObject" + QString::number(ID);
    }



    //qDebug()<<"GameObjName: "<<Name;
}

void GameObject::AddComponent(Component *newComponent)
{
    newComponent->SetGameObjOwner(this);
    components.push_back(newComponent);
    newComponent->OnAttach();
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
   // drawable->ubo.model = glm::translate(drawable->ubo.model,mTransform.mPosition);
    for (unsigned i = 0; i < components.size(); i++)
    {

        components[i]->Update();
    }
}

void GameObject::UpdateTransform(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale)
{

    qDebug()<<"called gamePos oi";
    mTransform.mPosition = Position;
    mTransform.mRotation = Rotation;
    mTransform.mScale = Scale;


    for (unsigned i = 0; i < components.size(); i++)
    {

        components[i]->UpdateTransform();
    }
}


