#include "raylib.h"
#include "raymath.h"
#include "Timer.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Bullet.h"

Bullet::Bullet()
{
	Bullet::BulletBaseSpeed = 200.0f;
}

Bullet::~Bullet() noexcept	
{
}

void Bullet::DrawBullet(std::vector <Bullet> bullets)
{
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].BulletDest = { bullets[i].BulletPos.x, bullets[i].BulletPos.y, bullets[i].BulletRect.width, bullets[i].BulletRect.height };
		DrawTexturePro(bullets[i].BulletTxt, bullets[i].BulletRect, bullets[i].BulletDest, bullets[i].BulletCentre, bullets[i].BulletRot, PINK);
	}
}

void Bullet::UpdateBullet(std::vector <Bullet> &bullets)
{
	for (int i = 0; i < bullets.size(); i++) {
		
		if (bullets[i].BulletPos.x < -bullets[i].BulletRad || bullets[i].BulletPos.x > GetScreenWidth() + bullets[i].BulletRad || bullets[i].BulletPos.y < -bullets[i].BulletRad || bullets[i].BulletPos.y > GetScreenHeight() + bullets[i].BulletRad) 
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			bullets[i].BulletPos.x += bullets[i].BulletSpeed.x * GetFrameTime();
			bullets[i].BulletPos.y -= bullets[i].BulletSpeed.y * GetFrameTime();
		}
	}
}

void Bullet::Shoot(Ship player)
{
	Bullet::SetBulletSize(player);
	Bullet::SetBulletPos(player);
	Bullet::SetBulletSpeed(player);
}

void Bullet::SetBulletPos(Ship player)
{
	Bullet::BulletPos = { player.Position.x + sin(player.Rotation * DEG2RAD) * player.ShipRect.width + 1, player.Position.y - cos(player.Rotation * DEG2RAD) * player.ShipRect.height };
	Bullet::BulletRot = player.Rotation;
}

void Bullet::SetBulletSpeed(Ship player)
{
	Bullet::BulletSpeed.x = Bullet::BulletBaseSpeed * sin(player.Rotation*DEG2RAD) * 200 * GetFrameTime();
	Bullet::BulletSpeed.y = Bullet::BulletBaseSpeed * cos(player.Rotation*DEG2RAD) * 200 * GetFrameTime();
}

void Bullet::SetBulletSize(Ship player)
{
	Bullet::BulletHeight = Bullet::BulletTxt.height / 1.1;
	Bullet::BulletWidth = Bullet::BulletTxt.width;

	Bullet::BulletSize = { Bullet::BulletHeight, Bullet::BulletWidth };
	Bullet::BulletRad = Bullet::BulletWidth / 2;

	Bullet::BulletRect = { 1, 1, (float)Bullet::BulletWidth, (float)Bullet::BulletHeight };
	Bullet::BulletCentre = { (float)Bullet::BulletWidth / 2, (float)Bullet::BulletHeight / 2 };
}

void Bullet::Load()
{
	BulletTxt = LoadTexture("../Images/GameImages/LaserPurple(1).png");
	BulletImg = LoadImage("../Images/GameImages/LaserPurple(1).png");
}
