#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include <vulkan/vulkan.h>
#include "modelloader.h"
#include <vector>


class EntityManager
{
public:
    EntityManager(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue graphicsQueue);

    bbl::Entity createPlayer();
    void destroyEntity(bbl::Entity& entity);
    void addEntities(const std::vector<bbl::Entity>& entities); // New method to adopt externally created entities

private:
    VkDevice mDevice;
    VkPhysicalDevice mPhysicalDevice;
    VkCommandPool mCommandPool;
    VkQueue mGraphicsQueue;
};

#endif // ENTITYMANAGER_H
