#include "EntityManager.h"

EntityManager::EntityManager()
{

}


bbl::Entity createPlayer()
{
    bbl::Entity player;

    //Adding mesh to the Player
    bbl::mesh m;
    m.mEntityId = player.mEntityId;
    bbl::MeshComponent.push_back(m);
    player.mComponents.push_back( { bbl::ComponentTypes::mesh, static_cast<short>(bbl::MeshComponent.size() - 1)  }   );

    //Adding transform
    bbl::transform t;
    t.mEntityId = player.mEntityId;
    bbl::TransformComponent.push_back(t);
    player.mComponents.push_back( {bbl::ComponentTypes::transform, static_cast<short>(bbl::TransformComponent.size() - 1)} );


    //Adding physics component
    bbl::physics p;
    p.mEntityId = player.mEntityId;
    bbl::PhysicsComponent.push_back(p);
    player.mComponents.push_back( {bbl::ComponentTypes::physics, static_cast<short>(bbl::PhysicsComponent.size() -1 )} );


    //Add more components beneath


    return player;
}
