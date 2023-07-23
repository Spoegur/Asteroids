#pragma once
#ifndef _ASTER_
#define _ASTER_
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Ship.h"
#include "Bullet.h"

class Asteroid {

public:

	Asteroid();
	~Asteroid() noexcept;

	Vector2 asteroidPosition;
	Vector2 vecAsteroidSpeed;
	float asteroidRotation;

	void DrawAsteroid(std::vector <Asteroid> vecAsteroid);
	void UpdateAsteroid(std::vector <Asteroid> &rVecAsteroid, Ship &rPlayer, std::vector <Bullet> &rVecBullets);

	Vector2 SetAsteroidPosition(Ship player);
	void SetAsteroidSize();
	void Load();
	void SpawnAsteroid();
	void AsteroidSplit(Asteroid &rAsteroid);

private:
	
	std::vector<Texture2D> textures;

	float mAsteroidSpeed;
	float mAsteroidRadius;
	float mAsteroidWidth;
	float mAsteroidHeight;
	int mAsteroidID;
	bool mDestroyed;

	Rectangle mAsteroidRect;
	Rectangle mAsteroidDest;
	Vector2 mAsteroidCentre;

	Texture2D mBigAsteroidTxt;
	Texture2D mMediumAsteroidTxt;
	Texture2D mSmallAsteroidTxt;
	Texture2D mAsteroidTxt;

	void OnDrawAsteroid();
	void OnUpdateAsteroid();
};
#endif // _ASTER_