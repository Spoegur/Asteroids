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

	bool EntityMax;
	bool Shoot;

protected:
	void Draw();
	void Update();
	void GameOver();
private:
	void OnDraw();
	void OnUpdate();
};

class Lives {

public:
	void LoadLives();
	Texture2D Livestxt;
	Vector2 Livespos;
};
#endif // _GAME_