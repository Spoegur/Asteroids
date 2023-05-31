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
	ShipSpeed = -250;
	ShipAcceleration = -80 * GetFrameTime();
	ShipMaxAcceleration = -350;
	ShipRotationSpeed = -50;
}

void Ship::Load()
{
	texture = LoadTexture("../Images/GameImages/ship.png");
	image = LoadImage("../Images/GameImages/ship.png");
}

void Ship::SetSize()
{
	ShipSize.x = (float)texture.width;
	ShipSize.y = (float)texture.height;
	ShipRect = { 0, 0, ShipSize.x, ShipSize.y };
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

		Position.y += ShipSpeed * GetFrameTime();
	}
	else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {

		Position.y -= ShipSpeed * GetFrameTime();
	}
	else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {

		Rotation -= 4;
	}
	else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {

		Rotation += 4;
	}
}

void Ship::OnDrawShip()
{
	Destination = { Position.x, Position.y, ShipRect.width, ShipRect.height };
	DrawTexturePro(texture, ShipRect, Destination, Centre, Rotation, WHITE);
}

void Ship::OnUpdateShip()
{

}

