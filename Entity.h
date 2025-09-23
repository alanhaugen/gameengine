#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Components.h"

//Need namespace, since we start to get naming collisions with other code
namespace gea
{
    struct EntityComponents {
        ComponentTypes mComponentType;
        short mCompoentIndex{-1};
    };

    class Entity {
    public:
        Entity() : mEntityID(++nextID) {}   //pre-increment - start at 1

        std::size_t mEntityID;              //unique ID for each Entity
        std::vector<EntityComponents> mComponents;  //holds the components for this Entity

        static std::size_t nextID; // should be increased by 1 for each entity made
    };

    //crude way to make unique IDs
    std::size_t Entity::nextID{0};  //initializing the static class value

} // namespace gea

#endif // ENTITY_H
