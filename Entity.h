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
        Entity() : mEntityId(++nextId){}

        std::size_t mEntityId;
        std::vector<EntityComponents> mComponents;

        inline static std::size_t nextId{0};

    };

}
//namespace bbl




#endif // ENTITY_H
