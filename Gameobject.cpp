#include "Gameobject.h"

GameObject::GameObject(const QString name)
{
    Name = name;

    //Entity ID? mabye if we want to use stack mabye mabye mabye

    if (name == "Nothing but Marvin")
    {
        //Give it id perhaps. So we dont have multiple faulty Objects
    }
}




void GameObject::addComponent(Component * newComponent)
{
    components.push_back(newComponent);
}

const QString GameObject::getName()
{
    return Name;
}

void GameObject::setName(const QString NewName)
{
    Name = NewName;
}

// void GameObject::update()
// {
//     for (unsigned i = 0; i < components.size(); i++)
//     {
//         components[i]->Update();
//     }
// }
