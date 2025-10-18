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

    direction = glm::vec3(0.5f, 0.5f, 0.0f);

    score1 = new Text("Player 1: 0", 0, 0);
    score2 = new Text("Player 2: 0", 700.0f, 0.0f);

    renderer->SetClearColor(0, 0, 0);
}

void Pong::Update()
{
    // Get paddle positions
    glm::mat4& playerMatrix = paddle1->drawable->ubo.model;
    glm::mat4& aiMatrix     = paddle2->drawable->ubo.model;

    // Move Player paddle
    if (input.Held(input.Key.UP) || input.Held(input.Key.W))
    {
        if (playerMatrix[3].y < 2.5f)
        {
            playerMatrix = glm::translate(playerMatrix, glm::vec3(0, 1.0f, 0.0f));
        }
    }
    else if (input.Held(input.Key.DOWN) || input.Held(input.Key.S))
    {
        if (playerMatrix[3].y > -2.5f)
        {
            playerMatrix = glm::translate(playerMatrix, glm::vec3(0, -1.0f, 0.0f));
        }
    }

    // Get ball matrix
    glm::mat4& ballMatrix = ball->drawable->ubo.model;

    if (aiMatrix[3].y < ballMatrix[3].y)
    {
        aiMatrix = glm::translate(aiMatrix, glm::vec3(0, 0.5f, 0.0f));
    }
    else if (aiMatrix[3].y > ballMatrix[3].y)
    {
        aiMatrix = glm::translate(aiMatrix, glm::vec3(0, -0.5f, 0.0f));
    }

    // Check collision with paddles
    if (goRight == false)
    {
        if (ballMatrix[3].x < -4.6f && ballMatrix[3].x > -4.8f
        && playerMatrix[3].y < ballMatrix[3].y + 0.5f && playerMatrix[3].y > ballMatrix[3].y - 0.5f)
        {
            direction.y = (ballMatrix[3].y - playerMatrix[3].y);
            goRight = true;
        }
    }
    else
    {
        if (ballMatrix[3].x > 4.6f && ballMatrix[3].x < 4.8f
        && aiMatrix[3].y < ballMatrix[3].y + 0.5f && aiMatrix[3].y > ballMatrix[3].y - 0.5f)
        {
            direction.y = (ballMatrix[3].y - aiMatrix[3].y);
            goRight = false;
        }
    }

    // Check collision with walls
    if (ballMatrix[3].y < -3.0f || ballMatrix[3].y > 3.0f)
    {
        direction.y *= -1;
    }

    // Check score state
    if (ballMatrix[3].x > 5.0f)
    {
        ballMatrix[3].x = 0.0;
        ballMatrix[3].y = 0.0;
        direction.y = 0.5;
        goRight = false;
        playerOneScore++;
        score1->drawable->isVisible = false;
        delete score1;
        score1 = new Text((std::string("Player 1: ") + std::to_string(playerOneScore)).c_str());
    }
    else if (ballMatrix[3].x < -5.0f)
    {
        ballMatrix[3].x = 0.0;
        ballMatrix[3].y = 0.0;
        direction.y = -0.5;
        goRight = true;
        playerTwoScore++;
        score2->drawable->isVisible = false;
        delete score2;
        score2 = new Text((std::string("Player 2: ") + std::to_string(playerTwoScore)).c_str(), 700.0f, 0.0f);
    }

    // Update direction
    if (goRight)
    {
        direction.x = abs(direction.x);
    }
    else
    {
        direction.x = -abs(direction.x);
    }

    ballMatrix = glm::translate(ballMatrix, direction);
}
