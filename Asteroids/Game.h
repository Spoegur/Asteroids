#pragma once
#ifndef _GAME_
#define _GAME_
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

class Game {

public:
	Game();

	Game(int screenWidth, int screenHeight, std::string title);

	~Game() noexcept;

	void Tick();

	void Init();

	bool GameShouldClose() const;

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

	bool entityMax;
	bool Shoot;

protected:
	void Draw();
	void Update();
private:
	void OnDraw();
	void OnUpdate();
};

class Lives {

public:
	void LoadLives();
	Texture2D livesTxt;
	Vector2 livesPos;
};
#endif // _GAME_