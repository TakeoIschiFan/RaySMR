#include <stdio.h>
#include "raylib.h"

#define SCREEN_SIZE 800
#define TARGET_FPS 60


int main(void){

    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Raysmr");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();

    return 0;

}
