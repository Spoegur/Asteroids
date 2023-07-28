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
// Creating instances of each entity
Ship ship;
Bullet bullet;
Asteroid asteroid;
Lives playerLives;
Timer timer;
// Creating lists
std::vector <Asteroid> asteroids;
std::vector <Bullet> bullets;
std::vector <Lives> lives;

Game::Game()
{
	Game::gameOver = false;
	Game::entityMax = false;
}
// Create the game window
Game::Game(int screenWidth, int screenHeight, std::string title)
{
	assert(!GetWindowHandle());
	InitWindow(screenWidth, screenHeight, title.c_str());
}
// Check whether the game screen is already open incase of resets
Game::~Game()
{
	assert(GetWindowHandle());
	CloseWindow();
}
// Game loop
void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}
// Game initialisation function for start up and resets
void Game::Init()
{
	ship.Load();
	ship.SetSize();
	ship.SetPosition();
	bullet.Load();
	playerLives.LoadLives();
}
// Game over screen
void Game::GameOver() 
{
	DrawText("Game Over!", GetScreenWidth() - MeasureText("Game Over!", 340) / 2, 20, 80, WHITE);
	DrawText("Press 'r' to Restart", GetScreenWidth() / 2, 100, 20, WHITE);
	if (IsKeyPressed(KEY_R)) {
		GameReset(); // Game reset function called
	}
	gameOver = true;
}
// Reset game function incase of game over
void Game::GameReset() 
{
	// Clear all lists and reset asteroid, player and bullet states
	asteroids.clear();
	bullets.clear();
	lives.clear();
	ship.Reset();
	asteroid.Reset();
	bullet.Reset();
	Init();
	gameOver = false;
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}
// Calling draw functions
void Game::Draw()
{
	OnDraw();

	if (!gameOver) {
		ship.DrawShip();
		asteroid.DrawAsteroid(asteroids);
		bullet.DrawBullet(bullets);
	}
}
// Calling update functions
void Game::Update()
{
	OnUpdate();

	if (!gameOver) {
		static float BulletTime = GetTime();

		ship.UpdateShip(timer, lives);

		if (!ship.destroyed) {
			// Bullet shoot cooldown implementation
			if (IsKeyDown(KEY_SPACE)) {
				if (BulletTime < GetTime()) {
					bullet.Shoot(ship);
					bullets.push_back(bullet);
					BulletTime = GetTime() + 0.15;
				}
			}
		}
		bullet.UpdateBullet(bullets);

		// Check whether there are no asteroids currently in existence
		if (entityMax == false) {
			for (int i = 1; i < ship.round + 4; i++) { // Respawn asteroids in relation to what round the player is on
				if (asteroids.size() <= 10) {
					asteroid.Load();
					asteroid.SetAsteroidSize();
					asteroid.SetAsteroidPosition(ship);
					asteroids.push_back(asteroid);
				}
				else if (asteroids.size() > 10) {
					i = ship.round + 4;
				}
			}
		}
		asteroid.UpdateAsteroid(asteroids, ship, bullets);
	}

	if (ship.shipLives <= 0) {
		GameOver();
	}
	else
	{
		gameOver = false;
	}
}
// Draw the players score and current lives
void Game::OnDraw()
{
	ClearBackground(BLACK);
	DrawFPS(10, 10);
	DrawText(std::to_string(ship.score).c_str(), GetScreenWidth() - MeasureText(std::to_string(ship.score).c_str(), 80) / 2, 10, 25, WHITE);

	for (int i = 0; i < lives.size(); i++)
	{
		DrawTexture(lives[i].livesTxt, lives[i].livesPos.x, lives[i].livesPos.y, WHITE);
	}
}

void Game::OnUpdate()
{
	if (asteroids.size() <= 0) {
		entityMax = false;
	}
	else {
		entityMax = true;
	}
}
// Load texture for player lives and put them in a vector
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

