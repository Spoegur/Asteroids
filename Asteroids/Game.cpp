#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Timer.h"

Ship ship;
Bullet bullet;
Asteroid asteroid;
Lives playerLives;
Timer timer;
std::vector <Asteroid> asteroids;
std::vector <Bullet> bullets;
std::vector <Lives> lives;

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
	bullet.Load();
	playerLives.LoadLives();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}

void Game::Draw()
{
	OnDraw();
	
	ship.DrawShip();
	asteroid.DrawAsteroid(asteroids);
	bullet.DrawBullet(bullets);
}

void Game::Update()
{
	OnUpdate();

	static float BulletTime = GetTime();
	
	ship.UpdateShip(timer, lives);

	if (IsKeyDown(KEY_SPACE)) {
		if (BulletTime < GetTime()) {
			bullet.Shoot(ship);
			bullets.push_back(bullet);
			BulletTime = GetTime() + 0.15;
		}
	}
	bullet.UpdateBullet(bullets);
	
	if (entityMax == false) {
		asteroid.Load();
		asteroid.SetAsteroidSize();
		asteroid.SetAsteroidPosition(ship);
		asteroids.push_back(asteroid);
	}

	asteroid.UpdateAsteroid(asteroids, ship, bullets);
}

void Game::OnDraw()
{
	ClearBackground(BLACK);
	DrawFPS(10, 10);

	for (int i = 0; i < lives.size(); i++)
	{
		DrawTexture(lives[i].livesTxt, lives[i].livesPos.x, lives[i].livesPos.y, WHITE);
	}
}

void Game::OnUpdate()
{
	if (asteroids.size() == 0) {
		entityMax = false;
	}
	if (asteroids.size() >= 8) {
		entityMax = true;
	}
	if (asteroids.size() < 0) {
		entityMax = false;
	}
}

void Lives::LoadLives()
{
	playerLives.livesTxt = LoadTexture("../Images/GameImages/ship.png");
	for (int i = 0; i < 3; i++)
	{
		lives.push_back(playerLives);
		if (i == 0)
		{
			lives[i].livesPos = { 3, 24 };
		}
		else if (i == 1) 
		{
			lives[i].livesPos = { 53, 24 };
		}
		else if (i == 2)
		{
			lives[i].livesPos = { 103, 24 };
		}
	}
}

