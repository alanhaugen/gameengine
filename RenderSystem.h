#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Systems.h"
#include <vector>

//Forward declarations
class Renderer;

namespace gea
{
struct RenderComponent;
struct Transform;
class Mesh;
class Texture;

    class RenderSystem : public SystemBase
	{
    public:
        RenderSystem(class Engine* engineInstance, Renderer* r) : SystemBase(engineInstance), mRenderer(r) {};

        void Initialize(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents,
                        std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures);
        void Update(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::Transform> dynamicTransformComponents);

        Renderer* mRenderer{nullptr};

        // to print position
        void Update(float) override;
	};
}

#endif // RENDERSYSTEM_H
