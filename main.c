#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

// graphics constants
#define SCREEN_SIZE 800
#define LINE_THICKNESS 12
#define LINE_COLOR BLACK
#define BALL_SIZE 30

// physics constants
#define TARGET_FPS 60
#define GRAVITY_PPF2 0.1

int main(void){

    const Vector2 lines[] = {
        {100.0, 700.0}, {700.0, 700.0},
        {700.0, 700.0}, {400.0, 100.0},
        {400.0, 100.0}, {100.0, 700.0},
    };
    const int num_points = (sizeof(lines) / sizeof(lines[0]));

    // calculate surface normals
    Vector2 normals[num_points/2] = {0};

    for (int i = 0; i < num_points; i+=2){
        Vector2 norm = {
            lines[i + 1].y - lines[i].y,
            - (lines[i+1].x - lines[i].x)
        };
        normals[i/2] = Vector2Normalize(norm);
    };



    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Raysmr");
    SetTargetFPS(TARGET_FPS);

    Vector2 pos = {400, 400};
    Vector2 vel = {-0.8, 0};
    Vector2 acc = {0, GRAVITY_PPF2};

    while (!WindowShouldClose()){
        //update
        vel.x += acc.x;
        vel.y += acc.y;

        pos.x += vel.x;
        pos.y += vel.y;

        for (int i = 0; i < num_points; i+=2){
            if(CheckCollisionPointLine(pos, lines[i], lines[i+1], LINE_THICKNESS + BALL_SIZE)){
                pos.x -= vel.x;
                pos.y -= vel.y;

                vel = Vector2Reflect(vel, normals[i/2]);
            }
        };

        //render
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(pos, BALL_SIZE, BLUE);

        for (int i = 0; i < num_points; i+=2){
            DrawLineEx(lines[i], lines[i+1], LINE_THICKNESS, LINE_COLOR);
        };

        EndDrawing();
    }
    CloseWindow();

    return 0;

}
