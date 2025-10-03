#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "Components.h"

// Forward declaration
namespace gea {
class Engine;
}

namespace gea
{
struct EntityComponents {
    ComponentTypes mComponentType;
    short mComponentIndex{-1};
};

class Entity {
public:
    Entity(Engine* engine = nullptr);
    ~Entity();

    std::size_t mEntityID;
    std::vector<EntityComponents> mComponents;
    static std::size_t nextID;

    bool HasComponent(ComponentTypes type) const;

    // Template declarations only
    template<typename T>
    T* GetComponent(ComponentTypes type);

    template<typename T>
    void AddComponent(const T& component);

    inline short GetComponentIndex(ComponentTypes type) const
    {
        for (const auto& comp : mComponents) {
            if (comp.mComponentType == type)
                return comp.mComponentIndex;
        }
        return -1;
    }

};

} // namespace gea

#endif // ENTITY_H

