#include "Game.h"
#include "raylib.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

Game::Game()
{
}

Game::Game(int screenWidth, int screenHeight, std::string title)
{
	InitWindow(screenWidth, screenHeight, title.c_str());
}

Game::~Game()
{
	CloseWindow();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}

void Game::Draw()
{
	OnDraw();
	
	ClearBackground(BLACK);
	DrawFPS(10, 10);

}

void Game::Update()
{
	OnUpdate();
}

void Game::OnDraw()
{
}

void Game::OnUpdate()
{
}
