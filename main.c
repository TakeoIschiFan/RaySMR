#include "raylib.h"
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

    const Vector2 shapes[] = {
        {100, 700}, {700, 700},
    };
    const int num_lines = (sizeof(shapes) / sizeof(shapes[0])) / 2;

    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Raysmr");
    SetTargetFPS(TARGET_FPS);

    Vector2 pos = {400, 400};
    Vector2 vel = {0, 0};
    Vector2 acc = {0, GRAVITY_PPF2};

    while (!WindowShouldClose()){
        //update
        vel.x += acc.x;
        vel.y += acc.y;

        pos.x += vel.x;
        pos.y += vel.y;

        for (int i = 0; i < num_lines; i++){
            if(CheckCollisionPointLine(pos, shapes[i], shapes[i+1], LINE_THICKNESS + BALL_SIZE)){
                vel.x = vel.x;
                vel.y = -vel.y;
            }
        };


        //render
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(pos, BALL_SIZE, BLUE);

        for (int i = 0; i < num_lines; i++){
            DrawLineEx(shapes[i], shapes[i+1], LINE_THICKNESS, LINE_COLOR);
        };

        EndDrawing();
    }
    CloseWindow();

    return 0;

}
