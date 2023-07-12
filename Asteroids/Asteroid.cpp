#include "raylib.h"
#include "raymath.h"
#include "Timer.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Asteroid.h"

Asteroid::Asteroid()
{
	std::srand((unsigned)time(NULL));
	Asteroid::ID = rand() % 3;
	Asteroid::Rotation = rand() % 360;
	Asteroid::AsteroidSpeed = 100 + (rand() % 201);
	
}

Asteroid::~Asteroid() noexcept
{
}

void Asteroid::Load()
{
	BigAsteroidtxt = LoadTexture("../Images/GameImages/Meteors/BigMeteor1.png");
	BigAsteroidimg = LoadImage("../Images/GameImages/Meteors/BigMeteor1.png");

	MediumAsteroidtxt = LoadTexture("../Images/GameImages/Meteors/MedMeteor1.png");
	MediumAsteroidimg = LoadImage("../Images/GameImages/Meteors/MedMeteor1.png");

	SmallAsteroidtxt = LoadTexture("../Images/GameImages/Meteors/SmallMeteor1.png");
	SmallAsteroidimg = LoadImage("../Images/GameImages/Meteors/SmallMeteor1.png");

	textures = { BigAsteroidtxt, MediumAsteroidtxt, SmallAsteroidtxt };
	std::cout << ID << std::endl;
	Asteroid::AsteroidTexture = textures[Asteroid::ID];
}

void Asteroid::SetAsteroidSize()
{
	Asteroid::AsteroidHeight = Asteroid::AsteroidTexture.height / 1.1;
	Asteroid::AsteroidWidth = Asteroid::AsteroidTexture.width / 1.1;

	Asteroid::AsteroidRect = { 1, 1, (float)Asteroid::AsteroidWidth, (float)Asteroid::AsteroidHeight };
	Asteroid::AsteroidCentre = { (float)Asteroid::AsteroidWidth / 2, (float)Asteroid::AsteroidHeight / 2 };

	Asteroid::AsteroidRadius = Asteroid::AsteroidWidth / 2;
}

Vector2 Asteroid::SetAsteroidPosition(Ship player)
{
	Asteroid::Position = { (float)(rand() % (GetScreenWidth() - (int)player.ShipRect.width)), (float)(rand() % (GetScreenHeight() - (int)player.ShipRect.height))};
	Asteroid::Rotation = rand() % 360;
	Asteroid::Speed.x = sin(Asteroid::Rotation * DEG2RAD) * Asteroid::AsteroidSpeed;
	Asteroid::Speed.y = cos(Asteroid::Rotation * DEG2RAD) * Asteroid::AsteroidSpeed;
	return Asteroid::Position;
}

void Asteroid::DrawAsteroid(std::vector <Asteroid> list)
{
	OnDrawAsteroid();

	for (int i = 0; i < list.size(); i++) {
		list[i].AsteroidDest = { list[i].Position.x, list[i].Position.y, list[i].AsteroidRect.width, list[i].AsteroidRect.height };
		DrawTexturePro(list[i].AsteroidTexture, list[i].AsteroidRect, list[i].AsteroidDest, list[i].AsteroidCentre, list[i].Rotation, WHITE);
	}
}

void Asteroid::UpdateAsteroid(std::vector <Asteroid> &list, Ship &player)
{
	OnUpdateAsteroid();

	for (int i = 0; i < list.size(); i++) {

		list[i].Position.y -= list[i].Speed.y * GetFrameTime();
		list[i].Position.x += list[i].Speed.x * GetFrameTime();

		if (list[i].Position.x > GetScreenWidth() + list[i].AsteroidRadius) {
			list[i].Position.x = -(list[i].AsteroidRadius);
		}
		else if (list[i].Position.x < -(list[i].AsteroidRadius)) {
			list[i].Position.x = GetScreenWidth() + list[i].AsteroidRadius;
		}
		if (list[i].Position.y > GetScreenHeight() + list[i].AsteroidRadius) {
			list[i].Position.y = -(list[i].AsteroidRadius);
		}
		else if (list[i].Position.y < -(list[i].AsteroidRadius)) {
			list[i].Position.y = GetScreenHeight() + list[i].AsteroidRadius;
		}

		if (CheckCollisionCircles(list[i].Position, list[i].AsteroidRadius, player.Position, player.ShipRadius))
		{
			list.erase(list.begin() + i);
			player.lives--;
		}
	}
}

void Asteroid::OnDrawAsteroid()
{
}

void Asteroid::OnUpdateAsteroid()
{
	Asteroid::ID = rand() % 3;
	Asteroid::AsteroidSpeed = 100 + (rand() % 201);
}																				   