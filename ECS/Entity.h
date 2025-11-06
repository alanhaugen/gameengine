#ifndef ENTITY_H
#define ENTITY_H

#include <qcontainerfwd.h>
#include <vector>
#include <QString>
#include "ECS/Components.h"

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
    Entity();
    ~Entity();

    QString mName{"Nemo"};

    std::size_t mEntityID;                      //unique ID for each Entity
    std::vector<EntityComponents> mComponents;  //holds the components for this Entity

    static std::size_t mStaticNextID;  // should be increased by 1 for each entity made


    // Helper methods for component management
    bool hasComponent(ComponentTypes type) const;
    short getComponentIndex(ComponentTypes type) const;
};

} // namespace gea

#endif // ENTITY_H
