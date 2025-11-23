#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "component.h"

class BoxCollider : public Component
{
public:
    Physics::Collider* collider;

    BoxCollider(GameObject* inGameObject, int type = Physics::DYNAMIC);
    void Update();
    bool IsColliding();
};

#endif // BOXCOLLIDER_H
