#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "Entity.h"
namespace bbl

{
class GameWorld
{
public:
    GameWorld();
    void Setup();
    void update();

    std::vector<bbl::Entity>& getEntities() { return mEntities; }


private:
    std::vector<bbl::Entity> mEntities;
};

}

#endif // GAMEWORLD_H
