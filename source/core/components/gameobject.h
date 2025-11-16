#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "core/components/visualobject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/components/wiredcube.h"
#include <glm/glm.hpp>
#include <vector>
#include <json.hpp>

using json = nlohmann::json;

class Component;

class GameObject
{
public:
    json mat4_to_json(const glm::mat4& m)
    {
        json j = json::array();
        for (int i = 0; i < 16; i++)
            j.push_back(((float*)&m)[i]);
        return j;
    }

    glm::mat4 mat4_from_json(const json& j)
    {
        glm::mat4 m(1.0f);
        for (int i = 0; i < 16; i++)
            ((float*)&m)[i] = j[i];
        return m;
    }

    json to_json()
    {
        return json{
            {"name", name},
            {"id", id},
            {"matrix", mat4_to_json(matrix)},
            {"components", json::array()}
            //{"components", serialize_components(o.components)}
        };
    }

    void from_json(const json& j, GameObject& o)
    {
        o.name = j.value("name", "GameObject");
        o.id = j.at("id");
        //o.matrix = mat4_from_json(j.at("matrix"));

        // Your custom component handling (or skip)
        // o.components = deserialize_components(j.at("components"));
    }

public:
    GameObject(std::string innName = "GameObject");
    unsigned id;

    glm::mat4 matrix;
    std::vector<Component*> components;

    WiredCube* wiredCube;

    std::string name;
    glm::vec3 dimensions = glm::vec3(1.0f);

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

    void Hide()
    {
        for (int i = 0; i < components.size(); i++)
        {
            VisualObject* visualObject = dynamic_cast<VisualObject*>(components[i]);

            if (visualObject)
            {
                visualObject->Hide();
            }
        }
    }

    void Show()
    {
        for (int i = 0; i < components.size(); i++)
        {
            VisualObject* visualObject = dynamic_cast<VisualObject*>(components[i]);

            if (visualObject)
            {
                visualObject->Show();
            }
        }
    }
};

#endif // GAMEOBJECT_H
