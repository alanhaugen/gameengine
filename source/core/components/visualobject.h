#pragma once

#include "component.h"
#include "glm/gtc/matrix_transform.hpp"

class VisualObject : public Component
{
public:
    Renderer::Drawable* drawable;

    void SetPosition(float x, float y, float z)
    {
        drawable->ubo.model[3].x = x;
        drawable->ubo.model[3].y = y;
        drawable->ubo.model[3].z = z;
    }

    void SetPosition(glm::vec3 pos)
    {
        drawable->ubo.model[3].x = pos.x;
        drawable->ubo.model[3].y = pos.y;
        drawable->ubo.model[3].z = pos.z;
    }

    glm::vec3 GetPosition()
    {
        return glm::vec3(drawable->ubo.model[3]);
    }

    void Scale(float scale_)
    {
        glm::vec3 scale(scale_);
        drawable->ubo.model = glm::scale(drawable->ubo.model, glm::vec3(scale));
    }

    void Scale(glm::vec3 scale)
    {
        drawable->ubo.model = glm::scale(drawable->ubo.model, glm::vec3(scale));
    }

    void Rotate(float radians, glm::vec3 rotation)
    {
        drawable->ubo.model = glm::rotate(drawable->ubo.model, radians, rotation);
    }

    void Translate(glm::vec3 translation)
    {
        drawable->ubo.model = glm::translate(drawable->ubo.model, translation);
    }

    void Translate(float x, float y, float z)
    {
        glm::vec3 translation(x, y, z);
        drawable->ubo.model = glm::translate(drawable->ubo.model, translation);
    }
};
