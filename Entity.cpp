#include "Entity.h"

//crude way to make unique IDs
std::size_t gea::Entity::mStaticNextID{0};  //initializing the static class value

namespace gea {

    Entity::Entity() : mEntityID(++mStaticNextID)      //pre-increment - start at 1
    {}

    Entity::~Entity()
    {
        //should probably clean up the components this entity has.
    }

    bool Entity::hasComponent(ComponentTypes type) const
    {
        for (const auto& comp : mComponents)
        {
            if (comp.mComponentType == type)
                return true;
        }
        return false;
    }

    short Entity::getComponentIndex(ComponentTypes type) const
    {
        for (const auto& comp : mComponents)
        {
            if (comp.mComponentType == type)
                return comp.mComponentIndex;
        }
        return -1;
    }

} // namespace gea
