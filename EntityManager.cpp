#include "EntityManager.h"

EntityManager::EntityManager(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue)
    : mDevice(device), mPhysicalDevice(physicalDevice), mCommandPool(commandPool), mGraphicsQueue(graphicsQueue)
{
}

bbl::Entity EntityManager::createPlayer()
{
    bbl::Entity player;

    // Adding mesh to the Player (simple triangle for now)
    bbl::mesh m;
    m.mEntityId = player.getEntityId();
    // Example vertices for a triangle
    m.mVertices = {
        {{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.5f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
    };
    m.mIndices = {0, 1, 2};
    // Create Vulkan buffers
    bbl::ModelLoader modelLoader(mDevice, mPhysicalDevice, mCommandPool, mGraphicsQueue);
    modelLoader.createVertexBuffer(m.mVertices, m.mVertexBuffer, m.mVertexBufferMemory);
    modelLoader.createIndexBuffer(m.mIndices, m.mIndexBuffer, m.mIndexBufferMemory);
    bbl::MeshComponent.push_back(m);
    player.addComponent(bbl::ComponentTypes::mesh, static_cast<short>(bbl::MeshComponent.size() - 1));

    // Adding transform
    bbl::transform t;
    t.mEntityId = player.getEntityId();
    t.mPosition = glm::vec3(0.0f, 0.0f, 0.0f); // Starting position
    bbl::TransformComponent.push_back(t);
    player.addComponent(bbl::ComponentTypes::transform, static_cast<short>(bbl::TransformComponent.size() - 1));

    // Adding physics component
    bbl::physics p;
    p.mEntityId = player.getEntityId();
    bbl::PhysicsComponent.push_back(p);
    player.addComponent(bbl::ComponentTypes::physics, static_cast<short>(bbl::PhysicsComponent.size() - 1));

    return player; // Move constructor will handle this
}

void EntityManager::destroyEntity(bbl::Entity& entity)
{
    for (const auto& comp : entity.getComponents()) {
        if (comp.mComponentType == bbl::ComponentTypes::mesh) {
            auto& mesh = bbl::MeshComponent[comp.mComponentIndex];
            vkDestroyBuffer(mDevice, mesh.mVertexBuffer, nullptr);
            vkFreeMemory(mDevice, mesh.mVertexBufferMemory, nullptr);
            vkDestroyBuffer(mDevice, mesh.mIndexBuffer, nullptr);
            vkFreeMemory(mDevice, mesh.mIndexBufferMemory, nullptr);
            bbl::MeshComponent.erase(bbl::MeshComponent.begin() + comp.mComponentIndex);
        } else if (comp.mComponentType == bbl::ComponentTypes::texture) {
            auto& tex = bbl::TextureComponent[comp.mComponentIndex];
            vkDestroySampler(mDevice, tex.mTextureSampler, nullptr);
            vkDestroyImageView(mDevice, tex.mTextureImageView, nullptr);
            vkDestroyImage(mDevice, tex.mTextureImage, nullptr);
            vkFreeMemory(mDevice, tex.mTextureImageMemory, nullptr);
            bbl::TextureComponent.erase(bbl::TextureComponent.begin() + comp.mComponentIndex);
        }
    }
    // Note: This simplistic erase doesn't update mComponentIndex in other entities. See previous response for a better approach.
}

void EntityManager::addEntities(const std::vector<bbl::Entity>& entities)
{
    for (const auto& entity : entities) {
        // Optionally validate or adjust components if needed
        for (const auto& comp : entity.getComponents()) {
            if (comp.mComponentType == bbl::ComponentTypes::mesh) {
                // Ensure mesh component indices are valid; this is a no-op in current design
            } else if (comp.mComponentType == bbl::ComponentTypes::transform) {
                // Ensure transform component is registered
            } else if (comp.mComponentType == bbl::ComponentTypes::texture) {
                // Ensure texture component is registered
            }
        }
        // In this design, we don't need to re-add to global vectors since ModelLoader already did this
        // However, you might want to track entities internally if needed
    }
}
