#include "raylib.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;

    InitWindow(ScreenWidth, ScreenHeight, "Asteroids");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

