#include "Game.h"
#include "raylib.h"
#include "Ship.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

Ship ship{};

Game::Game()
{

}

Game::Game(int screenWidth, int screenHeight, std::string title)
{
	assert(!GetWindowHandle());
	InitWindow(screenWidth, screenHeight, title.c_str());
}

Game::~Game()
{
	assert(GetWindowHandle());
	CloseWindow();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	ship.DrawShip();
	EndDrawing();
}

void Game::Launch()
{
	ship.Load();
	ship.SetSize();
	ship.SetPosition();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
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

	ship.UpdateShip();
}

void Game::OnDraw()
{
}

void Game::OnUpdate()
{
}
