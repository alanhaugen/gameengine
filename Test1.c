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
    const int width = 800;
    const int height = 1200;
    
    InitWindow(width, height, "Physics_sim");
    
    // ball1
    Vector2 ballPos = {(float)width / 1.2, (float)height/4};
    Vector2 velocity = {0.0f, 0.0f};
    
    //ball2
    Vector2 ball2Pos = {(float)width/2, (float)height/4};
    Vector2 velocity2 = {0.0f, 0.0f};
    
    Vector2 triPosA = {200.0f, 1200.0f};
    Vector2 triPosB = {800.0f, 1200.0f};
    Vector2 triPosC = {800.0f, 800.0f};
    Vector2 triPosD = {0.0f, 700.0f};
    Vector2 triPosE = {0.0f, 1200.0f};
    
    findAngle(triPosE, triPosA, triPosC); 
    
    
    
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("ayo it's a window", 190, 200, 20, RAYWHITE);
            DrawCircleV(ballPos, 50, RED);
            DrawTriangle(triPosA, triPosB, triPosC, RAYWHITE);
            //DrawTriangle(triPosA, triPosD, triPosE, RAYWHITE);
            
            if(CheckCollisionCircleLine(ballPos, 50, triPosA, triPosC)/* || 
            CheckCollisionCircleLine(ballPos, 50, triPosD, triPosA)*/)
            {
                DrawText("balls be balling", 190, 400, 20, RAYWHITE);
                velocity.x += velocity.y;
                velocity.y += -velocity.x/2;
                velocity.y *= -0.45;
                velocity.x *= -0.95;
                
            }
            
            ballPos.x += velocity.x;
            ballPos.y += velocity.y;
            //velocity.x += 0.5f;
            velocity.y += 9.81f / 10.0f;
            
            if(ballPos.y < 0 || ballPos.y > height)
            {
                velocity.y *= -0.95;
            }
            if(/*ballPos.x < 0 || */ballPos.x > width)
            {
                velocity.x *= -0.95;
            }
            
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}