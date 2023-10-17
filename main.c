#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

// graphics constants
#define SCREEN_SIZE 800
#define LINE_THICKNESS 12
#define LINE_COLOR BLACK
#define BALL_SIZE 30
#define BALL_BORDER_SIZE 1.5

// physics constants
#define TARGET_FPS 60
#define DRAW_RATE 40.0
#define GRAVITY_PPF2 0.1

int main(void){

    const Vector2 lines[] = {
        {100.0, 700.0}, {700.0, 700.0},
        {700.0, 700.0}, {400.0, 100.0},
        {400.0, 100.0}, {100.0, 700.0},
    };
    const int num_points = (sizeof(lines) / sizeof(lines[0]));

    // calculate surface normals
    Vector2 normals[num_points/2];

    for (int i = 0; i < num_points; i+=2){
        Vector2 norm = {
            lines[i + 1].y - lines[i].y,
            - (lines[i+1].x - lines[i].x)
        };
        normals[i/2] = Vector2Normalize(norm);
    };

    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Raysmr");
    SetTargetFPS(TARGET_FPS);

    InitAudioDevice();
    Sound woosh = LoadSound("assets/boop.wav");

    Vector2 pos = {400, 400};
    Vector2 vel = {-0.8, 0};
    Vector2 acc = {0, GRAVITY_PPF2};

    float time_since_last_frame = 0;

    Vector3 hsv_color = ColorToHSV(BLUE);

    ClearBackground(RAYWHITE);


    while (!WindowShouldClose()){


        //update
        time_since_last_frame += GetFrameTime();

        vel.x += acc.x;
        vel.y += acc.y;

        pos.x += vel.x;
        pos.y += vel.y;

        for (int i = 0; i < num_points; i+=2){
            if(CheckCollisionPointLine(pos, lines[i], lines[i+1], LINE_THICKNESS + BALL_SIZE)){
                pos.x -= vel.x;
                pos.y -= vel.y;

                vel = Vector2Reflect(vel, normals[i/2]);
                PlaySound(woosh);
            }
        };

        //render
        BeginDrawing();

        if(time_since_last_frame >= 1/DRAW_RATE){

            time_since_last_frame = 0;
                    // apparently, changing the hue from 0 -> 300 in HSV space is a semi-convincing rainbow effect.
            if (hsv_color.x >= 300){
                hsv_color.x = 0;
            }
            hsv_color.x += 1;

            DrawCircleV(pos, BALL_SIZE + BALL_BORDER_SIZE, BLACK);
            DrawCircleV(pos, BALL_SIZE, ColorFromHSV(hsv_color.x, hsv_color.y, hsv_color.z));
        }

        for (int i = 0; i < num_points; i+=2){
            DrawLineEx(lines[i], lines[i+1], LINE_THICKNESS, LINE_COLOR);
        };
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;

}
