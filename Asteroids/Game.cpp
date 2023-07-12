#include "Game.h"
#include "raylib.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "raymath.h"
#include "Timer.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

Ship ship;
Bullet bullet;
Asteroid asteroid;
Lives life;
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
	life.LoadLives();
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
	
	ship.UpdateShip();

	if (IsKeyDown(KEY_SPACE)) {
		if (BulletTime < GetTime()) {
			bullet.Shoot(ship);
			bullets.push_back(bullet);
			BulletTime = GetTime() + 0.15;
		}
	}
	bullet.UpdateBullet(bullets);
	
	if (EntityMax == false) {
		asteroid.Load();
		asteroid.SetAsteroidSize();
		asteroid.SetAsteroidPosition(ship);
		asteroids.push_back(asteroid);
	}

	asteroid.UpdateAsteroid(asteroids, ship);
	GameOver();
}

void Game::OnDraw()
{
	ClearBackground(BLACK);
	DrawFPS(10, 10);

	for (int i = 0; i < lives.size(); i++)
	{
		DrawTexture(lives[i].Livestxt, lives[i].Livespos.x, lives[i].Livespos.y, WHITE);
	}
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

void Lives::LoadLives()
{
	life.Livestxt = LoadTexture("../Images/GameImages/ship.png");
	for (int i = 0; i < 3; i++)
	{
		lives.push_back(life);
		if (i == 0)
		{
			lives[i].Livespos = { 3, 24 };
		}
		else if (i == 1) 
		{
			lives[i].Livespos = { 53, 24 };
		}
		else if (i == 2)
		{
			lives[i].Livespos = { 103, 24 };
		}
	}
}

void Game::GameOver() {
	if (ship.lives < lives.size()) {
		lives.erase(lives.begin() + ship.lives);
	}
};

