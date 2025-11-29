#include "breakout.h"

Breakout::Breakout()
{
}

void Breakout::Init()
{
    audio->PlayMusic("Assets/Sounds/music.wav");

    float x = 10.0f;
    float y = 20.0f;
    for (int i = 1; i < NUMBER_OF_BLOCKS + 1; i++)
    {
        blocks.push_back(new Sprite("Assets/Textures/blocks.png", x, y, 2.5f, 2.5f, 33,15));

        x += 33 * 2.5;

        if (i % 13 == 0)
        {
            y += 40.0f;
            x = 10.0f;
        }
    }

    paddle = new Sprite("Assets/Textures/blocks.png", 100, 600, 1, 1, 128, 16);
    renderer->SetSpriteSheetFrameIndex(paddle->drawable, 6);
    //paddle->drawable->ubo.index.x = 6;

    for (int i = 0; i < 7; i++)
    {
        balls.push_back(new Sprite("Assets/Textures/blocks.png", 600, 400, 1, 1, 8, 8));
        ballDirection.push_back(glm::vec3(1,1,0));

        renderer->SetSpriteSheetFrameIndex(balls[i]->drawable, 192 / 8 * 4);
        renderer->Hide(balls[i]->drawable);
        //balls[i]->drawable->ubo.index[0] = 192 / 8 * 4;
        //balls[i]->drawable->isVisible = false;
    }

    //balls[0]->drawable->isVisible = true;
    renderer->Show(balls[0]->drawable);

    background = new Sprite("Assets/Textures/background_2.png", -5, -5, 3.8, 5.6);
}

void Breakout::Update()
{
    for (int i = 0; i < 7; i++)
    {
        if (renderer->isVisible(balls[i]->drawable))
        {
            renderer->Translate(balls[i]->drawable, ballDirection[i]);
            glm::vec3 pos = renderer->GetPosition(balls[i]->drawable);
            //balls[i]->drawable->ubo.model[3] += glm::vec4(ballDirection[i],1);
            //glm::vec4 pos = balls[i]->drawable->ubo.model[3];

            if (pos.x > 1080)
            {
                ballDirection[i].x *= -1;
            }
            else if (pos.x < 0)
            {
                ballDirection[i].x *= -1;
            }
            if (pos.y > 600)
            {
                ballDirection[i].y *= -1;
            }
            else if (pos.y < 0)
            {
                ballDirection[i].y *= -1;
            }
        }
    }

    glm::vec3 pos = renderer->GetPosition(paddle->drawable);
    renderer->SetPosition(paddle->drawable,
                          glm::vec3(input.mouse.x * 2 - renderer->GetTextureWidth(paddle->drawable) / 2,
                                    pos.y,
                                    pos.z));
    //paddle->drawable->ubo.model[3].x = input.mouse.x * 2 - paddle->drawable->textureWidth / 2;

}
