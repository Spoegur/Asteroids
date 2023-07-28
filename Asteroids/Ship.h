#pragma once
#ifndef _SHIP_
#define _SHIP_
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Timer.h"
#include "Game.h"

class Ship {

public:

	Ship();

	~Ship() noexcept;

	Vector2 shipPosition;
	Vector2 vecShipSpeed;
	Vector2 shipCentre;
	Rectangle shipRect;
	Rectangle destination;
	float shipRotation;
	float shipSpeed;
	float shipRadius;
	float shipLives;
	int score;
	float round;
	bool destroyed;

	void DrawShip();
	void UpdateShip(Timer timer, std::vector <Lives> &rVecLives);

	Vector2 SetPosition();;
	void SetSize();
	void Load();
	void ShipReset();

	void Reset();

private:

	std::vector <Texture2D> mVecDamageTxt;

	bool mStartTimer;
	float mFacing;
	float mShipAcceleration;
	float mShipRotationSpeed;
	float mShipMaxAcceleration;
	float mShipDrag;

	Texture2D mShipTexture;
	Texture2D mDamage1;
	Texture2D mDamage2;
	Texture2D mDamage3;

	void OnDrawShip();
	void OnUpdateShip();
};
#endif // _SHIP_