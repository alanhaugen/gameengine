#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "Components.h"

//fd
namespace gea
{
    class Engine;
}

//Need namespace, since we start to get naming collisions with other code
namespace gea
{
    struct EntityComponents
    {
        ComponentTypes mComponentType;
        short mComponentIndex{-1};
    };

    class Entity
    {
    public:
        Entity(Engine* engine = nullptr);
        ~Entity();

        std::size_t mEntityID;
        std::vector<EntityComponents> mComponents;
        static std::size_t nextID;

        // Helper methods for component management
        bool HasComponent(ComponentTypes type) const;

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

    private:
        Engine* mEngine{nullptr};
    };

}


#endif // ENTITY_H
