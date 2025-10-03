#include "Entity.h"

// Initialize static member - crude way to make unique IDs
std::size_t gea::Entity::nextID{0};

namespace gea {
    Entity::Entity(Engine* engine): mEntityID(++nextID) {}

    Entity::~Entity()
    {
        // TODO: add a way to delete components attached to Entity. Strong vs. weak aggregation?
    }

    bool Entity::HasComponent(ComponentTypes type) const
    {
        for (const auto& comp : mComponents) {
            if (comp.mComponentType == type)
                return true;
        }
        return false;
    }

    // Note: Template implementations (GetComponent and AddComponent)
    // are now in Engine.h after the Engine class definition

}

