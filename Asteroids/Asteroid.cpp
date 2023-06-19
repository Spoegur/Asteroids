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
}

Asteroid::~Asteroid() noexcept
{
}

void Asteroid::SetStatus()
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
	Asteroid::AsteroidHeight = Asteroid::AsteroidTexture.height;
	Asteroid::AsteroidWidth = Asteroid::AsteroidTexture.width;

	Asteroid::AsteroidRect = { 1, 1, (float)Asteroid::AsteroidTexture.width, (float)Asteroid::AsteroidTexture.height };
	Asteroid::AsteroidCentre = { (float)Asteroid::AsteroidTexture.width / 2, (float)Asteroid::AsteroidTexture.height / 2 };
}

Vector2 Asteroid::SetAsteroidPosition()
{
	Asteroid::Position = { (float)(GetScreenWidth() / 2), (float)(GetScreenHeight() / 2) };
	return Asteroid::Position;
}

void Asteroid::DrawAsteroid()
{
	OnDrawAsteroid();
}

void Asteroid::UpdateAsteroid()
{
	OnUpdateAsteroid();
}

void Asteroid::OnDrawAsteroid()
{
	Asteroid::AsteroidDest = { Asteroid::Position.x, Asteroid::Position.y, Asteroid::AsteroidRect.width, Asteroid::AsteroidRect.height };
	DrawTexturePro(Asteroid::AsteroidTexture, Asteroid::AsteroidRect, Asteroid::AsteroidDest, Asteroid::AsteroidCentre, 1, RED);
}

void Asteroid::OnUpdateAsteroid()
{
}