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
	Ship::score = 0;
	Ship::round = 1;
}

Ship::~Ship()
{
}

// Load ship textures and damage textures for when the player is hit
void Ship::Load()
{
	Ship::mShipTexture = LoadTexture("../Images/GameImages/ship.png");

	Ship::mDamage1 = LoadTexture("../Images/GameImages/ShipDamageLarge.png");
	Ship::mDamage2 = LoadTexture("../Images/GameImages/ShipDamageMedium.png");
	Ship::mDamage3 = LoadTexture("../Images/GameImages/ShipDamageSmall.png");

	Ship::mVecDamageTxt = { Ship::mDamage3, Ship::mDamage2, Ship::mDamage1 };
}

// Resetting the ship to the centre of the screen after they collide with an asteroid
void Ship::ShipReset()
{
	SetPosition();
	Ship::mShipAcceleration = 0;
	Ship::shipRotation = 0;
	Load();
}

void Ship::Reset() // Ship Init Function
{
	Ship::shipSpeed = 10;
	Ship::mShipAcceleration = 0;
	Ship::mShipMaxAcceleration = 50;
	Ship::mShipRotationSpeed = 250;
	Ship::mShipDrag = 0.2f;
	Ship::mStartTimer = true;
	Ship::shipLives = 3;
	Ship::score = 0;
	Ship::round = 1;
}

// Set ship size in relation to its current texture
void Ship::SetSize()
{
	Ship::shipRect = { 0, 0, (float)Ship::mShipTexture.width, (float)Ship::mShipTexture.height };
	Ship::shipCentre = { (float)Ship::mShipTexture.width / 2, (float)Ship::mShipTexture.height / 2 };

	Ship::shipRadius = (float)Ship::mShipTexture.width / 2;
}

// Spawn the ship in the middle of the screen
Vector2 Ship::SetPosition()
{
	Ship::shipPosition = { (float)(GetScreenWidth() / 2), (float)GetScreenHeight() / 2 };

	return shipPosition;
}

// Ship draw function
void Ship::DrawShip()
{
	OnDrawShip();
	DrawTexturePro(Ship::mShipTexture, Ship::shipRect, Ship::destination, Ship::shipCentre, Ship::shipRotation, DARKBROWN);
}

void Ship::UpdateShip(Timer timer, std::vector <Lives> &rVecLives)
{
	static Timer shipTimer = { 0 }; // Stopwatch for drag/ship movement physics
	float shipLife = 0;

	static Timer resetTimer = { 0 }; // 3 second timer for when the ship is destroyed before respawn
	float resetLife = 3;

	if (Ship::mShipAcceleration > 0 && Ship::mStartTimer == true) { // Make sure the stopwatch only starts if the player is moving
		timer.StartTimer(&shipTimer, shipLife);
		Ship::mStartTimer = false;
	}

	OnUpdateShip();

	if (Ship::destroyed != true) { // Making sure the ship isnt currently destroyed

		if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) { // Forward movement

			if (Ship::mFacing != Ship::shipRotation) {
				Ship::mShipAcceleration -= timer.getTime(&shipTimer); // Ship drag implementation, the ships acceleration gets reduced by how long the ship had been moving for
				if (Ship::mShipAcceleration <= 0) {
					Ship::mFacing = Ship::shipRotation; // Statement to let the ship rotate without actually moving
					Ship::mShipAcceleration = 0;
				}
			}
			// Ship Max acceleration
			else if (Ship::mShipAcceleration < Ship::mShipMaxAcceleration) { 
				Ship::mShipAcceleration += 2 * (Ship::mShipDrag * 2);
			}
			if (Ship::mShipAcceleration > Ship::mShipMaxAcceleration) {
				Ship::mShipAcceleration = Ship::mShipMaxAcceleration;
			}
		}
		// Slowing down
		if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {

			if (Ship::mShipAcceleration > 0) {
				Ship::mShipAcceleration -= 0.8f;
			}
			else if (Ship::mShipAcceleration < 0) {
				Ship::mShipAcceleration = 0;
			}
		}
		// Rotate ship to the right
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {

			Ship::shipRotation += Ship::mShipRotationSpeed * GetFrameTime();
		}
		// Rotate ship to the left
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
	// Stopwatch update function
	if (Ship::mStartTimer == false) {
		timer.UpdateStopWatch(&shipTimer);
	}
	// If the ship isnt currently moving, restart the stopwatch
	if (Ship::mShipAcceleration <= 0) {
		Ship::mStartTimer = true;
	}
	// Ship collision with screen borders and screen wrapping
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
	// Checking whether the ship has been hit, if so remove a life, change the ship texture and set its current state to destroyed
	if (Ship::shipLives < rVecLives.size()) {
		if (rVecLives.size() > 0) {
			rVecLives.erase(rVecLives.begin() + Ship::shipLives);
			Ship::mShipTexture = Ship::mVecDamageTxt[Ship::shipLives];
			Ship::destroyed = true;
			timer.StartTimer(&resetTimer, resetLife);
		}
	}
	// Checking whether the ship has been destroyed for 3 seconds if so respawn the ship
	else if (Ship::destroyed && timer.TimerDone(&resetTimer))
	{
		Ship::destroyed = false;
		ShipReset();
	}
	else
	{
		timer.UpdateTimer(&resetTimer);
	}
	// Movement
	Ship::shipPosition.y -= Ship::vecShipSpeed.y * Ship::mShipAcceleration;
	Ship::shipPosition.x += Ship::vecShipSpeed.x * Ship::mShipAcceleration;

}

void Ship::OnDrawShip()
{
	// Destination rectangle initialisation
	Ship::destination = { Ship::shipPosition.x, Ship::shipPosition.y, Ship::shipRect.width, Ship::shipRect.height };
}

void Ship::OnUpdateShip()
{
	// Ship speed initialisation
	Ship::vecShipSpeed.x = sin(Ship::mFacing * DEG2RAD) * Ship::shipSpeed * GetFrameTime();
	Ship::vecShipSpeed.y = cos(Ship::mFacing * DEG2RAD) * Ship::shipSpeed * GetFrameTime();
}

