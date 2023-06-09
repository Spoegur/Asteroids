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

Timer timer{};

Ship::Ship()
{
	ShipSpeed = 10;
	ShipAcceleration = 0;
	ShipMaxAcceleration = 50;
	ShipRotationSpeed = 250;
	ShipDrag = 0.2f;
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
	Timer shipTimer = { 0 };
	float shipLife = 1.0f;

	timer.StartTimer(&shipTimer, shipLife);
	

	OnUpdateShip();

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {

		if (ShipAcceleration < ShipMaxAcceleration) {
			ShipAcceleration += 2 * (ShipDrag * 2);
		}
		else if (ShipAcceleration > ShipMaxAcceleration){
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
	
	timer.UpdateTimer(&shipTimer);

	if (!timer.TimerDone(&shipTimer)) {
		Position.y -= Speed.y * ShipAcceleration;
		Position.x += Speed.x * ShipAcceleration;
	}
	if (timer.TimerDone(&shipTimer)) {
		std::cout << "Timer is done         " << std::endl;
	}
}

void Ship::OnDrawShip()
{
	Destination = { Position.x, Position.y, ShipRect.width, ShipRect.height };
	DrawTexturePro(texture, ShipRect, Destination, Centre, Rotation, RED);
}

void Ship::OnUpdateShip()
{
	Speed.x = sin(Rotation * DEG2RAD) * ShipSpeed * GetFrameTime();
	Speed.y = cos(Rotation * DEG2RAD) * ShipSpeed * GetFrameTime();
}

