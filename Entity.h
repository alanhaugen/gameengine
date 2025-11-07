#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "Components.h"

namespace bbl
{
struct EntityComponents
{
    ComponentTypes mComponentType;
    short mComponentIndex{-1};
};

class Entity
{
public:
    Entity() : mEntityId(++nextId) {}
    ~Entity() = default; // Virtual destructor for safety if derived

    // Disable copying
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Enable moving
    Entity(Entity&& other) noexcept : mEntityId(other.mEntityId), mComponents(std::move(other.mComponents)) {
        other.mEntityId = 0; // Invalidate moved-from object
        other.mComponents.clear();
    }
    Entity& operator=(Entity&& other) noexcept {
        if (this != &other) {
            mEntityId = other.mEntityId;
            mComponents = std::move(other.mComponents);
            other.mEntityId = 0;
            other.mComponents.clear();
        }
        return *this;
    }

    // Getters
    std::size_t getEntityId() const { return mEntityId; }
    const std::vector<EntityComponents>& getComponents() const { return mComponents; }

    // Add a component (for use by EntityManager)
    void addComponent(ComponentTypes type, short index) {
        mComponents.push_back({type, index});
    }

    inline static std::size_t nextId{0};

private:
    std::size_t mEntityId;
    std::vector<EntityComponents> mComponents;


};

} // namespace bbl

#endif // ENTITY_H
