#pragma once
#ifndef _BULLET_
#define _BULLET_
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Ship.h"

class Bullet {

public:

	Bullet();
	~Bullet() noexcept;

	Vector2 bulletPos;
	Vector2 bulletSpeed;
	float bulletRot;
	float bulletRad;

	void DrawBullet(std::vector <Bullet> vecBullets);
	void UpdateBullet(std::vector <Bullet> &rVecBullets);
	void Shoot(Ship player);

	void SetBulletPos(Ship player);
	void SetBulletSpeed(Ship player);
	void SetBulletSize(Ship player);
	void Load();

private:
	
	float mBulletHeight;
	float mBulletWidth;
	float mBulletBaseSpeed;
	Vector2 mBulletSize;

	Rectangle mBulletRect;
	Rectangle mBulletDest;
	Vector2 mBulletCentre;

	Texture2D mBulletTxt;
};
#endif // _BULLET_