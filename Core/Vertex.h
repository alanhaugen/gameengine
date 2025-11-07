#ifndef VERTEX_H
#define VERTEX_H

#include <array>
#include <glm/glm.hpp>
#include <vulkan/vulkan_core.h>
//#include "Utilities.h"

struct Vertex 
{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();;

    bool operator==(const Vertex& other) const;;
};

#endif // VERTEX_H
