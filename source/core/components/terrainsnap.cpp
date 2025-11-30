#include "terrainsnap.h"
#include "core/components/gameobject.h"
#include "core/components/terrain.h"

TerrainSnap::TerrainSnap(Terrain* inTerrain)
{
    name = "Terrain Snap";
    terrain = inTerrain;
}

void TerrainSnap::Update(float deltaTime)
{
    if (gameObject)
    {
        glm::vec3 pos = gameObject->GetPosition();
        gameObject->SetPosition(pos.x, terrain->GetHeightAt(gameObject->GetPosition()), pos.z);
    }
}
