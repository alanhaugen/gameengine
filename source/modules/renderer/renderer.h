#pragma once

#include "vertex.h" // this header is insane

class Renderer
{
public:
    class Drawable
    {
    public:
        VkPipeline graphicsPipeline;

        Drawable() {};
        Drawable(std::vector<Vertex> vertices);
    };

    virtual Drawable CreateDrawable() = 0;
};
