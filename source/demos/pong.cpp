#include "pong.h"
#include "glm/gtc/matrix_transform.hpp"

Pong::Pong()
{
}

void Pong::Init()
{
    ball    = new Sphere(0, 0, -5, glm::vec3(0.1f));
    paddle1 = new Cube(-5, 0, -5, glm::vec3(0.01, 0.05f, 0.01f));
    paddle2 = new Cube( 5, 0, -5, glm::vec3(0.01, 0.05f, 0.01f));

    direction = glm::vec3(0.1f, 0.1f, 0.0f);

    score1 = new Text("Player 1: 0", 10,  10);
    score2 = new Text("Player 2: 0", renderer->windowWidth - 200.0f, 10);
}

void Pong::Update()
{
    // Move Player paddle
    if (input.Held(input.Key.UP) || input.Held(input.Key.W))
    {
        glm::mat4& matrix = paddle1->drawable->ubo.model;

        if (matrix[3].y < 2.5f)
        {
            matrix = glm::translate(matrix, glm::vec3(0, 1.0f, 0.0f));
        }
    }
    else if (input.Held(input.Key.DOWN) || input.Held(input.Key.S))
    {
        glm::mat4& matrix = paddle1->drawable->ubo.model;

        if (matrix[3].y > -2.5f)
        {
            matrix = glm::translate(matrix, glm::vec3(0, -1.0f, 0.0f));
        }
    }

    // Get ball matrix
    glm::mat4& ballMatrix = ball->drawable->ubo.model;

    // Control AI
    glm::mat4& aiMatrix = paddle2->drawable->ubo.model;

    if (aiMatrix[3].y < ballMatrix[3].y)
    {
        aiMatrix = glm::translate(aiMatrix, glm::vec3(0, 0.1f, 0.0f));
    }
    else if (aiMatrix[3].y > ballMatrix[3].y)
    {
        aiMatrix = glm::translate(aiMatrix, glm::vec3(0, -0.1f, 0.0f));
    }

    // Move the ball
    if (ballMatrix[3].x > 4.6 || ballMatrix[3].x < -4.6)
    {
        direction.x *= -1;
    }

    // If collision
    if (ballMatrix[3].y > 3.0f || ballMatrix[3].y < -3.0f)
    {
        direction.y *= -1;
    }

    ballMatrix = glm::translate(ballMatrix, direction);
}
