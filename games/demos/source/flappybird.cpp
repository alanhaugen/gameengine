#include "flappybird.h"

FlappyBird::FlappyBird()
{
}

void FlappyBird::Init()
{
    for (int i = 0; i < MAX_SCORE; i++)
    {
        Text* score = new Text(std::string("Score: " + std::to_string(i)).c_str());
        renderer->isVisible(score->drawable);
        //score->drawable->isVisible = false;
        scores.push_back(score);
    }

    score = scores[0];
    renderer->Show(score->drawable);
    //score->drawable->isVisible = true;

    instructions = new Text("Click or press SPACE to flap", 70, 250);

    bird = new Sprite("Assets/Textures/bird.png", 500, 350, 2, 2);
    ground = new Sprite("Assets/Textures/ground.png", 0, 335 * 2, 2, 2.5);

    for (int i = 0; i < MAX_SCORE; i++)
    {
        Sprite* pipe = new Sprite("Assets/Textures/pipe.png", 0, 0, 2, 2);
        //pipe->drawable->isVisible = false;
        renderer->Hide(pipe->drawable);
        pipes.push_back(pipe);
    }

    background = new Sprite("Assets/Textures/background.png", -330, 0, 2, 2.5);

    audio->PlayMusic("Assets/Sounds/marios_way.mp3");

    //startPos = bird->drawable->ubo.model[3];
    startPos = renderer->GetPosition(bird->drawable);
}

void FlappyBird::Update(float deltaTime)
{
    // Scroll background and ground
    //background->drawable->ubo.model[3].x -= 0.7f;
    //ground->drawable->ubo.model[3].x -= 1.0f;
    renderer->Translate(background->drawable, glm::vec3(-0.7f,0,0));
    renderer->Translate(ground->drawable, glm::vec3(-1.0f,0,0));

    /*if (background->drawable->ubo.model[3].x
        < (-background->drawable->textureWidth))
    {
        background->drawable->ubo.model[3].x = -330;
    }

    if (ground->drawable->ubo.model[3].x
        < (-ground->drawable->textureWidth))
    {
        ground->drawable->ubo.model[3].x = 0.0f;
    }

    // Get the matrix for drawable
    glm::mat4& matrix = bird->drawable->ubo.model;

    // Check game state
    if (state == START)
    {
        matrix[3] = startPos;
        instructions->drawable->isVisible = true;

        for (int i = 0; i < MAX_SCORE; i++)
        {
            pipes[i]->drawable->isVisible = false;
        }

        if (input.Held(input.Key.SPACE) || input.mouse.Down)
        {
            instructions->drawable->isVisible = false;
            force = 0.0f;
            playerScore = 0;
            score->drawable->isVisible = false;
            score = scores[0];
            score->drawable->isVisible = true;
            state = PLAYING;

            for (int i = 0; i < MAX_SCORE; i+=2)
            {
                float gap = (rand() % 200) + 50.0f;
                Sprite* pipe1 = pipes[i];
                Sprite* pipe2 = pipes[i+1];

                pipe1->drawable->isVisible = true;
                pipe2->drawable->isVisible = true;

                pipe1->drawable->ubo.model[3].x = 1000.0f + i * 200.0f;
                pipe1->drawable->ubo.model[3].y = 335*2 - gap;

                pipe2->drawable->ubo.model[3].x = 1000.0f + i * 200.0f;
                pipe2->drawable->ubo.model[3].y = -pipe2->drawable->textureHeight * 2 + gap;
                pipe2->drawable->ubo.flipVertical.x = 1.0f;
            }
        }

        return;
    }

    for (int i = 0; i < MAX_SCORE; i++)
    {
        pipes[i]->drawable->ubo.model[3].x -= 1.0f;

        // Check collisions
        if (matrix[3].y < pipes[i]->drawable->ubo.model[3].y + pipes[i]->drawable->textureHeight * 2
            && matrix[3].y + bird->drawable->textureHeight * 2 > pipes[i]->drawable->ubo.model[3].y
            && matrix[3].x + bird->drawable->textureWidth  * 2 > pipes[i]->drawable->ubo.model[3].x
            && matrix[3].x < pipes[i]->drawable->ubo.model[3].x + pipes[i]->drawable->textureWidth * 2)
        {
            audio->PlaySound("Assets/Sounds/explosion8bit.wav");
            state = START;
            return;
        }
        else if (matrix[3].x > pipes[i]->drawable->ubo.model[3].x + pipes[i]->drawable->textureWidth * 2
                   && matrix[3].x - 50 < pipes[i]->drawable->ubo.model[3].x + pipes[i]->drawable->textureWidth * 2
                   && isGiveScore)
        {
            isGiveScore = false;
            audio->PlaySound("Assets/Sounds/score_flappy.wav");
            score->drawable->isVisible = false;
            playerScore++;
            score = scores[playerScore];
            score->drawable->isVisible = true;
        }

        if (matrix[3].x + bird->drawable->textureWidth  * 2 > pipes[i]->drawable->ubo.model[3].x
            && matrix[3].x < pipes[i]->drawable->ubo.model[3].x + pipes[i]->drawable->textureWidth * 2)
        {
            isGiveScore = true;
        }
    }

    if (jumped == false && (input.Held(input.Key.SPACE) || input.mouse.Down))
    {
        jumped = true;
        force = -4.0f;
        audio->PlaySound("Assets/Sounds/jump.wav");
    }

    if (input.Held(input.Key.SPACE) == false && input.mouse.Down == false)
    {
        jumped = false;
    }

    if (matrix[3].y > 600)
    {
        audio->PlaySound("Assets/Sounds/hurt.wav");
        state = START;
    }

    matrix[3].y += force;

    force += 0.1f;*/
}
