#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"

class System
{
public:
    virtual ~System() = default;

public:
    virtual void update(bbl::Entity& entity) = 0;

};





#endif // SYSTEM_H
