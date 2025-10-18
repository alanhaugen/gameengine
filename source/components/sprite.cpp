#include "sprite.h"
#include "glm/gtc/matrix_transform.hpp"

Sprite::Sprite(const char* texture, float x, float y, const char *glyphs)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    int numberOfQuads = 1;

    if (glyphs[0] != '\0')
    {
        numberOfQuads = strlen(glyphs);
    }

    for (int i = 0; i < numberOfQuads; i++)
    {
        float glyph = glyphs[i] - 32;

        float indent = i;
        Vertex bottomLeft(-1.0 + indent, -1.0f, 0.0f);  // 0
        Vertex bottomRight(1.0f + indent, -1.0f, 0.0f); // 1
        Vertex topRight(1.0f + indent, 1.0f, 0.0f);     // 2
        Vertex topLeft(-1.0f + indent, 1.0f, 0.0f);     // 3

        bottomLeft.texCoord  = glm::vec2(0, 0);
        bottomRight.texCoord = glm::vec2(1, 0);
        topRight.texCoord    = glm::vec2(1, 1);
        topLeft.texCoord     = glm::vec2(0, 1);

        bottomLeft.glyph  = glyph;
        bottomRight.glyph = glyph;
        topRight.glyph    = glyph;
        topLeft.glyph     = glyph;

        vertices.push_back(bottomRight);
        vertices.push_back(bottomLeft);
        vertices.push_back(topRight);
        vertices.push_back(topRight);
        vertices.push_back(bottomLeft);
        vertices.push_back(topLeft);
    }

    drawable = &renderer->CreateDrawable(vertices,
                                         indices,
                                         "shaders/gui.vert.spv",
                                         "shaders/gui.frag.spv",
                                         Renderer::TRIANGLES,
                                         texture);

    drawable->ubo.width.x = 64.0f;
    drawable->ubo.height.x = 64.0f;
    drawable->ubo.totalWidth.x = 64.0f;
    drawable->ubo.totalHeight.x = 6144.0f;
    drawable->ubo.flip.x = 0.0f;
    drawable->ubo.flipVertical.x = 0.0f;

    drawable->ubo.model = glm::translate(drawable->ubo.model, glm::vec3(x,y,0));
}

void Sprite::Update()
{
}
