#include "pong.h"
#include "glm/gtc/matrix_transform.hpp"

Pong::Pong()
{
}

void Pong::Init()
{
    ball    = new Sphere(0, 0, -5, glm::vec3(0.1f));
    paddle1 = new Cube(-5, 0, -5, glm::vec3(0.1, 0.5f, 0.1f));
    paddle2 = new Cube( 5, 0, -5, glm::vec3(0.1, 0.5f, 0.1f));

    direction = glm::vec3(0.5f, 0.5f, 0.0f);

    score1 = new Text("Player 1: 0", 0, 0);
    score2 = new Text("Player 2: 0", 700.0f, 0.0f);

    instructions1 = new Text("Press SPACE to play", 250.0f, 200.0f);
    instructions2 = new Text("Use W and S to move", 250.0f, 250.0f);

    win1 = new Text("Player 1 Wins!", 300.0f, 200.0f);
    win2 = new Text("Player 2 Wins!", 300.0f, 200.0f);
    win1->drawable->isVisible = false;
    win2->drawable->isVisible = false;

    renderer->SetClearColor(0, 0, 0);
    audio->PlayMusic("Assets/Sounds/musicMono.wav");
}

void Pong::Update()
{
    if (state == WIN)
    {
        if (playerOneScore >= 10)
        {
            win1->drawable->isVisible = true;
        }
        else
        {
            win2->drawable->isVisible = true;
        }

        if (input.Held(input.Key.SPACE))
        {
            playerOneScore = 0;
            playerTwoScore = 0;

            score1->drawable->isVisible = false;
            delete score1;
            score1 = new Text((std::string("Player 1: ") + std::to_string(playerOneScore)).c_str());

            score2->drawable->isVisible = false;
            delete score2;
            score2 = new Text((std::string("Player 2: ") + std::to_string(playerOneScore)).c_str(), 700.0f, 0.0f);

            win1->drawable->isVisible = false;
            win2->drawable->isVisible = false;

            state = START;
        }

        return;
    }
    else if (input.Held(input.Key.SPACE))
    {
        state = PLAYING;
    }

    if (state == START)
    {
        instructions1->drawable->isVisible = true;
        instructions2->drawable->isVisible = true;
        return;
    }
    else if (state == WAIT)
    {
        instructions1->drawable->isVisible = true;
        return;
    }

    instructions1->drawable->isVisible = false;
    instructions2->drawable->isVisible = false;

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
            audio->PlaySound("Assets/Sounds/paddle_hit.wav");
            direction.y = (ballMatrix[3].y - playerMatrix[3].y);
            goRight = true;
        }
    }
    else
    {
        if (ballMatrix[3].x > 4.6f && ballMatrix[3].x < 4.8f
        && aiMatrix[3].y < ballMatrix[3].y + 0.5f && aiMatrix[3].y > ballMatrix[3].y - 0.5f)
        {
            audio->PlaySound("Assets/Sounds/paddle_hit.wav");
            direction.y = (ballMatrix[3].y - aiMatrix[3].y);
            goRight = false;
        }
    }

    // Check collision with walls
    if (ballMatrix[3].y < -3.0f || ballMatrix[3].y > 3.0f)
    {
        direction.y *= -1;
        audio->PlaySound("Assets/Sounds/wall_hit.wav");
    }

    // Check score state
    if (ballMatrix[3].x > 5.0f)
    {
        ballMatrix[3].x = 0.0;
        ballMatrix[3].y = 0.0;
        playerMatrix[3].y = 0.0;
        aiMatrix[3].y = 0.0;
        direction.y = 0.0;
        goRight = false;
        playerOneScore++;
        score1->drawable->isVisible = false;
        delete score1;
        score1 = new Text((std::string("Player 1: ") + std::to_string(playerOneScore)).c_str());
        audio->PlaySound("Assets/Sounds/score.wav");
        if (playerOneScore >= 10)
        {
            state = WIN;
        }
        else
        {
            state = WAIT;
        }
    }
    else if (ballMatrix[3].x < -5.0f)
    {
        ballMatrix[3].x = 0.0;
        ballMatrix[3].y = 0.0;
        playerMatrix[3].y = 0.0;
        aiMatrix[3].y = 0.0;
        direction.y = 0.0;
        goRight = true;
        playerTwoScore++;
        score2->drawable->isVisible = false;
        delete score2;
        score2 = new Text((std::string("Player 2: ") + std::to_string(playerTwoScore)).c_str(), 700.0f, 0.0f);
        audio->PlaySound("Assets/Sounds/score.wav");
        if (playerTwoScore >= 10)
        {
            state = WIN;
        }
        else
        {
            state = WAIT;
        }
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

void Pong::Clean()
{
}
