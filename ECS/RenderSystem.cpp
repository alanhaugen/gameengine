#include "RenderSystem.h"
#include "Core/Engine.h"
#include "Core/Renderer.h"

void gea::RenderSystem::initialize(std::vector<gea::RenderComponent> staticComponents, std::vector<gea::TransformComponent> staticTransformComponents,
                                   std::vector<gea::Mesh*> meshes, std::vector<gea::Texture*> textures)
{
    mRenderer->initComponents(staticComponents, staticTransformComponents, meshes, textures);
	mRenderer->initVulkan();
}

void gea::RenderSystem::update(std::vector<gea::RenderComponent> dynamicComponents, std::vector<gea::TransformComponent> dynamicTransformComponents)
{
	mRenderer->updateCompoments(dynamicComponents, dynamicTransformComponents);
    mRenderer->drawFrame();         //draw one frame
    mRenderer->requestUpdate();     //ask for the next fram to be drawn - will call engine->update()
}

void gea::RenderSystem::update(float) {
    for (const auto& tr : mEngine->mTransformComponents)
        qDebug() << "Entity " << tr.mEntityID << " Position:("
                  << tr.mPosition.x << ", " << tr.mPosition.y << ", " << tr.mPosition.z << ")\n";
}
