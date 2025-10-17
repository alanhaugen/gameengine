#include "pong.h"
#include "glm/gtc/matrix_transform.hpp"

Pong::Pong()
{
}

void Pong::Init()
{
    ball = new Sphere(0, 0, -5, glm::vec3(0.1f));
    paddle1 = new Cube(-5, 0, -5, glm::vec3(0.01, 0.05f, 0.01f));
    paddle2 = new Cube( 5, 0, -5, glm::vec3(0.01, 0.05f, 0.01f));

    direction = glm::vec3(0.1f, 0.1f, 0.0f);

    score1 = new Text("Player 1: 0", 10,  10);
    score2 = new Text("Player 2: 0", renderer->windowWidth - 200, 10);
}

void Pong::Update()
{
    if (input.Held(input.Key.UP) || input.Held(input.Key.W))
    {
        glm::mat4& matrix = paddle1->drawable->ubo.model;

        if (matrix[3].y < 2.5f)
        {
            matrix = glm::translate(matrix, glm::vec3(0, 1.0f, 0.0f));
        }
    }
    if (input.Held(input.Key.DOWN) || input.Held(input.Key.S))
    {
        glm::mat4& matrix = paddle1->drawable->ubo.model;

        if (matrix[3].y > -2.5f)
        {
            matrix = glm::translate(matrix, glm::vec3(0, -1.0f, 0.0f));
        }
    }

    glm::mat4& matrix = ball->drawable->ubo.model;

    if (matrix[3].x > 4.5 || matrix[3].x < -4.5)
    {
        direction.x *= -1;
    }

    if (matrix[3].y > 2.5f || matrix[3].y < -2.5f)
    {
        direction.y *= -1;
    }

    matrix = glm::translate(matrix, direction);
}
