#include "RenderSystem.h"

void gea::RenderSystem::Initialize(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents, std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
{
	mRenderer->initComponents(staticComponents, staticTransformComponents, meshes, textures);
	mRenderer->initVulkan();
}

void gea::RenderSystem::Update(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::TransformComponent> dynamicTransformComponents)
{
	mRenderer->UpdateCompoments(dynamicComponents, dynamicTransformComponents);
	mRenderer->requestUpdate();
}