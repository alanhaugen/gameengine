#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "glm/gtc/matrix_transform.hpp"
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

    // Helper functions
    void SetPosition(float x, float y, float z)
    {
        matrix[3].x = x;
        matrix[3].y = y;
        matrix[3].z = z;
    }

    void SetPosition(glm::vec3 pos)
    {
        matrix[3].x = pos.x;
        matrix[3].y = pos.y;
        matrix[3].z = pos.z;
    }

    glm::vec3 GetPosition()
    {
        return glm::vec3(matrix[3]);
    }

    void Scale(float scale_)
    {
        glm::vec3 scale(scale_);
        matrix = glm::scale(matrix, glm::vec3(scale));
    }

    void Scale(glm::vec3 scale)
    {
        matrix = glm::scale(matrix, glm::vec3(scale));
    }

    void Rotate(float radians, glm::vec3 rotation)
    {
        matrix = glm::rotate(matrix, radians, rotation);
    }

    void Translate(glm::vec3 translation)
    {
        matrix = glm::translate(matrix, translation);
    }

    void Translate(float x, float y, float z)
    {
        glm::vec3 translation(x, y, z);
        matrix = glm::translate(matrix, translation);
    }
};

#endif // GAMEOBJECT_H
