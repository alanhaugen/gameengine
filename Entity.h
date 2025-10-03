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

    class Entity {
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

// NOTE: AllEntities is now moved to Engine class!
// Remove: extern std::vector<Entity> AllEntities;

} // namespace gea

// Template implementations must be in header
#include "Engine.h"  // Need full definition for template implementation
#include <QDebug>
#include <type_traits>

namespace gea {

template<typename T>
T* Entity::GetComponent(ComponentTypes type)
{
    if (!mEngine) return nullptr;

    short index = GetComponentIndex(type);
    if (index == -1) return nullptr;

    // Access Engine's component arrays
    if constexpr (std::is_same_v<T, Transform>) {
        return &mEngine->GetTransforms()[index];
    }
    else if constexpr (std::is_same_v<T, Mesh>) {
        return &mEngine->GetMeshes()[index];
    }
    else if constexpr (std::is_same_v<T, Texture>) {
        return &mEngine->GetTextures()[index];
    }
    else if constexpr (std::is_same_v<T, Movement>) {
        return &mEngine->GetMovements()[index];
    }
    else if constexpr (std::is_same_v<T, Health>) {
        return &mEngine->GetHealths()[index];
    }
    else if constexpr (std::is_same_v<T, Tower>) {
        return &mEngine->GetTowers()[index];
    }
    else if constexpr (std::is_same_v<T, Enemy>) {
        return &mEngine->GetEnemies()[index];
    }
    else if constexpr (std::is_same_v<T, Projectile>) {
        return &mEngine->GetProjectiles()[index];
    }
    else if constexpr (std::is_same_v<T, AI>) {
        return &mEngine->GetAIs()[index];
    }

    return nullptr;
}

template<typename T>
void Entity::AddComponent(const T& component)
{
    if (!mEngine) {
        qDebug() << "Error: Entity" << mEntityID << "has no Engine reference!";
        return;
    }

    ComponentTypes type;

    if constexpr (std::is_same_v<T, Transform>) {
        type = ComponentTypes::Transform;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Transform component!";
            return;
        }

        Transform newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetTransforms().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetTransforms().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Mesh>) {
        type = ComponentTypes::Mesh;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Mesh component!";
            return;
        }

        Mesh newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetMeshes().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetMeshes().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Texture>) {
        type = ComponentTypes::Texture;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Texture component!";
            return;
        }

        Texture newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetTextures().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetTextures().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Movement>) {
        type = ComponentTypes::Movement;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Movement component!";
            return;
        }

        Movement newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetMovements().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetMovements().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Health>) {
        type = ComponentTypes::Health;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Health component!";
            return;
        }

        Health newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetHealths().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetHealths().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Tower>) {
        type = ComponentTypes::Tower;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Tower component!";
            return;
        }

        Tower newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetTowers().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetTowers().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Enemy>) {
        type = ComponentTypes::Enemy;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Enemy component!";
            return;
        }

        Enemy newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetEnemies().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetEnemies().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, Projectile>) {
        type = ComponentTypes::Projectile;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has Projectile component!";
            return;
        }

        Projectile newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetProjectiles().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetProjectiles().size() - 1;
        mComponents.push_back(ec);
    }
    else if constexpr (std::is_same_v<T, AI>) {
        type = ComponentTypes::AI;

        if (HasComponent(type)) {
            qDebug() << "Entity" << mEntityID << "already has AI component!";
            return;
        }

        AI newComp = component;
        newComp.mEntityID = mEntityID;
        mEngine->GetAIs().push_back(newComp);

        EntityComponents ec;
        ec.mComponentType = type;
        ec.mComponentIndex = mEngine->GetAIs().size() - 1;
        mComponents.push_back(ec);
    }
}

}

#endif // ENTITY_H
