#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "raylib.h"
#include "Game.h"

using namespace std;

int main()
{
    const int ScreenWidth = 1400;
    const int ScreenHeight = 800;
   
    Game game{ ScreenWidth, ScreenHeight, "Asteroids" };
    game.Init();
    SetTargetFPS(60);
    // Main gameplay loop
    while (!game.GameShouldClose()) {
        
        game.Tick();
    }
    
    return 0;
}

