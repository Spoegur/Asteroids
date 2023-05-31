#pragma once
#include "raylib.h"
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

	void Launch();

	bool GameShouldClose() const;

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;

protected:
	void Draw();
	void Update();
private:
	void OnDraw();
	void OnUpdate();
};