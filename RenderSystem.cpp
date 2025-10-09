#include "RenderSystem.h"
#include "Engine.h"
#include "Renderer.h"

void gea::RenderSystem::Initialize(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::Transform> staticTransformComponents,
                                   std::vector<gea::Mesh> meshes, std::vector<gea::Texture> textures)
{
	mRenderer->initComponents(staticComponents, staticTransformComponents, meshes, textures);
	mRenderer->initVulkan();
}

void gea::RenderSystem::Update(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::Transform> dynamicTransformComponents)
{
	mRenderer->UpdateCompoments(dynamicComponents, dynamicTransformComponents);
	mRenderer->requestUpdate();
	mRenderer->drawFrame();
}

void gea::RenderSystem::Update(float) {
    for (const auto& tr : mEngine->mTransformComponents)
        qDebug() << "Entity " << tr.mEntityID << " Position:("
                  << tr.mPosition.x << ", " << tr.mPosition.y << ", " << tr.mPosition.z << ")\n";
}
