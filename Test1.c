#include "raylib.h"
#include <math.h>
#include <stdio.h>

//#define PI 3.14159265359

// counter clockwise
float findAngle(Vector2 A, Vector2 B, Vector2 C){
    float AB = sqrt(((B.x - A.x)*(B.x - A.x)) + ((B.y - A.y)*(B.y - A.y)));
    float BC = sqrt(((C.x - B.x)*(C.x - B.x)) + ((C.y - B.y)*(C.y - B.y)));
    float angleRad = (BC / AB);
    float angle = acos(angleRad);
    float angleDeg = angleRad * (180 / PI);
    printf("angle is: %f\n", angle);
    return angleDeg;
}

int main(void)
{
    int bounciness = 5.0f;
    const int width = 800;
    const int height = 800;
    
    InitWindow(width, height, "Physics_sim");
    
    // ball1
    Vector2 ballPos = {(float)width / 1.2, (float)height/4};
    Vector2 velocity = {0.0f, 0.0f};
    
    //ball2
    Vector2 ball2Pos = {(float)width/2, (float)height/4};
    Vector2 velocity2 = {0.0f, 0.0f};
    
    Vector2 triPosA = {200.0f, height};
    Vector2 triPosB = {800.0f, height};
    Vector2 triPosC = {800.0f, 400.0f};
    Vector2 triPosD = {0.0f, 500.0f};
    Vector2 triPosE = {0.0f, height};
    
    findAngle(triPosE, triPosA, triPosC); 
    
    
    
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("ayo it's a window", 190, 200, 20, RAYWHITE);
            DrawCircleV(ballPos, 50, RED);
            //DrawTriangle(triPosA, triPosB, triPosC, RAYWHITE);
            //DrawTriangle(triPosA, triPosD, triPosE, RAYWHITE);
            
            /*if(CheckCollisionCircleLine(ballPos, 50, triPosA, triPosC)/* || 
            CheckCollisionCircleLine(ballPos, 50, triPosD, triPosA))
            {
                DrawText("balls be balling", 190, 400, 20, RAYWHITE);
                velocity.x += velocity.y;
                velocity.y += -velocity.x/2;
                velocity.y *= -0.45;
                velocity.x *= -0.95;
                
            }*/
            
            ballPos.x += velocity.x;
            ballPos.y += velocity.y;
            //velocity.x += 0.5f;
            velocity.y += 9.81f / 10.0f;
            
            if(ballPos.y < 0 || ballPos.y > height - 50)
            {
                velocity.y *= -0.95;
                if(abs(velocity.y) < 10)
                {
                    velocity.y = 0.0f;
                }
                else
                {
                    velocity.y += bounciness;
                    //printf("bounciness: %i\n", bounciness);
                    //bounciness -= 1;
                }
            }
            if(ballPos.x < 0 || ballPos.x > width - 50)
            {
                velocity.x *= -0.95;
                if(abs(velocity.x) < 10)
                {
                    velocity.x = 0.0f;
                }
                else
                {
                    velocity.x += bounciness;
                }
            }
            
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}