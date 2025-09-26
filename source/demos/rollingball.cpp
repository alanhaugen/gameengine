#include "rollingball.h"
#include "../components/mesh.h"
#include "../components/terrain.h"
#include "../components/spherecollider.h"
#include "../components/trianglecollider.h"

RollingBall::RollingBall()
{
}

void RollingBall::Init()
{
    GameObject* ball = new GameObject;
    ball->AddComponent(new Mesh("Assets/Models/ball.obj"));
    ball->AddComponent(new SphereCollider());

    GameObject* terrain = new GameObject;
    ball->AddComponent(new Terrain("Assets/terrain.png"));
    ball->AddComponent(new TriangleCollider());
}

void RollingBall::Update()
{

}
