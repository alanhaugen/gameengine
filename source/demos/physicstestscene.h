#ifndef PHYSICSTESTSCENE_H
#define PHYSICSTESTSCENE_H

#include "../x-platform/scene.h"

class Mesh;
class Terrain;
class SphereCollider;
class Cube;

class PhysicsTestScene : public Scene
{
public:
    PhysicsTestScene();
    void Init();
    void Update();

    float acceleration = 1.0f;
    float mass = 1.0f;

    std::vector<Mesh*> balls;
    std::vector<glm::vec3> directions;

    SphereCollider* sphereCollider;
    Cube* wireframeCubeA;

    int index = 0;

    //Terrain* terrainMesh;
};

#endif // PHYSICSTESTSCENE_H
