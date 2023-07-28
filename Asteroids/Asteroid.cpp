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
	std::srand((unsigned)time(NULL)); // Random num generator
	Asteroid::mAsteroidID = 2;
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::mAsteroidSpeed = 100 + (rand() % 201);
}

Asteroid::~Asteroid() noexcept
{
}

// Loading differently sized asteroid textures and putting them in a vector
void Asteroid::Load()
{
	mBigAsteroidTxt = LoadTexture("../Images/GameImages/Meteors/BigMeteor1.png");

	mMediumAsteroidTxt = LoadTexture("../Images/GameImages/Meteors/MedMeteor1.png");

	mSmallAsteroidTxt = LoadTexture("../Images/GameImages/Meteors/SmallMeteor1.png");

	textures = { mSmallAsteroidTxt, mMediumAsteroidTxt, mBigAsteroidTxt };
	std::cout << mAsteroidID << std::endl;
	Asteroid::mAsteroidTxt = textures[Asteroid::mAsteroidID]; // Setting the Asteroid texture to start as its biggest iteration
}

// Asteroid splitting function for collisions
void Asteroid::AsteroidSplit(Asteroid &rAsteroid)
{
	rAsteroid.mAsteroidID = rAsteroid.mAsteroidID - 1;
	rAsteroid.mAsteroidTxt = textures[rAsteroid.mAsteroidID]; // Changes its texture to the next smallest texture
	rAsteroid.SetAsteroidSize(); // Resets size

	rAsteroid.SpawnAsteroid(); // Resets Rotation and speed
}

void Asteroid::Reset() // Asteroid Init Function
{
	std::srand((unsigned)time(NULL));
	Asteroid::mAsteroidID = 2;
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::mAsteroidSpeed = 100 + (rand() % 201);
}

// Function for spawning new asteroids with new Rotations and Speeds
void Asteroid::SpawnAsteroid()
{
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::vecAsteroidSpeed.x = sin(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
	Asteroid::vecAsteroidSpeed.y = cos(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
}

// Setting Asteroid Sizes in relation to their textures
void Asteroid::SetAsteroidSize()
{
	Asteroid::mAsteroidHeight = Asteroid::mAsteroidTxt.height / 1.1;
	Asteroid::mAsteroidWidth = Asteroid::mAsteroidTxt.width / 1.1;

	// Hitbox and Centre
	Asteroid::mAsteroidRect = { 1, 1, (float)Asteroid::mAsteroidWidth, (float)Asteroid::mAsteroidHeight };
	Asteroid::mAsteroidCentre = { (float)Asteroid::mAsteroidWidth / 2, (float)Asteroid::mAsteroidHeight / 2 };

	Asteroid::mAsteroidRadius = Asteroid::mAsteroidWidth / 2;
}

// Setting Asteroid position in relation to the player so they dont spawn on top of the player
Vector2 Asteroid::SetAsteroidPosition(Ship player)
{
	Asteroid::asteroidPosition = { (float)(rand() % (GetScreenWidth() - (int)player.shipRect.width)), (float)(rand() % (GetScreenHeight() - (int)player.shipRect.height))};
	Asteroid::asteroidRotation = rand() % 360;
	Asteroid::vecAsteroidSpeed.x = sin(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
	Asteroid::vecAsteroidSpeed.y = cos(Asteroid::asteroidRotation * DEG2RAD) * Asteroid::mAsteroidSpeed;
	return Asteroid::asteroidPosition;
}

// Initialises the Destination rect and draws each existing Asteroid
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
		// Asteroid Movement
		rVecAsteroid[i].asteroidPosition.y -= rVecAsteroid[i].vecAsteroidSpeed.y * GetFrameTime();
		rVecAsteroid[i].asteroidPosition.x += rVecAsteroid[i].vecAsteroidSpeed.x * GetFrameTime();

		// Screen wrapping for the asteroids if they are out of bounds
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

		// Check if the asteroid is colliding with the player
		if (CheckCollisionCircles(rVecAsteroid[i].asteroidPosition, rVecAsteroid[i].mAsteroidRadius, rPlayer.shipPosition, rPlayer.shipRadius) && rPlayer.destroyed != true)
		{
			if (rVecAsteroid[i].mAsteroidID != 0) { // If the colliding asteroid is a large asteroid, then split
				rVecAsteroid[i].AsteroidSplit(rVecAsteroid[i]);
				rVecAsteroid.push_back(rVecAsteroid[i]);
				rVecAsteroid.back().SpawnAsteroid();
			}
			else // Else if the asteroid is a small asteroid then it gets erased
			{
				rVecAsteroid.erase(rVecAsteroid.begin() + i);
				if (rVecAsteroid.empty()) {
					break;
				}
			}
			rPlayer.shipLives--;
		}

		// Check if the asteroid is colliding with any bullets
		for (int t = 0; t < rVecBullets.size(); t++) 
		{
			if (i >= rVecAsteroid.size()) { // Making sure there is no vector subscript errors
				i = 0;
			}

			if (CheckCollisionCircles(rVecAsteroid[i].asteroidPosition, rVecAsteroid[i].mAsteroidRadius, rVecBullets[t].bulletPos, rVecBullets[t].bulletRad))
			{
				rVecBullets.erase(rVecBullets.begin() + t);

				// Asteroid splitting statements
				if (rVecAsteroid[i].mAsteroidID == 2)
				{
					rVecAsteroid[i].AsteroidSplit(rVecAsteroid[i]);
					rVecAsteroid.push_back(rVecAsteroid[i]);
					rVecAsteroid.back().SpawnAsteroid();
					rPlayer.score += 20;
				}
				else if (rVecAsteroid[i].mAsteroidID == 1)
				{
					rVecAsteroid[i].AsteroidSplit(rVecAsteroid[i]);
					rVecAsteroid.push_back(rVecAsteroid[i]);
					rVecAsteroid.back().SpawnAsteroid();
					rPlayer.score += 50;
				}
				else if (rVecAsteroid[i].mAsteroidID == 0)
				{
					rVecAsteroid.erase(rVecAsteroid.begin() + i);
					rPlayer.score += 100;
					if (rVecAsteroid.empty()) {
						rPlayer.round++;
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
	Asteroid::mAsteroidSpeed = 100 + (rand() % 201);
}																				   