#include "Entity.h"

//crude way to make unique IDs
std::size_t gea::Entity::nextID{0};  //initializing the static class value

namespace gea {

    Entity::Entity() : mEntityID(++nextID)      //pre-increment - start at 1
    {}

    Entity::~Entity()
    {
        //should probably clean up the components this entity has.
    }

    bool Entity::HasComponent(ComponentTypes type) const
    {
        for (const auto& comp : mComponents)
        {
            if (comp.mComponentType == type)
                return true;
        }
        return false;
    }

    short Entity::GetComponentIndex(ComponentTypes type) const
    {
        for (const auto& comp : mComponents)
        {
            if (comp.mComponentType == type)
                return comp.mComponentIndex;
        }
        return -1;
    }

} // namespace gea
