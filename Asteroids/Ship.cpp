#include "Game.h"
#include "Ship.h"
#include "raylib.h"
#include "raymath.h"
#include "Timer.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

Timer timer;

Ship::Ship()
{
	ShipSpeed = 10;
	ShipAcceleration = 0;
	ShipMaxAcceleration = 50;
	ShipRotationSpeed = 250;
	ShipDrag = 0.2f;
	startTimer = true;
	lives = 3;
}

Ship::~Ship()
{
}

void Ship::Load()
{
	texture = LoadTexture("../Images/GameImages/ship.png");
	image = LoadImage("../Images/GameImages/ship.png");
}

void Ship::SetSize()
{
	ShipRect = { 0, 0, (float)texture.width, (float) texture.height };
	Centre = { (float)texture.width / 2, (float)texture.height / 2 };

	ShipRadius = (float)texture.width / 2;
}

Vector2 Ship::SetPosition()
{
	Position = { (float)(GetScreenWidth() / 2), (float)GetScreenHeight() / 2 };

	return Position;
}

void Ship::DrawShip()
{
	OnDrawShip();
}

void Ship::UpdateShip()
{
	static Timer shipTimer = { 0 };
	float shipLife = 0;

	if (ShipAcceleration > 0 && startTimer == true) {
		timer.StartTimer(&shipTimer, shipLife);
		startTimer = false;
	}

	OnUpdateShip();

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {

		if (Facing != Rotation) {
			ShipAcceleration -= timer.getTime(&shipTimer);
			if (ShipAcceleration <= 0) {
				Facing = Rotation;
				ShipAcceleration = 0;
			}
		}
		else if (ShipAcceleration < ShipMaxAcceleration) {
			ShipAcceleration += 2 * (ShipDrag * 2);
		}
		if (ShipAcceleration > ShipMaxAcceleration){
			ShipAcceleration = ShipMaxAcceleration;
		}
	}
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {

		if (ShipAcceleration > 0) {
			ShipAcceleration -= 0.8f;
		}
		else if (ShipAcceleration < 0) {
			ShipAcceleration = 0;
		}
	}
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {

		Rotation += ShipRotationSpeed * GetFrameTime();
	}
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {

		Rotation -= ShipRotationSpeed * GetFrameTime();
	}

	if (Rotation > 360) {
		Rotation -= 360;
	}
	if (Rotation < -360) {
		Rotation += 360;
	}
	
	if (startTimer == false) {
		timer.UpdateTimer(&shipTimer);
	}
	
	if (ShipAcceleration <= 0) {
		startTimer = true;
	}

	if (Position.x > GetScreenWidth() + texture.height) {
		Position.x = -(texture.height);
	}
	else if (Position.x < -(texture.height)) {
		Position.x = GetScreenWidth() + texture.height;
	}

	if (Position.y > GetScreenHeight() + texture.height) {
		Position.y = -(texture.height);
	}
	else if (Position.y < -(texture.height)) {
		Position.y = GetScreenHeight() + texture.height;
	}

	Position.y -= Speed.y * ShipAcceleration;
	Position.x += Speed.x * ShipAcceleration;


}

void Ship::OnDrawShip()
{
	Destination = { Position.x, Position.y, ShipRect.width, ShipRect.height };
	DrawTexturePro(texture, ShipRect, Destination, Centre, Rotation, WHITE);
}

void Ship::OnUpdateShip()
{
	Speed.x = sin(Facing * DEG2RAD) * ShipSpeed * GetFrameTime();
	Speed.y = cos(Facing * DEG2RAD) * ShipSpeed * GetFrameTime();
}

