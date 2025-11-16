#include "sprite.h"
#include "core/components/gameobject.h"
#include "glm/gtc/matrix_transform.hpp"

Sprite::Sprite(const char* texture, float x, float y, float scaleX, float scaleY, int width, int height, const char *glyphs)
{
    name = "Sprite";
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
                                         texture,
                                         false);

    if (width == 0 && height == 0)
    {
        drawable->ubo.width.x  = drawable->textureWidth;
        drawable->ubo.height.x = drawable->textureHeight;
    }
    else
    {
        drawable->ubo.width.x  = width;
        drawable->ubo.height.x = height;
    }

    drawable->ubo.totalWidth.x = drawable->textureWidth;
    drawable->ubo.totalHeight.x = drawable->textureHeight;
    drawable->ubo.flip.x = 0.0f;
    drawable->ubo.flipVertical.x = 0.0f;
    drawable->ubo.scaleX.x = scaleX;
    drawable->ubo.scaleY.x = scaleY;

    drawable->ubo.model = glm::translate(drawable->ubo.model, glm::vec3(x,y,0));
}

void Sprite::Update()
{
    if (gameObject)
    {
        drawable->ubo.model = gameObject->matrix;
    }
}

bool Sprite::IsPressed()
{
    if (drawable->isVisible == false)
    {
        return false;
    }

    if (input.mouse.Down)
    {
        if (input.mouse.x > GetPosition().x &&
            input.mouse.x < GetPosition().x + (drawable->textureWidth * drawable->ubo.scaleX.x) &&
            input.mouse.y > GetPosition().y &&
            input.mouse.y < GetPosition().y + (drawable->textureHeight * drawable->ubo.scaleY.x))
        {
            return true;
        }
    }

    return false;
}
