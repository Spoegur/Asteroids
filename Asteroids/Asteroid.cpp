#include "raylib.h"
#include "raymath.h"
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
	Asteroid::mAsteroidID = rand() % 3;
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::mAsteroidSpeed = 100 + (rand() % 201);
}

Asteroid::~Asteroid() noexcept
{
}

void Asteroid::Load()
{
	mBigAsteroidTxt = LoadTexture("../Images/GameImages/Meteors/BigMeteor1.png");

	mMediumAsteroidTxt = LoadTexture("../Images/GameImages/Meteors/MedMeteor1.png");

	mSmallAsteroidTxt = LoadTexture("../Images/GameImages/Meteors/SmallMeteor1.png");

	textures = { mBigAsteroidTxt, mMediumAsteroidTxt, mSmallAsteroidTxt };
	std::cout << mAsteroidID << std::endl;
	Asteroid::mAsteroidTxt = textures[Asteroid::mAsteroidID];
}

void Asteroid::AsteroidSplit(Asteroid &rAsteroid)
{
	rAsteroid.mAsteroidID = rAsteroid.mAsteroidID + 1;
	rAsteroid.mAsteroidTxt = textures[rAsteroid.mAsteroidID];
	rAsteroid.SetAsteroidSize();

	rAsteroid.SpawnAsteroid();
}

void Asteroid::SpawnAsteroid()
{
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::vecAsteroidSpeed.x = sin(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
	Asteroid::vecAsteroidSpeed.y = cos(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
}

void Asteroid::SetAsteroidSize()
{
	Asteroid::mAsteroidHeight = Asteroid::mAsteroidTxt.height / 1.1;
	Asteroid::mAsteroidWidth = Asteroid::mAsteroidTxt.width / 1.1;

	Asteroid::mAsteroidRect = { 1, 1, (float)Asteroid::mAsteroidWidth, (float)Asteroid::mAsteroidHeight };
	Asteroid::mAsteroidCentre = { (float)Asteroid::mAsteroidWidth / 2, (float)Asteroid::mAsteroidHeight / 2 };

	Asteroid::mAsteroidRadius = Asteroid::mAsteroidWidth / 2;
}

Vector2 Asteroid::SetAsteroidPosition(Ship player)
{
	Asteroid::asteroidPosition = { (float)(rand() % (GetScreenWidth() - (int)player.shipRect.width)), (float)(rand() % (GetScreenHeight() - (int)player.shipRect.height))};
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::vecAsteroidSpeed.x = sin(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
	Asteroid::vecAsteroidSpeed.y = cos(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
	return Asteroid::asteroidPosition;
}

void Asteroid::DrawAsteroid(std::vector <Asteroid> vecAsteroid)
{
	OnDrawAsteroid();

	for (int i = 0; i < vecAsteroid.size(); i++) {
		vecAsteroid[i].mAsteroidDest = { vecAsteroid[i].asteroidPosition.x, vecAsteroid[i].asteroidPosition.y, vecAsteroid[i].mAsteroidRect.width, vecAsteroid[i].mAsteroidRect.height };
		DrawTexturePro(vecAsteroid[i].mAsteroidTxt, vecAsteroid[i].mAsteroidRect, vecAsteroid[i].mAsteroidDest, vecAsteroid[i].mAsteroidCentre, vecAsteroid[i].asteroidRotation, WHITE);
	}
}

void Asteroid::UpdateAsteroid(std::vector <Asteroid> &rVecAsteroid, Ship &rPlayer, std::vector <Bullet> &rVecBullets)
{
	OnUpdateAsteroid();

	for (int i = 0; i < rVecAsteroid.size(); i++) {

		rVecAsteroid[i].asteroidPosition.y -= rVecAsteroid[i].vecAsteroidSpeed.y * GetFrameTime();
		rVecAsteroid[i].asteroidPosition.x += rVecAsteroid[i].vecAsteroidSpeed.x * GetFrameTime();

		if (rVecAsteroid[i].asteroidPosition.x > GetScreenWidth() + rVecAsteroid[i].mAsteroidRadius) {
			rVecAsteroid[i].asteroidPosition.x = -(rVecAsteroid[i].mAsteroidRadius);
		}
		else if (rVecAsteroid[i].asteroidPosition.x < -(rVecAsteroid[i].mAsteroidRadius)) {
			rVecAsteroid[i].asteroidPosition.x = GetScreenWidth() + rVecAsteroid[i].mAsteroidRadius;
		}
		if (rVecAsteroid[i].asteroidPosition.y > GetScreenHeight() + rVecAsteroid[i].mAsteroidRadius) {
			rVecAsteroid[i].asteroidPosition.y = -(rVecAsteroid[i].mAsteroidRadius);
		}
		else if (rVecAsteroid[i].asteroidPosition.y < -(rVecAsteroid[i].mAsteroidRadius)) {
			rVecAsteroid[i].asteroidPosition.y = GetScreenHeight() + rVecAsteroid[i].mAsteroidRadius;
		}

		if (CheckCollisionCircles(rVecAsteroid[i].asteroidPosition, rVecAsteroid[i].mAsteroidRadius, rPlayer.shipPosition, rPlayer.shipRadius) && rPlayer.destroyed != true)
		{
			if (rVecAsteroid[i].mAsteroidID != 2) {
				rVecAsteroid[i].AsteroidSplit(rVecAsteroid[i]);
				rVecAsteroid.push_back(rVecAsteroid[i]);
				rVecAsteroid.back().SpawnAsteroid();
			}
			else
			{
				rVecAsteroid.erase(rVecAsteroid.begin() + i);
				if (rVecAsteroid.empty()) {
					break;
				}
			}
			rPlayer.shipLives--;
		}

		for (int t = 0; t < rVecBullets.size(); t++) 
		{
			if (i >= rVecAsteroid.size()) {
				i = 0;
			}

			if (CheckCollisionCircles(rVecAsteroid[i].asteroidPosition, rVecAsteroid[i].mAsteroidRadius, rVecBullets[t].bulletPos, rVecBullets[t].bulletRad))
			{
				rVecBullets.erase(rVecBullets.begin() + t);

				if (rVecAsteroid[i].mAsteroidID == 0)
				{
					rVecAsteroid[i].AsteroidSplit(rVecAsteroid[i]);
					rVecAsteroid.push_back(rVecAsteroid[i]);
					rVecAsteroid.back().SpawnAsteroid();
				}
				else if (rVecAsteroid[i].mAsteroidID == 1)
				{
					rVecAsteroid[i].AsteroidSplit(rVecAsteroid[i]);
					rVecAsteroid.push_back(rVecAsteroid[i]);
					rVecAsteroid.back().SpawnAsteroid();
				}
				else if (rVecAsteroid[i].mAsteroidID == 2)
				{
					rVecAsteroid.erase(rVecAsteroid.begin() + i);
					if (rVecAsteroid.empty()) {
						break;
					}
				}
			}
		}
	}
}

void Asteroid::OnDrawAsteroid()
{
}

void Asteroid::OnUpdateAsteroid()
{
	Asteroid::mAsteroidID = rand() % 3;
	Asteroid::mAsteroidSpeed = 100 + (rand() % 201);
}																				   