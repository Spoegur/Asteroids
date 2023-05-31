#pragma once
#include "raylib.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

class Game {

public:
	Game();

	Game(int screenWidth, int screenHeight, std::string title);

	~Game();

	void Tick();

protected:
	void Draw();
	void Update();
private:
	void OnDraw();
	void OnUpdate();
};