#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "component.h"

class BoxCollider : public Component
{
public:
    Physics::Collider* collider;

    BoxCollider();
    void Update();
};

#endif // BOXCOLLIDER_H
