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
    newComponent->gameobj = this;
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

void GameObject::UpdatePos(float x, float y, float z)
{

    qDebug()<<"called gamePos oi";
    glm::vec3 pos =glm::vec3(x, y, z);
    mTransform.mPosition = pos;

   // qDebug()<<"Gameobjpos: "<<mTransform.mPosition.x;

    for (unsigned i = 0; i < components.size(); i++)
    {

        components[i]->UpdatePos();
    }
    //drawable->ubo.model = glm::translate(drawable->ubo.model, glm::vec3(-0.3, 0, 0));
    //glm::translate(glm::vec3(-0.3, 0, 0));
}
