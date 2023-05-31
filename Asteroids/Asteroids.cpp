#include "raylib.h"
#include "Game.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

int main()
{
    const int ScreenWidth = 800;
    const int ScreenHeight = 600;
    
    Game game{ ScreenWidth, ScreenHeight, "Asteroids" };
    game.Launch();
    SetTargetFPS(60);

    while (!game.GameShouldClose()) {
        
        game.Tick();

    }
    
    return 0;
}

