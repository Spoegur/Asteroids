#pragma once
#ifndef _BULLET_
#define _BULLET_
#include "raylib.h"
#include "raymath.h"
#include "Ship.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

class Bullet {

public:

	Bullet();
	~Bullet() noexcept;

	Vector2 BulletPos;
	Vector2 BulletSpeed;
	float BulletRot;

	void DrawBullet(std::vector <Bullet> bullets);
	void UpdateBullet(std::vector <Bullet> &bullets);
	void Shoot(Ship player);

	void SetBulletPos(Ship player);
	void SetBulletSpeed(Ship player);
	void SetBulletSize(Ship player);
	void Load();

private:
	
	float BulletRad;
	float BulletHeight;
	float BulletWidth;
	float BulletBaseSpeed;
	Vector2 BulletSize;

	Rectangle BulletRect;
	Rectangle BulletDest;
	Vector2 BulletCentre;

	Texture2D BulletTxt;
	Image BulletImg;

};
#endif // _BULLET_