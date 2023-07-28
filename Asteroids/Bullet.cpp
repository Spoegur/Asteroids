#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Bullet.h"

Bullet::Bullet()
{
	Bullet::mBulletBaseSpeed = 200.0f;
}

Bullet::~Bullet() noexcept	
{
}

// Initialises the Destination Rect and Draws each bullet that currently exists in the bullet list
void Bullet::DrawBullet(std::vector <Bullet> vecBullets)
{
	for (int i = 0; i < vecBullets.size(); i++) {
		vecBullets[i].mBulletDest = { vecBullets[i].bulletPos.x, vecBullets[i].bulletPos.y, vecBullets[i].mBulletRect.width, vecBullets[i].mBulletRect.height };
		DrawTexturePro(vecBullets[i].mBulletTxt, vecBullets[i].mBulletRect, vecBullets[i].mBulletDest, vecBullets[i].mBulletCentre, vecBullets[i].bulletRot, PINK);
	}
}

void Bullet::UpdateBullet(std::vector <Bullet> &rVecBullets)
{
	for (int i = 0; i < rVecBullets.size(); i++) { // Checking whether the bullet is out of bounds if so it erases it else
		
		if (rVecBullets[i].bulletPos.x < -rVecBullets[i].bulletRad || rVecBullets[i].bulletPos.x > GetScreenWidth() + rVecBullets[i].bulletRad || rVecBullets[i].bulletPos.y < -rVecBullets[i].bulletRad || rVecBullets[i].bulletPos.y > GetScreenHeight() + rVecBullets[i].bulletRad) 
		{
			rVecBullets.erase(rVecBullets.begin() + i);
		}
		else // Bullet Movement
		{
			rVecBullets[i].bulletPos.x += rVecBullets[i].bulletSpeed.x * GetFrameTime();
			rVecBullets[i].bulletPos.y -= rVecBullets[i].bulletSpeed.y * GetFrameTime();
		}
	}
}

// Bullet initialisation
void Bullet::Shoot(Ship player)
{
	Bullet::SetBulletSize();
	Bullet::SetBulletPos(player);
	Bullet::SetBulletSpeed(player);
}

// Sets the bullet position in reference to the player rotation
void Bullet::SetBulletPos(Ship player)
{
	Bullet::bulletPos = { player.shipPosition.x + sin(player.shipRotation * DEG2RAD) * player.shipRect.width + 1, player.shipPosition.y - cos(player.shipRotation * DEG2RAD) * player.shipRect.height };
	Bullet::bulletRot = player.shipRotation;
}

// Sets the bullet speed in reference to the player rotation
void Bullet::SetBulletSpeed(Ship player)
{
	Bullet::bulletSpeed.x = Bullet::mBulletBaseSpeed * sin(player.shipRotation*DEG2RAD) * 200 * GetFrameTime();
	Bullet::bulletSpeed.y = Bullet::mBulletBaseSpeed * cos(player.shipRotation*DEG2RAD) * 200 * GetFrameTime();
}

// Sets the bullet size using the bullet texture
void Bullet::SetBulletSize()
{
	Bullet::mBulletHeight = Bullet::mBulletTxt.height / 1.1; // Divided by 1.1 to remove rogue texture lines
	Bullet::mBulletWidth = Bullet::mBulletTxt.width;

	Bullet::mBulletSize = { Bullet::mBulletHeight, Bullet::mBulletWidth };
	Bullet::bulletRad = Bullet::mBulletWidth / 2; // Bullet Radius

	// Setting the bullets hitbox and centre for future draw function
	Bullet::mBulletRect = { 1, 1, (float)Bullet::mBulletWidth, (float)Bullet::mBulletHeight }; 
	Bullet::mBulletCentre = { (float)Bullet::mBulletWidth / 2, (float)Bullet::mBulletHeight / 2 };
}

void Bullet::Load()
{
	mBulletTxt = LoadTexture("../Images/GameImages/LaserPurple(1).png"); // Load bullet texture
}

void Bullet::Reset()
{
	Bullet::mBulletBaseSpeed = 200.0f; // Bullet Init func
}
