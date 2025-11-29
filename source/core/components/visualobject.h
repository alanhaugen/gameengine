#pragma once

#include "component.h"
#include "glm/gtc/matrix_transform.hpp"

class VisualObject : public Component
{
public:
    int drawable;

    void SetPosition(float x, float y, float z)
    {
        renderer->SetPosition(drawable, glm::vec3(x, y, z));
    }

    void SetPosition(glm::vec3 pos)
    {
        renderer->SetPosition(drawable, pos);
    }

    glm::vec3 GetPosition()
    {
        return renderer->GetPosition(drawable);
    }

    void Scale(float scale_)
    {
        glm::vec3 scale(scale_);
        //drawable->ubo.model = glm::scale(drawable->ubo.model, glm::vec3(scale));
        renderer->Scale(drawable, scale);
    }

    void Scale(glm::vec3 scale)
    {
        //drawable->ubo.model = glm::scale(drawable->ubo.model, glm::vec3(scale));
        renderer->Scale(drawable, scale);
    }

    void Rotate(float radians, glm::vec3 rotation)
    {
        renderer->Rotate(drawable, radians, rotation);
        //drawable->ubo.model = glm::rotate(drawable->ubo.model, radians, rotation);
    }

    void Translate(glm::vec3 translation)
    {
        //drawable->ubo.model = glm::translate(drawable->ubo.model, translation);
        renderer->Translate(drawable, translation);
    }

    void Translate(float x, float y, float z)
    {
        glm::vec3 translation(x, y, z);
        renderer->Translate(drawable, translation);
        //drawable->ubo.model = glm::translate(drawable->ubo.model, translation);
    }

    void Show()
    {
        renderer->Show(drawable);
    }

    void Hide()
    {
        renderer->Hide(drawable);
    }
};
