#pragma once
#ifndef _ASTER_
#define _ASTER_
#include "raylib.h"
#include "raymath.h"
#include "Ship.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

class Asteroid {

public:

	Asteroid();
	~Asteroid() noexcept;

	Vector2 Position;
	Vector2 Speed;
	float Rotation;

	void DrawAsteroid(std::vector <Asteroid> list, Asteroid meteor);
	void UpdateAsteroid(std::vector <Asteroid> &list);

	Vector2 SetAsteroidPosition(Ship ship);
	void SetAsteroidSize();
	void Load();

private:
	
	std::vector<Texture2D> textures;

	float AsteroidSpeed;
	float AsteroidRadius;
	float AsteroidWidth;
	float AsteroidHeight;
	int ID;
	bool Destroyed;

	Rectangle AsteroidRect;
	Rectangle AsteroidDest;
	Vector2 AsteroidCentre;

	Texture2D BigAsteroidtxt;
	Texture2D MediumAsteroidtxt;
	Texture2D SmallAsteroidtxt;
	Texture2D AsteroidTexture;
	Image BigAsteroidimg;
	Image MediumAsteroidimg;
	Image SmallAsteroidimg;

	void OnDrawAsteroid();
	void OnUpdateAsteroid();
};
#endif // _ASTER_