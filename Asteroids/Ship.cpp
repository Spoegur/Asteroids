#include "Game.h"
#include "Ship.h"
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

Ship::Ship()
{
	ShipSpeed = 10;
	ShipAcceleration = 0;
	ShipMaxAcceleration = 50;
	ShipRotationSpeed = 250;
	ShipDrag = 0.2;
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
			ShipAcceleration -= 0.8;
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
	Speed.x = sin(Rotation * DEG2RAD) * ShipSpeed * GetFrameTime();
	Speed.y = cos(Rotation * DEG2RAD) * ShipSpeed * GetFrameTime();
}

