#include "ballemitter.h"
#include "core/components/gameobject.h"

BallEmitter::BallEmitter(Terrain *terrain)
{
    name = "Ball Emitter";

    for (int i = 0; i < 1500; i++)
    {
        balls.push_back(new InstancedBall(terrain));
    }

    for (int i = 0; i < balls.size(); i++)
    {
        active.push_back(false);
    }
}

void BallEmitter::Update()
{
    for (int i = 0; i < balls.size(); i++)
    {
        balls[i]->Update();
    }

    for (int i = 0; i < active.size(); i++)
    {
        if (active[i] == false)
        {
            active[i] = true;
            balls[i]->ballMesh->Show();
            float randomNumber1 = rand() % 5;
            float randomNumber2 = rand() % 5;
            randomNumber1 -= randomNumber1 / 2;
            randomNumber2 -= randomNumber2 / 2;
            balls[i]->ballMesh->SetPosition(gameObject->GetPosition() + glm::vec3(randomNumber1,0,randomNumber2));
            break;
        }
    }
}

void BallEmitter::Reset()
{
    for (int i = 0; i < active.size(); i++)
    {
        balls[i]->ballMesh->Hide();
        active[i] = false;
    }
}
