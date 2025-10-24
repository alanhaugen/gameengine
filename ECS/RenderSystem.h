#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ECS/Systems.h"
#include <vector>

//Forward declarations
class Renderer;

namespace gea
{
struct RenderComponent;
struct TransformComponent;
class Mesh;
class Texture;

class RenderSystem : public SystemBase
{
public:
    RenderSystem(class Engine* engineInstance, Renderer* r) : SystemBase(engineInstance), mRenderer(r) {};

    void initialize(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents,
                    std::vector<gea::Mesh*> meshes, std::vector<gea::Texture> textures);
    void update(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::TransformComponent> dynamicTransformComponents);

    // to print position
    void update(float) override;

    Renderer* mRenderer{nullptr};
};

} //namespace gea

#endif // RENDERSYSTEM_H
