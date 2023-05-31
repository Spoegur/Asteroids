#include "raylib.h"
#include "Game.h"
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
    
    Game game{ ScreenWidth, ScreenHeight, "Asteroids" };
    SetTargetFPS(60);

    Game* gameptr = NULL;

    while (!WindowShouldClose()) {
        
        gameptr->Tick();

    }
    
    return 0;
}

