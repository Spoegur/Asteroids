#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Ship.h"

Ship::Ship()
{
	Ship::shipSpeed = 10;
	Ship::mShipAcceleration = 0;
	Ship::mShipMaxAcceleration = 50;
	Ship::mShipRotationSpeed = 250;
	Ship::mShipDrag = 0.2f;
	Ship::mStartTimer = true;
	Ship::shipLives = 3;
}

Ship::~Ship()
{
}

void Ship::Load()
{
	Ship::mShipTexture = LoadTexture("../Images/GameImages/ship.png");

	Ship::mDamage1 = LoadTexture("../Images/GameImages/ShipDamageLarge.png");
	Ship::mDamage2 = LoadTexture("../Images/GameImages/ShipDamageMedium.png");
	Ship::mDamage3 = LoadTexture("../Images/GameImages/ShipDamageSmall.png");

	Ship::mVecDamageTxt = { Ship::mDamage3, Ship::mDamage2, Ship::mDamage1 };
}

void Ship::ShipReset()
{
	SetPosition();
	Ship::mShipAcceleration = 0;
	Ship::shipRotation = 0;
	Load();
}

void Ship::SetSize()
{
	Ship::shipRect = { 0, 0, (float)Ship::mShipTexture.width, (float)Ship::mShipTexture.height };
	Ship::shipCentre = { (float)Ship::mShipTexture.width / 2, (float)Ship::mShipTexture.height / 2 };

	Ship::shipRadius = (float)Ship::mShipTexture.width / 2;
}

Vector2 Ship::SetPosition()
{
	Ship::shipPosition = { (float)(GetScreenWidth() / 2), (float)GetScreenHeight() / 2 };

	return shipPosition;
}

void Ship::DrawShip()
{
	OnDrawShip();
	DrawTexturePro(Ship::mShipTexture, Ship::shipRect, Ship::destination, Ship::shipCentre, Ship::shipRotation, DARKBROWN);
}

void Ship::UpdateShip(Timer timer, std::vector <Lives> &rVecLives)
{
	static Timer shipTimer = { 0 };
	float shipLife = 0;

	static Timer resetTimer = { 0 };
	float resetLife = 3;

	if (Ship::mShipAcceleration > 0 && Ship::mStartTimer == true) {
		timer.StartTimer(&shipTimer, shipLife);
		Ship::mStartTimer = false;
	}

	OnUpdateShip();

	if (Ship::destroyed != true) {

		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {

			if (Ship::mFacing != Ship::shipRotation) {
				Ship::mShipAcceleration -= timer.getTime(&shipTimer);
				if (Ship::mShipAcceleration <= 0) {
					Ship::mFacing = Ship::shipRotation;
					Ship::mShipAcceleration = 0;
				}
			}
			else if (Ship::mShipAcceleration < Ship::mShipMaxAcceleration) {
				Ship::mShipAcceleration += 2 * (Ship::mShipDrag * 2);
			}
			if (Ship::mShipAcceleration > Ship::mShipMaxAcceleration) {
				Ship::mShipAcceleration = Ship::mShipMaxAcceleration;
			}
		}
		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {

			if (Ship::mShipAcceleration > 0) {
				Ship::mShipAcceleration -= 0.8f;
			}
			else if (Ship::mShipAcceleration < 0) {
				Ship::mShipAcceleration = 0;
			}
		}
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {

			Ship::shipRotation += Ship::mShipRotationSpeed * GetFrameTime();
		}
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {

			Ship::shipRotation -= Ship::mShipRotationSpeed * GetFrameTime();
		}
	}

	if (Ship::shipRotation > 360) {
		Ship::shipRotation -= 360;
	}
	if (Ship::shipRotation < -360) {
		Ship::shipRotation += 360;
	}
	
	if (Ship::mStartTimer == false) {
		timer.UpdateStopWatch(&shipTimer);
	}
	
	if (Ship::mShipAcceleration <= 0) {
		Ship::mStartTimer = true;
	}

	if (Ship::shipPosition.x > GetScreenWidth() + Ship::mShipTexture.height) {
		Ship::shipPosition.x = -(Ship::mShipTexture.height);
	}
	else if (Ship::shipPosition.x < -(Ship::mShipTexture.height)) {
		Ship::shipPosition.x = GetScreenWidth() + Ship::mShipTexture.height;
	}

	if (Ship::shipPosition.y > GetScreenHeight() + Ship::mShipTexture.height) {
		Ship::shipPosition.y = -(Ship::mShipTexture.height);
	}
	else if (Ship::shipPosition.y < -(Ship::mShipTexture.height)) {
		Ship::shipPosition.y = GetScreenHeight() + Ship::mShipTexture.height;
	}

	if (Ship::shipLives < rVecLives.size()) {
		if (rVecLives.size() > 0) {
			rVecLives.erase(rVecLives.begin() + Ship::shipLives);
			Ship::mShipTexture = Ship::mVecDamageTxt[Ship::shipLives];
			Ship::destroyed = true;
			timer.StartTimer(&resetTimer, resetLife);
		}
	}
	else if (Ship::destroyed && timer.TimerDone(&resetTimer))
	{
		Ship::destroyed = false;
		ShipReset();
	}
	else
	{
		timer.UpdateTimer(&resetTimer);
	}

	Ship::shipPosition.y -= Ship::vecShipSpeed.y * Ship::mShipAcceleration;
	Ship::shipPosition.x += Ship::vecShipSpeed.x * Ship::mShipAcceleration;

}

void Ship::OnDrawShip()
{
	Ship::destination = { Ship::shipPosition.x, Ship::shipPosition.y, Ship::shipRect.width, Ship::shipRect.height };
}

void Ship::OnUpdateShip()
{
	Ship::vecShipSpeed.x = sin(Ship::mFacing * DEG2RAD) * Ship::shipSpeed * GetFrameTime();
	Ship::vecShipSpeed.y = cos(Ship::mFacing * DEG2RAD) * Ship::shipSpeed * GetFrameTime();
}

