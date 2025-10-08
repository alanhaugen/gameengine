#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Components.h"

//Need namespace, since we start to get naming collisions with other code
namespace gea
{
    struct EntityComponents {
        ComponentTypes mComponentType;
        short mComponentIndex{-1};
    };

    class Entity {
    public:
        Entity();
        ~Entity();

        std::size_t mEntityID;                      //unique ID for each Entity
        std::vector<EntityComponents> mComponents;  //holds the components for this Entity

        static std::size_t nextID;  // should be increased by 1 for each entity made


        // Helper methods for component management
        bool HasComponent(ComponentTypes type) const;

        inline short GetComponentIndex(ComponentTypes type) const
        {
            for (const auto& comp : mComponents) {
                if (comp.mComponentType == type)
                    return comp.mComponentIndex;
            }
            return -1;
struct EntityComponents {
    ComponentTypes mComponentType;
    short mComponentIndex{ -1 };
};

class Entity {
public:
    Entity() : mEntityID(++nextID) {}   //pre-increment - start at 1

    std::size_t mEntityID;              //unique ID for each Entity
    std::vector<EntityComponents> mComponents;  //holds the components for this Entity

    static std::size_t nextID; // should be increased by 1 for each entity made

    // Helper methods for component management
    bool HasComponent(ComponentTypes type) const {
        for (const auto& comp : mComponents) {
            if (comp.mComponentType == type) return true;
        }
        return false;
    }

    short GetComponentIndex(ComponentTypes type) const {
        for (const auto& comp : mComponents) {
            if (comp.mComponentType == type) return comp.mComponentIndex;
        }
        return -1;
    }
};

    // Global entity storage - should be stored in an Engine class!
    extern std::vector<Entity> AllEntities;
// Global entity storage
extern std::vector<Entity> EntityVector;

} // namespace gea

#endif // ENTITY_H
