#ifndef CUBE_H
#define CUBE_H

#include "component.h"

class Cube : public Component
{
private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    void Init();

public:
    Cube();
    ~Cube();

    void Update();

    Cube(float x = 0.0f,
         float y = 0.0f,
         float z = 0.0f,
         glm::vec3 scale = glm::vec3(0.1f),
         glm::vec3 color = glm::vec3(1.0f));

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setColor(const glm::vec3& color);
    void setTransform(const glm::vec3& position, const glm::vec3& rotation);
    void setVisible(bool visible);
    bool isVisible() const;

    Renderer::Drawable* drawable;

    glm::vec3 GetNormal(const glm::vec3 position) const;
};

#endif // CUBE_H
