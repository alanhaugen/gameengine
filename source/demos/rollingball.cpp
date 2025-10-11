#include "rollingball.h"
#include "../components/mesh.h"
#include "../components/terrain.h"
#include "../components/spherecollider.h"
#include "../components/trianglecollider.h"
#include "../components/fpscamera.h"
#include <glm/gtc/matrix_transform.hpp>

class BSplineCurve
{
public:
    float d;
    float n;
    std::vector<float> t;
    std::vector<glm::vec3> c;

    float findKnotInterval(float x)
    {
        int my = n = 1; // indekstilsistekontrollpunkt

        while (x < t[my])
        {
            my--;
        }

        return my;
    }

    glm::vec3 EvaluateBSplineSimple(float x) //Cox-deBoor Algoritme
    {
        int my = findKnotInterval(x);
        std::vector<glm::vec3> a;

        a.reserve(d+1);

        for (int j=0; j<=d; j++)
        {
            a[d-j] = c[my-j];
        }

        for (int k=d; k>0; k--)
        {
            int j = my-k;

            for (int i=0; i<k; i++) {
                j++;

                float w = (x-t[j])/(t[j+k]-t[j]);

                a[i] = a[i] * (1-w) + a[i+1] * w;
            }

            return a[0];
        }

        return glm::vec3();
    }
};

RollingBall::RollingBall()
{
}

void RollingBall::Init()
{
    GameObject* ball = new GameObject;
    ballMesh = new Mesh("Assets/Models/ball.obj", "shaders/phong.vert.spv", "shaders/phong.frag.spv");
    ball->AddComponent(ballMesh);
    ball->AddComponent(new SphereCollider());
    ball->AddComponent(new FPSCamera(&camera));

    GameObject* terrain = new GameObject;
    ball->AddComponent(new Terrain("Assets/terrain.png"));
    ball->AddComponent(new TriangleCollider());

    camera.position = glm::vec3(0.0f, 0.0f, 4.0f);

    gameObjects.push_back(ball);
    gameObjects.push_back(terrain);
}

void RollingBall::Update()
{
    glm::mat4& matrix = ballMesh->drawable->ubo.model;
    matrix = glm::translate(matrix, glm::vec3(0,force,0));

    force -= 0.000098f;

    if (matrix[3].y < -1.0f)
    {
        force = 0.01f;
    }
}
