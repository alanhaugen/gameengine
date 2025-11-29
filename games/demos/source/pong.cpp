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
    score2 = new Text("Player 2: 0", renderer->windowWidth - 370.0f, 0.0f);

    instructions1 = new Text("Press SPACE to play", (renderer->windowWidth / 2) - 320.0f, (renderer->windowHeight / 2) - 150.0f);
    instructions2 = new Text("Use W and S to move", (renderer->windowWidth / 2) - 320.0f, (renderer->windowHeight / 2) - 100.0f);

    win1 = new Text("Player 1 Wins!", (renderer->windowWidth / 2) - 320.0f, renderer->windowHeight / 2);
    win2 = new Text("Player 2 Wins!", (renderer->windowWidth / 2) - 320.0f, renderer->windowHeight / 2);
    renderer->Hide(win1->drawable);
    renderer->Hide(win2->drawable);

    renderer->SetClearColor(0, 0, 0);
    audio->PlayMusic("Assets/Sounds/musicMono.wav");
}

void Pong::Update(float deltaTime)
{
    if (state == WIN)
    {
        if (playerOneScore >= 10)
        {
            renderer->Show(win1->drawable);
        }
        else
        {
            renderer->Show(win2->drawable);
        }

        if (input.Held(input.Key.SPACE))
        {
            playerOneScore = 0;
            playerTwoScore = 0;

            renderer->Hide(score1->drawable);
            delete score1;
            score1 = new Text((std::string("Player 1: ") + std::to_string(playerOneScore)).c_str());

            renderer->Hide(score2->drawable);
            delete score2;
            score2 = new Text((std::string("Player 2: ") + std::to_string(playerOneScore)).c_str(), renderer->windowWidth - 370.0f, 0.0f);

            renderer->Hide(win1->drawable);
            renderer->Hide(win2->drawable);

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
        renderer->Show(instructions1->drawable);
        renderer->Show(instructions2->drawable);
        //instructions1->drawable->isVisible = true;
        //instructions2->drawable->isVisible = true;
        return;
    }
    else if (state == WAIT)
    {
        renderer->Show(instructions1->drawable);
        //instructions1->drawable->isVisible = true;
        return;
    }

    renderer->Hide(instructions1->drawable);
    renderer->Hide(instructions2->drawable);
    //instructions1->drawable->isVisible = false;
    //instructions2->drawable->isVisible = false;

    // Get paddle positions
    glm::vec3 playerPos = renderer->GetPosition(paddle1->drawable);
    glm::vec3 aiPos     = renderer->GetPosition(paddle2->drawable);

    // Move Player paddle
    if (input.Held(input.Key.UP) || input.Held(input.Key.W))
    {
        if (playerPos.y < 2.5f)
        {
            renderer->Translate(paddle1->drawable, glm::vec3(0, 0.1f, 0.0f));
        }
    }
    else if (input.Held(input.Key.DOWN) || input.Held(input.Key.S))
    {
        if (playerPos.y > -2.5f)
        {
            renderer->Translate(paddle1->drawable, glm::vec3(0, -0.1f, 0.0f));
        }
    }

    // Get ball position
    glm::vec3 ballPos = renderer->GetPosition(ball->drawable);

    if (aiPos.y < ballPos.y)
    {
        renderer->Translate(paddle2->drawable, glm::vec3(0, 0.05f, 0.0f));
    }
    else if (aiPos.y > ballPos.y)
    {
        renderer->Translate(paddle2->drawable, glm::vec3(0, -0.05f, 0.0f));
    }

    // Check collision with paddles
    if (goRight == false)
    {
        if (ballPos.x < -4.6f && ballPos.x > -4.8f
        && playerPos.y < ballPos.y + 0.5f && playerPos.y > ballPos.y - 0.5f)
        {
            audio->PlaySound("Assets/Sounds/paddle_hit.wav");
            direction.y = (ballPos.y - playerPos.y);
            goRight = true;
        }
    }
    else
    {
        if (ballPos.x > 4.6f && ballPos.x < 4.8f
        && aiPos.y < ballPos.y + 0.5f && aiPos.y > ballPos.y - 0.5f)
        {
            audio->PlaySound("Assets/Sounds/paddle_hit.wav");
            direction.y = (ballPos.y - aiPos.y);
            goRight = false;
        }
    }

    // Check collision with walls
    if (ballPos.y < -3.0f || ballPos.y > 3.0f)
    {
        direction.y *= -1;
        audio->PlaySound("Assets/Sounds/wall_hit.wav");
    }

    // Check score state
    if (ballPos.x > 5.0f)
    {
        ballPos.x = 0.0;
        ballPos.y = 0.0;
        playerPos.y = 0.0;
        aiPos.y = 0.0;
        direction.y = 0.0;
        goRight = false;
        playerOneScore++;
        renderer->Hide(score1->drawable);
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
    else if (ballPos.x < -5.0f)
    {
        ballPos.x = 0.0;
        ballPos.y = 0.0;
        playerPos.y = 0.0;
        aiPos.y = 0.0;
        direction.y = 0.0;
        goRight = true;
        playerTwoScore++;
        renderer->Hide(score2->drawable);
        delete score2;
        score2 = new Text((std::string("Player 2: ") + std::to_string(playerTwoScore)).c_str(), renderer->windowWidth - 370.0f, 0.0f);
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

    renderer->Translate(ball->drawable, direction);
}
