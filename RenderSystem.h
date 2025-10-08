#include "Renderer.h"
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

namespace gea
{
	struct RenderSystem
	{
		RenderSystem(Renderer* r) : mRenderer(r) {};
		void Initialize(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures);
		void Update(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::TransformComponent> dynamicTransformComponents);
		Renderer* mRenderer;
	};
}

#endif // RENDERSYSTEM_H
