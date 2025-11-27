#ifndef TERRAINSNAP_H
#define TERRAINSNAP_H

#include "core/components/component.h"

class Terrain;

class TerrainSnap : public Component
{
public:
    Terrain* terrain;
    TerrainSnap(Terrain* inTerrain);
    void Update();
};

#endif // TERRAINSNAP_H
