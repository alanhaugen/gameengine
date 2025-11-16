#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <vector>

class Component;

class GameObject
{
public:
    GameObject(std::string innName = "GameObject");
    unsigned id;

    glm::mat4 matrix;
    std::vector<Component*> components;

    std::string name;

    void AddComponent(Component* newComponent);

    void Update();
};

#endif // GAMEOBJECT_H
