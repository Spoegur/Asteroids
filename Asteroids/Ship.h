#pragma once
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

class Ship {

public:

	Ship();

	~Ship() noexcept;

	Vector2 Position;
	Vector2 Speed;
	Vector2 Centre;
	float Rotation;

	void DrawShip();
	void UpdateShip();

	Vector2 SetPosition();;
	void SetSize();
	void Load();

private:

	bool startTimer;
	float Facing;
	float ShipSpeed;
	float ShipAcceleration;
	float ShipRotationSpeed;
	float ShipMaxAcceleration;
	float ShipDrag;
	int ShootCooldown;
	Texture2D texture;
	Image image;
	Rectangle ShipRect;
	Rectangle Destination;


	void OnDrawShip();
	void OnUpdateShip();
};