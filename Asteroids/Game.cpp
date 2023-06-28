#include "Game.h"
#include "raylib.h"
#include "Ship.h"
#include "Asteroid.h"
#include "raymath.h"
#include "Timer.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

Ship ship;
Asteroid asteroid;
std::vector <Asteroid> asteroids;

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
	EndDrawing();
}

void Game::Init()
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
	
	ship.DrawShip();
	asteroid.DrawAsteroid(asteroids, asteroid);
}

void Game::Update()
{
	OnUpdate();
	
	ship.UpdateShip();

	if (EntityMax == false) {
		asteroid.Load();
		asteroid.SetAsteroidSize();
		asteroid.SetAsteroidPosition(ship);
		asteroids.push_back(asteroid);
	}

	asteroid.UpdateAsteroid(asteroids);
}

void Game::OnDraw()
{
	ClearBackground(BLACK);
	DrawFPS(10, 10);
}

void Game::OnUpdate()
{
	if (asteroids.size() == 5) {
		EntityMax = true;
	}
	else if (asteroids.size() < 5) {
		EntityMax = false;
	}
}

